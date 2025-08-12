#include "../../src/core/Lesson.h"
#include "../../src/core/Exercise.h"
#include "lessons/lesson-1-variables-data-types.cpp"
#include "lessons/lesson-2-operators.cpp"
#include "exercises/exercise-1-variables-datatypes.cpp"
#include "exercises/exercise-2-operators.cpp"
#include <iostream>
#include <vector>
#include <memory>

class Module1Fundamentals {
private:
    std::vector<std::unique_ptr<Lesson>> lessons;
    std::vector<std::unique_ptr<Exercise>> exercises;
    
public:
    Module1Fundamentals() {
        loadLessons();
        loadExercises();
    }
    
    void loadLessons() {
        // Load Variable and Data Types lessons
        lessons.push_back(createVariablesDataTypesLesson());
        lessons.push_back(createCharacterBooleanLesson());
        lessons.push_back(createStringBasicsLesson());
        
        // Load Operator lessons
        lessons.push_back(createArithmeticOperatorsLesson());
        lessons.push_back(createComparisonLogicalOperatorsLesson());
    }
    
    void loadExercises() {
        // Load Variable and Data Types exercises
        auto varExercises = createVariableDataTypeExercises();
        for (auto& exercise : varExercises) {
            exercises.push_back(std::move(exercise));
        }
        
        // Load Operator exercises
        auto opExercises = createOperatorExercises();
        for (auto& exercise : opExercises) {
            exercises.push_back(std::move(exercise));
        }
    }
    
    void displayModuleOverview() {
        std::cout << "\n" << std::string(60, '=') << std::endl;
        std::cout << "MODULE 1: C++ FUNDAMENTALS" << std::endl;
        std::cout << std::string(60, '=') << std::endl;
        std::cout << "This module covers the basic building blocks of C++ programming:" << std::endl;
        std::cout << "• Variables and Data Types" << std::endl;
        std::cout << "• Operators and Expressions" << std::endl;
        std::cout << "• Basic Input/Output" << std::endl;
        std::cout << std::endl;
        std::cout << "Available Lessons: " << lessons.size() << std::endl;
        std::cout << "Available Exercises: " << exercises.size() << std::endl;
        std::cout << std::string(60, '=') << std::endl;
    }
    
    void runLesson(int lessonIndex) {
        if (lessonIndex >= 0 && lessonIndex < lessons.size()) {
            lessons[lessonIndex]->displayContent();
        } else {
            std::cout << "Invalid lesson index!" << std::endl;
        }
    }
    
    void runExercise(int exerciseIndex) {
        if (exerciseIndex >= 0 && exerciseIndex < exercises.size()) {
            exercises[exerciseIndex]->displayInstructions();
            std::cout << "\nStarter Code:" << std::endl;
            std::cout << exercises[exerciseIndex]->getStarterCode() << std::endl;
        } else {
            std::cout << "Invalid exercise index!" << std::endl;
        }
    }
    
    void listLessons() {
        std::cout << "\nAvailable Lessons:" << std::endl;
        for (size_t i = 0; i < lessons.size(); ++i) {
            std::cout << i << ". " << lessons[i]->getTitle() << std::endl;
        }
    }
    
    void listExercises() {
        std::cout << "\nAvailable Exercises:" << std::endl;
        for (size_t i = 0; i < exercises.size(); ++i) {
            std::cout << i << ". " << exercises[i]->getTitle() << std::endl;
        }
    }
    
    void runInteractiveMode() {
        displayModuleOverview();
        
        int choice;
        do {
            std::cout << "\n--- Module 1 Menu ---" << std::endl;
            std::cout << "1. List Lessons" << std::endl;
            std::cout << "2. Run Lesson" << std::endl;
            std::cout << "3. List Exercises" << std::endl;
            std::cout << "4. Run Exercise" << std::endl;
            std::cout << "0. Exit" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            
            switch (choice) {
                case 1:
                    listLessons();
                    break;
                case 2: {
                    listLessons();
                    std::cout << "Enter lesson number: ";
                    int lessonNum;
                    std::cin >> lessonNum;
                    runLesson(lessonNum);
                    break;
                }
                case 3:
                    listExercises();
                    break;
                case 4: {
                    listExercises();
                    std::cout << "Enter exercise number: ";
                    int exerciseNum;
                    std::cin >> exerciseNum;
                    runExercise(exerciseNum);
                    break;
                }
                case 0:
                    std::cout << "Exiting Module 1..." << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice! Please try again." << std::endl;
            }
        } while (choice != 0);
    }
};

// Demo function to test the module
void demonstrateModule1() {
    Module1Fundamentals module1;
    
    std::cout << "=== Module 1 Demonstration ===" << std::endl;
    
    // Show overview
    module1.displayModuleOverview();
    
    // Run first lesson
    std::cout << "\n--- Running First Lesson ---" << std::endl;
    module1.runLesson(0);
    
    // Show first exercise
    std::cout << "\n--- Showing First Exercise ---" << std::endl;
    module1.runExercise(0);
    
    std::cout << "\n=== End of Demonstration ===" << std::endl;
}

int main() {
    // Uncomment to run demonstration
    // demonstrateModule1();
    
    // Uncomment to run interactive mode
    Module1Fundamentals module1;
    module1.runInteractiveMode();
    
    return 0;
}
