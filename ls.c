/*************************************************************************
	> File Name: ls.c
	> Author: 
	> Mail: 
	> Created Time: 2020年03月15日 星期日 19时02分09秒
 ************************************************************************/

#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<termios.h>

void do_ls(char[]);
int init_ioctl(int *, int *);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        do_ls(".");
    } else {
        while(--argc) {
            printf("%s: \n", *++argv);
            do_ls(*argv);
        }
    }
    return 0;
}


void do_ls(char dirname[]) {
    DIR *dirp;
    struct dirent *direntp;
    if ((dirp = opendir(dirname)) == NULL) {
        perror("opendir");
        return ;
    }
    while ((direntp = readdir(dirp)) != NULL) {
        printf("%s \n", direntp->d_name);
    }
    closedir(dirp);
    printf("\n");
}


int init_ioctl(int *col, int *row) {
    struct winsize size;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
    *col = size.ws_col;
    *row = size.ws_row;
    return 0;
}




