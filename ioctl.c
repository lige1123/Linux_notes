/*************************************************************************
	> File Name: ioctl.c
	> Author: 
	> Mail: 
	> Created Time: 2020年03月17日 星期二 09时19分55秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<termios.h>


int ioctl(int *col, int *row) {
    struct winsize size;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
    *col = size.ws_col;
    *row = size.ws_row;
    return 0;
}





