#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <conio.h>
#include <algorithm>
#include <sstream>
#include <filesystem>
#include "course.hpp"
#include "question.hpp"

using namespace std;
namespace fs = std::filesystem;

class Teacher : public Course, public Question
{
private:
    string name;
    string id;

public:
    void setTeacher(string name, string id)
    {
        this->name = name;
        this->id = id;
    }
    string getName()
    {
        return name;
    }
    string getId()
    {
        return id;
    }

    bool verifyTeacher(int teacherCode)
    {
        int code;
        cout << "----------Please Verify to Continue----------" << endl;
        cout << "Enter teacher code: ";
        cin >> code;
        if (code == teacherCode)
        {
            return true;
        }
        else
        {
            cout << "Could not verify. Try Again" << endl;
            return false;
        }
    }

    void createDirectory(string parentDirectory)
    {
        // Create the parent directory if it doesn't exist
        if (!fs::exists(parentDirectory))
        {
            try
            {
                fs::create_directories(parentDirectory);
            }
            catch (const std::exception &e)
            {
                cout << "Error creating parent directory: " << e.what() << endl;
                exit(0);
            }
        }
    }

    void addStudent()
    {
        string name, id;
        cout << "----------Add Student----------" << endl;
        cout << "Enter student name: ";
        getline(cin, name);
        cout << "Enter student ID: ";
        cin >> id;
        // add the student to the database
        string parentDirectory = "Students/" + id;
        string fileName = parentDirectory + "/info.txt";

        // Create the parent directory if it doesn't exist

        createDirectory(parentDirectory);

        fstream studentfile(fileName, ios::in);
        fstream registerfile("registeredStudents.txt", ios::out | ios::app);
        //
        if (!studentfile)
        {
            studentfile.open(fileName, ios::out);
            if (!studentfile)
            {
                cout << "Error in creating file" << endl;
            }
            else
            {
                studentfile << "name:" << name << endl;
                studentfile << "id:" << id << endl;
                registerfile << id << endl;

                registerfile.close();
                studentfile.close();
                cout << "Student added successfully" << endl;
            }
        }
        else
        {
            cout << "Student already added" << endl;
        }
    }

    int showAllStudents()
    {
        int i = 0;
        cout << "---------------Registered Student List---------------" << endl;
        fstream registerfile("registeredStudents.txt", ios::in);
        cout << "NO.\t"
             << "ID" << endl;
        if (registerfile)
        {
            string line;

            while (getline(registerfile, line))
            {
                if (line.empty())
                {
                    continue;
                }
                cout << ++i << ".\t" << line << endl;
            }
            registerfile.close();
        }

        return i;
    }

    void removeStudent()
    {
        // show all students
        char again;
        do
        {
            system("cls");
            int i = showAllStudents();
            if (!i)
            {
                cout << "No student registered" << endl;
                system("pause");
                break;
            }
            string id;
            cout << "----------Remove Student----------" << endl;

            cout << "Enter student ID: ";
            cin >> id;
            // remove the student from the database

            string parentDirectory = "Students/" + id;
            if (fs::exists(parentDirectory))
            {
                fs::remove_all(parentDirectory);
                fstream registerfile("registeredStudents.txt", ios::in);
                fstream tempFile("temp.txt", ios::out);
                string line;
                while (getline(registerfile, line))
                {
                    if (line.empty())
                    {
                        continue;
                    }
                    if (line == id)
                    {
                        continue;
                    }
                    tempFile << line << endl;
                }
                registerfile.close();
                tempFile.close();
                fs::remove("registeredStudents.txt");
                fs::rename("temp.txt", "registeredStudents.txt");
                cout << "Successfully removed " << id << endl;
            }
            else
            {
                cout << "Student does not exist" << endl;
            }
            cout << "Press any key to remove another, q to exit" << endl;
            cin.ignore();
            again = _getch();

        } while (
            again != 'q');
    }
    void setCourseDetails(int courseChoice)
    {
        system("cls");
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
            if (i == courseChoice - 1)
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

    void showAttemptedStudents(string fileName)
    {
        fstream attemptedFile(fileName, ios::in);
        cout << "NO.\t"
             << "ID" << endl;
        if (attemptedFile)
        {
            string line;
            int i = 0;
            while (getline(attemptedFile, line))
            {
                if (line.empty())
                {
                    continue;
                }
                cout << ++i << ".\t" << line << endl;
            }
            attemptedFile.close();
        }
        else
        {
            cout << "No student attempted the exam" << endl;
        }
    }

    void showResult(string fileName)
    {
        fstream resultFile(fileName, ios::in);
        cout << "ID"
             << "\t\t"
             << "Marks"
             << "\t\t"
             << "Total Question"
             << "\t\t"
             << "Percentage"
             << endl;
        if (resultFile)
        {
            string line;
            while (getline(resultFile, line))
            {
                if (line.empty())
                {
                    continue;
                }
                stringstream ss(line);
                string id;
                int result, totalQuestion;
                double percentage;
                ss >> id >> result >> totalQuestion >> percentage;
                cout << id << "\t\t" << result << "\t\t" << totalQuestion << "\t\t\t" << percentage << "%" << endl;
            }
            resultFile.close();
        }
        else
        {
            cout << "No student attempted the exam" << endl;
        }
    }

    void addQuestion()
    {
        string courseName, courseID;
        char ch;
        cout << "----------Add Question----------" << endl;
        cout << "Course Name: ";
        getline(cin, courseName);
        cout << "Course ID: ";
        getline(cin, courseID);
        transform(courseName.begin(), courseName.end(), courseName.begin(), ::toupper);

        // add the question to the database
        string parentDirectory = "Courses/" + courseName + courseID;
        string fileName = parentDirectory + "/question.txt";

        // Create the parent directory if it doesn't exist
        createDirectory(parentDirectory);

        fstream questionfile(fileName, ios::in);
        if (!questionfile)
        {

            do
            {
                cout << "Enter question: ";
                getline(cin, question);
                for (int i = 0; i < 4; i++)
                {
                    cout << "Enter option " << i + 1 << ": ";
                    getline(cin, options[i]);
                }
                cout << "Enter correct option: ";
                cin >> correctOption;
                questionfile.open(fileName, ios::out | ios::app);
                questionfile << question << endl;
                for (int i = 0; i < 4; i++)
                {
                    questionfile << options[i] << endl;
                }
                questionfile << correctOption << endl;
                questionfile.close();
                cout << "Press any key add another, q to exit" << endl;
                cin.ignore();
                ch = _getch();

            } while (ch != 'q');

            questionfile.open("availableExam.txt", ios::out | ios::app);
            questionfile << courseName << " " << courseID << endl;
            questionfile.close();
            cout << "Question added successfully" << endl;
        }
        else
        {
            cout << "Question already added" << endl;
        }
    }
};