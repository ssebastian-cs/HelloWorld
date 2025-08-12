#include "CodeCompiler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <filesystem>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#include <process.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#endif

CodeCompiler::CodeCompiler(CompilerType compiler) 
    : compiler(compiler), tempDirectory("temp") {
    initializeCompiler();
    
    // Create temp directory if it doesn't exist
    std::filesystem::create_directories(tempDirectory);
}

void CodeCompiler::setCompiler(CompilerType compiler) {
    this->compiler = compiler;
    initializeCompiler();
}

void CodeCompiler::setCompilerPath(const std::string& path) {
    this->compilerPath = path;
}

void CodeCompiler::addCompilerFlag(const std::string& flag) {
    defaultFlags.push_back(flag);
}

void CodeCompiler::setTempDirectory(const std::string& directory) {
    this->tempDirectory = directory;
    std::filesystem::create_directories(tempDirectory);
}

CompilationResult CodeCompiler::compileCode(const std::string& sourceCode, 
                                           const std::string& filename) {
    CompilationResult result;
    
    if (!isCompilerAvailable()) {
        result.errorOutput = "Compiler not available";
        return result;
    }
    
    // Write source code to temporary file
    std::string sourceFile = tempDirectory + "/" + filename;
    if (!writeSourceToFile(sourceCode, sourceFile)) {
        result.errorOutput = "Failed to write source file";
        return result;
    }
    
    return compileFile(sourceFile);
}

CompilationResult CodeCompiler::compileFile(const std::string& sourceFile) {
    CompilationResult result;
    
    if (!std::filesystem::exists(sourceFile)) {
        result.errorOutput = "Source file does not exist: " + sourceFile;
        return result;
    }
    
    // Generate output executable name
    std::string baseName = std::filesystem::path(sourceFile).stem().string();
    std::string outputFile = tempDirectory + "/" + baseName;
    
#ifdef _WIN32
    outputFile += ".exe";
#endif
    
    // Build compile command
    std::string command = buildCompileCommand(sourceFile, outputFile);
    
    // Execute compilation
    std::string output = executeCommand(command);
    
    // Check if compilation was successful
    if (std::filesystem::exists(outputFile)) {
        result.success = true;
        result.executablePath = outputFile;
        result.exitCode = 0;
    } else {
        result.success = false;
        result.errorOutput = output;
        result.exitCode = 1;
    }
    
    return result;
}

ExecutionResult CodeCompiler::executeCode(const std::string& sourceCode, 
                                         const std::string& input) {
    ExecutionResult result;
    
    // First compile the code
    CompilationResult compileResult = compileCode(sourceCode);
    if (!compileResult.success) {
        result.errorOutput = "Compilation failed: " + compileResult.errorOutput;
        return result;
    }
    
    // Then execute it
    return executeFile(compileResult.executablePath, input);
}

ExecutionResult CodeCompiler::executeFile(const std::string& executablePath, 
                                         const std::string& input) {
    ExecutionResult result;
    
    if (!std::filesystem::exists(executablePath)) {
        result.errorOutput = "Executable not found: " + executablePath;
        return result;
    }
    
    auto startTime = std::chrono::high_resolution_clock::now();
    
    // Create command with input redirection if needed
    std::string command = executablePath;
    if (!input.empty()) {
        // Write input to temporary file
        std::string inputFile = tempDirectory + "/input.txt";
        std::ofstream inFile(inputFile);
        inFile << input;
        inFile.close();
        
        command += " < " + inputFile;
    }
    
    // Execute the program
    std::string output = executeCommand(command);
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    
    result.success = true;
    result.output = output;
    result.executionTime = duration.count() / 1000000.0; // Convert to seconds
    result.exitCode = 0;
    
    return result;
}

bool CodeCompiler::testCode(const std::string& sourceCode, 
                           const std::vector<std::pair<std::string, std::string>>& testCases) {
    auto results = runTestCases(sourceCode, testCases);
    return std::all_of(results.begin(), results.end(), [](bool result) { return result; });
}

std::vector<bool> CodeCompiler::runTestCases(const std::string& sourceCode,
                                            const std::vector<std::pair<std::string, std::string>>& testCases) {
    std::vector<bool> results;
    
    // Compile once
    CompilationResult compileResult = compileCode(sourceCode);
    if (!compileResult.success) {
        // All tests fail if compilation fails
        results.resize(testCases.size(), false);
        return results;
    }
    
    // Run each test case
    for (const auto& testCase : testCases) {
        ExecutionResult execResult = executeFile(compileResult.executablePath, testCase.first);
        
        if (execResult.success) {
            // Simple string comparison (could be enhanced with better matching)
            std::string expectedOutput = testCase.second;
            std::string actualOutput = execResult.output;
            
            // Trim whitespace for comparison
            expectedOutput.erase(expectedOutput.find_last_not_of(" \n\r\t") + 1);
            actualOutput.erase(actualOutput.find_last_not_of(" \n\r\t") + 1);
            
            results.push_back(expectedOutput == actualOutput);
        } else {
            results.push_back(false);
        }
    }
    
    return results;
}

bool CodeCompiler::isCompilerAvailable() const {
    if (compilerPath.empty()) {
        return false;
    }
    
    // Try to execute compiler with version flag
    std::string versionCommand = compilerPath + " --version";
    std::string output = executeCommand(versionCommand);
    
    return !output.empty();
}

std::string CodeCompiler::getCompilerVersion() const {
    if (!isCompilerAvailable()) {
        return "Compiler not available";
    }
    
    std::string versionCommand = compilerPath + " --version";
    std::string output = executeCommand(versionCommand);
    
    // Extract first line of version output
    size_t newlinePos = output.find('\n');
    if (newlinePos != std::string::npos) {
        return output.substr(0, newlinePos);
    }
    
    return output;
}

void CodeCompiler::cleanup() {
    // Remove temporary files
    try {
        if (std::filesystem::exists(tempDirectory)) {
            std::filesystem::remove_all(tempDirectory);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error during cleanup: " << e.what() << std::endl;
    }
}

std::string CodeCompiler::generateTempFilename(const std::string& extension) const {
    auto now = std::chrono::system_clock::now();
    auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()).count();
    
    return "temp_" + std::to_string(timestamp) + extension;
}

std::string CodeCompiler::buildCompileCommand(const std::string& sourceFile, 
                                             const std::string& outputFile) const {
    std::ostringstream command;
    command << compilerPath;
    
    // Add default flags
    for (const std::string& flag : defaultFlags) {
        command << " " << flag;
    }
    
    // Add source file and output specification
    command << " \"" << sourceFile << "\" -o \"" << outputFile << "\"";
    
    return command.str();
}

bool CodeCompiler::writeSourceToFile(const std::string& sourceCode, const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    file << sourceCode;
    return file.good();
}

std::string CodeCompiler::executeCommand(const std::string& command) const {
    std::string result;
    
#ifdef _WIN32
    // Windows implementation
    FILE* pipe = _popen(command.c_str(), "r");
    if (pipe) {
        char buffer[128];
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer;
        }
        _pclose(pipe);
    }
#else
    // Unix/Linux implementation
    FILE* pipe = popen(command.c_str(), "r");
    if (pipe) {
        char buffer[128];
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer;
        }
        pclose(pipe);
    }
#endif
    
    return result;
}

void CodeCompiler::initializeCompiler() {
    defaultFlags.clear();
    
    switch (compiler) {
        case CompilerType::GCC:
            compilerPath = "g++";
            defaultFlags = {"-std=c++17", "-Wall", "-Wextra"};
            break;
            
        case CompilerType::CLANG:
            compilerPath = "clang++";
            defaultFlags = {"-std=c++17", "-Wall", "-Wextra"};
            break;
            
        case CompilerType::MSVC:
            compilerPath = "cl";
            defaultFlags = {"/std:c++17", "/W4"};
            break;
    }
}
