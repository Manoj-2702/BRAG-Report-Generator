#include <iostream>
#include <vector>
#include <array>
#include <numeric>
#include <cmath>
#include "Functions.cpp"
#include "dev.cpp"
#include "testing.cpp"
#include "admin.cpp"
#include "hr.cpp"

using namespace std;

class Company
{
    Dev d;
    Test t;
    Admin a;
    Hr h;
    int flag;
    vector<int> flagsVector;

public:
    Company(vector<string> devinfo, vector<string> testinfo, string admininfo, string hrinfo) : d(devinfo), t(testinfo), a(admininfo), h(hrinfo)
    {
        flagsVector.push_back(0); // temp
        flagsVector.push_back(d.getFlag());
        flagsVector.push_back(t.getFlag());
        flagsVector.push_back(a.getFlag());
        flagsVector.push_back(h.getFlag());
        flag = round((flagsVector[1] + flagsVector[2] + flagsVector[3] + flagsVector[4]) / 4);
        flagsVector[0] = flag;
    }

    Company()
    {
        flag = 0;
    }

    vector<int> getFlags()
    {
        return flagsVector;
    }
};