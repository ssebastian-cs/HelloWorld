#include <iostream>
#include <memory>
#include "core/Lesson.h"
#include "core/Exercise.h"
#include "core/ProgressTracker.h"
#include "utils/CodeCompiler.h"
#include "utils/TestRunner.h"

int main() {
    std::cout << "C++ Learning Curriculum System" << std::endl;
    std::cout << "===============================" << std::endl;
    
    // Initialize core components
    auto progressTracker = std::make_unique<ProgressTracker>("student_001");
    auto compiler = std::make_unique<CodeCompiler>(CompilerType::GCC);
    auto testRunner = std::make_unique<TestRunner>();
    
    // Test basic functionality
    std::cout << "\nTesting system components..." << std::endl;
    
    // Test compiler availability
    if (compiler->isCompilerAvailable()) {
        std::cout << "✓ Code compiler is available" << std::endl;
        std::cout << "  Compiler version: " << compiler->getCompilerVersion() << std::endl;
    } else {
        std::cout << "✗ Code compiler not found" << std::endl;
    }
    
    // Test progress tracking
    progressTracker->startModule("module-1", "C++ Fundamentals");
    std::cout << "✓ Progress tracking initialized" << std::endl;
    std::cout << "  Student ID: " << progressTracker->getStudentId() << std::endl;
    
    // Create a sample lesson
    auto lesson = std::make_unique<Lesson>("lesson-1-1", "Variables and Data Types", 
                                          "Introduction to C++ variables and basic data types");
    
    auto concept = std::make_unique<Concept>("concept-1-1-1", "Integer Variables", 
                                           "Learn about int, long, and short data types",
                                           ConceptType::THEORY, DifficultyLevel::BEGINNER);
    
    lesson->addConcept(std::move(concept));
    std::cout << "✓ Sample lesson created: " << lesson->getTitle() << std::endl;
    
    // Create a sample exercise
    auto exercise = std::make_unique<Exercise>("exercise-1-1", "Variable Declaration",
                                             "Practice declaring and initializing variables",
                                             ExerciseType::CODING, DifficultyLevel::BEGINNER);
    
    exercise->setInstructions("Declare an integer variable named 'age' and initialize it to 25");
    exercise->setStarterCode("// Declare and initialize your variable here\n");
    
    TestCase testCase("", "25", "Variable should be initialized to 25");
    exercise->addTestCase(testCase);
    
    std::cout << "✓ Sample exercise created: " << exercise->getTitle() << std::endl;
    
    std::cout << "\nSystem initialization complete!" << std::endl;
    std::cout << "Ready to begin C++ learning journey." << std::endl;
    
    return 0;
}
