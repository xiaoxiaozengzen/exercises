#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include <chrono>
#include <thread>
#include <iostream>

/**
 * 对于应用程序自行处理的信号来说，信号的生命周期要经过信号的安装登记、信号集操作、信号的发送和信号的处理四个阶段。
 * 1）信号的安装登记指的是在应用程序中，安装对此信号的处理方法。
 * 2）信号集操作的作用是用于对指定的一个或多个信号进行信号屏蔽。
 * 3）信号的发送指的是发送信号，可以通过硬件（如在终端上按下Ctrl-C）发送的信号和软件（如通过kill函数）发送的信号。
 * 4）信号的处理指的是操作系统对接收信号进程的处理，处理方法是先检查信号集操作函数是否对此信号进行屏蔽，如果没有屏蔽，操作系统将按信号安装函数中登记注册的处理函数完成对此进程的处理。
 *
 */

/**
 * 实时信号和非实时信号的区别：
 * 1.kill -l显示的信号列表中：1-31号信号为非实时信号(非可靠)，34-64号信号为实时信号(可靠)
 * 
 * 非实时信号缺点：
 * 1.阻塞信号可能会丢失。当一个信号阻塞时，这个信号即使多次发送给进程，也被执行一次信号句柄。
 * 2.信号交付没有携带与信号有关信息。接受到信号的进程无法区分同种信号的不同情况，也不知道信号从何而来。
 * 3. 信号的交付没有优先级。当有多个信号悬挂与一个进程时，交付的顺序不确定
 * 
 * 实时信号相比非实时信号的优点：
 * 1.实时信号和标准信号不一样，他没有明确的含义，而是由使用者自己来决定如何使用。
 * 2.进程可以接受多个同样的实时信号，而标准信号不能，在标准信号没有得到处理的时候，多个标准信号会被合为一个。
 * 3.实时信号使用sigqueue发送的时候，可以携带附加的数据(int或者pointer)
 * 4.实时信号有时间顺序的概念，所以同样的实时信号会按次序被处理。
 * 5.实时信号有优先级的概念，数值越小优先级越高，数值越大优先级越低。
 */

/************************************1.1.信号安装*************************************************/
/**
 * void (*signal(int sig, void (*func)(int)))(int);
 * sig: 信号编号
 * func: 信号处理函数指针
 * 返回值: 旧的信号处理函数指针
 * 
 * func默认有三种处理方式：
 * 1. SIG_DFL: 默认处理方式
 * 2. SIG_IGN: 忽略该信号
 * 3. 使用func函数处理该信号
 */
void signal_handler(int signo) { printf("signal_handler: %d\n", signo); }
void signal_example() {
  signal(SIGABRT, signal_handler);
  signal(SIGALRM, signal_handler);
}

/************************************1.2.信号安装*************************************************/
// int sigaction(int sig, const struct sigaction *act, struct sigaction *oldact);
// sig: 信号编号
// act: 指向新的信号处理动作的指针。如果为 NULL，则不修改当前的信号处理动作。
// oldact: 指向用于保存旧的信号处理动作的指针。如果为 NULL，则不保存旧的信号处理动作。

// struct sigaction {
//     void (*sa_handler)(int);           // 信号处理函数指针，一般用来处理非实时信号(当然也可以处理实时信号)
//     void (*sa_sigaction)(int, siginfo_t *, void *); // 拓展信号处理函数指针，传递信号值以及其他信息，一般用来处理实时信号
//                                                     // sa_sigaction和sa_handler互斥，不能同时使用
//                                                     // 且只有sa_flags设置了SA_SIGINFO时，sa_sigaction才会被使能
//     sigset_t sa_mask;                  // 在处理该信号时要阻塞的信号集
//     int sa_flags;                      // 修改信号行为的选项
//     void (*sa_restorer)(void);         // 恢复函数，已废弃
// };
// sa_mask字段说明了一个信号集，指定在信号处理程序执行过程中，哪些信号应当被阻塞。缺省情况下当前信号本身被阻塞，防止信号的嵌套发送，
// sa_flags字段说明了信号处理的行为，列举了一些值，这些值可以通过or进行使用：
//      0 信号处理行为是默认的，当前信号处理函数执行期间会被阻塞，防止嵌套递送
//      #define	SA_NOCLDSTOP  1		 /* Don't send SIGCHLD when children stop.  */
//      #define SA_NOCLDWAIT  2		 /* Don't create zombie on child death.  */
//      #define SA_SIGINFO    4		 /* Invoke signal-catching function with three arguments instead of one.  */

// 不同平台siginfo_t结构体定义不同
// siginfo_t {
//   int      si_signo;     /* Signal number */
//   int      si_errno;     /* An errno value */
//   int      si_code;      /* Signal code */
//   int      si_trapno;    /* Trap number that caused hardware-generated signal(unused on most architectures) */
//   pid_t    si_pid;       /* Sending process ID */
//   uid_t    si_uid;       /* Real user ID of sending process */
//   int      si_status;    /* Exit value or signal */
//   clock_t  si_utime;     /* User time consumed */
//   clock_t  si_stime;     /* System time consumed */
//   union sigval si_value; /* Signal value */
//   int      si_int;       /* POSIX.1b signal */
//   void    *si_ptr;       /* POSIX.1b signal */
//   int      si_overrun;   /* Timer overrun count; POSIX.1b timers */
//   int      si_timerid;   /* Timer ID; POSIX.1b timers */
//   void    *si_addr;      /* Memory location which caused fault */
//   long     si_band;      /* Band event (was int in glibc 2.3.2 and earlier) */
//   int      si_fd;        /* File descriptor */
//   short    si_addr_lsb;  /* Least significant bit of address (since Linux 2.6.32) */
//   void    *si_lower;     /* Lower bound when address violation occurred (since Linux 3.19) */
//   void    *si_upper;     /* Upper bound when address violation occurred (since Linux 3.19) */
//   int      si_pkey;      /* Protection key on PTE that caused fault (since Linux 4.6) */
//   void    *si_call_addr; /* Address of system call instruction (since Linux 3.5) */
//   int      si_syscall;   /* Number of attempted system call (since Linux 3.5) */
//   unsigned int si_arch;  /* Architecture of attempted system call (since Linux 3.5) */
// } 
void sigaction_example() {
  struct sigaction act;
  act.sa_handler = signal_handler;
  act.sa_flags = 0;
  sigaction(SIGABRT, &act, NULL);
  sigaction(SIGALRM, &act, NULL);
  sigaction(SIGINT, &act, NULL);
}

/************************************2.信号集操作*************************************************/
/**
 * int sigemptyset(sigset_t *set); // 将某个信号集清 0: 成功:0;失败:-1
 * int sigfillset(sigset_t *set); // 将某个信号集置 1： 成功:0;失败:-1
 * int sigaddset(sigset_t *set, int signum); // 将某个信号加入信号集，将对应编号置1; 成功:0;失败:-1
 * int sigdelset(sigset_t *set, int signum); // 将某个信号清出信号集，将对应编号置0
 * int sigismember(const sigset_t *set, intsignum); // 判断某个信号是否在信号集中: 失败:-1，返回值:在集合:1;不在:0;
 * int sigprocmask(int how, const sigset_t *set, sigset_t *oldset); // 用来屏蔽信号、解除屏蔽也使用该函数。其本质,读取或修改进程的信号屏蔽字
 * int sigpending(sigset_t *set); // 获取未决信号集
 * int sigsuspend(const sigset_t *mask); // 临时解除对信号的屏蔽，然后进入休眠状态，直到捕捉到一个信号
 * int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact); // 信号处理函数的设置和获取
 * int sigwait(const sigset_t *set, int *signo); // 用于等待一个信号的产生
 * int sigwaitinfo(const sigset_t *set, siginfo_t *info); // 用于等待一个信号的产生
 * int sigtimedwait(const sigset_t, *set, siginfo_t *info, const struct timespec *timeout); // 用于等待一个信号的产生
 * int sigqueue(pid_t pid, int sig, const union sigval value); // 向指定进程发送一个信号
 */
void sigset_example() {
  sigset_t set;

  // 初始化信号集为空
  sigemptyset(&set);

  // 将SIGABRT信号添加到信号集中
  sigaddset(&set, SIGABRT);
  // 将SIGALRM信号添加到信号集中
  sigaddset(&set, SIGALRM);

  // SIG_BLOCK: 将set中的信号添加到进程的信号屏蔽字中
  // SIG_UNBLOCK: 将set中的信号从进程的信号屏蔽字中删除，解除阻塞
  // SIG_SETMASK: 将进程的信号屏蔽字设置为set
  sigprocmask(SIG_BLOCK, &set, NULL);  // 阻塞信号集中的信号

  // 发送SIGABRT信号
  raise(SIGABRT);  

  sigset_t ret_set;
  sigemptyset(&ret_set);
  // 获取未决信号集
  sigpending(&ret_set);
  if (sigismember(&ret_set, SIGABRT)) {
    printf("SIGABRT is pending\n");
  }
  if (sigismember(&ret_set, SIGALRM)) {
    printf("SIGALRM is pending\n");
  }

  // 发送SIGINT信号
  raise(SIGINT);
  std::this_thread::sleep_for(std::chrono::seconds(1)); 

  // 解除对信号集中的信号阻塞，当前进程可以接收到之前pending的信号
  sigprocmask(SIG_UNBLOCK, &set, NULL);
}

/************************************3.信号生成*************************************************/

// kill()：用于向进程或进程组发送信号；
// sigqueue()：只能向一个进程发送信号，不能像进程组发送信号；主要针对实时信号提出，与sigaction()组合使用，当然也支持非实时信号的发送；
// alarm()：用于调用进程指定时间后发出SIGALARM信号；
// setitimer()：设置定时器，计时达到后给进程发送SIGALRM信号，功能比alarm更强大；
// abort()：向进程发送SIGABORT信号，默认进程会异常退出。
// raise()：用于向进程自身发送信号
void system_call(int option) {
  if (option == 1) {
    printf("kill\n");
    kill(getpid(), SIGABRT);
  } else if (option == 2) {
    printf("raise\n");
    raise(SIGABRT);
  } else if (option == 3) {
    // 需要配合sigaction使用
    printf("sigqueue\n");
    sigqueue(getpid(), SIGABRT, {0});
  } else if (option == 4) {
    // 1）一个进程只能有一个闹钟时间，如果在调用alarm之前已设置过闹钟时间，则任何以前的闹钟时间都被新设置的闹钟时间所代替；
    // 2）经过指定的秒数后，信号由内核产生。
    printf("alarm\n");
    int ret = alarm(2);
    printf("alarm ret: %d\n", ret);
  } else if (option == 5) {
    // struct itimerval
    // {
    //     struct timeval it_interval;    //后续定时器时间间隔
    //     struct timeval it_value;    //当前定时间多久后开始执行
    // };
    struct itimerval itv;
    itv.it_interval.tv_sec = 1;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 1;
    itv.it_value.tv_usec = 0;
    printf("setitimer\n");
    /**
     * @brief Construct a new setitimer object
     * @param which
     *          ITIMER_REAL: :以实际时间递减, 计时器到期时，内核向进程发送SIGALRM信号
     *          ITIMER_VIRTUAL:
     * 以进程在用户模式CPU消耗的时间递减，计时器到期时，内核向进程发送SIGVTALRM信号 ITIMER_PROF:
     * :以进程在用户模式执行时间和进程背后系统的执行时间, 计时器到期时，内核向进程发送SIGPROF信号
     *
     */
    setitimer(ITIMER_REAL, &itv, NULL);
  } else if (option == 6) {
    printf("abort\n");
    abort();
  } else {
    return;
  }
}

/**
 * 多线程中信号处理是未定义行为，在多线程的场景下，信号处理可能在任何一个线程中运行，甚至是主线程
 */
void multi_thread() {

  sigset_t set;
  sigemptyset(&set);
  struct sigaction act;
  act.sa_handler = signal_handler;
  act.sa_flags = 0;

  std::thread t1([&]() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    printf("thread 1\n");

    sigaddset(&set, SIGABRT);
    sigaction(SIGABRT, &act, NULL);

    while(true) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  });

  std::thread t2([&]() {
    printf("thread 2\n");

    while(true) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }    
  });

  raise(SIGABRT);

  t1.join();
  t2.join();
}

void signal_habdler_info(int signo, siginfo_t *info, void *context) {
  printf("getpid: %d\n", getpid());
  printf("getid: %d\n", gettid());
  printf("signal_habdler_info: %d\n", signo);
  printf("signal_habdler_info.si_signo: %d\n", info->si_signo);
  printf("signal_habdler_info.si_errno: %d\n", info->si_errno);
  printf("signal_habdler_info.si_code: %d\n", info->si_code);
  printf("signal_habdler_info.si_pid: %d\n", info->si_pid);
  printf("signal_habdler_info.si_uid: %d\n", info->si_uid);
  printf("signal_habdler_info.si_status: %d\n", info->si_status);
  printf("signal_habdler_info.si_utime: %ld\n", info->si_utime);
  printf("signal_habdler_info.si_stime: %ld\n", info->si_stime);
}
void SigInfoTest() {
  sigset_t set;
  sigemptyset(&set);
  struct sigaction act;
  act.sa_sigaction = signal_habdler_info;
  act.sa_flags = SA_SIGINFO; // 需要设置SA_SIGINFO才能使用sa_sigaction
  sigaction(SIGABRT, &act, NULL);

  sigqueue(getpid(), SIGABRT, {10});
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <option>\n", argv[0]);
    return -1;
  }

  int option = atoi(argv[1]);

  std::cerr << "====================== sigaction_example ======================" << std::endl;
  sigaction_example();
  std::cerr << "====================== signal_example ======================" << std::endl;
  sigset_example();
  std::cerr << "====================== system_call ======================" << std::endl;
  system_call(option);
  std::cerr << "====================== SigInfoTest ======================" << std::endl;
  SigInfoTest();
  std::this_thread::sleep_for(std::chrono::seconds(10));
}