typedef struct token {
    int tokenType;
    char name[30];
}Token;
Token* create(Token* list);
