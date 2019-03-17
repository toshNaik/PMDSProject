#include <stdio.h>
#include <string.h>
#include <C:\Users\Naik\Desktop\c_assignment\EmployeeDB\sqlite3.h>
#include "employee.h"

static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}


int main(int argc, char** argv)
{
	sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("employee2.db", &DB);

	char * sql = "CREATE TABLE PERSON("
                      "ID INT PRIMARY KEY     NOT NULL, "
                      "NAME           TEXT    NOT NULL, "
                      "SURNAME          TEXT     NOT NULL, "
                      "AGE            INT     NOT NULL, "
                      "ADDRESS        CHAR(50), "
                      "SALARY         REAL );";

    exit = sqlite3_exec(DB, sql, NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        fprintf(stderr, "Error Creating TABLE!");
        sqlite3_free(messaggeError);
    }
    else fprintf(stdout, "Table Created Successfully!");

	char* query = "SELECT * FROM PERSON;";

	fprintf(stdout, "TABLE BEFORE INSERT");

	sqlite3_exec(DB, query, callback, NULL, NULL);

	createRecord(DB, messaggeError);

	fprintf (stdout, "TABLE AFTER INSERT");

	sqlite3_exec(DB, query, callback, NULL, NULL);
    int input;
    deleteRecord(DB, messaggeError);
	sqlite3_exec(DB, query, callback, NULL, NULL);

	sqlite3_close(DB);
	return (0);
}
