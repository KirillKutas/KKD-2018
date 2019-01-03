#pragma once

#define START_FSATable FST::FSA FSATable[] = {
#define FINISH_FSATable };
#define INTEGER { { "", 4,\
FST::NODE(1, FST::RELATION('i', 1)),\
FST::NODE(1, FST::RELATION('n', 2)),\
FST::NODE(1, FST::RELATION('t', 3)),\
FST::NODE() }, LEX_INTEGER, LT::PIN_I, 'd' }

#define STRING { { "", 7,\
FST::NODE(1, FST::RELATION('s', 1)),\
FST::NODE(1, FST::RELATION('t', 2)),\
FST::NODE(1, FST::RELATION('r', 3)),\
FST::NODE(1, FST::RELATION('i', 4)),\
FST::NODE(1, FST::RELATION('n', 5)),\
FST::NODE(1, FST::RELATION('g', 6)),\
FST::NODE() }, LEX_STRING, LT::PIN_S, 'd' }

#define LITERAL_1 { { "", 2,\
FST::NODE(20, FST::RELATION('1', 0), FST::RELATION('1', 1),\
FST::RELATION('2', 0), FST::RELATION('2', 1), FST::RELATION('3', 0), FST::RELATION('3', 1), FST::RELATION('4', 0),\
FST::RELATION('4', 1), FST::RELATION('5', 0), FST::RELATION('5', 1), FST::RELATION('6', 0), FST::RELATION('6', 1),\
FST::RELATION('7', 0), FST::RELATION('7', 1), FST::RELATION('8', 0), FST::RELATION('8', 1), FST::RELATION('9', 0),\
FST::RELATION('9', 1), FST::RELATION('0', 0), FST::RELATION('0', 1)),\
FST::NODE() }, LEX_LITERAL, LT::LT_INT, 'd' }

#define LITERAL_2 { { "", 3,\
FST::NODE(1, FST::RELATION(	'"', 1)),\
FST::NODE(41, FST::RELATION(' ', 1),\
FST::RELATION('a', 1), FST::RELATION('b', 1),\
FST::RELATION('c', 1), FST::RELATION('d', 1), FST::RELATION('e', 1), FST::RELATION('f', 1), FST::RELATION('g', 1),\
FST::RELATION('h', 1), FST::RELATION('i', 1), FST::RELATION('j', 1), FST::RELATION('k', 1), FST::RELATION('l', 1),\
FST::RELATION('m', 1), FST::RELATION('n', 1), FST::RELATION('o', 1), FST::RELATION('p', 1), FST::RELATION('q', 1),\
FST::RELATION('r', 1), FST::RELATION('s', 1), FST::RELATION('t', 1), FST::RELATION('u', 1), FST::RELATION('v', 1),\
FST::RELATION('w', 1), FST::RELATION('x', 1), FST::RELATION('y', 1), FST::RELATION('z', 1), FST::RELATION('1', 1),\
FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1),\
FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::RELATION('0', 1), FST::RELATION('"', 2)),\
FST::NODE() }, LEX_LITERAL, LT::LT_STR , 'd'}

#define FUNCTION { { "", 9,\
FST::NODE(1, FST::RELATION('f', 1)),\
FST::NODE(1, FST::RELATION('u', 2)),\
FST::NODE(1, FST::RELATION('n', 3)),\
FST::NODE(1, FST::RELATION('c', 4)),\
FST::NODE(1, FST::RELATION('t', 5)),\
FST::NODE(1, FST::RELATION('i', 6)),\
FST::NODE(1, FST::RELATION('o', 7)),\
FST::NODE(1, FST::RELATION('n', 8)),\
FST::NODE() }, LEX_FUNCTION, LT::PIN_F, 'd' } 

#define DECLARE { { "", 8,\
FST::NODE(1, FST::RELATION('d', 1)),\
FST::NODE(1, FST::RELATION('e', 2)),\
FST::NODE(1, FST::RELATION('c', 3)),\
FST::NODE(1, FST::RELATION('l', 4)),\
FST::NODE(1, FST::RELATION('a', 5)),\
FST::NODE(1, FST::RELATION('r', 6)),\
FST::NODE(1, FST::RELATION('e', 7)),\
FST::NODE() }, LEX_DECLARE, LT::PIN_DEF, 'd' }

#define RETURN { { "", 7,\
FST::NODE(1, FST::RELATION('r', 1)),\
FST::NODE(1, FST::RELATION('e', 2)),\
FST::NODE(1, FST::RELATION('t', 3)),\
FST::NODE(1, FST::RELATION('u', 4)),\
FST::NODE(1, FST::RELATION('r', 5)),\
FST::NODE(1, FST::RELATION('n', 6)),\
FST::NODE() }, LEX_RETURN, LT::PIN_DEF , 'd'}

#define PRINT { { "", 7,\
FST::NODE(1, FST::RELATION('p', 1)),\
FST::NODE(1, FST::RELATION('r', 2)),\
FST::NODE(1, FST::RELATION('i', 3)),\
FST::NODE(1, FST::RELATION('n', 4)),\
FST::NODE(1, FST::RELATION('t', 5)),\
FST::NODE(1, FST::RELATION('>', 6)),\
FST::NODE() }, LEX_PRINT, LT::PIN_DEF, 'd' }

#define SQUARE { { "", 4,\
FST::NODE(1, FST::RELATION('s', 1)),\
FST::NODE(1, FST::RELATION('q', 2)),\
FST::NODE(1, FST::RELATION('r', 3)),\
FST::NODE() }, LEX_COLLAB, LT::PIN_F , 'd'}

#define DOUBLE1 { { "", 5,\
FST::NODE(1, FST::RELATION('d', 1)),\
FST::NODE(1, FST::RELATION('o', 2)),\
FST::NODE(1, FST::RELATION('u', 3)),\
FST::NODE(1, FST::RELATION('b', 4)),\
FST::NODE() }, LEX_LENGTH, LT::PIN_F, 'd' }

#define WRITE { { "", 7,\
FST::NODE(1, FST::RELATION('w', 1)),\
FST::NODE(1, FST::RELATION('r', 2)),\
FST::NODE(1, FST::RELATION('i', 3)),\
FST::NODE(1, FST::RELATION('t', 4)),\
FST::NODE(1, FST::RELATION('e', 5)),\
FST::NODE(1, FST::RELATION('>', 6)),\
FST::NODE() }, LEX_WRITE, LT::PIN_DEF, 'd' }

#define MAIN { { "", 5,\
FST::NODE(1, FST::RELATION('m', 1)),\
FST::NODE(1, FST::RELATION('a', 2)),\
FST::NODE(1, FST::RELATION('i', 3)),\
FST::NODE(1, FST::RELATION('n', 4)),\
FST::NODE() }, LEX_MAIN, LT::PIN_M , 'd'}

#define SEMICOLON { { "", 2,\
FST::NODE(1, FST::RELATION(';', 1)),\
FST::NODE() }, LEX_SEMICOLON, LT::PIN_DEF, 'd' }

#define COMMA { { "", 2,\
FST::NODE(1, FST::RELATION(',', 1)),\
FST::NODE() }, LEX_COMMA, LT::PIN_DEF, 'd' }

#define LEFTBRACE { { "", 2,\
FST::NODE(1, FST::RELATION('{', 1)),\
FST::NODE() }, LEX_LEFTBRACE, LT::PIN_DEF, 'd' }

#define BRACELET { { "", 2,\
FST::NODE(1, FST::RELATION('}', 1)),\
FST::NODE() }, LEX_BRACELET, LT::PIN_DEF, 'd' }

#define LEFTTHESIS { { "", 2,\
FST::NODE(1, FST::RELATION('(', 1)),\
FST::NODE() }, LEX_LEFTTHESIS, LT::PIN_DEF, '(' }

#define RIGHTTHESIS { { "", 2,\
FST::NODE(1, FST::RELATION(')', 1)),\
FST::NODE() }, LEX_RIGHTTHESIS, LT::PIN_DEF, 'd' }

#define PLUS { { "", 2,\
FST::NODE(1, FST::RELATION('+', 1)),\
FST::NODE() }, LEX_PLUS, LT::PIN_DEF, '+' }

#define MINUS { {"", 2,\
FST::NODE(1, FST::RELATION('-', 1)),\
FST::NODE() }, LEX_MINUS, LT::PIN_DEF, '-' }

#define STAR { {"", 2,\
FST::NODE(1, FST::RELATION('*', 1)),\
FST::NODE() }, LEX_STAR, LT::PIN_DEF, '*' }

#define DIRSLASH { {"", 2,\
FST::NODE(1, FST::RELATION('/', 1)),\
FST::NODE() }, LEX_DIRSLASH, LT::PIN_DEF, '/' }

#define RAVNO { { "", 2,\
FST::NODE(1, FST::RELATION('=', 1)),\
FST::NODE() }, LEX_RAVNO, LT::PIN_DEF, 'd' }

#define IDENTIFIER { { "", 2,\
	FST::NODE(72, FST::RELATION('a', 0), FST::RELATION('a', 1),\
	FST::RELATION('b', 0), FST::RELATION('b', 1), FST::RELATION('c', 0), FST::RELATION('c', 1), FST::RELATION('d', 0),\
	FST::RELATION('d', 1), FST::RELATION('e', 0), FST::RELATION('e', 1), FST::RELATION('f', 0), FST::RELATION('f', 1),\
	FST::RELATION('g', 0), FST::RELATION('g', 1), FST::RELATION('h', 0), FST::RELATION('h', 1), FST::RELATION('i', 0),\
	FST::RELATION('i', 1), FST::RELATION('j', 0), FST::RELATION('j', 1), FST::RELATION('k', 0), FST::RELATION('k', 1),\
	FST::RELATION('l', 0), FST::RELATION('l', 1), FST::RELATION('m', 0), FST::RELATION('m', 1), FST::RELATION('n', 0),\
	FST::RELATION('n', 1), FST::RELATION('o', 0), FST::RELATION('o', 1), FST::RELATION('p', 0), FST::RELATION('p', 1),\
	FST::RELATION('q', 0), FST::RELATION('q', 1), FST::RELATION('r', 0), FST::RELATION('r', 1), FST::RELATION('s', 0),\
	FST::RELATION('s', 1), FST::RELATION('t', 0), FST::RELATION('t', 1), FST::RELATION('u', 0), FST::RELATION('u', 1),\
	FST::RELATION('v', 0), FST::RELATION('v', 1), FST::RELATION('w', 0), FST::RELATION('w', 1), FST::RELATION('x', 0),\
	FST::RELATION('x', 1), FST::RELATION('y', 0), FST::RELATION('y', 1), FST::RELATION('z', 0), FST::RELATION('z', 1),\
	FST::RELATION('1', 0), FST::RELATION('1', 1), FST::RELATION('2', 0), FST::RELATION('2', 1), FST::RELATION('3', 0),\
	FST::RELATION('3', 1), FST::RELATION('4', 0), FST::RELATION('4', 1), FST::RELATION('5', 0), FST::RELATION('5', 1),\
	FST::RELATION('6', 0), FST::RELATION('6', 1), FST::RELATION('7', 0), FST::RELATION('7', 1), FST::RELATION('8', 0),\
	FST::RELATION('8', 1), FST::RELATION('9', 0), FST::RELATION('9', 1), FST::RELATION('0', 0), FST::RELATION('0', 1)),\
	FST::NODE() }, LEX_IDENTIFIER, LT::PIN_DEF, 'd' }


namespace FST
{
	struct RELATION  // ребро:символ -> вершина графа переходов  ј
	{
		char symbol;  // символ перехода
		short nnode; // номер смежной вершины
		RELATION(
			char c = 0x00,    // символ перехода
			short ns = NULL  // новое состо€ние
		);
	};

	struct NODE  // вершина графа перехода
	{
		short n_relation;      // количество инциндентных ребер
		RELATION *relations;  // инцидентные ребра
		NODE();
		NODE(
			short n,           // количество инциндентных ребер
			RELATION rel, ... // список ребр
		);
	};

	struct FST // недетерминированный  ј
	{
		char* string;   // цепочка (строка, завершатс€ 0х00)
		char* op;		// дл€ операторов
		short errors;
		short position; // текуща€ позици€ в цепочке
		short nstates;  // количество состо€ний автомата 
		NODE* nodes;    // граф переходов: [0] - начальное состо€ние, [nstate-1] - конечное
		short* rstates;  // возможные состо€ни€ автомата на данной позиции
		FST(
			char* s,    // цепочка (строка, завершатс€ 0х00)
			short ns,   // количество состо€ний автомата
			NODE n, ... // —писок состо€ний (граф перехода)
		);
		FST();
	};

	bool execute(  // выполнить распознавание цепочки
		FST& fst1   // недетерминированный  ј
	);

	struct FSA
	{
		FST fst;
		char lexema;
		int CID;
		int PN;
		FSA(FST f, char l, int n, int pr);
		FSA();
		void setFSA(char* s);
	};

}