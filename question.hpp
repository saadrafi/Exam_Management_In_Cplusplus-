#include <iostream>
#include <string>
using namespace std;
#pragma once

class Question
{
protected:
    string question;
    string options[4];
    int correctOption;

public:
    void setQuestion(string question, string option1, string option2, string option3, string option4, int correctOption)
    {
        this->question = question;
        options[0] = option1;
        options[1] = option2;
        options[2] = option3;
        options[3] = option4;
        this->correctOption = correctOption;
    }
    string getQuestion()
    {
        return question;
    }
    string getOption(int index)
    {
        return options[index];
    }
    int getCorrectOption()
    {
        return correctOption;
    }
};