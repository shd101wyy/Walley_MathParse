//
//  walley_math_parser.h
//  Walley_MathParse
//
//  Created by shd101wyy on 13-2-14.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_math_infix_to_postfix.h"

/*
 Example
 The infix expression "5 + ((1 + 2) * 4) − 3" can be written down like this in RPN:
 
 5 1 2 + 4 * + 3 -
 The expression is evaluated left-to-right, with the inputs interpreted as shown in the following table (the Stack is the list of values the algorithm is "keeping track of" after the Operation given in the middle column has taken place):
 
 Input	Operation	Stack	Comment
 5	Push value	5
 1	Push value	1
 5
 2	Push value	2
 1
 5
 +	Add	3
 5	Pop two values (1, 2) and push result (3)
 4	Push value	4
 3
 5
 *	Multiply	12
 5	Pop two values (3, 4) and push result (12)
 +	Add	17	Pop two values (5, 12) and push result (17)
 3	Push value	3
 17
 −	Subtract	14	Pop two values (17, 3) and push result (14)
 Result	(14)
 When a computation is finished, its result remains as the top (and only) value in the stack; in this case, 14.
 
 The above example could be rewritten by following the "chain calculation" method described by HP for their series of RPN calculators:[4]
 
 As was demonstrated in the Algebraic mode, it is usually easier (fewer keystrokes) in working a problem like this to begin with the arithmetic operations inside the parentheses first.
 
 1 2 + 4 * 5 + 3 −
 
 */


// put coeffiecient ahead a*3--> 3*a
// put 3+a---> a+3

char *Walley_Math_Parser_Decimal(char *input_str);

bool stringHasSign(char *input_str){
    int i=0;
    int length=(int)strlen(input_str);
    for (; i<length; i++) {
        if (isSign(input_str[i])) {
            return TRUE;
        }
    }
    return FALSE;
}

// x+4
// 012
// return 1
int indexOfFirstSign(char *input_str){
    int i=0;
    int length=(int)strlen(input_str);
    for (; i<length; i++) {
        if (isSign(input_str[i])) {
            return i;
        }
    }
    return -1;
}
int indexOfFirstSignFromBehind(char *input_str){
    int length=(int)strlen(input_str);
    int i=length-1;

    for (; i>=0; i--) {
        if (isSign(input_str[i])) {
            return i;
        }
    }
    return -1;
}



char *Walley_Math_Operator(char *value1, char *value2, char sign){
    printf("%s %s %c\n",value1,value2,sign);
    if (stringIsDigit(value1)==TRUE) {
        
        // both value1 and value2 is digit
        if (stringIsDigit(value2)==TRUE) {
            return cleanDotZeroAfterNum(numToCString(Walley_Operator(atof(value1), atof(value2), sign)));
        }
        else{
            //3 * a
            //3 * 3*a
            //5 + 3*a
            //4 + 5+3*a
            
            // may not even enter this if
            if (stringHasSign(value2)==TRUE) {
                // + -
                if (sign=='+'||sign=='-') {
                    int index_of_first_sign=indexOfFirstSign(value2);
                    if (value2[index_of_first_sign]=='+'||value2[index_of_first_sign]=='-') {
                        char *value3=substr(value2, 0, index_of_first_sign);
                        value2=substr(value2, index_of_first_sign, (int)strlen(value2));
                        value3=Walley_Math_Operator(value1, value3, sign);
                        return append(value3, value2);
                    }
                    else{
                        return append(value2, append(charToString(sign), value1));
                    }
                }
                // * / % ^
                else{
                    int index_of_first_sign=indexOfFirstSign(value2);
                    if (value2[index_of_first_sign]=='*'||value2[index_of_first_sign]=='/'||value2[index_of_first_sign]=='%') {
                        char *value3=substr(value2, 0, index_of_first_sign);
                        value2=substr(value2, index_of_first_sign, (int)strlen(value2));
                        value3=Walley_Math_Operator(value1, value3, sign);
                        return append(value3, value2);
                    }
                    else{
                        value2=append("(", append(value2, ")"));
                        return append(value1, append(charToString(sign), value2));
                    }

                }
            }
            else{
                return append(value1, append(charToString(sign), value2));
            }
        }
        
    }
    
    else{
        //3*a 4 *
        if (stringIsDigit(value2)==TRUE) {
            //a   + 5
            //3+a + 2
            
            if (stringHasSign(value1)) {
                // + -
                if (sign=='+'||sign=='-') {
                    int index_of_first_sign=indexOfFirstSignFromBehind(value1);
                    if (value1[index_of_first_sign]=='+'||value1[index_of_first_sign]=='-') {
                        char *value3=substr(value1, index_of_first_sign+1, (int)strlen(value1));
                        value1=substr(value1, 0,index_of_first_sign+1);
                        value3=Walley_Math_Operator(value3, value2, sign);
                        return append(value1, value3);
                    }
                    else{
                        return append(value1, append(charToString(sign), value2));
                    }
                }
                // * / % ^
                else{
                    int index_of_first_sign=indexOfFirstSignFromBehind(value1);
                    if (value1[index_of_first_sign]=='*'||value1[index_of_first_sign]=='/'||value1[index_of_first_sign]=='%') {
                        char *value3=substr(value1, 0, index_of_first_sign);
                        value1=substr(value1, index_of_first_sign,(int)strlen(value1));
                        value3=Walley_Math_Operator(value3, value2, sign);
                        return append(value3, value1);
                    }
                    else{
                        value1=append("(", append(value1, ")"));
                        return append(value2, append(charToString(sign), value1));
                    }
                }
            }
            
            else{
                return append(value1, append(charToString(sign), value2));

            }
        }
        //3*a * a
        else{
            if (stringHasSign(value1)&&stringHasSign(value2)) {
                int index1=indexOfFirstSignFromBehind(value1);
                int index2=indexOfFirstSign(value2);
                char *value3=substr(value1, index1+1, (int)strlen(value1));
                value1=substr(value1, 0, index1+1);
                char *value4=substr(value2, 0, index2);
                value2=substr(value2, index2, (int)strlen(value2));
                char *value=Walley_Math_Operator(value3, value4, sign);
                return append(value1,append(value, value2));
            }
            else if(strcmp(value1, value2)==0){
                if (sign=='+') {
                    return append(value1, "*2");
                }
                else
                    return "0";
            }
            return append(value1, append(charToString(sign), value2));
        }
    }
}


char *Walley_Math_Operator_For_Fraction(char *value1, char *value2, char sign){
    printf("%s %s %c\n",value1,value2,sign);
    if (stringIsDigit(value1)==TRUE) {
        
        // both value1 and value2 is digit
        if (stringIsDigit(value2)==TRUE) {
            return cleanDotZeroAfterNum(Walley_Operator_For_Fraction(value1, value2, sign));
        }
        else{
            //3 * a
            //3 * 3*a
            //5 + 3*a
            //4 + 5+3*a
            
            // may not even enter this if
            if (stringHasSign(value2)==TRUE) {
                // + -
                if (sign=='+'||sign=='-') {
                    int index_of_first_sign=indexOfFirstSign(value2);
                    if (value2[index_of_first_sign]=='+'||value2[index_of_first_sign]=='-') {
                        char *value3=substr(value2, 0, index_of_first_sign);
                        value2=substr(value2, index_of_first_sign, (int)strlen(value2));
                        value3=Walley_Math_Operator_For_Fraction(value1, value3, sign);
                        return append(value3, value2);
                    }
                    else{
                        return append(value2, append(charToString(sign), value1));
                    }
                }
                // * / % ^
                else{
                    int index_of_first_sign=indexOfFirstSign(value2);
                    if (value2[index_of_first_sign]=='*'||value2[index_of_first_sign]=='/'||value2[index_of_first_sign]=='%') {
                        char *value3=substr(value2, 0, index_of_first_sign);
                        value2=substr(value2, index_of_first_sign, (int)strlen(value2));
                        value3=Walley_Math_Operator_For_Fraction(value1, value3, sign);
                        return append(value3, value2);
                    }
                    else{
                        value2=append("(", append(value2, ")"));
                        return append(value1, append(charToString(sign), value2));
                    }
                    
                }
            }
            else{
                return append(value1, append(charToString(sign), value2));
            }
        }
        
    }
    
    else{
        //3*a 4 *
        if (stringIsDigit(value2)==TRUE) {
            //a   + 5
            //3+a + 2
            
            if (stringHasSign(value1)) {
                // + -
                if (sign=='+'||sign=='-') {
                    int index_of_first_sign=indexOfFirstSignFromBehind(value1);
                    if (value1[index_of_first_sign]=='+'||value1[index_of_first_sign]=='-') {
                        char *value3=substr(value1, index_of_first_sign+1, (int)strlen(value1));
                        value1=substr(value1, 0,index_of_first_sign+1);
                        value3=Walley_Math_Operator_For_Fraction(value3, value2, sign);
                        return append(value1, value3);
                    }
                    else{
                        return append(value1, append(charToString(sign), value2));
                    }
                }
                // * / % ^
                else{
                    int index_of_first_sign=indexOfFirstSignFromBehind(value1);
                    if (value1[index_of_first_sign]=='*'||value1[index_of_first_sign]=='/'||value1[index_of_first_sign]=='%') {
                        char *value3=substr(value1, 0, index_of_first_sign);
                        value1=substr(value1, index_of_first_sign,(int)strlen(value1));
                        value3=Walley_Math_Operator_For_Fraction(value3, value2, sign);
                        return append(value3, value1);
                    }
                    else{
                        value1=append("(", append(value1, ")"));
                        return append(value2, append(charToString(sign), value1));
                    }
                }
            }
            
            else{
                return append(value1, append(charToString(sign), value2));
                
            }
        }
        //3*a * a
        else{
            if (stringHasSign(value1)&&stringHasSign(value2)) {
                int index1=indexOfFirstSignFromBehind(value1);
                int index2=indexOfFirstSign(value2);
                char *value3=substr(value1, index1+1, (int)strlen(value1));
                value1=substr(value1, 0, index1+1);
                char *value4=substr(value2, 0, index2);
                value2=substr(value2, index2, (int)strlen(value2));
                char *value=Walley_Math_Operator(value3, value4, sign);
                return append(value1,append(value, value2));
            }
            else if(strcmp(value1, value2)==0){
                if (sign=='+') {
                    return append(value1, "*2");
                }
                else
                    return "0";
            }
            return append(value1, append(charToString(sign), value2));
        }
    }
}


// only supports decimal now
// the input_str is the postfix notation
char *Walley_Math_Parser_Decimal(char *input_str){
    int start=0;
    int end=find(input_str, " ");
    char **stack;
    Str_initStringList(&stack);
    
    while (TRUE) {
        if (end==-1) {
            break;
        }
        char *temp_str=substr(input_str, start, end);
        // it is sign
        if (isSign(temp_str[0])==TRUE) {
            char *value1=Str_PopString(&stack);
            char *value2=Str_PopString(&stack);
      
            if (stack[0]==NULL) {
                return append("-", cleanDotZeroAfterNum(value1));
            }
                        
            char *output_str=Walley_Math_Operator(value2,value1, temp_str[0]);
            Str_addString(&stack, output_str);
            
        }
        // it is symbol or number
        else{
            Str_addString(&stack, temp_str);
        }
        
        
        start=end+1;
        end=find_from_index(input_str, " ", start);
    }
    
    return cleanDotZeroAfterNum(Str_PopString(&stack));
}

char *Walley_Math_Parser_Fraction(char *input_str){
    int start=0;
    int end=find(input_str, " ");
    char **stack;
    Str_initStringList(&stack);
    
    while (TRUE) {
        if (end==-1) {
            break;
        }
        char *temp_str=substr(input_str, start, end);
        // it is sign
        if (isSign(temp_str[0])==TRUE) {
            char *value1=Str_PopString(&stack);
            char *value2=Str_PopString(&stack);
            
            
            if (stack[0]==NULL) {
                return append("-", cleanDotZeroAfterNum(value1));
            }
            
            char *output_str=Walley_Math_Operator_For_Fraction(value2,value1, temp_str[0]);
            Str_addString(&stack, output_str);
            
        }
        // it is symbol or number
        else{
            Str_addString(&stack, temp_str);
        }
        
        
        start=end+1;
        end=find_from_index(input_str, " ", start);
    }
    
    return cleanDotZeroAfterNum(Str_PopString(&stack));
}