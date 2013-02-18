/* 
 * File:   walley_file_operation.h
 * Author: shd101wyy
 *
 * Created on September 1, 2012, 4:37 PM
 */
#include "walley_function.h"
//#########################################################################################
//#########################################################################################
//#########################################################################################
void writeVarNameAndVarValueIntoAppointedFile(char *file_name,char *var_name,char *var_value,char *var_value_type) {
    char *str_in_wy = getStringFromFile(file_name);

    FILE *fp = fopen(file_name, "w");
    char input_message[1000] = "";
    strcat(input_message, var_name);
    strcat(input_message, ":");
    strcat(input_message, var_value);
    strcat(input_message, ":");
    strcat(input_message, var_value_type);
    strcat(input_message, ":");
    strcat(input_message, "\n");
   //// printf("Input Message is %s\n", input_message);
    fputs(str_in_wy, fp);
    fputs(input_message, fp);
    fclose(fp);
}
void writeVarNameAndVarValueIntoFile(char *var_name,char *var_value,char *var_value_type) {
    /*
    char *str_in_wy = getStringFromFile("__walley__.wy");

    FILE *fp = fopen("__walley__.wy", "w");
    char input_message[1000] = "";
    strcat(input_message, var_name);
    strcat(input_message, ":");
    strcat(input_message, var_value);
    strcat(input_message, ":");
    strcat(input_message, var_value_type);
    strcat(input_message, "\n");
    printf("Input Message is %s\n", input_message);
    fputs(str_in_wy, fp);
    fputs(input_message, fp);
    fclose(fp);**/
    writeVarNameAndVarValueIntoAppointedFile("__walley__.wy",var_name,var_value,var_value_type);
}
//#########################################################################################
//#########################################################################################
//#########################################################################################

bool checkWhetherSameFunctionNameExists(char *function_name){
    FILE *fp;
    //char ch;
    char arr[1000]="";
    bool has_same_func_name=FALSE;
    if ((fp = fopen("__walley_function__.wy", "r")) == NULL) {
        perror("File open error!\n");
        exit(1);
    } //else {
      //  printf("Function checkWhetherSameFunctionNameExists Find file\n");
    //}
    char *var_name_in_file="";
    while ((fgets(arr, 1000, fp)) != NULL) {
        if(find(arr,":")==-1)
            continue;
        var_name_in_file=substr(arr,0,find(arr,":"));
        if (strcmp(var_name_in_file,function_name)==0){
            has_same_func_name=TRUE;
            break;
        }
    }
    fclose(fp);
    return has_same_func_name;
}

bool checkWhetherSameFunctionNameExistsFromVar(char *function_name){
    bool has_same_func_name=FALSE;
    char *var_name_in_file="";
    int row=0;
    int length=atoi(FUNCTION[0]);
    while (row<length) {
       // printf("row-->%d\n",row);
        char *arr=FUNCTION[row];
        if(find(arr,":")==-1){
            row++;
            continue;
        }
        var_name_in_file=substr(arr,0,find(arr,":"));
        if (strcmp(var_name_in_file,function_name)==0){
            has_same_func_name=TRUE;
            break;
        }
        row++;
    }
    //fclose(fp);
    return has_same_func_name;
}




//#########################################################################################
//#########################################################################################
//#########################################################################################
void changeTheVarValueFromItsInitialOneFromFile(char *file_name,char *var_name,char *var_value, char *var_value_type){
    //printf("1---------------\n%s---------------\n",getStringFromFile(file_name));
    //printf("Function changeTheVarValueFromItsInitialOneFromFile\nfile name %s\nvar_name %s\nvar_value %s\nvar_value_type %s\n",file_name,var_name,var_value,var_value_type);
    FILE *fp;
    //char ch;
    char arr[1000]="";
    char output[10000]="";
    if ((fp = fopen(file_name, "r")) == NULL) {
        perror("File open error!\n");
        exit(1);
    } //else {
      //  printf("Find file %s\n",file_name);
    //}
    
    while ((fgets(arr, 1000, fp)) != NULL) {
        //printf("arr is :%s\n",arr);
        if(find(arr,":")==-1){
            strcat(output, arr);
            continue;
        }
        char *var_name_in_file=substr(arr,0,find(arr,":"));
        if (strcmp(var_name_in_file, var_name) == 0) {
            strcat(output, var_name);
            strcat(output, ":");
            strcat(output, var_value);
            strcat(output, ":");
            strcat(output, var_value_type);
            strcat(output, ":");
            strcat(output, "\n");
     
        } else {
            strcat(output, arr);
        }
    }
    //printf("1 Input Message is %s\n", output);
    fclose(fp);
    fp=fopen(file_name, "w");
    fputs(output,fp);
    fclose(fp);
    //printf("2 Input Message is %s\n", output);
}



void changeTheVarValueFromItsInitialOne(char *var_name,char *var_value, char *var_value_type){
     changeTheVarValueFromItsInitialOneFromFile("__walley__.wy",var_name,var_value,var_value_type);
}
//#########################################################################################
//#########################################################################################
//#########################################################################################


void writeFunctionIntoFile(char *func_name,char *func_param_str) {
    char *str_in_wy = getStringFromFile("__walley_function__.wy");

    FILE *fp = fopen("__walley_function__.wy", "w");
    char input_message[1000] = "";
    strcat(input_message, func_name);
    strcat(input_message, ":");
    strcat(input_message, func_param_str);
    strcat(input_message, ":");
    //strcat(input_message, var_value_type);
    strcat(input_message, "\n");
   //// printf("Input Function is %s\n", input_message);
    fputs(str_in_wy, fp);
    fputs(input_message, fp);
    fclose(fp);
}

void writeFunctionIntoVar(char *func_name,char *func_param_str, char ***to_function_var) {
    //char *str_in_wy = getStringFromFile("__walley_function__.wy");
    
    //FILE *fp = fopen("__walley_function__.wy", "w");
    char input_message[1000] = "";
    strcat(input_message, func_name);
    strcat(input_message, ":");
    strcat(input_message, func_param_str);
    strcat(input_message, ":");
    //strcat(input_message, var_value_type);
    strcat(input_message, "\n");
    Str_addString(to_function_var, append("",input_message));
    //// printf("Input Function is %s\n", input_message);
    //fputs(str_in_wy, fp);
    //fputs(input_message, fp);
    //fclose(fp);
}



// I changed the code below to Use FUNCTION to store function
/*
void changeFunctionFromItsInitialOne(char *func_name,char *func_param_str){
    FILE *fp;
    char arr[1000]="";
    char output[1000]="";
    if ((fp = fopen("__walley_function__.wy", "r")) == NULL) {
        perror("File open error!\n");
        exit(1);
    } //else {
      //  printf("Find file\n");
    //}
    char *func_name_in_file="";
    while ((fgets(arr, 1000, fp)) != NULL) {
        func_name_in_file=substr(arr,0,find(arr,":"));
        if (strcmp(func_name_in_file, func_name) == 0) {
            strcat(output, func_name);
            strcat(output, ":");
            strcat(output, func_param_str);
            //strcat(output, ":");
            //strcat(output, var_value_type);
            strcat(output, "\n");
     
        } else {
            strcat(output, arr);
        }
    }
    fclose(fp);
    //printf("Output is %s\n",output);
    fp=fopen("__walley_function__.wy", "w");
    fputs(output,fp);
    fclose(fp);
   //// printf("Input Function is %s\n", output);
}
*/
void changeFunctionFromItsInitialOne(char *func_name,char *func_param_str){
    FILE *fp;
    char arr[1000]="";
    char output[1000]="";
    if ((fp = fopen("__walley_function__.wy", "r")) == NULL) {
        perror("File open error!\n");
        exit(1);
    } //else {
    //  printf("Find file\n");
    //}
    char *func_name_in_file="";
    while ((fgets(arr, 1000, fp)) != NULL) {
        func_name_in_file=substr(arr,0,find(arr,":"));
        if (strcmp(func_name_in_file, func_name) == 0) {
            strcat(output, func_name);
            strcat(output, ":");
            strcat(output, func_param_str);
            //strcat(output, ":");
            //strcat(output, var_value_type);
            strcat(output, "\n");
            
        } else {
            strcat(output, arr);
        }
    }
    fclose(fp);
    //printf("Output is %s\n",output);
    fp=fopen("__walley_function__.wy", "w");
    fputs(output,fp);
    fclose(fp);
    //// printf("Input Function is %s\n", output);
}

/* write a=6,b=3 into file*/
/* write a=6,b=3 into file*/
void writeFunctionParameterOneByOneToFile(char *func_param_str){
   //// printf("Now Run Function writeFunctionParameterOneByOneToFile\n");
    if(strcmp("None",func_param_str)==0){
        //printf("This function has no parameters\n");
        //writeStringToFile("__walley_function__.wy","#### Finish Initialize Parameters ####\n");
        printf("");
    } else {
        char *temp=malloc(sizeof(char)*((int)strlen(func_param_str)+2));
        strcpy(temp,func_param_str);
        strcat(temp,",");
        temp[(int)strlen(func_param_str)+1]=0;
        func_param_str=temp;
        
        while(count_str(func_param_str,",")>0){
            char *param=substr(func_param_str,0,find(func_param_str,","));
            char *temp_temp;
            if(find(param,"=")==-1){
                temp_temp=malloc(sizeof(char)*((int)strlen(param)+3));
                strcpy(temp_temp,param);
                strcat(temp_temp,"=\n");
                temp_temp[(int)strlen(param)+2]=0;
            }
            else{
                temp_temp=malloc(sizeof(char)*((int)strlen(param)+2));
                strcpy(temp_temp,param);
                strcat(temp_temp,"\n");
                temp_temp[(int)strlen(param)+1]=0;
            }
             
            writeStringToFile("__walley_function__.wy",temp_temp);
            func_param_str=substr(func_param_str,find(func_param_str,",")+1,(int)strlen(func_param_str));
        }
        //writeStringToFile("__walley_function__.wy","#### Finish Initialize Parameters ####\n");
        
    }
    
}

/* write a=6,b=3 into file*/
/* write a=6,b=3 into file*/
// Not modify
void writeFunctionParameterOneByOneToVar(char *func_param_str, char ***function){
    //// printf("Now Run Function writeFunctionParameterOneByOneToFile\n");
    if(strcmp("None",func_param_str)==0){
        //printf("This function has no parameters\n");
        //writeStringToFile("__walley_function__.wy","#### Finish Initialize Parameters ####\n");
        printf("");
    } else {
        func_param_str=append(func_param_str, ",");
        
        while(count_str(func_param_str,",")>0){
            char *param=substr(func_param_str,0,find(func_param_str,","));
            //char *temp_temp;
            if(find(param,"=")==-1){
                Str_addString(function, append(param, "=\n"));
            }
            else{
                Str_addString(function, append(param, "\n"));
            }
            
            //writeStringToFile("__walley_function__.wy",temp_temp);
            func_param_str=substr(func_param_str,find(func_param_str,",")+1,(int)strlen(func_param_str));
        }
        //writeStringToFile("__walley_function__.wy","#### Finish Initialize Parameters ####\n");
        
    }
    
}


/*
 * clean up file
 * to make sentences in order
 *  |
 *  |
 *  V
 */

void cleanWalleyLanguageFile(char *file_name){
    //printf("file_name is %s\n",file_name);
    FILE *fp=fopen(file_name, "r");
    char arr[10000];
    if (fp==NULL) {
        printf("No File %s Found\n",file_name);
        exit(0);
    }
    
    char *string_in_file[10000];
    int count=0;
    
    while (fgets(arr, 10000, fp)!=NULL) {
        //printf("--->%s count-->%d\n",arr,count);
        char *to_copy;
        if (arr[(int)strlen(arr)-1]=='\n') {
            to_copy=substr(arr, 0, (int)strlen(arr)-1);
        }else {
            to_copy=substr(arr, 0, (int)strlen(arr));
        }
        if (stringIsEmpty(to_copy)==TRUE) {
            continue;
        }
        string_in_file[count]=to_copy;
        count++;
    }
    fclose(fp);
    while (TRUE) {
        int i=0;
        bool can_exit=TRUE;
        for (i=0; i<count-1; i++) {
            if (strcmp(string_in_file[i], string_in_file[i+1])>0) {
                can_exit=FALSE;
            }
        }
        if (can_exit==TRUE) {
            break;
        }
        // Clean
        else{
            for (i=0; i<count-1; i++) {
                if (strcmp(string_in_file[i], string_in_file[i+1])>0) {
                    char *temp=string_in_file[i];
                    string_in_file[i]=string_in_file[i+1];
                    string_in_file[i+1]=temp;
                }
            }
        }
    }
   // printf("Finish Clean Up\n");
    int i=0;
    fp=fopen(file_name, "w");
    for (i=0; i<count; i++) {
        //printf("%s\n",string_in_file[i]);
        fputs(string_in_file[i], fp);
        fputs("\n", fp);
    }
    fclose(fp);
    
}



