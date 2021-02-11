#ifndef TOKEN_H
# define TOKEN_H

enum TokenType{
	REGULAR,
	NUMBER,
	DOT = '.',
	DOLLAR = '$',
	NEWLINE = '\n',
	TAB = '\t',
	COMMA = ',',
	SEMICOLON = ';',
	WHITESPACE = ' ',
	PIPE = '|',
	QUOTE = '\'',
	DOUBLEQUOTE = '\"',
	END = '\0',
	GREATER = '>',
	LESSER = '<',
	SLACH = '/',
	BACKSLACH = '\\',
	AMPERSAND = "&",
	TILDE = '~',
	WILDECARD = '"',
	OPENPARENTHESE = '(',
	CLOSEPARENTHESE = ')',
	OPENBRACE = '{',
	CLOSEBRACE = '}',
	OPENBRACKETS = '[',
	CLOSEBRACKETS = ']',
	DASH = '-',
	EQUAL = '=',
	PLUS = '+',
};

typedef struct	s_token
{
		enun TokenType;
		const char* command;
}		t_token;

TokenType get_token_type(char c);

#endif
