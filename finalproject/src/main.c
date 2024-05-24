#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>

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
    printf("\t-p <port> : Specify the port number\n");
}
int main(int argc, char *argv[])
{
    char *filepath = NULL;
    char *portarg = NULL;
    bool list = false;
    bool newfile = false;
    int c;
    int dbfd = -1;

    while ((c = getopt(argc, argv, "nf:a:l")) != -1)
    {
        switch (c)
        {
        case 'n':
            newfile = true;
            break;
        case 'f':
            filepath = optarg;
            break;
        case 'p':
            portarg = optarg;
            break;
        case 'l':
            list = true;
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
    }
    else
    {
        dbfd = open_db_file(filepath);
        if (dbfd == STATUS_ERROR)
        {
            printf("unable to open database file\n");
            return -1;
        }
    }

    return 0;
}
