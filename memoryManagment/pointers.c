#include <stdbool.h>
#include <stdio.h>

struct employee_t {
  int id;
  int income;
  bool staff;
};

void initialize_employee(struct employee_t *e) {
  e->id = 0;
  e->income = 0;
  e->staff = "";  // que seria ss (true o false)
}

int main() {
  // int x = 3;
  // int *px = &x;
  // printf("%d\n", *px);
  // printf("%p\n", px);

  struct employee_t ralph;
  initialize_employee(&ralph);

  printf("%d\n", ralph.staff);
}