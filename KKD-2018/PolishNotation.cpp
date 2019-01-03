#include "stdafx.h"

namespace PN
{
	void DoPolishNotation(LT::LexTable& lextable, IT::IdTable& idtable) // Перевод выражений в польскую запись
	{
		for (int i=0; i < lextable.size; i++)
		{
			if (lextable.table[i].lexema == '=')
			{
				if (lextable.table[i + 1].lexema != '"')
				{
					i++;
					PN::PolishNotation(i, lextable, idtable);
				}
			}
		}
	}
	int prior(char c) //приоретет операций
	{
		switch (c)
		{
		case '(': return 1;
		case '+': case '-': return 2;
		case '*': case '/': return 3;
		default: return 0;
		}
	}
	void  PolishNotation(int &lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable)
	{
		std::stack<LT::Entry> st_for_operations;
		int count;
		int i(lextable_pos), pos(lextable_pos), numb(0), numb_of_all(0);
		bool flag_for_leftthesis = false;
		for (; lextable.table[i].lexema != LEX_SEMICOLON; i++)
		{
			switch (lextable.table[i].lexema)
			{
			case LEX_LEFTTHESIS: st_for_operations.push(lextable.table[i]); break;
			case LEX_PLUS /* ('+', '-', '*', '/') */:
				if (!st_for_operations.empty())
					while (!st_for_operations.empty() && prior(lextable.table[i].pn) <= prior(st_for_operations.top().pn))
					{
						lextable.table[pos++] = st_for_operations.top();
						numb++;
						st_for_operations.pop();
					}
				st_for_operations.push(lextable.table[i]); break;
			case LEX_IDENTIFIER:
			case LEX_LITERAL:
				lextable.table[pos++] = lextable.table[i];  numb++; 
				if (lextable.table[i + 1].lexema == LEX_LEFTTHESIS)
				{
					i++;
					lextable.table[pos++] = lextable.table[i];
					numb++; numb_of_all++;
					flag_for_leftthesis = true;
				}
				break;
			case LEX_COMMA:	lextable.table[pos++] = lextable.table[i];  numb++; break;
			case LEX_RIGHTTHESIS:
				if (flag_for_leftthesis)
				{
					lextable.table[pos++] = lextable.table[i];
					numb++;
					flag_for_leftthesis = false;
				}
				else 
				{
					while (st_for_operations.top().lexema != LEX_LEFTTHESIS)
					{
						lextable.table[pos++] = st_for_operations.top();
						numb++;
						st_for_operations.pop();
					}
					st_for_operations.pop();
				}
				break;
			default: return;
			}
			numb_of_all++;
		}
		while (!st_for_operations.empty())
		{
			lextable.table[pos++] = st_for_operations.top();
			numb++;
			st_for_operations.pop();
		}
		for (int i = lextable_pos + numb; i <= lextable.size; i++) // "колибровка" ТЛ
		{
			lextable.table[i] = lextable.table[i + numb_of_all - numb];
		}
		lextable.size -= numb_of_all - numb;
	}
}