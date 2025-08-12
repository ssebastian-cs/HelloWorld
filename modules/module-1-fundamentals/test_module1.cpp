#include "module1_loader.cpp"
#include <cassert>
#include <sstream>

class Module1Tester {
public:
    static void testLessonCreation() {
        std::cout << "Testing lesson creation..." << std::endl;
        
        // Test Variables and Data Types lesson
        auto lesson1 = createVariablesDataTypesLesson();
        assert(lesson1 != nullptr);
        assert(lesson1->getId() == "mod1-lesson1");
        assert(lesson1->getTitle() == "Variables and Data Types");
        
        // Test Character and Boolean lesson
        auto lesson2 = createCharacterBooleanLesson();
        assert(lesson2 != nullptr);
        assert(lesson2->getId() == "mod1-lesson1b");
        
        // Test String Basics lesson
        auto lesson3 = createStringBasicsLesson();
        assert(lesson3 != nullptr);
        assert(lesson3->getId() == "mod1-lesson1c");
        
        // Test Arithmetic Operators lesson
        auto lesson4 = createArithmeticOperatorsLesson();
        assert(lesson4 != nullptr);
        assert(lesson4->getId() == "mod1-lesson2a");
        
        // Test Comparison and Logical Operators lesson
        auto lesson5 = createComparisonLogicalOperatorsLesson();
        assert(lesson5 != nullptr);
        assert(lesson5->getId() == "mod1-lesson2b");
        
        std::cout << "✓ All lessons created successfully!" << std::endl;
    }
    
    static void testExerciseCreation() {
        std::cout << "Testing exercise creation..." << std::endl;
        
        // Test Variable and Data Type exercises
        auto varExercises = createVariableDataTypeExercises();
        assert(varExercises.size() == 3);
        assert(varExercises[0]->getId() == "var-decl-1");
        assert(varExercises[1]->getId() == "data-sizes-1");
        assert(varExercises[2]->getId() == "char-ascii-1");
        
        // Test Operator exercises
        auto opExercises = createOperatorExercises();
        assert(opExercises.size() == 3);
        assert(opExercises[0]->getId() == "arithmetic-calc-1");
        assert(opExercises[1]->getId() == "comparison-logical-1");
        assert(opExercises[2]->getId() == "mixed-ops-1");
        
        std::cout << "✓ All exercises created successfully!" << std::endl;
    }
    
    static void testModuleIntegration() {
        std::cout << "Testing module integration..." << std::endl;
        
        Module1Fundamentals module1;
        
        // Capture output to test display methods
        std::ostringstream output;
        std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
        
        module1.displayModuleOverview();
        module1.listLessons();
        module1.listExercises();
        
        // Restore cout
        std::cout.rdbuf(oldCout);
        
        std::string result = output.str();
        assert(result.find("MODULE 1: C++ FUNDAMENTALS") != std::string::npos);
        assert(result.find("Available Lessons: 5") != std::string::npos);
        assert(result.find("Available Exercises: 6") != std::string::npos);
        
        std::cout << "✓ Module integration working correctly!" << std::endl;
    }
    
    static void testLessonContent() {
        std::cout << "Testing lesson content..." << std::endl;
        
        auto lesson = createVariablesDataTypesLesson();
        
        // Capture output
        std::ostringstream output;
        std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
        
        lesson->displayContent();
        
        // Restore cout
        std::cout.rdbuf(oldCout);
        
        std::string result = output.str();
        assert(result.find("Variables and Data Types") != std::string::npos);
        assert(result.find("What are Variables?") != std::string::npos);
        assert(result.find("Integer Data Types") != std::string::npos);
        
        std::cout << "✓ Lesson content displays correctly!" << std::endl;
    }
    
    static void testExerciseContent() {
        std::cout << "Testing exercise content..." << std::endl;
        
        auto exercises = createVariableDataTypeExercises();
        auto& exercise = exercises[0];
        
        assert(!exercise->getStarterCode().empty());
        assert(!exercise->getSolution().empty());
        assert(exercise->getStarterCode().find("#include <iostream>") != std::string::npos);
        assert(exercise->getSolution().find("int studentAge = 20") != std::string::npos);
        
        std::cout << "✓ Exercise content is complete!" << std::endl;
    }
    
    static void runAllTests() {
        std::cout << "\n=== Running Module 1 Tests ===" << std::endl;
        
        testLessonCreation();
        testExerciseCreation();
        testModuleIntegration();
        testLessonContent();
        testExerciseContent();
        
        std::cout << "\n✅ All tests passed! Module 1 is ready for use." << std::endl;
        std::cout << "=== Test Summary ===" << std::endl;
        std::cout << "• 5 lessons created and tested" << std::endl;
        std::cout << "• 6 exercises created and tested" << std::endl;
        std::cout << "• Module integration verified" << std::endl;
        std::cout << "• Content quality validated" << std::endl;
    }
};

int main() {
    Module1Tester::runAllTests();
    return 0;
}
