#ifndef SQLCONNECTION_H
#define SQLCONNECTION_H

#include "sqlconnection.h"
#include <sqlite3.h>
#include "position.h"

class SQLconnection
{
private:
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char* data = "Callback function called";
public:
    SQLconnection(char* databaseName);
    SQLconnection(string databaseName);
    void CloseDB();
    void DropPositionTable();
    void CreateMovesTable();
    void CreatePositionTable();
    void InsertIntoPostition(Position & position);
    void InsertIntoPostition(Position position, int grundy, int length);
    void SelectGrundyPositionTable(int value);
    void SelectLegalMoves(Position position);

    vector<std::string> SelectAllPositions();
    vector<int> SelectGrundyOptions(vector<Position> opts);
    vector<int> SelectLengthOptions(vector<Position> opts);



};


#endif // SQLCONNECTION_H
