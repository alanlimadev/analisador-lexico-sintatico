#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
#define ACESS_MOD 24
#define LEFT_PAREN 25 
#define RIGHT_PAREN 26
#define STATIC_KW 27
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
void addChar(){ //formar o lexema
    if(lex_lengh<99){
        lexema[lex_lengh++] = nextChar;
        lexema[lex_lengh]= 0;
    }
    else
        printf("Lexema mt grande!\n");
}
void addAndGetNextChar(){
    addChar();
    getChar();
}
void getNonBlank(){ //ignorar espaços em branco
    while(isspace(nextChar)){
        getChar();
    } 
}
int keyWordToken(){
    if(strcmp(lexema,"if")==0) return IF_STMT;
    if(strcmp(lexema,"public")==0||strcmp(lexema,"private")==0||strcmp(lexema,"protected")==0)return ACESS_MOD;
    if(strcmp(lexema,"char")==0||strcmp(lexema,"int")==0||strcmp(lexema,"float")==0||strcmp(lexema,"double")==0||strcmp(lexema,"void")==0)return VAR_TYPE;
    if(strcmp(lexema,"static")==0) return STATIC_KW;
    return IDENT;
}
int lookup(int ch){ //responsavel por identificar o token
    switch (ch)
    {
    case '(':
        addAndGetNextChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addAndGetNextChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addAndGetNextChar();
        nextToken = SUM_OP;
        break;
    case '*':
        addAndGetNextChar();
        nextToken = MULTIPLY_OP;
        break;
    case '=':
        addAndGetNextChar();
        nextToken = ASSIGN_OP;
        break;
    case '-':
        addAndGetNextChar();
        nextToken = SUB_OP;
        break;
    case '/':
        addAndGetNextChar();
        nextToken = DIVIDE_OP;
        break;
    case ';':
        addAndGetNextChar();
        nextToken = SEMICOLON;
        break;
    case ',':
        addAndGetNextChar();
        nextToken = COMMA;
        break;               
    default:
        if(nextChar!=EOF)
            nextToken = UNKNOW_TOKEN;
        else    
            nextToken = EOF;
        addAndGetNextChar();
        break;
    }
}
int lex(){
    lex_lengh=0;
    getNonBlank();
    //getNonComments();
    switch (charClass)
    {
    case LETTER:
        addAndGetNextChar();
        while(charClass == LETTER || charClass == DIGIT){
            addAndGetNextChar();
        }
        nextToken=IDENT;
        break;
    case DIGIT:
        addAndGetNextChar();
        while (charClass==DIGIT){
            addAndGetNextChar();
        }
        nextToken = INT_LIT;
        break;
    case UNKNOWN:
        lookup(nextChar);
        break;   
    case EOF:
        nextToken=EOF;
        lexema[0]='E';
        lexema[1]='O';
        lexema[2]='F';
        lexema[3]=0;
        break;
    }if(nextToken == IDENT)
        nextToken = keyWordToken();//verifica se o identificador da vez eh keyword
    if(nextToken==UNKNOW_TOKEN)
        printf("Lexema: %s nao reconhecido\n", lexema);
    else
        printf("Proximo token: %d, Proximo lexema: %s\n",nextToken,lexema);
    return nextToken;
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