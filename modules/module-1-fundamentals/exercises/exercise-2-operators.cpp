#include "../../src/core/Exercise.h"
#include <memory>
#include <vector>

std::vector<std::unique_ptr<Exercise>> createOperatorExercises() {
    std::vector<std::unique_ptr<Exercise>> exercises;

    // Exercise 1: Arithmetic Operations Calculator
    auto exercise1 = std::make_unique<Exercise>(
        "arithmetic-calc-1",
        "Basic Arithmetic Calculator",
        "Create a program that performs basic arithmetic operations.",
        DifficultyLevel::BEGINNER
    );
    
    exercise1->setInstructions(
        "Write a program that:\n"
        "1. Declares two integer variables (a = 25, b = 7)\n"
        "2. Performs and displays all arithmetic operations (+, -, *, /, %)\n"
        "3. Shows the difference between integer and floating-point division\n"
        "4. Demonstrates operator precedence with a complex expression\n"
        "5. Uses compound assignment operators to modify a variable"
    );
    
    exercise1->setStarterCode(
        "#include <iostream>\n"
        "using namespace std;\n\n"
        "int main() {\n"
        "    // TODO: Declare variables\n"
        "    \n"
        "    \n"
        "    // TODO: Perform arithmetic operations\n"
        "    \n"
        "    \n"
        "    // TODO: Show integer vs floating-point division\n"
        "    \n"
        "    \n"
        "    // TODO: Demonstrate operator precedence\n"
        "    \n"
        "    \n"
        "    // TODO: Use compound assignment operators\n"
        "    \n"
        "    \n"
        "    return 0;\n"
        "}"
    );
    
    exercise1->setSolution(
        "#include <iostream>\n"
        "using namespace std;\n\n"
        "int main() {\n"
        "    // Declare variables\n"
        "    int a = 25, b = 7;\n"
        "    \n"
        "    cout << \"Values: a = \" << a << \", b = \" << b << endl;\n"
        "    cout << \"\\nArithmetic Operations:\" << endl;\n"
        "    \n"
        "    // Perform arithmetic operations\n"
        "    cout << \"a + b = \" << (a + b) << endl;\n"
        "    cout << \"a - b = \" << (a - b) << endl;\n"
        "    cout << \"a * b = \" << (a * b) << endl;\n"
        "    cout << \"a / b = \" << (a / b) << \" (integer division)\" << endl;\n"
        "    cout << \"a % b = \" << (a % b) << endl;\n"
        "    \n"
        "    // Show integer vs floating-point division\n"
        "    cout << \"\\nDivision Comparison:\" << endl;\n"
        "    cout << \"Integer division: \" << a << \" / \" << b << \" = \" << (a / b) << endl;\n"
        "    cout << \"Floating-point division: \" << a << \" / \" << b << \" = \" << ((double)a / b) << endl;\n"
        "    \n"
        "    // Demonstrate operator precedence\n"
        "    cout << \"\\nOperator Precedence:\" << endl;\n"
        "    int result1 = 2 + 3 * 4;\n"
        "    int result2 = (2 + 3) * 4;\n"
        "    cout << \"2 + 3 * 4 = \" << result1 << endl;\n"
        "    cout << \"(2 + 3) * 4 = \" << result2 << endl;\n"
        "    \n"
        "    // Use compound assignment operators\n"
        "    cout << \"\\nCompound Assignment:\" << endl;\n"
        "    int score = 100;\n"
        "    cout << \"Initial score: \" << score << endl;\n"
        "    \n"
        "    score += 15;\n"
        "    cout << \"After += 15: \" << score << endl;\n"
        "    \n"
        "    score *= 2;\n"
        "    cout << \"After *= 2: \" << score << endl;\n"
        "    \n"
        "    score /= 5;\n"
        "    cout << \"After /= 5: \" << score << endl;\n"
        "    \n"
        "    return 0;\n"
        "}"
    );
    
    exercises.push_back(std::move(exercise1));

    // Exercise 2: Comparison and Logical Operations
    auto exercise2 = std::make_unique<Exercise>(
        "comparison-logical-1",
        "Comparison and Logical Operations",
        "Practice using comparison and logical operators.",
        DifficultyLevel::BEGINNER
    );
    
    exercise2->setInstructions(
        "Write a program that:\n"
        "1. Declares three integer variables (x = 10, y = 20, z = 10)\n"
        "2. Performs all comparison operations between x and y\n"
        "3. Uses logical operators to create complex conditions\n"
        "4. Demonstrates short-circuit evaluation\n"
        "5. Creates a simple eligibility checker (age >= 18 AND score >= 70)"
    );
    
    exercise2->setStarterCode(
        "#include <iostream>\n"
        "using namespace std;\n\n"
        "int main() {\n"
        "    // TODO: Declare variables\n"
        "    \n"
        "    \n"
        "    // TODO: Perform comparison operations\n"
        "    \n"
        "    \n"
        "    // TODO: Use logical operators\n"
        "    \n"
        "    \n"
        "    // TODO: Demonstrate short-circuit evaluation\n"
        "    \n"
        "    \n"
        "    // TODO: Create eligibility checker\n"
        "    \n"
        "    \n"
        "    return 0;\n"
        "}"
    );
    
    exercise2->setSolution(
        "#include <iostream>\n"
        "using namespace std;\n\n"
        "int main() {\n"
        "    // Declare variables\n"
        "    int x = 10, y = 20, z = 10;\n"
        "    \n"
        "    cout << \"Values: x = \" << x << \", y = \" << y << \", z = \" << z << endl;\n"
        "    cout << \"\\nComparison Operations:\" << endl;\n"
        "    \n"
        "    // Perform comparison operations\n"
        "    cout << \"x == y: \" << (x == y) << endl;\n"
        "    cout << \"x != y: \" << (x != y) << endl;\n"
        "    cout << \"x < y: \" << (x < y) << endl;\n"
        "    cout << \"x > y: \" << (x > y) << endl;\n"
        "    cout << \"x <= z: \" << (x <= z) << endl;\n"
        "    cout << \"y >= x: \" << (y >= x) << endl;\n"
        "    \n"
        "    // Use logical operators\n"
        "    cout << \"\\nLogical Operations:\" << endl;\n"
        "    bool condition1 = (x < y) && (x == z);\n"
        "    bool condition2 = (x > y) || (x == z);\n"
        "    bool condition3 = !(x == y);\n"
        "    \n"
        "    cout << \"(x < y) && (x == z): \" << condition1 << endl;\n"
        "    cout << \"(x > y) || (x == z): \" << condition2 << endl;\n"
        "    cout << \"!(x == y): \" << condition3 << endl;\n"
        "    \n"
        "    // Demonstrate short-circuit evaluation\n"
        "    cout << \"\\nShort-circuit Evaluation:\" << endl;\n"
        "    int counter = 0;\n"
        "    bool result = (x > y) && (++counter > 0);\n"
        "    cout << \"After (x > y) && (++counter > 0), counter = \" << counter << endl;\n"
        "    cout << \"Result: \" << result << endl;\n"
        "    \n"
        "    // Create eligibility checker\n"
        "    cout << \"\\nEligibility Checker:\" << endl;\n"
        "    int age = 19;\n"
        "    int score = 85;\n"
        "    \n"
        "    bool isEligible = (age >= 18) && (score >= 70);\n"
        "    cout << \"Age: \" << age << \", Score: \" << score << endl;\n"
        "    cout << \"Eligible (age >= 18 AND score >= 70): \" << isEligible << endl;\n"
        "    \n"
        "    return 0;\n"
        "}"
    );
    
    exercises.push_back(std::move(exercise2));

    // Exercise 3: Mixed Operations Challenge
    auto exercise3 = std::make_unique<Exercise>(
        "mixed-ops-1",
        "Mixed Operations Challenge",
        "Combine different types of operators in practical scenarios.",
        DifficultyLevel::INTERMEDIATE
    );
    
    exercise3->setInstructions(
        "Write a program that:\n"
        "1. Calculates the area and perimeter of a rectangle (length=12.5, width=8.3)\n"
        "2. Determines if a year is a leap year (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))\n"
        "3. Converts temperature from Celsius to Fahrenheit (F = C * 9/5 + 32)\n"
        "4. Checks if a number is even or odd using modulus operator\n"
        "5. Calculates compound interest: A = P(1 + r/n)^(nt) - simplified version"
    );
    
    exercise3->setStarterCode(
        "#include <iostream>\n"
        "#include <cmath>\n"
        "using namespace std;\n\n"
        "int main() {\n"
        "    // TODO: Rectangle calculations\n"
        "    \n"
        "    \n"
        "    // TODO: Leap year check\n"
        "    \n"
        "    \n"
        "    // TODO: Temperature conversion\n"
        "    \n"
        "    \n"
        "    // TODO: Even/odd check\n"
        "    \n"
        "    \n"
        "    // TODO: Simple interest calculation\n"
        "    \n"
        "    \n"
        "    return 0;\n"
        "}"
    );
    
    exercise3->setSolution(
        "#include <iostream>\n"
        "#include <cmath>\n"
        "using namespace std;\n\n"
        "int main() {\n"
        "    // Rectangle calculations\n"
        "    double length = 12.5, width = 8.3;\n"
        "    double area = length * width;\n"
        "    double perimeter = 2 * (length + width);\n"
        "    \n"
        "    cout << \"Rectangle (\" << length << \" x \" << width << \"):\" << endl;\n"
        "    cout << \"Area: \" << area << endl;\n"
        "    cout << \"Perimeter: \" << perimeter << endl;\n"
        "    \n"
        "    // Leap year check\n"
        "    int year = 2024;\n"
        "    bool isLeapYear = (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));\n"
        "    cout << \"\\nYear \" << year << \" is \" << (isLeapYear ? \"\" : \"not \") << \"a leap year.\" << endl;\n"
        "    \n"
        "    // Temperature conversion\n"
        "    double celsius = 25.0;\n"
        "    double fahrenheit = celsius * 9.0 / 5.0 + 32;\n"
        "    cout << \"\\nTemperature conversion:\" << endl;\n"
        "    cout << celsius << \"°C = \" << fahrenheit << \"°F\" << endl;\n"
        "    \n"
        "    // Even/odd check\n"
        "    int number = 17;\n"
        "    bool isEven = (number % 2 == 0);\n"
        "    cout << \"\\nNumber \" << number << \" is \" << (isEven ? \"even\" : \"odd\") << endl;\n"
        "    \n"
        "    // Simple interest calculation (simplified compound interest)\n"
        "    double principal = 1000.0;\n"
        "    double rate = 0.05;  // 5%\n"
        "    int time = 3;        // 3 years\n"
        "    \n"
        "    double simpleInterest = principal * rate * time;\n"
        "    double totalAmount = principal + simpleInterest;\n"
        "    \n"
        "    cout << \"\\nSimple Interest Calculation:\" << endl;\n"
        "    cout << \"Principal: $\" << principal << endl;\n"
        "    cout << \"Rate: \" << (rate * 100) << \"%\" << endl;\n"
        "    cout << \"Time: \" << time << \" years\" << endl;\n"
        "    cout << \"Interest: $\" << simpleInterest << endl;\n"
        "    cout << \"Total Amount: $\" << totalAmount << endl;\n"
        "    \n"
        "    return 0;\n"
        "}"
    );
    
    exercises.push_back(std::move(exercise3));

    return exercises;
}
