#include <iostream>
#include <string>
using namespace std;
#pragma once

class Course
{
private:
    string name;
    string code;

public:
    void setCourse(string name, string code)
    {
        this->name = name;
        this->code = code;
    }
    string getCourseName()
    {
        return name;
    }
    string getCourseCode()
    {
        return code;
    }

    int showAvailableExam()
    {
        string fileName = "availableExam.txt";
        fstream availableExamFile(fileName, ios::in);
        string line;
        int count = 0;
        while (getline(availableExamFile, line))
        {
            if (line.empty())
            {
                continue;
            }
            cout << ++count << ". " << line << endl;
        }
        availableExamFile.close();
        return count;
    }
};