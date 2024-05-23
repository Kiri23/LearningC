#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_EMPLOYEES 1000

struct employee_t {
  int id;
  int income;
  bool staff;
};

int initialize_employee(struct employee_t *e) {
  static int numEmployee = 0;
  numEmployee++;
  e->id = numEmployee;
  e->income = 0;
  e->staff = false;
  return numEmployee;
}

int main() {
  // this value came from the database header
  int n = 4;

  struct employee_t *employees = malloc(sizeof(struct employee_t) * n);
  if (employees == NULL) {
    printf("The allocator failed\n");
    return -1;
  }

  for (int i = 0; i < n; i++) {
    // Use the initialize_employee function
    int id = initialize_employee(&employees[0]);
    printf("new employee id is %d \n", id);
  }
  // Free allocated memory
  free(employees);
  employees = NULL;

  return 0;
}
