#pragma once
#define ID_MAXSIZE 10 // максимальное количество символов в идентификаторе
#define TI_MAXSIZE 4096 // максимальное количество строк в таблице идентификаторов
#define TI_INT_DEFAULT 0x00000000 // значение по умолчанию для int
#define	TI_STR_DEFAULT 0x00 // значение по умолчанию для str
#define TI_NULLIDX 0xffffffff // нет элемента таблицы идентификаторов
#define	TI_STR_MAXSIZE 255

namespace IT // таблица идентификаторов
{
	enum IDDATATYPE { DEFD = 0, INT = 1, STR = 2 }; // типы данных идентификаторов
	enum IDTYPE { DEFT = 0, V = 1, P = 2, F = 3, L = 4 }; // типы идентификаторов (переменная, параметр, функция, литерал)

	struct Entry //строка ТИ
	{
		int idxfirstLE; // индекс первой строки в таблице лексем
		char id_buf[ID_MAXSIZE]; // идентификатор(без обл. вид.)
		char id[ID_MAXSIZE*2]; // идентификатор
		char idvis[ID_MAXSIZE]; // область видимости идентификатора
		bool is_to = false;
		IDDATATYPE iddatatype; // тип данных (1-число, 2-символы)
		IDTYPE idtype; // тип идентификатора
		union
		{
			int vint; // значение int
			struct
			{
				uc len;// количество символов в str
				char str[TI_STR_MAXSIZE - 1]; // символы str
			} vstr; // значение str
		} value; // значение идентификатора
		Entry() 
		{ 
			iddatatype = IT::DEFD; 
		    idtype = IT::DEFT; 
		    is_to = false; 
		    idxfirstLE = TI_NULLIDX;
		    memset(id, NULL, strlen(id)); 
		    memset(id_buf, NULL, strlen(id_buf)); 
		}
	};

	struct IdTable //экземпляр таблицы идентификаторов
	{
		bool if_double_i = false;
		int IT_num = 0;
		bool f_main = false;
		bool f_parm = false;
		int maxsize; // емкость ТИ
		char literals[30][100];
		int size; // текущий размер ТИ
		int litCount; // количество литералов
		Entry* table; //  массив строк ТИ
		int getidnum(char* c)
		{
			int k = size;
			while  (k >= 0  && strcmp(table[k].id_buf, c))
				k--;
			return k >= 0 ? k : -1;
		}
	};

	IdTable Create(int size); // создать ТИ(емкость ТИ)
	void Add(IdTable&idtable, Entry entry); // добавить строку в ТИ(экземпляр ТИ, строка ТИ)
	Entry GetEntry(IdTable& idtable, int n);// получить строку ТИ(экземпляр ТИ,номер получаемой строки)
	int IsId(IdTable& idtable,char id[ID_MAXSIZE], char* idvis);// возврат: номер строки (если есть), TI_NULLIDX (если нет)
	void Delete(IdTable& idtable);
	int IsLiteral(IdTable& idtable, char *litrl);
}