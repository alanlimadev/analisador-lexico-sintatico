#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define LETTER 0 
#define DIGIT 1
#define UNKNOWN 99

//Definição dos Tokens
#define INT_LIT 10 
#define IDENT 11
#define VAR_TYPE 12
#define SEMICOLON 13
//operadores
#define ASSIGN_OP 14
#define SUM_OP 15
#define SUB_OP 16
#define MULTIPLY_OP 17
#define DIVIDE_OP 18
#define COMMA 19
#define AND_OP 20
#define OR_OP 21
#define NOT_OP 22

#define IF_STMT 23
#define LEFT_PAREN 25 
#define RIGHT_PAREN 26
#define UNKNOW_TOKEN 29
int charClass;
char lexema[100];
int lex_lengh=0;
char nextChar;
int nextToken;
FILE *in_fp, *fopen();

void getChar(){ //le o prox char e atualiza a sua classe
    nextChar=getc(in_fp);
    if(nextChar!=EOF)
        if(isalpha(nextChar))
            charClass=LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;   
        else
            charClass = UNKNOWN;    
    else
        charClass = EOF;
}

int main(){
    in_fp=fopen("entrada.txt","r");
    if(in_fp==NULL){
        printf("Erro ao abrir arquivo\n");
    }
    else{
        getChar(); //bota o primeiro char no nextChar
        do{
            lex();
        }while (nextToken!=EOF);
        
    }
    return 0;
}