#include <iostream>
#include "fileFunctions.cpp"
#include "company.cpp"
using namespace std;

using namespace std;

int main()
{
    vector<string> devinfo, testinfo;
    string admininfo, hrinfo;

    fileHandling(devinfo, testinfo, admininfo, hrinfo);

    Company c(devinfo, testinfo, admininfo, hrinfo);
    vector<int> flagsVector = c.getFlags();

    writeResult(flagsVector);

    return 0;
}