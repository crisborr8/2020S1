#ifndef REP_H
#define REP_H

#include "extras.h"

class rep
{
public:
    bool comandoRep(vector<string> c, vector<vector<string>> particiones);
    string nameDisk(string path);
    string nameMbr(string path);
private:
    extras ext;
};

#endif // REP_H
