#ifndef operater_h
#define operater_h
//删除语句中的空格
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

char ch[50];  //常常使用

char * deleteSpace(char * str)
{
    char * tail = str;
    char * next = str;
    while(*next){ // 两个if可以合并到一块儿，这样写只是为了看着方便
        if(*next != '\n'){ // 查找不是空格的字符
            *tail = *next;
            tail++;
        }
        next++;
    }
    *tail='\0'; // 字符串结束
    return str;
}
void del_char(char a[],char c)
{
    int i,j;
    for(i=0,j=0; *(a+i)!='\0'; i++)
    {
          if(*(a+i)==c)
             continue;
         else
         {
             *(a+j)=*(a+i);
             j++;
         }
     }
     *(a+j)='\0';
}


//存储每行数据的位置
struct A{
    char sentence[100];
    char *mystr[20]; //存储每个字符（按照空格分开）
    int numcount;
}word[100];
static int count;
//所有的字符数据都存储在
//将所在行按照空格拆分

void seperate(char *str,int line)
{
    const char s[2] = " ";
    char *token;
    
    /* 获取第一个子字符串 */
    token = strtok(str, s);
    
    /* 继续获取其他的子字符串 */
    while( token != NULL ) {
        word[line].mystr[word[line].numcount] = token;
        word[line].numcount++;
        token = strtok(NULL, s);
    }
}

int char_tran(char x)
{
    int i = 0;
    i = x - '0';
    return i;
}


//貌似用不上的数字转制
char int_tran(int x)
{
    char i;
    i = '0'+x;
    return i;
}


//规定了寻找的目录的复杂版本
void find_doc2(char *che,char *str) //复杂版本
{
   // if (!strcmp(str,"*.*"))
    DIR    *dir;
    struct    dirent    *ptr;
    dir = opendir(che); ///open the dir
    //const char str[] = "*.*";
    const char ch1 = '.';
    char *retmain;
    char *ret;
    retmain = strchr(str, ch1);
    if (!strcmp(retmain,".*"))
    {
        while((ptr = readdir(dir)) != NULL) ///read the list of this dir
        {
            ret = strchr(ptr->d_name,ch1);
            if (ret==NULL)
            {
                char dircha[100];
                //char *dir2;
                strcpy(dircha,che);
                strcat(dircha, "/");
                strcat(dircha, ptr->d_name);
                find_doc2(dircha,str);
                
            //方法说明 在原来的路径下面加上 /mylife
                //到下一级路径
                //程序编程使用递归的方法
                //没有使用队列的方法
                //printf("d_name: %s\n",ptr->d_name);
                continue;
            }
            if (*ret == '.' && *(ret+1) && (*(ret+1) != '.') )
            {
                printf("r_name: %s\n",ptr->d_name);
                //printf("d_name: %s\n",ptr->d_name);
            }
        }
        return;
    }
    //".txt"
    while((ptr = readdir(dir)) != NULL) ///read the list of this dir
    {
        ret = strchr(ptr->d_name,ch1);
        if (ret==NULL)
        {
            char dircha[100];
            //char *dir2;
            strcpy(dircha,che);
            strcat(dircha, "/");
            strcat(dircha, ptr->d_name);
            find_doc2(dircha,str);
            continue;
        }
        if (!strcmp(ret, retmain))
        {
            printf("r_name: %s\n",ptr->d_name);
            //printf("d_name: %s\n",ptr->d_name);
        }
    }
    return;
    closedir(dir);
    printf("hello");
}

void find_doc1(char *str) //简单版本的寻找文件
{
   // if (!strcmp(str,"*.*"))
    DIR    *dir;
    struct    dirent    *ptr;
    dir = opendir("/Users/sherry/Desktop/文件夹/text/dict"); ///open the dir
    //const char str[] = "*.*";
    const char ch1 = '.';
    char *retmain;
    char *ret;
    retmain = strchr(str, ch1);
    if (!strcmp(retmain,".*"))
    {
        while((ptr = readdir(dir)) != NULL) ///read the list of this dir
        {
            ret = strchr(ptr->d_name,ch1);
            if (ret==NULL)
            {
                char dircha[100];
                //char *dir2;
                strcpy(dircha,"/Users/sherry/Desktop/文件夹/text/dict");
                strcat(dircha, "/");
                strcat(dircha, ptr->d_name);
                find_doc2(dircha,str);
                //printf("d_name: %s\n",ptr->d_name);
                continue;
            }
            if (*ret == '.' && *(ret+1) && (*(ret+1) != '.') )
            {
                printf("r_name: %s\n",ptr->d_name);
                //printf("d_name: %s\n",ptr->d_name);
            }
        }
        return;
    }
    //".txt"
    while((ptr = readdir(dir)) != NULL) ///read the list of this dir
    {
        ret = strchr(ptr->d_name,ch1);
        if (ret==NULL)
        {
            char dircha[100];
            //char *dir2;
            strcpy(dircha,"/Users/sherry/Desktop/文件夹/text/dict");
            strcat(dircha, "/");
            strcat(dircha, ptr->d_name);
            find_doc2(dircha,str);
            continue;
        }
        if (!strcmp(ret, retmain))
        {
            printf("r_name: %s\n",ptr->d_name);
            //printf("d_name: %s\n",ptr->d_name);
        }
    }
    return;
    closedir(dir);
    printf("hello");
}

//关于文件夹的寻找 不需要 部分结构没有删除
void find_doc3()
{
    DIR    *dir;
    struct    dirent    *ptr;
    dir = opendir("/Users/sherry/Desktop/文件夹/text/dict"); ///open the dir
    const char str[] = "*.*";
    const char ch1 = '.';
    char *retmain;
    char *ret;
    retmain = strchr(str, ch1);
    if (!strcmp(retmain,".*"))
    {
        while((ptr = readdir(dir)) != NULL) ///read the list of this dir
        {
            ret = strchr(ptr->d_name,ch1);
            if (ret==NULL)
            {
                printf("d_name: %s\n",ptr->d_name);
            }
        }
        return;
    }
}

//复杂状况下的文件夹遍历

void find_doc4(char *che)
{
    DIR    *dir;
    struct    dirent    *ptr;
    dir = opendir(che); ///open the dir
    const char str[] = "*.*";
    const char ch1 = '.';
    char *retmain;
    char *ret;
    retmain = strchr(str, ch1);
    if (!strcmp(retmain,".*"))
    {
        while((ptr = readdir(dir)) != NULL) ///read the list of this dir
        {
            ret = strchr(ptr->d_name,ch1);
            if (ret==NULL)
            {
                printf("d_name: %s\n",ptr->d_name);
            }
        }
        return;
    }
}
//在默认路径下寻找是否有该文件
int find_doc5(char *che,char *doc)
{
    DIR    *dir;
    struct    dirent    *ptr;
    dir = opendir(che); ///open the dir
    while((ptr = readdir(dir)) != NULL) ///read the list of this dir
    {
        if (!strcmp(ptr->d_name,doc))
        {
            return 1;
        }
    }
    return 0;
}
//是否有该文件
int find_doc6(char *che)
{
    DIR    *dir;
    dir = opendir(che); ///open the dir
    if (dir == NULL) return 0;
    return 1;
}
char str_front(char *str)
{
    return *str;
}
char str_rear(char *str)
{
    return *(str+strlen(str)-1);
}
char *str_cut(char *str)
{
    str = str+1;
    int len;
    len = strlen(str);
    memset(ch, '\0', sizeof(ch));
    strncat(ch,str,(len-1));
    return ch;
}

#endif