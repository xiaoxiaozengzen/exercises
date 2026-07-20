# Overview

linux上查看进程线程的资源消耗

## 1.top

```
top -H -p <pid>
# -H 查看线程
# -p 指定进程
# 交互：按1可以切换每个cpu的资源消耗
#       按H可以切换线程/进程的视图
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
