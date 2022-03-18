#include<iostream> //cout头文件
#include "windows.h" //syeten头文件
using namespace std;
VOID displasy(bool bhello)
{
	if (bhello)
		cout<<"Hello World!\n";
	else
		cout<<"Reverse Me!\n";
}
int main(int argc, char* argv[])
{
	bool bFlag=true ;
	displasy(bFlag);
	system("pause"); //系统命令pause,在屏幕输出press any key
	return 0;
}
