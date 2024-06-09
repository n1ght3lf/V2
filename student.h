#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <deque>
#include <list>
#include <istream>
#include <ostream>
#include <iomanip>
#include <sstream>

class Student
{
private:
    std::string firstName; 
    std::string lastName; // changed from lastName
    std::vector<int> homeworkMarks; // changed from homeworkResults
    int examMark; // changed from examResults

public:
    // Constructors
    Student();
    Student(const std::string& firstName, const std::string& familyName, int examMark, const std::vector<int>& homeworkMarks);
    Student(const Student& other);
    Student(Student&& other) noexcept;

    // Assignment operators
    Student& operator=(const Student& other);
    Student& operator=(Student&& other) noexcept;

    // Input and output operators
    friend std::istream& operator>>(std::istream& is, Student& s);
    friend std::ostream& operator<<(std::ostream& os, const Student& s);

    // Destructor
    ~Student() {}

    // Getters
    inline std::string getFirstName() const { return firstName; } 
    inline std::string getLastName() const { return lastName; } // changed from getLastName
    std::string getName() const { return getFirstName() + " " + getLastName(); } // changed from getName
    const std::vector<int>& getHomeworkMarks() const { return homeworkMarks; } // changed from getHomeworkResults
    int getExamMark() const { return examMark; } // changed from getExamResults
    int getExamGrade() const { return homeworkMarks.back(); } // changed from getExamGrade
    void removeLastHomeworkMark() { if (!homeworkMarks.empty()) { homeworkMarks.pop_back(); } } // changed from removeLastHomeworkGrade

    // Setters
    void setFirstName(std::string firstName) { this->firstName = std::move(firstName); } 
    void setLastName(std::string lastName) { this->lastName = std::move(lastName); } // changed from setLastName
    void addHomeworkMark(int mark) { homeworkMarks.push_back(mark); } // changed from addHomeworkResult
    void clearHomeworkMarks() { homeworkMarks.clear(); } // changed from clearHomeworkResults
    void setExamMark(int examMark) { this->examMark = examMark; } // changed from setExamResults
    void setHomeworkMarks(std::vector<int> marks) { homeworkMarks = std::move(marks); } // changed from setHomeworkResults

    // Functions
    double calculateMedian() const;
    double calculateAverage() const;
    double calculateFinalGrade(bool median) const;
};

#endif // STUDENT_H