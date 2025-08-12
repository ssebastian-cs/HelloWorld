#pragma once
#include <string>
#include <vector>
#include <memory>

enum class DifficultyLevel {
    BEGINNER,
    INTERMEDIATE,
    ADVANCED
};

enum class ConceptType {
    THEORY,
    EXAMPLE,
    EXERCISE,
    PROJECT
};

class Concept {
private:
    std::string id;
    std::string title;
    std::string content;
    ConceptType type;
    DifficultyLevel difficulty;

public:
    Concept(const std::string& id, const std::string& title, 
            const std::string& content, ConceptType type, DifficultyLevel difficulty);
    
    // Getters
    const std::string& getId() const { return id; }
    const std::string& getTitle() const { return title; }
    const std::string& getContent() const { return content; }
    ConceptType getType() const { return type; }
    DifficultyLevel getDifficulty() const { return difficulty; }
    
    // Display methods
    void display() const;
    bool isCompleted() const;
};

class CodeExample {
private:
    std::string code;
    std::string explanation;
    std::string expectedOutput;

public:
    CodeExample(const std::string& code, const std::string& explanation, 
                const std::string& expectedOutput = "");
    
    const std::string& getCode() const { return code; }
    const std::string& getExplanation() const { return explanation; }
    const std::string& getExpectedOutput() const { return expectedOutput; }
    
    void demonstrate() const;
};

class Lesson {
private:
    std::string lessonId;
    std::string title;
    std::string description;
    std::vector<std::string> prerequisites;
    std::vector<std::unique_ptr<Concept>> concepts;
    std::vector<std::unique_ptr<CodeExample>> examples;
    bool completed;

public:
    Lesson(const std::string& id, const std::string& title, const std::string& description);
    
    // Content management
    void addConcept(std::unique_ptr<Concept> concept);
    void addExample(std::unique_ptr<CodeExample> example);
    void addPrerequisite(const std::string& prerequisite);
    
    // Getters
    const std::string& getId() const { return lessonId; }
    const std::string& getTitle() const { return title; }
    const std::string& getDescription() const { return description; }
    const std::vector<std::string>& getPrerequisites() const { return prerequisites; }
    bool isCompleted() const { return completed; }
    
    // Learning methods
    void startLesson();
    void completeLesson();
    bool checkPrerequisites(const std::vector<std::string>& completedLessons) const;
    void displayContent() const;
};
