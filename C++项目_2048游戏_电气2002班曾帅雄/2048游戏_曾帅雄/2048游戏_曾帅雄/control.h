#include <conio.h>// 与方向键的输入有关的头文件 
#include <iostream>
#include <ctime>// 随机数产生有关的头文件
#include <vector>// 随机数产生有关的头文件
#include <iomanip>// 格式控制
#include <windows.h>// 输出
#include <fstream>// 文件流，与记录历史最高分有关
using namespace std;
int display_arr[16];// 2048 的16个数的数组
int quitgame;// 退出游戏的控制变量
int sum =0;// 计算当前分数的变量
int formal_num = 0;// 历史最高分变量
int is_move = 0;// 判断键盘操作有效的控制变量

void read_formal_num(){ // 读取历史最高分
	int data=0;
	ifstream ifs;
	ifs.open("D:\\formal_num.txt",ios::in);
	if(ifs.is_open()){
	ifs >> data;
	formal_num = data;
	}
	ifs.close();
}

void change_new_file(){ // 判断当前分数是否为最高分，并且保存
	ofstream ofs;
	ofs.open("D:\\formal_num.txt",ios::out);
	if(sum > formal_num)
	ofs << sum <<" ";
	else
	ofs << formal_num << " ";
	ofs.close();
}

vector<int> randVector(int num) { // 产生0~15的乱序的数组 
    vector<int> result;
    result.clear();
    result.reserve(num);
    srand((int)time(0));
    for (size_t i = 0; i < num; i++)
    {
        result.push_back(i);
    }
    int p1;
    int p2;
    int temp;
    int count = num;

    while (--num)
    {
        p1 = num;
        p2 = rand() % num;
        temp = result[p1];
        result[p1] = result[p2];
        result[p2] = temp;
    }
    return result;
}

void special_input();

void print_lost(){ // 游戏失败输出
	HANDLE hout;
		COORD coord;
		coord.X=0;
		coord.Y=25;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
		cout << "YOU LOST!!!" << endl;
		cout << "TRY AGAIN" << endl;
}

void print_win(){ // 游戏胜利输出
	HANDLE hout;
		COORD coord;
		coord.X=0;
		coord.Y=25;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
		cout << "YOU WIN!!!" << endl;
}

int calculate(int k[]){ //计算当前分数
	for(int a=0; a<16; a++)
		sum += k[a];
	return sum;
}

void clearsum(){ //初始化当前分数
	sum = 0;
}

void rule_check(int k[]){ // 检查游戏是否还能正常进行
	int check_condition = 0;
	for(int a=0; a<16; a++){
		if(k[a]==0)//判断地图是否填满，没满不可能输
			check_condition++;
		if(k[a]>=2048)//游戏胜利！
			print_win();
	}
	if(check_condition == 0){
		int check_up = 0;
		int check_down = 0;
		int check_left = 0;
		int check_right = 0;
		for(int a = 1; a<=3;a++){//是否还能合成的判断
				for(int i=4*a;i<4*a+4;i++)
					if(display_arr[i] == display_arr[i-4])
						check_up++;
				for(int i=12-a*4;i<12-a*4+4;i++)
					if(display_arr[i] == display_arr[i+4])
						check_down++;
				for(int i=0+a;i<(0+a)+4*4;i+=4)
					if(display_arr[i] == display_arr[i-1])
						check_left++;
				for(int i=3-a;i<(3-a)+4*4;i+=4)
					if(display_arr[i] == display_arr[i+1])
						check_right++;
		}
		if(check_up || check_down || check_left || check_right)
			return;//如果地图满了但还可以合成，则没输，否则输了
		print_lost();
		special_input();
	}
}

void create(){ //在2048数组中产生一个随机位置的数
	 vector<int> random_arr = randVector(16);
	 for(int i=0;i<16;i++){
	 if(display_arr[random_arr[i]] == 0){
			display_arr[random_arr[i]] = 2;
			return;
		 }
	 }
}

void move(int condition){ //移动情况

	if(condition == 1){// up
		for(int b = 0; b<3; b++){//总共扫描3次，考虑所有情况
			for(int a = 1; a<=3;a++){//切换行，逐行扫描
				for(int i=4*a;i<4*a+4;i++){//这行的每个数字看是否符合合成条件
					if(display_arr[i]!=0 && display_arr[i] == display_arr[i-4]){
						display_arr[i-4] += display_arr[i];
						display_arr[i] = 0;//合成
						is_move++;//发生了合成，则这次操作有效
					}
					if(display_arr[i]!=0 && display_arr[i-4] == 0){
						int temp = display_arr[i];
						display_arr[i] = display_arr[i-4];
						display_arr[i-4] = temp;//如果相邻数字为0，则交换，代表数字移动
						is_move++;//数字移动即为有效操作
						}
				}
			}
		}
	}//以下类似，只是变量有所改变
	if(condition == 2){// down
		for(int b = 0; b<3; b++){
			for(int a = 1; a<=3;a++){
				for(int i=12-a*4;i<12-a*4+4;i++){
					if(display_arr[i]!=0 && display_arr[i] == display_arr[i+4]){
						display_arr[i+4] += display_arr[i];
						display_arr[i] = 0;
						is_move++;
					}
					if(display_arr[i]!=0 && display_arr[i+4] == 0){
						int temp = display_arr[i];
						display_arr[i] = display_arr[i+4];
						display_arr[i+4] = temp;
						is_move++;
						}
				}
			}
		}
	}
	if(condition == 3){//left
		for(int b = 0; b<3; b++){
			for(int a = 1; a<=3;a++){
				for(int i=0+a;i<(0+a)+4*4;i+=4){
					if(display_arr[i]!=0 && display_arr[i] == display_arr[i-1]){
						display_arr[i-1] += display_arr[i];
						display_arr[i] = 0;
						is_move++;
					}
					if(display_arr[i]!=0 && display_arr[i-1] == 0){
						int temp = display_arr[i];
						display_arr[i] = display_arr[i-1];
						display_arr[i-1] = temp;
						is_move++;
						}
				}
			}
		}
	}
	if(condition == 4){//right
		for(int b = 0; b<3; b++){
			for(int a = 1; a<=3;a++){
				for(int i=3-a;i<(3-a)+4*4;i+=4){
					if(display_arr[i]!=0 && display_arr[i] == display_arr[i+1]){
						display_arr[i+1] += display_arr[i];
						display_arr[i] = 0;
						is_move++;
					}
					if(display_arr[i]!=0 && display_arr[i+1] == 0){
						int temp = display_arr[i];
						display_arr[i] = display_arr[i+1];
						display_arr[i+1] = temp;
						is_move++;
						}
				}
			}
		}
	}
	if(condition == 5){// Replay 重新开始
		for(int i=0; i<16; i++)
			display_arr[i] = 0;
		 clearsum();
	}
	if(condition == 6){// Quit 退出游戏
		quitgame = 1;
	}
}

void input(){ //键盘输入读取函数
	BEGIN:
	char c1 = _getch();
	char c2 = _getch();
	switch (c2){
	case 72: // up
		cout << "up";
		move(1);
		if(is_move == 0)
			goto BEGIN;
		is_move = 0;
		break;
	case 80: // down
		cout << "down" ;
		move(2);
		if(is_move == 0)
			goto BEGIN;
		is_move = 0;
		break;
	case 75: // left
		cout << "left" ;
		move(3);
		if(is_move == 0)
			goto BEGIN;
		is_move = 0;
		break;
	case 77: // right
		cout << "right" ;
		move(4);
		if(is_move == 0)
			goto BEGIN;
		is_move = 0;
		break;
	case 'r'://重开
		move(5);
		break;
	case 'q'://退出游戏
		move(6);
		break;
	}
}

void special_input(){ //游戏失败时只能重开和退出的键盘读入操作
	while(1){
	char c1 = _getch();
	char c2 = _getch();
	switch (c2){
	case 'r':
		move(5);
		return;
		break;
	case 'q':
		move(6);
		return;
		break;
		}
	}
}

class print{ // 2048图形输出类
public:
	print(int k[]){// 6*8 output
		cout << endl;
		for(int a=0;a<16;a++)
			num[a] = k[a];
		for(int i=0;i<4;i++){
		for(int i=0;i<8*4;i++)
			cout << "_";
		cout << endl;
		for(int i=0;i<8*4;i+=8)
			cout << "|      |";
		cout << endl;
		for(int i=0;i<8*4;i+=8){
			cout << "|"<<setw(5) << num[count] <<" |";
			count++;
		}
		cout << endl;
		for(int i=0;i<8*4;i+=8)
			cout << "|      |";
		cout << endl;
		for(int i=0;i<8*4;i+=8)
			cout << "|      |";
		cout << endl;
		for(int i=0;i<8*4;i++)
			cout << "-";
		cout << endl;
		}
		count = 0;
	}
	int num[16];//2048 的一维数组
	static int count;
};
int print::count = 0;

void printHelp(){ //菜单及解释说明输出函数
	    int x = 10;int y =40;
		HANDLE hout;//先列后行
		COORD coord;
		coord.X=y;
		coord.Y=x;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
		cout << "按上下左右键控制方块移动方向";
		x++;//输出之后行坐标加一，相当于在列不变的情况下换行
		coord.X=y;
		coord.Y=x;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
		cout << "双击R键重新开始游戏";
		x++;
		coord.X=y;
		coord.Y=x;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
		cout << "双击Q键退出游戏";
		x++;
		coord.X=y;
		coord.Y=x;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
		cout << "历史最高分：" << setw(8) << formal_num;
		x++;
		coord.X=y;
		coord.Y=x;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
		cout << "当前分数：" << setw(8) << calculate(display_arr);
		//计算并显示当前分数
	    change_new_file();// 保存历史最高分
		clearsum(); //初始化现在分数以便下次计算
		x++;
		coord.X=y;
		coord.Y=x;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
		cout << "两个数字相同的方块撞在一起后，将会合并为一个数字是原来两倍的新方块!";
		x++;
		coord.X=y;
		coord.Y=x;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
		cout << "目标：合成2048！";
		x++;
		coord.X=y;
		coord.Y=x;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
}
