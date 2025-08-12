#include "TestRunner.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

TestRunner::TestRunner() : timeoutSeconds(10.0), verboseOutput(false) {
    compiler = std::make_unique<CodeCompiler>();
}

TestRunner::~TestRunner() = default;

void TestRunner::setCompiler(std::unique_ptr<CodeCompiler> compiler) {
    this->compiler = std::move(compiler);
}

void TestRunner::setTimeout(double seconds) {
    this->timeoutSeconds = seconds;
}

void TestRunner::setVerboseOutput(bool verbose) {
    this->verboseOutput = verbose;
}

TestResult TestRunner::runSingleTest(const std::string& sourceCode, 
                                    const std::string& testName,
                                    const std::string& input, 
                                    const std::string& expectedOutput) {
    TestResult result(testName);
    result.input = input;
    result.expectedOutput = expectedOutput;
    
    if (!compiler) {
        result.status = TestStatus::ERROR;
        result.errorMessage = "No compiler available";
        return result;
    }
    
    // Execute the code with the given input
    ExecutionResult execResult = compiler->executeCode(sourceCode, input);
    result.executionTime = execResult.executionTime;
    
    if (!execResult.success) {
        result.status = TestStatus::ERROR;
        result.errorMessage = execResult.errorOutput;
        result.actualOutput = execResult.output;
        return result;
    }
    
    result.actualOutput = execResult.output;
    result.status = determineTestStatus(execResult, expectedOutput);
    
    if (verboseOutput) {
        printTestResult(result);
    }
    
    return result;
}

TestSuite TestRunner::runTestSuite(const std::string& sourceCode, 
                                  const std::vector<TestCase>& testCases,
                                  const std::string& suiteName) {
    TestSuite suite(suiteName);
    
    if (verboseOutput) {
        std::cout << "\n=== Running Test Suite: " << suiteName << " ===" << std::endl;
    }
    
    // First, validate syntax
    if (!validateSyntax(sourceCode)) {
        // Create error results for all test cases
        for (size_t i = 0; i < testCases.size(); ++i) {
            TestResult result("Test " + std::to_string(i + 1));
            result.status = TestStatus::ERROR;
            result.errorMessage = "Syntax validation failed";
            suite.results.push_back(result);
        }
        updateSuiteStatistics(suite);
        return suite;
    }
    
    // Run each test case
    for (size_t i = 0; i < testCases.size(); ++i) {
        const TestCase& testCase = testCases[i];
        std::string testName = testCase.description.empty() ? 
            ("Test " + std::to_string(i + 1)) : testCase.description;
        
        TestResult result = runSingleTest(sourceCode, testName, 
                                         testCase.input, testCase.expectedOutput);
        suite.results.push_back(result);
    }
    
    updateSuiteStatistics(suite);
    
    if (verboseOutput) {
        printTestSuite(suite);
    }
    
    return suite;
}

TestSuite TestRunner::runExerciseTests(const std::string& sourceCode, 
                                      const Exercise& exercise) {
    return runTestSuite(sourceCode, exercise.getTestCases(), 
                       "Exercise: " + exercise.getTitle());
}

bool TestRunner::validateSyntax(const std::string& sourceCode) {
    if (!compiler) {
        return false;
    }
    
    CompilationResult result = compiler->compileCode(sourceCode, "syntax_check.cpp");
    return result.success;
}

std::vector<std::string> TestRunner::checkCommonMistakes(const std::string& sourceCode) {
    std::vector<std::string> mistakes;
    
    // Check for common C++ mistakes
    if (sourceCode.find("#include <iostream>") == std::string::npos && 
        sourceCode.find("cout") != std::string::npos) {
        mistakes.push_back("Missing #include <iostream> for cout usage");
    }
    
    if (sourceCode.find("using namespace std;") == std::string::npos && 
        sourceCode.find("std::") == std::string::npos &&
        (sourceCode.find("cout") != std::string::npos || sourceCode.find("cin") != std::string::npos)) {
        mistakes.push_back("Missing 'std::' prefix or 'using namespace std;'");
    }
    
    if (sourceCode.find("int main") == std::string::npos) {
        mistakes.push_back("Missing main function");
    }
    
    // Check for missing semicolons (basic check)
    std::istringstream iss(sourceCode);
    std::string line;
    int lineNumber = 0;
    while (std::getline(iss, line)) {
        lineNumber++;
        // Skip comments and preprocessor directives
        if (line.find("//") == 0 || line.find("#") == 0 || line.empty()) {
            continue;
        }
        
        // Check for statements that should end with semicolon
        if ((line.find("cout") != std::string::npos || 
             line.find("cin") != std::string::npos ||
             line.find("=") != std::string::npos) &&
            line.find(";") == std::string::npos &&
            line.find("{") == std::string::npos &&
            line.find("}") == std::string::npos) {
            mistakes.push_back("Line " + std::to_string(lineNumber) + 
                             " might be missing a semicolon");
        }
    }
    
    return mistakes;
}

bool TestRunner::checkRequiredFeatures(const std::string& sourceCode, 
                                       const std::vector<std::string>& requiredFeatures) {
    for (const std::string& feature : requiredFeatures) {
        if (sourceCode.find(feature) == std::string::npos) {
            return false;
        }
    }
    return true;
}

void TestRunner::printTestResult(const TestResult& result) const {
    std::cout << "\n--- " << result.testName << " ---" << std::endl;
    
    switch (result.status) {
        case TestStatus::PASSED:
            std::cout << "✓ PASSED";
            break;
        case TestStatus::FAILED:
            std::cout << "✗ FAILED";
            break;
        case TestStatus::ERROR:
            std::cout << "⚠ ERROR";
            break;
        case TestStatus::TIMEOUT:
            std::cout << "⏱ TIMEOUT";
            break;
    }
    
    std::cout << " (" << std::fixed << std::setprecision(3) 
              << result.executionTime << "s)" << std::endl;
    
    if (!result.input.empty()) {
        std::cout << "Input: " << result.input << std::endl;
    }
    
    if (result.status == TestStatus::FAILED) {
        std::cout << "Expected: " << result.expectedOutput << std::endl;
        std::cout << "Actual:   " << result.actualOutput << std::endl;
    }
    
    if (!result.errorMessage.empty()) {
        std::cout << "Error: " << result.errorMessage << std::endl;
    }
}

void TestRunner::printTestSuite(const TestSuite& suite) const {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "Test Suite Results: " << suite.suiteName << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    std::cout << "Passed: " << suite.passedCount << std::endl;
    std::cout << "Failed: " << suite.failedCount << std::endl;
    std::cout << "Errors: " << suite.errorCount << std::endl;
    std::cout << "Total:  " << suite.results.size() << std::endl;
    std::cout << "Time:   " << std::fixed << std::setprecision(3) 
              << suite.totalTime << "s" << std::endl;
    
    double successRate = suite.results.empty() ? 0.0 : 
        (static_cast<double>(suite.passedCount) / suite.results.size()) * 100.0;
    std::cout << "Success Rate: " << std::fixed << std::setprecision(1) 
              << successRate << "%" << std::endl;
}

std::string TestRunner::generateReport(const TestSuite& suite) const {
    std::ostringstream report;
    
    report << "Test Suite: " << suite.suiteName << "\n";
    report << "Results: " << suite.passedCount << " passed, " 
           << suite.failedCount << " failed, " << suite.errorCount << " errors\n";
    report << "Total Time: " << std::fixed << std::setprecision(3) 
           << suite.totalTime << "s\n";
    
    double successRate = suite.results.empty() ? 0.0 : 
        (static_cast<double>(suite.passedCount) / suite.results.size()) * 100.0;
    report << "Success Rate: " << std::fixed << std::setprecision(1) 
           << successRate << "%\n";
    
    return report.str();
}

std::string TestRunner::generateDetailedReport(const TestSuite& suite) const {
    std::ostringstream report;
    
    report << generateReport(suite);
    report << "\nDetailed Results:\n";
    
    for (const TestResult& result : suite.results) {
        report << "- " << result.testName << ": ";
        
        switch (result.status) {
            case TestStatus::PASSED: report << "PASSED"; break;
            case TestStatus::FAILED: report << "FAILED"; break;
            case TestStatus::ERROR: report << "ERROR"; break;
            case TestStatus::TIMEOUT: report << "TIMEOUT"; break;
        }
        
        report << " (" << std::fixed << std::setprecision(3) 
               << result.executionTime << "s)\n";
        
        if (result.status == TestStatus::FAILED) {
            report << "  Expected: " << result.expectedOutput << "\n";
            report << "  Actual:   " << result.actualOutput << "\n";
        }
        
        if (!result.errorMessage.empty()) {
            report << "  Error: " << result.errorMessage << "\n";
        }
    }
    
    return report.str();
}

bool TestRunner::isOutputMatch(const std::string& expected, const std::string& actual) const {
    std::string normalizedExpected = normalizeOutput(expected);
    std::string normalizedActual = normalizeOutput(actual);
    
    return normalizedExpected == normalizedActual;
}

std::string TestRunner::normalizeOutput(const std::string& output) const {
    std::string normalized = output;
    
    // Remove trailing whitespace
    normalized.erase(normalized.find_last_not_of(" \n\r\t") + 1);
    
    // Convert to lowercase for case-insensitive comparison (optional)
    // std::transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
    
    return normalized;
}

TestStatus TestRunner::determineTestStatus(const ExecutionResult& result, 
                                          const std::string& expectedOutput) const {
    if (!result.success) {
        return TestStatus::ERROR;
    }
    
    if (result.executionTime > timeoutSeconds) {
        return TestStatus::TIMEOUT;
    }
    
    return isOutputMatch(expectedOutput, result.output) ? 
        TestStatus::PASSED : TestStatus::FAILED;
}

void TestRunner::updateSuiteStatistics(TestSuite& suite) const {
    suite.passedCount = 0;
    suite.failedCount = 0;
    suite.errorCount = 0;
    suite.totalTime = 0.0;
    
    for (const TestResult& result : suite.results) {
        switch (result.status) {
            case TestStatus::PASSED:
                suite.passedCount++;
                break;
            case TestStatus::FAILED:
                suite.failedCount++;
                break;
            case TestStatus::ERROR:
            case TestStatus::TIMEOUT:
                suite.errorCount++;
                break;
        }
        
        suite.totalTime += result.executionTime;
    }
}

std::vector<std::string> TestRunner::splitLines(const std::string& text) const {
    std::vector<std::string> lines;
    std::istringstream iss(text);
    std::string line;
    
    while (std::getline(iss, line)) {
        lines.push_back(line);
    }
    
    return lines;
}

std::string TestRunner::trim(const std::string& str) const {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) {
        return "";
    }
    
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}
