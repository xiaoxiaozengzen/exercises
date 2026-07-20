# Overview

linux上查看进程线程的资源消耗

## 1.top

```
top -H -p <pid>
# -H 查看线程
# -p 指定进程
# 交互：按1可以切换每个cpu的资源消耗
#       按H可以切换线程/进程的视图

# top - 20:25:47 up 66 days, 17:41,  2 users,  load average: 7.23, 6.82, 6.14
# Threads:   3 total,   2 running,   1 sleeping,   0 stopped,   0 zombie
# %Cpu0  : 98.0 us,  2.0 sy,  0.0 ni,  0.0 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
# us：user，用户态消耗的CPU(普通优先级用户进程，nice=0)
# sy：system，内核态消耗的CPU
# ni：nice，被nice调低优先级(nice>0)的用户进程消耗的CPU
# id：idle，CPU空闲，且没有等IO
# wa：iowait，CPU空闲，在等待IO
# hi：hardware irq，处理硬中断(网卡收包，磁盘完成)
# si：software irq，处理软中断
# st：steal，被同宿主机的其他虚拟机偷走的时间，物理机永远为0
```

## 2.htop

```
htop -p <pid>
# F2设置里勾选 "show custom thread names"
# 按H显示/隐藏用户线程
# 按t树形视图，进程/线程一目了然
```

## 3.ps

```
ps -T -p <pid> -o pid,tid,comm,pcpu,pmem,rss,vsz,stat
# -T 显示所有线程
# tid=线程id，comm=线程名
# pcpu/pmem = CPU/内存百分比
```

## 4.pidstat

```
pidstat -t -p <pid> 1 # 每秒一次，-t显示线程
pidstat -t -r -p <pid> 1 #只看内存
pidstat -t -u -p <pid> 1 #只看cpu，默认
```
