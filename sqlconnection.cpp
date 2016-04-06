#include "sqlconnection.h"
#include <sqlite3.h>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

SQLconnection::SQLconnection(char* databaseName)
{
    rc = sqlite3_open(databaseName, &db);
}

SQLconnection::SQLconnection(string databaseName)
{
    rc = sqlite3_open(databaseName.c_str(), &db);
}

void SQLconnection::CloseDB(){ sqlite3_close(db); }

void SQLconnection::DropPositionTable(){
    char* sql = "DROP TABLE POSITIONS;";
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    cout << "drop" << endl;
}

void SQLconnection::CreatePositionTable(){
    char* sql =
          "CREATE TABLE POSITIONS("  \
          "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
          "POSITION CHAR(50) UNIQUE," \
          "LENGTH INTEGER," \
          "SUM INTEGER," \
          "GRUNDY INTEGER);";
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    cout << "create" << endl;
}


void SQLconnection::InsertIntoPostition(Position & position){
    if(position.IsTerminal()){
        InsertIntoPostition(position, 0, 0);
        return;
    }

    string pos = position.toString();
    string posReverse = position.toString();
    reverse(posReverse.begin(), pos.end());

    string sql =   "INSERT OR REPLACE INTO POSITIONS (ID, POSITION, GRUNDY) VALUES ( (select ID from POSITIONS where (POSITION = '"+ pos +"' and POSITION = '" + posReverse +"')), '"  + pos + "', NULL, NULL );";

    rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);
    cout << "Inserted position " << position << endl;

}

void SQLconnection::InsertIntoPostition(Position position, int grundy, int length){
    string pos = position.toString();

    ostringstream ssg;
    ssg << grundy;
    ostringstream ssl;
    ssl << length;
    ostringstream sssum;
    sssum << position.sum();

    string sql =   "INSERT OR REPLACE INTO POSITIONS (ID, POSITION, SUM, LENGTH, GRUNDY) VALUES ( (select ID from POSITIONS where POSITION = '"+ pos +"'), '"  + pos + "', " + sssum.str() + ", " + ssl.str() + ", " + ssg.str() + " );";

    /*
    string sql = "INSERT OR REPLACE INTO POSITIONS (ID, POSITION, GRUNDY) "\
                 "VALUES ("\
                 "(select ID from POSITIONS where POSITION = " + pos + " or POSITION = " + posReverse +"),"\
                 + pos + ", "\
                 + ss1.str() + ", ";
                 + ss2.str() + ");";
   */

    rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);
    cout << "Inserted position " << position << " with grundy value " << grundy  << endl;

}

/*
void SQLconnection::SelectGrundyPositionTable(int value){
    // select * from positions where grundy = 0;
}
*/


vector<std::string> SQLconnection::SelectAllPositions(){
    char* sql = "select position from positions;";
    sqlite3_stmt * stmt;
    vector<string> pos;

    rc = sqlite3_prepare(db, sql, -1, &stmt, NULL);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        stringstream ss;
        ss << sqlite3_column_text(stmt, 0);
        string p;
        ss >> p;
        pos.push_back(p);
    }
    sqlite3_finalize(stmt);
    return pos;
}

vector<int> SQLconnection::SelectGrundyOptions(vector<Position> opts){
    vector<int> values;
    if (opts.size() == 0){
        return values;
    }

    string sql = "select distinct grundy from positions where ";
    sql += "POSITION = '" + opts[0].toString() + "'";
    for(int i = 0; i < opts.size(); i ++){
        sql += "or POSITION = '" + opts[i].toString() + "' ";
    }
    sql += " and grundy NOT NULL ORDER BY grundy;";

    sqlite3_stmt * stmt;

    rc = sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int val = sqlite3_column_int(stmt, 0);
        values.push_back(val);
    }
    sqlite3_finalize(stmt);
    return values;
}

vector<int> SQLconnection::SelectLengthOptions(vector<Position> opts){
    vector<int> values;
    if (opts.size() == 0){
        return values;
    }

    string sql = "select distinct length from positions where ";
    sql += "POSITION = '" + opts[0].toString() + "'";
    for(int i = 0; i < opts.size(); i ++){
        sql += "or POSITION = '" + opts[i].toString() + "' ";
    }
    sql += " and length NOT NULL ORDER BY length;";

    sqlite3_stmt * stmt;

    rc = sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int val = sqlite3_column_int(stmt, 0);
        values.push_back(val);
    }
    sqlite3_finalize(stmt);
    return values;
}
