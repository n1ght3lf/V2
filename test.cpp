/**
 * @file test.cpp
 * @brief Unit tests for the Student class using Google Test.
 */

#include "gtest/gtest.h"
#include "student.h"
#include <cmath>

/// @brief Tests the default constructor of the Student class.
TEST(StudentTest, HandlesDefaultConstructor) {
    Student s;
    EXPECT_EQ(s.getFirstName(), "");
    EXPECT_EQ(s.getLastName(), "");
    EXPECT_EQ(s.getExamResults(), 0);
}

/// @brief Tests the parameterized constructor of the Student class.
TEST(StudentTest, HandlesParameterizedConstructor) {
    Student s("Jonas", "Kazlauskas", 10, {7, 8, 9});
    EXPECT_EQ(s.getFirstName(), "Jonas");
    EXPECT_EQ(s.getLastName(), "Kazlauskas");
    EXPECT_EQ(s.getExamResults(), 10);
    EXPECT_EQ(s.getHomeworkResults(), std::vector<int>({7, 8, 9}));
}

/// @brief Tests the copy constructor of the Student class.
TEST(StudentTest, HandlesCopyConstructor) {
    Student s1("Jonas", "Kazlauskas", 10, {7, 8, 9});
    Student s2(s1);
    EXPECT_EQ(s2.getFirstName(), "Jonas");
    EXPECT_EQ(s2.getLastName(), "Kazlauskas");
    EXPECT_EQ(s2.getExamResults(), 10);
    EXPECT_EQ(s2.getHomeworkResults(), std::vector<int>({7, 8, 9}));
}

/// @brief Tests the move constructor of the Student class.
TEST(StudentTest, HandlesMoveConstructor) {
    Student s1("Jonas", "Kazlauskas", 10, {7, 8, 9});
    Student s2(std::move(s1));
    EXPECT_EQ(s2.getFirstName(), "Jonas");
    EXPECT_EQ(s2.getLastName(), "Kazlauskas");
    EXPECT_EQ(s2.getExamResults(), 10);
    EXPECT_EQ(s2.getHomeworkResults(), std::vector<int>({7, 8, 9}));
}

/// @brief Tests the assignment operator of the Student class.
TEST(StudentTest, HandlesAssignmentOperator) {
    Student s1("Jonas", "Kazlauskas", 10, {7, 8, 9});
    Student s2;
    s2 = s1;
    EXPECT_EQ(s2.getFirstName(), "Jonas");
    EXPECT_EQ(s2.getLastName(), "Kazlauskas");
    EXPECT_EQ(s2.getExamResults(), 10);
    EXPECT_EQ(s2.getHomeworkResults(), std::vector<int>({7, 8, 9}));
}

/// @brief Tests the move assignment operator of the Student class.
TEST(StudentTest, HandlesMoveAssignmentOperator) {
    Student s1("Jonas", "Kazlauskas", 10, {7, 8, 9});
    Student s2;
    s2 = std::move(s1);
    EXPECT_EQ(s2.getFirstName(), "Jonas");
    EXPECT_EQ(s2.getLastName(), "Kazlauskas");
    EXPECT_EQ(s2.getExamResults(), 10);
    EXPECT_EQ(s2.getHomeworkResults(), std::vector<int>({7, 8, 9}));
}

/// @brief Tests the calculateAverage method of the Student class.
TEST(StudentTest, HandlesCalculateAverage) {
    Student s("Jonas", "Kazlauskas", 10, {7, 8, 9});
    EXPECT_DOUBLE_EQ(s.calculateAverage(), 8.0);
}

/// @brief Tests the calculateMedian method of the Student class.
TEST(StudentTest, HandlesCalculateMedian) {
    Student s("Jonas", "Kazlauskas", 10, {7, 8, 9});
    EXPECT_DOUBLE_EQ(s.calculateMedian(), 8.0);
}

/// @brief Tests the calculateFinalGrade method of the Student class.
TEST(StudentTest, HandlesCalculateFinalGrade) {
    Student s("Jonas", "Kazlauskas", 10, {7, 8, 9});
    EXPECT_EQ(s.calculateFinalGrade(false), 9.2);
    EXPECT_EQ(s.calculateFinalGrade(true), 9.2);
}
