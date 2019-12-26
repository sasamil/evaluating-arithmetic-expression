/***************************************************************************
 *   Copyright (C) 2018 by Саша Миленковић                                 *
 *   sasa.milenkovic.xyz@gmail.com                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *   ( http://www.gnu.org/licenses/gpl-3.0.en.html )                       *
 *									                                                *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <iostream>
#include <vector>
#include <stack>
#include <cstring>

#include <chrono> // Timer

using namespace std;

typedef vector<char> Operators;
typedef vector<Operators> Operators2d;

const int LSTR = 256;

// Used operators. Two levels of precedence.
const Operators precedence_1_operators = { '*', '/'};      // LRB left-to-right, binary
const Operators precedence_2_operators = { '+', '-'};      // LRB left-to-right, binary

const Operators2d operators_arrays = { precedence_2_operators, precedence_1_operators };

const int NUM_PRECEDENCES = operators_arrays.size();

//====================================================================
class Timer
{
public:
    Timer() : mStartTime(std::chrono::high_resolution_clock::now())
    {
        // mStartTime = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        Stop();
    }

private:
    void Stop()
    {
        auto endTime = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(mStartTime).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

        auto duration = end - start;
        double ms = duration * .001; // miliseconds

        std::cout << "duration: " << ms << "ms" << std::endl;
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> mStartTime;
};

//=============================================================
// utilities functions

//--------------------------------------------------------------
inline bool isOperatorFrom(const Operators& ops, const char ch) {
    for (auto it=ops.begin(); it!=ops.end(); it++)
        if(ch == *it) return true;

    return false;
}

//--------------------------------------------------------------
// find an operator in 'ops' searching from right to left
char* findOperatorIn(const Operators& ops, const char* str, char* _end)
{
    int iRParentheses = 0; // Number of encountered right parentheses.
    while (str < _end--) {
        char ch = *_end;
        switch (ch) {
            case ')':
                iRParentheses++;
                break;
            case '(':
                iRParentheses--;
                break;
            default:
                if (iRParentheses == 0 && isOperatorFrom(ops, ch)) return _end;
        }
    }

    return 0; // No operator has been found.
}

//--------------------------------------------------------------
// evaluate expression in post-order (rpn) form
int evaluate(const char* rpn)
{
    stack<int> st;

    int length = strlen(rpn);

    for (int ii = 0; ii < length; ii++) {
        const char ch = rpn[ii];
        if (ch >= '0' && ch <= '9') { // digit character
            st.push(ch - '0');
            continue;
        }

        // If it's not a digit, then it must be an operator. Apply it!
        int ival = st.top();
        st.pop();
        switch (ch) {
            case '+':
                st.top() += ival;
                break;
            case '-':
                st.top() -= ival;
                break;
            case '*':
                st.top() *= ival;
                break;
            case '/':
                st.top() /= ival;
                break;
        }
    }

    return st.top();
}

//=============================================================
// Classical approach: Shunting-Yard parsing -> rpn -> evaluation
// parsing copied from: http://www.csegeek.com/csegeek/view/tutorials/algorithms/stacks_queues/stk_que_part5.php

// get weight of operators as per precedence
// higher weight given to operators with higher precedence
// for non operators, return 0
int getWeight(char ch) {
    switch (ch) {
        case '/':
        case '*': return 2;
        case '+':
        case '-': return 1;
        default : return 0;
    }
}

// convert infix expression to postfix using a stack
void infix2postfix(const char infix[], char postfix[], int isize) {
    stack<char> s;
    int weight;
    int i = 0;
    int k = 0;

    // iterate over the infix expression
    while (i < isize) {
        char ch = infix[i];
        if (ch == '(') {
            // simply push the opening parenthesis
            s.push(ch);
            i++;
            continue;
        }
        if (ch == ')') {
            // if we see a closing parenthesis,
            // pop of all the elements and append it to
            // the postfix expression till we encounter
            // a opening parenthesis
            while (!s.empty() && s.top() != '(') {
                postfix[k++] = s.top();
                s.pop();

            }
            // pop off the opening parenthesis also
            if (!s.empty()) {
                s.pop();
            }
            i++;
            continue;
        }
        weight = getWeight(ch);
        if (weight == 0) {
            // we saw an operand
            // simply append it to postfix expression
            postfix[k++] = ch;

        }
        else {
            // we saw an operator
            if (s.empty()) {
                // simply push the operator onto stack if
                // stack is empty
                s.push(ch);
            }
            else {
                // pop of all the operators from the stack and
                // append it to the postfix expression till we
                // see an operator with a lower precedence that
                // the current operator
                while (!s.empty() && s.top() != '(' && weight <= getWeight(s.top())) {
                    postfix[k++] = s.top();
                    s.pop();

                }
                // push the current operator onto stack
                s.push(ch);
            }
        }
        i++;
    }
    // pop of the remaining operators present in the stack
    // and append it to postfix expression
    while (!s.empty()) {
        postfix[k++] = s.top();
        s.pop();
    }
    postfix[k] = 0; // null terminate the postfix expression
}


//=============================================================
// new rpn-string creating + evaluation (C-like character strings)

//--------------------------------------------------------------
void _rpn_(const char* str, char* _end, int indexops, char* result, int* resultit)
{
    if (str + 1 == _end) {
        result[(*resultit)++]=*str;
        return;
    }

    // Traverse the arrays of operators (with different precedence) and do reordering for the matching one
    for (int jj = indexops; jj < NUM_PRECEDENCES; jj++) {
        auto const& ops = operators_arrays[jj];
        char* position = findOperatorIn(ops, str, _end);
        if (position != 0) {
            _rpn_(str, position, jj, result, resultit);
            _rpn_(position + 1, _end, jj+1, result, resultit);
            result[(*resultit)++]=*position;
            return;
        }
    }

    _rpn_(str+1, _end-1, 0, result, resultit);
}

//--------------------------------------------------------------
// external rpn
inline void rpn_make(char* str, const int length, char* result)
{
    int resultit = 0;

    // Parsing and reordering the expression:
    _rpn_(str, str + length, 0, result, &resultit);
    result[resultit]=0;
}


//=============================================================
// new algorithm, in place evaluation

//--------------------------------------------------------------
int apply_operator(const int left, const int right, const char ch)
{
    switch (ch) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
        default: return (ch - '0');
    }
}

//--------------------------------------------------------------
int eval_inplace(const char* start, char* _end, int indexops)
{
    if (start + 1 == _end) return *start - '0';

    // Search for an operator (with different precedence) and make node for the matching one
    for (int jj = indexops; jj < NUM_PRECEDENCES; jj++) {
        auto const& ops = operators_arrays[jj];
        char* position = findOperatorIn(ops, start, _end);
        if (position != 0) {
            return apply_operator(eval_inplace(start, position,  jj),
                                  eval_inplace(position+1, _end, jj+1),
                                  *position);
        }
    }

    return eval_inplace(++start, --_end, 0);
}



//==============================================================
int main(/*int argc, char* argv[]*/)
{
    const char* input_expression1 = "1*(2+3-4*5)+(6-7*8)"; // -65
    const char* input_expression2 = "8*(1*(2+3*(4-5)+6)-7)+5"; // -11
    const char* input_expression3 = "(1+2*8-3)/(3-4-5)*(6-7*8/3+0)"; // 14 / -6 * -12 = 24
    const char* input_expression4 = "1+2*3-4*6/5+7*8/9+0"; // 9

    char infix[LSTR];
    char postfix[LSTR];
    int sizeinfix;

    const int NUM_LOOPS = 100000;

//-----------------------------
// Shunting-Yard + evaluation
    {
        Timer timer;
        //char infix[LSTR];
        //char postfix[LSTR];
        strncpy(infix, input_expression1, LSTR);
        sizeinfix = strlen(infix);
        for (int ii = 0; ii < NUM_LOOPS; ii++) {
            infix2postfix(infix, postfix, sizeinfix);
            evaluate(postfix);
        }

        strncpy(infix, input_expression2, LSTR);
        sizeinfix = strlen(infix);
        for (int ii = 0; ii < NUM_LOOPS; ii++) {
            infix2postfix(infix, postfix, sizeinfix);
            evaluate(postfix);
        }

        strncpy(infix, input_expression3, LSTR);
        sizeinfix = strlen(infix);
        for (int ii = 0; ii < NUM_LOOPS; ii++) {
            infix2postfix(infix, postfix, sizeinfix);
            evaluate(postfix);
        }

        strncpy(infix, input_expression4, LSTR);
        sizeinfix = strlen(infix);
        for (int ii = 0; ii < NUM_LOOPS; ii++) {
            infix2postfix(infix, postfix, sizeinfix);
            evaluate(postfix);
        }

    }
    cout << endl;

//-----------------------------
// rpn in-place + evaluation
    {
        Timer timer;

        strncpy(infix, input_expression1, LSTR);
        sizeinfix = strlen(infix);
        for (int ii = 0; ii < NUM_LOOPS; ii++) {
            rpn_make(infix, sizeinfix, postfix);
            evaluate(postfix);
        }

        strncpy(infix, input_expression2, LSTR);
        sizeinfix = strlen(infix);
        for (int ii = 0; ii < NUM_LOOPS; ii++) {
            rpn_make(infix, sizeinfix, postfix);
            evaluate(postfix);
        }

        strncpy(infix, input_expression3, LSTR);
        sizeinfix = strlen(infix);
        for (int ii = 0; ii < NUM_LOOPS; ii++) {
            rpn_make(infix, sizeinfix, postfix);
            evaluate(postfix);
        }

        strncpy(infix, input_expression4, LSTR);
        sizeinfix = strlen(infix);
        for (int ii = 0; ii < NUM_LOOPS; ii++) {
            rpn_make(infix, sizeinfix, postfix);
            evaluate(postfix);
        }

    }
    cout << endl;

//-----------------------------
// new algorithm in-place evaluation
    {
        Timer timer;

        strncpy(infix, input_expression1, LSTR);
        sizeinfix = strlen(infix);
        for (int ii = 0; ii < NUM_LOOPS; ii++) {
            eval_inplace(infix, infix + sizeinfix, 0);
        }

        strncpy(infix, input_expression2, LSTR);
        sizeinfix = strlen(infix);
        for (int ii = 0; ii < NUM_LOOPS; ii++) {
            eval_inplace(infix, infix + sizeinfix, 0);
        }

        strncpy(infix, input_expression3, LSTR);
        sizeinfix = strlen(infix);
        for (int ii = 0; ii < NUM_LOOPS; ii++) {
            eval_inplace(infix, infix + sizeinfix, 0);
        }

        strncpy(infix, input_expression4, LSTR);
        sizeinfix = strlen(infix);
        for (int ii = 0; ii < NUM_LOOPS; ii++) {
            eval_inplace(infix, infix + sizeinfix, 0);
        }

    }

    cout << endl;
    cout << "eval_inplace(expr1) = " << eval_inplace(input_expression1, const_cast<char*>(input_expression1 + strlen(input_expression1)), 0) << endl;
    cout << "eval_inplace(expr2) = " << eval_inplace(input_expression2, const_cast<char*>(input_expression2 + strlen(input_expression2)), 0) << endl;
    cout << "eval_inplace(expr3) = " << eval_inplace(input_expression3, const_cast<char*>(input_expression3 + strlen(input_expression3)), 0) << endl;
    cout << "eval_inplace(expr4) = " << eval_inplace(input_expression4, const_cast<char*>(input_expression4 + strlen(input_expression4)), 0) << endl;

    return 0;
}
