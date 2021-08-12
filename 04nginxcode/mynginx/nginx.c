#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_usr(int signo)
{
  if (signo == SIGUSR1)
  {
    printf("接收到SIGUSR1信号\n");
  }
  else if (signo == SIGUSR2)
  {
    printf("接收到SIGUSR2信号\n");
  }
  else
  {
    printf("收到了没有捕捉到的信号%d\n", signo);
  }
}

int main() 
{
  //调用signal函数，分别注册SIGUSR1和SIGUSR2的信号处理函数
  if (signal(SIGUSR1, sig_usr) == SIG_ERR)
  {
    printf("无法捕捉SIGUSR1信号\n");
  }

  if (signal(SIGUSR2, sig_usr) == SIG_ERR)
  {
    printf("无法捕捉SIGUSR2信号\n");
  }

  printf("hello world~\n");

  while (1)
  {
    sleep(1);
    printf("休息1秒~\n");
  }
  return 0;
}
