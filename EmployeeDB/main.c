#include <stdio.h>
#include <C:\Users\Naik\Desktop\c_assignment\EmployeeDB\sqlite3.h>

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
	int exit = sqlite3_open("employee.db", &DB);

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

	char * sql_insert = "INSERT INTO PERSON VALUES(1, 'STEVE', 'GATES', 30, 'PALO ALTO', 1000.0);"
			"INSERT INTO PERSON VALUES(2, 'BILL', 'ALLEN', 20, 'SEATTLE', 300.22);"
			"INSERT INTO PERSON VALUES(3, 'PAUL', 'JOBS', 24, 'SEATTLE', 9900.0);"
			"INSERT INTO PERSON VALUES(4, 'ASHUTOSH', 'NAIK', 18, 'MUMBAI', 10000.0);";

	exit = sqlite3_exec(DB, sql_insert, NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		fprintf(stderr, "Error Insert");
		sqlite3_free(messaggeError);
	}
	else
        fprintf(stderr, "Records created Successfully!");

	fprintf (stdout, "TABLE AFTER INSERT");

	sqlite3_exec(DB, query, callback, NULL, NULL);

	sql = "DELETE FROM PERSON WHERE ID = 2;";
	exit = sqlite3_exec(DB, sql, NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
        fprintf(stderr, "Error DELETE");
		sqlite3_free(messaggeError);
	}
	else
        fprintf(stdout, "Record deleted Successfully!");

	fprintf(stdout, "TABLE AFTER DELETE OF ELEMENT");
	sqlite3_exec(DB, query, callback, NULL, NULL);

	sqlite3_close(DB);
	return (0);
}
