#ifndef _TABLESTACK_H_
#define _TABLESTACK_H_

#include"Base.h"

class TableStack :public Base
{
protected:
	vector<char> to_any; //����ջ
	vector<char> left_any;//ʣ�����봮
	int tableMap[100][100];//Ԥ���
public:
	TableStack() { memset(tableMap, -1, sizeof(tableMap)); }

	void get_table(); //�õ�Ԥ���
	void analyExp(string s); //����ջ�Ĵ���
	void print_out();//���
	void getAns(); //��ϴ���
};
#endif
