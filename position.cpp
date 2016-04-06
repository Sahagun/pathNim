#include <stdio.h>
#include "position.h"
#include <iostream>
#include <sstream>
#include "circulardoublylinkedlist.h"
#include <vector>
#include <algorithm>
using namespace std;


Position::Position(int len, int k, int max) {
    this->max = max;
    this->k = k;
    for (int i = 0; i < len; i++) {
        position.push_back(0);
    }
}

Position::Position(vector<int> pos, int k, int max) {
    this->k = k;
    this->max = max;
    position = pos;
}

bool Position::IsMax() const{
    for (int i = 0; i < position.size(); i++) {
        if (position[i] < max) return false;
    }
    return true;
}

int Position::sum(){
    int s = 0;
    for (int i = 0; i < position.size(); i++) {
        s += position[i];
    }
    return s;
}

int Position::getLength() const{
    return position.size();
}

int Position::get_k() const{
    return this->k;
}

int Position::get_max() const{
    return this->max;
}


bool Position::IsLegalMove(int index) const{
    if ( k + index > position.size() ){
//        cout << k  << " + " << index << " > " << position.size()  << endl;
        return false;
    }
    for (int i = index; i < k + index; i++) {
        // If a piles is less than 0 this is not a legal move so return false.
        if (position[i] - 1 < 0){
//            cout << position[i] << " - " << 1 << " < " << 0 << endl;
            return false;
        }
    }
//    cout << "Legal Move." << endl;
    return true;
}


vector<Position> Position::Options() const{
    vector<Position> options;
    for(int i = 0; i < position.size(); i++){
        if(IsLegalMove(i)){
            Position opt (getVector(), k , max);
            opt.MakeMove(i);
            options.push_back(opt);
        }
    }
    return options;
}

int Position::longestPath() const{
    int len = 0;
    int max = 0;
    for (int i = 0; i < position.size(); i++) {
        if (position[i] > 0){
            len++;
        }
        else{
            len = 0;
        }
        if(len > max) max = len;
    }
    return max;
}

bool Position::IsTerminal() const {
    return (longestPath() < k);
}

void Position::MakeMove(int index) {
    if(IsLegalMove(index)){
        for (int i = 0; i < k; i++) {
            position[index + i]--;
        }
    }
}


int Position::longestPathToTerminal(){
    return longestPathToTerminal(Options(), 0);
}

int Position::longestPathToTerminal(vector<Position> options, int length){
    int max = length;
    for(int i = 0; i < options.size(); i++){
        int len = longestPathToTerminal(options[i].Options(), length + 1);
        max = (max > len) ? max : len;
    }
    return max;
}


bool Position::Increment() {
    if(IsMax())return false;
    int index = 0;
    while(position[index] == max){
        position[index] = 0;
        index++;
    }
    position[index]++;
    return true;
}

string Position::toString() const {
    ostringstream oss("");
    for (int i = 0; i < position.size(); i++) {
        oss << position[i];
        if (i < position.size() - 1){
            oss << ",";
        }
    }
    return oss.str();
}

vector<int> Position::getVector()  const {
    return position;
}

void Position::ReversePosistion() {
    reverse(position.begin(),position.end());
}

ostream& operator<<(std::ostream& stream, const Position& p) {
    vector<int> pos;
    pos= p.getVector();
    stream << "<";
    for (int i = 0; i < pos.size(); i++) {
        stream << pos[i];
        if (i < pos.size() - 1){
            stream << ",";
        }
    }
    return stream << ">";
}

bool Position::operator==(const Position &other) const {
    if (other.getVector() == this->getVector()) return true;

    if (other.getLength() == this->getVector().size()){
        for(int i = 0, j = this->getVector().size() - 1; i <= j; i++, j--){
            if(other.getVector()[i] !=  this->getVector()[j]) return false;
        }
        return true;
    }
    return false;
}

bool Position::operator!=(const Position &other) const {
    return !(*this == other);
}
