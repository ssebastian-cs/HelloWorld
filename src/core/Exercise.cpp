#include "Exercise.h"
#include <iostream>
#include <algorithm>
#include <numeric>

// TestCase implementation
TestCase::TestCase(const std::string& input, const std::string& expectedOutput, 
                  const std::string& description)
    : input(input), expectedOutput(expectedOutput), description(description) {}

// Exercise implementation
Exercise::Exercise(const std::string& id, const std::string& title, 
                  const std::string& description, ExerciseType type, 
                  DifficultyLevel difficulty)
    : exerciseId(id), title(title), description(description), type(type), 
      difficulty(difficulty), maxAttempts(3), currentAttempts(0), 
      completed(false), score(0.0) {}

void Exercise::setInstructions(const std::string& instructions) {
    this->instructions = instructions;
}

void Exercise::setStarterCode(const std::string& code) {
    this->starterCode = code;
}

void Exercise::setSolutionCode(const std::string& code) {
    this->solutionCode = code;
}

void Exercise::addTestCase(const TestCase& testCase) {
    testCases.push_back(testCase);
}

void Exercise::setMaxAttempts(int attempts) {
    this->maxAttempts = attempts;
}

void Exercise::displayExercise() const {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "Exercise: " << title << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    std::cout << "\nDescription: " << description << std::endl;
    std::cout << "\nInstructions: " << instructions << std::endl;
    
    std::string typeStr;
    switch (type) {
        case ExerciseType::CODING: typeStr = "Coding"; break;
        case ExerciseType::MULTIPLE_CHOICE: typeStr = "Multiple Choice"; break;
        case ExerciseType::FILL_IN_BLANK: typeStr = "Fill in the Blank"; break;
        case ExerciseType::DEBUG_CODE: typeStr = "Debug Code"; break;
    }
    
    std::string difficultyStr;
    switch (difficulty) {
        case DifficultyLevel::BEGINNER: difficultyStr = "Beginner"; break;
        case DifficultyLevel::INTERMEDIATE: difficultyStr = "Intermediate"; break;
        case DifficultyLevel::ADVANCED: difficultyStr = "Advanced"; break;
    }
    
    std::cout << "\nType: " << typeStr << " | Difficulty: " << difficultyStr << std::endl;
    std::cout << "Attempts remaining: " << getRemainingAttempts() << std::endl;
    
    if (!starterCode.empty()) {
        std::cout << "\nStarter Code:" << std::endl;
        std::cout << starterCode << std::endl;
    }
    
    if (!testCases.empty()) {
        std::cout << "\nTest Cases:" << std::endl;
        for (size_t i = 0; i < testCases.size(); ++i) {
            const auto& testCase = testCases[i];
            std::cout << "Test " << (i + 1) << ": ";
            if (!testCase.description.empty()) {
                std::cout << testCase.description;
            } else {
                std::cout << "Input: '" << testCase.input << "' -> Expected: '" << testCase.expectedOutput << "'";
            }
            std::cout << std::endl;
        }
    }
}

bool Exercise::submitSolution(const std::string& code) {
    if (currentAttempts >= maxAttempts) {
        std::cout << "Maximum attempts exceeded for this exercise." << std::endl;
        return false;
    }
    
    currentAttempts++;
    
    if (validateSolution(code)) {
        completed = true;
        std::cout << "✓ Exercise completed successfully!" << std::endl;
        std::cout << "Score: " << score << "/100" << std::endl;
        return true;
    } else {
        std::cout << "✗ Solution incorrect. Attempts remaining: " << getRemainingAttempts() << std::endl;
        return false;
    }
}

void Exercise::provideFeedback(const std::string& feedback) const {
    std::cout << "\nFeedback: " << feedback << std::endl;
}

void Exercise::reset() {
    currentAttempts = 0;
    completed = false;
    score = 0.0;
}

bool Exercise::validateSolution(const std::string& code) {
    // Basic validation - in a real implementation, this would compile and test the code
    if (code.empty()) {
        score = 0.0;
        return false;
    }
    
    // Simulate test case validation
    std::vector<bool> testResults;
    for (const auto& testCase : testCases) {
        // For now, just simulate passing tests
        // In real implementation, this would compile and run the code
        testResults.push_back(true);
    }
    
    score = calculateScore(testResults);
    return score >= 70.0; // Pass threshold
}

double Exercise::calculateScore(const std::vector<bool>& testResults) {
    if (testResults.empty()) return 0.0;
    
    int passedTests = std::count(testResults.begin(), testResults.end(), true);
    double baseScore = (static_cast<double>(passedTests) / testResults.size()) * 100.0;
    
    // Apply attempt penalty
    double attemptPenalty = (currentAttempts - 1) * 10.0;
    return std::max(0.0, baseScore - attemptPenalty);
}

// ExerciseManager implementation
void ExerciseManager::addExercise(std::unique_ptr<Exercise> exercise) {
    exercises.push_back(std::move(exercise));
}

Exercise* ExerciseManager::getExercise(const std::string& id) {
    auto it = std::find_if(exercises.begin(), exercises.end(),
        [&id](const std::unique_ptr<Exercise>& ex) {
            return ex->getId() == id;
        });
    
    return (it != exercises.end()) ? it->get() : nullptr;
}

std::vector<Exercise*> ExerciseManager::getExercisesByDifficulty(DifficultyLevel difficulty) {
    std::vector<Exercise*> result;
    for (const auto& exercise : exercises) {
        if (exercise->getDifficulty() == difficulty) {
            result.push_back(exercise.get());
        }
    }
    return result;
}

std::vector<Exercise*> ExerciseManager::getExercisesByType(ExerciseType type) {
    std::vector<Exercise*> result;
    for (const auto& exercise : exercises) {
        if (exercise->getType() == type) {
            result.push_back(exercise.get());
        }
    }
    return result;
}

bool ExerciseManager::startExercise(const std::string& id) {
    Exercise* exercise = getExercise(id);
    if (exercise) {
        currentExerciseId = id;
        exercise->displayExercise();
        return true;
    }
    return false;
}

void ExerciseManager::completeCurrentExercise() {
    if (!currentExerciseId.empty()) {
        Exercise* exercise = getExercise(currentExerciseId);
        if (exercise && exercise->isCompleted()) {
            std::cout << "Exercise '" << exercise->getTitle() << "' marked as completed." << std::endl;
        }
        currentExerciseId.clear();
    }
}

Exercise* ExerciseManager::getCurrentExercise() {
    return currentExerciseId.empty() ? nullptr : getExercise(currentExerciseId);
}

int ExerciseManager::getCompletedCount() const {
    return std::count_if(exercises.begin(), exercises.end(),
        [](const std::unique_ptr<Exercise>& ex) {
            return ex->isCompleted();
        });
}

double ExerciseManager::getAverageScore() const {
    std::vector<double> scores;
    for (const auto& exercise : exercises) {
        if (exercise->isCompleted()) {
            scores.push_back(exercise->getScore());
        }
    }
    
    if (scores.empty()) return 0.0;
    
    return std::accumulate(scores.begin(), scores.end(), 0.0) / scores.size();
}

std::vector<std::string> ExerciseManager::getCompletedExerciseIds() const {
    std::vector<std::string> result;
    for (const auto& exercise : exercises) {
        if (exercise->isCompleted()) {
            result.push_back(exercise->getId());
        }
    }
    return result;
}
