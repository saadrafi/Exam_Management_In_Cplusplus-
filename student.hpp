
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <filesystem>
#include "course.hpp"
using namespace std;
class Student : public Course
{
private:
    string name;
    string id;

public:
    void setStudent(string name, string id)
    {
        this->name = name;
        this->id = id;
    }
    void setID(string id)
    {
        this->id = id;
    }
    void setName(string name)
    {
        this->name = name;
    }
    string getName()
    {
        return name;
    }
    string getId()
    {
        return id;
    }

    bool isRegistered()
    {
        cout << "----------Please Log In to Continue----------" << endl;
        cout << "Enter student ID: ";
        cin >> id;

        // find student id in the file if present continue or show no added

        string studentDirectory = "Students/" + id;
        string fileName = studentDirectory + "/info.txt";
        fstream studentfile(fileName, ios::in);

        // check the student is registered or not
        if (studentfile)
        {
            string line;
            while (getline(studentfile, line))
            {
                if (line.find("name:") != string::npos) // taking the student name from file
                {
                    name = line.substr(5);
                }
                else if (line.find("id:") != string::npos) // taking the student id from file
                {
                    id = line.substr(3);
                }
            }
            studentfile.close();
            return true;
        }
        else
        {
            cout << "Student not registered. Contact with course teacher" << endl;
            cout << "Do you want to continue? (y/n): ";
            char ch;
            cin >> ch;
            if (ch == 'n' || ch == 'N')
            {
                exit(0);
            }
            else
            {
                return false;
            }
        }
    }

    void setCourseDetails(int examChoice)
    {
        string fileName = "availableExam.txt";
        fstream availableExamFile(fileName, ios::in);
        string line;
        string courseName, courseID;
        int i = 0;
        while (getline(availableExamFile, line))
        {
            if (line.empty())
            {
                continue;
            }
            if (i == examChoice - 1)
            {
                stringstream ss(line);
                ss >> courseName >> courseID;
                // transform course name into uppercase
                transform(
                    courseName.begin(),
                    courseName.end(),
                    courseName.begin(),
                    ::toupper);

                setCourse(courseName, courseID);
                cout << getCourseName() << "  " << getCourseCode() << endl;
                break;
            }
            i++;
        }
        availableExamFile.close();
    }

    void viewResult(string fileName)
    {
        fstream resultfile(fileName, ios::in);
        if (resultfile)
        {
            string line;
            cout << "Course"
                 << "\t\t"
                 << "Marks"
                 << "\t      \t"
                 << "Total Question"
                 << "\t\t"
                 << "Percentage" << endl;
            while (getline(resultfile, line))
            {
                stringstream ss(line);
                string courseName;
                int result, numOfQuestion;
                double percentage;
                ss >> courseName >> result >> numOfQuestion >> percentage;

                cout << courseName << "\t\t" << result << "\tout of\t" << numOfQuestion << "\t\t\t" << percentage << "%" << endl;
            }
            resultfile.close();
        }
        else
        {
            cout << "No result found" << endl;
        }
    }

    void addResultInStudentDatabase(string courseName, string courseCode, int result, int numOfQuestion, double percentage)
    {
        string studentDirectory = "Students/" + id;
        string fileName = studentDirectory + "/result.txt";
        fstream resultFile(fileName, ios::app);
        resultFile << courseName << courseCode << " " << result << " " << numOfQuestion << " " << percentage << endl;
        resultFile.close();
    }

    void addResultInCourseDatabase(string studentID, int result, int numOfQuestion, double percentage)
    {
        string courseDirectory = "Courses/" + getCourseName() + getCourseCode();
        string fileName = courseDirectory + "/result.txt";
        fstream resultFile(fileName, ios::app);
        resultFile << studentID << " " << result << " " << numOfQuestion << " " << percentage << endl;
        resultFile.close();
    }
};