#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <string>
using namespace std;

static bool isNum(string str, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (str[i] == '-')
            continue;
        if (isdigit(str[i]) == false)
            return false;
    }
    return true;
};

void splitdate(string str, char del, int &d, int &m)
{

    string temp = "";
    for (int i = 0; i < (int)str.size(); i++)
    {

        if (str[i] != del)
        {
            temp += str[i];
        }
        else
        {
            try
            {
                if (isNum(temp, temp.size()))
                    d = stoi(temp);
                else
                    throw temp;
            }
            catch (string x)
            {
                cout << "Unexpected data from an input file: " << x << endl;
                exit(0);
            }

            temp = "";
        }
    }

    try
    {
        if (isNum(temp, temp.size() - 1))
            m = stoi(temp);
        else
            throw temp;
    }
    catch (string x)
    {
        cout << "Unexpected data from an input file: " << x << endl;
        exit(0);
    }
};

void split(string str, char del, string &a, string &b)
{
    string temp = "";
    for (int i = 0; i < (int)str.size(); i++)
    {

        if (str[i] != del)
        {
            temp += str[i];
        }
        else
        {
            a = temp;
            try
            {
                if (isNum(temp, temp.size()))
                    a = temp;
                else
                    throw temp;
            }
            catch (string x)
            {
                cout << "Unexpected data from an input file: " << x << endl;
                exit(0);
            }
            temp = "";
        }
    }

    b = temp;
    try
    {
        if (isNum(temp, temp.size() - 1))
            b = temp;
        else
            throw temp;
    }
    catch (string x)
    {
        cout << "Unexpected data from an input file: " << x << endl;
        exit(0);
    }
};

class Project
{
    int flag;
    string expdate;
    string comdate;

public:
    Project(string e, string c)
    {
        expdate = e;
        comdate = c;
    }
    void calc()
    {
        int day1, day2, mon1, mon2;
        fstream fin_config;
        const char *env = "FB";
        const char *vv = getenv(env);
        string configpath = "\\config.txt";
        configpath.insert(0, vv);
        splitdate(expdate, '-', day1, mon1);
        splitdate(comdate, '-', day2, mon2);

        int num = 1;
        fin_config.open(configpath, ios::in);
        if (!fin_config.is_open())
        {
            cout << "Failed to open the file.1" << endl;
            return;
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
        if (mon2 > mon1)
        {
            flag = RED;
        }
        else if (mon2 == mon1)
        {
            if (day2 > day1 + m)
            {
                flag = AMBER;
            }
            else if (day2 <= day1 + m && day2 >= day1 + m)
            {
                flag = GREEN;
            }
            else
            {
                flag = BLUE;
            }
        }
    }
    void print()
    {
        cout << expdate << "    " << comdate << endl;
        cout << "this is flag " << flag << endl;
    }
    int getFlag()
    {
        return flag;
    }
};

class Process
{
    int flag;
    string expdate;
    string comdate;

public:
    Process(string e, string c)
    {
        expdate = e;
        comdate = c;
    }
    void calc()
    {
        int day1, day2, mon1, mon2;
        splitdate(expdate, '-', day1, mon1);
        splitdate(comdate, '-', day2, mon2);
        if (mon2 > mon1)
        {
            if (day2 < day1 + 4)
            {
                flag = 2;
            }
            else if (day2 <= day1 + 4 && day2 >= day1 + 4)
            {
                flag = 3;
            }
            else
            {
                flag = 4;
            }
        }
        else if (mon2 == mon1)
        {
            if (day2 > day1 + 4)
            {
                flag = 3;
            }
            else if (day2 <= day1 + 4 && day2 >= day1 + 4)
            {
                flag = 2;
            }
            else
            {
                flag = 1;
            }
        }
        else if (mon2 < mon1)
        {
            if (day2 > day1 + 5)
            {
                flag = 1;
            }
            else if (day2 <= day1 + 5 && day2 >= day1 + 5)
            {
                flag = 2;
            }
            else
            {
                flag = 3;
            }
        }
    }
    void print()
    {
        cout << expdate << "    " << comdate << endl;
        cout << "this is flag " << flag << endl;
    }
    int getFlag()
    {
        return flag;
    }
};

class Parent
{
    // vector of projects processes
protected:
    vector<Project> projectList;
    int flag;

public:
    Parent(vector<string> p)
    {
        for (auto i : p)
        {
            string temp1, temp2;
            split(i, '_', temp1, temp2);
            Project o(temp1, temp2);
            o.calc();
            projectList.push_back(o);
        }
    }

    Parent()
    {
        flag = 0;
    }
    void print()
    {
        for (auto i : projectList)
        {
            i.print();
            cout << "\n";
        }
    }

    void printflag()
    {
        cout << flag << endl;
    }

    void calc()
    {
        int a = 0;
        for (auto i : projectList)
        {
            a += i.getFlag();
        }
        flag = a / projectList.size();
    }
    int getFlag()
    {
        calc();
        return flag;
    }
};
