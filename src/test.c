#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "common/common.h"
#include "lex/pl0_lex.h"
#include "syntax/pl0_tax.h"

void show_help(const char * arg0)
{
	printf("Usage: %s <src>\n\n", arg0);
}

int main(int argc, char * argv[])
{
	/* Parse arguments */
	if (argc != 2)
	{
		show_help(argv[0]);
		exit(-1);
	}
	fin = fopen(argv[1], "rb");
	if (!fin)
	{
		printf("Fatal: Cannot open file for reading: %s\n", argv[1]);
		exit(-1);
	}

	/* Start */
	/* Parse arguments */

	fin = fopen("examples/mytest.txt", "r");
	if (!fin)
	{
		printf("Fatal: Cannot open file for reading:\n");
		exit(-1);
	}

	/* Start */
	printf("=== This is the program for PL/0 testing ===\n");

	/* Setup */
	compiler = PL0Compiler_create();

	/* Lexical Analysis */
	printf("--- Lexical Analysis testing ---\n");
	PL0Lex * lex = compiler->lex;
	/*
	while (PL0Lex_get_token(lex))
	{
	//断言不能有TOKEN_NULL、TOKEN_RESWORDS、TOKEN_SYMBOL三类
	assert(lex->last_token_type != TOKEN_NULL);
	assert(lex->last_token_type != TOKEN_RESWORDS);
	assert(lex->last_token_type != TOKEN_SYMBOL);

	if (lex->last_token_type == TOKEN_IDENTIFIER)
	{
	printf("Identifier: \t%s\t%d:%d-%d\n", lex->last_id, lex->line, lex->index[0], lex->index[1]);
	}
	else if (lex->last_token_type == TOKEN_NUMBER)
	{
	printf("Number: \t%d\t%d:%d-%d\n", lex->last_num, lex->line, lex->index[0], lex->index[1]);
	}
	else if (lex->last_token_type > TOKEN_RESWORDS)
	{
	printf("Reserved word: \t%s\t%d:%d-%d\n", TOKEN_RESERVED_WORDS[lex->last_token_type - TOKEN_RESWORDS - 1],lex->line, lex->index[0], lex->index[1]);
	}
	else
	{
	printf("Symbol: \t%s\t%d:%d-%d\n", TOKEN_SYMBOLS[lex->last_token_type - TOKEN_SYMBOL - 1], lex->line, lex->index[0], lex->index[1]);
	}
	}

	printf("--- Lexical Analysis testing end. ---\n");
	*/

	//test syntax ayalysis
	syntax = (Stack *)malloc(sizeof(Stack));
	PL0Lex_get_token(lex);
	program_begin(lex);

	PrintError();
	// Cleanup 
	fclose(fin);

	/* Finish */
	printf("=== Normal end for testing. ===\n");
	system("pause");
	return 0;
}
