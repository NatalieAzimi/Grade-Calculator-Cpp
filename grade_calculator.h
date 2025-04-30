//Basic grade calculator
#ifndef GRADE_CALCULATOR_H
#define GRADE_CALCULATOR_H

#include <vector>
#include <string>
#include"assignment.h"


// Simple grade calculator (unweighted)
class GradeCalculator {
private:
     // Variables for course grading
    int total_course_points;
    float total_points_earned;
    float total_percentage_earned;
    float A_points;
    float B_points;
    float C_points;
    float D_points;
    float A_percentage;
    float B_percentage;
    float C_percentage;
    float D_percentage;
    char earned_grade;
    std::vector<Assignment> assignments;

public:
    GradeCalculator();

    void setGradingScheme(int total_course_points, float A_points,
                          float B_points, float C_points, float D_points);
    void inputAssignments();
    void calculateGrade();
    void displayResults();
};

#endif // GRADE_CALCULATOR_H
