#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "common.h"
#include "parse.h"

void update_employee(struct dbheader_t *dbhdr, struct employee_t *employees, char *update)
{
    char *nameToFind = strtok(update, ",");

    char *name = strtok(NULL, ",");
    char *addr = strtok(NULL, ",");

    char *hours = strtok(NULL, ",");

    printf("searching for %s\n", nameToFind);
    printf("update string: %s %s %s\n", name, addr, hours);
    if (!nameToFind || !name || !addr || !hours)
    {
        printf("Invalid update format.\n");
        return;
    }
    // Check if the source strings fit in the destination buffers
    if (strlen(name) >= sizeof(employees[0].name))
    {
        printf("New name is too long.\n");
        return;
    }
    if (strlen(addr) >= sizeof(employees[0].address))
    {
        printf("Address is too long.\n");
        return;
    }
    int i = 0;
    for (; i < dbhdr->count; i++)
    {
        // if we found a match , case insensitive
        if (strcasecmp(employees[i].name, nameToFind) == 0)
        {
            strncpy(employees[i].address, addr, sizeof(employees[i].address));
            strncpy(employees[i].name, name, sizeof(employees[i].name));
            employees[i].hours = atoi(hours);
            printf("Updated employee %s\n", name);
            break; // break once we found a match
        }
    }
}
int delete_employee(struct dbheader_t *dbhdr, struct employee_t *employees, char *delete)
{
    int employee_index = -1;
    if (dbhdr->count < 1)
    {
        printf("Invalid Command: No Employees in the DB\n");
        return STATUS_ERROR;
    }

    printf("searching for %s\n", delete);
    for (int i = 0; i < dbhdr->count; i++)
    {
        printf("comparing %s\n", employees[i].name);
        if (strcasecmp(delete, employees[i].name) == 0)
        {
            printf("index of employee to delete %d\n", i);
            employee_index = i;
            break;
        }
    }

    if (employee_index != -1)
    {
        for (int i = employee_index; i < dbhdr->count - 1; i++)
        {
            employees[i] = employees[i + 1];
        }

        return STATUS_SUCCESS;
    }

    return STATUS_ERROR;
}
void list_employee(struct dbheader_t *dbhdr, struct employee_t *employees)
{
    int i = 0;
    for (; i < dbhdr->count; i++)
    {
        printf("Employee %d\n", i);
        printf("\tName: %s\n", employees[i].name);
        printf("\tAddress: %s\n", employees[i].address);
        printf("\tHours: %d\n", employees[i].hours);
    }
}

int add_employee(struct dbheader_t *dbhdr, struct employee_t *employees, char *addstring)
{
    printf("%s\n", addstring);

    char *name = strtok(addstring, ",");

    char *addr = strtok(NULL, ",");

    char *hours = strtok(NULL, ",");

    printf("%s %s %s\n", name, addr, hours);

    strncpy(employees[dbhdr->count - 1].name, name, sizeof(employees[dbhdr->count - 1].name));
    strncpy(employees[dbhdr->count - 1].address, addr, sizeof(employees[dbhdr->count - 1].address));

    employees[dbhdr->count - 1].hours = atoi(hours);

    return STATUS_SUCCESS;
}

int read_employees(int fd, struct dbheader_t *dbhdr, struct employee_t **employeesOut)
{
    if (fd < 0)
    {
        printf("Got a bad FD from the user\n");
        return STATUS_ERROR;
    }

    int count = dbhdr->count;

    struct employee_t *employees = calloc(count, sizeof(struct employee_t));
    if (employees == -1)
    {
        printf("Malloc failed\n");
        return STATUS_ERROR;
    }

    read(fd, employees, count * sizeof(struct employee_t));

    int i = 0;
    for (; i < count; i++)
    {
        employees[i].hours = ntohl(employees[i].hours);
    }

    *employeesOut = employees;
    return STATUS_SUCCESS;
}

int output_file(int fd, struct dbheader_t *dbhdr, struct employee_t *employees)
{
    if (fd < 0)
    {
        printf("Got a bad FD from the user\n");
        return STATUS_ERROR;
    }

    int realcount = dbhdr->count;

    dbhdr->magic = htonl(dbhdr->magic);
    dbhdr->filesize = htonl(sizeof(struct dbheader_t) + (sizeof(struct employee_t) * realcount));
    dbhdr->count = htons(dbhdr->count);
    dbhdr->version = htons(dbhdr->version);

    // go to the beginning of the file
    lseek(fd, 0, SEEK_SET);
    // write the header
    if (write(fd, dbhdr, sizeof(struct dbheader_t)) != sizeof(struct dbheader_t))
    {
        perror("write db header");
        return STATUS_ERROR;
    }

    int i = 0;
    for (; i < realcount; i++)
    {
        employees[i].hours = htonl(employees[i].hours);
        // save epmloyees data
        if (write(fd, &employees[i], sizeof(struct employee_t)) != sizeof(struct employee_t))
        {
            perror("write employee");
            return STATUS_ERROR;
        }
    }
    // Calculate the new size of the file
    off_t new_size = sizeof(struct dbheader_t) + (sizeof(struct employee_t) * realcount);

    // Truncate (remove old data) the file to the new size
    if (ftruncate(fd, new_size) == -1)
    {
        perror("ftruncate");
        return STATUS_ERROR;
    }
    return STATUS_SUCCESS;
}

int validate_db_header(int fd, struct dbheader_t **headerOut)
{
    if (fd < 0)
    {
        printf("Got a bad FD from the user\n");
        return STATUS_ERROR;
    }

    struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));
    if (header == -1)
    {
        printf("Malloc failed create a db header\n");
        return STATUS_ERROR;
    }

    if (read(fd, header, sizeof(struct dbheader_t)) != sizeof(struct dbheader_t))
    {
        perror("read validate header");
        free(header);
        return STATUS_ERROR;
    }

    header->version = ntohs(header->version);
    header->count = ntohs(header->count);
    header->magic = ntohl(header->magic);
    header->filesize = ntohl(header->filesize);

    if (header->magic != HEADER_MAGIC)
    {
        printf("Impromper header magic\n");
        free(header);
        return -1;
    }

    if (header->version != 1)
    {
        printf("Impromper header version\n");
        free(header);
        return -1;
    }

    struct stat dbstat = {0};
    fstat(fd, &dbstat);
    if (header->filesize != dbstat.st_size)
    {
        printf("Corrupted database\n");
        free(header);
        return -1;
    }

    *headerOut = header;
    return STATUS_SUCCESS;
}

int create_db_header(int fd, struct dbheader_t **headerOut)
{
    // is like a malloc but it also initializes the memory to 0
    // 1 is the number of elements to allocate, sizeof(struct dbheader_t) is the size of each element
    struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));
    if (header == -1)
    {
        printf("Malloc failed to create db header\n");
        return STATUS_ERROR;
    }

    header->version = 0x1;
    header->count = 0;
    header->magic = HEADER_MAGIC;
    header->filesize = sizeof(struct dbheader_t);

    *headerOut = header;

    return STATUS_SUCCESS;
}
