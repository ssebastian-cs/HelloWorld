#include "../../src/core/Lesson.h"
#include <memory>

std::unique_ptr<Lesson> createVariablesDataTypesLesson() {
    auto lesson = std::make_unique<Lesson>(
        "mod1-lesson1", 
        "Variables and Data Types",
        "Learn about C++ fundamental data types, variable declaration, and initialization."
    );

    // Theory: Introduction to Variables
    lesson->addConcept(std::make_unique<Concept>(
        "variables-intro",
        "What are Variables?",
        "Variables are named storage locations in memory that hold data. In C++, every variable must be declared with a specific data type before it can be used. Think of variables as labeled boxes that store different types of information.\n\nSyntax: datatype variable_name = initial_value;",
        ConceptType::THEORY,
        DifficultyLevel::BEGINNER
    ));

    // Code Example: Variable Declaration
    lesson->addExample(std::make_unique<CodeExample>(
        "#include <iostream>\nusing namespace std;\n\nint main() {\n    // Variable declarations\n    int age = 25;\n    double height = 5.9;\n    char grade = 'A';\n    bool isStudent = true;\n    \n    cout << \"Age: \" << age << endl;\n    cout << \"Height: \" << height << endl;\n    cout << \"Grade: \" << grade << endl;\n    cout << \"Is Student: \" << isStudent << endl;\n    \n    return 0;\n}",
        "This example shows how to declare and initialize variables of different data types.",
        "Age: 25\nHeight: 5.9\nGrade: A\nIs Student: 1"
    ));

    // Theory: Integer Data Types
    lesson->addConcept(std::make_unique<Concept>(
        "integer-types",
        "Integer Data Types",
        "C++ provides several integer types to store whole numbers:\n\n• int: Standard integer (typically 32 bits)\n• short: Short integer (typically 16 bits)\n• long: Long integer (typically 64 bits)\n• long long: Extended integer (at least 64 bits)\n\nEach type can be signed (positive/negative) or unsigned (positive only).\nChoose the appropriate type based on the range of values you need to store.",
        ConceptType::THEORY,
        DifficultyLevel::BEGINNER
    ));

    // Code Example: Integer Types
    lesson->addExample(std::make_unique<CodeExample>(
        "#include <iostream>\n#include <climits>\nusing namespace std;\n\nint main() {\n    int regularInt = 42;\n    short smallInt = 100;\n    long bigInt = 1000000L;\n    long long veryBigInt = 9223372036854775807LL;\n    \n    unsigned int positiveOnly = 4294967295U;\n    \n    cout << \"Regular int: \" << regularInt << endl;\n    cout << \"Short int: \" << smallInt << endl;\n    cout << \"Long int: \" << bigInt << endl;\n    cout << \"Long long: \" << veryBigInt << endl;\n    cout << \"Unsigned int: \" << positiveOnly << endl;\n    \n    // Display size and limits\n    cout << \"\\nSize of int: \" << sizeof(int) << \" bytes\" << endl;\n    cout << \"Int range: \" << INT_MIN << \" to \" << INT_MAX << endl;\n    \n    return 0;\n}",
        "This example demonstrates different integer types and their ranges.",
        "Regular int: 42\nShort int: 100\nLong int: 1000000\nLong long: 9223372036854775807\nUnsigned int: 4294967295\n\nSize of int: 4 bytes\nInt range: -2147483648 to 2147483647"
    ));

    // Theory: Floating-Point Data Types
    lesson->addConcept(std::make_unique<Concept>(
        "floating-types",
        "Floating-Point Data Types",
        "Floating-point types store decimal numbers:\n\n• float: Single precision (typically 32 bits, ~7 decimal digits)\n• double: Double precision (typically 64 bits, ~15 decimal digits)\n• long double: Extended precision (varies by system)\n\nUse double for most decimal calculations as it provides better precision.\nFloating-point numbers may have small rounding errors due to binary representation.",
        ConceptType::THEORY,
        DifficultyLevel::BEGINNER
    ));

    // Code Example: Floating-Point Types
    lesson->addExample(std::make_unique<CodeExample>(
        "#include <iostream>\n#include <iomanip>\nusing namespace std;\n\nint main() {\n    float pi_float = 3.14159f;\n    double pi_double = 3.141592653589793;\n    long double pi_long = 3.141592653589793238L;\n    \n    cout << fixed << setprecision(10);\n    cout << \"Float pi: \" << pi_float << endl;\n    cout << \"Double pi: \" << pi_double << endl;\n    cout << \"Long double pi: \" << pi_long << endl;\n    \n    // Demonstrate precision differences\n    float result_f = 1.0f / 3.0f;\n    double result_d = 1.0 / 3.0;\n    \n    cout << \"\\n1/3 as float: \" << result_f << endl;\n    cout << \"1/3 as double: \" << result_d << endl;\n    \n    return 0;\n}",
        "This example shows the precision differences between floating-point types.",
        "Float pi: 3.1415927410\nDouble pi: 3.1415926536\nLong double pi: 3.1415926536\n\n1/3 as float: 0.3333333433\n1/3 as double: 0.3333333333"
    ));

    return lesson;
}

std::unique_ptr<Lesson> createCharacterBooleanLesson() {
    auto lesson = std::make_unique<Lesson>(
        "mod1-lesson1b", 
        "Character and Boolean Data Types",
        "Learn about character and boolean data types in C++."
    );

    // Theory: Character Data Type
    lesson->addConcept(std::make_unique<Concept>(
        "char-type",
        "Character Data Type",
        "The char data type stores single characters:\n\n• char: Stores a single character (8 bits)\n• Characters are enclosed in single quotes: 'A', 'x', '5'\n• Internally stored as ASCII values (numbers)\n• Can perform arithmetic operations on characters\n• Special characters use escape sequences: '\\n', '\\t', '\\\\', '\\''\n\nCharacters are essentially small integers that represent symbols.",
        ConceptType::THEORY,
        DifficultyLevel::BEGINNER
    ));

    // Code Example: Character Operations
    lesson->addExample(std::make_unique<CodeExample>(
        "#include <iostream>\nusing namespace std;\n\nint main() {\n    char letter = 'A';\n    char digit = '5';\n    char symbol = '@';\n    \n    cout << \"Character: \" << letter << \", ASCII value: \" << (int)letter << endl;\n    cout << \"Character: \" << digit << \", ASCII value: \" << (int)digit << endl;\n    cout << \"Character: \" << symbol << \", ASCII value: \" << (int)symbol << endl;\n    \n    // Character arithmetic\n    char nextLetter = letter + 1;\n    cout << \"\\nNext letter after \" << letter << \" is: \" << nextLetter << endl;\n    \n    // Escape sequences\n    cout << \"\\nEscape sequences:\" << endl;\n    cout << \"New line: Hello\\nWorld\" << endl;\n    cout << \"Tab: Hello\\tWorld\" << endl;\n    cout << \"Quote: He said \\\"Hello\\\"\" << endl;\n    \n    return 0;\n}",
        "This example demonstrates character storage, ASCII values, and escape sequences.",
        "Character: A, ASCII value: 65\nCharacter: 5, ASCII value: 53\nCharacter: @, ASCII value: 64\n\nNext letter after A is: B\n\nEscape sequences:\nNew line: Hello\nWorld\nTab: Hello\tWorld\nQuote: He said \"Hello\""
    ));

    // Theory: Boolean Data Type
    lesson->addConcept(std::make_unique<Concept>(
        "bool-type",
        "Boolean Data Type",
        "The bool data type stores logical values:\n\n• bool: Stores true or false values\n• true represents logical truth (internally stored as 1)\n• false represents logical falsehood (internally stored as 0)\n• Any non-zero value is considered true when converted to bool\n• Zero values are considered false\n• Essential for conditional statements and logical operations",
        ConceptType::THEORY,
        DifficultyLevel::BEGINNER
    ));

    // Code Example: Boolean Operations
    lesson->addExample(std::make_unique<CodeExample>(
        "#include <iostream>\nusing namespace std;\n\nint main() {\n    bool isTrue = true;\n    bool isFalse = false;\n    bool result;\n    \n    cout << \"Boolean values:\" << endl;\n    cout << \"isTrue: \" << isTrue << \" (as int: \" << (int)isTrue << \")\" << endl;\n    cout << \"isFalse: \" << isFalse << \" (as int: \" << (int)isFalse << \")\" << endl;\n    \n    // Boolean from expressions\n    int a = 10, b = 5;\n    result = (a > b);\n    cout << \"\\n\" << a << \" > \" << b << \" is: \" << result << endl;\n    \n    result = (a == b);\n    cout << a << \" == \" << b << \" is: \" << result << endl;\n    \n    // Conversion from numbers\n    bool fromNumber = 42;  // Any non-zero is true\n    bool fromZero = 0;     // Zero is false\n    \n    cout << \"\\nBool from 42: \" << fromNumber << endl;\n    cout << \"Bool from 0: \" << fromZero << endl;\n    \n    return 0;\n}",
        "This example shows boolean values, comparisons, and type conversions.",
        "Boolean values:\nisTrue: 1 (as int: 1)\nisFalse: 0 (as int: 0)\n\n10 > 5 is: 1\n10 == 5 is: 0\n\nBool from 42: 1\nBool from 0: 0"
    ));

    return lesson;
}

std::unique_ptr<Lesson> createStringBasicsLesson() {
    auto lesson = std::make_unique<Lesson>(
        "mod1-lesson1c", 
        "String Basics",
        "Introduction to working with strings in C++."
    );

    // Theory: String Data Type
    lesson->addConcept(std::make_unique<Concept>(
        "string-type",
        "String Data Type",
        "Strings store sequences of characters:\n\n• #include <string> required for std::string\n• string: Stores text of variable length\n• Strings are enclosed in double quotes: \"Hello World\"\n• Can be concatenated with + operator\n• Provides many useful methods for text manipulation\n• More flexible and safer than C-style character arrays",
        ConceptType::THEORY,
        DifficultyLevel::BEGINNER
    ));

    // Code Example: String Operations
    lesson->addExample(std::make_unique<CodeExample>(
        "#include <iostream>\n#include <string>\nusing namespace std;\n\nint main() {\n    string firstName = \"John\";\n    string lastName = \"Doe\";\n    string fullName = firstName + \" \" + lastName;\n    \n    cout << \"First name: \" << firstName << endl;\n    cout << \"Last name: \" << lastName << endl;\n    cout << \"Full name: \" << fullName << endl;\n    \n    // String properties\n    cout << \"\\nString length: \" << fullName.length() << endl;\n    cout << \"Is empty: \" << firstName.empty() << endl;\n    \n    // String access\n    cout << \"First character: \" << fullName[0] << endl;\n    cout << \"Last character: \" << fullName[fullName.length() - 1] << endl;\n    \n    // String input\n    string userInput;\n    cout << \"\\nEnter your name: \";\n    getline(cin, userInput);  // Reads entire line including spaces\n    cout << \"Hello, \" << userInput << \"!\" << endl;\n    \n    return 0;\n}",
        "This example demonstrates basic string operations and input.",
        "First name: John\nLast name: Doe\nFull name: John Doe\n\nString length: 8\nIs empty: 0\nFirst character: J\nLast character: e\n\nEnter your name: Alice Smith\nHello, Alice Smith!"
    ));

    return lesson;
}
