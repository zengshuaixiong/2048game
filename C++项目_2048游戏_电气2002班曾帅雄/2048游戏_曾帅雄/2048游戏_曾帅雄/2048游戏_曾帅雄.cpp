#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>
#include "control.h"
#include <vector>
#include <fstream>
using namespace std;

int main()
{
	read_formal_num();//��ȡ��ʷ��߷�
	while(1){ //��Ϸ��Ҫ����
	create(); // �������λ�ò���һ����
	print p1(display_arr); //��ʾ����
	printHelp(); //�˵���ʾ
	input(); //����������Ӧ����
	if(quitgame) //�˳���Ϸ����
		goto FLAG;
	system("cls"); //����
	}
FLAG:
	read_formal_num();//������ʷ��߷�
	return 0;
}