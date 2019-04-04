#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "employee.h"
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

    int leave = 0;
    char* buffer_leave;
    buffer_leave = (char*)malloc(3);

    float pf;
    char* buffer_pf;
    buffer_pf = (char*)malloc(8);

    float med_all;
    char* buffer_med_all;
    buffer_med_all = (char*)malloc(5);

    float travel_all;
    char* buffer_travel_all;
    buffer_travel_all = (char*)malloc(5);

    float salary_tax;
    char* buffer_tax;
    buffer_tax = (char*)malloc(8);

    float gross;
    char* buffer_gross;
    buffer_gross = (char*)malloc(10);

    float net;
    char* buffer_net;
    buffer_net = (char*)malloc(10);

    char* name;
    name = (char*)malloc(30);

	char* address;
	address = (char*)malloc(15);

	char* sql_insert = "INSERT INTO PERSON VALUES(";
	fflush(stdin);
	printf("Enter name: ");
	scanf("%[^\n]s", name);
	fflush(stdin);

	printf("Enter address: ");
	scanf("%[^\n]s", address);
	fflush(stdin);
	printf("Enter age: ");
	scanf("%d", &age);

    printf("Enter salary: ");
    scanf("%f", &salary);
    validSalary(&salary);
    salary_tax = tax(&salary);
    printf("Enter Provident Fund Amount: ");
    scanf("%f", &pf);
    valid_pf(&salary, &pf);
    printf("Enter Medical Allowance: ");
    scanf("%f", &med_all);
    valid_allowance(&med_all);
    printf("Enter Travel Allowance: ");
    scanf("%f", &travel_all);
    valid_allowance(&travel_all);
    gross = salary + med_all + travel_all + pf;
    net = gross - salary_tax - (travel_all/12);

    sprintf(buffer_age, "%d", age);
    sprintf(buffer_salary, "%0.1f", salary);
    sprintf(buffer_tax, "%0.1f", salary_tax);
    sprintf(buffer_pf, "%0.1f", pf);
    sprintf(buffer_med_all, "%0.1f", med_all);
    sprintf(buffer_travel_all, "%0.1f", travel_all);
    sprintf(buffer_leave, "%d", leave);
    sprintf(buffer_gross, "%0.1f", gross);
    sprintf(buffer_net, "%0.1f", net);

    char* sql_query;
    sql_query = (char*)malloc(strlen(buffer_leave)+strlen(buffer_tax)+strlen(buffer_gross)+strlen(buffer_travel_all)+strlen(buffer_med_all)+strlen(buffer_pf)+strlen(buffer_tax)+strlen(buffer_id)+strlen(name)+strlen(address)+strlen(buffer_age)+strlen(buffer_salary)+strlen(sql_insert)+20);
    sprintf(sql_query,"%s%s,'%s',%s,'%s',%s,%s,%s,%s,%s,%s,%s,%s);",sql_insert,buffer_id,name,buffer_age,address,buffer_salary,buffer_pf,buffer_med_all,buffer_travel_all,buffer_leave,buffer_tax,buffer_gross,buffer_net);
	int exit;
	exit = sqlite3_exec(db, sql_query, NULL, 0, &msg);
	if (exit != SQLITE_OK) {
        fprintf(stderr, "Error create\n");
		sqlite3_free(msg);
	}
	else
        fprintf(stdout, "Record created Successfully!\n");

    free(sql_query);
    free(buffer_age);
    free(buffer_gross);
    free(buffer_id);
    free(buffer_leave);
    free(buffer_med_all);
    free(buffer_net);
    free(buffer_pf);
    free(buffer_salary);
    free(buffer_tax);
    free(buffer_travel_all);
    return 0;
}

void validSalary(float * salary)
{
    if(*salary<=10000 || *salary>1200000)
    {
        printf("INVALID SALARY ENTER VALID SALARY: ");
        scanf("%f", salary);
        validSalary(salary);
    }
}

void valid_pf(float * salary, float * pf)
{
    if(*pf>=0.5*(*salary)||*pf<0.05*(*salary))
    {
        printf("INVALID PF ENTER VALID PF: ");
        scanf("%f", pf);
        valid_pf(salary,pf);
    }
}

void valid_allowance(float * allowance)
{
    if(*allowance>=6000||*allowance<1500)
    {
        printf("INVALID ALLOWANCE ENTER VALID ALLOWANCE: ");
        scanf("%f", allowance);
        valid_allowance(allowance);
    }
}

float tax(float * salary)
{
    if(*salary<=41666)
        return (0.05*(*salary));
    else if(*salary>=41667&&*salary<=83333)
        return(0.2*(*salary-41666)+1042);
    else
        return(0.3*(*salary-83334)+9375);
}

int searchName(sqlite3 * db, char * msg)
{
    char* sql = "SELECT * FROM PERSON WHERE NAME LIKE '%";
	char* query;
	char* name;
	name = (char*)malloc(30);
	printf("Enter name: ");
	fflush(stdin);               //Select * From PERSON where NAME like '%NAIK%';
	scanf("%[^\n]s", name);
	query = (char*)malloc(strlen(sql)+strlen(name)+6);
	sprintf(query, "%s%s%%';",sql, name);
	sqlite3_exec(db, query, callback, NULL, NULL);
	return 0;
}

int searchId(sqlite3 * db, char * msg)
{
    char* sql = "SELECT * FROM PERSON WHERE ID LIKE '";
	char* query;
	int id;
	char* buffer;
	buffer = (char*)malloc(4);
	printf("Enter id: ");
	fflush(stdin);
	scanf("%d", &id);
	sprintf(buffer, "%d", id);
	query = (char*)malloc(strlen(sql)+strlen(buffer)+4);
	sprintf(query, "%s%s';",sql, buffer);
	sqlite3_exec(db, query, callback, NULL, NULL);
	return 0;
}

int markAttendance(sqlite3 * db,char * msg)
{
    int i;
    printf("Enter id of absent employee: ");
    scanf("%d", &i);
    char * sql = "UPDATE PERSON SET LEAVE = LEAVE + 1 WHERE ID = ";
    char * buffer;
    buffer = (char*)malloc(4);
    sprintf(buffer,"%d",i);
    char * query;
    query = (char*)malloc(strlen(sql)+strlen(buffer));
    sprintf(query, "%s%s;", sql, buffer);
    int exit = sqlite3_exec(db, query, NULL, NULL, &msg);
    if( exit != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", msg);
        sqlite3_free(msg);
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }
    free(query);
    free(buffer);
    return 0;
}

int hoursOverworked(sqlite3 * db,char * msg)
{
    int hours;
    int i;
    printf("Enter id of employee who has overworked: ");
    scanf("%d", &i);
    char* buffer_id = (char*)malloc(4);
    sprintf(buffer_id, "%d", i);

    printf("Enter hours over-worked: ");
    scanf("%d", &hours);
    char* buffer_hours = (char*)malloc(4);
    sprintf(buffer_hours, "%d", hours);

    char * sql = "UPDATE PERSON SET NET = NET + 500*";
    char * append = " WHERE ID = ";
    char* query = (char*)malloc(strlen(sql)+strlen(append)+strlen(buffer_hours)+strlen(buffer_id)+4);
    sprintf(query, "%s%s%s%s;", sql,buffer_hours,append,buffer_id);
    int exit = sqlite3_exec(db, query, NULL, NULL, &msg);
    if( exit != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", msg);
        sqlite3_free(msg);
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }
    free(query);
    free(buffer_hours);
    free(buffer_id);
    return 0;
}

void updateBase(sqlite3* db, char * msg)
{
    int i;
    float salary;
    printf("Enter id of employee whose base is to be updated: ");
    scanf("%d", &i);
    char* buffer_id = (char*)malloc(4);
    sprintf(buffer_id, "%d", i);
    //printf("%s\n", buffer_id);


    printf("Enter new base salary: ");
    scanf("%f", &salary);
    validSalary(&salary);
    char* buffer_salary = (char*)malloc(10);
    sprintf(buffer_salary, "%f", salary);

    char * query = (char*)malloc(sizeof(buffer_id)+sizeof(buffer_salary)+50);
    sprintf(query, "UPDATE PERSON SET SALARY = %s WHERE ID = %s;", buffer_salary, buffer_id);
    int exit;
	exit = sqlite3_exec(db, query, NULL, 0, &msg);
    if( exit != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", msg);
        sqlite3_free(msg);
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }
    free(query);
    free(buffer_id);
    free(buffer_salary);
}
