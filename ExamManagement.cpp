#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <conio.h>
#include <sstream> // stringstream
#include <filesystem>
#include "student.hpp"
#include "questionPaper.hpp"
#include "teacher.hpp"

using namespace std;
namespace fs = std::filesystem;

int main()
{
    int choice, studentChoice, teacherChoice;
    Student student;
    Teacher teacher;
    cout << "----------Welcome to Exam Management System----------" << endl;
    cout << "1. Student" << endl;
    cout << "2. Teacher" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        //  Enter the student portal
        {
            cin.ignore();
            system("cls");
            system("color B9");

            bool flag = false;
            bool istaken = false;

            do
            {
                flag = student.isRegistered();
            } while (flag != true);

            char ch = '\0';
            do
            {
                system("cls");

                cout << "----------Welcome " << student.getName() + " to Student Portal----------" << endl;
                cout << "1. Take Exam" << endl;
                cout << "2. View Result" << endl;
                cout << "0. Exit" << endl;
                cout << "Enter your choice: ";
                cin >> studentChoice;
                switch (studentChoice)
                {
                    // exam portal open
                case 1:
                {
                    system("cls");
                    cout << "----------Available Exam----------" << endl;
                    // show the available exam
                    int i = student.showAvailableExam();
                    if (i == 0)
                    {
                        cout << "No exam available" << endl;
                        system("pause");
                        break;
                    }

                    int examChoice;
                    do
                    {
                        cout << "Enter your choice: ";
                        cin >> examChoice;
                        if (examChoice < 1 || examChoice > i)
                        {
                            cout << "Invalid choice" << endl;
                        }
                    } while (examChoice < 0 || examChoice > i);

                    // set the course name and course code
                    student.setCourseDetails(examChoice);

                    // check if the student already attempted the exam
                    string courseDirectory = "Courses/" + student.getCourseName() + student.getCourseCode();
                    string attemptedFileName = courseDirectory + "/attempted.txt";
                    fstream attemptedFile(attemptedFileName, ios::in);

                    if (attemptedFile)
                    {
                        string line;
                        while (getline(attemptedFile, line))
                        {
                            if (line == student.getId())
                            {
                                cout << "You have already attempted the exam" << endl;
                                istaken = true;
                                break;
                            }
                        }
                        attemptedFile.close();
                    }
                    if (!istaken)
                    {
                        // add the student to the attempted list
                        attemptedFile.open(attemptedFileName, ios::out | ios::app);
                        attemptedFile << student.getId() << endl;
                        attemptedFile.close();
                        // take the exam
                        string fileName = courseDirectory + "/question.txt";
                        fstream questionfile(fileName, ios::in);

                        if (questionfile)
                        {
                            string question, option1, option2, option3, option4;
                            int correctOption;
                            int numOfQuestion = 0;
                            //  Check the number of question
                            while (getline(questionfile, question))
                            {
                                getline(questionfile, option1);
                                getline(questionfile, option2);
                                getline(questionfile, option3);
                                getline(questionfile, option4);
                                questionfile >> correctOption;
                                questionfile.ignore();
                                numOfQuestion++;
                            }
                            questionfile.close();
                            //  Create the array of question
                            Question questions[numOfQuestion];
                            questionfile.open(fileName, ios::in);
                            int i = 0;

                            while (getline(questionfile, question))
                            {
                                getline(questionfile, option1);
                                getline(questionfile, option2);
                                getline(questionfile, option3);
                                getline(questionfile, option4);
                                questionfile >> correctOption;
                                questionfile.ignore();
                                questions[i].setQuestion(question, option1, option2, option3, option4, correctOption);
                                i++;
                            }
                            questionfile.close();
                            //  set the question paper
                            QuestionPaper questionPaper;
                            questionPaper.setQuestionPaper(numOfQuestion, questions);
                            int result = 0;
                            // start exam
                            system("cls");
                            for (int i = 0; i < numOfQuestion; i++)
                            {
                                cout << "----------Question " << i + 1 << "----------" << endl;
                                cout << questionPaper.getQuestion(i).getQuestion() << endl;
                                cout << "a. " << questionPaper.getQuestion(i).getOption(0) << endl;
                                cout << "b. " << questionPaper.getQuestion(i).getOption(1) << endl;
                                cout << "c. " << questionPaper.getQuestion(i).getOption(2) << endl;
                                cout << "d. " << questionPaper.getQuestion(i).getOption(3) << endl;
                                cout << "Enter your answer: ";
                                char answer;
                                do
                                {
                                    cin.ignore();
                                    cin >> answer;
                                    switch (answer)
                                    {
                                    case 'a':
                                        answer = 1;
                                        break;
                                    case 'b':
                                        answer = 2;
                                        break;
                                    case 'c':
                                        answer = 3;
                                        break;
                                    case 'd':
                                        answer = 4;
                                        break;
                                    default:
                                        cout << "Invalid choice" << endl;
                                        break;
                                    }
                                } while (
                                    answer != 1 && answer != 2 && answer != 3 && answer != 4);
                                if (questionPaper.isCorrectAnswer(i, answer))
                                {
                                    result++;
                                }
                            }
                            // exam finish

                            // show the result
                            system("cls");
                            double percentage = questionPaper.calculatePercentage(numOfQuestion, result);
                            cout << "----------Result----------" << endl;
                            cout << "Total Question: " << numOfQuestion << endl;
                            cout << "Correct Answer: " << result << endl;
                            cout << "Wrong Answer: " << numOfQuestion - result << endl;

                            cout << "Percentage: " << percentage << "%" << endl;
                            // add the result to the database
                            student.addResultInStudentDatabase(student.getCourseName(), student.getCourseCode(), result, numOfQuestion, percentage);

                            // add the result to the course database

                            student.addResultInCourseDatabase(student.getId(), result, numOfQuestion, percentage);
                        }
                    }
                    system("pause");

                    break;
                }
                case 2:
                {
                    system("cls");
                    cout << "----------View Result----------" << endl;
                    // show the result
                    string parentDirectory = "Students/" + student.getId();
                    string fileName = parentDirectory + "/result.txt";
                    student.viewResult(fileName);
                    system("pause");
                }

                break;
                case 0:
                    exit(0);
                    break;
                default:
                    cout << "Invalid choice" << endl;
                    system("pause");
                    break;
                }

            } while (studentChoice != 0);
        }
        break;

    case 2:
    {
        system("cls");
        system("color 7E");
        bool flag = false;
        do
        {
            flag = teacher.verifyTeacher(1010);

        } while (flag != true);
        do
        {
            system("cls");

            cout << "----------Welcome to Teacher Portal----------" << endl;
            cout << "1. Add Student" << endl;
            cout << "2. Remove Student" << endl;
            cout << "3. Add Question" << endl;
            cout << "4. View Attempted Students" << endl;
            cout << "5. View Result Of A Course " << endl;
            cout << "0. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> teacherChoice;
            switch (teacherChoice)
            {
                // Add student
            case 1:
            {
                system("cls");
                cin.ignore();
                teacher.addStudent();
                system("pause");
                break;
            }
            // Remove student
            case 2:
            {
                system("cls");
                cin.ignore();
                teacher.removeStudent();
                break;
            }
            // Add question
            case 3:
            {
                system("cls");
                cin.ignore();
                teacher.addQuestion();
                system("pause");
                break;
            }
            // View attempted students
            case 4:
            {
                system("cls");
                cin.ignore();
                cout << "----------View Attempted Students----------" << endl;

                int i = teacher.showAvailableExam();
                if (!i)
                {
                    cout << "No course available" << endl;
                    system("pause");
                    break;
                }

                int courseChoice;
                do
                {
                    cout << "Enter your choice: ";
                    cin >> courseChoice;
                    if (courseChoice < 1 || courseChoice > i)
                    {
                        cout << "Invalid choice" << endl;
                    }
                } while (
                    courseChoice < 1 || courseChoice > i);

                teacher.setCourseDetails(courseChoice);

                string parentDirectory = "Courses/" + teacher.getCourseName() + teacher.getCourseCode();
                string fileName = parentDirectory + "/attempted.txt";
                teacher.showAttemptedStudents(fileName);
                system("pause");
                break;
            }
            // View result of a course
            case 5:
            {
                system("cls");
                cin.ignore();
                cout << "----------View Result Of A Course----------" << endl;

                int i = teacher.showAvailableExam();
                if (!i)
                {
                    cout << "No course available" << endl;
                    system("pause");
                    break;
                }

                int courseChoice;
                do
                {
                    cout << "Enter your choice: ";
                    cin >> courseChoice;
                    if (courseChoice < 1 || courseChoice > i)
                    {
                        cout << "Invalid choice" << endl;
                    }
                } while (
                    courseChoice < 1 || courseChoice > i);

                teacher.setCourseDetails(courseChoice);
                string parentDirectory = "Courses/" + teacher.getCourseName() + teacher.getCourseCode();
                string fileName = parentDirectory + "/result.txt";
                teacher.showResult(fileName);
                system("pause");
                break;
            }

            case 0:
                exit(0);
                break;
            default:
                cout << "Invalid choice" << endl;
                system("pause");
                break;
            }
        } while (teacherChoice != 0);
    }
    }
}
