#include "stdafx.h"
#define GRB_ERROR_SERIES 600
namespace GRB
{
#define NS(n) Rule::Chain::N(n)
#define TS(n) Rule::Chain::T(n)

	Greibach greibach(NS('S'), TS('$'), // стартовый символ, дно стека
		6, // кол-во правил
		Rule(NS('S'), GRB_ERROR_SERIES + 0, // Структура программы (неверная стуктура программы)
			8,
			Rule::Chain(4, TS('m'), TS('['), NS('N'), TS(']')),
			Rule::Chain(5, TS('m'), TS('['), NS('N'), TS(']'), TS(';')),
			Rule::Chain(12, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('['), NS('N'), TS('r'), NS('E'), TS(';'), TS(']'), NS('S')),
			Rule::Chain(12, TS('s'), TS('f'), TS('i'), TS('('), TS(')'), TS('['), NS('N'), TS('r'), NS('E'), TS(';'), TS(']'), NS('S')),
			Rule::Chain(9, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('['), NS('N'), TS(']'), NS('S')),
			Rule::Chain(9, TS('s'), TS('f'), TS('i'), TS('('), TS(')'), TS('['), NS('N'), TS(']'), NS('S')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('['), NS('N'), TS('r'), NS('E'), TS(';'), TS(']'), NS('S')),
			Rule::Chain(13, TS('s'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('['), NS('N'), TS('r'), NS('E'), TS(';'), TS(']'), NS('S'))
			),
		Rule(NS('N'), GRB_ERROR_SERIES + 1, // Возможные конструкции в ф-иях (ошибочный оператор)
			20,
			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(4, TS('d'), TS('s'), TS('i'), TS(';')),
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(5, TS('d'), TS('s'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(6, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(6, TS('d'), TS('s'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(7, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(7, TS('d'), TS('s'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('r'), NS('E'), TS(';')),
			Rule::Chain(4, TS('r'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('('), TS(')'), TS(';')),
			Rule::Chain(5, TS('i'), TS('('), TS(')'), TS(';'), NS('N')),
			Rule::Chain(3, TS('w'), NS('E'), TS(';')),
			Rule::Chain(4, TS('w'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('p'), NS('N'), TS(';')),
			Rule::Chain(4, TS('p'), NS('N'), TS(';'), NS('N'))
			),
		Rule(NS('E'), GRB_ERROR_SERIES + 2, // Выражения (ошибка в выражении)
			8, 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))
			),
		Rule(NS('M'), GRB_ERROR_SERIES + 3, // Знаки
			2, 
			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M'))
			),
		Rule(NS('F'), GRB_ERROR_SERIES + 4, // Параметры ф-ии
			4, 
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(2, TS('s'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F')),
			Rule::Chain(4, TS('s'), TS('i'), TS(','), NS('F'))
			),
		Rule(NS('W'), GRB_ERROR_SERIES + 5, // Принимаемые параметры ф-ии
			4, 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
			)
		);

	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
	{
		nt = new GRBALPHABET[size = psize];
		int* p = (int*)&s;
		for (short i(0); i < psize; ++i)
			nt[i] = (GRBALPHABET)p[i];
	};
	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...)
	{
		nn = pnn;
		iderror = piderror;
		chains = new Chain[size = psize];
		Chain* p = &c;
		for (int i(0); i < size; i++)
			chains[i] = p[i];
	};
	Greibach::Greibach(GRBALPHABET pstatrN, GRBALPHABET pstbottom, short psize, Rule r, ...)
	{
		startN = pstatrN;
		stbottomT = pstbottom;
		rules = new Rule[size = psize];
		Rule* p = &r;
		for (int i(0); i < size; i++)
			rules[i] = p[i];
	};

	Greibach getGreibach()
	{
		return greibach;
	};

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
	{
		short rc = -1, k = 0;
		while (k < size && rules[k].nn != pnn)
			k++;
		if (k < size)
			prule = rules[rc = k];
		return rc;
	};

	Rule Greibach::getRule(short n)
	{
		Rule rc;
		if (n < size) rc = rules[n];
		return rc;
	};

	char* Rule::getCRule(char* b, short nchain) // получить правило в виде N->цепочка
	{
		char bchain[200];
		b[0] = Chain::alphabet_to_char(nn);	b[1] = '-'; b[2] = '>'; b[3] = 0x00;
		chains[nchain].getCChain(bchain);
		strcat_s(b, sizeof(bchain) + 5, bchain);
		return b;
	};

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
	{
		short rc = -1;
		while (j < size && chains[j].nt[0] != t) ++j;
		rc = (j < size ? j : -1);
		if (rc >= 0) pchain = chains[rc];
		return rc;
	};

	char* Rule::Chain::getCChain(char* b) // получить правую сторону правила
	{
		for (int i(0); i < size; i++) b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	};
}