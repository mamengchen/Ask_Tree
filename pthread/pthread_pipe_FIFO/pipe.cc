//这是一个父进程通过过管道给子进程发送数据
//子进程读取数据的demo

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    if (pipe(fd) < 0)
    {
        perror("管道创建失败\n");
        exit(0);
    }

    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("创建子进程失败\n");
        exit(1);
    }
    if (pid > 0)
    {
        //父进程运行
        //父进程关闭读端
        close(fd[0]);
        for (int start = 0; start < 100; start++)
        {
            if (write(fd[1], &start, sizeof(int)) != sizeof(int))
            {
                sleep(1);
                perror("写出错\n");
                exit(2);
            }
            printf("父进程写入: %d\n", start);
        }
        close(fd[1]);
        wait(0);    //等待子进程结束
    } else {
        //子进程运行
        //子进程关闭写端
        close(fd[1]);
        while (1){
            int start;
            if (read(fd[0], &start, sizeof(int)) < 0)
            {
                perror("读出错\n");
                exit(3);
            }
            printf("子进程读入: %d\n", start);
            if (start == 99)
            {
                break;
            }
        }      
        close(fd[0]);
    }

    return 0;
}

