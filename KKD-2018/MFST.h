#pragma once
#include "stdafx.h"
#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3

typedef std::stack<short> MFSTSTSTACK; // ���� ��������
#define MFST_TRACE_START <<std::setw(4)<<std::left<<"���"<<":"\
						 <<std::setw(25)<<std::left<<" �������"\
						 <<std::setw(30)<<std::left<<" ������� �����"\
						 <<std::setw(20)<<std::left<<" ����"\
						 <<std::endl;

namespace MFST
{
	void Do_Sentence_Analysis(Log::LOG &log, P::LEX tables, Error::ERRORS& table);

	struct MfstState // ��������� ��������
	{
		short lenta_position; // ������� �� �����
		short nrule; // ����� �������� �������
		short nrulechain; // ����� ������� �������, �������� �������
		MFSTSTSTACK st; // ���� ��������
		MfstState();
		MfstState(
			short pposition, // ������� �� �����
			MFSTSTSTACK pst, // ���� �������� 
			short pnrulechain // ����� ������� �������, �������� �������
			);
		MfstState(
			short pposition, // ������� �� �����
			MFSTSTSTACK pst, // ���� ��������
			short pnrule, // ����� �������� �������
			short pnrulechain // ����� ������� �������, �������� �������
			);
	};
	struct Mfst // ���������� �������
	{
		enum RC_STEP { // ��� �������� ������� step
			NS_OK, // ������� ������� � �������, ������� �������� � ����
			NS_NORULE, // �� ������� ������� ���������� (������ � ����������)
			NS_NORULECHAIN, //�� ������� ���������� ������� ������� (������ � �������� ����)
			NS_ERROR, // ����������� �������������� ������ ����������
			TS_OK, // ���.������ ����� == ������� �����, ������������ �����, pop �����
			TS_NOK, // ���.������ ����� != ������� �����, �������������� ���������
			LENTA_END, // ������� ������� ����� >= lenta_size
			SURPRISE // ����������� ��� �������� (������ � step)
		};
		struct MfstDiagnosis // �����������
		{
			short lenta_position; // ������� �� �����
			RC_STEP rc_step; // ��� ���������� ����
			short nrule; // ����� �������
			short nrule_chain; // ����� ������� �������
			MfstDiagnosis();
			MfstDiagnosis( // �����������
				short plenta_position, // ������� �� �����
				RC_STEP prc_step, // ��� ���������� ����
				short pnrule, // ����� �������
				short pnrule_chain // ����� ������� �������
				);
		} diagnosis[MFST_DIAGN_NUMBER]; // ��������� ����� �������� ���������

		GRBALPHABET* lenta; // ���������������� (TS/NS) ����� (�� LEX)
		short lenta_position; // ������� ������� �� �����
		short nrule; // ����� �������� �������
		short nrulechain; // ����� ������� �������, �������� �������
		short lenta_size; // ������ �����
		GRB::Greibach grebach; // ���������� �������
		P::LEX lex;
		MFSTSTSTACK st; // ���� ��������
		std::stack<MfstState> storestate; // ���� ��� ���������� ���������
		Mfst();
		Mfst(
			P::LEX plex, // ��������� ������ ������������ �����������
			GRB::Greibach pgrebach // ���������� �������
			);
		char* getCSt(char* buf); // �������� ���������� �����
		char* getCLenta(char* buf, short pos, short n = 25); // �����: n �������� � pos
		char* getDiagnosis(short n, char* buf); // �������� n-�� ������ ����������� ��� 0x00
		bool savestate(Log::LOG log); // ��������� ��������� ��������
		bool restate(Log::LOG log); // ������������ ��������� ��������
		bool push_chain( // ��������� ������� ������� � ����
			GRB::Rule::Chain chain // ������� �������
			);
		RC_STEP step(Log::LOG log); // ��������� ��� ��������
		bool start(Log::LOG log, Error::ERRORS& table); // ��������� �������
		bool savediagnosis(
			RC_STEP pprc_step // ��� ���������� ����
			);
		void printrules(Log::LOG log); // ������ ������������������ ������

		struct Deducation // �����
		{
			short size; // ���������� ����� � ������
			short* nrules; // ����� ������ ����������
			short* nrulechains; // ������ ������� ������ ���������� (nrules)
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		} deducatuon;
		bool savededucation(); // ��������� ������ ������
	};
};