//
//  walley_math_parse.h
//  Walley_MathParse
//
//  Created by shd101wyy on 12-12-26.
//  Copyright (c) 2012年 shd101wyy. All rights reserved.
//

#include "walley_core.h"
char *eval_for_decimal_with_alpha_for_fraction(char *input_str);


//calculate 9/2/4--->9/8
char *calculate_for_division_for_fraction(char *input_str){
    char *temp_input_str=changeOperatorStrToOriginalForWhoStr(input_str);
    if (stringIsDigit(temp_input_str)||stringIsFraction(temp_input_str)) {
        return input_str;
    }
    else{
        if (find(temp_input_str, "+")==-1&&find(temp_input_str, "-")==-1&&find(temp_input_str, "*")==-1&&find(temp_input_str, "^")==-1&&find(temp_input_str, "%")==-1) {
            //int num_of_division=count_str(temp_input_str, "/");
            int index_of_temp_input_str=find(temp_input_str, "/");
            char *numerator=substr(temp_input_str, 0, index_of_temp_input_str);
            //int first=index_of_temp_input_str;
            char *denominator=substr(temp_input_str, index_of_temp_input_str+1, (int)strlen(temp_input_str));
            denominator=replace(denominator, "#LEFT#","");
            denominator=replace(denominator, "#RIGHT#", "");
            denominator=replace(denominator, "/", "*");
            denominator=eval_for_decimal_with_alpha(denominator);
            denominator=append("#LEFT#", append(denominator, "#RIGHT#"));
            char *output=append(numerator, append("/", denominator));
            return changeOperatorToStrForWhoStr(output);
        }
        else{
            int index_of_temp_input_str=find(temp_input_str, "/");
            if (index_of_temp_input_str==-1) {
                return input_str;
            }
            else{
                char *numerator=substr(temp_input_str, 0, index_of_temp_input_str);
                //int first=index_of_temp_input_str;
                char *denominator=substr(temp_input_str, index_of_temp_input_str+1, (int)strlen(temp_input_str));
                denominator=replace(denominator, "#LEFT#","");
                denominator=replace(denominator, "#RIGHT#", "");
                denominator=replace(denominator, "/", "*");
                denominator=eval_for_decimal_with_alpha(denominator);
                
                if (stringHasAlpha(denominator)==FALSE&&isdigit(numerator[0])) { // 6*x*x/8
                    char *numerator_num=substr(temp_input_str, 0, find(temp_input_str, "*")); //6
                    char *rest=substr(temp_input_str, find(temp_input_str, "*"),index_of_temp_input_str);//*x*x
                    char *simplified=simplify_fraction(numerator_num, denominator);
                    //   3/4
                    if (stringIsFraction(simplified)) {
                        char *temp_numerator=numerator_of_fraction(simplified);
                        char *temp_denominator=denominator_of_fraction(simplified);
                        char *output=append(temp_numerator, append(rest, append("/", temp_denominator)));
                        output=changeOperatorToStrForWhoStr(output);
                        return output;
                    }
                    // 3
                    else{
                        char *output=append(simplified, rest);
                        return changeOperatorToStrForWhoStr(output);
                    }
                }
                else{
                    denominator=append("#LEFT#", append(denominator, "#RIGHT#"));
                
                    char *output=append(numerator, append("/", denominator));
                    return changeOperatorToStrForWhoStr(output);
                }
            }
        }
    }
}

//clean_code  1/(4)--->1/4  1/(x+4)--->1/(x+4)
char *clean_math_output_for_fraction(char *input_str){
    int num_of_bracket=count_str(input_str, "(");
    int i=0;
    for (; i<num_of_bracket; i++) {
        int right=find(input_str, ")");
        int left=right;
        for (; left>=0; left--) {
            if (input_str[left]=='(') {
                break;
            }
        }
        
        char *string_in_bracket=substr(input_str, left+1, right);
        char *replace_str=substr(input_str, left, right+1);
        // can not remove bracket
        if (stringHasAlpha(string_in_bracket)) {
            input_str=replace_from_index_to_index(input_str, replace_str, append("#LEFT#", append(string_in_bracket, "#RIGHT#")), left, right+1);
        }
        // can remove bracket
        else{
            input_str=replace_from_index_to_index(input_str, replace_str, string_in_bracket, left, right+1);
        }
        
    }
    input_str=replace(input_str,"#LEFT#","(");
    input_str=replace(input_str,"#RIGHT#",")");
    return input_str;
}

char *eval_CalculatePowerAtFirst_with_alpha_for_fraction(char *input_str){
    int count_of_power=count_str(input_str, "^");
    int i=0;
    for (i=0; i<count_of_power; i++) {
        //printf("enter\n");
        int index_of_power=find(input_str, "^");
        // 2^3 (2)^3 2^(3) (2)^(3)
        int left=0;
        int right=0;
        
        
        // Find Left.
        //(2)^3
        if (input_str[index_of_power-1]==')') {
            int num_of_right=0;
            int num_of_left=0;
            int j=index_of_power-1;
            for (j=index_of_power-1; j>=0; j--) {
                if (input_str[j]==')') {
                    num_of_right++;
                    continue;
                }
                if (input_str[j]=='(') {
                    num_of_left++;
                    if (num_of_left==num_of_right) {
                        left=j;
                        break;
                    }
                    else
                        continue;
                }
            }
            
        }
        //2^3
        else{
            int j=index_of_power-1;
            for (j=index_of_power-1; j>=0; j--) {
                if (isdigit(input_str[j])==FALSE&&isalpha(input_str[j])==FALSE&&input_str[j]!='_') {
                    left=j+1;
                    break;
                }
                if (j==0) {
                    left=0;
                    break;
                }
            }
            
        }
        
        //2^(3)
        if (input_str[index_of_power+1]=='(') {
            int num_of_left=0;
            int num_of_right=0;
            int j=index_of_power+1;
            for (; j<(int)strlen(input_str); j++) {
                if (input_str[j]=='(') {
                    num_of_left++;
                    continue;
                }
                if (input_str[j]==')') {
                    num_of_right++;
                    if (num_of_left==num_of_right) {
                        right=j;
                        break;
                    }
                    else
                        continue;
                }
            }
        }
        //2^2
        else{
            int j=index_of_power+1;
            for (j=index_of_power+1; j<(int)strlen(input_str); j++) {
                if (isdigit(input_str[j])==FALSE&&isalpha(input_str[j])==FALSE&&input_str[j]!='_') {
                    right=j-1;
                    break;
                }
                if(j==(int)strlen(input_str)-1){
                    right=(int)strlen(input_str)-1;
                    break;
                }
            }
            
        }
        char *replace_str=substr(input_str, left, right+1);
        char *left_str=substr(input_str, left, index_of_power);
        char *right_str=substr(input_str, index_of_power+1, right+1);
        
        left_str=eval_for_decimal_with_alpha_for_fraction(left_str);
        right_str=eval_for_decimal_with_alpha_for_fraction(right_str);
        char *with_str="";//numToCString(pow(atof(left_str), atof(right_str)));
        printf("left %s right %s\n",left_str,right_str);
        // 3^4
        if (stringIsDigit(left_str)&&stringIsDigit(right_str)) {
            with_str=numToCString(pow(atof(left_str), atof(right_str)));
            with_str=cleanDotZeroAfterNum(with_str);
        }
        else if(stringHasAlpha(left_str)||stringHasAlpha(right_str)){
            bool left_str_has_alpha=stringHasAlpha(left_str);
            bool right_str_has_alpha=stringHasAlpha(right_str);
            if (left_str[0]!='('&&(left_str_has_alpha||stringIsFraction(left_str))&&stringIsAlpha(left_str)==FALSE&&stringIsDigit(left_str)==FALSE) {
                with_str=append("(", append(left_str, ")^("));
            }
            else{
                with_str=append(left_str, "^");
            }
            if (right_str[0]!='('&&(right_str_has_alpha||stringIsFraction(right_str))&&stringIsAlpha(left_str)==FALSE&&stringIsDigit(right_str)==FALSE) {
                with_str=append(with_str, append("(", append(right_str, ")")));
            }
            else{
                with_str=append(with_str, right_str);
            }

        }
        else{
            char *temp_with_var=numToCString(pow((double)atof(eval(left_str)), (double)atof(eval(right_str))));
            int temp_length1=(int)strlen(temp_with_var);
            temp_with_var=cleanDotZeroAfterNum(temp_with_var);
            int temp_length2=(int)strlen(temp_with_var);
            printf("temp_with_var %s\n",temp_with_var);
            if (atof(temp_with_var)==(int)atof(temp_with_var)) {
                with_str=temp_with_var;
            }
            // there maybe some mistake
            else if (temp_length1-temp_length2>=5){
                with_str=temp_with_var;
            }
            else{
                // this code below may affect efficiency....
                with_str=eval_for_fraction_root_power(input_str);
            }
            
            printf("with_str--->%s\n",with_str);
        }
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, left, right+1);
        
        
    }
    return input_str;
}

// it does not support + and - now
char* Walley_Operator_with_alpha_for_fraction(char* num1_str,char* num2_str,char sign){
    // after running codes..
    // it may have input_str like
    // x#time#3#time#y#divide#4
    
    char *output_output="";
    
    // or
    // if has alpha like 3*x, then return 3#time#x
    bool num1_is_digit=stringIsDigit(num1_str);
    bool num2_is_digit=stringIsDigit(num2_str);
    if (num1_is_digit==TRUE&&num2_is_digit==TRUE) {
        if (sign!='/') {
            //return cleanDotZeroAfterNum(numToCString(Walley_Operator(atof(num1_str), atof(num2_str), sign)));
            output_output=cleanDotZeroAfterNum(numToCString(Walley_Operator(atof(num1_str), atof(num2_str), sign)));

        }
        else{
            //return changeOperatorToStrForWhoStr(Walley_Operator_For_Fraction(num1_str, num2_str, sign));
            output_output=changeOperatorToStrForWhoStr(Walley_Operator_For_Fraction(num1_str, num2_str, sign));;
        }
    }
    else{
        if (find(num1_str, "#")==-1) {
            char *output;
            //always put number ahead...
            //3*x
            if (num1_is_digit==TRUE && num2_is_digit==FALSE) {
                
                output=append(num1_str, changeOperatorToStr(sign));
                output=append(output, num2_str);
            }
            //x*3
            else if(num1_is_digit==FALSE && num2_is_digit==TRUE){
                if (sign!='^'&&sign!='/') {
                    output=append(num2_str, changeOperatorToStr(sign));
                    output=append(output, num1_str);
                }
                else{
                    output=append(num1_str, changeOperatorToStr(sign));
                    output=append(output, num2_str);
                    
                }
            }
            //x*y
            else{
                output=append(num1_str, changeOperatorToStr(sign));
                output=append(output, num2_str);
                
            }
            //return output;
            output_output=output;
        }
        // x#time#3#time#y/4
        else{
            // num1_str 3#time#x ; num2 x or 3 ; sign *
            if (isdigit(num1_str[0])) {
                if (num2_is_digit) {
                    int index=find(num1_str, "#");
                    char *num=substr(num1_str, 0, index);
                    char *replace_str=num;
                    char *with_str=Walley_Operator_with_alpha_for_fraction(num, num2_str, sign);
                    //return replace_from_index_to_index(num1_str, replace_str, with_str, 0, index+1);
                    output_output=replace_from_index_to_index(num1_str, replace_str, with_str, 0, index+1);
                }
                else{
                    char *output=append(num1_str, changeOperatorToStr(sign));
                    output=append(output, num2_str);
                    //return output;
                    output_output=output;
                }
                
            }
            else{
                if (num2_is_digit) {
                    if (sign!='^'&&sign!='/') {
                        char *output=append(num2_str, changeOperatorToStr(sign));
                        output=append(output, num1_str);
                        //return output;
                        output_output=output;
                    }
                    else{
                        char *output=append(num1_str, changeOperatorToStr(sign));
                        output=append(output, num2_str);
                        //return output;
                        output_output=output;
                    }
                }
                else{
                    int index=find(num1_str, "#");
                    char *num=substr(num1_str, 0, index);
                    if (strcmp(num, num2_str)==0) {
                        //return replace_from_index_to_index(num1_str, num, "1", 0, index+1);
                        if (sign=='/') {
                            output_output=replace_from_index_to_index(num1_str, num, "1", 0, index+1);
                        }
                        if (sign=='*') {
                            output_output=replace_from_index_to_index(num1_str, num, append(num, append("#time#",num)), 0, index+1);

                        }
                    }
                    else{
                    
                        char *output=append(num1_str, changeOperatorToStr(sign));
                        output=append(output, num2_str);
                        //return output;
                        output_output=output;
                    }
                }
            }
            
        }
    }
    if (sign=='/') {
        output_output=calculate_for_division_for_fraction(output_output);
    }
    return output_output;
    
}

char *countFirstOrderSignAndChangeTheStrOnlyOnce_with_alpha_for_fraction(char *input_str){
    int i=0;
    int j=0;
    int begin_of_first_num=0;
    int end_of_second_num=(int)strlen(input_str)-1;
    int place_of_first_order_sign;
    
    char *num1_str;
    char *num2_str;
    
    for(;i<(int)strlen(input_str);i++){
        if(isdigit(input_str[i])==TRUE){
            continue;
        }
        
        if(input_str[i]=='+'||input_str[i]=='-'){
            begin_of_first_num=i+1;
        }
        
        if(isFirstOrderSign(input_str[i])==TRUE) {
            j = i + 1;
            place_of_first_order_sign=i;
            
            for (; j < (int) strlen(input_str); j++) {
                // I just change this code here 9/17/2012
                if (isSign(input_str[j]) == TRUE && j!=i+1) {
                    end_of_second_num=j-1;
                    break;
                }
                if (j == (int) strlen(input_str) - 1) {
                    end_of_second_num=j;
                    break;
                }
            }
            num1_str=substr(input_str,begin_of_first_num,place_of_first_order_sign);
            num2_str=substr(input_str,place_of_first_order_sign+1,end_of_second_num+1);
            
            
            char* output_str=Walley_Operator_with_alpha_for_fraction(num1_str,num2_str,input_str[i]);
            
            char *output_temp=malloc(sizeof(char)*1000);
            
            if(begin_of_first_num==0){
                strcat(output_temp,output_str);
                if(end_of_second_num!=(int)strlen(input_str)-1){
                    strcat(output_temp,substr(input_str,end_of_second_num+1,(int)strlen(input_str)));
                }
            }  else  {
                strcat(output_temp,substr(input_str,0,begin_of_first_num));
                if(end_of_second_num==(int)strlen(input_str)-1)
                    strcat(output_temp,output_str);
                else{
                    strcat(output_temp,output_str);
                    strcat(output_temp,substr(input_str,end_of_second_num+1,(int)strlen(input_str)));
                }
            }
            input_str=(char*)output_temp;
            break;
        }
    }
    
    return input_str;
}

char* countFromExpression_with_alpha_for_fraction(char *var_value) {
    
    if (hasSign(var_value) == FALSE){
        //printf("$$$$$$ %s\n",var_value);
        return var_value;
    }
    else {
        
        if (var_value[0]!='0') {
            if (var_value[0]=='-') {
                var_value=append("0",var_value);
            }else{
                var_value=append("0+", var_value);
            }
            var_value=append(var_value, "+0");
        }
        
        
        double output;
        
        char *my_output_str="";
        
        char *input = var_value;
        //char sign;
        
        int i = 0;
        int j = 0;
        int temp = 0;
        
        double num1;
        double num2;
        double previous_num;
        bool begin = FALSE;
        
        char *num1_str;
        char *num2_str;
        
        for (; i < strlen(input); i++) {
            if (isSign(input[i]) == TRUE && input[i]!='/') {
                num1_str = substr(input, temp, i);
                //printf("sign %c\n",input[i]);
                //printf("num1_str %s\n",num1_str);
                j = i + 1;
                int final_place=0; // for a+b+4--->final_place=3
                for (; j < (int) strlen(input); j++) {
                    if (input[i]=='+'&&input[i+1]=='+') {
                        num2_str="1";
                        i++;
                        break;
                    }
                    if (input[i]=='-'&&input[i+1]=='-') {
                        num2_str="1";
                        i++;
                        break;
                    }
                    
                    if (isSign(input[j]) == TRUE) {
                        num2_str = substr(input, i + 1, j);
                        final_place=j;
                        break;
                    }
                    if (j == (int) strlen(input) - 1) {
                        num2_str = substr(input, i + 1, j + 1);
                        final_place=j+1;
                        break;
                    }
                }
                //temp=i;
                //printf("/n Begin %d\n",begin);
                //printf("num1_str %s, num2_str %s, previous_num %s\n",num1_str,num2_str,numToCString(previous_num));
                //printf("my_output_str %s\n",my_output_str);
                
                num1 = atof(num1_str);
                num2 = atof(num2_str);
                //printf("num1 %f, num2 %f, input[i] %c\n",num1,num2,input[i]);
                if (begin == FALSE) {
                    //####################################################
                    // I plan to add new code here\n
                    
                    if(stringIsDigit(num1_str)==FALSE){
                        // a+b+3+4
                        if (stringIsDigit(num2_str)==FALSE) {
                            my_output_str=append(my_output_str, substr(input, 0, final_place));
                            previous_num=0;
                            output=previous_num;
                            begin=TRUE;
                        }
                        // a+3+4
                        else{
                            my_output_str=append(my_output_str, substr(input, 0, i+1)); // get a+
                            previous_num=num2;
                            output=previous_num;
                            if (input[i]=='-') {
                                previous_num=-previous_num;
                                output=previous_num;
                            }
                            begin=TRUE;
                        }
                    }
                    // num1 is not string while num2 is . like   3+a+4+5
                    else if (stringIsDigit(num2_str)==FALSE){
                        my_output_str=append(my_output_str, substr(input, i, final_place));  // get +a
                        previous_num=num1;
                        output=previous_num;
                        begin=TRUE;
                    }
                    
                    else{
                        
                        
                        //#####################################################
                        
                        
                        previous_num = Walley_Operator(num1, num2, input[i]);
                        output = previous_num;
                        begin = TRUE;
                        
                        //my_output_str=append(my_output_str, "+");
                        //my_output_str=append(my_output_str, numToCString(output));
                        
                    }
                }
                // Begin =TRUE
                else {
                    
                    // I add new code here to solve a+3+5 like problem
                    //#####################################################
                    // 3+4+a+5-->7+a+5
                    if (stringIsDigit(num2_str)==FALSE) {
                        my_output_str=append(my_output_str, substr(input, i, final_place)); // get +a
                        //previous_num=num1;
                        output=previous_num;
                    }
                    else{
                        //####################################################
                        
                        previous_num = Walley_Operator(previous_num, num2, input[i]);
                        output = previous_num;
                        
                    }
                }
            }
        }
        //printf("END %s\n",my_output_str);
        char *temp_output=numToCString(output);
        if (output!=0) {
            if (temp_output[0]=='-') {
                my_output_str=append(my_output_str, temp_output);
                
            }
            else{
                my_output_str=append(my_output_str, "+");
                my_output_str=append(my_output_str, temp_output);
                
            }
        }
        my_output_str=cleanDotZeroAfterNum(my_output_str);
        //printf("my_output_str is |%s|\n",my_output_str);
        if (my_output_str[0]=='+') {
            my_output_str=substr(my_output_str, 1, (int)strlen(my_output_str));
        }
        return my_output_str;
    }
}


// calculate outside parenthesis
char *eval_simple_str_with_alpha_for_fraction(char *input_str){
    // at this place, eg 3*x+5.
    // I will replace 3*x with 3#time#x    #time# ---> *
    while(hasFirstOrderSignExist(input_str)==TRUE){
        input_str=countFirstOrderSignAndChangeTheStrOnlyOnce_with_alpha_for_fraction(input_str);
    }
    //printf("$$$---> %s\n",input_str);
    // Afte running the above code.
    // input_str maybe like.
    // 3#time#x#time#y+5/3
    return countFromExpression_with_alpha_for_fraction(input_str);
}

// Calculate like (y*3*4/5^2+x)*y*3*4+x^(3/4)*y--->12*(0.48*y+x)*y+(x)^0.75*y
char *eval_for_decimal_with_alpha_for_fraction(char *input_str){
    
    
    char **replace_str_list=(char**)malloc(sizeof(char*)*10000);
    int INDEX_OF_SAVED_MATH_FUNCTIOn=0;
    while (count_str(input_str, "sin(")!=0) {
        int index=find(input_str, "sin(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(INDEX_OF_SAVED_MATH_FUNCTIOn));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[INDEX_OF_SAVED_MATH_FUNCTIOn]=append(replace_str, append("#", with_str));
        INDEX_OF_SAVED_MATH_FUNCTIOn++;
    }
    while (count_str(input_str, "cos(")!=0) {
        int index=find(input_str, "cos(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(INDEX_OF_SAVED_MATH_FUNCTIOn));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[INDEX_OF_SAVED_MATH_FUNCTIOn]=append(replace_str, append("#", with_str));
        INDEX_OF_SAVED_MATH_FUNCTIOn++;
    }
    while (count_str(input_str, "tan(")!=0) {
        int index=find(input_str, "tan(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(INDEX_OF_SAVED_MATH_FUNCTIOn));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[INDEX_OF_SAVED_MATH_FUNCTIOn]=append(replace_str, append("#", with_str));
        INDEX_OF_SAVED_MATH_FUNCTIOn++;
    }
    while (count_str(input_str, "cot(")!=0) {
        int index=find(input_str, "cot(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(INDEX_OF_SAVED_MATH_FUNCTIOn));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[INDEX_OF_SAVED_MATH_FUNCTIOn]=append(replace_str, append("#", with_str));
        INDEX_OF_SAVED_MATH_FUNCTIOn++;
    }
    while (count_str(input_str, "sec(")!=0) {
        int index=find(input_str, "sec(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(INDEX_OF_SAVED_MATH_FUNCTIOn));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[INDEX_OF_SAVED_MATH_FUNCTIOn]=append(replace_str, append("#", with_str));
        INDEX_OF_SAVED_MATH_FUNCTIOn++;
    }
    while (count_str(input_str, "csc(")!=0) {
        int index=find(input_str, "csc(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(INDEX_OF_SAVED_MATH_FUNCTIOn));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[INDEX_OF_SAVED_MATH_FUNCTIOn]=append(replace_str, append("#", with_str));
        INDEX_OF_SAVED_MATH_FUNCTIOn++;
    }
    while (count_str(input_str, "exp(")!=0) {
        int index=find(input_str, "exp(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(INDEX_OF_SAVED_MATH_FUNCTIOn));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[INDEX_OF_SAVED_MATH_FUNCTIOn]=append(replace_str, append("#", with_str));
        INDEX_OF_SAVED_MATH_FUNCTIOn++;
    }
    while (count_str(input_str, "log10(")!=0) {
        int index=find(input_str, "log10(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(INDEX_OF_SAVED_MATH_FUNCTIOn));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[INDEX_OF_SAVED_MATH_FUNCTIOn]=append(replace_str, append("#", with_str));
        INDEX_OF_SAVED_MATH_FUNCTIOn++;
    }

    
    input_str=changeAllDecimalToFraction(input_str);
    //input_str=addParenthesisForPowerAndCalculateIfNecessary(input_str);

    
    
    char **SAVE_EXPRESSION_THAT_HAS_ALPHA_IN_BRACKTER; // save (y*3*4/5^2+x) to #SAVED1#
    int INDEX_OFR_SAVE_EXPRESSION=0;                   //                             1
    Str_initStringList(&SAVE_EXPRESSION_THAT_HAS_ALPHA_IN_BRACKTER);
    input_str=trim(input_str);
    input_str=eval_CalculatePowerAtFirst_with_alpha_for_fraction(input_str);
    int count_of_left_bracket=count_str(input_str,"(");
    int count_of_right_bracket=count_str(input_str,")");
    
    //char *output;
    if(count_of_left_bracket!=count_of_right_bracket){
        printf("Mistakes occurred while calling function eval:\nnum of ( != num of )");
        exit(1);
    }
    
    int num_of_left_bracket=count_str(input_str, "(");
    for (int x=0; x<num_of_left_bracket; x++) {
        int index_of_final_left_bracket=find(input_str, "(");
        int index_of_first_right_bracket=find(input_str, ")");
        while (TRUE) {
            
            int temp=find_from_index(input_str, "(", index_of_final_left_bracket+1);
            if (temp==-1 || temp>index_of_first_right_bracket) {
                break;
            }
            else {
                index_of_final_left_bracket=temp;
            }
            
        }
        char *temp=substr(input_str,0,index_of_final_left_bracket);
        
        char *part_output=eval_simple_str_with_alpha_for_fraction(substr(input_str,index_of_final_left_bracket+1,index_of_first_right_bracket));
        if (findAlphaInString(part_output)==TRUE) {
            part_output=append("(", part_output);
            part_output=append(part_output, ")");
            Str_addString(&SAVE_EXPRESSION_THAT_HAS_ALPHA_IN_BRACKTER, part_output);
            part_output=append("#SAVED", append(intToCString(INDEX_OFR_SAVE_EXPRESSION), "#"));
            INDEX_OFR_SAVE_EXPRESSION++;
        }
        
        temp=append(temp,part_output);
        temp=append(temp,substr(input_str,index_of_first_right_bracket+1,(int)strlen(input_str)));
        input_str=temp;
    }
    input_str=eval_simple_str_with_alpha_for_fraction(input_str);
    
    int x=INDEX_OFR_SAVE_EXPRESSION-1;
    for (; x>=0; x--) {
        char *replace_str=append("#SAVED", append(intToCString(x), "#"));
        char *with_str=SAVE_EXPRESSION_THAT_HAS_ALPHA_IN_BRACKTER[x+1];
        input_str=replace(input_str,replace_str, with_str);
    }
    input_str=changeOperatorStrToOriginalForWhoStr(input_str);
    
    //for calculate_for_division_for_fraction
    input_str=replace(input_str, "#LEFT#", "(");
    input_str=replace(input_str, "#RIGHT#", ")");

    // Delete 0 after
    int a=(int)strlen(input_str)-1;
    int place=(int)strlen(input_str);
    if (find(input_str, ".") != -1) {
        for (; a >= 0; a--) {
            if (input_str[a] == '0')
                place--;
            else
                break;
        }
    }
    if(place!=(int)strlen(input_str))
        input_str=substr(input_str,0,place);
    if(input_str[(int)strlen(input_str)-1]=='.')
        input_str=substr(input_str,0,(int)strlen(input_str)-1);
    
    input_str=clean_math_output_for_fraction(input_str);
    printf("---> %s\n",input_str);
    // return sin cos tan cot sec csc exp log10
    a=0;
    for (a=0; a<INDEX_OF_SAVED_MATH_FUNCTIOn; a++) {
        char *replace_str_a=replace_str_list[a];
        int index_of_mark=find(replace_str_a ,"#");
        char *replace_str=substr(replace_str_a, 0, index_of_mark);
        char *with_str=substr(replace_str_a, index_of_mark+1, (int)strlen(replace_str_a));
        input_str=replace(input_str,with_str,replace_str);
    }
    return input_str;
    
}


