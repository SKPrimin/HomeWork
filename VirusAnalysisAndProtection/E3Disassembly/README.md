

# 反汇编工具的使用

## 【实验目的】

1. 熟悉动态分析工具OllyDBG的界面和常用模块

2. 熟悉静态分析工具IDA的界面和常用模块

3. 掌握使用OllyDBG分析修改可执行文件的方法

## 【实验原理】

### 1OD界面

![img](反汇编工具的使用/wps2EDC.tmp.jpg) 

a. **反汇编窗口：**显示被调试程序的反汇编代码，标题栏上的地址、机器码、反汇编代码、注释。 

b. **寄存器窗口：**显示当前所选线程的 CPU 寄存器内容

c. **信息窗口**：显示反汇编窗口中选中的第一个命令的参数及一些跳转目标地址、字串等

d. **数据窗口：**显示内存或文件的内容。右键菜单可用于切换显示方式。

e. **堆栈窗口：**显示当前线程的堆栈。

### 2OD使用

#### （1） 快捷键

> a) F2：设置断点
> b) F9：运行
> c) F8：单步步过
> d) F7：单步步入
> e) F4：运行到选定位置
> f) CTRL + F9：执行到返回
> g) CTRL + F2：重新开始
> h) ALT + F9：执行到用户代码

#### （2） 查找可执行文件中所有字符串：

在`“反汇编窗口”`单击鼠标右键，选择`“查找”`选项可查看可执行文件反汇编代码的`“所有参考文本字串”`

#### （3） 修改某个内存地址的数据：

在“数据窗口”按`“Ctrl+G”`，可查找某个内存地址的值。

在`“数据窗口”`，选中要修改的数据，单击鼠标右键，选择`“二进制”`选项		的`“编辑”`项，可修改数据值。

在`“数据窗口”`，单击鼠标右键，选择`“复制到可执行文件”`选项，再选择		`“保存文件选项”`

3. OD的使用

https://www.bilibili.com/video/BV1cE411f7sE?p=1

## 【实验内容】

参看《课3-实验步骤》

### 1使用VC 6.0 编写win32 控制台程序

Hello world，得到可执行文件hello.exe

a) 创建新的工程hello：Win32 Console Application

![image-20220314165756625](反汇编工具的使用/image-20220314165756625.png)

b) 创建CPP源文件

![image-20220314170045164](反汇编工具的使用/image-20220314170045164.png)

c) 写入代码

```c++
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
```

### 2更改输出

使用《课3-实验步骤》中的方法将hello.exe的输出由“Hello World！”改为“Reverse Me！”

1. 在反汇编窗口，单击鼠标右键。查找所有

![image-20220314175431254](反汇编工具的使用/image-20220314175431254.png)

2. 在弹出的对话框中`R`框，单击鼠标右键，选择`‘查找文本’`。查找`“Hello World”`

![image-20220314180042063](反汇编工具的使用/image-20220314180042063.png)

3. 在弹出的对话框中，单击鼠标右键，选择‘查找文本’。查找“Hello World”

![image-20220314180722875](反汇编工具的使用/image-20220314180722875.png)

跳转到对应位置

![image-20220314181408177](反汇编工具的使用/image-20220314181408177.png)

4. 双击进入

![image-20220314181458268](反汇编工具的使用/image-20220314181458268.png)

5. 反汇编窗口，选中’Hello World’所在的行，单击鼠标右键-分析-从模块中删除分析。删除掉 OD的分析结果。

![image-20220314182104424](反汇编工具的使用/image-20220314182104424.png)

6. 反汇编窗口，选中’Hello World’所在的行，单击鼠标右键-分析—分析代码

![image-20220314182201975](反汇编工具的使用/image-20220314182201975.png)

#### 修改代码

##### 直接修改内容

本方式直接修改字符内容，

1. 从反汇编窗口找到字符串Hello World在内存中的地址，复制地址43402C，后点取消

![image-20220314182519838](反汇编工具的使用/image-20220314182519838.png)

2. 在内存窗口，查找地址。CtrL+G弹出查找内存地址的窗口。

![image-20220314182724443](反汇编工具的使用/image-20220314182724443.png)

3. 修改内存中的数据

![image-20220314182944321](反汇编工具的使用/image-20220314182944321.png)

4. 此处需要保证修改前后占用空间大小相同，原末尾的`0A`前移，最后填充`00`

| ![image-20220315095040608](反汇编工具的使用/image-20220315095040608.png) | 修改前                                                       |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| 修改后                                                       | ![image-20220315095134698](反汇编工具的使用/image-20220315095134698.png) |

5. 选中修改的数据，右键选择`复制到可执行文件`

![image-20220315095402537](反汇编工具的使用/image-20220315095402537.png)

6. 再次右键即可保存

   ![image-20220315095611291](反汇编工具的使用/image-20220315095611291.png)

7. 效果正确

![image-20220315095716355](反汇编工具的使用/image-20220315095716355.png)

##### 修改代码逻辑

![image-20220315124120960](反汇编工具的使用/image-20220315124120960.png)

对于此部分代码，我们可以修改逻辑

```assembly
00401172  je      short 00401188
00401174  push    0043402C                         ;  ASCII "Hello World!",LF
00401179  push    offset std::cout
0040117E  call    00401096
00401183  add     esp, 8
00401186  jmp     short 0040119A
00401188  push    0043401C                         ;  ASCII "Reverse Me!",LF
0040118D  push    offset std::cout
00401192  call    00401096
```

`je`	相等跳转，与之相对的是`jne`不等跳转	

双击修改指令

![image-20220315124602686](反汇编工具的使用/image-20220315124602686.png)

此处OD自动更改为`jnz`指令, if(ZF!=0)则跳转,所以说这两条指令完全没区别

![image-20220315124920618](反汇编工具的使用/image-20220315124920618.png)

复制到可执行

![image-20220315125257467](反汇编工具的使用/image-20220315125257467.png)

保存文件

![image-20220315125355795](反汇编工具的使用/image-20220315125355795.png)

也可以实现

![image-20220315125427562](反汇编工具的使用/image-20220315125427562.png)



### 3使用OD找到crackme3.exe的注册码

打开程序直接点击，发现弹窗`Beggar off!`内容为`Wrong Serial,try again!`。

![image-20220315143525999](反汇编工具的使用/image-20220315143525999.png)



使用OD打开程序，右键查找，所有文本模式。

![image-20220315151218861](反汇编工具的使用/image-20220315151218861.png)

再右键查找对应字符串`Wrong Serial,try again!`。

![image-20220315151405432](反汇编工具的使用/image-20220315151405432.png)

并在此处发现大量预留字符串

```assembly
00440EDC   mov ecx, 00440FC8    ;ASCII "No Name entered"
00440EE1   mov edx, 00440FD8    ;ASCII "Enter a Name!"
00440F08   mov ecx, 00440FE8    ;ASCII "No Serial entered"
00440F0D   mov edx, 00440FFC    ;ASCII "Enter a Serial!"
00440F2F   mov edx, 00441014    ;ASCII "Registered User"
00440F4C   mov edx, 0044102C    ;ASCII "GFX-754-IER-954"
00440F5A   mov ecx, 0044103C    ;ASCII "CrackMe cracked successfully"
00440F5F   mov edx, 0044105C    ;ASCII "Congrats! You cracked this CrackMe!"
00440F74   mov ecx, 00441080    ;ASCII "Beggar off!"
00440F79   mov edx, 0044108C    ;ASCII "Wrong Serial,try again!"
00440F8E   mov ecx, 00441080    ;ASCII "Beggar off!"
00440F93   mov edx, 0044108C    ;ASCII "Wrong Serial,try again!"
00440FC8   ascii "No Name entered",0
00440FD8   ascii "Enter a Name!",0
00440FE8   ascii "No Serial entere"
00440FF8   ascii "d",0
00440FFC   ascii "Enter a Serial!",0
00441014   ascii "Registered User",0
0044102C   ascii "GFX-754-IER-954",0
0044103C   ascii "CrackMe cracked "
0044104C   ascii "successfully",0
0044105C   ascii "Congrats! You cr"
0044106C   ascii "acked this Crack"
0044107C   ascii "Me!",0
00441080   ascii "Beggar off!",0
0044108C   ascii "Wrong Serial,try"
0044109C   ascii " again!",0
004410A9   mov ecx, 004410C8    ;ASCII "Have a nice day"
004410AE   mov edx, 004410D8    ;ASCII "Mail Name/Serial to acidbytes@gmx.net !"
004410C8   ascii "Have a nice day",0
004410D8   ascii "Mail Name/Serial"
004410E8   ascii " to acidbytes@gm"
004410F8   ascii "x.net !",0
00441270   push ebp                     ;(初始 CPU 选择)
00441276   mov eax, 00441160    ;UNICODE "!"
00441293   mov edx, 004412D0    ;ASCII "Crackers For Freedom CrackMe v3.0"
004412D0   ascii "Crackers For Fre"
004412E0   ascii "edom CrackMe v3."
004412F0   ascii "0",0
```

这里我们选择`"CrackMe cracked successfully"`处，双击进入查看汇编代码。

发现使用了众多`jnz`即不等跳转。以及`call`调用了众多函数。其很有可能是通过函数进行判断。

![image-20220315151726584](反汇编工具的使用/image-20220315151726584.png)

#### 动态调试

向上拉去，到合适的地方打下断点F2,运行至此F9，在弹出的额程序中我们随意（随着梁意）输入，并点击`Resgister now`随后F8逐步执行。

![image-20220315181344561](反汇编工具的使用/image-20220315181344561.png)

在这一步我们发现用户名已经被放入内存

```assembly
00440ECF   call    00420E20
```

```assembly
0019F854   0223F008  ASCII "SKPrimin"
```

![image-20220315181702830](反汇编工具的使用/image-20220315181702830.png)

在下一步发现直接跳转。

|        CMP结果        |  ZF  |
| :-------------------: | :--: |
| 目的操作数 < 源操作数 |  0   |
| 目的操作数 > 源操作数 |  0   |
| 目的操作数 = 源操作数 |  1   |

`jnz`结果不为零（或不相等）则转移，根据`ZF`标志位进行判断。

两句结合效果是进行用户名非空判断，输入非空则会进行下一步判断

```assembly
00440ED4   cmp     dword ptr [ebp-4], 0 
00440ED8   jnz     short 00440EF2
```

![image-20220315182029514](反汇编工具的使用/image-20220315182029514.png)

继续F8单步步过，发现接收了序列号，两次接收输入都调用了`00420E20`函数

![image-20220315183042781](反汇编工具的使用/image-20220315183042781.png)

同样是进行序列号是否为空的判断。

![image-20220315183032499](反汇编工具的使用/image-20220315183032499.png)

接下来为了以探究究竟，我们在下一个`00420E20`函数<kbd>F7</kbd>单步步入，发现是个三参数入栈的操作。推测可能是scanf函数

![image-20220315183231324](反汇编工具的使用/image-20220315183231324.png)



随后F8直到返回主程序，发现在调用了`00403B2C`函数之后便大幅度跳转，直到`push 0`。

![image-20220315185351128](反汇编工具的使用/image-20220315185351128.png)

在运行就直接结束咧。

![image-20220315185550014](反汇编工具的使用/image-20220315185550014.png)

至此我们可以肯定`00403B2C`函数暗藏玄机，<kbd>Ctrl</kbd> + <kbd>F2</kbd>重新开始。

#### 探究具体函数

熟练地找到字符串，双击进入，熟练地打断点、F9运行至此，同样是随机输入，点击Resgister now，F7单步步入。

但这一次我们选中到`00403B2C`，<kbd>F4</kbd>运行到选定的位置，<kbd>F7</kbd>步入。

![image-20220315185138523](反汇编工具的使用/image-20220315185138523.png)

进入后发现是个复杂的程序

`je`指令是是在(ZF=0)时进行跳转，也就是相等的时候跳转。

则刚进来就执行的这段代码，是比较eax，edx是否相等

```assembly
00403B33     39D0          cmp     eax, edx
00403B35     0F84 8F000000 je      00403BCA  
```

![image-20220315190756109](反汇编工具的使用/image-20220315190756109.png)

而敲好在其执行前，eax和eax刚刚被赋值，故其相当于比较输入的值与00441014   内存位置的值

```assembly
00440F2C       mov     eax, dword ptr [ebp-4]
00440F2F       mov     eax, 00441014                    ;  ASCII "Registered User"
```

而此处正是字符串"Registered User"

```assembly
00441014   ascii "Registered User",0
```

![image-20220315193724614](反汇编工具的使用/image-20220315193724614.png)

至此我们得知，输入的用户名必须是"Registered User"。

同样的方式重新出发。<button>Resgister now</button>

![image-20220315194202999](反汇编工具的使用/image-20220315194202999.png)

这一次直奔序列号部分，发现调用同一个函数

![image-20220315194348440](反汇编工具的使用/image-20220315194348440.png)

而这次我们可以看出，正是在此，由于比对结果不正确，变跳过了`"Congrats! You cracked this CrackMe!"`部分。

![image-20220315195007267](反汇编工具的使用/image-20220315195007267.png)

而`0044102C`的内容为`"GFX-754-IER-954"`。

![image-20220315195157969](反汇编工具的使用/image-20220315195157969.png)

接下来，我们单独打开程序。输入`Registered User`和`GFX-754-IER-954`。可以看到，成功注册！

![image-20220315195730266](反汇编工具的使用/image-20220315195730266.png)

## 【小结或讨论】

- 本次实验是对反汇编工具的一次综合使用，先是使用OD静态修改了字符串参数，或是一条指令。熟悉了OD的基本操作以及快捷键。
-  随后动态调式开始找寻注册码，有了上一次的经验，这次我们直接一字符串为切入点，很快找到了相关的代码段，进过一些处理便开始动态调试。

- 动态调试的过程中单步步入、单步步过、运行到此等一些功能灵活搭配，步入一些关键函数查找代码之间的逻辑关系。步过一些不关紧要的函数，加快进程。
- 本次也是对汇编语言的一次运用，JE、JNZ的关系和含义等等，一些跳转指令也是破译代码含义的关键。

