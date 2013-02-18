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



