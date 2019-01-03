#pragma once
#define LEXEMA_FIXSIZE 1 // фиксированный размер лексемы
#define	LT_MAXSIZE 4096 // максимальное кол-во строк в таблице
#define LT_TI_NULLIDX 0xffffffff // нет элемента ТИ
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

namespace LT // таблица лексем
{
	enum Let { LT_INT = 1, LT_STR = 2 };
	enum Pin { PIN_DEF = 0, PIN_I = 1, PIN_S = 2, PIN_F = 3, PIN_M = 4};
	struct Entry
	{
		char lexema; // лексема
		int sn; // номер строки
		int idxTI; // индекс в ТИ
		char pn; // приоритет
	};

	struct LexTable
	{
		int maxsize; // емкость ТЛ
		int size; // текущий размер ТЛ
		Entry* table; // массив строк ТЛ
	};

	LexTable Create( // создать ТЛ
		int size // емкость ТЛ
		);
	void Add( // добавить строку в ТЛ
		LexTable& lextable, // экземпляр ТЛ
		Entry entry // строка ТЛ
		);
	Entry GetEntry( //  получить строку ТЛ
		LexTable& lextable, //  экземпляр ТЛ
		int n // номер получаемой строки
		);
	void Delete(LexTable& lextable);
}