#include <iostream>
#include <map>
#include <limits>
#include "unweighted_calculator.h"
#include "weighted_calculator.h"

void clearScreen() {
    #ifdef _WIN32
    (void) system("clear");
    #else
    (void) system("clear");
    #endif
}

void displayWelcome() {
    clearScreen();
    std::cout << "==========================================\n";
    std::cout << "      COSC 1437 Grade Calculator\n";
    std::cout << "==========================================\n\n";
}

int main() {
    displayWelcome();

    Calculator* calculator = nullptr;

    try {
        std::cout << "Please choose your calculator type:\n\n";
        std::cout << "1. Standard Points-Based Calculator\n";
        std::cout << "   - All assignments contribute equally\n";
        std::cout << "   - Simple points earned vs points possible\n\n";
        std::cout << "2. Category-Based Weighted Calculator\n";
        std::cout << "   - Assignments grouped by categories (e.g., Exams, Homework)\n";
        std::cout << "   - Each category contributes a percentage to final grade\n\n";

        char choice;
        while (true) {
            std::cout << "Enter your choice (1 or 2): ";
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (choice == '1' || choice == '2') {
                break;
            }
            std::cout << "Invalid input. Please enter 1 or 2.\n";
        }

        if (choice == '2') {
            calculator = new WeightedCalculator();
            clearScreen();
            std::cout << "WEIGHTED GRADE CALCULATOR SETUP\n";
            std::cout << "================================\n\n";

            int num_categories;
            while (true) {
                std::cout << "How many grade categories do you have? (e.g., Exams, Homework, Labs): ";
                if (!(std::cin >> num_categories)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter a positive number.\n";
                } else if (num_categories <= 0) {
                    std::cout << "Please enter a positive number.\n";
                } else {
                    break;
                }
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::map<std::string, float> category_weights;
            float total_weight = 0.0f;

            std::cout << "\nEnter each category and its weight (must total 100%)\n";
            std::cout << "---------------------------------------------------\n";

            for (int i = 0; i < num_categories; i++) {
                std::string category;
                float weight;

                std::cout << "\nCategory " << (i + 1) << ":\n";
                std::cout << "Name (e.g., 'Exams', 'Homework'): ";
                std::getline(std::cin, category);

                while (true) {
                    std::cout << "Weight for " << category << " (in %, remaining: "
                              << (100 - total_weight) << "%): ";
                    if (!(std::cin >> weight)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input. Please enter a number.\n";
                    } else if (weight <= 0) {
                        std::cout << "Weight must be positive.\n";
                    } else if ((total_weight + weight) > 100.01f) { // Allow for floating point imprecision
                        std::cout << "Total weight cannot exceed 100%.\n";
                    } else {
                        total_weight += weight;
                        break;
                    }
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                category_weights[category] = weight;
            }

            // Verify weights sum to 100% (with some tolerance for floating point)
            if (std::abs(total_weight - 100.0f) > 0.01f) {
                throw std::runtime_error("Category weights must sum to exactly 100%");
            }

            static_cast<WeightedCalculator*>(calculator)->setGradingScheme(category_weights);
        } else {
            calculator = new UnweightedCalculator();
            clearScreen();
            std::cout << "STANDARD GRADE CALCULATOR SETUP\n";
            std::cout << "===============================\n\n";

            int total_points;
            float A_points, B_points, C_points, D_points;

            // Get total course points with validation
            while (true) {
                std::cout << "Enter the total points possible for the course: ";
                if (!(std::cin >> total_points) || total_points <= 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter a positive number.\n";
                } else {
                    break;
                }
            }

            std::cout << "\nGRADE CUTOFFS\n";
            std::cout << "-------------------------\n";
            std::cout << "Enter the minimum points needed for each letter grade:\n";

            auto getGradeCutoff = [](const std::string& grade, int max) {
                float points;
                while (true) {
                    std::cout << grade << " (" << max-10 << "-" << max << "% equivalent): ";
                    if (!(std::cin >> points) || points < 0) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input. Please enter a non-negative number.\n";
                    } else {
                        return points;
                    }
                }
            };

            A_points = getGradeCutoff("A", 100);
            B_points = getGradeCutoff("B", 89);
            C_points = getGradeCutoff("C", 79);
            D_points = getGradeCutoff("D", 69);

            static_cast<UnweightedCalculator*>(calculator)->setGradingScheme(
                total_points, A_points, B_points, C_points, D_points);
        }

        clearScreen();
        calculator->inputAssignments();
        calculator->calculateGrade();

        clearScreen();
        calculator->displayResults();

        delete calculator;

        std::cout << "\nPress Enter to exit...";
        std::cin.ignore();
        std::cin.get();

    } catch (const std::exception& e) {
        std::cerr << "\nERROR: " << e.what() << "\n";
        delete calculator;
        return 1;
    }

    return 0;
}
