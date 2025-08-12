#include "Lesson.h"
#include <iostream>
#include <algorithm>

// Concept implementation
Concept::Concept(const std::string& id, const std::string& title, 
                const std::string& content, ConceptType type, DifficultyLevel difficulty)
    : id(id), title(title), content(content), type(type), difficulty(difficulty) {}

void Concept::display() const {
    std::cout << "\n=== " << title << " ===" << std::endl;
    std::cout << content << std::endl;
    
    std::string typeStr;
    switch (type) {
        case ConceptType::THEORY: typeStr = "Theory"; break;
        case ConceptType::EXAMPLE: typeStr = "Example"; break;
        case ConceptType::EXERCISE: typeStr = "Exercise"; break;
        case ConceptType::PROJECT: typeStr = "Project"; break;
    }
    
    std::string difficultyStr;
    switch (difficulty) {
        case DifficultyLevel::BEGINNER: difficultyStr = "Beginner"; break;
        case DifficultyLevel::INTERMEDIATE: difficultyStr = "Intermediate"; break;
        case DifficultyLevel::ADVANCED: difficultyStr = "Advanced"; break;
    }
    
    std::cout << "Type: " << typeStr << " | Difficulty: " << difficultyStr << std::endl;
}

bool Concept::isCompleted() const {
    // For now, concepts are considered completed when displayed
    // This can be enhanced with more sophisticated tracking
    return true;
}

// CodeExample implementation
CodeExample::CodeExample(const std::string& code, const std::string& explanation, 
                        const std::string& expectedOutput)
    : code(code), explanation(explanation), expectedOutput(expectedOutput) {}

void CodeExample::demonstrate() const {
    std::cout << "\n--- Code Example ---" << std::endl;
    std::cout << explanation << std::endl;
    std::cout << "\nCode:" << std::endl;
    std::cout << code << std::endl;
    
    if (!expectedOutput.empty()) {
        std::cout << "\nExpected Output:" << std::endl;
        std::cout << expectedOutput << std::endl;
    }
}

// Lesson implementation
Lesson::Lesson(const std::string& id, const std::string& title, const std::string& description)
    : lessonId(id), title(title), description(description), completed(false) {}

void Lesson::addConcept(std::unique_ptr<Concept> concept) {
    concepts.push_back(std::move(concept));
}

void Lesson::addExample(std::unique_ptr<CodeExample> example) {
    examples.push_back(std::move(example));
}

void Lesson::addPrerequisite(const std::string& prerequisite) {
    prerequisites.push_back(prerequisite);
}

void Lesson::startLesson() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "Starting Lesson: " << title << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << description << std::endl;
    
    if (!prerequisites.empty()) {
        std::cout << "\nPrerequisites:" << std::endl;
        for (const auto& prereq : prerequisites) {
            std::cout << "- " << prereq << std::endl;
        }
    }
}

void Lesson::completeLesson() {
    completed = true;
    std::cout << "\n✓ Lesson completed: " << title << std::endl;
}

bool Lesson::checkPrerequisites(const std::vector<std::string>& completedLessons) const {
    for (const auto& prereq : prerequisites) {
        if (std::find(completedLessons.begin(), completedLessons.end(), prereq) == completedLessons.end()) {
            return false;
        }
    }
    return true;
}

void Lesson::displayContent() const {
    startLesson();
    
    // Display all concepts
    for (const auto& concept : concepts) {
        concept->display();
    }
    
    // Display all examples
    for (const auto& example : examples) {
        example->demonstrate();
    }
    
    std::cout << "\n" << std::string(50, '-') << std::endl;
    std::cout << "End of lesson content" << std::endl;
}
