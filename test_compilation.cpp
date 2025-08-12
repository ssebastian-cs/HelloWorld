// Simple compilation test to verify header structure
#include "src/core/Lesson.h"
#include "src/core/Exercise.h"
#include "src/core/ProgressTracker.h"
#include "src/utils/CodeCompiler.h"
#include "src/utils/TestRunner.h"

int main() {
    // Test that all classes can be instantiated
    ProgressTracker tracker("test_student");
    
    // Test lesson creation
    Lesson lesson("test-lesson", "Test Lesson", "A test lesson");
    
    // Test exercise creation
    Exercise exercise("test-ex", "Test Exercise", "A test exercise", 
                     ExerciseType::CODING, DifficultyLevel::BEGINNER);
    
    // Test compiler creation
    CodeCompiler compiler(CompilerType::GCC);
    
    // Test runner creation
    TestRunner testRunner;
    
    return 0;
}
