#include <stdio.h>
#include <stdlib.h>
#include "../common/common.h"
#include "../lex/pl0_lex.h"
#include "../syntax/pl0_tax.h"
#include <string.h>

char temp[15] = { '\0'};
int table_index = 1;
int CurrentLevel = 0;
int CurrentError = 0;
int CurrentAddress = 0;
int tempAddress;
Error error[100];
static int PAREN_count = 0;
int IfThenStateEnd = 0;

int asmTotalLine = 0;
int localVariableAddress = 100;
int returnValueAddress = 120;//固定


void PrintError() {
	int i;
	for (i = 0; i < CurrentError; i++) {
		printf("%d行， %d位置处，%s\n\n", error[i].line, error[i].index, error[i].message);
	}
}

void DealError(PL0Lex * lex, int number) {
	error[CurrentError].index = lex->index[0];
	error[CurrentError].line = lex->line;
	switch (number)
	{
		case(0): {//error case 0 : undefined error
			strcpy(error[CurrentError].message, "undefined error ");
			PrintError();
			system("pause");
			exit(1);
			break;
		}
		case(1): {  //error1 case; Found "=" when expecting ":="
			strcpy(error[CurrentError].message, "Error 1 :Found = when expecting  := in statement");
			break;
		}
		case(2): {  //error2 case; Found ":=" when expecting "="
			strcpy(error[CurrentError].message, "Error 2 :Found := when expecting  = ");
			break;
		}
		case(3): {  //error3 case: there must be a number to follow '='
			strcpy(error[CurrentError].message, "Error 3 :there must be a number to follow =");
			break;
		}
		case(4): {  //error4 case: there must be an '=' to follow the identifier
			strcpy(error[CurrentError].message, "Error 4 :there must be an '=' to follow the identifier");
			break;
		}
		case(5): {  //error5 case: there must be "DO" to follow the "WHILE"
			strcpy(error[CurrentError].message, "Error 5: there must be DO to follow the WHILE");
			break;
		}
		case(6): {  //error6 case: there must be "THEN" to follow the "IF"
			strcpy(error[CurrentError].message, "Error 6: there must be THEN after the IF");
			break;
		}
		case(7): {  //error7 case: missing a  ")"
			strcpy(error[CurrentError].message, " Error 7 case: missing a  ) ");
			break;
		}
		case(8): {  //error case 8 : SEMICOLON should be COMMA
			strcpy(error[CurrentError].message, " Error case 8 : SEMICOLON should be COMMA");
			break;
		} 
		case(9): {  // error case 9: call statement missing an ident
			strcpy(error[CurrentError].message, "Error case 9: call statement missing an ident\n");
			break;
		}
		case(10): {  // error case 10: statemente missing a :=
			strcpy(error[CurrentError].message, "error case 10: statemente missing a := \n");
			break;
		}
		case(11): {  // const missing a ;
			strcpy(error[CurrentError].message, "error case 11: const missing a ; \n");
			break;
		}
		case(12): {  // var missing a ,
			strcpy(error[CurrentError].message, "error case 12: var missing a , \n");
			break;
		}
		case(13): {  // const missing a id
			strcpy(error[CurrentError].message, "error case 13: const missing a id \n");
			break;
		}
		case(14): {  // procedure declaration missing a id
			strcpy(error[CurrentError].message, "error case 14: procedure declaration missing a id \n");
			break;
		}
		case(15): {  // var missing a id
			strcpy(error[CurrentError].message, "error case 15: var missing a id \n");
			break;
		}
		case(16): {  // statement missing an end
			strcpy(error[CurrentError].message, "error case 16: statement missing an end \n");
			break;
		}
		case(17): {  // expression missing a ( when matching with )
			strcpy(error[CurrentError].message, "error case 17: expression missing a ( when matching with ) \n");
			break;
		}
		case(18): {  // 当前词法单元不在statement的first集合中
			strcpy(error[CurrentError].message, "error case 18: the first of syntax sentence is not in the {first} of statement\n");
			break;
		}
		case(19): { // missing ) after (
			strcpy(error[CurrentError].message, "error case 19: missing ) after (\n");
			break;
		}
		case(20): { // 条件的比较符出错
			strcpy(error[CurrentError].message, "error case 20: 条件的比较符出错\n");
			break;
		}
		case(21): { // Wrong beginning of procedure: could only use 'const', 'var', 'procdure', 'ident', 'call', 'begin', 'if', 'while'
			strcpy(error[CurrentError].message, "Wrong beginning of procedure: could only use 'const', 'var', 'procdure', 'ident', 'call', 'begin', 'if', 'while'\n");
			break;
		}
		case(22): { // Wrong beginning of statement: could only use 'ident', 'call', 'begin', 'if', 'while'
			strcpy(error[CurrentError].message, "Wrong beginning of statement: could only use 'ident', 'call', 'begin', 'if', 'while'\n");
			break;
		}
		case(23): { // Wrong beginning of condition: could only use 'ident', '(', 'number', 'minus','odd'
			strcpy(error[CurrentError].message, "Wrong beginning of condition: could only use 'ident', '(', 'number', 'minus','odd'\n");
			break;
		}
		case(24): { // Wrong beginning of factor: could only use 'ident', '(', 'number', 'minus'
			strcpy(error[CurrentError].message, "Wrong beginning of factor: could only use 'ident', '(', 'number', 'minus'\n");
			break;
		}
		case(25): {  // var missing a ;
			strcpy(error[CurrentError].message, " var missing a ; \n");
			break;
		}
		case(26): {  // procedure missing first ;
			strcpy(error[CurrentError].message, " procedure missing first ;\n");
			break;
		}
		case(27): {  // procedure missing second ;
			strcpy(error[CurrentError].message, " procedure missing second ;\n");
			break;
		}
		case(28): {  // statement missing a ;
			strcpy(error[CurrentError].message, " statement missing a ;\n");
			break;
		}
		case(29): {  // missing a , in const declaration
			strcpy(error[CurrentError].message, " missing a , in const declaration \n");
			break;
		}
		case(30): {  // An unrecognized character appears.
			strcpy(error[CurrentError].message, "An unrecognized character appears. \n");
			break;
		}
		case(31): {  // Too long identifier or number
			strcpy(error[CurrentError].message, "Too long identifier or number. \n");
			break;
		}
		case(32): {  // Wrong identifier format: identifier cannot start with a number.
			strcpy(error[CurrentError].message, "Wrong identifier format: identifier cannot start with a number. \n");
			break;
		}
		case(33): {  // Expect an '=' after ':'
			strcpy(error[CurrentError].message, "Expect an '=' after ':' \n");
			break;
		}
		case(34): {  // Expect an '=' after '!'
			strcpy(error[CurrentError].message, "Expect an '=' after '!' \n");
			break;
		}
		case(35): {  // Undeclared identifier
			strcpy(error[CurrentError].message, "Undeclared identifier \n");
			break;
		}
	}
	printf("%d行， %d位置处，%s\n\n", error[CurrentError].line, error[CurrentError].index, error[CurrentError].message);
	CurrentError++;
}

/*operation for stack*/
void initstack(Stack *s) {
	
	if (s == NULL) {
		printf("没有空间\n");
		system("pause");
	}
	s->top = 0;
	int i, j;
	for (i = 0; i < TXMAX; i++) {
		for (j = 0; j < 15; j++) {
			s->element[i][j] = '\0';
		}
	}
}

void pushstack(Stack *s, char *b) {
	(s->top)++;
	strcpy(s->element[s->top], b);
}

void popstack(Stack *s, char *b) {
	strcpy(b, s->element[s->top]);
	s->top--;
}

void printstack(Stack *s) {
	int i = 1;
	for (; i <= (s->top); i++) {
		printf("%s ", s->element[i]);
	}
	printf("\n");
}

/*operations for token table*/
void table_append(PL0Lex * lex, int kind) {
	strcpy(token_table[table_index].name, lex->last_id);
	token_table[table_index].kind = kind;
	switch (kind) {
		case ID_CONSTANT:
			if (lex->last_num > MAXADDRESS) {
				printf("the number is too great!\n");
				lex->last_num = 0;
			}
			token_table[table_index].value = lex->last_num;
			token_table[table_index].address = CurrentAddress;
			CurrentAddress++;
			break;
		case ID_VARIABLE:
			token_table[table_index].level = lex->last_level;
			token_table[table_index].address = CurrentAddress;
		   
			break;
		case ID_PROCEDURE:
			token_table[table_index].level = lex->last_level;
			token_table[table_index].address = CurrentAddress;
			//CurrentAddress++;
			break;
	} //switch
	table_index += 1;
} //table_append

int SearchTablebyName(char *b) {
	int j = -1;
	for (int i=0;i < table_index;i++) {
		if(strcmp(b, token_table[i].name) == 0) {
			j = i;break;
		}
	}
	return j;
}

int SearchTable(PL0Lex * lex, int parentFunction) {
	int j = -1;
	int i;
	while (1) {
		for (i = 0; i < token_table[parentFunction].TotalLocalVariable; i++) {
			if (strcmp(lex->last_id, token_table[token_table[parentFunction].LocalVariableIndex[i]].name) == 0) {
				j = token_table[parentFunction].LocalVariableIndex[i];
				return j;
			}
		}
		if (parentFunction == 0)break;
		parentFunction = token_table[parentFunction].function;
	}
	return j;
}

/*functions for syntax analysis*/
void statement(PL0Lex * lex, int parentFunction) { //SEMICOLON  STATEMENT
	int StatetempAddress = 0;
	int arrayOrId = 2; // 0表示array，1表示id
	if (lex->last_token_type == TOKEN_IDENTIFIER) {
		popstack(syntax, temp);
		pushstack(syntax, "Exp");
		pushstack(syntax, "BECOMES");
		pushstack(syntax, "L");
		pushstack(syntax, "ident");
		printstack(syntax);
		popstack(syntax, temp);
		printstack(syntax);
		int i = SearchTable(lex, parentFunction);
		StatetempAddress = token_table[i].address;
		if (i == -1) {
			DealError(lex, 35);
		}
		int temp2 = 1;
		PL0Lex_get_token(lex);
		int tempaddress;
		if (lex->last_token_type == TOKEN_LBRACKET) {
			arrayOrId = 0;
			fprintf(fout, "PUT 0\n"); asmTotalLine++;

			while (lex->last_token_type == TOKEN_LBRACKET) {
				pushstack(syntax, "]");
				pushstack(syntax, "EXP");
				pushstack(syntax, "[");
				printstack(syntax);
				popstack(syntax, temp);
				printstack(syntax);
				PL0Lex_get_token(lex);
				if (lex->last_token_type == lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER ||
					lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type == TOKEN_CALL) {
					//popstack(syntax, temp);
					printstack(syntax);
					expression(lex, parentFunction);
					fprintf(fout, "ADD\n"); asmTotalLine++;
					/*if (token_table[i].array[temp2] == 0) {
						break;
					}*/
					if (token_table[i].array[temp2] != 0) {
						fprintf(fout, "PUT %d\n", token_table[i].array[temp2]); asmTotalLine++; temp2++;
						fprintf(fout, "MUL\n"); asmTotalLine++;
					}
					if (lex->last_token_type == TOKEN_RBRACKET) {
						popstack(syntax, temp);
						printstack(syntax);
						PL0Lex_get_token(lex);
					}
				}
			}
			fprintf(fout, "PUT %d\n", token_table[i].address); asmTotalLine++;
			fprintf(fout, "ADD\n"); asmTotalLine++;
			
			fprintf(fout, "ST %d\n", localVariableAddress); asmTotalLine++;
			tempaddress = localVariableAddress;
			localVariableAddress--;
			popstack(syntax, temp);
			printstack(syntax);
		}
		else {
			arrayOrId = 1;
			popstack(syntax, temp);
			printstack(syntax);
			//fprintf(fout, "PUT %d\n", token_table[i].address); asmTotalLine++;
			
			//fprintf(fout, "ST %d\n", localVariableAddress); asmTotalLine++;
			tempaddress = localVariableAddress;
			localVariableAddress--;
		}
		if (lex->last_token_type == TOKEN_BECOMES) {
			popstack(syntax, temp);
			printstack(syntax);
			PL0Lex_get_token(lex);
			if (lex->last_token_type == lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER ||
				lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type == TOKEN_CALL) {
				expression(lex, parentFunction);
				if (arrayOrId == 0) {
					fprintf(fout, "PUT %d\n", tempaddress); asmTotalLine++;
					fprintf(fout, "LD\n"); asmTotalLine++;
					fprintf(fout, "ST\n"); asmTotalLine++;
				}
				else {
					fprintf(fout, "ST %d\n", token_table[i].address); asmTotalLine++;
				}
				//printstack(syntax);
			}
		}
		else if (lex->last_token_type == TOKEN_EQU) {  //error1 case; Found "=" when expecting ":="
			DealError(lex, 1);
			popstack(syntax, temp);
			printstack(syntax);
			PL0Lex_get_token(lex);
			if (lex->last_token_type == lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER ||
				lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type == TOKEN_CALL) expression(lex, parentFunction);
		}
		else if (lex->last_token_type == lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER ||
			lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type == TOKEN_CALL) {
			//error 10 : statement missing an :=
			//printf("There should be a := after identifier\n");
			DealError(lex, 10);
			popstack(syntax, temp);
			//popstack(syntax, temp);
			printstack(syntax);
			//PL0Lex_get_token(lex);
			expression(lex, parentFunction);
		}
		else {
			DealError(lex, 0);//undefined error
		}
	}
	else if (lex->last_token_type == TOKEN_CALL) {
		popstack(syntax, temp);
		pushstack(syntax, "ident");
		pushstack(syntax, "CALL");
		printstack(syntax);
		popstack(syntax, temp);
		printstack(syntax);
		PL0Lex_get_token(lex);
		if (lex->last_token_type == TOKEN_IDENTIFIER) {
			popstack(syntax, temp);
			printstack(syntax);
			int i = SearchTable(lex, parentFunction); //i 是函数名
			int tempLine = token_table[i].startLine;
			if (parentFunction != 0) {
				for (int k = 0; k < token_table[parentFunction].TotalLocalVariable;k++) {
					if (token_table[token_table[parentFunction].LocalVariableIndex[k]].kind != ID_PROCEDURE) {
						fprintf(fout, "LD %d\n", token_table[token_table[parentFunction].LocalVariableIndex[k]].address);asmTotalLine++;
					}
				}
			}
			fprintf(fout, "PUT %d\n", asmTotalLine + 2); asmTotalLine++;
			fprintf(fout, "JMP %d\n", token_table[i].startLine); asmTotalLine++;
			if (parentFunction != 0) {
				for (int k = token_table[parentFunction].TotalLocalVariable - 1; k >= 0;k--) {
					if (token_table[token_table[parentFunction].LocalVariableIndex[k]].kind != ID_PROCEDURE) {
						fprintf(fout, "ST %d\n", token_table[token_table[parentFunction].LocalVariableIndex[k]].address);asmTotalLine++;
					}
				}
			}
			if (i == -1) {
				DealError(lex, 35);
			}
			PL0Lex_get_token(lex);
		}
		else if (lex->last_token_type == TOKEN_SEMICOLON) { //error case 9 : call statement missing an ident
			popstack(syntax, temp);
			printstack(syntax);
			DealError(lex, 9);
			
		}
	}
	else if (lex->last_token_type == TOKEN_BEGIN) {
		popstack(syntax, temp);
		pushstack(syntax, "END");
		pushstack(syntax, "STATEMENTLIST");
		pushstack(syntax, "BEGIN");
		printstack(syntax); // END  STATEMENTLIST BEGIN
		popstack(syntax, temp);
		printstack(syntax);//END  STATEMENTLIST
		PL0Lex_get_token(lex);
		statementlist(lex, parentFunction);
		if (lex->last_token_type == TOKEN_END) {
			popstack(syntax, temp);
			printstack(syntax);
			PL0Lex_get_token(lex);
		}
		else if (lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_SEMICOLON) {
			popstack(syntax, temp);
			popstack(syntax, temp);
			printstack(syntax);
			DealError(lex, 16);
		}
	}
	else if (lex->last_token_type == TOKEN_IF) {
	popstack(syntax, temp);
	pushstack(syntax, "STATEMENT");
	pushstack(syntax, "THEN");
	pushstack(syntax, "CONDITION");
	pushstack(syntax, "IF");
	printstack(syntax);
	popstack(syntax, temp);
	printstack(syntax);
	PL0Lex_get_token(lex);
	int offset1 = 0;
	int offset2 = 0;
	int offsetend = 0;     //表示if elif else语句结束的文件指针偏移量
	int offsetJMPtoEnd[10] = { 0 };    //表示有多少个地方需要跳转到if then else 的终点
	int offsetAccount = 0;
	int ifelsethenEndLine = 0;
	int flag = 0;
	int flagIfThen = 1;//0 表示只是if 和then，1表示是if，elif和then
	if (lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER ||
		lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type == TOKEN_ODD || lex->last_token_type == TOKEN_CALL) {
		condition(lex, parentFunction);
		fprintf(fout, "NOT\n"); asmTotalLine++;
		offset1 = ftell(fout);
		fprintf(fout, "         \n"); asmTotalLine++;
	}
	else
	{
		DealError(lex, 23);
		while (lex->last_token_type != TOKEN_THEN) {
			PL0Lex_get_token(lex);
		}
		popstack(syntax, temp);
		printstack(syntax);
	}
	if (lex->last_token_type == TOKEN_THEN) {
		popstack(syntax, temp);
		printstack(syntax);
		PL0Lex_get_token(lex);
		flagIfThen = 0;
	}
	if (lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_BEGIN || lex->last_token_type == TOKEN_RETURN
		|| lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_PRINT) {
		if (strcmp((syntax->element[syntax->top]), "THEN") == 0) {   //error case 6: there must be THEN to follow the IF
			popstack(syntax, temp);
			printstack(syntax);
			DealError(lex, 6);
		}

		statement(lex, parentFunction);
		offsetJMPtoEnd[offsetAccount++] = ftell(fout);
		if (lex->last_token_type == TOKEN_ELIF) {
			fprintf(fout, "         \n"); asmTotalLine++;
		}
		offset2 = ftell(fout);
		ifelsethenEndLine = asmTotalLine;
		IfThenStateEnd = asmTotalLine;
		fseek(fout, offset1 - offset2, SEEK_CUR);
		fprintf(fout, "JPC %d", IfThenStateEnd);
		fseek(fout, offset2, SEEK_SET);
		while (lex->last_token_type == TOKEN_ELIF) {
			flag = 1;
			pushstack(syntax, "STATEMENT");
			pushstack(syntax, "THEN");
			pushstack(syntax, "CONDITION");
			pushstack(syntax, "ELIF");
			printstack(syntax);
			popstack(syntax, temp);
			printstack(syntax);
			PL0Lex_get_token(lex);
			condition(lex, parentFunction);
			fprintf(fout, "NOT\n"); asmTotalLine++;
			offset1 = ftell(fout);
			fprintf(fout, "         \n"); asmTotalLine++;
			if (lex->last_token_type == TOKEN_THEN) {
				popstack(syntax, temp);
				printstack(syntax);
				PL0Lex_get_token(lex);
				statement(lex, parentFunction);
				offsetJMPtoEnd[offsetAccount++] = ftell(fout);
				fprintf(fout, "         \n"); asmTotalLine++;
				offset2 = ftell(fout);
				ifelsethenEndLine = asmTotalLine;
				IfThenStateEnd = asmTotalLine;
				fseek(fout, offset1 - offset2, SEEK_CUR);
				fprintf(fout, "JPC %d", IfThenStateEnd);
				fseek(fout, offset2, SEEK_SET);
			}
		}
		if (lex->last_token_type == TOKEN_ELSE) {
			flag = 1;
			pushstack(syntax, "STATEMENT");
			pushstack(syntax, "ELSE");
			printstack(syntax);
			popstack(syntax, temp);
			printstack(syntax);
			PL0Lex_get_token(lex);
			statement(lex, parentFunction);
			offsetend = ftell(fout);
			ifelsethenEndLine = asmTotalLine;

		}
		if (flag == 1)for (int i = 0; i < offsetAccount; i++) {
			fseek(fout, offsetJMPtoEnd[i] - offsetend, SEEK_CUR);
			fprintf(fout, "JMP %d", ifelsethenEndLine);
			fseek(fout, offsetend, SEEK_SET);
		}
	}
	}
	else if (lex->last_token_type == TOKEN_WHILE) {
		popstack(syntax, temp);
		pushstack(syntax, "STATEMENT");
		pushstack(syntax, "DO");
		pushstack(syntax, "CONDITION");
		pushstack(syntax, "WHILE");
		printstack(syntax);
		int whiledostart = 0;    //while语句起始位置
		int conditionfinish = 0;
		int offset1 = 0;
		int offset2 = 0;
		whiledostart = asmTotalLine;
		popstack(syntax, temp);
		printstack(syntax);
		PL0Lex_get_token(lex);
		if (lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER ||
			lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type == TOKEN_ODD || lex->last_token_type == TOKEN_CALL) {
			condition(lex, parentFunction);
			fprintf(fout, "NOT\n"); asmTotalLine++;
			offset1 = ftell(fout);
			fprintf(fout, "           \n"); asmTotalLine++;
		}
		if (lex->last_token_type == TOKEN_DO) {
			popstack(syntax, temp);
			printstack(syntax);
			PL0Lex_get_token(lex);
		}
		if (lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_BEGIN || lex->last_token_type == TOKEN_RETURN
			|| lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE ||lex ->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_PRINT) {
			if (strcmp((syntax->element[syntax->top]), "DO") == 0) {   //error case 5: there must be DO to follow the WHILE
				popstack(syntax, temp);
				printstack(syntax);
				DealError (lex, 5);
			}
			statement(lex, parentFunction);
			fprintf(fout, "JMP %d\n", whiledostart); asmTotalLine++;
			offset2 = ftell(fout);
			int whiledoStateEnd = asmTotalLine;
			fseek(fout, offset1 - offset2, SEEK_CUR);
			fprintf(fout, "JPC %d", whiledoStateEnd);
			fseek(fout, offset2, SEEK_SET);
		}
	}
	else if (lex->last_token_type == TOKEN_DO) {
		popstack(syntax, temp);
		pushstack(syntax, "CONDITION");
		pushstack(syntax, "WHILE");
		pushstack(syntax, "STATEMENT");
		pushstack(syntax, "DO");
		printstack(syntax);
		popstack(syntax, temp);
		printstack(syntax);
		PL0Lex_get_token(lex);
		int dowhilestart = 0;
		if (lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_BEGIN || lex->last_token_type == TOKEN_RETURN
			|| lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_PRINT) {
			dowhilestart = asmTotalLine;
			statement(lex, parentFunction);
		}
		if (lex->last_token_type == TOKEN_WHILE) {
			popstack(syntax, temp);
			printstack(syntax);
			PL0Lex_get_token(lex);
		}
		if (lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER ||
			lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type == TOKEN_ODD
			|| lex->last_token_type == TOKEN_CALL) {
			condition(lex, parentFunction);
			fprintf(fout, "JPC %d\n", dowhilestart); asmTotalLine++;
		}
	}
	else if (lex->last_token_type == TOKEN_PRINT) {
		popstack(syntax, temp);
		pushstack(syntax, "EXP");
		pushstack(syntax, "PRINT");
		printstack(syntax);
		popstack(syntax, temp);
		printstack(syntax);
		PL0Lex_get_token(lex);
		expression(lex, parentFunction);   //？？？？？？
		fprintf(fout, "INT 0\n"); asmTotalLine++;
		fprintf(fout, "PUT %d\n", localVariableAddress);asmTotalLine++;
		fprintf(fout, "ST\n");asmTotalLine++;
	}
	else if (lex->last_token_type == TOKEN_RETURN) {
		popstack(syntax, temp);

		pushstack(syntax, "EXP");
		pushstack(syntax, "RETURN");
		printstack(syntax);
		popstack(syntax, temp);
		printstack(syntax);
		PL0Lex_get_token(lex);
		expression(lex, parentFunction);
		/*
		fprintf(fout, "ST %d\n", localVariableAddress); asmTotalLine++;
		localVariableAddress--;
		fprintf(fout, "ST %d\n", localVariableAddress); asmTotalLine++;
		fprintf(fout, "LD %d\n", (localVariableAddress + 1)); asmTotalLine++;
		fprintf(fout, "LD %d\n", localVariableAddress); asmTotalLine++;
		localVariableAddress++;
		*/
		fprintf(fout, "ST %d\n", returnValueAddress); asmTotalLine++;
		fprintf(fout, "JMP\n"); asmTotalLine++;
	}
	else {
		DealError(lex, 22);
		while (lex->last_token_type != TOKEN_IDENTIFIER && lex->last_token_type != TOKEN_CALL && lex->last_token_type != TOKEN_BEGIN
			&& lex->last_token_type != TOKEN_IF && lex->last_token_type != TOKEN_DO && lex->last_token_type != TOKEN_WHILE) {
			PL0Lex_get_token(lex);
		}
		//printf("不应该进入statement analysis\n");
	}
	
	printf("analysis the statement\n");
}

void statementlist(PL0Lex * lex, int parentFunction) {
	int flag = 0;
	int flag_2 =0 ; //用以修正第二个分号
	
	printstack(syntax);

	/*while (lex->last_token_type != TOKEN_END) {
		pushstack(syntax, "STATEMENTLIST");
		pushstack(syntax, "SEMICLON");
		pushstack(syntax, "STATEMENT"); //STATEMENTLIST  SEMICLON STATEMENT
		printstack(syntax);
		if (lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_BEGIN
			|| lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO) {
			statement(lex);
		}
		else
		{
			DealError(lex, 18);
			while (lex->last_token_type != TOKEN_IDENTIFIER && lex->last_token_type != TOKEN_CALL && lex->last_token_type != TOKEN_BEGIN
				&& lex->last_token_type != TOKEN_IF && lex->last_token_type != TOKEN_WHILE && lex->last_token_type != TOKEN_DO
				) {
				if (lex->last_token_type == TOKEN_END) {
					popstack(syntax, temp);
					popstack(syntax, temp);
					printstack(syntax); //STATEMENTLIST 
				}
				PL0Lex_get_token(lex);
			}

		}
		if (lex->last_token_type == TOKEN_SEMICOLON) {
			popstack(syntax, temp);
			printstack(syntax);
			PL0Lex_get_token(lex);
		}
	}
	popstack(syntax, temp);
	printstack(syntax);
	*/
	do {
		flag_2 = 0;
		if (lex->last_token_type == TOKEN_SEMICOLON) {
			flag = 0;
			popstack(syntax, temp);
			printstack(syntax);
			PL0Lex_get_token(lex);
		}
		pushstack(syntax, "SEMICOLON");
		pushstack(syntax, "STATEMENT");
		printstack(syntax); //SEMICOLON  STATEMENT
		if (lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_BEGIN || lex->last_token_type == TOKEN_RETURN
			|| lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_PRINT) {
			statement(lex, parentFunction);
			flag = 1;
		}
		else if(lex->last_token_type != TOKEN_END){
			while (lex->last_token_type != TOKEN_SEMICOLON) {
				PL0Lex_get_token(lex);
			}
			DealError(lex, 18);
			popstack(syntax, temp);
			printstack(syntax);
		}
		if (lex->last_token_type == TOKEN_END && flag == 1) {
			popstack(syntax, temp);
			DealError(lex, 28);
			break;
		}
		
		else if (lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_BEGIN
			|| lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO) {
			popstack(syntax, temp);
			DealError(lex, 28);
			flag_2 = 1;
			continue;

		}

	} while (lex->last_token_type == TOKEN_SEMICOLON || flag_2 == 1);
	popstack(syntax, temp);
	popstack(syntax, temp);
	popstack(syntax, temp);
	printf("Finished list\n");
}

void condition(PL0Lex * lex, int parentFunction) {
	popstack(syntax, temp);
	if (lex->last_token_type == TOKEN_ODD) {
		pushstack(syntax, "EXP");
		pushstack(syntax, "ODD");
		printstack(syntax);
		popstack(syntax, temp);
		printstack(syntax);
		PL0Lex_get_token(lex);
		expression(lex, parentFunction);
		fprintf(fout, "PUT 1\n"); asmTotalLine++;
		fprintf(fout, "AND\n"); asmTotalLine++;
	}
	else if (lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER ||
		lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type == TOKEN_CALL) {
		pushstack(syntax, "EXP");
		pushstack(syntax, "COMPARE");
		pushstack(syntax, "EXP");
		printstack(syntax);
		//PL0Lex_get_token(lex);
		expression(lex, parentFunction);
		if (lex->last_token_type >= TOKEN_EQU && lex->last_token_type <= TOKEN_GEQ) {
			operatoStack.top++;
			operatoStack.op[operatoStack.top] = lex->last_token_type - 4;
			popstack(syntax, temp);
			printstack(syntax);
			PL0Lex_get_token(lex);
			expression(lex, parentFunction);
			if (operatoStack.op[operatoStack.top] == EQU) {
				fprintf(fout, "EQ\n"); asmTotalLine++;
				operatoStack.top--;
			}
			else if (operatoStack.op[operatoStack.top] == NEQ) {
				fprintf(fout, "EQ\n"); asmTotalLine++;
				fprintf(fout, "NOT\n");asmTotalLine++;
				operatoStack.top--;
			}
			else if (operatoStack.op[operatoStack.top] == LES) {
				fprintf(fout, "GT\n"); asmTotalLine++;
				operatoStack.top--;
			}
			else if (operatoStack.op[operatoStack.top] == LEQ) {
				fprintf(fout, "GE\n"); asmTotalLine++;
				operatoStack.top--;
			}
			else if (operatoStack.op[operatoStack.top] == GTR) {
				fprintf(fout, "LT\n"); asmTotalLine++;
				operatoStack.top--;
			}
			else if (operatoStack.op[operatoStack.top] == GEQ) {
				fprintf(fout, "LE\n"); asmTotalLine++;
				operatoStack.top--;
			}
			
		}
		else {
			//printf("比较符出错\n");
			DealError(lex, 20);
			popstack(syntax, temp);
			printstack(syntax);
			while (lex->last_token_type != TOKEN_IDENTIFIER && lex->last_token_type != TOKEN_NUMBER && lex->last_token_type != TOKEN_LPAREN && lex->last_token_type != TOKEN_MINUS && lex->last_token_type != TOKEN_CALL) {
				PL0Lex_get_token(lex);
			}
			expression(lex, parentFunction);
		}
	}
	/*else {
		DealError(lex, 23);
		while (lex->last_token_type != TOKEN_MINUS && lex->last_token_type != TOKEN_ODD && lex->last_token_type != TOKEN_NUMBER && lex->last_token_type != TOKEN_IDENTIFIER) {
			PL0Lex_get_token(lex);
		}
	}*/
	printf("analysis the condition expression\n");
}

void expression(PL0Lex * lex, int parentFunction) {
	popstack(syntax, temp);
	pushstack(syntax, "J");
	pushstack(syntax, "TERM");
	printstack(syntax);
	//PL0Lex_get_token(lex);
	term(lex, parentFunction);
	while (lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_PLUS) {
		pushstack(syntax, "TERM");
		if (lex->last_token_type == TOKEN_MINUS) { 
			pushstack(syntax, "MINUS"); 
			operatoStack.top++;
			operatoStack.op[operatoStack.top] = SUB;
		}
		if (lex->last_token_type == TOKEN_PLUS) {
			pushstack(syntax, "PLUS");
			operatoStack.top++;
			operatoStack.op[operatoStack.top] = ADD;
		}
		printstack(syntax);
		popstack(syntax, temp);
		printstack(syntax);
		PL0Lex_get_token(lex);
		term(lex, parentFunction);
		if (operatoStack.op[operatoStack.top] == SUB) {
			fprintf(fout, "SUB\n"); asmTotalLine++;
			fprintf(fout, "PUT 0\n"); asmTotalLine++;
			fprintf(fout, "SUB\n"); asmTotalLine++;
			operatoStack.top--;
		}
		else if (operatoStack.op[operatoStack.top] == ADD) {
			fprintf(fout, "ADD\n"); asmTotalLine++;
			operatoStack.top--;
		}
	}
	popstack(syntax, temp);
	printstack(syntax);
	printf("analysis the expression\n");
}

void term(PL0Lex * lex, int parentFunction) {  //项
	popstack(syntax, temp);
	pushstack(syntax, "K");
	pushstack(syntax, "FACTOR");
	printstack(syntax);
	factor(lex, parentFunction);
	while (lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH) {
		pushstack(syntax, "FACTOR");
		if (lex->last_token_type == TOKEN_TIMES) {
			pushstack(syntax, "TIMES");
			operatoStack.top++;
			operatoStack.op[operatoStack.top] = MUL;
		}

		if (lex->last_token_type == TOKEN_SLASH) {
			pushstack(syntax, "SLASH");
			operatoStack.top++;
			operatoStack.op[operatoStack.top] = DIV;
		}
		printstack(syntax);
		popstack(syntax, temp);
		printstack(syntax);
		PL0Lex_get_token(lex);
		factor(lex, parentFunction);
		if (operatoStack.op[operatoStack.top] == MUL) {
			fprintf(fout, "MUL\n"); asmTotalLine++;
			operatoStack.top--;
		}
		else if (operatoStack.op[operatoStack.top] == DIV) {
			//fprintf(fout, "DIV\n"); asmTotalLine++;
			operatoStack.top--;fprintf(fout, "ST %d\n", localVariableAddress); asmTotalLine++;
			localVariableAddress--;
			fprintf(fout, "ST %d\n", localVariableAddress); asmTotalLine++;
			fprintf(fout, "LD %d\n", localVariableAddress + 1); asmTotalLine++;

			fprintf(fout, "LD %d\n", localVariableAddress); asmTotalLine++;
			localVariableAddress++;
			fprintf(fout, "DIV\n"); asmTotalLine++;
			operatoStack.top--;
		}
	}
	popstack(syntax, temp);
	printstack(syntax);
	printf("analysis the term\n");
}

void factor(PL0Lex * lex, int parentFunction) {
	if (lex->last_token_type == TOKEN_IDENTIFIER) {
		int arrayOrId = 1;
		popstack(syntax, temp);
		pushstack(syntax, "L");
		pushstack(syntax, "ident");
		printstack(syntax);
		popstack(syntax, temp);
		printstack(syntax);
		int i = SearchTable(lex, parentFunction);
		int offset = 0;     //数组元素的偏移量
		if (i == -1) {
			DealError(lex, 35);
		}
		PL0Lex_get_token(lex);
		int temp2 = 1;
		if (lex->last_token_type == TOKEN_LBRACKET) {
			fprintf(fout, "PUT 0\n"); asmTotalLine++;
			while (lex->last_token_type == TOKEN_LBRACKET) {

				pushstack(syntax, "]");
				pushstack(syntax, "EXP");
				pushstack(syntax, "[");
				printstack(syntax);
				popstack(syntax, temp);
				printstack(syntax);
				PL0Lex_get_token(lex);

				if (lex->last_token_type == lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER ||
					lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type == TOKEN_CALL) {
					//popstack(syntax, temp);
					printstack(syntax);
					expression(lex, parentFunction);
					fprintf(fout, "ADD\n"); asmTotalLine++;
					/*if (token_table[i].array[temp2] == 0) {
						break;
					}*/
					if (token_table[i].array[temp2] != 0) {
						fprintf(fout, "PUT %d\n", token_table[i].array[temp2]); asmTotalLine++; temp2++;
						fprintf(fout, "MUL\n"); asmTotalLine++;
					}
					if (lex->last_token_type == TOKEN_RBRACKET) {
						popstack(syntax, temp);
						printstack(syntax);
						PL0Lex_get_token(lex);
					}
				}
			}

			fprintf(fout, "PUT %d\n", token_table[i].address); asmTotalLine++;
			fprintf(fout, "ADD\n"); asmTotalLine++;
			fprintf(fout, "LD\n"); asmTotalLine++;
		}
		else
		{
			fprintf(fout, "LD %d\n", token_table[i].address);asmTotalLine++;
		}
		if (lex->last_token_type == TOKEN_RPAREN) {
			PAREN_count--;
			if (PAREN_count < 0) {
				DealError(lex, 17);
				PL0Lex_get_token(lex);
			}
		}
		popstack(syntax, temp);
		printstack(syntax);
	}
	else if (lex->last_token_type == TOKEN_NUMBER) {
		popstack(syntax, temp);
		pushstack(syntax, "NUMBER");
		printstack(syntax);
		popstack(syntax, temp);
		printstack(syntax);
		fprintf(fout, "PUT %d\n", lex->last_num); asmTotalLine++;
		PL0Lex_get_token(lex);
		if (lex->last_token_type == TOKEN_RPAREN) {
			PAREN_count--;
			if (PAREN_count < 0) {
				DealError(lex, 17);
				PL0Lex_get_token(lex);
			}
		}
	}
	else if (lex->last_token_type == TOKEN_MINUS) {
		popstack(syntax, temp);
		pushstack(syntax, "EXP");
		pushstack(syntax, "MINUS");
		printstack(syntax);
		popstack(syntax, temp);
		printstack(syntax);
		PL0Lex_get_token(lex);
		if (lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER ||
			lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type == TOKEN_CALL) {
			expression(lex, parentFunction);
		}
		if (lex->last_token_type == TOKEN_RPAREN) {
			PAREN_count--;
			if (PAREN_count < 0) {
				DealError(lex, 17);
				PL0Lex_get_token(lex);
			}
		}
		fprintf(fout, "PUT 0\n"); asmTotalLine++;
		fprintf(fout, "SUB\n"); asmTotalLine++;
	}
	else if (lex->last_token_type == TOKEN_LPAREN) {
		PAREN_count++;
		popstack(syntax, temp);
		pushstack(syntax, ")");
		pushstack(syntax, "EXP");
		pushstack(syntax, "(");
		printstack(syntax);
		popstack(syntax, temp);
		printstack(syntax);
		PL0Lex_get_token(lex);
		if (lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER ||
			lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type == TOKEN_CALL) {
			expression(lex, parentFunction);
		}
		if (lex->last_token_type == TOKEN_RPAREN) {
			popstack(syntax, temp);
			//printf("temp = %s  是右括号就对了\n", temp);
			printstack(syntax);
			PL0Lex_get_token(lex);
		}
		else {
			popstack(syntax, temp);
			printstack(syntax);
			DealError(lex, 19);
		}
		if (lex->last_token_type == TOKEN_RPAREN) {
			DealError(lex, 17);
			PL0Lex_get_token(lex);
		}
	}
	else if (lex->last_token_type == TOKEN_CALL) {
		popstack(syntax, temp);
		pushstack(syntax, "ident");
		pushstack(syntax, "call");
		printstack(syntax);
		popstack(syntax, temp);
		printstack(syntax);
		PL0Lex_get_token(lex);
		if (lex->last_token_type == TOKEN_IDENTIFIER) {
			popstack(syntax, temp);
			printstack(syntax);
			int i = SearchTable(lex, parentFunction); //i 是函数名
			int tempLine = token_table[i].startLine;
			if (parentFunction != 0) {
				for (int k = 0; k < token_table[parentFunction].TotalLocalVariable;k++) {
					if (token_table[token_table[parentFunction].LocalVariableIndex[k]].kind != ID_PROCEDURE) {
						fprintf(fout, "LD %d\n", token_table[token_table[parentFunction].LocalVariableIndex[k]].address);asmTotalLine++;
					}
				}
			}
			fprintf(fout, "PUT %d\n", asmTotalLine + 2); asmTotalLine++;
			fprintf(fout, "JMP %d\n", token_table[i].startLine); asmTotalLine++;
			if (parentFunction != 0) {
				for (int k = token_table[parentFunction].TotalLocalVariable - 1; k >= 0;k--) {
					if (token_table[token_table[parentFunction].LocalVariableIndex[k]].kind != ID_PROCEDURE) {
						fprintf(fout, "ST %d\n", token_table[token_table[parentFunction].LocalVariableIndex[k]].address);asmTotalLine++;
					}
				}
			}
			fprintf(fout, "LD %d\n", returnValueAddress);asmTotalLine++;
			if (i == -1) {
				DealError(lex, 35);
			}
			PL0Lex_get_token(lex);
		}
		if (lex->last_token_type == TOKEN_RPAREN) {
			PAREN_count--;
			if (PAREN_count < 0) {
				DealError(lex, 17);
				PL0Lex_get_token(lex);
			}
		}
	}
	else {
		DealError(lex, 24);
		while (lex->last_token_type != TOKEN_MINUS && lex->last_token_type != TOKEN_NUMBER && lex->last_token_type != TOKEN_IDENTIFIER && lex->last_token_type != TOKEN_CALL) {
			PL0Lex_get_token(lex);
				
		}
		factor(lex, parentFunction);
	}
	printf("analysis the factor\n");
}

void procedure_declaration(PL0Lex * lex, int parentFunction) { //SEMICOLON N  SEMICLON ident
	char tempname[30];
	if (lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_SEMICOLON) {
		if (lex->last_token_type == TOKEN_SEMICOLON) {
			popstack(syntax, temp);
			popstack(syntax, temp);
			printstack(syntax);
			DealError(lex, 14);
			PL0Lex_get_token(lex);
		}
		
		else if (lex->last_token_type == TOKEN_IDENTIFIER) {
			popstack(syntax, temp);
			printstack(syntax);
			lex->last_level = CurrentLevel;
			strcpy(tempname, lex->last_id);
			token_table[parentFunction].LocalVariableIndex[token_table[parentFunction].TotalLocalVariable] = table_index;
			token_table[parentFunction].TotalLocalVariable++;
			token_table[table_index].function = parentFunction;
			parentFunction = table_index;
			table_append(lex, ID_PROCEDURE);
			token_table[table_index - 1].startLine = asmTotalLine;
			PL0Lex_get_token(lex);
			if (lex->last_token_type != TOKEN_SEMICOLON) {

				DealError(lex, 26);
				popstack(syntax, temp);
				printstack(syntax);
			}
			else {
				popstack(syntax, temp);
				printstack(syntax);
				PL0Lex_get_token(lex);
			}
		}
		
		
		
		if (lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type != TOKEN_PROCEDURE
			&& lex->last_token_type != TOKEN_IDENTIFIER && lex->last_token_type != TOKEN_CALL && lex->last_token_type != TOKEN_IF
			&& lex->last_token_type != TOKEN_BEGIN && lex->last_token_type != TOKEN_WHILE)
			DealError(lex,21);
		while (lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type != TOKEN_PROCEDURE
			&& lex->last_token_type != TOKEN_IDENTIFIER && lex->last_token_type != TOKEN_CALL && lex->last_token_type != TOKEN_IF
			&& lex->last_token_type != TOKEN_BEGIN && lex->last_token_type != TOKEN_WHILE) {
			PL0Lex_get_token(lex);
		}
		
		if (lex->last_token_type == TOKEN_CONST || lex->last_token_type == TOKEN_VAR || lex->last_token_type == TOKEN_PROCEDURE
			|| lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_IF
			|| lex->last_token_type == TOKEN_BEGIN || lex->last_token_type == TOKEN_WHILE) {
			CurrentLevel++;
			program_block(lex, parentFunction);
			CurrentLevel--;
			/*if (lex->last_token_type == TOKEN_RETURN) {
				pushstack(syntax, "EXP");
				pushstack(syntax, "RETURN");
				printstack(syntax);
				popstack(syntax, temp);
				printstack(syntax);
				PL0Lex_get_token(lex);
				expression(lex);
			}*/
			
			int j = SearchTablebyName(tempname);
			token_table[j].endLine = asmTotalLine;
			fprintf(fout, "JMP\n"); asmTotalLine++;
			/*if (lex->last_token_type != TOKEN_SEMICOLON) {
				popstack(syntax, temp);
				printstack(syntax);
				printf("There must be an ; follow the procedure! \n");
			}*/
		}
		else {
			printf("There must be a first{program} element!\n");

			PL0Lex_get_token(lex);
			program_block(lex, parentFunction);
			
		}
	}
	else {
		printf("There must be an identifier to follow 'procedure'\n");
		
	}
}

void var_declaration(PL0Lex * lex, int parentFunction) {
	if (lex->last_token_type == TOKEN_IDENTIFIER) {
		popstack(syntax, temp);
		pushstack(syntax, "I");
		pushstack(syntax, "L");
		pushstack(syntax, "ident");
		printstack(syntax);
		popstack(syntax, temp);
		printstack(syntax);
		lex->last_level = CurrentLevel;
		token_table[parentFunction].LocalVariableIndex[token_table[parentFunction].TotalLocalVariable] = table_index;
		token_table[parentFunction].TotalLocalVariable++;
		token_table[table_index].function = parentFunction;
		table_append(lex, ID_VARIABLE);
		int temp2 = 1;
		PL0Lex_get_token(lex);
		// by zhongxiang
		fprintf(fout, "PUT %d\n", -1);asmTotalLine++;
		fprintf(fout, "ST %d\n",CurrentAddress);asmTotalLine++;
		while (lex->last_token_type == TOKEN_LBRACKET) {
			pushstack(syntax, "]");
			pushstack(syntax, "num");
			pushstack(syntax, "[");
			printstack(syntax);
			popstack(syntax, temp);
			printstack(syntax);
			PL0Lex_get_token(lex);
			if (lex->last_token_type == TOKEN_NUMBER) {
				popstack(syntax, temp);
				printstack(syntax);
				temp2 = temp2 * lex->last_num;
				token_table[table_index - 1].array[token_table[table_index - 1].dimension] = lex->last_num;
				token_table[table_index - 1].dimension++;
				PL0Lex_get_token(lex);
				if (lex->last_token_type == TOKEN_RBRACKET) {
					popstack(syntax, temp);
					printstack(syntax);
					PL0Lex_get_token(lex);
				}
			}
		}
		CurrentAddress += temp2;
		popstack(syntax, temp);
	}
	else {
		DealError(lex, 15);
		//printf("There must be an identifier to follow 'var'\n");
	}
}

void const_declaration(PL0Lex * lex, int parentFunction) {
	if (lex->last_token_type == TOKEN_IDENTIFIER) {
		
		popstack(syntax, temp);
		pushstack(syntax, "E");
		pushstack(syntax, "number");
		pushstack(syntax, "EQU");
		pushstack(syntax, "ident");
		printstack(syntax);

		popstack(syntax, temp); 
		printstack(syntax);
		lex->last_level = CurrentLevel;
		token_table[parentFunction].LocalVariableIndex[token_table[parentFunction].TotalLocalVariable] = table_index;
		token_table[parentFunction].TotalLocalVariable++;
		token_table[table_index].function = parentFunction;
		table_append(lex, ID_CONSTANT);
		PL0Lex_get_token(lex);
		if (lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_BECOMES) {
			if (lex->last_token_type == TOKEN_BECOMES)
				DealError(lex, 2);

			popstack(syntax, temp);
			printstack(syntax);
			PL0Lex_get_token(lex);
			if (lex->last_token_type == TOKEN_NUMBER) {
				lex->last_level = CurrentLevel;
				tempAddress = CurrentAddress - 1;
				fprintf(fout, "PUT %d\n", lex->last_num); asmTotalLine++;
				fprintf(fout, "PUT %d\n", tempAddress); asmTotalLine++;
				fprintf(fout, "ST\n"); asmTotalLine++;
				popstack(syntax, temp);
				printstack(syntax);
				

				PL0Lex_get_token(lex);

			} 
			else {   //error case3: there must be a number to follow '='
				popstack(syntax, temp);
				printstack(syntax);
				DealError(lex, 3);
				while (lex->last_token_type != TOKEN_COMMA && lex->last_token_type != TOKEN_SEMICOLON) {
					PL0Lex_get_token(lex);
				}
			}
		} 
		else if(lex->last_token_type == TOKEN_NUMBER){  // error case4 : there must be an '=' to follow the identifier
			popstack(syntax, temp);
			printstack(syntax);
			lex->last_level = CurrentLevel;
			table_append(lex, ID_CONSTANT);
			popstack(syntax, temp);
			printstack(syntax);
			DealError(lex, 4);
			PL0Lex_get_token(lex);
			
		}
	}
	else {
		//printf("There must be an identifier to follow 'const'\n");
		DealError(lex, 13);
		while (lex->last_token_type != TOKEN_IDENTIFIER && lex->last_token_type!= TOKEN_COMMA && 
			lex->last_token_type != TOKEN_SEMICOLON)
		{
			PL0Lex_get_token(lex);
		}

		
	}
} //const_declaration

void program_begin(PL0Lex * lex) {
	initstack(syntax);
	pushstack(syntax, "DOLLA");
	pushstack(syntax, "B");
	program_block(lex, 0);
	printstack(syntax);
	printf("------\n");
	if (lex->last_token_type == TOKEN_PERIOD) {
		popstack(syntax, temp);
		printstack(syntax);
		printf("语法分析完毕\n");
	}
	fprintf(fout, "INT 1\n"); asmTotalLine++;
}

void program_block(PL0Lex * lex, int parentFunction) {
	printf("analysis the program block\n");
	printstack(syntax);
	// PL0Lex * lex = (PL0Lex *) calloc(1, sizeof(PL0Lex));
	// PL0Lex_get_token(lex);
	do {
		if (lex->last_token_type == TOKEN_CONST) {
			pushstack(syntax, "S");
			printstack(syntax);
			popstack(syntax, temp);
			pushstack(syntax, "C");
			printstack(syntax);
			popstack(syntax, temp);
			pushstack(syntax, "SEMICOLON");
			pushstack(syntax, "V");
			pushstack(syntax, "const");
			printstack(syntax);
			popstack(syntax, temp);
			printstack(syntax);
			PL0Lex_get_token(lex);
			do {
				const_declaration(lex, parentFunction);
				while (lex->last_token_type == TOKEN_COMMA || lex->last_token_type == TOKEN_IDENTIFIER) {
					if (lex->last_token_type == TOKEN_IDENTIFIER) {
						popstack(syntax, temp);
						printstack(syntax);
						pushstack(syntax, "V");
						pushstack(syntax, "COMMA");
						printstack(syntax);
						popstack(syntax, temp);
						printstack(syntax);
						
						DealError(lex, 29);
						const_declaration(lex, parentFunction);
					}
					else {
						popstack(syntax, temp);
						if (strcmp(temp, "E") != 0) {
							printf("出问题\n");
						}
						pushstack(syntax, "V");
						pushstack(syntax, "COMMA");
						printstack(syntax);
						popstack(syntax, temp);
						printstack(syntax);
						
						PL0Lex_get_token(lex);
						const_declaration(lex, parentFunction);
					}
					
				}
				if (lex->last_token_type == TOKEN_SEMICOLON) {
					popstack(syntax, temp);
					printstack(syntax);
					popstack(syntax, temp);
					printstack(syntax);
					PL0Lex_get_token(lex);
					
					
				}
				else {
					popstack(syntax, temp);
					printstack(syntax);
					popstack(syntax, temp);
					printstack(syntax);
					
					DealError(lex, 11);
				}
			} while (lex->last_token_type == TOKEN_IDENTIFIER);
		}
		else if (lex->last_token_type == TOKEN_VAR) {
			pushstack(syntax, "S");
			printstack(syntax);
			popstack(syntax, temp);
			pushstack(syntax, "M");
			printstack(syntax);
			popstack(syntax, temp);
			pushstack(syntax, "SEMICOLON");
			pushstack(syntax, "H");
			pushstack(syntax, "var");
			printstack(syntax);
			popstack(syntax, temp);
			printstack(syntax);
			PL0Lex_get_token(lex);
			do {
				var_declaration(lex, parentFunction);
				while (lex->last_token_type == TOKEN_COMMA || lex->last_token_type == TOKEN_IDENTIFIER) {
					if (lex->last_token_type == TOKEN_IDENTIFIER) {
						popstack(syntax, temp);
						printstack(syntax);
						pushstack(syntax, "H");
						pushstack(syntax, "COMMA");
						printstack(syntax);
						popstack(syntax, temp);
						printstack(syntax);
						
						DealError(lex, 12);
						var_declaration(lex, parentFunction);
					}
					else {
						popstack(syntax, temp);
						printstack(syntax);
						pushstack(syntax, "H");
						pushstack(syntax, "COMMA");
						printstack(syntax);
						popstack(syntax, temp);
						printstack(syntax);

						PL0Lex_get_token(lex);
						var_declaration(lex, parentFunction);
					}
					
				}
				if (lex->last_token_type == TOKEN_SEMICOLON) {
					popstack(syntax, temp);
					printstack(syntax);
					popstack(syntax, temp);
					printstack(syntax);
					PL0Lex_get_token(lex);
				}
				else {
					popstack(syntax, temp);
					printstack(syntax);
					popstack(syntax, temp);
					printstack(syntax);
					DealError(lex, 25);   //missing a ; after var
					
				}
			} while (lex->last_token_type == TOKEN_IDENTIFIER);
		}
		else if (lex->last_token_type == TOKEN_PROCEDURE) {
			int offset1, offset2;
			offset1 = ftell(fout);
			fprintf(fout, "JMP       \n"); asmTotalLine++;
			pushstack(syntax, "SEMICOLON");
			pushstack(syntax, "N");
			pushstack(syntax, "SEMICOLON");
			pushstack(syntax, "ident");
			pushstack(syntax, "PROCEDURE");
			printstack(syntax); //SEMICOLON N  SEMICLON ident procedure
			popstack(syntax, temp);
			printstack(syntax);//SEMICOLON N  SEMICLON ident
			PL0Lex_get_token(lex);
			
			procedure_declaration(lex, parentFunction);
			
			if (lex->last_token_type == TOKEN_SEMICOLON) {
				popstack(syntax, temp);
				printstack(syntax);
				PL0Lex_get_token(lex);
			}
			else {
				popstack(syntax, temp);
				printstack(syntax);
				DealError(lex, 27);   //missing second ; after procedure
			}
			offset2 = ftell(fout);
			fseek(fout, offset1 - offset2, SEEK_CUR);
			fprintf(fout, "JMP %d", asmTotalLine);
			fseek(fout, offset2, SEEK_SET);
		}
		else if (lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_BEGIN || lex->last_token_type == TOKEN_RETURN
			|| lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_PRINT) {
			pushstack(syntax, "STATEMENT");
			printstack(syntax);
			statement(lex, parentFunction);
			
			break;
		}
		else {
			DealError(lex, 21);
			PL0Lex_get_token(lex);
		}
	} while(lex->last_token_type == TOKEN_CONST || lex->last_token_type == TOKEN_VAR || lex->last_token_type == TOKEN_PROCEDURE || lex->last_token_type == TOKEN_NULL||
	lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_BEGIN
		|| lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_RETURN);
	popstack(syntax, temp);
	printstack(syntax);
} //program_block
