#include "../common/common.h"

#ifndef __PL0_LEX_H__
#define __PL0_LEX_H__


#define NRW			15	/* Number of reserved words */
#define NSYM		21	/* Number of symbols */
#define MAX_NUM_LEN	9	/* Maximum length of a number, set to 9 to fit in range of C (-2147483648 to 2147483647) */
#define MAX_ID_LEN	29	/* Maximum length of an identifier */
#define MaxTableNum 500 //词法分析结果报存的最大值

struct _tPL0Compiler;

typedef enum _tPL0TokenType {
	TOKEN_NULL,
	TOKEN_IDENTIFIER,
	TOKEN_NUMBER,
	TOKEN_SYMBOL,	/* Below are accepted symbols */
	TOKEN_PLUS,		/* + */
	TOKEN_MINUS,	/* - */
	TOKEN_TIMES,	/* * */
	TOKEN_SLASH,	/* / */
	TOKEN_EQU,  	/* = */
	TOKEN_NEQ,  	/* <> */
	TOKEN_LES,  	/* < */
	TOKEN_LEQ,  	/* <= */
	TOKEN_GTR,  	/* > */
	TOKEN_GEQ,  	/* >= */
	TOKEN_LPAREN,	/* ( */
	TOKEN_RPAREN,	/* ) */
	TOKEN_LBRACKET, /* [ */
	TOKEN_RBRACKET, /* ] */
	TOKEN_COMMA,	/* , */
	TOKEN_SEMICOLON,/* ; */
	TOKEN_PERIOD,	/* . */
	TOKEN_BECOMES,	/* := */
	TOKEN_RESWORDS, /* Below are reserved words */
	TOKEN_VAR,
	TOKEN_CONST,
	TOKEN_PROCEDURE,
	TOKEN_BEGIN,
	TOKEN_END,
	TOKEN_IF,
	TOKEN_THEN,
	TOKEN_DO,
	TOKEN_WHILE,
	TOKEN_CALL,
	TOKEN_ODD,
	TOKEN_RETURN,
	TOKEN_PRINT,
	TOKEN_ELIF,
	TOKEN_ELSE
} PL0TokenType;

extern const char * TOKEN_RESERVED_WORDS[NRW];  //保留字和数组里依次比较，具体的定义在pl0_lex.c文件中
extern const char * TOKEN_SYMBOLS[NSYM];
//extern struct _tPL0Lex LexTable[MaxTableNum];   //报存词法分析结果
//extern int LexTableIndex = 0;     //词法分析的token数量

typedef struct _tPL0Lex {
	//Parent return pointer  用于回指
	struct _tPL0Compiler * compiler;
	
	// For output  输出的三元组 用于表示token的信息

	PL0TokenType last_token_type;
	char last_id[MAX_ID_LEN + 1];
	int last_num;
	int line;      //该token所在的行号
	int index[2];  //该token所在的行的起始位置和终止位置

	int last_level;
	/** --------------------------
	 * TODO: Your variables here
	 */
} PL0Lex;

PL0Lex * PL0Lex_create(PL0Compiler * parent);
BOOL PL0Lex_destroy(PL0Lex * lex);

BOOL PL0Lex_get_token(PL0Lex * lex);

#endif /* pl0_lex.h */
