/*************************************************************************
	> File Name: more.c
	> Author: 
	> Mail: 
	> Created Time: 2020年03月21日 星期六 19时30分22秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/ioctl.h>

#define PAGELINE 10
#define LENLINE 512

void do_more(FILE *fp);


int main(int argc, int **argv) {
    struct winsize size;
    if (isatty(STDOUT_FILENO) == 0) {
        exit(1);
    }
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) < 0 ) {
        perror("ioctl");
        exit(1);
    }
    printf("window size row = %d, col = %d\n", size.ws_row, size.ws_col); 
    FILE *fp;
    if (argc == 1) do_more(stdin);
    //printf("Usage : %s [filename | stdin]\n", argv[0]);
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
            reply = get_cmd();
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
    printf("more :");
    int c;
    while ((c = getchar(fp)) != EOF) {
        if (c == 'q') return 0;
        if (c == ' ') return PAGELINE;
        if (c == '\n') return 1;
    }
    return -1;
}


