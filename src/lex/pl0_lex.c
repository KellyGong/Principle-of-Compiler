#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../lex/pl0_lex.h"
#include "../syntax/pl0_tax.h"
#include "../common/common.h"



const char * TOKEN_RESERVED_WORDS[NRW] = {"var", "const", "procedure", "begin", "end", "if", "then", "do", "while", "call", "odd", "return", "print", "elif", "else"};
const char * TOKEN_SYMBOLS[NSYM] = { "+", "-", "*", "/", "=", "!=", "<", "<=", ">", ">=", "(", ")","[", "]" ",", ";", ".", ":=" };

int flag = 0;  //ѭ����־λ��������ע��ʱ��ε���PL0Lex_get_token��������
int tokenNum = 0;
char ch;   //����ĵ�ǰ�ַ�
int CurrentLine = 1;   //��ǰ���ڵ�����
int CurrentIndex = -1;  //��ǰ�����е�����λ��
int tokenlocation[2] = { 0 };    //��token����λ�õ���������

/*void addLexTable(PL0Lex * lex) {
	LexTable[LexTableIndex].last_token_type = lex->last_token_type;
	LexTable[LexTableIndex].last_num = lex->last_num;
	LexTable[LexTableIndex].last_level = lex->last_level;
	LexTable[LexTableIndex].line = lex->line;
	LexTable[LexTableIndex].index[0] = lex->index[0];
	LexTable[LexTableIndex].index[1] = lex->index[1];
	LexTableIndex++;
}
*/
BOOL mygetchar() {
	ch = fgetc(fin);
	CurrentIndex++;
	if (ch == EOF) {
		printf("�ļ������Ѿ�����");
		PrintError();
		printf("%d�� %d������ ����һ��dolla����\n", CurrentLine, CurrentLine);
		system("pause");
		exit(0); //�ļ����ݶ���
	}
	else return TRUE;
}

PL0Lex * PL0Lex_create(PL0Compiler * parent)
{
	PL0Lex * lex = (PL0Lex *) calloc(1, sizeof(PL0Lex));
	lex->compiler = parent;

	return lex;
}

BOOL DealSymbol(PL0Lex * lex) {
	if (ch == '+') {
		lex->last_token_type;
		lex->last_token_type = TOKEN_PLUS;
		lex->line = CurrentLine;
		lex->last_id[0] = '+';
		lex->index[0] = CurrentIndex;
		lex->index[1] = CurrentIndex;
		//addLexTable(lex);
		return TRUE;
	}
	else if (ch == '-') {
		if (lex->last_token_type == TOKEN_RPAREN || lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER) {
			lex->last_token_type = TOKEN_MINUS;
			lex->line = CurrentLine;
			lex->last_id[0] = '-';
			lex->index[0] = CurrentIndex;
			lex->index[1] = CurrentIndex;
			return TRUE;
		}
		else {
			mygetchar();
			//add by mzk
			if (isdigit(ch)) {
				lex->index[0] = CurrentIndex - 1;
				int num_temp = 0;
				for (; isdigit(ch); mygetchar()) {
					num_temp = num_temp * 10 + (ch - '0');
				}
				lex->last_num = 0 - num_temp;
				lex->last_token_type = TOKEN_NUMBER;
				lex->line = CurrentLine;
				lex->index[1] = (--CurrentIndex);
				fseek(fin, -1, 1);
				//addLexTable(lex);
				return TRUE;
			}
			else {
				fseek(fin, -1, 1);
				lex->last_token_type = TOKEN_MINUS;
				lex->line = CurrentLine;
				lex->last_id[0] = '-';
				lex->index[0] = CurrentIndex;
				lex->index[1] = CurrentIndex;
				return TRUE;
			}

		}
		/*
		mygetchar();
		//add by mzk

		if (isdigit(ch)) {
		lex->index[0] = CurrentIndex-1;
		int num_temp = 0;
		for (; isdigit(ch); mygetchar()) {
		num_temp = num_temp * 10 + (ch - '0');
		}
		lex->last_num = 0 - num_temp;
		lex->last_token_type = TOKEN_NUMBER;
		lex->line = CurrentLine;
		lex->index[1] = (--CurrentIndex);
		fseek(fin, -1, 1);
		//addLexTable(lex);
		return TRUE;
		}
		else {
		fseek(fin, -1, 1);
		lex->last_token_type = TOKEN_MINUS;
		lex->line = CurrentLine;
		lex->last_id[0] = '-';
		lex->index[0] = CurrentIndex;
		lex->index[1] = CurrentIndex;
		return TRUE;
		}
		*/
		
		//addLexTable(lex);
		
	}
	else if (ch == '*') {
		lex->last_token_type = TOKEN_TIMES;
		lex->line = CurrentLine;
		lex->last_id[0] = '*';
		lex->index[0] = CurrentIndex;
		lex->index[1] = CurrentIndex;
		//addLexTable(lex);
		return TRUE;
	}
	else if (ch == '/') {
		mygetchar();
		if (ch != '/' && ch != '*') {
			lex->last_token_type = TOKEN_SLASH;
			lex->line = CurrentLine;
			lex->last_id[0] = '/';
			lex->index[0] = (--CurrentIndex);
			lex->index[1] = CurrentIndex;
			fseek(fin, -1, 1);
			//addLexTable(lex);
			return TRUE;
		}
		else if (ch == '/') {
			flag = 1;
			while (ch != '\n') {
				mygetchar();
			}
			CurrentLine++;
			CurrentIndex = -1;
		}
		else if (ch == '*') {
			flag = 1;
			mygetchar();
			while (1) {
				if (ch == '\n' || ch == '\r') {
					CurrentLine++;
					CurrentIndex = -1;
				}
				if (ch == '*') {
					mygetchar();
					if (ch == '/') break;

				}
				mygetchar();
			}

		}
	}
	else if (ch == '<') {
		mygetchar();
		if (ch == '=') {
			lex->last_token_type = TOKEN_LEQ;
			lex->line = CurrentLine;
			lex->last_id[0] = '<';
			lex->last_id[1] = '=';
			lex->index[0] = (CurrentIndex-1);
			lex->index[1] = CurrentIndex;
			//addLexTable(lex);
			return TRUE;
		}
		else {
			lex->last_token_type = TOKEN_LES;
			lex->line = CurrentLine;
			lex->last_id[0] = '<';
			lex->index[0] = --CurrentIndex;
			lex->index[1] = CurrentIndex;
			fseek(fin, -1, 1);
			//addLexTable(lex);
			return TRUE;
		}
	}
	else if (ch == '=') {
		lex->last_token_type = TOKEN_EQU;
		lex->line = CurrentLine;
		lex->last_id[0] = '=';
		lex->index[0] = CurrentIndex;
		lex->index[1] = CurrentIndex;
		//addLexTable(lex);
		return TRUE;
	}
	else if (ch == '>') {
		mygetchar();
		if (ch == '=') {
			lex->last_token_type = TOKEN_GEQ;
			lex->line = CurrentLine;
			lex->last_id[0] = '>';
			lex->last_id[1] = '=';
			lex->index[0] = (CurrentIndex - 1);
			lex->index[1] = CurrentIndex;
			//addLexTable(lex);
			return TRUE;
		}
		else {
			lex->last_token_type = TOKEN_GTR;
			lex->line = CurrentLine;
			lex->last_id[0] = '>';
			lex->index[0] = --CurrentIndex;
			lex->index[1] = CurrentIndex;
			fseek(fin, -1, 1);
			//addLexTable(lex);
			return TRUE;
		}
	}
	
	else if (ch == '(') {
		lex->last_token_type = TOKEN_LPAREN;
		lex->line = CurrentLine;
		lex->last_id[0] = '(';
		lex->index[0] = CurrentIndex;
		lex->index[1] = CurrentIndex;
		//addLexTable(lex);
		return TRUE;
	}
	else if (ch == ')') {
		lex->last_token_type = TOKEN_RPAREN;
		lex->line = CurrentLine;
		lex->last_id[0] = ')';
		lex->index[0] = CurrentIndex;
		lex->index[1] = CurrentIndex;
		//addLexTable(lex);
		return TRUE;
	}
	else if (ch == '[') {
		lex->last_token_type = TOKEN_LBRACKET;
		lex->line = CurrentLine;
		lex->last_id[0] = '[';
		lex->index[0] = CurrentIndex;
		lex->index[1] = CurrentIndex;
		//addLexTable(lex);
		return TRUE;
	}
	else if (ch == ']') {
		lex->last_token_type = TOKEN_RBRACKET;
		lex->line = CurrentLine;
		lex->last_id[0] = ']';
		lex->index[0] = CurrentIndex;
		lex->index[1] = CurrentIndex;
		//addLexTable(lex);
		return TRUE;
	}
	else if (ch == ',') {
		lex->last_token_type = TOKEN_COMMA;
		lex->line = CurrentLine;
		lex->last_id[0] = ',';
		lex->index[0] = CurrentIndex;
		lex->index[1] = CurrentIndex;
		//addLexTable(lex);
		return TRUE;
	}
	else if (ch == ';') {
		lex->last_token_type = TOKEN_SEMICOLON;
		lex->line = CurrentLine;
		lex->last_id[0] = ';';
		lex->index[0] = CurrentIndex;
		lex->index[1] = CurrentIndex;
		//addLexTable(lex);
		return TRUE;
	}
	else if (ch == '.') {
		lex->last_token_type = TOKEN_PERIOD;
		lex->line = CurrentLine;
		lex->last_id[0] = '.';
		lex->index[0] = CurrentIndex;
		lex->index[1] = CurrentIndex;
		//addLexTable(lex);
		return TRUE;
	}
	else if (ch == ':') {
		mygetchar();
		if (ch == '=') {
			lex->last_token_type = TOKEN_BECOMES;
			lex->line = CurrentLine;
			lex->last_id[0] = ':';
			lex->last_id[1] = '=';
			lex->index[0] = (CurrentIndex-1);
			lex->index[1] = CurrentIndex;
			//addLexTable(lex);
			return TRUE;
		}
		else {
			//printf("��%d�У���%d��λ����:=�Ĵ��� : ��Ӧ���Ǹ� = \n", CurrentLine, CurrentIndex);
			DealError(lex, 33);
			fseek(fin, -1, 1);
			lex->last_token_type = TOKEN_BECOMES;
			return TRUE;
		}
		
	}
	else if (ch == '!') {
		mygetchar();
		if (ch == '=') {
			lex->last_token_type = TOKEN_NEQ;
			lex->line = CurrentLine;
			lex->last_id[0] = '!';
			lex->last_id[1] = '=';
			lex->index[0] = (CurrentIndex - 1);
			lex->index[1] = CurrentIndex;
			//addLexTable(lex);
			return TRUE;
		}
		else {
			//printf("��%d�У���%d��λ����!=�Ĵ��� ������Ӧ���и� = \n", CurrentLine, CurrentIndex);
			DealError(lex, 34);
			fseek(fin, -1, 1);
			lex->last_token_type = TOKEN_NEQ;
			return TRUE;
		}
	}
}

BOOL PL0Lex_destroy(PL0Lex * lex)
{
	free(lex);
	return TRUE;
}

int JudgeReserve(char *tempname) {
	int i;
	for (i = 0; i < NRW; i++) {
		if (strcmp(tempname, TOKEN_RESERVED_WORDS[i]) == 0) {
		
			return i;
		}
	}
	return -1;
}

BOOL PL0Lex_get_token(PL0Lex *lex)
{	
	flag = 1;
	while (flag == 1) {
		flag = 0;
		/*     ÿ�ζ����ַ�ǰ�Ƚ�lex���    */
		lex->last_num = -1;
		int i;
		for (i = 0; i <= MAX_ID_LEN; i++) {
			lex->last_id[i] = '\0';
		}

		mygetchar();
		//���˵�token֮ǰ�Ŀո�
		while (ch == ' ' || ch == '\n' || ch == '\t'|| ch == '\r') {
			if (ch == '\n' || ch == '\r') {
				CurrentLine++;
				CurrentIndex = -1;
			}
			mygetchar();
		}
		if (isdigit(ch)) {
			lex->index[0] = CurrentIndex;
			int num = 0;
			for (; isdigit(ch); mygetchar()) {
				num = num * 10 + (ch - '0');
			}

			if (isalpha(ch) || ch == '_') {
				while (ch == '_' || isdigit(ch) || isalpha(ch)) {
					mygetchar();
				}
				DealError(lex, 32);
				fseek(fin, -1, SEEK_CUR );
				//printf("%d�� %dλ�ô� ���ֺ�����ַ�", CurrentLine, CurrentIndex);
				lex->last_token_type = TOKEN_IDENTIFIER;
				return TRUE;
			}
			else {
				lex->last_num = num;
				lex->last_token_type = TOKEN_NUMBER;
				lex->line = CurrentLine;
				lex->index[1] = (--CurrentIndex);
				fseek(fin, -1, 1);
				//addLexTable(lex);
				return TRUE;
			}
		}

		if (ch == '_') {
			lex->index[0] = CurrentIndex;
			int start = 0;
			char tempname[30];
			for (i = 0; i < 30; i++) {
				tempname[i] = '\0';
			}

			do {
				tempname[start++] = ch;
				if (start == 30) break;
				mygetchar();
			} while (isalpha(ch) || isdigit(ch) || ch == '_');

			if (start >= 11) {
				printf("��%d�� ��%dλ�� ID is too long\n", CurrentLine, CurrentIndex);
				lex->last_token_type = TOKEN_IDENTIFIER;
;
				return TRUE;
			}
			else {
				lex->last_token_type = TOKEN_IDENTIFIER;
				strcpy(lex->last_id, tempname);
				lex->line = CurrentLine;
				lex->index[1] = (--CurrentIndex);
				fseek(fin, -1, 1);
				//addLexTable(lex);
				return TRUE;
			}
		}

		if (isalpha(ch)) {
			lex->index[0] = CurrentIndex;
			int start = 0;
			char tempname[30]="\0";
			int index_resersed;//�������±�
			

			do {
				tempname[start++] = ch;
				if (start == 30) break;
				mygetchar();
			} while (isalpha(ch) || isdigit(ch) || ch == '_');

			if (start >= 11) {
				DealError(lex, 31);
				lex->last_token_type = TOKEN_IDENTIFIER;
				strcpy(lex->last_id, tempname);
				lex->line = CurrentLine;
				lex->index[1] = (--CurrentIndex);
				fseek(fin, -1, 1);
				return TRUE;
			}
			else if ((index_resersed=JudgeReserve(tempname)) >= 0) {
				lex->last_token_type = TOKEN_RESWORDS+index_resersed+1;
				strcpy(lex->last_id, tempname);
				lex->line = CurrentLine;
				lex->index[1] = (--CurrentIndex);
				fseek(fin, -1, 1);
				//addLexTable(lex);
				return TRUE;
			}
			else {
				lex->last_token_type = TOKEN_IDENTIFIER;
				strcpy(lex->last_id, tempname);
				lex->line = CurrentLine;
				lex->index[1] = (--CurrentIndex);
				fseek(fin, -1, 1);
				//addLexTable(lex);
				return TRUE;
			}
		}
		//����������Ǹ��ַ��ŵ����
		if (ch == '-' || ch == '+' || ch == '/' 
			|| ch == '*' || ch == '=' || ch == '!' 
			|| ch == '>' || ch == '<' || ch == '(' || ch == ')' || ch == '.' || ch == ',' || ch == ';' || ch == ':'|| ch == ']' || ch == '[') {
			if (DealSymbol(lex) == TRUE) return TRUE;
			else if(flag == 1); 
			else if (flag == 0) return TRUE;
		}
		else {
			lex->last_token_type = TOKEN_IDENTIFIER;
			DealError(lex, 30);
			return TRUE;
		}

		
	}
	return FALSE;
}
