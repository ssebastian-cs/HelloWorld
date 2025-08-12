#pragma once
#include <string>
#include <vector>
#include <functional>

enum class ExerciseType {
    CODING,
    MULTIPLE_CHOICE,
    FILL_IN_BLANK,
    DEBUG_CODE
};

struct TestCase {
    std::string input;
    std::string expectedOutput;
    std::string description;
    
    TestCase(const std::string& input, const std::string& expectedOutput, 
             const std::string& description = "");
};

class Exercise {
private:
    std::string exerciseId;
    std::string title;
    std::string description;
    std::string instructions;
    ExerciseType type;
    DifficultyLevel difficulty;
    std::vector<TestCase> testCases;
    std::string starterCode;
    std::string solutionCode;
    int maxAttempts;
    int currentAttempts;
    bool completed;
    double score;

public:
    Exercise(const std::string& id, const std::string& title, 
             const std::string& description, ExerciseType type, 
             DifficultyLevel difficulty);
    
    // Setup methods
    void setInstructions(const std::string& instructions);
    void setStarterCode(const std::string& code);
    void setSolutionCode(const std::string& code);
    void addTestCase(const TestCase& testCase);
    void setMaxAttempts(int attempts);
    
    // Getters
    const std::string& getId() const { return exerciseId; }
    const std::string& getTitle() const { return title; }
    const std::string& getDescription() const { return description; }
    const std::string& getInstructions() const { return instructions; }
    ExerciseType getType() const { return type; }
    DifficultyLevel getDifficulty() const { return difficulty; }
    const std::string& getStarterCode() const { return starterCode; }
    const std::vector<TestCase>& getTestCases() const { return testCases; }
    bool isCompleted() const { return completed; }
    double getScore() const { return score; }
    int getRemainingAttempts() const { return maxAttempts - currentAttempts; }
    
    // Exercise execution
    void displayExercise() const;
    bool submitSolution(const std::string& code);
    void provideFeedback(const std::string& feedback) const;
    void reset();
    
private:
    bool validateSolution(const std::string& code);
    double calculateScore(const std::vector<bool>& testResults);
};

class ExerciseManager {
private:
    std::vector<std::unique_ptr<Exercise>> exercises;
    std::string currentExerciseId;

public:
    void addExercise(std::unique_ptr<Exercise> exercise);
    Exercise* getExercise(const std::string& id);
    std::vector<Exercise*> getExercisesByDifficulty(DifficultyLevel difficulty);
    std::vector<Exercise*> getExercisesByType(ExerciseType type);
    
    bool startExercise(const std::string& id);
    void completeCurrentExercise();
    Exercise* getCurrentExercise();
    
    // Progress tracking
    int getCompletedCount() const;
    double getAverageScore() const;
    std::vector<std::string> getCompletedExerciseIds() const;
};
