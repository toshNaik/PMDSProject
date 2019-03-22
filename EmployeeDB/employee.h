#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED
extern int id;
int deleteRecord(sqlite3 * db, char * msg);
int createRecord(sqlite3 * db, char * msg);
int displayRecord(sqlite3 * db, char * msg);
void validSalary(float * salary);
//void valid_pf(float * salary, float* pf)
float tax(float * salary);
//static int callback(void* data, int argc, char** argv, char** azColName);

#endif // EMPLOYEE_H_INCLUDED
