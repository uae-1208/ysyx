# ysyx

> 大致从2024/1/14开始ysyx的学习，预学习阶段耗费约5周的时间，包括间歇性的摆烂，其中花了一周多的时间学习Linux的基础部分，一周完成PA1。以及一周时间为NEMU添加RV32IM的指令集。



- **2024/3/5** ：绘制整体的框架图，包括`top module`、`regfile module`、`control unit module`
- **2024/3/6** ：小修了一下框架图，完成简单NPC的RTL代码
- **2024/3/7** ：修改简单NPC的RTL代码的语法错误，编写tbcpp文件，修改Makefile以适应**bug迭出**的`verilator`(如不弹出所有warning，避免type信号命名一致等)
- **2024/3/8** ：完成了简单的NPC部分，包括执行`addi`指令和`DPI-C`机制下的`ebreak`指令（又被`Verilator`折磨了几个小时：在**多.v文件体系**下使用`import "DPI-C" function <return_type> <function_name>(<argument_list>);`时，要将其放在**module内部**，否则又会报重复定义的错。）
- **2024/3/9** ：学习了`.gtkw`文件的妙用，并在`Makefile`中添加相应的指令。粗略了阅读AM的Makefile。
- **2024/3/10** ：仔细了阅读AM的`Makefile`和观看了B站视频。在这一天的最后半小时悟到如何通过AM的`Makefile`设置nemu的批处理模式。
- **2024/3/12** ：完善AM和NEMU的笔记，并且实现了部分的`string.c`。
- **2024/3/13** ：完整实现`string.c`并通过`string` cpu test。
- **2024/3/15** ：实现了`stdio.c`中的`sprintf`系列函数。效率属实有点低。
- **2024/3/16** ：看B站的elf课程录制，整理Markdown笔记。
- **2024/3/17** ：修改`nemu.md`和`defect.md`，完成`iringbuf`和`mtrace`。
- **2024/3/18** ：完成了解析`elf`文件的代码框架。
- **2024/3/20** ：完成了`ftrace`。
- **2024/3/21** ：完成了`difftest`。
- **2024/3/23** ：阅读`npc`的makefile文件，给`npc`添加了`auipc`指令。
- **2024/3/24** ：给`npc`添加了`auipc`、`jal`、`jalr`、`sw`指令，建立了`monitor`和`sdb`框架。
- **2024/3/25** ：添加了`sdb`、`itrace`、`ftrace`和`iringbuf`。
- **2024/3/26** ：为`nemu`添加了`REF DiffTest`接口，为`npc`添加了`DiffTest`框架并验证`dummy`程序执行的正确性。  
- **2024/3/27** ：为`npc`添加了`FTrace`。  
- **2024/3/28** ：为`npc`添加了`add, sub, lw, sw`等4条指令。  
- **2024/4/3** ：为`npc`添加了`sltiu, beq, bne, sltu, xor,or,sh,srai`等8条指令。  
- **2024/4/4** ：为`npc`添加了`lbu, andi, sll, and, xori, sb, bge, blt, lui, srli, bgeu, slli, bltu, lh, lhu, sra, srl`等17条指令。  
- **2024/4/5** ：将`npc`从**三周期**改成了**单周期**，频率提升了3倍。    `verilator`太多坑了，`inst_data`会莫名其妙被`rdata_temp = pmem_read(raddr);`修改。
- **2024/4/7** ：看`IO`的源代码。
- **2024/4/8** ：完成了`IO`的串口部分。
- **2024/4/8** ：完成了`IO`的`RTC`部分。
- **2024/4/9** ：在`kilb`中添加`malloc`和`free`函数，为`nemu`增加`dtrce`，完成了`IO`的键盘部分。
- **2024/4/10** ：在`kilb`中添加`malloc`和`free`函数，为`nemu`增加`dtrce`，完成了`IO`的键盘部分。
- **2024/4/12** ：完成了`IO`的`vga`部分。
- **2024/4/14** ：整理笔记，完成`PA2`。
- **2024/4/16** ：完成了`NPC`的外设部分，并且修改了`DiffTest`的框架。
- **2024/4/17** ：修补了`NPC`的一些小bug。
- **2024/4/18** ：完成了除`etrace`之外的`PA3.1`。
- **2024/4/20** ：完成了`etrace`，修改`trap.S`，看了一些`PA4.1`。
- **2024/4/21** ：完成了`yoeld-os`。
- **2024/4/23** ：为`npc`添加了`csrrw`、`csrrs`、`mret`、`ecall`等特权指令和`etrace`。
- **2024/4/27** ：重构了`npc`的框图，完成了`idu`和`exu`的rtl代码。
- **2024/4/28** ：完成了整体的rtl代码，但是握手协议还没有着手写。
- **2024/5/1** ：构思出了比较合理的握手协议，并画出其时序图。
- **2024/5/2** ：完成了所有的RTL代码，修改了一下cpp部分以适配新的微结构，但是还存在一些bug。
- **2024/5/3** ：修改了的RTL代码和cpp代码的bug，同时通过所有的IO测试。
- **2024/5/5** ：水论文。
- **2024/5/6** ：完成了新框架下的CSR部分。


