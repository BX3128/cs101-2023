#include <stdio.h>
#include <string.h>

typedef struct employee {
    int    em_id;
    char   em_name[10];
    int    em_age;
    char   em_phone[12];
    float  em_salary;
} employee_t;

void employee_info(employee_t my_emp) {
    printf("Employee ID:     %d\n", my_emp.em_id);
    printf("Employee Name:   %s\n", my_emp.em_name);
    printf("Employee Age:    %d\n", my_emp.em_age);
    printf("Employee Phone:  %s\n", my_emp.em_phone);
    printf("Employee Salary: %.2f\n", my_emp.em_salary);
    return;
}

int main() {
    printf("size of employee_t = %ld\n\n", sizeof(employee_t));

    employee_t my_emp;

    my_emp.em_id = 100;
    strcpy(my_emp.em_name, "IU Lee");
    my_emp.em_age = 18;
    strcpy(my_emp.em_phone, "0937123456");
    my_emp.em_salary = 1000.30;

    employee_info(my_emp);

    printf("\n");
    return 0;
}
