#pragma once
#include "stdafx.h"

#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Rule::Chain::T(n)
#define ISNS(n) GRB::Rule::Chain::isN(n)
#define MFST_TRACE1 << std::setw(4) << std::left<< ++FST_TRACE_n << ": "\
					<< std::setw(25) << std::left << rule.getCRule(rbuf,nrulechain)\
					<< std::setw(30) << std::left << getCLenta(lbuf,lenta_position)\
					<< std::setw(20) << std::left << getCSt(sbuf)\
					<< std::endl;
#define MFST_TRACE2 << std::setw(4)<<std::left<< FST_TRACE_n << ": "\
					<< std::setw(25) << std::left << " "\
					<< std::setw(30) << std::left << getCLenta(lbuf, lenta_position)\
					<< std::setw(20) << std::left << getCSt(sbuf)\
					<< std::endl;
#define MFST_TRACE3 << std::setw(4) << std::left<< ++FST_TRACE_n << ": "\
					<< std::setw(25) << std::left << " "\
					<< std::setw(30) << std::left << getCLenta(lbuf, lenta_position)\
					<< std::setw(20) << std::left << getCSt(sbuf)\
					<< std::endl;
#define MFST_TRACE4(c) << std::setw(4)<<std::left<<++FST_TRACE_n<<": "<<std::setw(20)<<std::left<<c<<std::endl;
#define MFST_TRACE5(c) << std::setw(4)<<std::left<< FST_TRACE_n<<": "<<std::setw(20)<<std::left<<c<<std::endl;
#define MFST_TRACE6(c,k) << std::setw(4)<<std::left<< FST_TRACE_n<<": "<<std::setw(20)<<std::left<<c<<k<<std::endl;
#define MFST_TRACE7 << std::setw(4)<<std::left<<state.lenta_position<<": "\
					<<std::setw(20)<<std::left<<rule.getCRule(rbuf,state.nrulechain)\
					<<std::endl;


typedef short GRBALPHABET; // символы алфавита грамматики терминалы > 0, нетерминалы < 0
namespace GRB
{
	struct Rule // правило в грамматике Грейбах
	{
		GRBALPHABET nn; // нетерминал (левый символ правила) < 0
		int iderror; // идентификатор диагностического сообщения
		short size; // количество цепочек - правых частей правила
		struct Chain // цепочка (правая часть правила)
		{
			short size; // длина цепочки
			GRBALPHABET* nt; // цепочка терминалов (>0) и нетерминалов (<0)
			Chain() { size = 0; nt = 0; };
			Chain(
				short psize, // количество символов в цепочка
				GRBALPHABET s, ... // символы (терминал или нетерминал)
				);
			char* getCChain(char* b); // получить правую сторону правила
			static GRBALPHABET T(char t) { return GRBALPHABET(t); }; // терминал
			static GRBALPHABET N(char n) { return -GRBALPHABET(n); }; // нетерминал
			static bool isT(GRBALPHABET s) { return s > 0; }; // терминал ?
			static bool isN(GRBALPHABET s) { return !isT(s); }; // нетерминал ?
			static char alphabet_to_char(GRBALPHABET s) { return isT(s) ? char(s) : char(-s); }; // GRBALPHABET->char
		}*chains; // массив цепочек - правых частей правила
		Rule() { nn = 0x00; size = 0; }
		Rule(
			GRBALPHABET pnn, // нетерминал (<0)
			int iderror, // идентификатор диагностического сообщения (Error)
			short psize, // количество цепочек - правых частей правила
			Chain c, ... // можество цепочек - правых частей правила 
			);
		char* getCRule( // получить правило в виде N->цепочка (для распечатки)
			char* b, // буфер
			short nchain // номер цепочки (правой части) в правиле
			);
		short Rule::getNextChain( // получить следующую за j подходязую цепочку, вернуть ее номер или -1
			GRBALPHABET t, // первый символ цепочки
			Rule::Chain& pchain, // возвращаемая цепочка
			short j // номер цепочки
			);
	};

	struct Greibach // грамматика Грейбах
	{
		short size; // количество правил
		GRBALPHABET startN; // стартовый символ
		GRBALPHABET stbottomT; // дно стека
		Rule* rules; // множество правил
		Greibach() { short size = 0; startN = 0; stbottomT = 0; rules = 0; };
		Greibach(
			GRBALPHABET pstartN, // стартовый символ
			GRBALPHABET pstbottom, // дно стека
			short psize, // количество правил
			Rule r, ... // правила
			);
		short getRule( // получить правило, возвращается номер правила или -1
			GRBALPHABET pnn, // левый символ правила
			Rule& prule // возвращаемое правило грамматики
			);
		Rule getRule(short n); // получить правило по номеру
	};

	Greibach getGreibach(); // получить грамматику
}