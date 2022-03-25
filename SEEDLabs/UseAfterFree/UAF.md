1、名词解释：double free，UAF (Use After Free)，RELRO(Relocation Read Only)，Dangling pointer，Control Flow Guard

> Double Free是同一个指针free两次。实际上只要是free一个指向堆内存的指针都有可能产生可以利用的漏洞。

> Use After Free(UAF)是一个与程序运行期间不正确使用动态内存相关的漏洞。如果在释放内存位置后，程序没有清除指向该内存的指针，那么攻击者可以利用该错误来攻击程序。
>
> UAF漏洞源于动态内存分配机制。与堆栈不同，动态内存(也称为堆)旨在存储大量数据。程序员可以在堆中分配任意大小的块，程序中的任务可以修改或释放堆，然后返回堆中，供同一程序中的其他任务后续使用。
>
> 由于动态内存是重复重新分配的，程序需要不断地检查堆的哪些部分是空闲的，哪些部分被占用了。在这里，头文件通过引用已分配的内存区域来提供帮助。每个报头包含相应块的起始地址。当程序没有正确管理这些头文件时，就会出现UAF错误。
>
> 这是如何发生的。程序中的指针指向动态内存中的数据集。如果一个数据集被删除或移动到另一个块，但是指针没有被清除(设置为null)，而是继续指向现在释放的内存，结果是一个悬空指针。如果程序随后将相同的内存块分配给另一个对象(例如，攻击者输入的数据)，空指针现在将引用这个新数据集。也就话说，UAF漏洞允许代码替换。
>
> https://encyclopedia.kaspersky.com/glossary/use-after-free/

> 重定位只读(Relocation Read-Only，简称RELRO)是一种安全措施，它使一些二进制区段只读。
>
> RELRO(Relocation Read Only)告诉链接器在执行开始时解析所有动态链接的函数，并使文件变为只读。
>
> 现在在生成可执行文件或共享库时，将其标记为告诉动态链接器解析程序时的所有符号或当共享库被链接到使用时Dlopen，而不是将函数调用解析延迟到第一次调用函数时的点。
>
> > 部分RELRO
> > Partial RELRO是GCC中的默认设置，您将看到的几乎所有二进制文件都至少有Partial RELRO。
>
> > 全RELRO
> > 全RELRO使整个GOT变成只读，从而消除了执行“GOT覆盖”攻击的能力，即一个函数的GOT地址被另一个函数的位置或一个攻击者想要运行的ROP小工具覆盖。
>
> https://blog.osiris.cyber.nyu.edu/exploitation%20mitigation%20techniques/exploitation%20techniques/2011/06/02/relro-relocation-read-only/

> 顾名思义，悬空指针是指向无效内存或不再有效的内存的指针。当引用对象被删除或释放时，摆动指针出现，而指针仍然指向一个内存位置。它造成了一个问题，因为指针指向不可用的内存。当我们尝试解引用这种类型的指针时，它会显示未定义的行为，并可能导致分段错误。

> 控制流保护(CFG)是一个高度优化的平台安全特性，是为了对抗内存破坏漏洞而创建的。通过严格限制应用程序可以从何处执行代码，它使得利用缓冲区溢出等漏洞执行任意代码变得更加困难。CFG扩展了以前的exploit缓解技术，如/GS、DEP和ASLR。

2、阅读下面这三篇文章：
UAF学习--原理及利用
https://www.cnblogs.com/alert123/p/4918041.html

本文介绍了如何利用UAF

Linux内核提权漏洞的分析和利用（CVE-2016-0728）
http://www.freebuf.com/vuls/93799.html

看不了

通过UseAfterFree实现命令执行
https://bbs.pediy.com/thread-221537.htm

利用UAF漏洞，实现GOT表覆盖，从而实现命令执行，