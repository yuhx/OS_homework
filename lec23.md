#键盘输入

##执行过程
```
中断处理 trap_dispatch()
	-> 获取字符 cons_getc() -> 从键盘获取字符 kbd_intr() -> 使用键盘驱动获取字符 cons_intr()
	-> 缓存字符 dev_stdin_write() -> 唤醒等待线程 wakeup_queue()
```

##时间开销
```
由于键盘输入数据量有限，因此时间开销主要是花在中断处理上。
```