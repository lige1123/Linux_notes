/*************************************************************************
	> File Name: more_3.c
	> Author:Zhangze 
	> Mail: 
	> Created Time: 六  3/21 19:30:00 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
//#include <termios.h>

#define LENLINE 512

int PAGELINE = 0;

void do_more(FILE *fp);




int main(int argc, char **argv) {
	struct winsize size;
    if (isatty(STDOUT_FILENO) == 0) {
        exit(1);
    }
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) < 0 ) {
        perror("ioctl");
        exit(1);
    }
    PAGELINE = size.ws_row;
    if (PAGELINE >= 3) {
        PAGELINE -= 2;
    } else {
        PAGELINE = 1;
    }
    FILE *fp;
    if (argc == 1)
        do_more(stdin);
    else
        while (--argc) {
            if ((fp = fopen(*++argv, "r")) != NULL) {
                do_more(fp);
            }
        }
    return 0;
}

void do_more(FILE *fp) {
    char line[LENLINE] = {0};
    FILE *cmd = fopen("/dev/tty", "r");
    int num_line = 0, reply, get_cmd(FILE*);
    while (fgets(line, LENLINE, fp)) {
        if (num_line == PAGELINE) {
            reply = get_cmd(cmd);
            if (reply == 0) break;
            num_line -= reply;
        }
        if (fputs(line, stdout) == EOF) {
            perror("fputs");
            exit(1);
        }
        num_line++;
    }

}

int get_cmd(FILE *fp) {
    printf("more:");
    int c;
    while ((c = fgetc(fp)) != EOF){
        if (c == 'q') return 0;
        if (c == ' ') return PAGELINE;
        if (c == '\n') return 1;
    }
    return -1;
}
