### 进程之间互相通信
创建一个子进程和一个父进程，子进程向父进程传递消息

### 孤儿进程和僵尸进程的区别及其产生原因
孤儿进程是父进程提前退出而子进程还在运行，这样子进程就会被转交给init进程，由init进程来回收子进程，防止子进程变成僵尸进程,需要注意的是现代linux系统中，init进程已经被systemd进程取代了，所以这里的init进程变成了systemd进程，孤儿进程会被转交给systemd进程
僵尸进程就是子进程退出后父进程没有调用wait函数来回收子进程

信号会打断sleep函数，当正在sleep时候一个信号被接收到并去执行这个回调函数回来后sleep语句被自动跳过了不管有没有sleep够
总之，信号会使得sleep函数没有sleep够
本质上是sleep函数一旦被中断就不能再继续sleep