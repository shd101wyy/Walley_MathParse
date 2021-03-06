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
char *Walley_Math_Parser_Decimal_For_Symbolic(char *input_str);
bool JUST_INIT_MATH_LIST=TRUE;

double Walley_Operator(double num1,double num2,char sign){
    double output=0;
    if (sign == '*') {
        output = num1*num2;
    } else if (sign == '/') {
        output = num1 / num2;
    } else if (sign == '\\') {
        output = num2 / num1;
    } else if (sign == '%'){
        output=((int)num1)%((int)num2);
    } else if (sign == '^'){
        output=pow(num1,num2);
    } else if (sign == '+') {
        output = num1 + num2;
    } else if (sign == '-') {
        output = num1-num2;
    } else {
        printf("Mistake Occurred while calling function Walley_Operator");
        output=0;
    }
    return output;
}


// put coeffiecient ahead a*3--> 3*a
// put 3+a---> a+3

char *Walley_Math_Parser_Decimal_For_Symbolic(char *input_str);

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

int find_not_in_parenthesis(char *from_str, char *find_str) {
    int index = -1;
    bool find_index = TRUE;
    int i;
    int j;
    for (i = 0; i < (int) strlen(from_str); i++) {
        // I add one code here.
        find_index=TRUE;
        if (from_str[i] == find_str[0] && charIsInParenthesis(from_str,i)==FALSE) {
            for (j = 0; j < (int) strlen(find_str); j++) {
                //printf("Find_Str[j] %c From_Str[i+j] %c\n",find_str[j],from_str[i+j]);
                if (find_str[j] != from_str[i + j]) {
                    //printf("!= %d %d\n",j,j+i);
                    find_index = FALSE;
                    break;
                }
            }
            if (find_index == TRUE) {
                //find_index = TRUE;
                //printf("Fin_Index--->%d\n",i);
                index = i;
                break;
            }
        }
    }
    return index;
}


// x---> 1 x 1
// 12--> 12 0 1
struct Math_Data changeValueToMathDate(char *value){
    struct Math_Data md;
    if (stringHasAlpha(value)==TRUE) {
        md.coefficient="1";
        md.value=value;
        md.power="1";
    }
    else{
        md.coefficient=value;
        md.value="0";
        md.power="1";
    }
    return md;
}



/*
    side:
        l: mdl / md
        r: md  / mdl
 
 
 */
void MDL_operator_for_decimal(struct Math_Data_List *mdl, struct Math_Data md, char sign, char side){
    printf("MDL_operator_for_decimal\n");
    MDL_PrintMathDataList(*mdl);
    printf("========\n");
    printf("md %s: %s: %s:\n%c\n",md.coefficient,md.value,md.power,sign);
    printf("side %c\n",side);
    printf("========\n");
    
    int length=(*mdl).length;
    if (sign=='+' || sign=='-') {
        
        int i=0;
        bool find_same_symbol=FALSE;
        for (; i<length; i++) {
            // find same symbol or number and same power
            if (strcmp((*mdl).math_data_list[i].value,md.value)==0 && strcmp((*mdl).math_data_list[i].power,md.power)==0) {
                find_same_symbol=TRUE;
                if (stringHasAlpha(md.coefficient)||stringHasAlpha((*mdl).math_data_list[i].coefficient)) {
                    printf("HAS ALPHA %s %s\n",(*mdl).math_data_list[i].coefficient,md.coefficient);
                    if (side=='l') {
                        (*mdl).math_data_list[i].coefficient=append((*mdl).math_data_list[i].coefficient, append(charToString(sign), md.coefficient));
                    }
                    // right side
                    else{
                        (*mdl).math_data_list[i].coefficient=append(md.coefficient, append(charToString(sign), (*mdl).math_data_list[i].coefficient));
                    }
                }
                else{
                (*mdl).math_data_list[i].coefficient= cleanDotZeroAfterNum(numToCString(Walley_Operator(atof((*mdl).math_data_list[i].coefficient), atof(md.coefficient), sign)));
                }
            }
        }
        if (find_same_symbol==FALSE) {
            if (sign=='-') {
                md.coefficient=append("-", md.coefficient);
            }
            MDL_addMathData(mdl, md);
        }
    }
    else if(sign=='*'||sign=='/'){
        
        if (length==1) {
            printf("Length is 1\n");
            
            //=================================
            // Calculate Coef
            if (stringHasAlpha((*mdl).math_data_list[length-1].coefficient)) {
                //  mdl b
                //  md  a
                // or
                //  md  1
                if (stringHasAlpha(md.coefficient)) {
                    // has problem here
                    (*mdl).math_data_list[length-1].value=md.value;
                    char *coef=append("(", append(md.coefficient, ")"));
                    coef=append(coef, charToString(sign));
                    coef=append(coef,append("(", append((*mdl).math_data_list[length-1].coefficient, ")")));
                    printf("coef--------> %s\n",coef);
                    char *new_coef=Walley_Math_Parser_Decimal_For_Symbolic(coef);
                    printf("new_coef----> %s\n",new_coef);
                    (*mdl).math_data_list[length-1].coefficient=new_coef;
                }
                else{
                    char *coef1=md.coefficient;
                    char *sign_string=charToString(sign);
                    if (hasSecondOrderSign(coef1)) {
                        if (coef1[0]=='('&&indexOfFinal(coef1, 0)==(int)strlen(coef1)-1) {
                            // coef1 = coef1;
                        }
                        else{
                            coef1=append("(", append(coef1, ")"));
                        }
                    }
                    if (sign=='*' && strcmp("1", md.coefficient)==0) {
                        coef1="";
                        sign_string="";
                    }
                    
                    char *coef2=(*mdl).math_data_list[length-1].coefficient;
                    if (hasSecondOrderSign(coef2)) {
                        if (coef2[0]=='('&&indexOfFinal(coef2, 0)==(int)strlen(coef2)-1) {
                            // coef2 = coef2;
                        }
                        else{
                            coef2=append("(", append(coef2, ")"));
                        }
                    }
                    
                    if (side=='r') {
                        printf("side is r\n");
                        md.coefficient=append(coef1, append(sign_string, coef2));
                        (*mdl).math_data_list[length-1].coefficient="1";
                    }
                    else{
                        printf("side is l\n");
                        if (sign=='*') {
                            printf("IT IS *\n");
                            (*mdl).math_data_list[length-1].coefficient=Walley_Math_Parser_Decimal_For_Symbolic(append(coef1, append(sign_string, coef2)));
                        }
                        else{
                            if (strcmp(coef1, "1")==0) {
                                (*mdl).math_data_list[length-1].coefficient=coef2;
                            }
                            else{
                                (*mdl).math_data_list[length-1].coefficient=append(coef2, append(sign_string, coef1));
                            }
                        }
                        md.coefficient="1";
                    }
                }
            }
            else{
                // mdl 3
                // md  a
                // or
                // md  3
                if (stringHasAlpha(md.coefficient)) {
                    char *coef1=md.coefficient;
                    if (hasSecondOrderSign(coef1)) {
                        coef1=append("(", append(coef1, ")"));
                    }
                    char *coef2=(*mdl).math_data_list[length-1].coefficient;
                    if (hasSecondOrderSign(coef2)) {
                        coef2=append("(", append(coef2, ")"));
                    }
                    if (side=='r') {
                        md.coefficient=append(coef1, append(charToString(sign), coef2));
                        (*mdl).math_data_list[length-1].coefficient="1";
                    }
                    else{
                        (*mdl).math_data_list[length-1].coefficient=append(coef2, append(charToString(sign), coef1));
                        md.coefficient="1";
                    }
                }
                else{
                    if (side=='l') {
                        (*mdl).math_data_list[length-1].coefficient=cleanDotZeroAfterNum(numToCString(Walley_Operator(atof((*mdl).math_data_list[length-1].coefficient), atof(md.coefficient), sign)));
                        md.coefficient="1";
                    }
                    else{
                            md.coefficient=cleanDotZeroAfterNum(numToCString(Walley_Operator(atof(md.coefficient),atof((*mdl).math_data_list[length-1].coefficient),sign)));
                        (*mdl).math_data_list[length-1].coefficient="1";
                    }
                }
            }
            
            //Finish Calculating Coef=================================

            printf("COEF MDL----> %s\n",(*mdl).math_data_list[length-1].coefficient);
            printf("COEF MD----> %s\n",md.coefficient);

            
            
            if (stringHasAlpha(md.value)==TRUE) {
                if (stringHasAlpha((*mdl).math_data_list[length-1].value)==TRUE) {
                    
                    if (sign=='*') {
                        char *temp_value=(*mdl).math_data_list[length-1].value;
                        struct TOKEN *tl=Walley_MATH_Lexica_Analysis(temp_value);
                        int length_of_tl=TL_length(tl);
                        
                        //a*a
                        if (length_of_tl==2) {
                            printf("## ENTER HERE\n");
                            if (strcmp(md.value,(*mdl).math_data_list[length-1].value)==0) {
                                (*mdl).math_data_list[length-1].power=cleanDotZeroAfterNum(numToCString(Walley_Operator(atof((*mdl).math_data_list[length-1].power), atof(md.power), '+')));
                            }
                            else{
                                int i=1;
                                int smallest_end_index=0;
                                bool can_be_smaller_one=FALSE;
                                for (; i<length_of_tl; i++) {
                                    if (strcmp("W_ID",tl[i].TOKEN_CLASS)==0) {
                                        if (strcmp(tl[i].TOKEN_STRING, md.value)<=0) {
                                            printf("%s %s\n",tl[i].TOKEN_STRING, md.value);
                                            smallest_end_index=tl[i].TOKEN_END+1;
                                            can_be_smaller_one=TRUE;
                                            break;
                                        }
                                    }
                                }
                                
                                if (can_be_smaller_one==FALSE) {
                                    (*mdl).math_data_list[length-1].value=append((*mdl).math_data_list[length-1].value, append("*", md.value));
                                }
                                else{
                                    
                                    (*mdl).math_data_list[length-1].value=append(substr(temp_value, 0, smallest_end_index), append("*", append(md.value,substr(temp_value, smallest_end_index, (int)strlen(temp_value)))));
                                }

                            }
                        }
                        else{
                            int i=1;
                            int smallest_end_index=0;
                            bool can_be_smaller_one=FALSE;
                            for (; i<length_of_tl; i++) {
                                if (strcmp("W_ID",tl[i].TOKEN_CLASS)==0) {
                                    if (strcmp(tl[i].TOKEN_STRING, md.value)<=0) {
                                        printf("%s %s\n",tl[i].TOKEN_STRING, md.value);
                                        smallest_end_index=tl[i].TOKEN_END+1;
                                        can_be_smaller_one=TRUE;
                                        break;
                                    }
                                }
                            }
                            
                            if (can_be_smaller_one==FALSE) {
                                (*mdl).math_data_list[length-1].value=append((*mdl).math_data_list[length-1].value, append("*", md.value));
                            }
                            else{
                               
                                    (*mdl).math_data_list[length-1].value=append(substr(temp_value, 0, smallest_end_index), append("*", append(md.value,substr(temp_value, smallest_end_index, (int)strlen(temp_value)))));
                            }
                        }
                        
                        
                        
                    }
                    else{
                        // b/b
                        if (strcmp(md.value, (*mdl).math_data_list[length-1].value)==0) {
                            (*mdl).math_data_list[length-1].power=cleanDotZeroAfterNum(numToCString(Walley_Operator(atof((*mdl).math_data_list[length-1].power), atof(md.power), '-')));
                            if (strcmp("0", (*mdl).math_data_list[length-1].power)==0) {
                                (*mdl).math_data_list[length-1].power="1";
                                (*mdl).math_data_list[length-1].coefficient=(*mdl).math_data_list[length-1].coefficient;
                                (*mdl).math_data_list[length-1].value="0";

                            }
                        }
                        else{
                            char *temp_value=(*mdl).math_data_list[length-1].value;
                            struct TOKEN *tl=Walley_MATH_Lexica_Analysis(temp_value);
                            int length_of_tl=TL_length(tl);
                            if (length_of_tl==2) {
                                printf("## ENTER HERE\n");
                                if (strcmp(md.value,(*mdl).math_data_list[length-1].value)==0) {
                                    (*mdl).math_data_list[length-1].power=cleanDotZeroAfterNum(numToCString(Walley_Operator(atof((*mdl).math_data_list[length-1].power), atof(md.power), '-')));
                                }
                                else{
                                    int i=1;
                                    int smallest_end_index=0;
                                    bool can_be_smaller_one=FALSE;
                                    for (; i<length_of_tl; i++) {
                                        if (strcmp("W_ID",tl[i].TOKEN_CLASS)==0) {
                                            if (strcmp(tl[i].TOKEN_STRING, md.value)<=0) {
                                                printf("%s %s\n",tl[i].TOKEN_STRING, md.value);
                                                smallest_end_index=tl[i].TOKEN_END+1;
                                                can_be_smaller_one=TRUE;
                                                break;
                                            }
                                        }
                                    }
                                    
                                    if (can_be_smaller_one==FALSE) {
                                        printf("Here2\n");
                                        //(*mdl).math_data_list[length-1].value=append(md.value, append("/",(*mdl).math_data_list[length-1].value));
                                        
           
                                        
                                        char *t=MD_changeMathDataToString((*mdl).math_data_list[length-1]);
                                        
                                        printf("--*** %s\n",append((*mdl).math_data_list[length-1].coefficient, append("/", t)));
                                        
                                        
                                        struct TOKEN *tl=Walley_MATH_Lexica_Analysis(append((*mdl).math_data_list[length-1].coefficient, append("/", t)));
                                        char *postfix=WALLEY_MATH_Infix_to_Postfix(tl);
                                        
                                        (*mdl).math_data_list[length-1].coefficient=Walley_Math_Parser_Decimal_For_Symbolic(postfix);
                                        
                                        printf("--*** %s\n",(*mdl).math_data_list[length-1].coefficient);
                                        
                                        (*mdl).math_data_list[length-1].value=md.value;

                                        MDL_PrintMathDataList(*mdl);
                                        
                                    }
                                    else{
                                        printf("ENTER HERE 6\n");
                                        char *append_power="";
                                        if (stringIsDigit((*mdl).math_data_list[length-1].power)) {
                                            append_power=append("^",(*mdl).math_data_list[length-1].power);
                                        }
                                        else{
                                            append_power= append("^(", append((*mdl).math_data_list[length-1].power, ")"));

                                        }
                                        if (strcmp((*mdl).math_data_list[length-1].power, "1")==0) {
                                            append_power="";
                                        }
                                        
                                        
                                        if (side=='r') {
                                            printf("side is r\n");
                                            char *value_to_be_divided=append((*mdl).math_data_list[length-1].value, append_power);
                                            printf("value_to_be_divided %s\n",value_to_be_divided);
                                            printf("calculate %s\n",append((*mdl).math_data_list[length-1].coefficient,append("/",value_to_be_divided)));
                                            (*mdl).math_data_list[length-1].coefficient=Walley_Math_Parser_Decimal_For_Symbolic(append((*mdl).math_data_list[length-1].coefficient,append("/",value_to_be_divided)));
                                            printf("coefficient %s\n",(*mdl).math_data_list[length-1].coefficient);
                                            (*mdl).math_data_list[length-1].value=md.value;
                                            (*mdl).math_data_list[length-1].power=md.power;
                                        }
                                        else{
                                            printf("side is l\n");
                                            //(*mdl).math_data_list[length-1].value=append(substr(temp_value, 0, smallest_end_index),append(append_power,append("/", append(md.value,substr(temp_value, smallest_end_index, (int)strlen(temp_value))))));
                                            (*mdl).math_data_list[length-1].coefficient=Walley_Math_Parser_Decimal_For_Symbolic(append((*mdl).math_data_list[length-1].coefficient, append("/",append(md.value,append_power))));
                                            printf("@@@@ %s\n",(*mdl).math_data_list[length-1].value);
                                            (*mdl).math_data_list[length-1].power="1";

                                            
                                        }
                                        
                                    }

                                }

                            }
                            
                            else{
                                int i=1;
                                int smallest_end_index=0;
                                bool can_be_smaller_one=FALSE;
                                for (; i<length_of_tl; i++) {
                                    if (strcmp("W_ID",tl[i].TOKEN_CLASS)==0) {
                                        if (strcmp(tl[i].TOKEN_STRING, md.value)<=0) {
                                            printf("%s %s\n",tl[i].TOKEN_STRING, md.value);
                                            smallest_end_index=tl[i].TOKEN_END+1;
                                            can_be_smaller_one=TRUE;
                                            break;
                                        }
                                    }
                                }
                                
                                if (can_be_smaller_one==FALSE) {
                                    (*mdl).math_data_list[length-1].value=append((*mdl).math_data_list[length-1].value, append("/", md.value));
                                }
                                else{
                                        (*mdl).math_data_list[length-1].value=append(substr(temp_value, 0, smallest_end_index), append("/", append(md.value,substr(temp_value, smallest_end_index, (int)strlen(temp_value)))));
                                }
                                
                            }
                        
                        }
                    }
                    
                }
                else{
                    printf("ENTER ELSE 3\n");
                    if (sign=='*') {
                        if (side=='r') {
                            (*mdl).math_data_list[length-1].coefficient=md.coefficient;
                            (*mdl).math_data_list[length-1].value=md.value;
                            (*mdl).math_data_list[length-1].power=md.power;
                        }
                        else{
                        (*mdl).math_data_list[length-1].value=md.value;
                        (*mdl).math_data_list[length-1].power=md.power;
                        }
                    }
                    else{
                        char *value_to_be_divide=MD_changeMathDataToString(md);
                        (*mdl).math_data_list[length-1].coefficient=append((*mdl).math_data_list[length-1].coefficient,append("/", value_to_be_divide));
                        
                    }
                }
            }
            else{
                printf("ENTER ELSE\n");
                if (stringHasAlpha((*mdl).math_data_list[length-1].value)==TRUE){
                    if (sign=='*') {
                        if (side=='r') {
                            (*mdl).math_data_list[length-1].coefficient=md.coefficient;
                        }
                    }
                    // /
                    else{                        
                        printf("ENTER ELSE 2\n");
                        
                        char *append_power="";
                        if (stringIsDigit((*mdl).math_data_list[length-1].power)) {
                            append_power=append("^",(*mdl).math_data_list[length-1].power);
                        }
                        else{
                            append_power= append("^(", append((*mdl).math_data_list[length-1].power, ")"));
                            
                        }
                        if (strcmp((*mdl).math_data_list[length-1].power, "1")==0) {
                            append_power="";
                        }

                        if (side=='r') {
                            printf("side is r\n");
                            char *value_to_be_divided=(*mdl).math_data_list[length-1].value;
                            value_to_be_divided=append(value_to_be_divided,append_power);
                            (*mdl).math_data_list[length-1].coefficient=append(md.coefficient, append("/",value_to_be_divided));
                            (*mdl).math_data_list[length-1].value=md.value;
                            (*mdl).math_data_list[length-1].power=md.power;
                            
                        }
                        
                        else{
                            printf("side is l\n");
                            (*mdl).math_data_list[length-1].coefficient=Walley_Math_Parser_Decimal_For_Symbolic(append((*mdl).math_data_list[length-1].coefficient, append("/", md.coefficient)));
                        }
                                                
                    }
                }
                else{
                    printf("ENTER ELSE 7\n");
                }
            }

        }
        else{
            char *temp_string=MDL_changeMathDataListToString((*mdl));
            temp_string=append("(", append(temp_string, ")"));
            (*mdl).math_data_list=(struct Math_Data*)realloc((*mdl).math_data_list, sizeof(struct Math_Data)*1);
            (*mdl).length=1;
            if (strcmp(md.value, "0")==0) {
                (*mdl).math_data_list[0].coefficient=md.coefficient;
                (*mdl).math_data_list[0].value=temp_string;
            }
            else{
                (*mdl).math_data_list[0].coefficient=temp_string;
                (*mdl).math_data_list[0].value=md.value;
            }
            
            
            
        }
    }
    // 3^a
    // a^3
    // 3^3
    else{
        // a^3
        // a^a
        if (stringHasAlpha((*mdl).math_data_list[length-1].value)==TRUE) {
            if (strcmp(md.value, "0")==0) {
                // a^3
                (*mdl).math_data_list[length-1].power=md.coefficient;
                (*mdl).math_data_list[length-1].coefficient=cleanDotZeroAfterNum(numToCString(Walley_Operator(atof((*mdl).math_data_list[length-1].coefficient), atof(md.coefficient), sign)));
            }
            else{
                (*mdl).math_data_list[length-1].power=md.value;
            }
        }
        
        // 3^a
        // 3^2
        else{
            if (strcmp(md.value, "0")==0) {

                (*mdl).math_data_list[length-1].coefficient=cleanDotZeroAfterNum(numToCString(Walley_Operator(atof((*mdl).math_data_list[length-1].coefficient), atof(md.coefficient), sign)));
            }
            else{
                (*mdl).math_data_list[length-1].power=md.value;
            }
        }
    }
    
    printf("output=======\n");
    MDL_PrintMathDataList(*mdl);
    printf("\n\n");

}

void MDL_operator_for_fraction(struct Math_Data_List *mdl, struct Math_Data md, char sign){
    
    int length=(*mdl).length;
    if (sign=='+' || sign=='-') {
        
        int i=0;
        bool find_same_symbol=FALSE;
        for (; i<length; i++) {
            // find same symbol or number
            if (strcmp((*mdl).math_data_list[i].value,md.value)==0) {
                find_same_symbol=TRUE;
                (*mdl).math_data_list[i].coefficient= Walley_Operator_For_Fraction((*mdl).math_data_list[i].coefficient, md.coefficient, sign);
            }
        }
        if (find_same_symbol==FALSE) {
            if (sign=='-') {
                md.coefficient=append("-", md.coefficient);
            }
            MDL_addMathData(mdl, md);
        }
    }
    else if(sign=='*'||sign=='/'){
        
        if (length==1) {
            (*mdl).math_data_list[length-1].coefficient=Walley_Operator_For_Fraction((*mdl).math_data_list[length-1].coefficient, md.coefficient, sign);
            if (stringHasAlpha(md.value)==TRUE) {
                if (stringHasAlpha((*mdl).math_data_list[length-1].value)==TRUE) {
                    
                    if (sign=='*') {
                        char *temp_value=(*mdl).math_data_list[length-1].value;
                        struct TOKEN *tl=Walley_MATH_Lexica_Analysis(temp_value);
                        int length_of_tl=TL_length(tl);
                        
                        //a*a
                        if (length_of_tl==2) {
                            if (strcmp(md.value,(*mdl).math_data_list[length-1].value)==0) {
                                (*mdl).math_data_list[length-1].power=Walley_Operator_For_Fraction((*mdl).math_data_list[length-1].power, md.power, '+');
                            }
                            else{
                                int i=1;
                                int smallest_end_index=0;
                                bool can_be_smaller_one=FALSE;
                                for (; i<length_of_tl; i++) {
                                    if (strcmp("W_ID",tl[i].TOKEN_CLASS)==0) {
                                        if (strcmp(tl[i].TOKEN_STRING, md.value)<=0) {
                                            smallest_end_index=tl[i].TOKEN_END+1;
                                            can_be_smaller_one=TRUE;
                                            break;
                                        }
                                    }
                                }
                                
                                if (can_be_smaller_one==FALSE) {
                                    (*mdl).math_data_list[length-1].value=append((*mdl).math_data_list[length-1].value, append("*", md.value));
                                }
                                else{
                                    
                                    (*mdl).math_data_list[length-1].value=append(substr(temp_value, 0, smallest_end_index), append("*", append(md.value,substr(temp_value, smallest_end_index, (int)strlen(temp_value)))));
                                }
                                
                            }
                        }
                        else{
                            int i=1;
                            int smallest_end_index=0;
                            bool can_be_smaller_one=FALSE;
                            for (; i<length_of_tl; i++) {
                                if (strcmp("W_ID",tl[i].TOKEN_CLASS)==0) {
                                    if (strcmp(tl[i].TOKEN_STRING, md.value)<=0) {
                                        smallest_end_index=tl[i].TOKEN_END+1;
                                        can_be_smaller_one=TRUE;
                                        break;
                                    }
                                }
                            }
                            
                            if (can_be_smaller_one==FALSE) {
                                (*mdl).math_data_list[length-1].value=append((*mdl).math_data_list[length-1].value, append("*", md.value));
                            }
                            else{
                                
                                (*mdl).math_data_list[length-1].value=append(substr(temp_value, 0, smallest_end_index), append("*", append(md.value,substr(temp_value, smallest_end_index, (int)strlen(temp_value)))));
                            }
                        }
                        
                        
                        
                    }
                    else{
                        // b/b
                        if (strcmp(md.value, (*mdl).math_data_list[length-1].value)==0) {
                            (*mdl).math_data_list[length-1].power=Walley_Operator_For_Fraction((*mdl).math_data_list[length-1].power, md.power, '-');
                            if (strcmp("0", (*mdl).math_data_list[length-1].power)==0) {
                                (*mdl).math_data_list[length-1].power="1";
                                (*mdl).math_data_list[length-1].coefficient=(*mdl).math_data_list[length-1].coefficient;
                                (*mdl).math_data_list[length-1].value="0";
                                
                            }
                        }
                        else{
                            char *temp_value=(*mdl).math_data_list[length-1].value;
                            struct TOKEN *tl=Walley_MATH_Lexica_Analysis(temp_value);
                            int length_of_tl=TL_length(tl);
                            if (length_of_tl==2) {
                                if (strcmp(md.value,(*mdl).math_data_list[length-1].value)==0) {
                                    (*mdl).math_data_list[length-1].power=Walley_Operator_For_Fraction((*mdl).math_data_list[length-1].power, md.power, '-');
                                }
                                else{
                                    int i=1;
                                    int smallest_end_index=0;
                                    bool can_be_smaller_one=FALSE;
                                    for (; i<length_of_tl; i++) {
                                        if (strcmp("W_ID",tl[i].TOKEN_CLASS)==0) {
                                            if (strcmp(tl[i].TOKEN_STRING, md.value)<=0) {
                                                smallest_end_index=tl[i].TOKEN_END+1;
                                                can_be_smaller_one=TRUE;
                                                break;
                                            }
                                        }
                                    }
                                    
                                    if (can_be_smaller_one==FALSE) {
                                        (*mdl).math_data_list[length-1].value=append((*mdl).math_data_list[length-1].value, append("/", md.value));
                                    }
                                    else{
                                        char *append_power=append("^(", append((*mdl).math_data_list[length-1].power, ")"));
                                        if (strcmp((*mdl).math_data_list[length-1].power, "1")==0) {
                                            append_power="";
                                        }
                                        (*mdl).math_data_list[length-1].value=append(substr(temp_value, 0, smallest_end_index),append(append_power,append("/", append(md.value,substr(temp_value, smallest_end_index, (int)strlen(temp_value))))));
                                        (*mdl).math_data_list[length-1].power="1";
                                    }
                                    
                                }
                                
                            }
                            
                            else{
                                int i=1;
                                int smallest_end_index=0;
                                bool can_be_smaller_one=FALSE;
                                for (; i<length_of_tl; i++) {
                                    if (strcmp("W_ID",tl[i].TOKEN_CLASS)==0) {
                                        if (strcmp(tl[i].TOKEN_STRING, md.value)<=0) {
                                            smallest_end_index=tl[i].TOKEN_END+1;
                                            can_be_smaller_one=TRUE;
                                            break;
                                        }
                                    }
                                }
                                
                                if (can_be_smaller_one==FALSE) {
                                    (*mdl).math_data_list[length-1].value=append((*mdl).math_data_list[length-1].value, append("/", md.value));
                                }
                                else{
                                    (*mdl).math_data_list[length-1].value=append(substr(temp_value, 0, smallest_end_index), append("/", append(md.value,substr(temp_value, smallest_end_index, (int)strlen(temp_value)))));
                                }
                                
                            }
                            
                        }
                    }
                    
                }
                else{
                    (*mdl).math_data_list[length-1].value=md.value;
                }
            }
            
        }
        else{
            char *temp_string=MDL_changeMathDataListToString((*mdl));
            temp_string=append("(", append(temp_string, ")"));
            (*mdl).math_data_list=(struct Math_Data*)realloc((*mdl).math_data_list, sizeof(struct Math_Data)*1);
            (*mdl).length=1;
            if (strcmp(md.value, "0")==0) {
                (*mdl).math_data_list[0].coefficient=md.coefficient;
                (*mdl).math_data_list[0].value=temp_string;
            }
            else{
                (*mdl).math_data_list[0].coefficient=temp_string;
                (*mdl).math_data_list[0].value=md.value;
            }
            
            
            
        }
    }
    // 3^a
    // a^3
    // 3^3
    else{
        // a^3
        // a^a
        if (stringHasAlpha((*mdl).math_data_list[length-1].value)==TRUE) {
            if (strcmp(md.value, "0")==0) {
                // a^3
                (*mdl).math_data_list[length-1].power=md.coefficient;
                
            }
            else{
                (*mdl).math_data_list[length-1].power=md.value;
            }
        }
        
        // 3^a
        // 3^2
        else{
            if (strcmp(md.value, "0")==0) {
                
                (*mdl).math_data_list[length-1].coefficient=Walley_Operator_For_Fraction((*mdl).math_data_list[length-1].coefficient, md.coefficient, sign);
            }
            else{
                (*mdl).math_data_list[length-1].power=md.value;
            }
        }
    }
    
}

/*
char *Walley_Math_Operator(char *value1, char *value2, char sign){
    printf("decimal %s %s %c\n",value1,value2,sign);
    
    if (JUST_INIT_MATH_LIST==TRUE) {
        printf("Enter Here\n");
        
        struct Math_Data md1=changeValueToMathDate(value1);
        MDL_addMathData(&(MDA.mdl[0]), md1);
        
        struct Math_Data md2=changeValueToMathDate(value2);
        
        MDL_operator_for_decimal(&(MDA.mdl[0]), md2, sign);
        
        JUST_INIT_MATH_LIST=FALSE;
        
        return "MDL";
    }
    
    else{
        if (strcmp(value1, "MDL")==0) {
            printf("\n\nit is MDL\n");
            struct Math_Data md2=changeValueToMathDate(value2);
            MDL_operator_for_decimal(&(MDA.mdl[0]), md2, sign);
            return "MDL";
        }
        
        
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
                    if (WALLEY_MATH_signOrder(value2[index_of_first_sign])==WALLEY_MATH_signOrder(sign)) {
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
                    else{
                        if (sign=='+') {
                            return append(value2, append(charToString(sign), value1));

                        }
                        return append(value1, append(charToString(sign), value2));
                    }
                }
                // * / % ^
                else{
                    int index_of_first_sign=indexOfFirstSign(value2);
                    if (WALLEY_MATH_signOrder(value2[index_of_first_sign])==WALLEY_MATH_signOrder(sign)&&(find_not_in_parenthesis(value2, "+")==-1&&find_not_in_parenthesis(value2, "-")==-1)) {

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
                    else{
                        value2=append("(", append(value2, ")"));
                        return append(value1,append(charToString(sign),value2));
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
                    if (WALLEY_MATH_signOrder(value1[index_of_first_sign])==WALLEY_MATH_signOrder(sign)) {
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
                    else{
                        return append(value1, append(charToString(sign), value2));
                    }
                }
                // * / % ^
                else{
                    int index_of_first_sign=indexOfFirstSign(value1);
                    if (WALLEY_MATH_signOrder(value1[index_of_first_sign])==WALLEY_MATH_signOrder(sign)&&(find_not_in_parenthesis(value1, "+")==-1&&find_not_in_parenthesis(value1, "-")==-1)) {
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
           
                if (WALLEY_MATH_signOrder(value1[index1])==WALLEY_MATH_signOrder(value2[index2]) && WALLEY_MATH_signOrder(value1[index1])==sign) {
                    char *value3=substr(value1, index1+1, (int)strlen(value1));
                    value1=substr(value1, 0, index1+1);
                    char *value4=substr(value2, 0, index2);
                    value2=substr(value2, index2, (int)strlen(value2));
                    char *value=Walley_Math_Operator(value3, value4, sign);
                    return append(value1,append(value, value2));
                }
                else{
                    return append(value1, append(charToString(sign), value2));
                }
                
                
            }
            else if(strcmp(value1, value2)==0){
                if (sign=='+') {
                    return append("2*",value1);
                }
                else
                    return "0";
            }
            return append(value1, append(charToString(sign), value2));
        }
    }
        
    }
}

char *Walley_Math_Operator_For_Fraction(char *value1, char *value2, char sign){
    printf("fraction %s %s %c\n",value1,value2,sign);
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
 */


// only supports decimal now
//// the input_str is the postfix notation

// the input now is not postfix
// this function fill format postfix
char *Walley_Math_Parser_Decimal_For_Symbolic(char *input_str){
    
    printf("input_str %s\n",input_str);
    
    struct TOKEN *tl=Walley_MATH_Lexica_Analysis(input_str);
    input_str=WALLEY_MATH_Infix_to_Postfix(tl);
    // input_str here is postfix
    
    printf("postfix %s\n",input_str);
    
    JUST_INIT_MATH_LIST=TRUE;
    struct Math_Data_Array MDA;
    MDA_init(&MDA);
    // MDA_0
    // MDA_1
    // MDA_2
    // ....
    
    
    
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
            char sign=temp_str[0];
            char *value2=Str_PopString(&stack);
            char *value1=Str_PopString(&stack);
      
            if (stack[0]==NULL) {
                return append("-", cleanDotZeroAfterNum(value2));
            }
            
            char *output_str;
            if (find(value1, "MDA_")==0 && find(value2, "MDA_")==0) {
                printf("\nThey Are Both MDA\n");
                int mda_index1=atoi(substr(value1, 4, (int)strlen(value1)));
                int mda_index2=atoi(substr(value2, 4, (int)strlen(value2)));
                
                struct Math_Data_List mdl1=MDA.mdl[mda_index1];
                struct Math_Data_List mdl2=MDA.mdl[mda_index2];
                
                int length_of_mdl2=mdl2.length;
                
                int i=0;
                for (; i<length_of_mdl2; i++) {
                    MDL_operator_for_decimal(&mdl1, mdl2.math_data_list[i], sign,'l');
                }
                
                MDA_pop(&MDA);
                MDA.mdl[mda_index1]=mdl1;
                
                output_str=value1;
            }
            else if (find(value1, "MDA_")==0) {
                int mda_index=atoi(substr(value1, 4, (int)strlen(value1)));
                printf("\n\nValue1 is MDL\n");
                struct Math_Data md2=changeValueToMathDate(value2);
                MDL_operator_for_decimal(&(MDA.mdl[mda_index]), md2, sign,'l');
                output_str=value1;
            }
            else if(find(value2, "MDA_")==0){
                printf("\n\nValue2 is MDL %s\n",value2);

                int mda_index=atoi(substr(value2, 4, (int)strlen(value2)));
                struct Math_Data md1=changeValueToMathDate(value1);
                
                                
                MDL_operator_for_decimal(&(MDA.mdl[mda_index]), md1, sign,'r');
                output_str=value2;
                
                printf("\nFinish Value2 is MDL %s\n",value2);
                
                MDL_PrintMathDataList(MDA.mdl[mda_index]);


            }
            else{
                
                struct Math_Data_List temp_mdl;
                MDL_init(&temp_mdl);
                
                struct Math_Data md1=changeValueToMathDate(value1);
                MDL_addMathData(&temp_mdl, md1);
                
                struct Math_Data md2=changeValueToMathDate(value2);
                
                MDL_operator_for_decimal(&(temp_mdl), md2, sign,'l');
                
                JUST_INIT_MATH_LIST=FALSE;
                
                MDA_addMathDataList(&MDA, temp_mdl);
                
                output_str=append("MDA_", intToCString(MDA.length-1));

            }
            printf("----> %s\n",output_str);
            Str_addString(&stack, output_str);
            
        }
        // it is symbol or number
        else{
            Str_addString(&stack, temp_str);
        }
        
        
        start=end+1;
        end=find_from_index(input_str, " ", start);
    }
    
    printf("ENDING\n");
    MDL_PrintMathDataList(MDA.mdl[0]);
    char *output=MDL_changeMathDataListToString(MDA.mdl[0]);
    if (stringIsEmpty(output)) {
        output=Str_PopString(&stack);
    }
    //return cleanDotZeroAfterNum(Str_PopString(&stack));
    return output;
}




char *Walley_Math_Parser_Fraction(char *input_str){
    struct Math_Data_Array MDA;
    MDA_init(&MDA);

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
            char sign=temp_str[0];
            char *value2=Str_PopString(&stack);
            char *value1=Str_PopString(&stack);
            
            if (stack[0]==NULL) {
                return append("-", cleanDotZeroAfterNum(value2));
            }
            
            char *output_str;
            if (find(value1, "MDA_")==0 && find(value2, "MDA_")==0) {
                printf("\nThey Are Both MDA\n");
                int mda_index1=atoi(substr(value1, 4, (int)strlen(value1)));
                int mda_index2=atoi(substr(value2, 4, (int)strlen(value2)));
                
                struct Math_Data_List mdl1=MDA.mdl[mda_index1];
                struct Math_Data_List mdl2=MDA.mdl[mda_index2];
                
                int length_of_mdl2=mdl2.length;
                
                int i=0;
                for (; i<length_of_mdl2; i++) {
                    MDL_operator_for_fraction(&mdl1, mdl2.math_data_list[i], sign);
                }
                
                MDA_pop(&MDA);
                MDA.mdl[mda_index1]=mdl1;
                
                output_str=value1;
            }
            else if (find(value1, "MDA_")==0) {
                int mda_index=atoi(substr(value1, 4, (int)strlen(value1)));
                printf("\n\nValue1 is MDL\n");
                struct Math_Data md2=changeValueToMathDate(value2);
                MDL_operator_for_fraction(&(MDA.mdl[mda_index]), md2, sign);
                output_str=value1;
            }
            else if(find(value2, "MDA_")==0){
                printf("\n\nValue2 is MDL\n");
                int mda_index=atoi(substr(value2, 4, (int)strlen(value2)));
                struct Math_Data md1=changeValueToMathDate(value1);
                MDL_operator_for_fraction(&(MDA.mdl[mda_index]), md1, sign);
                output_str=value2;
                
            }
            else{
                
                struct Math_Data_List temp_mdl;
                MDL_init(&temp_mdl);
                
                struct Math_Data md1=changeValueToMathDate(value1);
                MDL_addMathData(&temp_mdl, md1);
                
                struct Math_Data md2=changeValueToMathDate(value2);
                
                MDL_operator_for_fraction(&(temp_mdl), md2, sign);
                
                JUST_INIT_MATH_LIST=FALSE;
                
                MDA_addMathDataList(&MDA, temp_mdl);
                
                output_str=append("MDA_", intToCString(MDA.length-1));
                
            }
            printf("----> %s\n",output_str);
            Str_addString(&stack, output_str);
            
        }
        // it is symbol or number
        else{
            Str_addString(&stack, temp_str);
        }
        
        
        start=end+1;
        end=find_from_index(input_str, " ", start);
    }
    
    char *output=MDL_changeMathDataListToString(MDA.mdl[0]);
    if (stringIsEmpty(output)) {
        output=Str_PopString(&stack);
    }
    //return cleanDotZeroAfterNum(Str_PopString(&stack));
    return output;
}