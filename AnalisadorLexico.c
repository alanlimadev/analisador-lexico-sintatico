#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "TokenList.h"
#include"Parser.h"

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
            charClass = NEW_LINE;
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
    if(strcmp(lexema,"public")==0)
        return fillToken("ACESS_MOD",ACESS_MOD);
    if(strcmp(lexema,"private")==0)
        return fillToken("ACESS_MOD",ACESS_MOD);
    if(strcmp(lexema,"protected")==0)
        return fillToken("ACESS_MOD",ACESS_MOD);
    if(strcmp(lexema,"void")==0)
        return fillToken("VOID_KW",VOID_KW);
    if(strcmp(lexema,"char")==0||strcmp(lexema,"float")==0||strcmp(lexema,"double")==0||strcmp(lexema,"bool")==0||strcmp(lexema,"string")==0)
        return fillToken("VAR_TYPE",VAR_TYPE);
    if(strcmp(lexema,"int")==0)
        return fillToken("INT_TYPE",INT_TYPE);
    if(strcmp(lexema,"static")==0)
        return fillToken("STATIC_KW",STATIC_KW);
    if(strcmp(lexema,"if")==0)
        return fillToken("IF_STMT",IF_STMT);
    if(strcmp(lexema,"args")==0)
        return fillToken("ARGS_KW", ARGS_KW);
    if(strcmp(lexema,"Main")==0)
        return fillToken("MAIN_KW",MAIN_KW);    
    if(strcmp(lexema,"while")==0)
        return fillToken("WHILE_STMT",WHILE_STMT);
    if(strcmp(lexema,"for")==0)
        return fillToken("FOR_STMT",FOR_STMT);
    if(strcmp(lexema,"else")==0)
        return fillToken("ELSE_STMT",ELSE_STMT);
    if(strcmp(lexema,"true")==0)
        return fillToken("TRUE_OP",TRUE_OP);
    if(strcmp(lexema,"false")==0)
        return fillToken("FALSE_OP",FALSE_OP);
    if(strcmp(lexema,"return")==0)
        return fillToken("RETURN_KW", RETURN_KW);    
}
void lookup(int ch){ //responsavel por identificar o token
    char next;
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
        fillToken("ASSIGN_OP", ASSIGN_OP);
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
    case '.':
        addAndGetNextChar();
        fillToken("DOT",DOT);
        break;
    case '"': //aspas duplas (duble quotation mark)
        addAndGetNextChar();
        fillToken("DQUOT_MARK", DQUOT_MARK);
        break;
    case '\'': //aspas simples (single quotation mark)
        addAndGetNextChar();
        fillToken("SQUOT_MARK", SQUOT_MARK);
        break;
    case '{':
        addAndGetNextChar();
        fillToken("BRACE_LEFT", BRACE_LEFT);
        break;
    case '}':
        addAndGetNextChar();
        fillToken("BRACE_RIGHT", BRACE_RIGHT);
        break;
    case '[':
        addAndGetNextChar();
        fillToken("LEFT_SQUARE_BRKT", LEFT_SQUARE_BRKT);
        break;
    case ']':
        addAndGetNextChar();
        fillToken("RIGHT_SQUARE_BRKT", RIGHT_SQUARE_BRKT);
        break;
    case '&':
        addChar();
        next= getc(in_fp);
        if(next=='&'){
            addChar();
        } else {
            ungetc(next,in_fp);
        }
        fillToken("AND_OP", AND_OP);
        getChar();
        break;
    case '|':
        addChar();
        next= getc(in_fp);
        if(next=='|'){
            addChar();
        } else {
            ungetc(next,in_fp);
        }
        fillToken("OR_OP", OR_OP);
        getChar();
        break;
    case '!':
        addAndGetNextChar();
        fillToken("NOT_OP", NOT_OP);
        break;
    case '^':
        addAndGetNextChar();
        fillToken("OR_OP", OR_OP);
        break;
    case EOF:
        fillToken("EOF", EOF);
        getChar();
        break;
    default:
        if(ch=='<' || ch=='>'){
            addAndGetNextChar();
            if(ch=='='){
                addAndGetNextChar();
            }
            fillToken("COMPARE_OP", COMPARE_OP);
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
    case NEW_LINE:
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
     //printf("Proximo token: %s value: %d, Proximo lexema: %s\n",nextTokenn.name,nextTokenn.tokenType,lexema);    
        tokenList=insert(tokenList,nextTokenn.tokenType,nextTokenn.name, lineCount,lexema); //insere o token na lista
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
    
    parserFunction(tokenList);

    return 0;
}