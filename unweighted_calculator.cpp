//Unweighted calculator implementation
#include "unweighted_calculator.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cmath>

// Constructor - initialize values
UnweightedCalculator::UnweightedCalculator()
    : total_course_points(0), total_points_earned(0.0f), total_percentage_earned(0.0f),
      A_points(0.0f), B_points(0.0f), C_points(0.0f), D_points(0.0f),
      A_percentage(0.0f), B_percentage(0.0f), C_percentage(0.0f), D_percentage(0.0f),
      earned_grade('F') {}


// Set grade cutoffs
void UnweightedCalculator::setGradingScheme(int total_course_points, float A_points,
                                           float B_points, float C_points, float D_points) {
    this->total_course_points = total_course_points;
    this->A_points = A_points;
    this->B_points = B_points;
    this->C_points = C_points;
    this->D_points = D_points;


    // Calculate percentages
    A_percentage = (A_points / total_course_points) * 100;
    B_percentage = (B_points / total_course_points) * 100;
    C_percentage = (C_points / total_course_points) * 100;
    D_percentage = (D_points / total_course_points) * 100;
}

// Get assignments from user
void UnweightedCalculator::inputAssignments() {
    std::string assignment_name;
    float points_possible, points_earned;
    bool is_bonus;

    std::cout << "\nENTERING ASSIGNMENTS\n";
    std::cout << "====================\n\n";
    std::cout << "Instructions:\n";
    std::cout << "- Enter each assignment's details\n";
    std::cout << "- Type 'done' when finished\n";
    std::cout << "- Bonus assignments add extra points without affecting total possible\n\n";

    int assignment_num = 1;
    while (true) {
        std::cout << "Assignment #" << assignment_num << "\n";
        std::cout << "------------\n";

        std::cout << "Name (or 'done' to finish): ";
        std::getline(std::cin >> std::ws, assignment_name);

        if (assignment_name == "done" || assignment_name == "Done") {
            break;
        }

        Assignment assignment;
        assignment.setName(assignment_name);

        std::cout << "Points possible for " << assignment_name << ": ";
        while (!(std::cin >> points_possible)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }
        assignment.setPointsPossible(points_possible);

        std::cout << "Points earned for " << assignment_name << ": ";
        while (!(std::cin >> points_earned)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }
        assignment.setPointsEarned(points_earned);

        std::cout << "Is this a bonus assignment? (1: Yes, 0: No): ";
        while (!(std::cin >> is_bonus)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter 1 or 0: ";
        }
        assignment.setBonus(is_bonus);

        assignments.push_back(assignment);
        assignment_num++;

        std::cout << "\n";
    }
}

// Calculate final grade
void UnweightedCalculator::calculateGrade() {
    // Reset totals
    total_points_earned = 0.0f;
    float bonus_points = 0.0f;

    // Calculate totals
    for (const auto& assignment : assignments) {
        if (assignment.isBonus()) {
            bonus_points += assignment.getPointsEarned();
        } else {
            total_points_earned += assignment.getPointsEarned();
        }
    }

    // Calculate percentages
    if (total_course_points > 0) {
        total_percentage_earned = (total_points_earned / total_course_points) * 100;
        total_percentage_earned += (bonus_points / total_course_points) * 100;
    } else {
        total_percentage_earned = 0.0f;
    }

    // Determine grade
    if (total_percentage_earned >= A_percentage) {
        earned_grade = 'A';
    } else if (total_percentage_earned >= B_percentage) {
        earned_grade = 'B';
    } else if (total_percentage_earned >= C_percentage) {
        earned_grade = 'C';
    } else if (total_percentage_earned >= D_percentage) {
        earned_grade = 'D';
    } else {
        earned_grade = 'F';
    }
}

// Show results
void UnweightedCalculator::displayResults() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nUnweighted Grade Calculation Results\n";
    std::cout << "------------------------------------\n";

    // Display individual assignments
    for (const auto& assignment : assignments) {
        float percentage = (assignment.getPointsEarned() / assignment.getPointsPossible()) * 100;
        std::cout << "Assignment: " << assignment.getName()
                  << "\n Points Earned: " << assignment.getPointsEarned()
                  << "\n Points Possible: " << assignment.getPointsPossible()
                  << "\n Percentage: " << percentage << "%"
                  << "\n Bonus: " << (assignment.isBonus() ? "Yes" : "No")
                  << "\n\n";
    }

    // Calculate bonus points separately
    float bonus_points = 0.0f;
    for (const auto& assignment : assignments) {
        if (assignment.isBonus()) {
            bonus_points += assignment.getPointsEarned();
        }
    }

    // Display summary
    std::cout << "SUMMARY\n";
    std::cout << "-------\n";
    std::cout << "Regular Points Earned: " << total_points_earned << "\n"
              << "Bonus Points Earned: " << bonus_points << "\n"
              << "Total Points (Including Bonus): " << (total_points_earned + bonus_points) << "\n"
              << "Total Course Points: " << total_course_points << "\n"
              << "Final Percentage: " << total_percentage_earned << "%\n"
              << "Final Letter Grade: " << earned_grade << "\n";
}
