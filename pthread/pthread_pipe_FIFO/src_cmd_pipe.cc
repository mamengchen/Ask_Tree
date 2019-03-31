#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

char *cmd1[3] = {"/bin/cat", "/etc/passwd", NULL};
char *cmd2[3] = {"/bin/grep", "root", NULL};

int main(void)
{
    int fd[2];
    if (pipe(fd) < 0)
    {
        printf("管道创建失败\n");
    }

    pid_t pid;
    int i = 0;
    for (; i < 2; i++) 
    {
        if ((pid = fork()) < 0)
        {
            printf("子进程创建失败\n");
        } else if (pid > 0) {
            //父进程执行
            if (i == 1)
            {
                close(fd[0]);
                close(fd[1]);
                wait(0);
                wait(0);
            }
        } else {
            //子进程执行
            if (i == 0)
            {
                //关闭读端
                close(fd[0]);
                
                /*
                 * 将标准输出重定向到管道的写端
                 * (下面命令执行的结果会写入到管道中
                 * 而不是输出到屏幕)
                 * 
                 */
                if (dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO)
                {
                    printf("写端重定向失败\n");
                }
                close(fd[1]);

                //调用exec函数执行cat命令
                if (execvp(cmd1[0], cmd1) < 0)
                {
                    perror("cat替换子进程失败\n");
                    exit(1);
                }

                break;
            }

            if (i == 1)
            {
                //关闭写端
                close(fd[1]);
                if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
                {
                    printf("读端重定向失败\n");
                }
                close(fd[0]);

                //调用exec函数执行grep命令
                if (execvp(cmd2[0], cmd2) < 0)
                {
                    perror("grep替换子进程失败\n");
                    exit(2);
                }

                break;
            }
        }
    }
    return 0;
}
