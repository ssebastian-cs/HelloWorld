#include "../../src/core/Exercise.h"
#include <memory>
#include <vector>

std::vector<std::unique_ptr<Exercise>> createVariableDataTypeExercises() {
    std::vector<std::unique_ptr<Exercise>> exercises;

    // Exercise 1: Variable Declaration and Initialization
    auto exercise1 = std::make_unique<Exercise>(
        "var-decl-1",
        "Variable Declaration Practice",
        "Practice declaring and initializing variables of different data types.",
        DifficultyLevel::BEGINNER
    );
    
    exercise1->setInstructions(
        "Complete the following tasks:\n"
        "1. Declare an integer variable 'studentAge' and initialize it to 20\n"
        "2. Declare a double variable 'gpa' and initialize it to 3.75\n"
        "3. Declare a char variable 'letterGrade' and initialize it to 'A'\n"
        "4. Declare a bool variable 'isEnrolled' and initialize it to true\n"
        "5. Declare a string variable 'studentName' and initialize it to your name\n"
        "6. Print all variables with descriptive labels"
    );
    
    exercise1->setStarterCode(
        "#include <iostream>\n"
        "#include <string>\n"
        "using namespace std;\n\n"
        "int main() {\n"
        "    // TODO: Declare and initialize variables here\n"
        "    \n"
        "    \n"
        "    // TODO: Print all variables with labels\n"
        "    \n"
        "    \n"
        "    return 0;\n"
        "}"
    );
    
    exercise1->setSolution(
        "#include <iostream>\n"
        "#include <string>\n"
        "using namespace std;\n\n"
        "int main() {\n"
        "    // Variable declarations and initialization\n"
        "    int studentAge = 20;\n"
        "    double gpa = 3.75;\n"
        "    char letterGrade = 'A';\n"
        "    bool isEnrolled = true;\n"
        "    string studentName = \"John Doe\";\n"
        "    \n"
        "    // Print all variables with labels\n"
        "    cout << \"Student Name: \" << studentName << endl;\n"
        "    cout << \"Age: \" << studentAge << endl;\n"
        "    cout << \"GPA: \" << gpa << endl;\n"
        "    cout << \"Letter Grade: \" << letterGrade << endl;\n"
        "    cout << \"Is Enrolled: \" << isEnrolled << endl;\n"
        "    \n"
        "    return 0;\n"
        "}"
    );
    
    exercises.push_back(std::move(exercise1));

    // Exercise 2: Data Type Sizes and Limits
    auto exercise2 = std::make_unique<Exercise>(
        "data-sizes-1",
        "Data Type Sizes and Limits",
        "Explore the sizes and limits of different data types.",
        DifficultyLevel::BEGINNER
    );
    
    exercise2->setInstructions(
        "Write a program that:\n"
        "1. Uses sizeof() to display the size in bytes of: int, float, double, char, bool\n"
        "2. Uses <climits> to display the minimum and maximum values for int\n"
        "3. Uses <cfloat> to display the minimum and maximum values for float\n"
        "4. Creates variables of each type and displays their values"
    );
    
    exercise2->setStarterCode(
        "#include <iostream>\n"
        "#include <climits>\n"
        "#include <cfloat>\n"
        "using namespace std;\n\n"
        "int main() {\n"
        "    // TODO: Display sizes of data types\n"
        "    \n"
        "    \n"
        "    // TODO: Display limits for int and float\n"
        "    \n"
        "    \n"
        "    // TODO: Create and display variables\n"
        "    \n"
        "    \n"
        "    return 0;\n"
        "}"
    );
    
    exercise2->setSolution(
        "#include <iostream>\n"
        "#include <climits>\n"
        "#include <cfloat>\n"
        "using namespace std;\n\n"
        "int main() {\n"
        "    // Display sizes of data types\n"
        "    cout << \"Data Type Sizes:\" << endl;\n"
        "    cout << \"int: \" << sizeof(int) << \" bytes\" << endl;\n"
        "    cout << \"float: \" << sizeof(float) << \" bytes\" << endl;\n"
        "    cout << \"double: \" << sizeof(double) << \" bytes\" << endl;\n"
        "    cout << \"char: \" << sizeof(char) << \" bytes\" << endl;\n"
        "    cout << \"bool: \" << sizeof(bool) << \" bytes\" << endl;\n"
        "    \n"
        "    // Display limits for int and float\n"
        "    cout << \"\\nData Type Limits:\" << endl;\n"
        "    cout << \"int range: \" << INT_MIN << \" to \" << INT_MAX << endl;\n"
        "    cout << \"float range: \" << FLT_MIN << \" to \" << FLT_MAX << endl;\n"
        "    \n"
        "    // Create and display variables\n"
        "    int maxInt = INT_MAX;\n"
        "    float smallFloat = FLT_MIN;\n"
        "    double preciseNum = 3.141592653589793;\n"
        "    char firstLetter = 'A';\n"
        "    bool isPositive = true;\n"
        "    \n"
        "    cout << \"\\nSample Values:\" << endl;\n"
        "    cout << \"Max int: \" << maxInt << endl;\n"
        "    cout << \"Small float: \" << smallFloat << endl;\n"
        "    cout << \"Precise double: \" << preciseNum << endl;\n"
        "    cout << \"Character: \" << firstLetter << endl;\n"
        "    cout << \"Boolean: \" << isPositive << endl;\n"
        "    \n"
        "    return 0;\n"
        "}"
    );
    
    exercises.push_back(std::move(exercise2));

    // Exercise 3: Character and ASCII Operations
    auto exercise3 = std::make_unique<Exercise>(
        "char-ascii-1",
        "Character and ASCII Operations",
        "Practice working with characters and their ASCII values.",
        DifficultyLevel::BEGINNER
    );
    
    exercise3->setInstructions(
        "Write a program that:\n"
        "1. Declares a char variable with your first initial\n"
        "2. Displays the character and its ASCII value\n"
        "3. Converts the character to lowercase (if uppercase) or uppercase (if lowercase)\n"
        "4. Displays the new character and its ASCII value\n"
        "5. Creates a character from an ASCII value (try 65 for 'A')\n"
        "6. Demonstrates escape sequences: newline, tab, and quote"
    );
    
    exercise3->setStarterCode(
        "#include <iostream>\n"
        "using namespace std;\n\n"
        "int main() {\n"
        "    // TODO: Declare character variable\n"
        "    \n"
        "    \n"
        "    // TODO: Display character and ASCII value\n"
        "    \n"
        "    \n"
        "    // TODO: Convert case and display\n"
        "    \n"
        "    \n"
        "    // TODO: Create character from ASCII value\n"
        "    \n"
        "    \n"
        "    // TODO: Demonstrate escape sequences\n"
        "    \n"
        "    \n"
        "    return 0;\n"
        "}"
    );
    
    exercise3->setSolution(
        "#include <iostream>\n"
        "using namespace std;\n\n"
        "int main() {\n"
        "    // Declare character variable\n"
        "    char initial = 'J';\n"
        "    \n"
        "    // Display character and ASCII value\n"
        "    cout << \"Original character: \" << initial << endl;\n"
        "    cout << \"ASCII value: \" << (int)initial << endl;\n"
        "    \n"
        "    // Convert case and display\n"
        "    char converted;\n"
        "    if (initial >= 'A' && initial <= 'Z') {\n"
        "        converted = initial + 32;  // Convert to lowercase\n"
        "        cout << \"Converted to lowercase: \" << converted << endl;\n"
        "    } else if (initial >= 'a' && initial <= 'z') {\n"
        "        converted = initial - 32;  // Convert to uppercase\n"
        "        cout << \"Converted to uppercase: \" << converted << endl;\n"
        "    }\n"
        "    cout << \"New ASCII value: \" << (int)converted << endl;\n"
        "    \n"
        "    // Create character from ASCII value\n"
        "    char fromASCII = 65;  // ASCII for 'A'\n"
        "    cout << \"\\nCharacter from ASCII 65: \" << fromASCII << endl;\n"
        "    \n"
        "    // Demonstrate escape sequences\n"
        "    cout << \"\\nEscape sequences demonstration:\" << endl;\n"
        "    cout << \"Line 1\\nLine 2\" << endl;  // Newline\n"
        "    cout << \"Column1\\tColumn2\" << endl;  // Tab\n"
        "    cout << \"He said \\\"Hello!\\\"\" << endl;  // Quote\n"
        "    \n"
        "    return 0;\n"
        "}"
    );
    
    exercises.push_back(std::move(exercise3));

    return exercises;
}
