#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "TokenList.h"
//teste branch Paser
#define LETTER 0 
#define DIGIT 1
#define CONTROL 98
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
#define LOGIC_OP 20
#define COMPARE_OP 21

#define FOR_STMT 24
#define ELSE_STMT 25
#define IF_STMT 26

#define ACESS_MOD 29
#define LEFT_PAREN 30 
#define RIGHT_PAREN 31
#define STATIC_KW 32
#define WHILE_STMT 33
#define QUOT_MARK 34
#define BRACE_LEFT 35
#define BRACE_RIGHT 36
#define UNKNOWN_TOKEN 404

int charClass;
char lexema[100];
int lex_lengh=0;
char nextChar;
int nextToken;
int lineCount=1;
FILE *in_fp, *fopen();
Token nextTokenn;
Token* tokenList;

void fillToken(char* name, int tokenType){ //preencher token a cada iteração
    strcpy(nextTokenn.name,name);
    nextTokenn.tokenType = tokenType;
}

void getChar(){ //le o prox char e atualiza a sua classe
    nextChar=getc(in_fp);
    if(nextChar!=EOF)
        if(isalpha(nextChar))
            charClass=LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else if (nextChar=='\n'){
            charClass = CONTROL;
        }
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
    while(isblank(nextChar)){
        getChar();
    } 
}
void getNonComments(){
        if(nextChar=='/'){
        char next =getc(in_fp);
        if(next=='/'){
            while(next!='\n' && next!= EOF){
                next=getc(in_fp);
                next == '\n'? lineCount++ : lineCount;
            }
            getChar();
            getNonComments();//chamada recursiva para verificar se a prox linha tem //
        }
        else{
            ungetc(next,in_fp);
        }
    }
}
void keyWordToken(){
    if(strcmp(lexema,"public")==0||strcmp(lexema,"private")==0||strcmp(lexema,"protected")==0)
        return fillToken("ACESS_MOD",ACESS_MOD);
    if(strcmp(lexema,"char")==0||strcmp(lexema,"int")==0||strcmp(lexema,"float")==0||strcmp(lexema,"double")==0||strcmp(lexema,"void")==0||strcmp(lexema,"string")==0)
        return fillToken("VAR_TYPE",VAR_TYPE);
    if(strcmp(lexema,"static")==0)
        return fillToken("STATIC_KW",STATIC_KW);
    if(strcmp(lexema,"if")==0)
        return fillToken("IF_STMT",IF_STMT);
    if(strcmp(lexema,"while")==0)
        return fillToken("WHILE_STMT",WHILE_STMT);
    if(strcmp(lexema,"for")==0)
        return fillToken("FOR_STMT",FOR_STMT);
    if(strcmp(lexema,"else")==0)
        return fillToken("ELSE_STMT",ELSE_STMT);
}
int lookup(int ch){ //responsavel por identificar o token
    switch (ch)
    {
    case '(':
        addAndGetNextChar();
        fillToken("LEFT_PAREN",LEFT_PAREN);
        break;
    case ')':
        addAndGetNextChar();
        fillToken("RIGHT_PAREN",RIGHT_PAREN);
        break;
    case '+':
        addAndGetNextChar();
        fillToken("SUM_OP",SUM_OP);
        break;
    case '*':
        addAndGetNextChar();
        fillToken("MULTIPLY_OP",MULTIPLY_OP);
        break;
    case '=':
        addAndGetNextChar();
        fillToken("ASSIGN_OP",ASSIGN_OP);
        break;
    case '-':
        addAndGetNextChar();
        fillToken("SUB_OP",SUB_OP);
        break;
    case '/':
        addAndGetNextChar();
        fillToken("DIVIDE_OP",DIVIDE_OP);
        break;
    case ';':
        addAndGetNextChar();
        fillToken("SEMICOLON",SEMICOLON);
        break;
    case ',':
        addAndGetNextChar();
        fillToken("COMMA",COMMA);
        break;
    case '"':
        addAndGetNextChar();
        fillToken("QUOT_MARK", QUOT_MARK);
        break;
    case '{':
        addAndGetNextChar();
        fillToken("BRACE_LEFT", BRACE_LEFT);
        break;
    case '}':
        addAndGetNextChar();
        fillToken("BRACE_RIGHT", BRACE_RIGHT);
        break;
    case '&':
        char next= getc(in_fp);
        if(next=='&'){
            ungetc(next,in_fp);
            addAndGetNextChar();
        }
        addAndGetNextChar();
        fillToken("LOGIC_OP", LOGIC_OP);
        break;
    case '|':
        char next1= getc(in_fp);
        if(next1=='|'){
            ungetc(next1,in_fp);
            addAndGetNextChar();
        }
        addAndGetNextChar();
        fillToken("LOGIC_OP", LOGIC_OP);
        break;                    
    case EOF:
        fillToken("EOF", EOF);
        getChar();
        break;
    default:
        if(ch=='<'||ch=='!'||ch=='>'||ch=='^'){
            fillToken("LOGIC_OP",LOGIC_OP);
        }
        else
            fillToken("UNKNOWN_TOKEN", UNKNOWN_TOKEN);   
        addAndGetNextChar();
        break;
    }
}
int lex(){
    lex_lengh=0;
    getNonBlank();
    getNonComments();
    switch (charClass)
    {
    case LETTER:
        addAndGetNextChar();
        while(charClass == LETTER || charClass == DIGIT){
            addAndGetNextChar();
        }
        fillToken("IDENT",IDENT);
        break;
    case DIGIT:
        addAndGetNextChar();
        while (charClass==DIGIT){
            addAndGetNextChar();
        }
        fillToken("INT_LIT",INT_LIT);
        break;
    case CONTROL:
        lineCount++;
        getChar();
        return 0;   
    case UNKNOWN:
        lookup(nextChar);
        break;   
    case EOF:
        fillToken("EOF",EOF);
        lexema[0]='E';
        lexema[1]='O';
        lexema[2]='F';
        lexema[3]=0;
        break;
    }
    if(nextTokenn.tokenType == IDENT)
        keyWordToken();//verifica se o identificador da vez eh keyword    
    if(nextTokenn.tokenType==UNKNOWN_TOKEN)
        printf("Lexema: %s nao reconhecido error in line: %d\n", lexema,lineCount);
    else{
        //printf("Proximo token: %s value: %d, Proximo lexema: %s\n",nextTokenn.name,nextTokenn.tokenType,lexema);
        tokenList=insert(tokenList,nextTokenn.tokenType,nextTokenn.name, lineCount); //insere o token na lista
    }
    return nextTokenn.tokenType;
}

int main(){
    in_fp=fopen("entrada.txt","r");
    if(in_fp==NULL){
        printf("Erro ao abrir arquivo\n");
    }
    else{
        tokenList = create();
        getChar(); //bota o primeiro char no nextChar
        do{
            lex();
        }while (nextTokenn.tokenType!=EOF);
        printList(tokenList);
    }
    return 0;
}