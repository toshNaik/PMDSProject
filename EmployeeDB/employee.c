#include <stdio.h>
#include <string.h>
#include <C:\Users\Naik\Desktop\c_assignment\EmployeeDB\sqlite3.h>

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

int createRecord(sqlite3 * db, char * msg)
{
    int exit;
    char * sql_insert ="INSERT INTO PERSON VALUES(3, 'ASHUTOSH', 'NAIK', 18, 'MUMBAI', 10000.0);";

	exit = sqlite3_exec(db, sql_insert, NULL, 0, &msg);
	if (exit != SQLITE_OK) {
		fprintf(stderr, "Error Insert");
		sqlite3_free(msg);
	}
	else
        fprintf(stderr, "Records created Successfully!");
}
