#include "ProgressTracker.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

ProgressTracker::ProgressTracker(const std::string& studentId) 
    : studentId(studentId) {
    metrics.enrollmentDate = std::chrono::system_clock::now();
    metrics.lastLoginDate = std::chrono::system_clock::now();
}

void ProgressTracker::startModule(const std::string& moduleId, const std::string& moduleName) {
    if (moduleProgress.find(moduleId) == moduleProgress.end()) {
        moduleProgress[moduleId] = ModuleProgress(moduleId, moduleName);
        std::cout << "Started module: " << moduleName << std::endl;
    }
}

void ProgressTracker::completeLesson(const std::string& moduleId, const std::string& lessonId) {
    auto it = moduleProgress.find(moduleId);
    if (it != moduleProgress.end()) {
        auto& lessons = it->second.completedLessons;
        if (std::find(lessons.begin(), lessons.end(), lessonId) == lessons.end()) {
            lessons.push_back(lessonId);
            it->second.lastActivity = std::chrono::system_clock::now();
            metrics.totalLessonsCompleted++;
            
            // Update completion percentage (simplified calculation)
            // In real implementation, this would be based on total lessons in module
            it->second.completionPercentage = std::min(100.0f, 
                static_cast<float>(lessons.size()) * 10.0f);
            
            std::cout << "Completed lesson: " << lessonId << " in module: " << moduleId << std::endl;
        }
    }
}

void ProgressTracker::completeExercise(const std::string& moduleId, const std::string& exerciseId, double score) {
    auto it = moduleProgress.find(moduleId);
    if (it != moduleProgress.end()) {
        auto& exercises = it->second.completedExercises;
        if (std::find(exercises.begin(), exercises.end(), exerciseId) == exercises.end()) {
            exercises.push_back(exerciseId);
            it->second.lastActivity = std::chrono::system_clock::now();
            metrics.totalExercisesCompleted++;
            
            // Update average score
            double totalScore = metrics.averageExerciseScore * (metrics.totalExercisesCompleted - 1) + score;
            metrics.averageExerciseScore = totalScore / metrics.totalExercisesCompleted;
            
            std::cout << "Completed exercise: " << exerciseId << " with score: " << score << std::endl;
        }
    }
}

void ProgressTracker::completeModule(const std::string& moduleId) {
    auto it = moduleProgress.find(moduleId);
    if (it != moduleProgress.end()) {
        it->second.isCompleted = true;
        it->second.completionPercentage = 100.0f;
        metrics.totalProjectsCompleted++; // Assuming each module has a project
        
        std::cout << "✓ Module completed: " << it->second.moduleName << std::endl;
    }
}

void ProgressTracker::updateConceptMastery(const std::string& conceptId, double performanceScore) {
    auto it = conceptMastery.find(conceptId);
    if (it == conceptMastery.end()) {
        conceptMastery[conceptId] = ConceptMastery(conceptId);
        it = conceptMastery.find(conceptId);
    }
    
    ConceptMastery& mastery = it->second;
    mastery.practiceCount++;
    mastery.lastPracticed = std::chrono::system_clock::now();
    
    // Update mastery level using weighted average
    double weight = 0.3; // Weight for new performance
    mastery.masteryLevel = (1.0 - weight) * mastery.masteryLevel + weight * (performanceScore / 100.0);
    
    std::cout << "Updated mastery for concept " << conceptId << ": " 
              << std::fixed << std::setprecision(2) << mastery.masteryLevel * 100 << "%" << std::endl;
}

double ProgressTracker::getConceptMastery(const std::string& conceptId) const {
    auto it = conceptMastery.find(conceptId);
    return (it != conceptMastery.end()) ? it->second.masteryLevel : 0.0;
}

std::vector<std::string> ProgressTracker::getWeakConcepts(double threshold) const {
    std::vector<std::string> weakConcepts;
    for (const auto& pair : conceptMastery) {
        if (pair.second.masteryLevel < threshold) {
            weakConcepts.push_back(pair.first);
        }
    }
    return weakConcepts;
}

float ProgressTracker::getModuleProgress(const std::string& moduleId) const {
    auto it = moduleProgress.find(moduleId);
    return (it != moduleProgress.end()) ? it->second.completionPercentage : 0.0f;
}

float ProgressTracker::getOverallProgress() const {
    if (moduleProgress.empty()) return 0.0f;
    
    float totalProgress = 0.0f;
    for (const auto& pair : moduleProgress) {
        totalProgress += pair.second.completionPercentage;
    }
    
    return totalProgress / moduleProgress.size();
}

bool ProgressTracker::isModuleCompleted(const std::string& moduleId) const {
    auto it = moduleProgress.find(moduleId);
    return (it != moduleProgress.end()) ? it->second.isCompleted : false;
}

std::vector<std::string> ProgressTracker::getCompletedModules() const {
    std::vector<std::string> completed;
    for (const auto& pair : moduleProgress) {
        if (pair.second.isCompleted) {
            completed.push_back(pair.first);
        }
    }
    return completed;
}

std::vector<std::string> ProgressTracker::getAvailableModules(
    const std::map<std::string, std::vector<std::string>>& prerequisites) const {
    
    std::vector<std::string> available;
    std::vector<std::string> completed = getCompletedModules();
    
    for (const auto& pair : prerequisites) {
        const std::string& moduleId = pair.first;
        const std::vector<std::string>& prereqs = pair.second;
        
        // Check if all prerequisites are completed
        bool allPrereqsMet = true;
        for (const std::string& prereq : prereqs) {
            if (std::find(completed.begin(), completed.end(), prereq) == completed.end()) {
                allPrereqsMet = false;
                break;
            }
        }
        
        if (allPrereqsMet && !isModuleCompleted(moduleId)) {
            available.push_back(moduleId);
        }
    }
    
    return available;
}

void ProgressTracker::startSession() {
    sessionStartTime = std::chrono::system_clock::now();
    metrics.lastLoginDate = sessionStartTime;
}

void ProgressTracker::endSession() {
    if (sessionStartTime.time_since_epoch().count() > 0) {
        auto sessionDuration = std::chrono::system_clock::now() - sessionStartTime;
        metrics.totalStudyTime += sessionDuration;
        sessionStartTime = std::chrono::system_clock::time_point{}; // Reset
    }
}

std::chrono::duration<double> ProgressTracker::getCurrentSessionTime() const {
    if (sessionStartTime.time_since_epoch().count() > 0) {
        return std::chrono::system_clock::now() - sessionStartTime;
    }
    return std::chrono::duration<double>::zero();
}

void ProgressTracker::updateMetrics() {
    calculateOverallMetrics();
}

std::string ProgressTracker::generateProgressReport() const {
    std::ostringstream report;
    
    report << "=== Progress Report for Student: " << studentId << " ===" << std::endl;
    report << "Overall Progress: " << std::fixed << std::setprecision(1) 
           << getOverallProgress() << "%" << std::endl;
    
    report << "\nModule Progress:" << std::endl;
    for (const auto& pair : moduleProgress) {
        const ModuleProgress& progress = pair.second;
        report << "- " << progress.moduleName << ": " 
               << std::fixed << std::setprecision(1) << progress.completionPercentage << "%";
        if (progress.isCompleted) {
            report << " ✓";
        }
        report << std::endl;
    }
    
    report << "\nLearning Metrics:" << std::endl;
    report << "- Lessons Completed: " << metrics.totalLessonsCompleted << std::endl;
    report << "- Exercises Completed: " << metrics.totalExercisesCompleted << std::endl;
    report << "- Projects Completed: " << metrics.totalProjectsCompleted << std::endl;
    report << "- Average Exercise Score: " << std::fixed << std::setprecision(1) 
           << metrics.averageExerciseScore << "%" << std::endl;
    report << "- Total Study Time: " << formatDuration(metrics.totalStudyTime) << std::endl;
    
    // Weak concepts
    auto weakConcepts = getWeakConcepts();
    if (!weakConcepts.empty()) {
        report << "\nConcepts Needing Review:" << std::endl;
        for (const std::string& concept : weakConcepts) {
            report << "- " << concept << " (Mastery: " 
                   << std::fixed << std::setprecision(1) 
                   << getConceptMastery(concept) * 100 << "%)" << std::endl;
        }
    }
    
    return report.str();
}

bool ProgressTracker::saveProgress(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    // Simple JSON-like format for demonstration
    file << "{\n";
    file << "  \"studentId\": \"" << studentId << "\",\n";
    file << "  \"overallProgress\": " << getOverallProgress() << ",\n";
    file << "  \"totalLessons\": " << metrics.totalLessonsCompleted << ",\n";
    file << "  \"totalExercises\": " << metrics.totalExercisesCompleted << ",\n";
    file << "  \"averageScore\": " << metrics.averageExerciseScore << "\n";
    file << "}\n";
    
    return true;
}

bool ProgressTracker::loadProgress(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    // Simple loading implementation
    // In a real system, this would parse JSON or use a proper serialization format
    std::string line;
    while (std::getline(file, line)) {
        // Basic parsing logic would go here
    }
    
    return true;
}

void ProgressTracker::calculateOverallMetrics() {
    // Update any calculated metrics
    // This is called periodically to ensure metrics are current
}

std::string ProgressTracker::formatDuration(const std::chrono::duration<double>& duration) const {
    auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration - hours);
    
    std::ostringstream oss;
    oss << hours.count() << "h " << minutes.count() << "m";
    return oss.str();
}
