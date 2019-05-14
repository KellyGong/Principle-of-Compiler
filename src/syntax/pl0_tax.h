#ifndef __PL0_TAX_H__
#define __PL0_TAX_H__

#define TXMAX				500 		// max length of token table
#define MAXADDRESS 	32767		// max address


typedef enum _toptype {
	ADD,
	SUB,
	MUL,
	DIV,
	EQU,
	NEQ,
	LES,//<
	LEQ,//<=
	GTR,//>
	GEQ//>=
}optype;
/*variables for token table*/

/*struct for token table*/
typedef struct {
	char name[MAX_ID_LEN + 1];
	int kind;
	int value;
	short level;
	short address;
	short startLine;
	short endLine;
	int dimension; //用于表示数组维数
	int array[3];
	int TotalLocalVariable;     //函数的token_table才有，表示有多少个变量在该函数内
	int LocalVariableIndex[10];     //该函数所有变量在token_table的索引
	int function;  //表示父函数的下标
} Table;

typedef  struct _tStack{
	int top;
	char element[TXMAX][15];
}Stack;

typedef struct _toperator {
	optype op[15];
	int top;
}OperatorStack;

OperatorStack operatoStack;

Stack *syntax;

typedef struct _tError {
	int line;
	int index;
	char message[80];
}Error;

void PrintError();
void DealError(PL0Lex * lex, int number);
void initstack(Stack *s);
void pushstack(Stack *s, char *b);
void popstack(Stack *s, char *b);
void printstack(Stack *s);

/*definition for token table*/
Table token_table[TXMAX];

/*identifier type*/
enum idtype {
	ID_CONSTANT,
	ID_VARIABLE,
	ID_PROCEDURE
};


//extern char temp[10] = {'\0'};

/*operations for token table*/
void table_append(PL0Lex * lex, int kind);

/*functions for syntax analysis*/
void statement(PL0Lex * lex, int parentFunction); //analysis the statement
void condition(PL0Lex * lex, int parentFunction); //analysis the condition statement
void expression(PL0Lex * lex, int parentFunction); //analysis the expression
void term(PL0Lex * lex, int parentFunction); //analysis the term
void factor(PL0Lex * lex, int parentFunction); //analysis the factor
void program_block(PL0Lex * lex, int parentFunction); //analysis the program block
void program_begin(PL0Lex * lex); //begin the program
void statementlist(PL0Lex * lex, int parentFunction);
#endif //pl0_tax.h