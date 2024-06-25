#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>

#include "common.h"
#include "file.h"
#include "parse.h"

void print_usage(char *argv)
{
    printf("Usage: %s -f <database-file> [-n] [-l] [-p <port>]\n", argv);
    printf("Options:\n");
    printf("\t-f <database-file> : required Path to the database file\n");
    printf("\t-n : Create a new database file\n");
    printf("\t-l : List all records\n");
    printf("\t-a <name>,<address>,<hours> : Add a new record\n");
    printf("\t-u <name>,<address>,<hours> : Update a record\n");
    printf("\t-d <name> : Delete a record\n");
}
int main(int argc, char *argv[])
{
    char *filepath = NULL;
    char *addstring = NULL;
    bool list = false;
    bool newfile = false;
    char *update = NULL;
    char *delete = NULL;
    int c;
    int dbfd = -1;
    struct dbheader_t *dbhdr = NULL;
    struct employee_t *employees = NULL;

    // Todo: Delete and update options
    while ((c = getopt(argc, argv, "nf:a:lu:d:")) != -1)
    {
        switch (c)
        {
        case 'n':
            newfile = true;
            break;
        case 'f':
            filepath = optarg;
            break;
        case 'a':
            addstring = optarg;
            break;
        case 'l':
            list = true;
            break;
        case 'u':
            update = optarg;
            break;
        case 'd':
            delete = optarg;
            break;
        case '?':
            printf("Unknown option -%c\n", c);
            break;
        default:
            return -1;
        }
    }
    if (filepath == NULL)
    {
        printf("FilePath is a required argument\n");
        print_usage(argv[0]);
        return 0;
    }

    if (newfile)
    {
        dbfd = create_db_file(filepath);
        if (dbfd == STATUS_ERROR)
        {
            printf("unable to create database file\n");
            return -1;
        }
        printf("Database file created with fd: %d\n", dbfd);
        if (create_db_header(dbfd, &dbhdr) == STATUS_ERROR)
        {
            printf("unable to create database header\n");
            return -1;
        }
    }
    else
    {
        dbfd = open_db_file(filepath);
        if (dbfd == STATUS_ERROR)
        {
            printf("unable to open database file\n");
            return -1;
        }
        if (validate_db_header(dbfd, &dbhdr) == STATUS_ERROR)
        {
            printf("unable to validate database header\n");
            return -1;
        }
    }

    if (read_employees(dbfd, dbhdr, &employees) != STATUS_SUCCESS)
    {
        printf("unable to read employees\n");
        return 0;
    }

    if (addstring)
    {
        dbhdr->count++;
        employees = realloc(employees, dbhdr->count * sizeof(struct employee_t));
        add_employee(dbhdr, employees, addstring);
    }
    if (update)
    {
        update_employee(dbhdr, employees, update);
    }
    if (delete)
    {
        if (delete_employee(dbhdr, employees, delete) == STATUS_ERROR)
        {
            printf("Could not remove employee");
            return -1;
        }

        dbhdr->count--;
        employees = realloc(employees, dbhdr->count * (sizeof(struct employee_t)));
    }
    if (list)
    {
        list_employee(dbhdr, employees);
    }
    if (output_file(dbfd, dbhdr, employees) != STATUS_SUCCESS)
    {
        printf("Error writing to file\n");
        return -1;
    }
    printf("File written\n");

    return 0;
}
