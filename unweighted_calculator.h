//Unweighted grade calculator
#ifndef UNWEIGHTED_CALCULATOR_H
#define UNWEIGHTED_CALCULATOR_H

#include <vector>
#include <string>
#include "calculator.h"
#include "assignment.h"

// Calculates grades without weights
class UnweightedCalculator : public Calculator {
private:
    int total_course_points;    // Total course points
    float total_points_earned;  // Points student earned
    float total_percentage_earned;  // Final percentage
    float A_points, B_points, C_points, D_points;   // Grade cutoffs
    float A_percentage, B_percentage, C_percentage, D_percentage;
    char earned_grade;  // Final grade letter
    std::vector<Assignment> assignments;    // List of assignments

public:
    UnweightedCalculator();
    void setGradingScheme(int total_course_points, float A_points,
                         float B_points, float C_points, float D_points);
    void inputAssignments() override;
    void calculateGrade() override;
    void displayResults() const override;
};

#endif
