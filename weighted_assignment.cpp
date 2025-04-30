//Weighted assignment implementation
#include "weighted_assignment.h"

// Constructor
WeightedAssignment::WeightedAssignment()
    : Assignment(), category(""), category_weight(0.0f) {}

// Setter
void WeightedAssignment::setCategory(const std::string& category) {
    this->category = category;
}

void WeightedAssignment::setCategoryWeight(float category_weight) {
    this->category_weight = category_weight;
}

//Getters
std::string WeightedAssignment::getCategory() const {
    return category;
}

float WeightedAssignment::getCategoryWeight() const {
    return category_weight;
}
