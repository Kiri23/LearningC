#ifndef PARSE_H
#define PARSE_H

// binary file representation xxd ./test.db
// 4c4c 4144 0001 0000 0000 000c
// struct dbheader_t header = {
//     .magic = 0x4c4c4144,    // Magic number
//     .version = 0x0001,      // Version
//     .count = 0x0000,        // Count
//     .filesize = 0x0000000c  // Filesize
// };

// LLAD - Low Level Academic Database
#define HEADER_MAGIC 0x4c4c4144

struct dbheader_t
{
    unsigned int magic;
    unsigned short version;
    unsigned short count;
    unsigned int filesize;
};

struct employee_t
{
    char name[256];
    char address[256];
    unsigned int hours;
};

int create_db_header(int fd, struct dbheader_t **headerOut);
int validate_db_header(int fd, struct dbheader_t **headerOut);
int add_employee(struct dbheader_t *, struct employee_t *employee, char *addstring);
int read_employees(int fd, struct dbheader_t *, struct employee_t **employeesOut);
int output_file(int fd, struct dbheader_t *, struct employee_t *employees);
void list_employee(struct dbheader_t *, struct employee_t *employees);
void update_employee(struct dbheader_t *, struct employee_t *employees, char *update);
int delete_employee(struct dbheader_t *, struct employee_t *employees, char *delete);

#endif
