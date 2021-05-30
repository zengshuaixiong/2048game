#include <conio.h>// �뷽����������йص�ͷ�ļ� 
#include <iostream>
#include <ctime>// ����������йص�ͷ�ļ�
#include <vector>// ����������йص�ͷ�ļ�
#include <iomanip>// ��ʽ����
#include <windows.h>// ���
#include <fstream>// �ļ��������¼��ʷ��߷��й�
using namespace std;
int display_arr[16];// 2048 ��16����������
int quitgame;// �˳���Ϸ�Ŀ��Ʊ���
int sum =0;// ���㵱ǰ�����ı���
int formal_num = 0;// ��ʷ��߷ֱ���
int is_move = 0;// �жϼ��̲�����Ч�Ŀ��Ʊ���

void read_formal_num(){ // ��ȡ��ʷ��߷�
	int data=0;
	ifstream ifs;
	ifs.open("D:\\formal_num.txt",ios::in);
	if(ifs.is_open()){
	ifs >> data;
	formal_num = data;
	}
	ifs.close();
}

void change_new_file(){ // �жϵ�ǰ�����Ƿ�Ϊ��߷֣����ұ���
	ofstream ofs;
	ofs.open("D:\\formal_num.txt",ios::out);
	if(sum > formal_num)
	ofs << sum <<" ";
	else
	ofs << formal_num << " ";
	ofs.close();
}

vector<int> randVector(int num) { // ����0~15����������� 
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

void print_lost(){ // ��Ϸʧ�����
	HANDLE hout;
		COORD coord;
		coord.X=0;
		coord.Y=25;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
		cout << "YOU LOST!!!" << endl;
		cout << "TRY AGAIN" << endl;
}

void print_win(){ // ��Ϸʤ�����
	HANDLE hout;
		COORD coord;
		coord.X=0;
		coord.Y=25;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
		cout << "YOU WIN!!!" << endl;
}

int calculate(int k[]){ //���㵱ǰ����
	for(int a=0; a<16; a++)
		sum += k[a];
	return sum;
}

void clearsum(){ //��ʼ����ǰ����
	sum = 0;
}

void rule_check(int k[]){ // �����Ϸ�Ƿ�����������
	int check_condition = 0;
	for(int a=0; a<16; a++){
		if(k[a]==0)//�жϵ�ͼ�Ƿ�������û����������
			check_condition++;
		if(k[a]>=2048)//��Ϸʤ����
			print_win();
	}
	if(check_condition == 0){
		int check_up = 0;
		int check_down = 0;
		int check_left = 0;
		int check_right = 0;
		for(int a = 1; a<=3;a++){//�Ƿ��ܺϳɵ��ж�
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
			return;//�����ͼ���˵������Ժϳɣ���û�䣬��������
		print_lost();
		special_input();
	}
}

void create(){ //��2048�����в���һ�����λ�õ���
	 vector<int> random_arr = randVector(16);
	 for(int i=0;i<16;i++){
	 if(display_arr[random_arr[i]] == 0){
			display_arr[random_arr[i]] = 2;
			return;
		 }
	 }
}

void move(int condition){ //�ƶ����

	if(condition == 1){// up
		for(int b = 0; b<3; b++){//�ܹ�ɨ��3�Σ������������
			for(int a = 1; a<=3;a++){//�л��У�����ɨ��
				for(int i=4*a;i<4*a+4;i++){//���е�ÿ�����ֿ��Ƿ���Ϻϳ�����
					if(display_arr[i]!=0 && display_arr[i] == display_arr[i-4]){
						display_arr[i-4] += display_arr[i];
						display_arr[i] = 0;//�ϳ�
						is_move++;//�����˺ϳɣ�����β�����Ч
					}
					if(display_arr[i]!=0 && display_arr[i-4] == 0){
						int temp = display_arr[i];
						display_arr[i] = display_arr[i-4];
						display_arr[i-4] = temp;//�����������Ϊ0���򽻻������������ƶ�
						is_move++;//�����ƶ���Ϊ��Ч����
						}
				}
			}
		}
	}//�������ƣ�ֻ�Ǳ��������ı�
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
	if(condition == 5){// Replay ���¿�ʼ
		for(int i=0; i<16; i++)
			display_arr[i] = 0;
		 clearsum();
	}
	if(condition == 6){// Quit �˳���Ϸ
		quitgame = 1;
	}
}

void input(){ //���������ȡ����
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
	case 'r'://�ؿ�
		move(5);
		break;
	case 'q'://�˳���Ϸ
		move(6);
		break;
	}
}

void special_input(){ //��Ϸʧ��ʱֻ���ؿ����˳��ļ��̶������
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

class print{ // 2048ͼ�������
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
	int num[16];//2048 ��һά����
	static int count;
};
int print::count = 0;

void printHelp(){ //�˵�������˵���������
	    int x = 10;int y =40;
		HANDLE hout;//���к���
		COORD coord;
		coord.X=y;
		coord.Y=x;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
		cout << "���������Ҽ����Ʒ����ƶ�����";
		x++;//���֮���������һ���൱�����в��������»���
		coord.X=y;
		coord.Y=x;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
		cout << "˫��R�����¿�ʼ��Ϸ";
		x++;
		coord.X=y;
		coord.Y=x;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
		cout << "˫��Q���˳���Ϸ";
		x++;
		coord.X=y;
		coord.Y=x;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
		cout << "��ʷ��߷֣�" << setw(8) << formal_num;
		x++;
		coord.X=y;
		coord.Y=x;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
		cout << "��ǰ������" << setw(8) << calculate(display_arr);
		//���㲢��ʾ��ǰ����
	    change_new_file();// ������ʷ��߷�
		clearsum(); //��ʼ�����ڷ����Ա��´μ���
		x++;
		coord.X=y;
		coord.Y=x;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
		cout << "����������ͬ�ķ���ײ��һ��󣬽���ϲ�Ϊһ��������ԭ���������·���!";
		x++;
		coord.X=y;
		coord.Y=x;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
		cout << "Ŀ�꣺�ϳ�2048��";
		x++;
		coord.X=y;
		coord.Y=x;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,coord);
}
