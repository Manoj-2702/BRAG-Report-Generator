#include <iostream>
#include <vector>
#include <array>
#include <string>

using namespace std;

class Dev : public Parent
{
protected:
    vector<Process> prolist;

public:
    Dev() {}
    Dev(vector<string> p) : Parent(p)
    {
        for (auto i : p)
        {
            string temp1, temp2;
            split(i, '_', temp1, temp2);
            Project t(temp1, temp2);
            t.calc();
            projectList.push_back(t);
        }
    }
};