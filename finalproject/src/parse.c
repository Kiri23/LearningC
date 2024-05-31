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
    printf("Count: %d\n", count);

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
    printf("Real count: %d\n", realcount);

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
        printf("Writing employee %d\n", i);
        printf("Name: %s\n", employees[i].name);
        printf("Address: %s\n", employees[i].address);
        printf("Hours: %d\n", employees[i].hours);
        // save epmloyees data
        if (write(fd, &employees[i], sizeof(struct employee_t)) != sizeof(struct employee_t))
        {
            perror("write employee");
            return STATUS_ERROR;
        }
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
