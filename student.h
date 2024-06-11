#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"

/// @brief Studentų klasė, paveldinti asmens klasę
class Student : public Person {
private:
    std::string firstName;
    std::string lastName;
    std::vector<int> homeworkMarks;
    int examMark;

public:
    /// @brief Konstruktorius
    Student();
    Student(const std::string& firstName, const std::string& familyName, int examMark, const std::vector<int>& homeworkMarks);
    Student(const Student& other);
    Student(Student&& other) noexcept;

    /// @brief Priskyrimo operatoriai
    Student& operator=(const Student& other);
    Student& operator=(Student&& other) noexcept;

    /// @brief Įvesties ir išvesties operatoriai
    friend std::istream& operator>>(std::istream& is, Student& s);
    friend std::ostream& operator<<(std::ostream& os, const Student& s);

    /// @brief Destruktorius
    ~Student() {}

    /// @brief Geteriai
    inline std::string getFirstName() const { return firstName; }
    inline std::string getLastName() const { return lastName; }
    std::string getName() const { return getFirstName() + " " + getLastName(); }
    const std::vector<int>& getHomeworkMarks() const { return homeworkMarks; }
    int getExamMark() const { return examMark; }
    int getExamGrade() const { return homeworkMarks.back(); }
    void removeLastHomeworkMark() { if (!homeworkMarks.empty()) { homeworkMarks.pop_back(); } }

    /// @brief Seteriai
    void setFirstName(std::string firstName) { this->firstName = std::move(firstName); }
    void setLastName(std::string lastName) { this->lastName = std::move(lastName); }
    void addHomeworkMark(int mark) { homeworkMarks.push_back(mark); }
    void clearHomeworkMarks() { homeworkMarks.clear(); }
    void setExamMark(int examMark) { this->examMark = examMark; }
    void setHomeworkMarks(std::vector<int> marks) { homeworkMarks = std::move(marks); }

    /// @brief Funkcijos
    double calculateMedian() const;
    double calculateAverage() const;
    double calculateFinalGrade(bool median) const;
};

#endif // STUDENT_H
