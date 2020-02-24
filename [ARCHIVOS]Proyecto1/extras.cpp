#include "extras.h"

//*************************************************************************
//*************************************************************************
//*****************************   TRIM    *********************************
//*************************************************************************
string extras::trim(string s){
    if(s.size() == 0) return s;
    return trimL(trimR(s));
}
string extras::trimL(string s){
    if(s.size() == 0) return s;
    int L = s.find_first_not_of(" ");
    return s.substr(L, s.size());
}
string extras::trimR(string s){
    if(s.size() == 0) return s;
    int R = s.find_last_not_of(" ");
    return s.substr(0, R + 1);
}

string extras::c_toString(char c[]){
    string s = c;
    return s;
}
string extras::c_toStringC(char c){
    string s = "";
    s += c;
    return s;
}

//*************************************************************************
//*************************************************************************
//***************************  TO LOWER STRING   **************************
//*************************************************************************
string extras::toLowerS(string s){
    string toLower = "";
    for (char& c: s)
        toLower += toLowerC(c);
    return toLower;
}
char extras::toLowerC(char c){
    if(c <= 'Z' && c >= 'A')
        return c - ('Z' - 'z');
    return c;
}

//*************************************************************************
//*************************************************************************
//******************************  RANDOM   ********************************
//*************************************************************************
int extras::getRandom(){
    srand(time(0));
    return rand() % 99999 + 1;
}
