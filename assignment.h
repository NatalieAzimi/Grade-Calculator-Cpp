//Assignment class definition
#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <string>

// Stores information about a single assignment
class Assignment {
private:
  std::string name;      // name of the assignment
  float points_possible; // total points possible for the assignment
  float points_earned;   // points earned by student input
  bool bonus;            // whether the assignment is a bonus
  static int total_assignments; // static counter to track total assignments created

public:
  // Default constructor
  Assignment();

  // Setters
  void setName(const std::string &name);         // set the assignment name
  void setPointsPossible(float points_possible); // set total points possible
  void setPointsEarned(float points_earned);     // set points earned
  void setBonus(bool bonus); // set whether the assignment is a bonus

  // Getters
  std::string getName() const;      // get assignment name
  float getPointsPossible() const;  // get total points possible
  float getPointsEarned() const;    // get points earned
  bool isBonus() const;             // checks if assignment is a bonus
  static int getTotalAssignments(); // get the number of assignments created
};

#endif // ASSIGNMENT_H

