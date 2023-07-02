#include <iostream>
#include <vector>
#include <array>
#include <string>

using namespace std;

class Admin
{
    string admininfo;
    int profitexp, profitcom;
    int flag;

public:
    Admin()
    {
        flag = 0;
    }
    Admin(string p)
    {
        admininfo = p;
    }
    void calc()
    {
        splitdate(admininfo, '_', profitexp, profitcom);
        if (profitexp == profitcom)
        {
            flag = GREEN;
        }
        else if (profitexp < profitcom)
        {
            flag = BLUE;
        }
        else if ((profitexp - profitexp / 4) < profitcom && profitcom < profitexp)
        {
            flag = AMBER;
        }
        else
        {
            flag = RED;
        }
    }
    int getFlag()
    {
        calc();
        return flag;
    }
};
