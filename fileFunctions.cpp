#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>

#define BLUE 1
#define GREEN 2
#define AMBER 3
#define RED 4

using namespace std;

void printColoredText(const string &text, int colorCode)
{
    cout << "\033[1;" << colorCode << "m" << text << "\033[0m";
}

string getColorName(int colorCode)
{
    switch (colorCode)
    {
    case BLUE:
        return "BLUE";
    case GREEN:
        return "GREEN";
    case AMBER:
        return "AMBER";
    case RED:
        return "RED";
    default:
        return "UNKNOWN";
    }
}

vector<string> splitString(const string &input, const string &delimiters)
{
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;

    while (getline(iss, token))
    {
        size_t startPos = 0;
        size_t endPos = token.find_first_of(delimiters);

        while (endPos != string::npos)
        {
            if (endPos != startPos)
            {
                tokens.push_back(token.substr(startPos, endPos - startPos));
            }
            startPos = endPos + 1;
            endPos = token.find_first_of(delimiters, startPos);
        }

        if (startPos < token.length())
        {
            tokens.push_back(token.substr(startPos, token.length() - startPos));
        }
    }

    return tokens;
}

void fileHandling(vector<string> &devinfo, vector<string> &testinfo, string &admininfo, string &hrinfo)
{
    string delimiters = "\n";
    fstream fin_hr, fin_ad, fin_dev, fin_test;
    const char *env = "FB";
    const char *vv = getenv(env);
    string hrpath = "\\hr.txt", testpath = "\\test.txt", devpath = "\\dev.txt", adminpath = "\\admin.txt";

    hrpath.insert(0, vv);
    adminpath.insert(0, vv);
    devpath.insert(0, vv);
    testpath.insert(0, vv);

    fin_hr.open(hrpath, ios::in);
    fin_ad.open(adminpath, ios::in);
    fin_dev.open(devpath, ios::in);
    fin_test.open(testpath, ios::in);

    if ((!fin_hr.is_open()) || (!fin_ad.is_open()) || (!fin_dev.is_open()) || (!fin_test.is_open()))
    {
        cout << "Failed to open the file. 2" << endl;
        return;
    }

    string line_hr, line_ad, line_dev, line_test;
    vector<string> lines_hr, lines_ad, lines_dev, lines_test;

    while (getline(fin_hr, line_hr))
    {
        vector<string> result = splitString(line_hr, delimiters);
        lines_hr.insert(lines_hr.end(), result.begin(), result.end());
    }
    hrinfo = lines_hr[0];
    fin_hr.close();

    while (getline(fin_ad, line_ad))
    {
        vector<string> result = splitString(line_ad, delimiters);
        lines_ad.insert(lines_ad.end(), result.begin(), result.end());
    }
    admininfo = lines_ad[0];
    fin_ad.close();

    while (getline(fin_dev, line_dev))
    {
        vector<string> result = splitString(line_dev, delimiters);
        lines_dev.insert(lines_dev.end(), result.begin(), result.end());
        devinfo.insert(devinfo.end(), result.begin(), result.end());
    }
    fin_dev.close();

    while (getline(fin_test, line_test))
    {
        vector<string> result = splitString(line_test, delimiters);
        lines_test.insert(lines_test.end(), result.begin(), result.end());
        testinfo.insert(testinfo.end(), result.begin(), result.end());
    }
    fin_test.close();
};

void writeResult(vector<int> &a)
{
    int admin_flag = a[3];
    int dev_flag = a[1];
    int test_flag = a[2];
    int overall_flag = a[0];
    int hr_flag = a[4];

    string colorName_overall = getColorName(overall_flag);
    string colorName_dev = getColorName(dev_flag);
    string colorName_test = getColorName(test_flag);
    string colorName_admin = getColorName(admin_flag);
    string colorName_hr = getColorName(hr_flag);
    cout << "---------------------------------------------------------------------------------\n";
    printColoredText("Overall: " + to_string(overall_flag) + " (" + colorName_overall + ")", overall_flag);
    cout << "\n---------------------------------------------------------------------------------";
    cout << "\nDetailed Analysis" << endl;
    cout << "---------------------------------------------------------------------------------\n";
    cout << "Development Team Report: " << dev_flag << " which is indicating that development is in the " << colorName_dev << " in the BRAG.\n";
    cout << "Testing Team Report: " << test_flag << " which is indicating that development is in the " << colorName_test << " in the BRAG.\n";
    cout << "Admin Team Report: " << admin_flag << " which is indicating that development is in the " << colorName_admin << " in the BRAG.\n";
    cout << "HR Team Report: " << hr_flag << " which is indicating that development is in the " << colorName_hr << " in the BRAG.\n";
    fstream final_file;
    final_file.open("result.txt", ios::out);
    if (!final_file)
    {
        cout << "File not created!";
    }
    else
    {
        final_file << "---------------------------------------------------------------------------------\n";
        final_file << "Combined Analysis\n";
        final_file << "---------------------------------------------------------------------------------\n";
        final_file
            << "\n";
        final_file << "-> Overall Performance by the company: " << overall_flag << " which is indicating that your company has got the " << colorName_overall << " Flag of the BRAG."
                   << "\n"
                   << "\n";
        final_file << "---------------------------------------------------------------------------------\n";
        final_file << "Detailed Report\n";
        final_file << "---------------------------------------------------------------------------------\n";
        final_file << '\n';
        final_file << "Development Team Report: " << dev_flag << " which is indicating that development is in the " << colorName_dev << " in the BRAG.\n";
        final_file << "\n";
        final_file << "Testing Team Report: " << test_flag << " which is indicating that development is in the " << colorName_test << " in the BRAG.\n";
        final_file << "\n";
        final_file << "Admin Team Report: " << admin_flag << " which is indicating that development is in the " << colorName_admin << " in the BRAG.\n";
        final_file << "\n";
        final_file << "HR Team Report: " << hr_flag << " which is indicating that development is in the " << colorName_hr << " in the BRAG.\n";
        final_file << "\n";
        final_file.close();
    }
};