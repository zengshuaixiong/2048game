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
	read_formal_num();//读取历史最高分
	while(1){ //游戏主要程序
	create(); // 先在随机位置产生一个数
	print p1(display_arr); //显示出来
	printHelp(); //菜单显示
	input(); //键盘输入相应操作
	if(quitgame) //退出游戏操作
		goto FLAG;
	system("cls"); //清屏
	}
FLAG:
	read_formal_num();//保存历史最高分
	return 0;
}