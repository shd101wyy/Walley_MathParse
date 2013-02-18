//
//  walley_math_infix_to_postfix.h
//  Walley_MathParse
//
//  Created by shd101wyy on 13-2-14.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_math_lexical.h"
/*
 CHECK WIKIPEDIA......
 
 Shunting-yard algorithm
 From Wikipedia, the free encyclopedia
 In computer science, the shunting-yard algorithm is a method for parsing mathematical expressions specified in infix notation. It can be used to produce output in Reverse Polish notation (RPN) or as an abstract syntax tree (AST). The algorithm was invented by Edsger Dijkstra and named the "shunting yard" algorithm because its operation resembles that of a railroad shunting yard. Dijkstra first described the Shunting Yard Algorithm in Mathematisch Centrum report MR 34/61.
 
 Like the evaluation of RPN, the shunting yard algorithm is stack-based. Infix expressions are the form of mathematical notation most people are used to, for instance 3+4 or 3+4*(2−1). For the conversion there are two text variables (strings), the input and the output. There is also a stack that holds operators not yet added to the output queue. To convert, the program reads each symbol in order and does something based on that symbol.
 
 The shunting-yard algorithm has been later generalized into operator-precedence parsing.
 
 
 ================================================================================================================================
 
 
 
 Infix - Postfix
 
 Infix Expression :
 
 Any expression in the standard form like "2*3-4/5" is an Infix(Inorder) expression.
 
 Postfix Expression :
 
 The Postfix(Postorder) form of the above expression is "23*45/-".
 
 Infix to Postfix Conversion :
 
 In normal algebra we use the infix notation like a+b*c. The corresponding postfix notation is abc*+. The algorithm for the conversion is as follows :
 Scan the Infix string from left to right.
 Initialise an empty stack.
 If the scannned character is an operand, add it to the Postfix string. If the scanned character is an operator and if the stack is empty Push the character to stack.
 If the scanned character is an Operand and the stack is not empty, compare the precedence of the character with the element on top of the stack (topStack). If topStack has higher precedence over the scanned character Pop the stack else Push the scanned character to stack. Repeat this step as long as stack is not empty and topStack has precedence over the character.
 Repeat this step till all the characters are scanned.
 (After all characters are scanned, we have to add any character that the stack may have to the Postfix string.) If stack is not empty add topStack to Postfix string and Pop the stack. Repeat this step as long as stack is not empty.
 Return the Postfix string.
 Example :
 
 Let us see how the above algorithm will be imlemented using an example.
 
 Infix String : a+b*c-d
 
 Initially the Stack is empty and our Postfix string has no characters. Now, the first character scanned is 'a'. 'a' is added to the Postfix string. The next character scanned is '+'. It being an operator, it is pushed to the stack.
 
 
 Stack
 Postfix String
 
 Next character scanned is 'b' which will be placed in the Postfix string. Next character is '*' which is an operator. Now, the top element of the stack is '+' which has lower precedence than '*', so '*' will be pushed to the stack.
 
 
 Stack
 Postfix String
 
 The next character is 'c' which is placed in the Postfix string. Next character scanned is '-'. The topmost character in the stack is '*' which has a higher precedence than '-'. Thus '*' will be popped out from the stack and added to the Postfix string. Even now the stack is not empty. Now the topmost element of the stack is '+' which has equal priority to '-'. So pop the '+' from the stack and add it to the Postfix string. The '-' will be pushed to the stack.
 
 
 Stack
 Postfix String
 
 Next character is 'd' which is added to Postfix string. Now all characters have been scanned so we must pop the remaining elements from the stack and add it to the Postfix string. At this stage we have only a '-' in the stack. It is popped out and added to the Postfix string. So, after all characters are scanned, this is how the stack and Postfix string will be :
 
 
 Stack
 Postfix String
 
 End result :
 Infix String : a+b*c-d
 Postfix String : abc*+d-
 © 2002 Premshree Pillai.

 
 
 
 */

// pop the last string and return it
char *Str_PopString(char ***input_str_list){
    
    int length=atoi((*input_str_list)[0]);
    length=length-1;
    char *output=(*input_str_list)[length];
    (*input_str_list)[length]=NULL;
    (*input_str_list)[0]=intToCString(length);
    (*input_str_list)=(char**)realloc(*input_str_list, sizeof(char*)*(length));
    return output;
}


// sign order
// 3 ^
// 2 * / %
// 1 + -
// 0 ( )
int WALLEY_MATH_signOrder(char sign){
    if (sign=='^')
        return 3;
    else if(sign=='*'||sign=='/'||sign=='%'||sign=='\\')
        return 2;
    else if(sign=='+'||sign=='-')
        return 1;
    // ( )
    else
        return 0;
}

// the token here is the token without whitespaces
char *WALLEY_MATH_Infix_to_Postfix(struct TOKEN *token){
    char *output="";
    char **stack;
    Str_initStringList(&stack);
    int length_of_token=TOKEN_length(token);
    int row=1;
    
    int sign_order=0;
    int previous_sign_order=-1;
    
    int num_of_p=0;
    
    while (row<length_of_token) {
        char *token_string=token[row].TOKEN_STRING;
        char *token_class=token[row].TOKEN_CLASS;
        // it is number or symbol..
        if (strcmp(token_class, "W_ID")==0||
            strcmp(token_class, "W_NUMBER")==0) {
            output=append(output, token_string);
            output=append(output, " ");
        }
        else if(strcmp(token_class, "W_LEFT_P")==0){
            num_of_p++;
            Str_addString(&stack, token_string);
        }
        else if(strcmp(token_class, "W_RIGHT_P")==0){
            num_of_p--;
            int i=0;
            int length_of_stack=atoi(stack[0]);
            i=length_of_stack-1;
            for (i=length_of_stack-1; i>0; i--) {
                if (strcmp(stack[i], "(")==0) {
                    Str_PopString(&stack);
                    break;
                }
                else{
                    output=append(output,Str_PopString(&stack));
                    output=append(output, " ");
                }
            }

        }
        // it is operator..
        else{
            sign_order=WALLEY_MATH_signOrder(token_string[0]);
            
            if (sign_order>previous_sign_order) {
                Str_addString(&stack, token_string);
            }
            
            else{
                int length_of_stack=atoi(stack[0]);
                int i=length_of_stack-1;
                for (; i>=0; i--) {
                    int sign_order_in_stack;
                    if (i==0) {
                        sign_order_in_stack=-1;
                    }
                    else{
                        sign_order_in_stack=WALLEY_MATH_signOrder(stack[i][0]);
                    }
                    if (sign_order<=sign_order_in_stack) {
                        output=append(output,Str_PopString(&stack));
                        output=append(output, " ");
                    }
                    else{
                        Str_addString(&stack, token_string);
                        break;
                    }
                }
            }
            
            
            previous_sign_order=sign_order;
        }
        row++;
    }
    
    int length_of_stack=atoi(stack[0]);
    int i=length_of_stack-1;
    for (; i>0; i--) {
        output=append(output,Str_PopString(&stack));
        output=append(output, " ");
    }
    return output;
}

/*
char *WALLEY_MATH_Infix_to_Postfix_For_Symbolic(struct TOKEN *token){
    char **output;
    char **stack;
    Str_initStringList(&stack);
    Str_initStringList(&output);
    int length_of_token=TOKEN_length(token);
    int row=1;
    
    int sign_order=0;
    int previous_sign_order=-1;
    
    int num_of_p=0;
    
    bool just_initialize_stack=TRUE;
    
    char *last_append_str="";
    char *last_operator="";
    
    while (row<length_of_token) {
        char *token_string=token[row].TOKEN_STRING;
        char *token_class=token[row].TOKEN_CLASS;
        
        // it is number or symbol..
        if (strcmp(token_class, "W_ID")==0||
            strcmp(token_class, "W_NUMBER")==0) {
            if (just_initialize_stack==FALSE) {
                //char *last_operator=Str_PopString(&stack);
                //Str_addString(&stack, last_operator);
                char *temp_str=Str_PopString(&stack);
                Str_addString(&stack, temp_str);
                if (strcmp(temp_str, "(")==0) {
                    Str_addString(&output, token_string);
                    last_append_str=token_string;
                }
                // put number ahead
                else if (strcmp(last_operator, "+")==0||strcmp(last_operator, "-")==0) {
                    if (output[atoi(output[0])-1][0]=='*'||output[atoi(output[0])-1][0]=='/') {
                        Str_addString(&output, token_string);
                        last_append_str=token_string;
                    }
                    else if (stringIsDigit(token_string)) {
                        // a+3 ---> 3a+
                        if (stringIsDigit(last_append_str)==FALSE) {
                            char **temp_str_list;
                            Str_initStringList(&temp_str_list);
                            
                            int str_list_length=atoi(output[0]);
                            int a=str_list_length-1;
                            for (; a>1; a--) {
                                if (strcmp(output[a], last_append_str)!=0) {
                                    Str_addString(&temp_str_list, Str_PopString(&output));
                                }
                                else{
                                    break;
                                }
                            }
                            char *temp_str=Str_PopString(&output);
                            Str_addString(&output, token_string);
                            Str_addString(&output, temp_str);
                            
                            last_append_str=temp_str;
                            
                            
                            int temp_str_list_length=atoi(temp_str_list[0]);
                            a=1;
                            for (; a<temp_str_list_length; a++) {
                                Str_addString(&output, temp_str_list[a]);
                            }
                            
                        }
                        
                        else{
                            Str_addString(&output, token_string);
                            last_append_str=token_string;
                        }
                    }
                    else{
                        char **temp_str_list;
                        Str_initStringList(&temp_str_list);
                        
                        int str_list_length=atoi(output[0]);
                        int a=str_list_length-1;
                        for (; a>1; a--) {
                            if (strcmp(output[a], last_append_str)!=0) {
                                Str_addString(&temp_str_list, Str_PopString(&output));
                            }
                            else{
                                break;
                            }
                        }
                        
                        Str_addString(&output, token_string);
                        last_append_str=token_string;
                        
                        int temp_str_list_length=atoi(temp_str_list[0]);
                        a=1;
                        for (; a<temp_str_list_length; a++) {
                            Str_addString(&output, temp_str_list[a]);
                        }
                        
                    }
                }
                
                // put number behind
                else if(strcmp(last_operator, "*")==0||strcmp(last_operator, "/")==0){
                    if (output[atoi(output[0])-1][0]=='+'||output[atoi(output[0])-1][0]=='-') {
                        Str_addString(&output, token_string);
                        last_append_str=token_string;
                    }
                    // 3*a*2 --> a32**
                    // a*3---> a3*   a*b*3---> ab3**
                    else if (stringIsDigit(token_string)) {
                        char **temp_str_list;
                        Str_initStringList(&temp_str_list);
                        
                        int str_list_length=atoi(output[0]);
                        int a=str_list_length-1;
                        for (; a>1; a--) {
                            if (strcmp(output[a], last_append_str)!=0) {
                                Str_addString(&temp_str_list, Str_PopString(&output));
                            }
                            else{
                                break;
                            }
                        }
                        
                        Str_addString(&output, token_string);
                        last_append_str=token_string;
                        
                        int temp_str_list_length=atoi(temp_str_list[0]);
                        a=1;
                        for (; a<temp_str_list_length; a++) {
                            Str_addString(&output, temp_str_list[a]);
                        }
                    }
                    else{
                        // a*b---> ab*
                        if (stringIsDigit(last_append_str)==FALSE) {
                            //printf("%s %s %s\n",token_string,last_append_str,last_operator);
                            
                            char **temp_str_list;
                            Str_initStringList(&temp_str_list);
                            
                            int str_list_length=atoi(output[0]);
                            int a=str_list_length-1;
                            for (; a>1; a--) {
                                if (strcmp(output[a], last_append_str)!=0) {
                                    Str_addString(&temp_str_list, Str_PopString(&output));
                                }
                                else{
                                    break;
                                }
                            }
                            Str_PrintStr(output);
                            if (atoi(output[0])!=1) {
                                char *compare_str=Str_PopString(&output);
                                if (isSign(compare_str[0])==FALSE && stringIsDigit(compare_str)==FALSE) {
                                    // aba3 ---> baa3
                                    // 3*a*b*a --> baa3***
                                    if (strcmp(compare_str, token_string)>0) {
                                        Str_addString(&output, token_string);
                                        Str_addString(&output, compare_str);
                                        last_append_str=compare_str;
                                        
                                    }
                                    else{
                                        Str_addString(&output, compare_str);
                                        Str_addString(&output, token_string);
                                        last_append_str=token_string;
                                    }
                                }
                                else{
                                    Str_addString(&output, compare_str);
                                    Str_addString(&output, token_string);
                                    last_append_str=token_string;
                                    
                                }
                            }
                            else{
                                Str_addString(&output, token_string);
                                last_append_str=token_string;
                            }
                            
                            int temp_str_list_length=atoi(temp_str_list[0]);
                            a=1;
                            for (; a<temp_str_list_length; a++) {
                                Str_addString(&output, temp_str_list[a]);
                            }
                            
                        }
                        // 3*a---> a3*
                        else{
                            char **temp_str_list;
                            Str_initStringList(&temp_str_list);
                            
                            int str_list_length=atoi(output[0]);
                            int a=str_list_length-1;
                            for (; a>1; a--) {
                                if (strcmp(output[a], last_append_str)!=0) {
                                    Str_addString(&temp_str_list, Str_PopString(&output));
                                }
                                else{
                                    break;
                                }
                            }
                            char *temp_str=Str_PopString(&output);
                            if (atoi(output[0])!=1) {
                                char *compare_str=Str_PopString(&output);
                                // aba3 ---> baa3
                                if (isSign(compare_str[0])==FALSE && stringIsDigit(compare_str)==FALSE) {
                                    if (strcmp(compare_str, token_string)<0) {
                                        Str_addString(&output, token_string);
                                        Str_addString(&output, compare_str);
                                    }
                                    else{
                                        Str_addString(&output, compare_str);
                                        Str_addString(&output, token_string);
                                    }
                                }
                                else{
                                    Str_addString(&output, compare_str);
                                    Str_addString(&output, token_string);
                                    last_append_str=token_string;
                                }
                                
                            }
                            else{
                                Str_addString(&output, token_string);
                            }
                            
                            Str_addString(&output, temp_str);
                            last_append_str=temp_str;
                            
                            int temp_str_list_length=atoi(temp_str_list[0]);
                            a=1;
                            for (; a<temp_str_list_length; a++) {
                                Str_addString(&output, temp_str_list[a]);
                            }
                        }
                    }
                    
                }
                else{
                    printf("Error..only support +- * / now\n");
                    exit(3);
                }
            }
            
            
            // just initialize stack
            else{
                Str_addString(&output, token_string);
                last_append_str=token_string;
            }
            
            just_initialize_stack=FALSE;
            
            //output=append(output, token_string);
            //output=append(output, " ");
        }
        else if(strcmp(token_class, "W_LEFT_P")==0){
            num_of_p++;
            Str_addString(&stack, token_string);
        }
        else if(strcmp(token_class, "W_RIGHT_P")==0){
            num_of_p--;
            int i=0;
            int length_of_stack=atoi(stack[0]);
            i=length_of_stack-1;
            for (i=length_of_stack-1; i>0; i--) {
                if (strcmp(stack[i], "(")==0) {
                    Str_PopString(&stack);
                    break;
                }
                else{
                    Str_addString(&output, Str_PopString(&stack));
                    //output=append(output,Str_PopString(&stack));
                    //output=append(output, " ");
                }
            }
            
        }
        // it is operator..
        else{
            sign_order=WALLEY_MATH_signOrder(token_string[0]);
            
            if (sign_order>previous_sign_order) {
                Str_addString(&stack, token_string);
            }
            
            else{
                int length_of_stack=atoi(stack[0]);
                int i=length_of_stack-1;
                for (; i>=0; i--) {
                    int sign_order_in_stack;
                    if (i==0) {
                        sign_order_in_stack=-1;
                    }
                    else{
                        sign_order_in_stack=WALLEY_MATH_signOrder(stack[i][0]);
                    }
                    if (sign_order<=sign_order_in_stack) {
                        Str_addString(&output,Str_PopString(&stack));
                        // output=append(output,Str_PopString(&stack));
                        // output=append(output, " ");
                    }
                    else{
                        Str_addString(&stack, token_string);
                        break;
                    }
                }
            }
            
            char *temp_str=Str_PopString(&stack);
            last_operator=temp_str;
            Str_addString(&stack, temp_str);
            
            previous_sign_order=sign_order;
        }
        row++;
    }
    
    int length_of_stack=atoi(stack[0]);
    int i=length_of_stack-1;
    for (; i>0; i--) {
        Str_addString(&output, Str_PopString(&stack));
        //output=append(output,Str_PopString(&stack));
        //output=append(output, " ");
    }
    char *output_str="";
    int length_of_output=atoi(output[0]);
    for (i=1; i<length_of_output; i++) {
        output_str=append(output_str, output[i]);
        output_str=append(output_str, " ");
    }
    return output_str;
}


*/
