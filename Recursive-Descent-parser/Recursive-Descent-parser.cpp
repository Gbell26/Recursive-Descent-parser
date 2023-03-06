// Recursive-Descent-parser

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <cctype>

using namespace std;

string splitString(char[], int&);
int countLexemes(char[]);
bool isIdentifier(string);
bool isAlphaNumRest(string);
bool isAlphaNum(char);
bool isAlpha(char);
bool isNumber(string);
bool isRest(string);
bool isNonZeroDigit(char);
bool isDigit(char);
bool isFactor(string);
bool isTerm(vector<string>);
bool isExpr(vector<string>);


int main()
{
    char userExpression[100];
    int iteration = 0;
    int currentLexeme = 0;
    int numOfLexeme = 0;
    string expressionString = "";
    vector <string> expressionList;

    cout << "enter expression ";
    cin.getline(userExpression, 100);


    // the number of lexemes in the statement is equal to the number of spaces + 1
    numOfLexeme = countLexemes(userExpression) + 1;
    for (int number = 0; number < numOfLexeme; number++) {
        expressionString = splitString(userExpression, currentLexeme);
        expressionList.push_back(expressionString);
        currentLexeme++;
    }


    // check if the input expression is valid
    if (isExpr(expressionList) == true) {
        cout << " valid";
    }
    else {
        cout << "invalid";
    }

}

string splitString(char expression[100], int& lexeme) {

    // recieve expression input and split it into strings separated by space. 
    string expressionString;
    // add each character to the string until reaching a whitespace or a null character ie end of the expression
    while (expression[lexeme] != ' ' && expression[lexeme] != '\0') {
        expressionString += expression[lexeme];
        // move to the next character
        lexeme++;
    }

    return expressionString;
}

int countLexemes(char expression[100]) {
    int numOfLexemes = 0;
    int number = 0;
    // count the number of whitespaces until getting to the end of the expression
    // this will return 1 less than the number of lexemes in the expression so we add one to the output of the 
    // function call
    while (expression[number] != '\0') {
        if (expression[number] == ' ') {
            numOfLexemes++;
        }
        number++;
    }

    return numOfLexemes;
}

// check whether the character is a digit 0-9
bool isDigit(char digit) {
    bool num = true;
    if (digit == '0' || digit == '1' || digit == '2' || digit == '3' || digit == '4' || digit == '5' || digit == '6' || digit == '7' || digit == '8' || digit == '9') {
        num = true;
    }
    else {
        num = false;
    }
    return num;
}

// check if the character is a non zero digit 1-9
bool isNonZeroDigit(char digit) {
    bool nonZero = true;
    if (digit == '1' || digit == '2' || digit == '3' || digit == '4' || digit == '5' || digit == '6' || digit == '7' || digit == '8' || digit == '9') {
        nonZero = true;
    }
    else {
        nonZero = false;
    }
    return nonZero;
}

// check if string is series of digits
bool isRest(string expr) {
    bool rest = false;
    //iterate through string and if any character is not a digit return false
    for (int i = 0; i < expr.size(); i++) {
        if (isDigit(expr[i]) == false) {
            rest = false;
            break;
        }
    }
    return rest;
}

// check if string is a number 
bool isNumber(string expr) {
    bool num = true;
    //if it is a single digit return true
    if (expr.size() == 1 && isDigit(expr[0])) {
        num = true;
    }
    // if it does not have a leading 0 and is a series of digits
    else if (isNonZeroDigit(expr[0])) {
        for (int i = 0; i < expr.size(); i++) {
            if (isDigit(expr[i]) == false) {
                num = false;
                break;
            }
        }
    }
    else {
        num = false;
    }
    return num;
}


// check if a character is a letter in the alphabet
bool isAlpha(char letter) {
    bool alpha = true;
    if (isalpha(letter) == false) {
        alpha = false;
    }
    if (letter == '_') {
        alpha = true;
    }
    return alpha;
}

// check if the character is either a letter in the alphabet or a digit
bool isAlphaNum(char character) {
    if (isDigit(character) == true || isAlpha(character) == true) {
        return true;
    }
    else {
        return false;
    }
}

// check if the string is alphanumeric
bool isAlphaNumRest(string expr) {
    bool anr = true;
    //iterate through the string checking if each character is eiter a letter or a digit
    for (int i = 0; i < expr.size(); i++) {
        if (isAlphaNum(expr[0]) == false) {
            anr = false;
            break;
        }
    }
    return anr;
}

// check if the string is a valid identifier
bool isIdentifier(string expr) {
    bool identifier = true;
    //if it is a single letter than it is valid
    if (expr.length() == 1 && isAlpha(expr[0])) {
        identifier = true;
    }
    // if it starts with a letter and is followed by a series of letters or digits it is valid
    else if (isAlpha(expr[0])) {
        for (int i = 1; i < expr.size(); i++) {
            if (isAlphaNum(expr[i]) == false) {
                identifier = false;
                break;
            }
        }
    }
    else {
        identifier = false;
    }
    return identifier;
}

//check if the string is a factor
bool isFactor(string expr) {
    vector <string> exprVec;
    string insideParen;
    //if the string contains parentheses extract the contents
    if (expr[0] == '(') {
        for (int i = 1; i < expr.length()-1; i++) {
            insideParen += expr[i];
        }
        // add the contents of the parenthesis to string vector to check if contents are a valid expression
        exprVec.push_back(insideParen);

        //check if paren contents are valid expression, if they are it is a valid factor
        if (isExpr(exprVec)) {
            return true;
        }
        else {
            return false;
        }
    }
    // if it is a valid identifier or a valid number then it is a valid factor
    else if (isIdentifier(expr) || isNumber(expr)) {
        return true;
    }
    else {
        return false;
    }
}


//here it gets confusing a little
//check if the parts of the vector string is a valid term
bool isTerm(vector<string> fullExpr) {

    string first;
    string second;
    // if it is a single factor then it is valid
    if (fullExpr.size() == 1 && isFactor(fullExpr[0])) {
        return true;
    }
    //if the term contains a + get everything on either side of the + and check if they are factors
    else if (find(fullExpr.begin(), fullExpr.end(), "+") != fullExpr.end()) {
        // get everything in the vector before the + and add it to the new first vector
        for (int i = 0; i < find(fullExpr.begin(), fullExpr.end(), "+") - fullExpr.begin(); i++) {
            first += fullExpr[i];
        }  
        //get everything in the vector after the + and add it to the new second vector
        for (int i = (find(fullExpr.begin(), fullExpr.end(), "+") - fullExpr.begin()) + 1; i < fullExpr.size(); i++) {
            second += fullExpr[i];
        }
        // if the strings on both sides of the + are valid factors return true
        if (isFactor(first) && isFactor(second)) {
            return true;
        }
    }
    //if the term contains a / get everything on either side of the + and check if they are factors
    else if (find(fullExpr.begin(), fullExpr.end(), "/") != fullExpr.end()) {
        // get everything in the vector before the / and add it to the new first vector
        for (int i = 0; i < find(fullExpr.begin(), fullExpr.end(), "/") - fullExpr.begin(); i++) {
            first += fullExpr[i];
        }
        //get everything in the vector after the / and add it to the new second vector
        for (int i = find(fullExpr.begin(), fullExpr.end(), "/") - fullExpr.begin() + 1; i < fullExpr.size(); i++) {
            second += fullExpr[i];
        }
        // if the strings on both sides of the / are valid factors return true
        if (isFactor(first) && isFactor(second)) {
            return true;
        }
    }
    else {
        return false;
    }
}

// check if the expression is valid
bool isExpr(vector<string> fullExpr) {

    vector <string> first;
    vector <string> second;

    // get everything on either side of the *
    if (find(fullExpr.begin(), fullExpr.end(), "*") != fullExpr.end()) {
        for (int i = 0; i < find(fullExpr.begin(), fullExpr.end(), "*") - fullExpr.begin(); i++) {
            first.push_back(fullExpr[i]);
        }
        for (int i = (find(fullExpr.begin(), fullExpr.end(), "*") - fullExpr.begin()) + 1; i < fullExpr.size(); i++) {
            second.push_back(fullExpr[i]);
        }
        // if everything on either side of the * are valid terms the  expression is valid
        if (isTerm(first) && isTerm(second)) {
            return true;
        }
    }
    // get everything on either side of the -
    else if (find(fullExpr.begin(), fullExpr.end(), "-") != fullExpr.end()) {
        for (int i = 0; i < find(fullExpr.begin(), fullExpr.end(), "-") - fullExpr.begin(); i++) {
            first.push_back(fullExpr[i]);
        }
        for (int i = find(fullExpr.begin(), fullExpr.end(), "-") - fullExpr.begin() + 1; i < fullExpr.size(); i++) {
            second.push_back(fullExpr[i]);
        }
        // if everything on either side of the - are valid terms the  expression is valid
        if (isTerm(first) && isTerm(second)) {
            return true;
        }
    }
    // if the expression is a single valid term the expression is valid
    else if (isTerm(fullExpr)) {
        return true;
    }
    else {
        return false;
    }
}