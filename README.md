BLDM
====

Breshless DC Motor Based on STM32

2012/11/3  OS运行正常，遇到的问题总结如下：
1) 有无HardFault产生
2) 中断是否可以运行
3）中断可以运行的情况下，可以打印任务列表来确定哪个任务运行存在问题
4) 最好使用汇编来代替ST标准库函数如：__get_PSP等
5）Makefile建议参考uboot重新编码
