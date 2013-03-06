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
    /*
    printf("%d\n",strcmp("a", "b"));
    CURRENT_INPUT_STR="a/a^3";
    //CURRENT_INPUT_STR="a+b+a/b";
    struct TOKEN *token=Walley_MATH_Lexica_Analysis(CURRENT_INPUT_STR);
    TOKEN_PrintTOKEN(token);
    char *postfix=WALLEY_MATH_Infix_to_Postfix(token);
    printf("%s\n",postfix);
     */
    
    char *output=Walley_Math_Parser_Decimal("a+3*a");
    //char *output=Walley_Math_Parser_Fraction(postfix);
    printf("## output1---> %s\n",output);

    //================ Very Important ===============
    // IT IS CORRECT TO CALCULATE TWICE

    
    return 0;
}

