#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED
extern int id;                                  //The id of employees
int deleteRecord(sqlite3 * db, char * msg);     //To delete records
int createRecord(sqlite3 * db, char * msg);     //To create records
int displayRecord(sqlite3 * db, char * msg);    //To display list of all employees
int searchName(sqlite3 * db, char * msg);       //Search database by name
int searchId(sqlite3 * db, char * msg);         //Search database by id
void validSalary(float * salary);               //Check if salary falls within valid range
void valid_pf(float * salary, float* pf);       //Check if pf falls within valid range
void valid_allowance(float * allowance);        //Check if allowance falls within valid range
int markAttendance(sqlite3 * db,char * msg);    //Mark daily attendance of employees
float tax(float * salary);                      //Calculate tax levied on salary


#endif // EMPLOYEE_H_INCLUDED
//static int callback(void* data, int argc, char** argv, char** azColName);
