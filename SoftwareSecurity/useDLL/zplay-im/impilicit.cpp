#include <stdio.h>
#include <stdlib.h>
#include "libzplay.h"
// 导入lib,否则报错 LNK2019 无法解析的外部符号
#pragma comment(lib,"libzplay.dll")


void prompt(int statevalue)
{
	printf("当前播放状态：");
	switch (statevalue)
	{
	case 1:
		printf("播放");
		break;
	case 2:
		printf("暂停");
		break;
	case 3:
		printf("停止");
		break;
	default:
		break;
	}
	printf("\n请输入操作代号：\n播放：1，暂停：2，停止：3:");
}

int main()
{
	ZPLAY_HANDLE player = zplay_CreateZPlay(); // 创建实例，libzplay申请各类资源
	zplay_OpenFile(player, "homeland.mp3", sfAutodetect); //打开音乐文件
	zplay_Play(player); // 播放音乐文件

	int statevalue = 1; //定义音乐播放状态，初始时播放
	prompt(1);
	while (scanf_s("%d",&statevalue))
	{
		switch (statevalue)
		{
		case 1:
			zplay_Play(player);
			prompt(1);
			break;
		case 2:
			zplay_Pause(player); // 暂停音乐播放
			prompt(2);
			break;
		case 3:
			zplay_Stop(player); // 停止音乐播放
			goto outexit; // 输入停止命令后跳到关闭文件、资源部分
			prompt(3);
			break;
		default:
			break;
		}
	}
	outexit:
	zplay_Close(player); //关闭不再播放的音乐文件
	zplay_DestroyZPlay(player);//销毁libzplay申请的各类资源

	system("pause");
	return 0;
}