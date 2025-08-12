#pragma once
#include <string>
#include <vector>
#include <memory>

enum class CompilerType {
    GCC,
    CLANG,
    MSVC
};

struct CompilationResult {
    bool success;
    std::string executablePath;
    std::string errorOutput;
    std::string warningOutput;
    int exitCode;
    
    CompilationResult() : success(false), exitCode(-1) {}
};

struct ExecutionResult {
    bool success;
    std::string output;
    std::string errorOutput;
    int exitCode;
    double executionTime; // in seconds
    
    ExecutionResult() : success(false), exitCode(-1), executionTime(0.0) {}
};

class CodeCompiler {
private:
    CompilerType compiler;
    std::string compilerPath;
    std::vector<std::string> defaultFlags;
    std::string tempDirectory;

public:
    CodeCompiler(CompilerType compiler = CompilerType::GCC);
    
    // Configuration
    void setCompiler(CompilerType compiler);
    void setCompilerPath(const std::string& path);
    void addCompilerFlag(const std::string& flag);
    void setTempDirectory(const std::string& directory);
    
    // Compilation
    CompilationResult compileCode(const std::string& sourceCode, 
                                  const std::string& filename = "temp.cpp");
    CompilationResult compileFile(const std::string& sourceFile);
    
    // Execution
    ExecutionResult executeCode(const std::string& sourceCode, 
                               const std::string& input = "");
    ExecutionResult executeFile(const std::string& executablePath, 
                               const std::string& input = "");
    
    // Testing utilities
    bool testCode(const std::string& sourceCode, 
                  const std::vector<std::pair<std::string, std::string>>& testCases);
    std::vector<bool> runTestCases(const std::string& sourceCode,
                                   const std::vector<std::pair<std::string, std::string>>& testCases);
    
    // Utility methods
    bool isCompilerAvailable() const;
    std::string getCompilerVersion() const;
    void cleanup();
    
    // Getters
    CompilerType getCompilerType() const { return compiler; }
    const std::string& getCompilerPath() const { return compilerPath; }
    const std::vector<std::string>& getDefaultFlags() const { return defaultFlags; }

private:
    std::string generateTempFilename(const std::string& extension = ".cpp") const;
    std::string buildCompileCommand(const std::string& sourceFile, 
                                   const std::string& outputFile) const;
    bool writeSourceToFile(const std::string& sourceCode, const std::string& filename) const;
    std::string executeCommand(const std::string& command) const;
    void initializeCompiler();
};
