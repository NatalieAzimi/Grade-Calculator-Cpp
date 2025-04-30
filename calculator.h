//Base class for grade calculators
#ifndef CALCULATOR_H
#define CALCULATOR_H

// Abstract base class for grade calculators
class Calculator {
public:
    virtual void inputAssignments() = 0;    // Get assignment data from user
    virtual void calculateGrade() = 0;  // Calculate final grade
    virtual void displayResults() const = 0;    // Show results
    virtual ~Calculator() {}    // Virtual destructor
};
#endif // CALCULATOR_H

