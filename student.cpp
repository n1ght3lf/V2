#include "student.h"

Student::Student() : firstName(""), lastName(""), examMark(0) {} //  konstruktorius

//  konstruktorius su parametrais
Student::Student(const std::string& firstName, const std::string& lastName, int examMark, const std::vector<int>& homeworkMarks)
    : firstName(firstName), lastName(lastName), examMark(examMark), homeworkMarks(homeworkMarks) {}

//  konstruktorius su parametrais
Student::Student(const Student& other)
    : firstName(other.firstName), lastName(other.lastName),
      homeworkMarks(other.homeworkMarks), examMark(other.examMark) {}

//  move konstruktorius
Student::Student(Student&& other) noexcept
    : firstName(std::move(other.firstName)), lastName(std::move(other.lastName)),
      homeworkMarks(std::move(other.homeworkMarks)), examMark(other.examMark) {}

//  copy konstruktorius
Student& Student::operator=(const Student& other) {
    if (this != &other) {
        firstName = other.firstName;
        lastName = other.lastName;
        homeworkMarks = other.homeworkMarks;
        examMark = other.examMark;
    }
    return *this;
}

//  move konstruktorius
Student& Student::operator=(Student&& other) noexcept {
    if (this != &other) {
        firstName = std::move(other.firstName);
        lastName = std::move(other.lastName);
        homeworkMarks = std::move(other.homeworkMarks);
        examMark = other.examMark;
    }
    return *this;
}

// ivesties operatorius (nuskaitymui is failo)
std::istream& operator>>(std::istream& is, Student& s) {
    std::string tempFirstName, tempLastName;
    std::vector<int> grades;
    int grade;

    if (!(is >> tempFirstName >> tempLastName)) {
        return is;
    }
    s.setFirstName(tempFirstName);
    s.setLastName(tempLastName);

    while (is >> grade) {
        grades.push_back(grade);
    }

    // Clear the fail state if end of file is reached
    if (is.eof()) {
        is.clear();
    }

    if (!grades.empty()) {
        s.setExamMark(grades.back()); // Set the last grade as the exam result
        grades.pop_back(); // Remove the last grade from the homework results
    }
    s.setHomeworkMarks(std::move(grades));

    return is;
}

// isvesties operatorius 
std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << std::setw(15) << s.getLastName() 
       << std::setw(15) << s.getFirstName();
    return os;
}

double Student::calculateAverage() const {
    if (homeworkMarks.empty()) {
        return 0;
    }
    double sum = std::accumulate(homeworkMarks.begin(), homeworkMarks.end(), 0.0);
    return sum / homeworkMarks.size();
}

double Student::calculateMedian() const { 
    if (homeworkMarks.empty()) { 
        return 0;
    }
    std::vector<int> scores = homeworkMarks; 
    std::sort(scores.begin(), scores.end()); 
    int size = scores.size(); 
    if (size % 2 == 0) { 
        return (scores[size / 2 - 1] + scores[size / 2]) / 2.0; 
    } else {
        return scores[size / 2];
    }
}

double Student::calculateFinalGrade(bool median) const { 
    double homeworkGrade = median ? calculateMedian() : calculateAverage();
    return 0.4 * homeworkGrade + 0.6 * examMark;
}
