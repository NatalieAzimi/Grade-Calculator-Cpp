# Grade Calculator User Guide:

## Table of Contents
1. [Introduction](#Introduction)
2. [Features](#Features)
3. [Getting Started](#Getting-Started)
4. [Using the Calculator](#Using-The-Calculator)
   - [Standard Calculator](#Standard-Points-Based-Calculator)
   - [Weighted Calculator](#Category-Based-Weighted-Calculator)
5. [Understanding Results](#Understanding-Results)
6. [Tips](#Tips)
7. [Troubleshooting](#Troubleshooting)



## Introduction
This Grade Calculator helps students track their academic performance by calculating course grades based on assignment scores. It offers two calculation methods:
1. **Standard Points-Based** - All assignments contribute equally
2. **Category-Based Weighted** - Assignments are grouped by categories with different weights



## Features
- Calculate overall course grade
- Support for bonus assignments
- Detailed assignment tracking
- Clear grade breakdowns
- Both points-based and weighted grading schemes



## Getting Started
1. **Compile the program** using Code::Blocks or your preferred C++ compiler
2. **Run the executable** from your terminal or IDE
3. Follow the on-screen instructions



# Using the Calculator:

## Standard Points-Based Calculator
1. Select option `1` when prompted for calculator type
2. Enter the **total points possible** for the course
3. Set grade cutoffs (minimum points needed for each letter grade)
4. Input your assignments:
   - Assignment name
   - Points possible
   - Points earned
   - Whether it's a bonus assignment
5. Type `done` when finished entering assignments

## Category-Based Weighted Calculator
1. Select option `2` when prompted for calculator type
2. Enter the number of grade categories (e.g., Exams, Homework, Labs)
3. For each category:
   - Enter category name
   - Set weight percentage (must total 100%)
4. Input your assignments:
   - Assignment name
   - Category it belongs to
   - Points possible
   - Points earned
   - Whether it's a bonus assignment
5. Type `done` when finished entering assignments



## Understanding Results
After entering all assignments, the calculator displays:
- Detailed list of all assignments with percentages
- Highest and lowest scores (standard calculator)
- Points summary:
  - Regular points earned
  - Bonus points (if any)
  - Total points
- Final percentage (rounded and unrounded)
- Letter grade earned
- Total number of assignments entered



## Tips
- Bonus assignments add extra points without affecting total possible points
- For weighted calculations, ensure category weights sum to exactly 100%
- You can enter partial scores (e.g., 8.5 out of 10)
- The program validates all inputs to prevent errors



## Troubleshooting!
- **Invalid numeric input**: The program will prompt you to enter a valid number
- **Weights don't sum to 100%**: The weighted calculator requires exact 100% total
- **Blank screen**: Try resizing your terminal window if output seems missing
- **Program crashes**: Ensure you're entering data in the requested format


