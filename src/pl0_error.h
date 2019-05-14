#ifndef __PL0_ERROR_H__
#define __PL0_ERROR_H__
#include <stdio.h>

//Possible errors in lex
#define ERR_UNRECOGNIZED_CHAR "An unrecognized character appears."    //y
#define ERR_WRONG_IDEN_FORMAT "Wrong identifier format: identifier cannot start with a number."
#define ERR_MISS_END_FOR_COMMENT "Missing a end for comment: has reached the EOF."
#define ERR_TOO_LONG_IDEN_OR_NUM "Too long identifier or number."
#define ERR_COLON_EXPECT_EQUAL "Expect an '=' after ':'"
#define ERR_EXCLAMATION_EXPECT_EQUAL "Expect an '=' after '!'"

//Possible errors in syntax
#define ERR_SEMICOLON_MISS "Missing ';'."  // 
#define ERR_DOT_MISS "Missing '.'."   // 1 y
#define ERR_COMMA_MISS "Missing ','."  //2 y
#define ERR_RIGHT_PARENTHESIS_MISS "Right parenthesis Missing')'."  // 3 y
#define ERR_SEMICOLON_OR_COMMA_MISS "Missing ';' or ','." //
#define ERR_CONST_EXPECT_IDEN "Expect an identifier after const."   // 4 y
#define ERR_VAR_EXPECT_IDEN "Expect an identifier after var."   //5 y
#define ERR_PROC_EXPECT_IDEN "Expect an identifier after procedure." //6 y
#define ERR_CALL_EXPECT_IDEN "Expect an identifier after call."  // 7 y
#define ERR_IDEN_EXPECT_EQUAL "Expect an '=' after identifier."    //8 y
#define ERR_ASSIGN_EXPECT_IDEN "Expect an ':=' after identifier."    // 9 y
#define ERR_ILLEGAL_ASSIGNMENT "Only a number can be assigned to '='"   //10 y
#define ERR_NEED_END_FOR_BEGIN "'begin' needs to end with 'end'."    // ?
#define ERR_NEED_THEN_FOR_IF "'if' needs to end with 'then'."     //  12 y
#define ERR_NEED_DO_FOR_WHILE "Need a 'do' for the loop statement after the condition."   //13 y
#define ERR_WRONG_OP_IN_BINARY_COND "Wrong op in a binary conditional expression: could only use '=', '!=', '<', '>', '<=', '>='."  // 14 y
#define ERR_WRONG_BEGIN_OF_PROC "Wrong beginning of procedure: could only use 'const', 'var', 'procdure', 'ident', 'call', 'begin', 'if', 'while'."  // 15 y
#define ERR_WRONG_BEGIN_OF_STATEMENT "Wrong beginning of statement: could only use 'ident', 'call', 'begin', 'if', 'while'."  // 16 y
#define ERR_WRONG_BEGIN_OF_COND "Wrong beginning of condition: could only use 'odd'." //17 y
#define ERR_WRONG_BEGIN_OF_FACTOR "Wrong beginning of factor: could only use 'iden', 'number', '-', '('."   // 18 y
#define ERR_UD_IDEN "Undeclared identifier."

void PL0_print_error(char * err_msg, char* cur_line_content, int cur_line_num, int offset);

#endif
#pragma once
