# 游戏外挂设计与防范——扫雷

实验说明：游戏外挂是通过篡改游戏原本设定和规则制作而成的辅助程序，它不仅破坏了游戏的公平性、影响游戏生态的健康发展，另外许多外挂程序捆绑木马程序，直接威胁玩家的虚拟财产安全。

实验目的：本实验通过分析 Windows XP 附带的扫雷游戏，实现自动扫雷的外挂程序，一方面了解内存外挂的相关技术，另一方面分析防范此类外挂的方法。

实验原理：通过读写内存数据，确定游戏雷区，之后模拟鼠标操作，实现自动扫雷。

实验环境：Windows 桌面系统

实验工具：Visual Studio 6.0 及以上版本，CheatEngine，Windows XP 扫雷游戏

参与作者：[lanpesk](https://lanpesk.github.io/)、[对酒当歌](https://blog.csdn.net/youyouwoxi)

# 实验步骤

1.  加载游戏

运行扫雷游戏，然后打开 CheatEngine(CE)，加载游戏进程，如图 8-1 所示。

<img src="游戏外挂设计与防范/image-20220506151226280.png" alt="image-20220506151226280" style="zoom: 50%;" />

<center>图 8-1 CheatEngine 打开游戏进程</center>

2.  寻找地雷数量的内存地址

> 在 CE 界面选择数据类型为 4 字节，扫描类型为"精确数值"，数值内容填写扫雷游戏所显示的地雷数量，然后单击"初次扫描"，如图 8-2 所示。

<img src="游戏外挂设计与防范/image-20220506151330137.png" alt="image-20220506151330137" style="zoom:50%;" />

<center>图 8-2 初次扫描地雷数量</center>

显然这么多的地址我们时很难分辨出哪个是代表雷个数的

> 调整扫雷游戏难度等级，使地雷数量发生改变，然后在 CE 界面填写新的地雷数量，单击"再次扫描"按钮。不断重复这样的操作，直至 CE 左侧找到的地址数降为个位数，双击所找到的地址，将其添加到 CE 下方地址列表中。

<img src="游戏外挂设计与防范/image-20220506152711634.png" alt="image-20220506152711634" style="zoom: 33%;" />

现在只剩下两个了

![image-20220506153942924](游戏外挂设计与防范/image-20220506153942924.png)

然而接下俩我们无论怎么调整难度都是这哥仨，为了能够变数，我们可以鼠标右键标记几个雷再扫描雷数，实际上我们已经不用扫了，这是实时变化的

<img src="游戏外挂设计与防范/image-20220506153854751.png" alt="image-20220506153854751" style="zoom: 33%;" />

显然雷数的地址在 `01005194`

双击将其添加到 CE 下方地址列表中。

![image-20220506154417257](游戏外挂设计与防范/image-20220506154417257.png)

3.  寻找雷区行和列所对应的内存地址

> 单击"新的扫描"按钮，在 CE 界面选择数据类型为 4 字节，扫描类型为"精确数值"，数值内容填写雷区的行数，例如初级行和列均为 9，然后单击初次扫描按钮。

<img src="游戏外挂设计与防范/image-20220506154349855.png" alt="image-20220506154349855" style="zoom: 33%;" />

> 在扫雷程序单击"游戏\--自定义"设置新的高度和宽度值，然后在 CE 界面填写新行或列的数值，单击"再次扫描"按钮。不断重复这样的操作，直至 CE 左侧找到的地址数减少为个位数，双击所找到的地址，将其添加到 CE 下方地址列表中。

为了能更快，我们可以选择一些冷门的数字

<img src="游戏外挂设计与防范/image-20220506154622733.png" alt="image-20220506154622733" style="zoom:33%;" />

扫描便只剩下四个

<img src="游戏外挂设计与防范/image-20220506154653060.png" alt="image-20220506154653060" style="zoom: 50%;" />

再次修改，本次修改为 高 10 宽20

<img src="游戏外挂设计与防范/image-20220506154939751.png" alt="image-20220506154939751" style="zoom:33%;" />

我们暂且全部加载进去，由于加载的数量较多，我们可以命名

![image-20220506155339049](游戏外挂设计与防范/image-20220506155339049.png)

4.  寻找游戏计时的内存地址

> 单击"新的扫描"按钮，在 CE 界面选择数据类型为 4 字节，扫描类型为"精确数值"，数值内容填写 0，然后单击初次扫描按钮。

<img src="游戏外挂设计与防范/image-20220506155550103.png" alt="image-20220506155550103" style="zoom:50%;" />



> 点开雷区任意一个格子，使游戏开始计时，在 CE 界面将扫描类型改为"增加的数值"，然后单击"再次扫描"。计时增加后，重复这样的操作，或者计时增加到较高数值后开始新的一局，然后将 CE 扫描类型改为"减少的数值"，再次扫描。直至找出计时地址，双击、将其添加到 CE 下方地址列表中。

<img src="游戏外挂设计与防范/image-20220506155720631.png" alt="image-20220506155720631" style="zoom:50%;" />

尝试了几次发现效果不明显

<img src="游戏外挂设计与防范/image-20220506155837213.png" alt="image-20220506155837213" style="zoom:50%;" />

于是使用更精确的`Value between`

![image-20220506160138283](游戏外挂设计与防范/image-20220506160138283.png)

于是分段两次便直接定位，双击加到下方地址列表

<img src="游戏外挂设计与防范/image-20220506160058562.png" alt="image-20220506160058562" style="zoom:50%;" />

5.  扫描雷区内存地址范围

> 单击 CE"新的扫描"按钮，选择数据类型为 Byte，扫描类型为"未知的初始数值"，然后进行初次扫描，如图 8-3 所示。

<img src="游戏外挂设计与防范/image-20220506151442077.png" alt="image-20220506151442077" style="zoom:50%;" />

<center>图 8-3 扫描雷区的内存地址范围</center>

> 左键单击雷区左上角第一个格子，然后将 CE 扫描类型改为"变动的数值"，再单击 CE"再次扫描"按钮。开启新一局游戏，重复这样的操作，直至左侧地址（被标注为绿色的地址）减少为个位数。

> 重复操作过程中切记：**只要左上角格子被翻开或者开始新局时被覆盖，都选择"变动的数值"进行一次扫描**。

<img src="游戏外挂设计与防范/image-20220506160555042.png" alt="image-20220506160555042" style="zoom:50%;" />

直接循环重开难以找到，我们在其宣示为绿色的地方再点击查看，发现`01005164`处发生变化。

<img src="游戏外挂设计与防范/image-20220506163308328.png" alt="image-20220506163308328" style="zoom:50%;" />

在扫描得到的多组地址中，依次通过右键"浏览相关内存区域"，打开地址所对应的内存空间，然后通过开始新一局游戏和点击雷区左上角的操作，确定**雷区真实的内存起始地址，以及地雷和非地雷的标识**，

<img src="游戏外挂设计与防范/image-20220506163852155.png" alt="image-20220506163852155" style="zoom: 33%;" />

随后我们稍微下拉，开始游戏

开始时<img src="游戏外挂设计与防范/image-20220506164128953.png" alt="image-20220506164128953" style="zoom: 33%;" />

踩雷时<img src="游戏外挂设计与防范/image-20220506164216049.png" alt="image-20220506164216049" style="zoom:33%;" />

确定**雷区真实的内存起始地址，以及地雷和非地雷的标识**，地址为：`01005361 `，

地雷标识数据为： 

- 未爆炸`8F`，
- 爆炸`8A`，
- 起爆点`CC`，
- 标上旗子为`8E`
- 标上问号为`8D`

非地雷标识数据为：

- 未点开：`0F`，
- 空：`40`，
- 雷的个数为：`41、42、43、44、45、46……` 。
- 标旗为`0E`
- 标问号为`0D`

最后通过创建新一局游戏，依次点击第 1、2、3 行最左侧格子的操作确定雷区每行的起始地址，寻找起始地址与雷区行和列之间的对应关系，

第二行![image-20220506164610310](游戏外挂设计与防范/image-20220506164610310.png)

第三行

![image-20220506164659812](游戏外挂设计与防范/image-20220506164659812.png)

即确定**每行格子的数量，**为：`0x20=32` 。

7.  确定扫雷游戏格子大小

打开 Spy++，单击"监视\--日志消息"，勾选"隐藏 Spy++选项"，拖动"查找程序工具"至扫雷游戏主界面，如图 8-4 所示，显示的内容包括扫雷窗口类（WNDCLASS）的名称以及标题名。

<img src="游戏外挂设计与防范/image-20220506164934954.png" alt="image-20220506164934954" style="zoom:33%;" />

<img src="游戏外挂设计与防范/image-20220506151457523.png" alt="image-20220506151457523" style="zoom:50%;" />

<center>图 8-4 Spy++监视扫雷游戏窗口</center>

切换至 Spy++的"消息"窗口，先清除所有消息，然后勾选"WM_LBUTTONDOWN 和 WM_LBUTTONUP"两个消息，如图 8-5 所示，单击确定后返回 Spy++主界面。

<img src="游戏外挂设计与防范/image-20220506151517029.png" alt="image-20220506151517029" style="zoom:50%;" />

<center>图 8-5 Spy++监视扫雷消息</center>



返回扫雷游戏界面，依次单击左上角、紧邻左上角右方、紧邻左上角下方的三个格子，查看 Spy++记录的鼠标单击时的 xPos 和 yPos 的值，以此计算每个格子的宽度和高度。

得到数据：

![image-20220506165827183](游戏外挂设计与防范/image-20220506165827183.png)

x横向 $39-16=23$，y纵向 $78-60=18$

在 Spy++界面，右键\--清除消息日志，然后重复上述操作，也可间隔数个格子单击，以此**计算每个格子的平均值，作为每个格子的宽和高度值**。

三点定位

![image-20220506170049839](游戏外挂设计与防范/image-20220506170049839.png)

x横向 $149-17=132$，纵向 $190-63=127$

平均值 x横向 $16.5$，y纵向 $15.8$

格子的宽度为：16.5 ；格子的高度为：15.8 。

# 编程实现

## 实现逻辑

1.  创建 WIN32 空项目；
2.  打开扫雷进程，根据雷区的行和列所在内存地址，获取行、列的值；
3.  根据雷区首地址和雷区范围，读取雷区数据；
4.  将扫雷游戏界面置顶，读取雷区第 i 行第 j 列的数值，判断是否为地雷，如果不是则模拟鼠标左键单击操作，如果是地雷则模拟鼠标右键单击操作。
5.  根据扫雷游戏界面的客户坐标系，计算第 i 行第 j 列的坐标位置，然后将鼠标移动到该位置，执行第 3 步的鼠标操作。
6.  重复 3-4，直至雷区数据全部被扫描完成。

## 相关 API 函数

> 读写内存地址中的内容使用的 WindowsAPI 函数为：
>
> ```c++
> BOOL ReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesRead);
> 
> BOOL WriteProcessMemory( HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesWritten);
> ```

随后使用ReadProcessMemory来获取对应地址的数据。这里的地址我们是在CE中拿到的。
这里我们开辟data这个数据的代码写的不太规范，可能在别的编译器中无法通过。可以将height换为24。


```c++
ReadProcessMemory(hProcess,(LPVOID)0x1005334, &width,sizeof(BYTE),NULL);
ReadProcessMemory(hProcess,(LPVOID)0x1005338, &height,sizeof(BYTE),NULL);
```

> 读写内存 API 函数需要目标进程的句柄作为参数，为此需要调用OpenProcess 用于获取进程句柄：
>
> ```c++
> HANDLE OpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId);
> ```

```cpp
HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
```

> OpenProcess 需要进程 ID 作为参数，可通过 GetWindowThreadProcessId 函数得到：
>
> ```c++
> DWORD GetWindowThreadProcessId(HWND hWnd, LPDWORD lpdwProcessId);
> ```

```cpp
GetWindowThreadProcessId(hwnd, &pid);
```

> GetWindowThreadProcessId 函数需要窗口句柄作为参数，为此可通过FindWindow 获得，而该 API 函数用到的窗口类和窗口标题名两个参数，已在步骤（7）中通过 Spy++得到。
>
> ```c++
> HWND FindWindowA(LPCSTR lpClassName, LPCSTR lpWindowName);
> ```



> 模拟鼠标操作的 API 函数为 mouse_event，具体使用方式为，使用SetCursorPos API 函数将鼠标移动到指定位置，然后模拟鼠标按下和弹起操作。函数声明如下：
>
> ```c++
> void mouse_event(DWORD dwFlags, DWORD dx, DWORD dy, DWORD dwData, ULONG_PTR dwExtraInfo);
> BOOL SetCursorPos(int X, int Y);
> ```

本实验中 mouse_event 函数仅需设置第一项参数即可，具体包括左键按下、弹起（MOUSEEVENTF_LEFTDOWN、MOUSEEVENTF_LEFTUP），右键按下、弹起（MOUSEEVENTF_RIGHTDOWN、MOUSEEVENTF_RIGHTUP）。

Spy++记录的消息日志中 xPos 和 yPos 均是以扫雷游戏窗口左上角作为坐标系原点，而 mouse_event 以桌面左上角作为坐标系原点，因此使用 SetCursorPos 移动鼠标位置时，需要进行坐标系转换，具体操作如下：

![image-20220506151746783](游戏外挂设计与防范/image-20220506151746783.png)

将某个 GUI 程序界面置顶的 API 函数为：

```c++
BOOL SetForegroundWindow(HWND hWnd);
```

综合上述部分，我们只需要在内容不为0x8F的地方，左击即可

```cpp
#include <windows.h>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	HWND hwnd = FindWindow(TEXT("扫雷"), TEXT("扫雷"));
	if
		(hwnd == NULL)
	{
		MessageBox(NULL, TEXT("Winmine is not found!"), TEXT("AutoMineSweeper"), MB_ICONSTOP);
		return 1;
	}

	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	int width = 0, height = 0;
	ReadProcessMemory(handle, (LPCVOID)0x01005338, &width, sizeof(int), NULL);
	ReadProcessMemory(handle, (LPCVOID)0x01005334, &height, sizeof(int), NULL);

	BYTE data[32 * 24] = { 0 };
	ReadProcessMemory(handle, (LPCVOID)0x01005361, data, 24 * 32, NULL);

	ShowWindow(hwnd, SW_RESTORE);
	SetForegroundWindow(hwnd);
	Sleep(300);
	int xPos, yPos;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++)
		{
			if(data[32 * y + x] != 0x8F)
			{
				xPos = 20 + x * 16;
				yPos = 62 + y * 16;
				RECT rect;
				GetClientRect(hwnd, &rect);
				POINT curPos = { rect.left + xPos, rect.top + yPos };
				ClientToScreen(hwnd, &curPos);
				SetCursorPos(curPos.x, curPos.y);

				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
		}
	}
	CloseHandle(handle);
	return 0;
}

```

![image-20220513173602268](游戏外挂设计与防范/image-20220513173602268.png)



如果我们稍加润色，也可以对读入的雷区数据做判断，如果最高位为0，那么就左击。如果是雷就右击。这样我们就能实现自动扫雷。

```cpp
#include <windows.h>

using namespace std;

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    HWND hwnd = FindWindow(TEXT("扫雷"), TEXT("扫雷"));

    if (hwnd == NULL)
    {
        MessageBox(NULL, TEXT("Winmine is not found!"), TEXT("AutoMineSweeper"), MB_ICONSTOP);
        return 1;
    }

    DWORD pid;
    GetWindowThreadProcessId(hwnd, &pid);
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    int width, height;
    ReadProcessMemory(handle, (LPCVOID)0x1005334, &width, sizeof(width), NULL);
    ReadProcessMemory(handle, (LPCVOID)0x10056A8, &height, sizeof(height), NULL);


    BYTE data[32 * 24] = { 0 };
    ReadProcessMemory(handle, (LPCVOID)0x1005360, &data, sizeof(BYTE) * 32 * height, NULL);

    ShowWindow(hwnd, SW_RESTORE);
    SetForegroundWindow(hwnd);
    Sleep(300);

    // position trans
    int xPos = 12, yPos = 54;
    int blockWidth = 16, blockHeight = 16;
    RECT rect;
    GetClientRect(hwnd, &rect);
    POINT curPos = { rect.left + xPos + blockWidth / 2, rect.top + yPos + blockHeight / 2 };
    ClientToScreen(hwnd, &curPos);
    SetCursorPos(curPos.x, curPos.y);

    int index = 0;
    int currentX = curPos.x, currentY = curPos.y;
    int startX = rect.left + xPos + blockWidth / 2;
    int startY = rect.top + yPos + blockHeight / 2;
    for (int y = 1; y <= height; y++)
    {
        for (int x = 1; x <= width; x++)
        {
            if (data[index + x] & 0x80)
            {
                mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
            }
            else
            {
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            }
            curPos.x += blockWidth;
            SetCursorPos(curPos.x, curPos.y);
        }
        index += 32;
        curPos.x = startX;
        curPos.y = startY;
        ClientToScreen(hwnd, &curPos);
        curPos.y += y * blockHeight;
        SetCursorPos(curPos.x, curPos.y);
    }
    CloseHandle(handle);
    return 0;
}

```



# 8、思考与总结

1.  除了使用 CE 得到各项地址外，还有哪些方法可以得到这些地址？
    - OD、IDA等著名工具得到这些地址。
2.  除了通过模拟鼠标按键操作之外，还有哪些方法能够实现自动扫雷？
    - 直接修改内存内容，将0x8F改成0x0E标旗。
3.  如何防范内存型外挂？
    - 单人游戏可以通过多地点存放数据，增加破解难度
    - 多人游戏游戏时时上传数据，数据较大也可传递hash值，服务器时时比较
    - 重要的数据不以明文的方式保存。可以采用多重的分散和引用关系，来复杂数据的分配。使得从内存中无法得到准确的数据和直接关联的数据。可以引入监测机制，检测内存数据是否被外部程序所读取或者修改。
