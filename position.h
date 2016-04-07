#ifndef POSITION_H
#define POSITION_H

#include <stdio.h>
#include "circulardoublylinkedlist.h"
#include <iostream>
#include <vector>

using namespace std;

class Position
{
private:
    vector<int> position;
    int k;
    int max;

    int longestPathToTerminal(vector<Position> options, int length);

public:
    Position(int len, int k, int max);
    Position(vector<int> pos, int k, int max);

    bool IsMax() const;

    int longestPathToTerminal();

    int sum();

    int getLength() const;

    bool IsLegalMove(int index) const;
    bool IsTerminal() const;
    void MakeMove(int index);
    bool Increment();

    vector<Position> Options() const;

    string toString(void) const;
    string reverseString();

    vector<int>  getVector() const;
    int get_k() const;
    int get_max() const;

    void  ReversePosistion();

    int longestPath() const;

    friend std::ostream& operator<<(std::ostream&, const Position&);
    bool operator==(const Position & other) const;
    bool operator!=(const Position & other) const;
};

#endif // POSITION_H
