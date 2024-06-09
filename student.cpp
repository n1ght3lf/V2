#include "student.h"

// Default constructor: initializes an empty student
Student::Student() : firstName(""), lastName(""), examMark(0) {}

// Parameterized constructor: initializes a student with given details
Student::Student(const std::string& firstName, const std::string& lastName, int examMark, const std::vector<int>& homeworkMarks)
    : firstName(firstName), lastName(lastName), examMark(examMark), homeworkMarks(homeworkMarks) {}

// Copy constructor: creates a copy of an existing student
Student::Student(const Student& other)
    : firstName(other.firstName), lastName(other.lastName),
      homeworkMarks(other.homeworkMarks), examMark(other.examMark) {}

// Move constructor: transfers ownership of resources from another student
Student::Student(Student&& other) noexcept
    : firstName(std::move(other.firstName)), lastName(std::move(other.lastName)),
      homeworkMarks(std::move(other.homeworkMarks)), examMark(other.examMark) {}

// Copy assignment operator: copies data from another student
Student& Student::operator=(const Student& other) {
    if (this != &other) {
        firstName = other.firstName;
        lastName = other.lastName;
        homeworkMarks = other.homeworkMarks;
        examMark = other.examMark;
    }
    return *this;
}

// Move assignment operator: moves data from another student
Student& Student::operator=(Student&& other) noexcept {
    if (this != &other) {
        firstName = std::move(other.firstName);
        lastName = std::move(other.lastName);
        homeworkMarks = std::move(other.homeworkMarks);
        examMark = other.examMark;
    }
    return *this;
}

// Input operator: reads student data from input stream
std::istream& operator>>(std::istream& is, Student& s) {
    std::string tempFirstName, tempLastName;
    std::vector<int> grades;
    int grade;

    // Read first and last names
    if (!(is >> tempFirstName >> tempLastName)) {
        return is;
    }
    s.setFirstName(tempFirstName);
    s.setLastName(tempLastName);

    // Read grades until end of input
    while (is >> grade) {
        grades.push_back(grade);
    }

    // Clear the fail state if end of file is reached
    if (is.eof()) {
        is.clear();
    }

    // Set the exam mark and homework marks
    if (!grades.empty()) {
        s.setExamMark(grades.back());
        grades.pop_back();
    }
    s.setHomeworkMarks(std::move(grades));

    return is;
}

// Output operator: writes student data to output stream
std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << std::setw(15) << s.getLastName() 
       << std::setw(15) << s.getFirstName();
    return os;
}

// Calculates the average of homework marks
double Student::calculateAverage() const {
    if (homeworkMarks.empty()) {
        return 0;
    }
    double sum = std::accumulate(homeworkMarks.begin(), homeworkMarks.end(), 0.0);
    return sum / homeworkMarks.size();
}

// Calculates the median of homework marks
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

// Calculates the final grade based on exam mark and homework marks
double Student::calculateFinalGrade(bool median) const { 
    double homeworkGrade = median ? calculateMedian() : calculateAverage();
    return 0.4 * homeworkGrade + 0.6 * examMark;
}
