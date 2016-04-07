#include <iostream>
#include <vector>
#include "position.h"
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include <sqlite3.h>
#include "sqlconnection.h"
using namespace std;

int calcMEX(vector<int> vec){
    int counter = 0;
    while(counter < vec.size()){
        if ( vec[counter] != counter )
            return counter;
        counter++;
    }
    return counter;
}

int calcLength(SQLconnection data, Position p){
    if(p.IsTerminal()){
        return 0;
    }
    vector<int> grundys = data.SelectLengthOptions(p.Options());

    int max = 0;
    for(int i = 0; i < grundys.size(); i++){
        max = (max > grundys[i]) ? max : grundys[i];
    }
    cout << "length = " << max << "   ";
    return max + 1;
}

void calcGrundy(SQLconnection data, Position p){
    if(p.IsTerminal()){
        cout << "terminal ";
        data.InsertIntoPostition(p,0,0);
        return;
    }

    vector<int> grundys = data.SelectGrundyOptions(p.Options());
    int grundy = calcMEX(grundys);

    int leng = calcLength(data, p);

    data.InsertIntoPostition(p,grundy, leng);
}

int main1(){
    vector<int> p;
    p.push_back(0);
    p.push_back(0);
    p.push_back(1);
    Position pos(p,2,100);
    cout << pos.sum();
}

int main2(){
    vector<int> p;
    p.push_back(0);
    p.push_back(0);
    p.push_back(1);
    p.push_back(1);
    Position pos(p,2,100);

//    cout << pos << endl;
//    cout << posReverse << endl;


    stringstream nameStream;
    nameStream << "PN(" << 4 << ", " << 2 << ")";
    string name = nameStream.str();

    SQLconnection data (name);

    cout << data.isInTable(pos) << endl;

}

int main(){
    int max;
    int n;
    int k;

    cout << "Enter the number of stacks: " ;
    cin >> n;

    cout << endl << "Enter the number of stacks we can take from: ";
    cin >> k;

    cout << endl << "Enter the max number : ";
    cin >> max;

    stringstream nameStream;
    nameStream << "PN(" << n << ", " << k << ")";
    string name = nameStream.str();

    SQLconnection data (name);
    data.DropPositionTable();
    data.CreatePositionTable();

    Position p (n, k, max);

    while(!p.IsMax()){
        if(!data.isInTable(p)){
            calcGrundy(data, p);
        }
        p.Increment();
    }
    calcGrundy(data, p);

    cout << endl << "Done" << endl;
}
