//
//  walley_data.h
//  CPractice
//
//  Created by shd101wyy on 12-10-17.
//  Copyright (c) 2012年 shd101wyy. All rights reserved.
//

#include "walley_string.h"

struct VAR{
    char *var_name;
    char *var_value;
    char *var_type;
};
/*
void Var_PrintVar(struct VAR struct_var[]){
    int row=0;
    while (struct_var[row].var_name!=NULL) {
        printf("%s:%s:%s:\n",struct_var[row].var_name,struct_var[row].var_value,struct_var[row].var_type);
        row++;
    }
}*/
void Var_PrintVar(struct VAR *struct_var){
    int row=0;
    int length=0;
    if (strcmp((struct_var)->var_name,"__size_of_array__")!=0) {
        printf("Var_PrintVar..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((struct_var)->var_value);
    }
    while (row<length) {
        printf("%s:%s:%s:\n",struct_var[row].var_name,struct_var[row].var_value,struct_var[row].var_type);
        row++;
    }
}

/*
void Var_addProperty(struct VAR *var,char *var_name, char *var_value, char *var_type){
    int i=0;
    int length=0;
   // printf("add %s %s %s\n",var_name,var_value,var_type);
    while (1) {
        //printf("%s",var[i]->var_name);
        
        if (var[i].var_name==NULL) {
            //printf("Find\n");
            //printf("i is %d\n",i);
            length=i;
            break;
        }
        i=i+1;
    }
    
    
    var[i].var_name=var_name;
    var[i].var_value=var_value;
    var[i].var_type=var_type;
    
        
    
    printf("######################\n");
    Var_PrintVar(var);
    printf("######################\n");
    
    printf("length is %d\n",length);
   
    struct VAR *new_var=(struct VAR*)realloc(var, sizeof(struct VAR)*(length+1));
    if (new_var==NULL) {
        printf("can not realloc\n");
        exit(0);
    }
    if (var!=new_var) {
        free(var);
        var=new_var;
    }
    else{
        printf("THEY ARE THE SAME\n");
    }
    
    
    }
*/
void Var_initVar(struct VAR **var){
    *var=(struct VAR*)malloc(sizeof(struct VAR)*1);
    (*var)->var_name="__size_of_array__";
    (*var)->var_value="1";
    (*var)->var_type="int";
}
void Var_addProperty(struct VAR **var,char *var_name, char *var_value, char *var_type){
    
    int length=0;
    if (strcmp((*var)->var_name,"__size_of_array__")!=0) {
        printf("Var_addProperty..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((*var)->var_value);
    }
    
    //printf("length is %d\n",length);
    (*var)->var_value=numToCString(1+atoi((*var)->var_value));
    
    *var=realloc(*var, sizeof(struct VAR)*(length+1));
    (*var+length)->var_name=var_name;
    (*var+length)->var_type=var_type;
    (*var+length)->var_value=var_value;
    //printf("##################\n");
    //Var_PrintVar(*var);
    //printf("##################\n");
    
}
int Var_Existed(struct VAR var[], char *var_name){
   // printf("ENTER HERE %s\n",var_name);
    int existed=0;
    int i=0;
    int length=0;
    if (strcmp((var)->var_name,"__size_of_array__")!=0) {
        printf("Var_Existed..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((var)->var_value);
    }

   // printf("There\n");
    while (i<length) {
       // printf("a");
       // printf("i-->%d",i);
        if (strcmp(var[i].var_name,var_name)==0) {
            existed=1;
            break;
        }
        i=i+1;
    }
    return existed;
}
/*
void Var_removeVar(struct VAR var[], char *remove_var_name){
   // printf("Var_Remove_Var");
    
    
    int i=0;
    int find_var=0;
        
    while (1) {
        if (var[i].var_name==NULL) {
            break;
        }
        if (find_var==1) {
            var[i-1].var_name=var[i].var_name;
            var[i-1].var_type=var[i].var_type;
            var[i-1].var_value=var[i].var_value;
            i++;
            continue;
        }
        if (strcmp(var[i].var_name,remove_var_name)==0) {
            find_var=1;
        }
        i=i+1;
    }
    if (find_var==1) {
        var[i-1].var_name=NULL;
        var[i-1].var_type=NULL;
        var[i-1].var_value=NULL;
    }
    
    realloc(var, sizeof(struct VAR)*i);
}
*/
void Var_removeVar(struct VAR **var, char *remove_var_name){
    //printf("Var_Remove_Var--> remove %s\n",remove_var_name);
    int length=0;
    if (strcmp((*var)->var_name,"__size_of_array__")!=0) {
        printf("Var_removeVar..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((*var)->var_value);
    }
    
    
    int i=0;
    int find_var=0;
    
    while (i<length) {
        if (find_var==1) {
            (*var+i-1)->var_name=(*var+i)->var_name;
            (*var+i-1)->var_type=(*var+i)->var_type;
            (*var+i-1)->var_value=(*var+i)->var_value;
            i++;
            continue;
        }
        if (strcmp((*var+i)->var_name,remove_var_name)==0) {
            find_var=1;
        }
        i=i+1;
    }
    if (find_var==1) {
        //printf("Find var, i is %d\n",i);
        //printf("#################\n");
        //Var_PrintVar(*var);
        //printf("#################\n");
        (*var+length-1)->var_name=NULL;
        (*var+length-1)->var_type=NULL;
        (*var+length-1)->var_value=NULL;
        *var=realloc(*var, sizeof(struct VAR)*(length-1));
        (*var)->var_value=numToCString(atoi((*var)->var_value)-1);
        //printf("#################\n");
        //Var_PrintVar(*var);
        //printf("#################\n");
    }
    
}

void Var_changeValueOfVar(struct VAR *var, char *var_name, char *var_value, char *var_type){
    int i=0;
    int length=0;
    if (strcmp((var)->var_name,"__size_of_array__")!=0) {
        printf("Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((var)->var_value);
    }
    
    while (i<length) {
        if (strcmp(var[i].var_name,var_name)==0) {
            var[i].var_value=var_value;
            var[i].var_type=var_type;
            break;
        }
        i=i+1;
    }
}

char *Var_getValueOfVar(struct VAR *var, char *var_name){
    int i=0;
    int length=0;
    if (strcmp((var)->var_name,"__size_of_array__")!=0) {
        printf("Var_getValueOfVar..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((var)->var_value);
    }
    
    while (i<length) {
        if (strcmp(var[i].var_name,var_name)==0) {
            return var[i].var_value;
        }
        i=i+1;
    }
    //return "None";
    return var_name;
}

//==============================================================================
//===================== Math Data ==============================================

// coefficient
// value
// power

// 3*x^3
// coefficient 3
// value x
// power 3

// 9
// coefficient 9
// value 0       // 0 means it is number not symbol
// power 1


struct Math_Data{
    char *coefficient;
    char *value;
    char *power;
};


struct Math_Data_List{
    int length;
    struct Math_Data *math_data_list;
};


// MDL IS MATH DATA LIST
void MDL_init(struct Math_Data_List *mdl){
    (*mdl).length=0;
    (*mdl).math_data_list=(struct Math_Data*)malloc(sizeof(struct Math_Data)*1);
}

void MDL_addProperty(struct Math_Data_List *mdl,char *coefficient, char *value, char *power){
    int length=(*mdl).length;
    if (length==0) {
        (*mdl).math_data_list[0].coefficient=coefficient;
        (*mdl).math_data_list[0].value=value;
        (*mdl).math_data_list[0].power=power;
        (*mdl).length=1;
    }
    else{
        (*mdl).length=length+1;
        length=length+1;
        (*mdl).math_data_list=(struct Math_Data*)realloc((*mdl).math_data_list, sizeof(struct Math_Data)*length);
        (*mdl).math_data_list[length-1].coefficient=coefficient;
        (*mdl).math_data_list[length-1].value=value;
        (*mdl).math_data_list[length-1].power=power;
    }
}

void MDL_addMathData(struct Math_Data_List *mdl, struct Math_Data math_data){
    MDL_addProperty(mdl, math_data.coefficient, math_data.value, math_data.power);
}


void MDL_PrintMathDataList(struct Math_Data_List mdl){
    int length=mdl.length;
    int i=0;
    for (;i<length;i++) {
        printf("%d -> %s:%s:%s\n",i,mdl.math_data_list[i].coefficient,mdl.math_data_list[i].value,mdl.math_data_list[i].power);
    }
}

// MDA is MDL Array
struct Math_Data_Array{
    int length;
    struct Math_Data_List *mdl;
};
void MDA_init(struct Math_Data_Array *mda){
    (*mda).length=0;
    (*mda).mdl=(struct Math_Data_List*)malloc(sizeof(struct Math_Data_List)*1);
    MDL_init(&((*mda).mdl[0]));
}

void MDA_addMathDataList(struct Math_Data_Array *mda, struct Math_Data_List mdl){
    int length=(*mda).length;
    if (length==0) {
        (*mda).length=1;
        (*mda).mdl[0]=mdl;
    }
    else{
        (*mda).length=(*mda).length+1;
        (*mda).mdl=(struct Math_Data_List*)realloc((*mda).mdl, sizeof(struct Math_Data_List)*((*mda).length));
        (*mda).mdl[(*mda).length-1]=mdl;
    }
}

struct Math_Data_List MDA_pop(struct Math_Data_Array *mda){
    int length=(*mda).length;
    (*mda).length=length-1;
    struct Math_Data_List return_mdl=(*mda).mdl[length-1];
    (*mda).mdl=(struct Math_Data_List*)realloc((*mda).mdl, sizeof(struct Math_Data_List)*((*mda).length));
    
    return return_mdl;
}

char *MDL_changeMathDataListToString(struct Math_Data_List mdl){
    char *output_str="";
    int length=mdl.length;
    int i=0;
    for (;i<length ; i++) {
        struct Math_Data left_md=mdl.math_data_list[i];
        int j=i;
        int smallest_md_index=i;
        char *smallest_string=left_md.value;
        for (; j<length; j++) {
            if (strcmp(smallest_string, mdl.math_data_list[j].value)>0) {
                smallest_string=mdl.math_data_list[j].value;
                smallest_md_index=j;
            }
        }
        
        // swap
        mdl.math_data_list[i]=mdl.math_data_list[smallest_md_index];
        mdl.math_data_list[smallest_md_index]=left_md;
    }

    printf("Finishing Sorting\n");
    MDL_PrintMathDataList(mdl);

    i=0;
    for(i=0;i<length;i++){
        char *coef=mdl.math_data_list[i].coefficient;
        char *value=mdl.math_data_list[i].value;
        char *power=mdl.math_data_list[i].power;
        if(strcmp(value,"0")==0){
            output_str=append(output_str, coef);
            if(strcmp(power, "1")!=0){
                if(stringIsDigit(power)){
                    output_str=append(output_str, append("^", power));
                }
                else{
                    output_str=append(output_str, append("^(", append(power,")")));
                }
        
            }
        }
        else{
            if(strcmp(coef, "1")!=0){
                if(strcmp(coef, "-1")==0){
                    output_str=append(output_str, "-");
                }
                else{
                    output_str=append(output_str, append(coef,"*"));
                }
            }
            output_str=append(output_str, value);
            if(strcmp(power, "1")!=0){
                if(stringIsDigit(power)){
                    output_str=append(output_str, append("^", power));
                }
                else{
                    output_str=append(output_str, append("^(", append(power,")")));
                }
            }
        }
        if(i!=length-1)
            output_str=append(output_str, "+");
    }
output_str=replace(output_str, "+-", "-");
printf("OUTPUT_STR-----> %s\n",output_str);
    return output_str;
}


