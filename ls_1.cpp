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
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

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



int my_sort(char (*a)[20], int n) {
    for (int i = 0; i < n ;i++) {
        for (int j = 0; j < n - i - 1; j++) {
        //    char r[25], s[25];
        //    strcpy(r, a[j]);
        //    strcpy(s, a[j + 1]);
        //    strcat(r, a[j + 1]);
        //    strcat(s, a[j]);
            if (strcmp(a[j], a[j + 1]) > 0) {
                char t[25];
                strcpy(t, a[j]);
                strcpy(a[j], a[j + 1]);
                strcpy(a[j + 1], t);
            }
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
    char complete_d_name[1005][20];
    int n = 0;
    while ((direntp = readdir(dirp)) != NULL) {
        if (direntp->d_name[0] == '.') continue;
        strcpy(complete_d_name[n++], direntp->d_name);
    }
    cout << "total " << n << " files" << endl;
    my_sort(complete_d_name, n);
    for (int i = 0; i < n; i++) {
        printf("%s ", complete_d_name[i]);
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




