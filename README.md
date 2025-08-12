# C++ Learning Curriculum System

A comprehensive C++ learning platform that provides structured lessons, interactive exercises, and hands-on projects to guide students from basic programming concepts to advanced software engineering practices.

## Project Structure

```
├── src/
│   ├── core/                 # Core learning framework classes
│   │   ├── Lesson.h/.cpp     # Lesson and concept management
│   │   ├── Exercise.h/.cpp   # Exercise system and validation
│   │   └── ProgressTracker.h/.cpp # Student progress tracking
│   ├── utils/                # Utility classes
│   │   ├── CodeCompiler.h/.cpp    # Code compilation and execution
│   │   └── TestRunner.h/.cpp      # Automated testing framework
│   └── main.cpp              # Main application entry point
├── modules/                  # Learning modules (8 modules total)
├── exercises/                # Practice exercises organized by module
├── projects/                 # Hands-on projects and capstone work
├── assessments/              # Evaluation materials and rubrics
└── CMakeLists.txt           # Build configuration
```

## Features

### Core Learning Framework
- **Lesson Management**: Structured lessons with concepts, examples, and prerequisites
- **Exercise System**: Interactive coding exercises with automated testing
- **Progress Tracking**: Comprehensive student progress and performance analytics
- **Code Compilation**: Multi-compiler support (GCC, Clang, MSVC)
- **Automated Testing**: Test runner with detailed feedback and reporting

### Learning Modules
1. **C++ Fundamentals** - Variables, data types, control structures
2. **Functions and Modularity** - Function design, scope, header files
3. **Arrays, Pointers, and Memory Management** - Memory concepts and dynamic allocation
4. **Object-Oriented Programming** - Classes, inheritance, polymorphism
5. **Advanced C++ Features** - Templates, STL, modern C++ features
6. **System Design and UML** - Design principles and documentation
7. **Design Patterns** - Common software design patterns
8. **Capstone Projects** - Comprehensive final projects

## Building the Project

### Prerequisites
- C++17 compatible compiler (GCC, Clang, or MSVC)
- CMake 3.16 or higher

### Build Instructions

```bash
# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the project
cmake --build .

# Run the application
./curriculum_app  # Linux/Mac
curriculum_app.exe  # Windows
```

### Build Options

```bash
# Build with tests
cmake -DBUILD_TESTS=ON ..

# Specify build type
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

## Usage

### Running the System
```bash
./curriculum_app
```

The application will initialize the core components and verify system functionality.

### Key Classes

#### Lesson Management
```cpp
// Create a lesson
auto lesson = std::make_unique<Lesson>("lesson-1", "Variables", "Learn about C++ variables");

// Add concepts and examples
lesson->addConcept(std::make_unique<Concept>("concept-1", "Integer Types", 
                                           "Understanding int, long, short", 
                                           ConceptType::THEORY, DifficultyLevel::BEGINNER));
```

#### Exercise System
```cpp
// Create an exercise
auto exercise = std::make_unique<Exercise>("ex-1", "Variable Practice", 
                                         "Practice variable declaration",
                                         ExerciseType::CODING, DifficultyLevel::BEGINNER);

// Add test cases
exercise->addTestCase(TestCase("", "42", "Should output 42"));
```

#### Progress Tracking
```cpp
// Initialize progress tracker
auto tracker = std::make_unique<ProgressTracker>("student_001");

// Track progress
tracker->startModule("module-1", "C++ Fundamentals");
tracker->completeLesson("module-1", "lesson-1");
tracker->completeExercise("module-1", "exercise-1", 85.0);
```

## Development

### Adding New Modules
1. Create module directory in `modules/`
2. Add lessons, exercises, and projects
3. Update module dependencies and prerequisites
4. Create assessment materials

### Adding New Exercise Types
1. Extend `ExerciseType` enum in `Exercise.h`
2. Implement validation logic in `Exercise.cpp`
3. Add test runner support in `TestRunner.cpp`

### Extending Compiler Support
1. Add new compiler type to `CompilerType` enum
2. Implement compiler-specific logic in `CodeCompiler.cpp`
3. Add appropriate compiler flags and commands

## Testing

The system includes comprehensive testing capabilities:

- **Syntax Validation**: Checks code for compilation errors
- **Test Case Execution**: Runs code against predefined test cases
- **Performance Monitoring**: Tracks execution time and resource usage
- **Common Mistake Detection**: Identifies typical programming errors

## Contributing

1. Follow C++17 standards and best practices
2. Maintain consistent code formatting
3. Add appropriate documentation and comments
4. Include test cases for new functionality
5. Update README for significant changes

## License

This project is designed for educational purposes as part of a comprehensive C++ learning curriculum.

## Requirements Addressed

This implementation addresses the following requirements from the specification:

- **Requirement 9.1**: Interactive learning tools with code examples and exercises
- **Requirement 9.3**: Progress tracking and completion indicators

The foundational framework provides the core infrastructure needed to support all curriculum modules and learning activities.
