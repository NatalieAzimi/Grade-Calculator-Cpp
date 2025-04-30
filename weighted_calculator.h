//Weighted grade calculator class definition
#ifndef WEIGHTED_CALCULATOR_H
#define WEIGHTED_CALCULATOR_H

#include "weighted_assignment.h"
#include "calculator.h"
#include <vector>
#include <map>
#include <stdexcept>


// Custom exception class for grade calculation errors
class GradeCalculatorException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;    // Inherit constructors
};

// Calculates grades using weighted categories
class WeightedCalculator : public Calculator {
private:
    std::vector<WeightedAssignment> assignments;    // List of assignments
    std::map<std::string, float> category_weights;  // Categories and their weights
    float total_weighted_score; // Final calculated score
    char earned_grade;  // Final letter grade

    // Helper function to validate user input
    float validateNumericInput(const std::string& prompt, float min = 0.0f, float max = 1000.0f);

public:
    WeightedCalculator();   // Constructor
    void setGradingScheme(const std::map<std::string, float>& category_weights);
    void inputAssignments() override;
    void calculateGrade() override;
    void displayResults() const override;
};

#endif
