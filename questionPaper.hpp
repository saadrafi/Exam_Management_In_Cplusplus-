#include <iostream>
#include <string>
#include "question.hpp"

using namespace std;

class QuestionPaper
{
private:
    int numOfQuestion;
    Question questions[30];

public:
    void setQuestionPaper(int numOfQuestion, Question questions[])
    {
        this->numOfQuestion = numOfQuestion;
        for (int i = 0; i < numOfQuestion; i++)
        {
            this->questions[i] = questions[i];
        }
    }
    int getNumOfQuestion()
    {
        return numOfQuestion;
    }
    Question getQuestion(int index)
    {
        return questions[index];
    }
    bool isCorrectAnswer(int questionIndex, char answer) // returns true if the given answer is correct otherwise false.
    {
        if (questions[questionIndex].getCorrectOption() == answer)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    double calculatePercentage(int totalQuestion, int correctAnswer)
    {
        return (double)correctAnswer * 100 / totalQuestion;
    }
};