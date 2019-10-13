# CE-1337-Derivative-Calculator
# CE/CS 1337 – PROJECT  – Wario World Economics

**Project Due:**       5/3 by 10:00PM

**KEY ITEMS:** Key items are marked in red. Failure to include or complete key items will incur additional deductions as noted beside the item.

# Submission and Grading:

- All project deliverables are to be submitted ineLearning.
- The pseudocode should be submitted as a Word or PDF document
- Zip all of the source files into a single zippedfile
  - Make sure the zipped file has a .zip extension (not .tar, .rar, .7z, etc.) (-5points)
- Projects submitted after the due date are not accepted.
- Each submitted program will be graded with a set of test cases. Each student is responsible for developing sample test cases to ensure the program works asexpected.
- **Type your name and netID in the comments at the top of all files submitted. (-5 points)** 
**Objectives:**
  - Create multiple classes that interact with eachother
  - Implement a linked list withclasses.
  - Implement overloaded operators in aclass

**Problem:** As usual, Wario is concerned about nothing other than acquiring more money. In order to maximize profits, Wario needs to use calculus to create derivatives for analysis. Unfortunately, Wario never took calculus; there wasn't much need of it in the Mushroom Kingdom. So, Wario is calling on you to help him by creating a program to create derivatives.

**Pseudocode:** Your pseudocode should describe the following items

- Main.cpp
  - Detail the step-by-step logic of the mainfunction
  - List other functions you plan tocreate
    - Determine the parameters
    - Determine the return type
    - Detail the step-by-step logic that the function will perform

- You do not need to write any pseudocode for any of the class functions

# Details

- This project must use two classes – created in review homework #7
  - Linked Listclass
  - Nodeclass
- **Linked Listclass**
    - Variables
      - Head – node pointer
    - Functions
      - Default constructor
      - Overloaded Constructor
        - Make copy of list passed in
      - Destructor
        - Delete thelist
      - Accessors andmutators
      - Overloaded operators – created in review homework #8
        - Overloaded []
          - Return the node at the givenindex
        - Overloaded << operator
          - Display the linkedlist
          - Use [] notation to treat the linked list like an array
          - See output format below
        - Overloaded ++ operator
          - Prefix notation only
          - Add node to head of linkedlist
      - Sort
        - Sort the linked list in descending order by exponent
- Nodeclass
  - Variables
    - Outer coefficient
    - Innercoefficient
    - (optional) numerator and denominator variables if doing extra creditportion
    - Exponent
    - Trigidentifier
    - Nodepointer
  - Functions
    - Defaultconstructor
    - Overloadedconstructor
    - Accessors andmutators
    - Overloaded << operator – created in review homework #8
      - Display a singlenode
      - See output format below
- All nodes will be dynamicallycreated
  - There should only be enough nodes to hold data for the current expression
  - You will have to consider a way to reuse the linked list for the next expression
- All input will be read from afile
- Each term in the expression will be stored into a node and added into the linkedlist
- Each line in the file will be a mathematical function that can be derived
- The number of lines in the file is unknown
- Each calculated derivative will be written to afile

**User Interface:** There will be no user interface for this program

**Input:** All input will be read from a file named functions.txt. Each line in the file will be a mathematical function with the following parameters:

- Consist of polynomial terms - the highest degree will be10
- May also contain trigfunctions
- Exponents will be represented by the ^ character.
- Exponents may be positive ornegative
- Do not assume that the expression will be in order from highest to lowest exponent.
- All coefficients will beintegers.
- The absence of a coefficient should be interpreted as a coefficient of1
- Trigonometric functions may havecoefficients
- The variable will always be 'x'.
- There will be spaces around the operators between terms
- If a trig function is used, there will be a space between the trig function and the coefficient of x
- **ExampleInput:**

    - 3x^2 + 2x + 1
    - x^-2 + 3x + 4 
    - 4x – x^3
    - 3sin x + cosx
    - 1 – cos4x
    - 3x^4 – 6x^2 + tan 10x

**Output:** All output will be written to a file.

- The file will be namedtxt.
- Each derivative will be written on a separate line.
- Use the ^ character to represent exponents.
- The terms of the derivative must be ordered from highest to lowest exponent
  - Trig functions should be listed at the end in the order they were encountered in the original expression
- The format of the output for each term will be the same as the input format
- Do not use double operators
  - Invalid format: 2x^2 +-3x

**EXTRA CREDIT:** Add to your program to derive functions with fractional coefficients (potential 25 extra points for this project)

- Fractional coefficients will be enclosed within parentheses (for both input andoutput)
- Each coefficient in the derivative should be simplified as much as possible
- Fractional coefficients with a denominator of 1 after derivation will be written as a whole number without parentheses
- **ExampleInput**
    - x – (1/4)sin4x
    - (3/5)x^5 – 2x^3 - 10cos10x
