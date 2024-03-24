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
