//
//  main.c
//  Walley_MathParse
//
//  Created by shd101wyy on 12-12-26.
//  Copyright (c) 2012年 shd101wyy. All rights reserved.
//

#include <stdio.h>
#include "walley_math_parser.h"

// b+3*a*3   ->  b 3 a * 3 * +
// (b+3*a)*3 ->  b 3 a * + 3 *
// b+3*a*3+b ->  b 3 a * 3 * + b +
// a+b+a     ->  a b + a +
/*
 b 3 a * 3 * +
 
 1.  3 a 1
 
 2.  9 a 1
 
 3.  9 a 1
     1 b 1
 ==============
 b 3 a * + 3 *
 
 1. 3 a 1
 
 2. 3 a 1
    1 b 1
 
 3  9 a 1
    3 b 1
 ==============
 b 3 a * 3 * + b +

 1. 3 a 1
 2. 9 a 1
 3. 9 a 1
    1 b 1
 4  9 a 1
    2 b 1
 =============
 a b + a +
 
 1. 1 a 1
    1 b 1
 2. 2 a 1 
    1 b 1
 */

int main(int argc, char **argv){
    CURRENT_INPUT_STR="2*4/3";
    struct TOKEN *token=Walley_MATH_Lexica_Analysis(CURRENT_INPUT_STR);
    TOKEN_PrintTOKEN(token);
    char *postfix=WALLEY_MATH_Infix_to_Postfix(token);
    printf("%s\n",postfix);
    
    char *output=Walley_Math_Parser_Decimal(postfix);
    printf("output---> %s\n",output);
    
    //struct TOKEN *token2=Walley_MATH_Lexica_Analysis(output);
    //TOKEN_PrintTOKEN(token2);
    //postfix=WALLEY_MATH_Infix_to_Postfix(token2);
    //printf("%s\n",postfix);

    
    return 0;
}

