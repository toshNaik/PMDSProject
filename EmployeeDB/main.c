#include <stdio.h>
#include <string.h>
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

int deleteRecord(sqlite3 * db, char * msg)
{
    int input;
    scanf("%d", &input);
    printf("%d", input);
    char * buffer;
    itoa(input, buffer, 10);
    printf("%s", buffer);
	char sql[] = "DELETE FROM PERSON WHERE ID = ";
	strcat(sql,buffer);
	strcat(sql,";");
	int exit;
	exit = sqlite3_exec(db, sql, NULL, 0, &msg);
	if (exit != SQLITE_OK) {
        fprintf(stderr, "Error DELETE");
		sqlite3_free(msg);
	}
	else
        fprintf(stdout, "Record deleted Successfully!");
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

	char * sql_insert ="INSERT INTO PERSON VALUES(4, 'ASHUTOSH', 'NAIK', 18, 'MUMBAI', 10000.0);";

	exit = sqlite3_exec(DB, sql_insert, NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		fprintf(stderr, "Error Insert");
		sqlite3_free(messaggeError);
	}
	else
        fprintf(stderr, "Records created Successfully!");

	fprintf (stdout, "TABLE AFTER INSERT");

	sqlite3_exec(DB, query, callback, NULL, NULL);
    int input;
    deleteRecord(DB, messaggeError);
//	sql = "DELETE FROM PERSON WHERE ID = 2;";
//	exit = sqlite3_exec(DB, sql, NULL, 0, &messaggeError);
//	if (exit != SQLITE_OK) {
//        fprintf(stderr, "Error DELETE");
//		sqlite3_free(messaggeError);
//	}
//	else
//        fprintf(stdout, "Record deleted Successfully!");
//
//	fprintf(stdout, "TABLE AFTER DELETE OF ELEMENT");
	sqlite3_exec(DB, query, callback, NULL, NULL);

	sqlite3_close(DB);
	return (0);
}







//int deleteRecord(sqlite3 * db, char * msg)
//{
//	char sql[] = "DELETE FROM PERSON WHERE ID = 3;";
//	int exit;
//	exit = sqlite3_exec(db, sql, NULL, 0, &msg);
//	if (exit != SQLITE_OK) {
//        fprintf(stderr, "Error DELETE");
//		sqlite3_free(msg);
//	}
//	else
//        fprintf(stdout, "Record deleted Successfully!");
//    return 0;
//}
