#include "student.h"
#include "input.h"
#include "calculations.h"
#include "functionality.h"

using namespace std;

int main()
{
    auto startTotal = chrono::high_resolution_clock::now();
    setlocale(LC_ALL, "lt_LT.UTF-8");
    srand(time(0));
    bool Median = getMedianPreference();
    vector<Student> students;
    processStudents(students, Median, startTotal);
    return 0;
}