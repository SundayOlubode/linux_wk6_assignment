#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
        pid_t pid = fork();

        if (pid < 0)
        {
                printf("Fork failed");
                exit(1);
        }

        if (pid == 0)
        {
                char *child_args[] = {"ls", "-l", NULL};
                execvp(child_args[0], child_args);
                printf("Exec failed in child");
                exit(1);
        }
        else
        {
                int status;
                char strace_cmd[256];
                snprintf(strace_cmd, sizeof(strace_cmd),
                         "strace -f -o parent_child_syscalls.log -p %d", getpid());

                system(strace_cmd);

                waitpid(pid, &status, 0);

                printf("Parent process completed\n");
        }

        return 0;
}