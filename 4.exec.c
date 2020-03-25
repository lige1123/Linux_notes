/*************************************************************************
	> File Name: 3.exec.c
	> Author: zhangze
	> Mail: 
	> Created Time: 2020年03月26日 星期四 01时07分32秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int pid, ppid, pppid;
    for (int i = 0; i < 3; i++) {
        if ((pid = fork()) < 0) {
            perror("fork1");
        } else if (pid == 0) {
            if (i == 0) execl("/usr/bin/vim", "vim", "t.c", NULL);
            else if (i == 1) execl("/usr/bin/gcc", "gcc", "t.c", "-o", "b.out", NULL);
            else if (i == 2) execl("/home/zhangze/LS/b.out", "./b.out", NULL);
            break;
        }
        wait(NULL);
    }
    exit(1);
   // wait(NULL);
    return 0;
}

                //if((execl("/home/zhangze/LS/b.out", "./b.out", NULL) < 0)) {
                 //   perror("b.out");

