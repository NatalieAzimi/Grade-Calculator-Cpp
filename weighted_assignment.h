//Weighted assignment class
#ifndef WEIGHTED_ASSIGNMENT_H
#define WEIGHTED_ASSIGNMENT_H
#include "assignment.h"
#include <string>

// Assignment with category and weight
class WeightedAssignment : public Assignment {

private:
    std::string category;   // Category name (e.g., "Homework")
    float category_weight;  // Weight percentage

public:
    WeightedAssignment();
    void setCategory(const std::string& category);
    void setCategoryWeight(float category_weight);
    std::string getCategory() const;
    float getCategoryWeight() const;
};
#endif
