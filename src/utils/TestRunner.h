#pragma once
#include "CodeCompiler.h"
#include "../core/Exercise.h"
#include <string>
#include <vector>
#include <functional>

enum class TestStatus {
    PASSED,
    FAILED,
    ERROR,
    TIMEOUT
};

struct TestResult {
    std::string testName;
    TestStatus status;
    std::string input;
    std::string expectedOutput;
    std::string actualOutput;
    std::string errorMessage;
    double executionTime;
    
    TestResult(const std::string& name) 
        : testName(name), status(TestStatus::ERROR), executionTime(0.0) {}
};

struct TestSuite {
    std::string suiteName;
    std::vector<TestResult> results;
    double totalTime;
    int passedCount;
    int failedCount;
    int errorCount;
    
    TestSuite(const std::string& name) 
        : suiteName(name), totalTime(0.0), passedCount(0), 
          failedCount(0), errorCount(0) {}
};

class TestRunner {
private:
    std::unique_ptr<CodeCompiler> compiler;
    double timeoutSeconds;
    bool verboseOutput;

public:
    TestRunner();
    ~TestRunner();
    
    // Configuration
    void setCompiler(std::unique_ptr<CodeCompiler> compiler);
    void setTimeout(double seconds);
    void setVerboseOutput(bool verbose);
    
    // Test execution
    TestResult runSingleTest(const std::string& sourceCode, 
                            const std::string& testName,
                            const std::string& input, 
                            const std::string& expectedOutput);
    
    TestSuite runTestSuite(const std::string& sourceCode, 
                          const std::vector<TestCase>& testCases,
                          const std::string& suiteName = "Test Suite");
    
    TestSuite runExerciseTests(const std::string& sourceCode, 
                              const Exercise& exercise);
    
    // Validation methods
    bool validateSyntax(const std::string& sourceCode);
    std::vector<std::string> checkCommonMistakes(const std::string& sourceCode);
    bool checkRequiredFeatures(const std::string& sourceCode, 
                              const std::vector<std::string>& requiredFeatures);
    
    // Reporting
    void printTestResult(const TestResult& result) const;
    void printTestSuite(const TestSuite& suite) const;
    std::string generateReport(const TestSuite& suite) const;
    std::string generateDetailedReport(const TestSuite& suite) const;
    
    // Utility methods
    bool isOutputMatch(const std::string& expected, const std::string& actual) const;
    std::string normalizeOutput(const std::string& output) const;
    
private:
    TestStatus determineTestStatus(const ExecutionResult& result, 
                                  const std::string& expectedOutput) const;
    void updateSuiteStatistics(TestSuite& suite) const;
    std::vector<std::string> splitLines(const std::string& text) const;
    std::string trim(const std::string& str) const;
};
