#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <fstream>

using namespace std;

#define BLUE 1
#define GREEN 2
#define AMBER 3
#define RED 4

class Hr
{
    string hrinfo;
    int recruitsExpected, recruitsCompleted, resignationsExpected, resignationsCompleted;
    int flag, flagRecruits, flagResignations;

public:
    Hr()
    {
        flag = 0;
        flagRecruits = 0;
        flagResignations = 0;
    }

    Hr(string p)
    {
        hrinfo = p;
    }

    void calc()
    {

        string str1, str2;
        split(hrinfo, '_', str1, str2);
        splitdate(str1, '-', recruitsExpected, recruitsCompleted);
        splitdate(str2, '-', resignationsExpected, resignationsCompleted);

        calcResignFlag();
        calcRecFlag();
        flag = (flagRecruits + flagResignations) / 2;
    }

    int calcResignFlag()
    {
        fstream fin_config;
        const char *env = "FB";
        const char *vv = getenv(env);
        string configpath = "\\config.txt";
        configpath.insert(0, vv);
        int num = 3;
        fin_config.open(configpath, ios::in);
        if (!fin_config.is_open())
        {
            cout << "Failed to open the file." << endl;
            return 0;
        }
        int cur_line = 0;
        string line;
        while (!fin_config.eof())
        {
            cur_line++;
            getline(fin_config, line);
            if (cur_line == num)
            {
                break;
            }
        }
        fin_config.close();
        int m = stoi(line);
        if (resignationsExpected > resignationsCompleted)
        {
            flagRecruits = BLUE;
        }
        else if (resignationsExpected == resignationsCompleted)
        {
            flagRecruits = GREEN;
        }
        else if (resignationsExpected > resignationsCompleted - m)
        {
            flagRecruits = AMBER;
        }
        else
        {
            flagRecruits = RED;
        }
        return flagRecruits;
    }

    int calcRecFlag()
    {
        fstream fin_config;
        const char *env = "FB";
        const char *vv = getenv(env);
        string configpath = "\\config.txt";
        configpath.insert(0, vv);
        int num = 3;
        fin_config.open(configpath, ios::in);
        if (!fin_config.is_open())
        {
            cout << "Failed to open the file." << endl;
            return 0;
        }
        int cur_line = 0;
        string line;
        while (!fin_config.eof())
        {
            cur_line++;
            getline(fin_config, line);
            if (cur_line == num)
            {
                break;
            }
        }
        fin_config.close();
        int m = stoi(line);
        if (recruitsExpected < recruitsCompleted)
        {
            flagResignations = BLUE;
        }
        else if (recruitsExpected == recruitsCompleted)
        {
            flagResignations = GREEN;
        }
        else if (recruitsExpected < recruitsCompleted + m)
        {
            flagResignations = AMBER;
        }
        else
        {
            flagResignations = RED;
        }
        return flagResignations;
    }

    int getFlag()
    {
        calc();
        return flag;
    }
};
