#pragma once
#define LEXEMA_FIXSIZE 1 // ������������� ������ �������
#define	LT_MAXSIZE 4096 // ������������ ���-�� ����� � �������
#define LT_TI_NULLIDX 0xffffffff // ��� �������� ��
#define LEX_INTEGER 't'
#define	LEX_STRING 's'
#define LEX_IDENTIFIER 'i'
#define LEX_LITERAL 'l'
#define LEX_FUNCTION 'f'
#define LEX_DECLARE 'd'
#define LEX_RETURN 'r'
#define LEX_PRINT 'p'
#define LEX_WRITE 'w'
#define LEX_MAIN 'm'
#define LEX_SEMICOLON ';'
#define	LEX_COMMA ','
#define LEX_LEFTBRACE '['
#define LEX_BRACELET ']'
#define LEX_LEFTTHESIS '('
#define	LEX_RIGHTTHESIS ')'
#define LEX_PLUS 'v'
#define LEX_MINUS 'v'
#define LEX_STAR 'v'
#define LEX_DIRSLASH 'v'
#define LEX_RAVNO '='
#define BUF_SEP '*'
#define BUF_SEP2 '#'

namespace LT // ������� ������
{
	enum Let { LT_INT = 1, LT_STR = 2 };
	enum Pin { PIN_DEF = 0, PIN_I = 1, PIN_S = 2, PIN_F = 3, PIN_M = 4};
	struct Entry
	{
		char lexema; // �������
		int sn; // ����� ������
		int idxTI; // ������ � ��
		char pn; // ���������
	};

	struct LexTable
	{
		int maxsize; // ������� ��
		int size; // ������� ������ ��
		Entry* table; // ������ ����� ��
	};

	LexTable Create( // ������� ��
		int size // ������� ��
		);
	void Add( // �������� ������ � ��
		LexTable& lextable, // ��������� ��
		Entry entry // ������ ��
		);
	Entry GetEntry( //  �������� ������ ��
		LexTable& lextable, //  ��������� ��
		int n // ����� ���������� ������
		);
	void Delete(LexTable& lextable);
}