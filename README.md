# ysyx

> 大致从2024/1/14开始ysyx的学习，预学习阶段耗费约5周的时间，包括间歇性的摆烂，其中花了一周多的时间学习Linux的基础部分，一周完成PA1。以及一周时间为NEMU添加RV32IM的指令集。



- **2024/3/5** ：绘制整体的框架图，包括`top module`、`regfile module`、`control unit module`
- **2024/3/6** ：小修了一下框架图，完成简单NPC的RTL代码
- **2024/3/7** ：修改简单NPC的RTL代码的语法错误，编写tbcpp文件，修改Makefile以适应**bug迭出**的`verilator`(如不弹出所有warning，避免type信号命名一致等)