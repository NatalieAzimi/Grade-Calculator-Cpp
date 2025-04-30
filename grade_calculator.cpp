//Basic grade calculator implementation
#include "grade_calculator.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cmath>

// Constructor - initialize values
GradeCalculator::GradeCalculator()
    : total_course_points(0), total_points_earned(0.0f), total_percentage_earned(0.0f),
    A_points(0.0f), B_points(0.0f), C_points(0.0f), D_points(0.0f),
    A_percentage(0.0f), B_percentage(0.0f), C_percentage(0.0f), D_percentage(0.0f),
    earned_grade('F'){}

// Set grade cutoffs
void GradeCalculator::setGradingScheme(int total_course_points, float A_points,
                          float B_points, float C_points, float D_points){
    this -> total_course_points = total_course_points;
    this -> A_points = A_points;
    this -> B_points = B_points;
    this -> C_points = C_points;
    this -> D_points = D_points;


    // Calculate percentages
    A_percentage = (A_points/total_course_points) * 100;
    B_percentage = (B_points/total_course_points) * 100;
    C_percentage = (C_points/total_course_points) * 100;
    D_percentage = (D_points/total_course_points) * 100;
}

// Get assignments from user
void GradeCalculator::inputAssignments(){
    bool score_input = true;
    std::string assignment_name;
    float assignment_score;
    float assignment_possible;
    bool assignment_bonus;

    // Displays the grading scheme entered by the user
    std::cout << "--------Grading Scheme You Input--------\n";
    std::cout << "Total Points Possible in the Course: " << total_course_points
                << '\n';
    std::cout << "Points needed for an 'A': " << A_points << " or "
            << A_percentage << '%' << '\n';
    std::cout << "Points needed for an 'B': " << B_points << " or "
            << B_percentage << '%' << '\n';
    std::cout << "Points needed for an 'C': " << C_points << " or "
            << C_percentage << '%' << '\n';
    std::cout << "Points needed for an 'D': " << D_points << " or "
            << D_percentage << '%' << '\n';

    std::cout <<'\n';

    // simple prompt with instructions for user
    std::cout << "--------Grade Calculation--------\n";
    std::cout << "You will be prompted to input scores for all assignments. \n"
              << "(Input 'done' or 'Done' to cease input and calculate the "
                 "letter grade.) \n \n";

    do {
        std::cout << "Please input the assignment name or 'done' to quit: ";
        std::getline(std::cin >> std::ws, assignment_name); // Read entire line, ignore leading whitespace

        if (assignment_name != "done" && assignment_name != "Done") {
            Assignment assignment;
            assignment.setName(assignment_name);

            std::cout << "Please input the points possible for " << assignment_name << ": ";
            std::cin >> assignment_possible;

            // Input validation: ensure the user inputs a numeric score
            while (std::cin.fail()) {
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // Discard invalid input
                std::cout << "Invalid input. Please enter a valid numeric value for points possible: ";
                std::cin >> assignment_possible;
            }
        assignment.setPointsPossible(assignment_possible);

        std::cout << "Please input the points earned for " << assignment_name << ": ";
        std::cin >> assignment_score;

        while (std::cin.fail()) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a valid numeric score for "
                  << assignment_name << ": ";
            std::cin >> assignment_score;
      }
      assignment.setPointsEarned(assignment_score);

        // Input where the assignment is a bonus
        std::cout << "Is this a bonus assignment? 1: Yes | 2: No ";
        bool assignment_bonus;
        int bonus_input; // Use an int to read the input
        std::cin >> bonus_input;

        while (std::cin.fail() || (bonus_input != 1 && bonus_input != 2)) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter (1: Yes | 2: No): ";
            std::cin >> bonus_input;
        }
        assignment_bonus = (bonus_input == 1); // converts 1 -> true, 2 -> false
        assignment.setBonus(assignment_bonus);

        assignments.push_back(assignment); // Add the assignment to the vector
        total_points_earned += assignment_score;
        } else {
        score_input = false;
        }
    } while (score_input);
}

void GradeCalculator::calculateGrade(){
      // Determines the final letter grade based on total points earned
  if (total_points_earned >= A_points) {
    earned_grade = 'A';
  } else if (total_points_earned >= B_points) {
    earned_grade = 'B';
  } else if (total_points_earned >= C_points) {
    earned_grade = 'C';
  } else if (total_points_earned >= D_points) {
    earned_grade = 'D';
  } else {
    earned_grade = 'F';
  }

    // Calculates total percentage earned
  total_percentage_earned = (total_points_earned / total_course_points) * 100;
}

void GradeCalculator::displayResults(){

 // Display the scores stored in the vector
  std::cout << "\n--------Scores entered--------\n";
  if (!assignments.empty()) {
    for (const auto &assignment : assignments) {
      float percentage =(assignment.getPointsEarned() / assignment.getPointsPossible()) * 100;
      std::cout << "Assignment: " << assignment.getName()
                << ", Points Earned: " << assignment.getPointsEarned()
                << ", Points Possible: " << assignment.getPointsPossible()
                << ", Percentage: " << percentage << '%'
                << ", Bonus: " << (assignment.isBonus() ? "Yes" : "No") << '\n';
    }

   // Find the highest and lowest scores using lambda functions
    auto min_it =
        std::min_element(assignments.begin(), assignments.end(),
                         [](const Assignment &a, const Assignment &b) {
                           return a.getPointsEarned() < b.getPointsEarned();
                         });
    auto max_it =
        std::max_element(assignments.begin(), assignments.end(),
                         [](const Assignment &a, const Assignment &b) {
                           return a.getPointsEarned() < b.getPointsEarned();
                         });

    std::cout << "\nHighest score: " << max_it->getPointsEarned() << '\n';
    std::cout << "Lowest score: " << min_it->getPointsEarned() << '\n';
  } else {
    std::cout << "\nNo scores were entered.\n";
  }

  std::cout << '\n';

  // Displays the final results!
  std::cout << "Total Points Earned: " << total_points_earned << '\n'
            << "Total Points Possible: " << total_course_points << '\n'
            << "Total Percentage: " << total_percentage_earned << '%' << '\n'
            << "Total Percentage (Rounded): " << round(total_percentage_earned)
            << '%' << '\n'
            << "Final Letter Grade: " << earned_grade << '\n'
            << '\n'
            << "Total number of assignments created: "
            << Assignment::getTotalAssignments() << '\n';

}
