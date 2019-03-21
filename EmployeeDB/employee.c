#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <C:\Users\Naik\Desktop\c_assignment\EmployeeDB\sqlite3.h>
int id;

static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

int displayRecord(sqlite3 * db, char * msg)
{
	char* query = "SELECT * FROM PERSON;";
	fprintf (stdout, "TABLE\n");
	sqlite3_exec(db, query, callback, NULL, NULL);
	return 0;
}
int deleteRecord(sqlite3 * db, char * msg)
{
    int input;
    char * buffer;
    char * query;
    buffer = (char*)malloc(4);
    printf("Enter id of record to be deleted: ");
    scanf("%d", &input);
    sprintf(buffer, "%d", input);
	char * sql = "DELETE FROM PERSON WHERE ID = ";
	query = (char*)malloc(strlen(sql)+strlen(buffer)+1);
	sprintf(query, "%s%s", sql, buffer);
	int exit;
	exit = sqlite3_exec(db, query, NULL, 0, &msg);
	if (exit != SQLITE_OK) {
        fprintf(stderr, "Error DELETE\n");
		sqlite3_free(msg);
	}
	else
        fprintf(stdout, "Record deleted Successfully!\n");
    return 0;
}

int createRecord(sqlite3 * db, char * msg)
{
    id++;
    char* buffer_id;
    buffer_id = (char*)malloc(4);
    sprintf(buffer_id, "%d", id);
    int age;
    char* buffer_age;
    buffer_age = (char*)malloc(4);
    float salary;
    char* buffer_salary;
    buffer_salary = (char*)malloc(10);
    char* name;
    name = (char*)malloc(15);
    char* surname;
	surname = (char*)malloc(15);
	char* address;
	address = (char*)malloc(15);
	char* sql_insert = "INSERT INTO PERSON VALUES(";
	fflush(stdin);
	printf("Enter name: ");
	scanf("%[^\n]s", name);
	fflush(stdin);
	printf("Enter surname: ");
	scanf("%[^\n]s", surname);
	fflush(stdin);
	printf("Enter address: ");
	scanf("%[^\n]s", address);
	fflush(stdin);
	printf("Enter age: ");
	scanf("%d", &age);
    printf("Enter salary: ");
    scanf("%f", &salary);
    sprintf(buffer_age, "%d", age);
    sprintf(buffer_salary, "%0.1f", salary);
    char* sql_query;
    sql_query = (char*)malloc(strlen(buffer_id)+strlen(name)+strlen(surname)+strlen(address)+strlen(buffer_age)+strlen(buffer_salary)+strlen(sql_insert)+20);
    sprintf(sql_query,"%s%s,'%s','%s',%s,'%s',%s);",sql_insert,buffer_id,name,surname,buffer_age,address,buffer_salary);
	int exit;
	exit = sqlite3_exec(db, sql_query, NULL, 0, &msg);
	if (exit != SQLITE_OK) {
        fprintf(stderr, "Error create\n");
		sqlite3_free(msg);
	}
	else
        fprintf(stdout, "Record created Successfully!\n");
    return 0;
}

