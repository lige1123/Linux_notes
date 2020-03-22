#include<stdio.h>
#include<stdlib.h>

#define LINELEN    512
#define    PAGELEN    24

void do_more(FILE *fp);
int see_more(FILE *cmd);

int main(int argc,char *argv[])
{
    if(argc == 1)
        do_more(stdin);
    else
    {
        system( "stty -F /dev/tty cbreak" ); //打开/dev/tty作为输入终端,并且控制属性为不用回车
        while(--argc)
        {
            FILE *fp;
            if( (fp = fopen( *++argv,"r" )) != NULL )
            {
                do_more(fp);
                fclose(fp);
            }
            else
            {
                printf("open %s failed",*argv);
                exit(1);
            }
        }
           system( "stty -F /dev/tty -cbreak" ); //恢复终端属性为需要回车
    }
    
    return 0;
}


void do_more(FILE *fp)
{
    char line[LINELEN];
    int num_of_lines = 0;
    int reply;
    FILE *fp_tty;

    if( (fp_tty = fopen("/dev/tty","r")) == NULL )
    {
        puts("open /dev/tty failed");
        exit(1);
    }
    
    while( fgets(line,LINELEN,fp) )
    {
        if(num_of_lines == PAGELEN)
        {
            reply = see_more(fp_tty);
            if(reply == 0)//键盘输入q退出
                break;
            num_of_lines -= reply;
        }
        if( fputs(line,stdout) == EOF)
            exit(1);
        ++num_of_lines;
    }
}

int see_more(FILE *cmd)
{
    int ch;
    printf("\033[7m more ? \033[m");//反白字体
    
    while( (ch = getc(cmd)) != EOF )
    {
        if(ch == 'q')//退出
            return 0;
        if(ch == '\n')//下一行
            return 1;
        if(ch == ' ')//下一页
            return PAGELEN;
    }
    return 0;
}
