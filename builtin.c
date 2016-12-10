#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdlib.h>
#include "builtin.h"
#include "defs.h"

int compare(char* s1,char* s2){
    unsigned long int n = 0;

    if(strlen(s1) < strlen(s2)){
        n = strlen(s1);
    }else{
        n = strlen(s2);
    }

    for (int i = 0; i < n; ++i) {
        if(s1[i] < s2[i]) {
            return -1;
        }
            if(s1[i] > s2[i]) {
                return 1;
            }
    }


    if(strlen(s1) < strlen(s2)){
        return -1;
    }
    if(strlen(s1) > strlen(s2)){
        return 1;
    }

    return 0;
}

char* substr(char* s,int i,int n){
    if(i > length(s) || n > (length(s)-i))
	ret_error(OTHER_RUNTIME_ERROR);

    char* substr;
    substr = (char *) malloc(n);
    for (int j = 0; j < n; ++j) {
        substr[j] = s[i];
        ++i;
    }

return substr;
}

void print(TVariable* var){
    if(var->type == VARTYPE_INTEGER)
        printf("%d",var->value.i);
    if(var->type == VARTYPE_DOUBLE)
        printf("%g",var->value.d);
    if(var->type == VARTYPE_STRING)
        printf("%s",var->value.s);
}

int length(char* str){
    int size;
    size = (int)strlen(str);

    return size;
}

double readDouble(){
    int c;
    char *str;
    int i = 0;
    bool bodka = FALSE;
    str = (char *) malloc(1);

    while((c = getchar()) != '\n'){
        if(c == EOF)
            break;
        if((!isdigit(c)) && (c != '.'))
            return -1;
        if(c == '.'){
            if(bodka == FALSE)
                bodka = TRUE;
            else
                return -1;
        }

        str = (char *) realloc(str, (i + 2));
        str[i++] = c;
    }
    double cislo = atof(str);

    free(str);

    return cislo;
}

int readInt(){
    int c;
    char *str;
    int i = 0;
    str = (char *) malloc(1);

    while((c = getchar()) != '\n'){
        if(c == EOF)
            break;
        if(!isdigit(c))
            return -1;

        str = (char *) realloc(str, (i + 2));
        str[i++] = c;
    }
    int cislo = atoi(str);

    free(str);

    return cislo;
}



char* readString(){
    int c;
    char *str;
    int i = 0;
    str = (char *) malloc(1);

    while((c = getchar()) != '\n') {
        if(c == EOF)
            break;
        str = (char *) realloc(str, (i+2));

        str[i++] = c;
    }

return str;
}
