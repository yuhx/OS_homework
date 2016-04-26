参考wiki上的资料使用CPP编写了程序。编译时要加上-lpthread参数。

在进程进入和退出临界区的时候都输出了turn的值，并且临界区中输出了所有进程flags的值，可以发现turn在临界区中并未被改变，实验成功。
如下是一组输出值。

Process 0 enter
2000000000
Process 0 exit

Process 1 enter
0200000000
Process 1 exit

Process 2 enter
0020000000
Process 2 exit

Process 3 enter
0002000000
Process 3 exit

Process 4 enter
0000210000
Process 4 exit

Process 5 enter
0000021000
Process 5 exit

Process 6 enter
0000002000
Process 6 exit

Process 7 enter
0000000200
Process 7 exit

Process 8 enter
0000000021
Process 8 exit

Process 9 enter
0000000002
Process 9 exit
