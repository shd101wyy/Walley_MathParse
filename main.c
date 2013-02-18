//
//  main.c
//  Walley_MathParse
//
//  Created by shd101wyy on 12-12-26.
//  Copyright (c) 2012年 shd101wyy. All rights reserved.
//

#include <stdio.h>
#include "walley_math_parser.h"
int main(int argc, char **argv){
    CURRENT_INPUT_STR="3^4*a/18";
    struct TOKEN *token=Walley_MATH_Lexica_Analysis(CURRENT_INPUT_STR);
    TOKEN_PrintTOKEN(token);
    char *postfix=WALLEY_MATH_Infix_to_Postfix(token);
    printf("%s\n",postfix);
    
    char *output=Walley_Math_Parser_Fraction(postfix);
    printf("output---> %s\n",output);
    return 0;
}

