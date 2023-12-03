typedef struct token Token;
struct token{int tokenType;char name[30];Token* prox;};
Token* create();
Token* insert(Token* list, int tokenType,char* name);
void printList(Token* list);
