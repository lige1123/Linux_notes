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
#include<sys/stat.h>
#include<unistd.h>
#include<termios.h>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<pwd.h>
#include<ctime>
#include<grp.h>
using namespace std;

void do_ls(char[]);
void do_ls_1(char[]);
int init_ioctl(int *, int *);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        do_ls(".");
    } else {
        while(--argc) {
            int FLAG = 0;
            if (strcmp(*argv, "-a") == 0) FLAG = 1;
            if (strcmp(*argv, "-l") == 0) FLAG = 2;
            printf("%s: \n", *++argv);
            if (FLAG == 1) do_ls(*argv);
            if (FLAG == 2) do_ls_1(*argv);
        }
    }
    return 0;
}


int my_sort(char (*a)[20], int n) {
    for (int i = 0; i < n ;i++) {
        for (int j = 0; j < n - i - 1; j++) {
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


int OUTPUTcolor_file_Name(char *a, int FLAG) {
    int m = strlen(a);
    switch(FLAG) {
        case 1 :
            printf("\033[1;0m%s\033[0m", a);
            break;
        case 2 :
            printf("\033[0;34m%s\033[0m", a);
            break;
        case 3 :
            printf("\033[0;33m%s\033[0m", a);
            break ;
        case 4 :
            printf("\033[0;31m%s\033[0m", a);
            break;
        case 5 :
            printf("\033[0;32m%s\033[0m", a);
            break;
        case 6 :
            printf("\033[0;34m%s\033[0m", a);
            break;
        case 7 :
            printf("\033[0;29m%s\033[0m", a);
            break;
        case 8 :
            printf("\033[0;32m%s\033[0m", a);
            break;
        default :
            //printf("\033[1;0m %s \033[0m", a);
            printf("%s", a);
    }
    return m;
}




int init_ioctl(int *col, int *row) {
    struct winsize size;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
    *col = size.ws_col;
    *row = size.ws_row;
    return 0;
}

char *Get_uid(uid_t uid) {
    struct passwd *p;
    p = getpwuid(uid);
    return p->pw_name;
}

char *Get_gid(gid_t gid) {
    struct group *g;
    g = getgrgid(gid);
    return g->gr_name;
}




char *Get_mode(mode_t mode, int *f) {
    char s[15];
    strcpy(s, "----------.");
    if (S_ISDIR(mode)) {
        s[0] = 'd';
        *f = 1;
    } else if (S_ISLNK(mode)) {
        s[0] = 'l';
        *f = 5;
    } else if (S_ISCHR(mode)) {
        s[0] = 'c';
        *f = 2;
    } else if (S_ISBLK(mode)) {
        s[0] = 'b';
        *f = 3;
    } else if (S_ISFIFO(mode)) {
        s[0] = 'i';
        *f= 4;
    } else if (S_ISREG(mode)) {
        s[0] = 'r';
        *f = 6;
    } else if (S_ISBLK(mode)) {
        s[0] = 'b';
        *f = 7;
    }
    if (mode & S_IRUSR) s[1] = 'r';
    if (mode & S_IWUSR) s[2] = 'w';
    if (mode & S_IXUSR) s[3] = 'x';
    if (mode & S_IRGRP) s[4] = 'r';
    if (mode & S_IWGRP) s[5] = 'w';
    if (mode & S_IXGRP) s[6] = 'x';
    if (mode & S_IROTH) s[7] = 'r';
    if (mode & S_IWOTH) s[8] = 'w';
    if (mode & S_IXOTH) {
        s[9] = 'x';
        *f = 8;
    }
    return s;
}


void do_ls_1(char dirname[]) {
    DIR *dirp;
    struct dirent *direntp;
    if ((dirp = opendir(dirname)) == NULL) {
        perror("opendir");
        return ;
    }
    char complete_d_name[1005][20];
    int n = 0, Blanket_MAX = 0;
    while ((direntp = readdir(dirp)) != NULL) {
        if (direntp->d_name == ".") continue;
        int Blanket = sprintf(complete_d_name[n++], "%s", direntp->d_name);
        if (Blanket_MAX < Blanket) Blanket_MAX = Blanket;
    }
    int COL, ROW;
    init_ioctl(&COL, &ROW);
    cout << "total " << n << " files" << endl;
    my_sort(complete_d_name, n);
    for (int i = 0; i < n; i++) {
        char complete_D_name[200];
        int ans = sprintf(complete_D_name, "%s",dirname);
        sprintf(complete_D_name + ans, "/%s", complete_d_name[i]);
        struct stat info;
        stat(complete_D_name, &info);
        int Flag = 0;
        printf("%10s ", Get_mode(info.st_mode, &Flag));
        printf("%d ", info.st_nlink);
        printf("%7s ", Get_uid(info.st_uid));
        printf("%7s ", Get_gid(info.st_gid));
        printf("%5ld ", info.st_size);
        printf("%.15s", 8 + ctime(&info.st_mtime));
        cout << "  ";
        OUTPUTcolor_file_Name(complete_d_name[i], Flag);
        //cout << complete_d_name[i];
        cout << endl;
    }
    closedir(dirp);
}

void do_ls(char dirname[]) {
    DIR *dirp;
    struct dirent *direntp;
    if ((dirp = opendir(dirname)) == NULL) {
        perror("opendir");
        return ;
    }
    char complete_d_name[1005][20];
    int n = 0, Blanket_MAX = 0;
    while ((direntp = readdir(dirp)) != NULL) {
        int Blanket = sprintf(complete_d_name[n++], "%s", direntp->d_name);
        if (Blanket_MAX < Blanket) Blanket_MAX = Blanket;
    }
    int COL, ROW;
    init_ioctl(&COL, &ROW);
    cout << "total " << n << " files" << endl;
    my_sort(complete_d_name, n);
    int COL_NUM = COL / Blanket_MAX;
    int ROM_NUM = n / COL_NUM;
    int ROM_MODNUM = n % COL_NUM;
    if(ROM_MODNUM > 0) ROM_NUM++;
    COL_NUM = n / ROM_NUM;
    int COL_MODNUM = n % ROM_NUM;
    for (int i = 0; i < ROM_NUM; i++) {
        int flag = 0;
        if((COL_MODNUM--) > 0) {
            flag = 1;
        }
        for (int k = 0; k < COL_NUM + flag; k++) {
            struct stat info;
            stat(complete_d_name[k * ROM_NUM + i], &info);
            int Flag = 0;
            Get_mode(info.st_mode, &Flag);
            int RBlanket = OUTPUTcolor_file_Name(complete_d_name[k * ROM_NUM + i], Flag);
            //int RBlanket = printf("%s", complete_d_name[k * ROM_NUM + i]);
            for (int j = RBlanket; j < (Blanket_MAX + 1); j++) {
                if (k == COL_NUM) break;
                cout << " ";
            }
        }
        cout << endl;
    }
    closedir(dirp);
}

