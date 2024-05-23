#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_EMPLOYEES 1000

struct employee_t {
  int id;
  int income;
  bool staff;
};

void initialize_employee(struct employee_t *e) {
  e->id = 0;
  e->income = 0;
  e->staff = false;
  return;
}

int main() {
  // this value came from the database header
  int n = 4;

  struct employee_t *employees = malloc(sizeof(struct employee_t) * n);
  if (employees == NULL) {
    printf("The allocator failed\n");
    return -1;
  }

  // Use the initialize_employee function
  initialize_employee(&employees[0]);

  // Example usage
  employees[0].id = 1;
  employees[0].income = 5000;
  employees[0].staff = true;

  printf("Employee ID: %d, Income: %d, Staff: %d\n", employees[0].id, employees[0].income, employees[0].staff);

  // Free allocated memory
  free(employees);
  employees = NULL;

  return 0;
}
