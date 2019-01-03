#include "stdafx.h"
namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] // ������� ������
	{
		ERROR_ENTRY(0, "System error: ������������ ��� ������."),
		ERROR_ENTRY(1, "System error: ��������� ����."),
		ERROR_ENTRY(2, "System error: �������� -in ������ ���� �����."),
		ERROR_ENTRY(3, "System error: ��������� ����� �������� ���������."),
		ERROR_ENTRY(4, "System error: ������ ��� �������� ����� ��������� (-log)."),
		ERROR_ENTRY(5, "System error: ������ ��� �������� ����� � �������� ����� (-in)."),
		ERROR_ENTRY_NODEF(6),
		ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Lexical error: �������� ��������� ���� �� ���������."),
		ERROR_ENTRY(101, "Lexical error: ������������ ������ � ����� � �������� �����."),
		ERROR_ENTRY(102, "Semantic error: ���������� ����� �������������� ���������."),
		ERROR_ENTRY(103, "Semantic error: �� ����������� �������������."),
		ERROR_ENTRY(104, "Semantic error: ������ ��������� �������� �������."), 
		ERROR_ENTRY(105, "Semantic error: ���������� ����� ���������� �������� ���������."),
		ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107), ERROR_ENTRY_NODEF(108),
		ERROR_ENTRY_NODEF(109), ERROR_ENTRY_NODEF10(110), ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140),
		ERROR_ENTRY_NODEF10(150), ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "Syntax error: �������� ��������� ���������"),
		ERROR_ENTRY(601, "Syntax error: �������� ����������� �������"),
		ERROR_ENTRY(602, "Syntax error: �������� ���������"),
		ERROR_ENTRY(603, "Syntax error: ������, ��������� �� �������"),
		ERROR_ENTRY(604, "Syntax error: �������� ���������� ��������� �������"),
		ERROR_ENTRY(605, "Syntax error: �������� ����������� ��������� �������")
	};
	
	ERROR geterror(int id)// ������, ��� ������� ����� ������ id
	{
		return (id > 0 && id < ERROR_MAX_ENTRY) ? errors[id] : errors[0];
	}


	ERROR geterrorin(int id, int line, int col)
	{
		ERROR ret;
		if (id > 0 && id < ERROR_MAX_ENTRY)
		{
			errors[id].inext.line = line; //������ � ������
			errors[id].inext.col = col; //������� � ������
			ret = errors[id];
		}
		else ret = errors[0]; //����������� ���������� ��������� ERROR ��������������� ������ � ����� 0
		return ret;
	}
	void ERRORS::pushError(int id, int line, int col)
	{
		if (ERRORS::size < MAX_NUMBER_OF_ERRORS)
		{
			this->errors[this->ERRORS::size++] = geterrorin(id, line, col);
		}
	}
	ERRORS createTable(int size)
	{
		ERRORS rc;
		rc.errors = new ERROR[size > MAX_NUMBER_OF_ERRORS ? MAX_NUMBER_OF_ERRORS : size];
		size = 0;
		return rc;
	}
}