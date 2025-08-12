#include "../../src/core/Lesson.h"
#include <memory>

std::unique_ptr<Lesson> createArithmeticOperatorsLesson() {
    auto lesson = std::make_unique<Lesson>(
        "mod1-lesson2a", 
        "Arithmetic Operators",
        "Learn about arithmetic operators and mathematical expressions in C++."
    );

    // Theory: Arithmetic Operators
    lesson->addConcept(std::make_unique<Concept>(
        "arithmetic-ops",
        "Arithmetic Operators",
        "C++ provides several arithmetic operators for mathematical calculations:\n\n• + (Addition): Adds two operands\n• - (Subtraction): Subtracts right operand from left\n• * (Multiplication): Multiplies two operands\n• / (Division): Divides left operand by right\n• % (Modulus): Returns remainder of division\n\nOperator precedence follows mathematical rules:\n1. Parentheses ()\n2. Multiplication *, Division /, Modulus %\n3. Addition +, Subtraction -",
        ConceptType::THEORY,
        DifficultyLevel::BEGINNER
    ));

    // Code Example: Basic Arithmetic
    lesson->addExample(std::make_unique<CodeExample>(
        "#include <iostream>\nusing namespace std;\n\nint main() {\n    int a = 15, b = 4;\n    double x = 15.0, y = 4.0;\n    \n    cout << \"Integer arithmetic:\" << endl;\n    cout << a << \" + \" << b << \" = \" << (a + b) << endl;\n    cout << a << \" - \" << b << \" = \" << (a - b) << endl;\n    cout << a << \" * \" << b << \" = \" << (a * b) << endl;\n    cout << a << \" / \" << b << \" = \" << (a / b) << endl;  // Integer division\n    cout << a << \" % \" << b << \" = \" << (a % b) << endl;\n    \n    cout << \"\\nFloating-point arithmetic:\" << endl;\n    cout << x << \" / \" << y << \" = \" << (x / y) << endl;  // Precise division\n    \n    // Operator precedence\n    int result = 2 + 3 * 4;  // 3 * 4 first, then + 2\n    cout << \"\\n2 + 3 * 4 = \" << result << endl;\n    \n    result = (2 + 3) * 4;    // Parentheses first\n    cout << \"(2 + 3) * 4 = \" << result << endl;\n    \n    return 0;\n}",
        "This example demonstrates basic arithmetic operations and precedence.",
        "Integer arithmetic:\n15 + 4 = 19\n15 - 4 = 11\n15 * 4 = 60\n15 / 4 = 3\n15 % 4 = 3\n\nFloating-point arithmetic:\n15 / 4 = 3.75\n\n2 + 3 * 4 = 14\n(2 + 3) * 4 = 20"
    ));

    // Theory: Assignment Operators
    lesson->addConcept(std::make_unique<Concept>(
        "assignment-ops",
        "Assignment and Compound Operators",
        "Assignment operators modify variable values:\n\n• = (Assignment): Assigns right value to left variable\n• += (Add and assign): a += b is equivalent to a = a + b\n• -= (Subtract and assign): a -= b is equivalent to a = a - b\n• *= (Multiply and assign): a *= b is equivalent to a = a * b\n• /= (Divide and assign): a /= b is equivalent to a = a / b\n• %= (Modulus and assign): a %= b is equivalent to a = a % b\n\nThese compound operators are more concise and often more efficient.",
        ConceptType::THEORY,
        DifficultyLevel::BEGINNER
    ));

    // Code Example: Assignment Operators
    lesson->addExample(std::make_unique<CodeExample>(
        "#include <iostream>\nusing namespace std;\n\nint main() {\n    int score = 100;\n    \n    cout << \"Initial score: \" << score << endl;\n    \n    // Compound assignment operators\n    score += 25;  // Add 25 points\n    cout << \"After bonus (+= 25): \" << score << endl;\n    \n    score -= 10;  // Lose 10 points\n    cout << \"After penalty (-= 10): \" << score << endl;\n    \n    score *= 2;   // Double the score\n    cout << \"After doubling (*= 2): \" << score << endl;\n    \n    score /= 4;   // Quarter the score\n    cout << \"After quartering (/= 4): \" << score << endl;\n    \n    score %= 50;  // Get remainder when divided by 50\n    cout << \"After modulus (%= 50): \" << score << endl;\n    \n    // Multiple assignments\n    int a, b, c;\n    a = b = c = 10;  // All variables get value 10\n    cout << \"\\na = \" << a << \", b = \" << b << \", c = \" << c << endl;\n    \n    return 0;\n}",
        "This example shows compound assignment operators in action.",
        "Initial score: 100\nAfter bonus (+= 25): 125\nAfter penalty (-= 10): 115\nAfter doubling (*= 2): 230\nAfter quartering (/= 4): 57\nAfter modulus (%= 50): 7\n\na = 10, b = 10, c = 10"
    ));

    return lesson;
}

std::unique_ptr<Lesson> createComparisonLogicalOperatorsLesson() {
    auto lesson = std::make_unique<Lesson>(
        "mod1-lesson2b", 
        "Comparison and Logical Operators",
        "Learn about comparison and logical operators for decision making."
    );

    // Theory: Comparison Operators
    lesson->addConcept(std::make_unique<Concept>(
        "comparison-ops",
        "Comparison Operators",
        "Comparison operators compare values and return boolean results:\n\n• == (Equal to): Returns true if operands are equal\n• != (Not equal to): Returns true if operands are different\n• < (Less than): Returns true if left is smaller than right\n• > (Greater than): Returns true if left is larger than right\n• <= (Less than or equal): Returns true if left ≤ right\n• >= (Greater than or equal): Returns true if left ≥ right\n\nNote: Use == for comparison, = is for assignment!",
        ConceptType::THEORY,
        DifficultyLevel::BEGINNER
    ));

    // Code Example: Comparison Operators
    lesson->addExample(std::make_unique<CodeExample>(
        "#include <iostream>\nusing namespace std;\n\nint main() {\n    int a = 10, b = 20, c = 10;\n    \n    cout << \"Values: a = \" << a << \", b = \" << b << \", c = \" << c << endl;\n    cout << \"\\nComparison results:\" << endl;\n    \n    cout << \"a == b: \" << (a == b) << endl;  // false (0)\n    cout << \"a == c: \" << (a == c) << endl;  // true (1)\n    cout << \"a != b: \" << (a != b) << endl;  // true (1)\n    cout << \"a < b: \" << (a < b) << endl;    // true (1)\n    cout << \"a > b: \" << (a > b) << endl;    // false (0)\n    cout << \"a <= c: \" << (a <= c) << endl;  // true (1)\n    cout << \"b >= a: \" << (b >= a) << endl;  // true (1)\n    \n    // String comparison\n    string str1 = \"apple\";\n    string str2 = \"banana\";\n    cout << \"\\nString comparison:\" << endl;\n    cout << \"\\\"\" << str1 << \"\\\" < \\\"\" << str2 << \"\\\": \" << (str1 < str2) << endl;\n    \n    return 0;\n}",
        "This example demonstrates comparison operators with different data types.",
        "Values: a = 10, b = 20, c = 10\n\nComparison results:\na == b: 0\na == c: 1\na != b: 1\na < b: 1\na > b: 0\na <= c: 1\nb >= a: 1\n\nString comparison:\n\"apple\" < \"banana\": 1"
    ));

    // Theory: Logical Operators
    lesson->addConcept(std::make_unique<Concept>(
        "logical-ops",
        "Logical Operators",
        "Logical operators combine boolean expressions:\n\n• && (Logical AND): Returns true if both operands are true\n• || (Logical OR): Returns true if at least one operand is true\n• ! (Logical NOT): Returns opposite of operand's truth value\n\nShort-circuit evaluation:\n• && stops if first operand is false\n• || stops if first operand is true\n\nTruth table:\nA | B | A && B | A || B | !A\nT | T |   T    |   T    | F\nT | F |   F    |   T    | F\nF | T |   F    |   T    | T\nF | F |   F    |   F    | T",
        ConceptType::THEORY,
        DifficultyLevel::BEGINNER
    ));

    // Code Example: Logical Operators
    lesson->addExample(std::make_unique<CodeExample>(
        "#include <iostream>\nusing namespace std;\n\nint main() {\n    bool sunny = true;\n    bool warm = false;\n    bool weekend = true;\n    \n    cout << \"Weather conditions:\" << endl;\n    cout << \"Sunny: \" << sunny << \", Warm: \" << warm << \", Weekend: \" << weekend << endl;\n    \n    // Logical AND\n    bool perfectDay = sunny && warm && weekend;\n    cout << \"\\nPerfect day (sunny AND warm AND weekend): \" << perfectDay << endl;\n    \n    // Logical OR\n    bool goodDay = sunny || warm;\n    cout << \"Good day (sunny OR warm): \" << goodDay << endl;\n    \n    // Logical NOT\n    bool notRaining = !false;  // Assuming it's not raining\n    cout << \"Not raining: \" << notRaining << endl;\n    \n    // Complex expressions\n    bool goOutside = (sunny || warm) && weekend && notRaining;\n    cout << \"Should go outside: \" << goOutside << endl;\n    \n    // Short-circuit demonstration\n    int x = 5;\n    bool result = (x > 10) && (++x > 0);  // ++x won't execute\n    cout << \"\\nAfter short-circuit AND, x = \" << x << endl;\n    \n    return 0;\n}",
        "This example shows logical operators and short-circuit evaluation.",
        "Weather conditions:\nSunny: 1, Warm: 0, Weekend: 1\n\nPerfect day (sunny AND warm AND weekend): 0\nGood day (sunny OR warm): 1\nNot raining: 1\nShould go outside: 1\n\nAfter short-circuit AND, x = 5"
    ));

    return lesson;
}
