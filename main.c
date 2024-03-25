#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_DATE_LEN 10
#define MAX_POSITION_LEN 50
#define MAX_LINE_LEN 256
#define MAX_EMPLOYEES 100
#define MAX_DEPARTMENTS 20
#define MAX_COMPANIES 10

typedef struct {
    int company_id;
    char company_name[MAX_NAME_LEN];
} Company;

typedef struct {
    int department_id;
    int company_id;
    char department_name[MAX_NAME_LEN];
} Department;

typedef struct {
    char employee_id[MAX_NAME_LEN];
    char name[MAX_NAME_LEN];
    int department_id;
    char start_date[MAX_DATE_LEN];
    char position[MAX_POSITION_LEN];
} Employee;

Company companies[MAX_COMPANIES];
Department departments[MAX_DEPARTMENTS];
Employee employees[MAX_EMPLOYEES];

int company_count = 0;
int department_count = 0;
int employee_count = 0;


void read_companies(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open the file");
        exit(1);
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, MAX_LINE_LEN, file) != NULL) {
        sscanf(line, "%d,%49[^\n]", &companies[company_count].company_id, companies[company_count].company_name);
        company_count++;
    }

    fclose(file);
}

void read_departments(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open the file");
        exit(1);
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, MAX_LINE_LEN, file) != NULL) {
        sscanf(line, "%d,%d,%49[^\n]", &departments[department_count].department_id, &departments[department_count].company_id, departments[department_count].department_name);
        department_count++;
    }

    fclose(file);
}

void read_employees(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open the file");
        exit(1);
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, MAX_LINE_LEN, file) != NULL) {
        sscanf(line, "%49[^,],%49[^,],%d,%10[^,],%49[^\n]", 
               employees[employee_count].employee_id, employees[employee_count].name, &employees[employee_count].department_id, 
               employees[employee_count].start_date, employees[employee_count].position);
        employee_count++;
    }

    fclose(file);
}

void search_employee_by_id(const char* id) {
    for (int i = 0; i < employee_count; i++) {
        if (strcmp(employees[i].employee_id, id) == 0) {
            printf("Employee Found: %s, %s\n", employees[i].employee_id, employees[i].name);
            return;
        }
    }
    printf("Employee not found.\n");
}


void list_employees_by_position(const char* position) {
    printf("Employees with position %s:\n", position);
    for (int i = 0; i < employee_count; i++) {
        if (strcmp(employees[i].position, position) == 0) {
            printf("%s, %s\n", employees[i].employee_id, employees[i].name);
        }
    }
}


void list_employees_in_department(int department_id) {
    printf("Employees in Department %d:\n", department_id);
    for (int i = 0; i < employee_count; i++) {
        if (employees[i].department_id == department_id) {
            printf("%s, %s\n", employees[i].employee_id, employees[i].name);
        }
    }
}


void print_total_employees(void) {
    printf("Total number of employees: %d\n", employee_count);
}


void print_total_employees_in_department(int department_id) {
    int count = 0;
    for (int i = 0; i < employee_count; i++) {
        if (employees[i].department_id == department_id) {
            count++;
        }
    }
    printf("Total number of employees in Department %d: %d\n", department_id, count);
}


void print_total_engineers_in_department(int department_id) {
    int count = 0;
    for (int i = 0; i < employee_count; i++) {
        if (employees[i].department_id == department_id && strcmp(employees[i].position, "Engineer") == 0) {
            count++;
        }
    }
    printf("Total number of engineers in Department %d: %d\n", department_id, count);
}

void remove_department_from_company(int company_id, int department_id) {
    int i;
    for (i = 0; i < department_count; i++) {
        if (departments[i].company_id == company_id && departments[i].department_id == department_id) {
            break;
        }
    }
    if (i < department_count) {
        for (int j = i; j < department_count - 1; j++) {
            departments[j] = departments[j + 1];
        }
        department_count--;
        printf("Department %d removed from company %d.\n", department_id, company_id);
        
    } else {
        printf("Department not found in company.\n");
    }
}

void add_employee_to_department(Employee new_employee) {
    if (employee_count >= MAX_EMPLOYEES) {
        printf("Maximum number of employees reached.\n");
        return;
    }
    employees[employee_count++] = new_employee;
    printf("Employee %s added to department %d.\n", new_employee.name, new_employee.department_id);
}

void remove_employee_from_department(const char* employee_id) {
    int i;
    for (i = 0; i < employee_count; i++) {
        if (strcmp(employees[i].employee_id, employee_id) == 0) {
            break;
        }
    }
    if (i < employee_count) {
        for (int j = i; j < employee_count - 1; j++) {
            employees[j] = employees[j + 1];
        }
        employee_count--;
        printf("Employee %s removed from department.\n", employee_id);
    } else {
        printf("Employee not found.\n");
    }
}

void print_all_companies(FILE *fp) {
    for (int i = 0; i < company_count; i++) {
        fprintf(fp, "Company ID: %d, Name: %s\n", companies[i].company_id, companies[i].company_name);
    }
}

void print_all_departments(FILE *fp) {
    for (int i = 0; i < department_count; i++) {
        fprintf(fp, "Department ID: %d, Company ID: %d, Name: %s\n", 
                departments[i].department_id, 
                departments[i].company_id, 
                departments[i].department_name);
    }
}

void print_all_employees(FILE *fp) {
    for (int i = 0; i < employee_count; i++) {
        fprintf(fp, "Employee ID: %s, Name: %s, Department ID: %d, Start Date: %s, Position: %s\n",
                employees[i].employee_id, 
                employees[i].name, 
                employees[i].department_id, 
                employees[i].start_date, 
                employees[i].position);
    }
}




void print_new_employees(FILE *fp) {
    fprintf(fp, "List of Employees:\n");
    for (int i = 0; i < employee_count; i++) {
        fprintf(fp, "ID: %s, Name: %s, Department ID: %d, Start Date: %s\n",
                employees[i].employee_id, 
                employees[i].name, 
                employees[i].department_id, 
                employees[i].start_date);
    }
}

void print_department_employee_percentage() {
    printf("Percentage of employees in each department:\n");
    for (int i = 0; i < department_count; i++) {
        int dept_employee_count = 0;
        for (int j = 0; j < employee_count; j++) {
            if (employees[j].department_id == departments[i].department_id) {
                dept_employee_count++;
            }
        }
        double percentage = (double)dept_employee_count / employee_count * 100;
        printf("Department %d (%s): %.2f%%\n", departments[i].department_id, departments[i].department_name, percentage);
    }
}

void list_employees_after_date(const char* date) {
    printf("Employees who started after %s:\n", date);
    for (int i = 0; i < employee_count; i++) {
        if (strcmp(employees[i].start_date, date) > 0) {
            printf("%s, %s\n", employees[i].employee_id, employees[i].name);
        }
    }
}

void list_employees_by_title_in_all_departments(const char* title) {
    printf("Employees with the title '%s' in all departments:\n", title);
    for (int i = 0; i < employee_count; i++) {
        if (strcmp(employees[i].position, title) == 0) {
            printf("ID: %s, Name: %s, Department ID: %d\n", employees[i].employee_id, employees[i].name, employees[i].department_id);
        }
    }
}



int main(void) {
    read_companies("companies.csv");
    read_departments("departments.csv");
    read_employees("employees.csv");

    int choice;
    char userChoice;
    char id[MAX_NAME_LEN], position[MAX_POSITION_LEN];
    int department_id;
    Employee new_employee;
    FILE *fp = NULL;

    do {
        printf("\nOperations:\n");
        printf("1. Search employee by ID\n");
        printf("2. List employees by position\n");
        printf("3. List employees in department\n");
        printf("4. Print total number of employees\n");
        printf("5. Print total employees in department\n");
        printf("6. Print total engineers in department\n");
        printf("7. Remove department from company\n");
        printf("8. Add new employee\n");
        printf("9. Remove employee from department\n");
        printf("10. Print all departments\n");
        printf("11. Print all employees\n");
        printf("12. Print the file as you want\n");
        printf("13. Print percentage of employees in each department\n");
        printf("14. List employees who started after a certain date\n");
        printf("15. List employees by title in all departments\n");
        printf("16. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        

        switch (choice) {
            case 1: // Search employee by ID
                printf("Enter employee ID: ");
                scanf("%s", id);
                search_employee_by_id(id);
                break;
            case 2: // List employees by position
                printf("Enter position (BrandManager, Engineer etc.): ");
                scanf("%s", position);
                list_employees_by_position(position);
                break;
            case 3: // List employees in department
                printf("Enter department ID: ");
                scanf("%d", &department_id);
                list_employees_in_department(department_id);
                break;
            case 4: // Print total number of employees
                print_total_employees();
                break;
            case 5: // Print total employees in department
                printf("Enter department ID: ");
                scanf("%d", &department_id);
                print_total_employees_in_department(department_id);
                break;
            case 6: // Print total engineers in department
                printf("Enter department ID: ");
                scanf("%d", &department_id);
                print_total_engineers_in_department(department_id);
                break;
            case 7: // Remove department from company
                printf("Enter company ID: ");
                int company_id;
                scanf("%d", &company_id);
                printf("Enter department ID: ");
                scanf("%d", &department_id);
                remove_department_from_company(company_id, department_id);
                break;
            case 8: // Add new employee
                printf("Enter employee ID: ");
                scanf("%s", new_employee.employee_id);
                printf("Enter employee name: ");
                scanf(" %[^\n]", new_employee.name);
                printf("Enter department ID: ");
                scanf("%d", &new_employee.department_id);
                printf("Enter start date (YYYY-MM-DD): ");
                scanf("%s", new_employee.start_date);
                printf("Enter position: ");
                scanf("%s", new_employee.position);
                add_employee_to_department(new_employee);
             break;
         case 9: // Remove employee from department
                printf("Enter employee ID: ");
                scanf("%s", id);
                remove_employee_from_department(id);
                break;
            case 10: // Print all departments
                print_all_departments(stdout); // stdout kullanıldı
                break;
            case 11: // Print all employees
                print_all_employees(stdout); // stdout kullanıldı
                break;
            case 12: {
                printf("Do you want to print the information to a file? (y/n): ");
                scanf(" %c", &userChoice);

                if (userChoice == 'y' || userChoice == 'Y') {
                    char filename[100];
                    printf("Enter the filename: ");
                    scanf("%s", filename);
                   

                    fp = fopen(filename, "w");
                    if (!fp) {
                        perror("Error opening file");
                        break;
                    }
                } else {
                    fp = stdout;
                }

                print_all_companies(fp);
                print_all_departments(fp);
                print_all_employees(fp);

                if (fp != stdout) {
                    fclose(fp); // Close the file if it's not stdout
                     printf("You can access your renewed content from the project file.");
                }
                break;
            }
            case 13:
                print_department_employee_percentage();
                break;
            case 14:
                printf("Enter start date (YYYY-MM-DD): ");
                char date[MAX_DATE_LEN];
                scanf("%s", date);
                list_employees_after_date(date);
                break;
            case 15:
                printf("Enter job title (BrandManager, Engineer etc.): ");
                char title[MAX_POSITION_LEN];
                scanf("%s", title);
                list_employees_by_title_in_all_departments(title);
                break;


            case 16:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 16);

    return 0;
}
    
