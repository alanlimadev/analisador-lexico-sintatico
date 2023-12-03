#include<stdio.h>
#include<stdlib.h>
#include"TokenList.h"

Token* create(Token* list){
    return (Token*)malloc(sizeof(Token));
}

