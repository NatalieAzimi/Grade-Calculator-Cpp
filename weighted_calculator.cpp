//Weighted grade calculator implementation
#include "weighted_calculator.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cmath>

// Constructor - initialize values
WeightedCalculator::WeightedCalculator()
    : total_weighted_score(0.0f), earned_grade('F') {}

// Helper function to validate numeric input
float WeightedCalculator::validateNumericInput(const std::string& prompt, float min, float max) {
    float value;
    while (true) {
        std::cout << prompt;
        if (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between "
                      << min << " and " << max << ".\n";
        } else if (value < min || value > max) {
            std::cout << "Value must be between " << min << " and " << max << ".\n";
        } else {
            return value;
        }
    }
}

// Set up grading categories and weights
void WeightedCalculator::setGradingScheme(const std::map<std::string, float>& category_weights) {
    float total_weight = 0.0f;
    for (const auto& pair : category_weights) {
        total_weight += pair.second;
    }

    // Check if weights sum to 100%
    if (std::abs(total_weight - 100.0f) > 0.01f) {
        throw GradeCalculatorException("Category weights must sum to 100% (current sum: " +
                                    std::to_string(total_weight) + "%)");
    }

    this->category_weights = category_weights;
}

// Get assignment details from user
void WeightedCalculator::inputAssignments() {
    if (category_weights.empty()) {
        throw GradeCalculatorException("No categories set. Set grading scheme first.");
    }

    std::cout << "\nENTERING WEIGHTED ASSIGNMENTS\n";
    std::cout << "==================================\n\n";

    int assignment_num = 1;
    while (true) {
        std::string name;
        std::cout << "\nAssignment #" << assignment_num << " (or 'done' to finish): ";
        std::getline(std::cin >> std::ws, name);

        if (name == "done" || name == "Done") break;

        WeightedAssignment assignment;
        assignment.setName(name);

        // Select category
        std::cout << "\nAvailable Categories:\n";
        int index = 1;
        std::vector<std::string> categories;
        for (const auto& cat : category_weights) {
            std::cout << index++ << ". " << cat.first << " (" << cat.second << "%)\n";
            categories.push_back(cat.first);
        }

        int cat_choice = validateNumericInput("Select category (number): ", 1, categories.size());
        assignment.setCategory(categories[cat_choice-1]);

        // Get points
        float possible = validateNumericInput("Points possible: ", 0, 10000);
        assignment.setPointsPossible(possible);

        float earned = validateNumericInput("Points earned: ", 0, possible);
        assignment.setPointsEarned(earned);

        // Bonus status
        int is_bonus = validateNumericInput("Is this a bonus assignment? (1: Yes, 0: No): ", 0, 1);
        assignment.setBonus(is_bonus == 1);

        assignments.push_back(assignment);
        assignment_num++;
    }
}

void WeightedCalculator::calculateGrade() {
    total_weighted_score = 0.0f;
    std::map<std::string, std::pair<float, float>> category_totals; // <earned, possible>

    // Initialize category totals
    for (const auto& cat : category_weights) {
        category_totals[cat.first] = {0.0f, 0.0f};
    }

    // Calculate category totals
    for (const auto& assignment : assignments) {
        const std::string& cat = assignment.getCategory();
        if (assignment.isBonus()) {
            category_totals[cat].first += assignment.getPointsEarned(); // Bonus adds to earned only
        } else {
            category_totals[cat].first += assignment.getPointsEarned();
            category_totals[cat].second += assignment.getPointsPossible();
        }
    }

    // Calculate weighted score
    for (const auto& cat : category_weights) {
        float earned = category_totals[cat.first].first;
        float possible = category_totals[cat.first].second;
        float percentage = (possible > 0) ? (earned / possible) * 100 : 0.0f;
        total_weighted_score += (percentage * cat.second) / 100;
    }

    // Determine letter grade
    if (total_weighted_score >= 90) earned_grade = 'A';
    else if (total_weighted_score >= 80) earned_grade = 'B';
    else if (total_weighted_score >= 70) earned_grade = 'C';
    else if (total_weighted_score >= 60) earned_grade = 'D';
    else earned_grade = 'F';
}

void WeightedCalculator::displayResults() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nFINAL GRADE REPORT:\n";
    std::cout << "=================\n\n";

    // Display summary
    std::cout << "SUMMARY:\n";
    std::cout << "-------\n";
    std::cout << "Total Weighted Score: " << total_weighted_score << "%\n";
    std::cout << "Final Letter Grade: " << earned_grade << "\n\n";

    // Display assignments
    std::cout << "ASSIGNMENT DETAILS:\n";
    std::cout << "------------------\n";
    std::cout << std::left << std::setw(25) << "Assignment"
              << std::setw(15) << "Category"
              << std::setw(15) << "Points"
              << std::setw(15) << "Percentage"
              << "Bonus\n";
    std::cout << std::string(80, '-') << "\n";

    for (const auto& assignment : assignments) {
        float percentage = (assignment.getPointsEarned() / assignment.getPointsPossible()) * 100;
        std::cout << std::left << std::setw(25) << assignment.getName()
                  << std::setw(15) << assignment.getCategory()
                  << std::setw(6) << assignment.getPointsEarned() << "/"
                  << std::setw(8) << assignment.getPointsPossible()
                  << std::setw(15) << std::setprecision(1) << percentage << "%"
                  << (assignment.isBonus() ? "Yes" : "No") << "\n";
    }

    // Category breakdown
    std::cout << "\nCATEGORY BREAKDOWN:\n";
    std::cout << "------------------\n";
    for (const auto& category : category_weights) {
        float earned = 0.0f, possible = 0.0f, bonus = 0.0f;

        for (const auto& assignment : assignments) {
            if (assignment.getCategory() == category.first) {
                if (assignment.isBonus()) {
                    bonus += assignment.getPointsEarned();
                } else {
                    earned += assignment.getPointsEarned();
                    possible += assignment.getPointsPossible();
                }
            }
        }

        float percentage = (possible > 0) ? (earned / possible) * 100 : 0.0f;
        float weighted_contribution = (percentage * category.second) / 100;

        std::cout << "\n" << category.first << " (" << category.second << "% weight)\n";
        std::cout << "  Regular Points: " << earned << "/" << possible << " ("
                  << std::setprecision(1) << percentage << "%)\n";
        if (bonus > 0) {
            std::cout << "  Bonus Points: +" << bonus << "\n";
        }
        std::cout << "  Weighted Contribution: " << std::setprecision(2)
                  << weighted_contribution << "%\n";
    }
    std::cout << "\n";
}
