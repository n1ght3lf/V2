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
    std::string lastName;
    std::vector<int> homeworkMarks;
    int examMark;

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
    inline std::string getLastName() const { return lastName; }
    std::string getName() const { return getFirstName() + " " + getLastName(); }
    const std::vector<int>& getHomeworkMarks() const { return homeworkMarks; }
    int getExamMark() const { return examMark; }
    int getExamGrade() const { return homeworkMarks.back(); } 
    void removeLastHomeworkMark() { if (!homeworkMarks.empty()) { homeworkMarks.pop_back(); } }

    // Setters
    void setFirstName(std::string firstName) { this->firstName = std::move(firstName); } 
    void setLastName(std::string lastName) { this->lastName = std::move(lastName); }
    void addHomeworkMark(int mark) { homeworkMarks.push_back(mark); } 
    void clearHomeworkMarks() { homeworkMarks.clear(); }
    void setExamMark(int examMark) { this->examMark = examMark; }
    void setHomeworkMarks(std::vector<int> marks) { homeworkMarks = std::move(marks); }

    // Functions
    double calculateMedian() const;
    double calculateAverage() const;
    double calculateFinalGrade(bool median) const;
};

#endif // STUDENT_H
