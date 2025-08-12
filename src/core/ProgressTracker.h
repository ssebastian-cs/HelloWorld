#pragma once
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <memory>

struct ConceptMastery {
    std::string conceptId;
    double masteryLevel; // 0.0 to 1.0
    int practiceCount;
    std::chrono::system_clock::time_point lastPracticed;
    
    ConceptMastery(const std::string& id) 
        : conceptId(id), masteryLevel(0.0), practiceCount(0) {}
};

struct ModuleProgress {
    std::string moduleId;
    std::string moduleName;
    float completionPercentage;
    std::vector<std::string> completedLessons;
    std::vector<std::string> completedExercises;
    std::chrono::system_clock::time_point startDate;
    std::chrono::system_clock::time_point lastActivity;
    bool isCompleted;
    
    ModuleProgress(const std::string& id, const std::string& name)
        : moduleId(id), moduleName(name), completionPercentage(0.0f), 
          isCompleted(false), startDate(std::chrono::system_clock::now()) {}
};

struct LearningMetrics {
    int totalLessonsCompleted;
    int totalExercisesCompleted;
    int totalProjectsCompleted;
    double averageExerciseScore;
    std::chrono::duration<double> totalStudyTime;
    std::chrono::system_clock::time_point enrollmentDate;
    std::chrono::system_clock::time_point lastLoginDate;
    
    LearningMetrics() 
        : totalLessonsCompleted(0), totalExercisesCompleted(0), 
          totalProjectsCompleted(0), averageExerciseScore(0.0),
          totalStudyTime(std::chrono::duration<double>::zero()),
          enrollmentDate(std::chrono::system_clock::now()) {}
};

class ProgressTracker {
private:
    std::string studentId;
    std::map<std::string, ModuleProgress> moduleProgress;
    std::map<std::string, ConceptMastery> conceptMastery;
    LearningMetrics metrics;
    std::chrono::system_clock::time_point sessionStartTime;

public:
    ProgressTracker(const std::string& studentId);
    
    // Module progress tracking
    void startModule(const std::string& moduleId, const std::string& moduleName);
    void completeLesson(const std::string& moduleId, const std::string& lessonId);
    void completeExercise(const std::string& moduleId, const std::string& exerciseId, double score);
    void completeModule(const std::string& moduleId);
    
    // Concept mastery tracking
    void updateConceptMastery(const std::string& conceptId, double performanceScore);
    double getConceptMastery(const std::string& conceptId) const;
    std::vector<std::string> getWeakConcepts(double threshold = 0.7) const;
    
    // Progress queries
    float getModuleProgress(const std::string& moduleId) const;
    float getOverallProgress() const;
    bool isModuleCompleted(const std::string& moduleId) const;
    std::vector<std::string> getCompletedModules() const;
    std::vector<std::string> getAvailableModules(const std::map<std::string, std::vector<std::string>>& prerequisites) const;
    
    // Time tracking
    void startSession();
    void endSession();
    std::chrono::duration<double> getCurrentSessionTime() const;
    
    // Metrics and analytics
    const LearningMetrics& getMetrics() const { return metrics; }
    void updateMetrics();
    std::string generateProgressReport() const;
    
    // Persistence
    bool saveProgress(const std::string& filename) const;
    bool loadProgress(const std::string& filename);
    
    // Getters
    const std::string& getStudentId() const { return studentId; }
    const std::map<std::string, ModuleProgress>& getModuleProgress() const { return moduleProgress; }
    
private:
    void calculateOverallMetrics();
    std::string formatDuration(const std::chrono::duration<double>& duration) const;
};
