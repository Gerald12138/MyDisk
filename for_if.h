#ifndef for_if_h
#define for_if_h
#include "func.h"

//for if
//-l
//-f
//-r
//-d

//bool=1 存在该文件
//if 中是否包含 goto
//如果含有goto返回1
int goto_if(int line)
{
    for (int i = 0;i<word[line].numcount;i++)
    {
        if (!strcmp(word[line].mystr[i],"goto"))
        {
            return 1;
        }
    }
    return 0;
}
//if goto 返回需要返回的label
char * goto_if_find(int line)
{
    int flag = -1;
    for (int i = 0;i<word[line].numcount;i++)
    {
        if (!strcmp(word[line].mystr[i],"goto"))
        {
            flag = i;
            break;
        }
    }
    if (flag == -1 ) return NULL;
    return word[line].mystr[flag+1];
}
//是否看到变量
int flag_if_define(char *str)
{
    char ch2[10];
    strcpy(ch2,str);
    int i;
    i = strlen(ch2);
    if ((ch2[0] == '%') && (ch2[i-1] == '%'))
    {
        char * ch3;
        ch3 = find_charater(str);
        return char_tran(*ch3);
    }
    if (ch2[0] == '%')
    {
        int flag1;
        flag1 = char_tran(ch2[1]);
        char *ch3;
        ch3 = charater_num[flag1].contant;
        return char_tran(*ch3);
    }
    return char_tran(ch2[0]);
    return 0;
}

//if %1 == 3 goto lable
//判断两者是否相等，
//相等返回1，不相等返回0
int flag_if_define2(int line)
{
    int a;
    int b;
    a = flag_if_define(word[line].mystr[1]);
    b = flag_if_define(word[line].mystr[3]);
    if (a == b)
    {
        return 1;
    }
    return 0;
}
//为if语句量身定做的doc寻找
//只在本文件夹中寻找

//若缺省，在指定目录下寻找
int find_if_doc(int line)
{
    char ch2[50];
    strcpy(ch2,word[line].mystr[2]);
    char *ret;
    ret = strchr(ch2,'/');
    if (ret == NULL)
    {
        return find_doc5("/Users/sherry/Desktop/文件夹/text/dict", ch2);
    }
    return find_doc6(ch2);
}
void echo_if(int line,int n)
{
    char ch2[50];
    strcpy(ch2, word[line].mystr[n]);
    int len;
    len = strlen(ch2);
    if (ch2[len-1]==')') ch2[len-1] = '\0';
    printf("%s\n",ch2);
}

void func_if_exist(int line)
{
    if (find_if_doc(line)==1)
    {
        echo_if(line, 4);
        return;
    }
    else
    {
        if (word[line].numcount>5)
        {
            echo_if(line, 7);
        }
    }
    return;
}
//判断两个字符串是否相等
//暂时为不包含变量的简单版本
void func_if_char(int line)
{
    if (!strcmp(word[line].mystr[1],word[line].mystr[3]))
    {
        echo_if(line, 5);
        return;
    }
    else
    {
        if (word[line].numcount>6)
        {
            echo_if(line, 8);
        }
    }
    return;
}
//为if goto 量身打造的
int func_if_char1(int line)
{
    char *str1;
    str1 = goto_if_find(line);
    return func_goto(str1, line);
    //不涉及位置，可以直接用
}
void func_if_equal(int line)
{
    if (!strcmp(word[line].mystr[1],word[line].mystr[3]))
    {
        echo_if(line, 5);
        return;
    }
    else
    {
        if (word[line].numcount>6)
        {
            echo_if(line, 8);
        }
    }
    return;
}
void func_if_define(int line)
{
    char * ch2;
    ch2 = find_charater(word[line].mystr[2]);
    if (ch2 != NULL)
    {
        echo_if(line, 4);
        return;
    }
    else
    {
        if (word[line].numcount>6)
        {
            echo_if(line, 7);
        }
    }
    return;
}
//专门为if 设计的echo
// n 反应位置

//1、判断驱动器、文件或文件夹是否存在，用 if exist 语句；
//2、判断某两个字符串是否相等，用 if "字符串1"=="字符串2" 语句；
//3、判断某两个数值是否相等，用 if 数值1 equ 数值2 语句；
//4、判断某个变量是否已经被赋值，用 if defined str 语句；
//1、if exist d:\test.txt (echo D盘下有test.txt存在) else (echo D盘下不存在test.txt)
//2、if "abc" == "xyz" (echo 字符串abc等于字符串xyz) else (echo 字符串abc不等于字符串xyz)
//3、if 1 equ 2 (echo 1等于2) else (echo 1不等于2)
//4、if defined str (echo 变量str已经被赋值，其值为%str%) else (echo 变量str的值为空)
void func_if(int line)
{
    char str[30];
    strcpy(str, word[line].mystr[1]);
    if (!strcmp(str, "defined"))
    {
        func_if_define(line);
        return;
    }
    if (!strcmp(str, "exist"))
    {
        func_if_exist(line);
        return;
    }
    strcpy(str, word[line].mystr[2]);
    if (!strcmp(str, "equ"))
    {
        func_if_equal(line);
        return;
    }
    if (!strcmp(str, "=="))
    {
        func_if_char(line);
        return;
    }
}
//if " " goto
//if %1 == 3 goto lable
int func_if_goto(int line)
{
    char str[30];
    int flag_flag;
    //标注是否同意goto
    strcpy(str, word[line].mystr[2]);
    if (!strcmp(str, "not"))
    {
        flag_flag=flag_if_define2(line);
    }
    if (flag_flag==0)
    {
        return func_if_char1(line);
    }
    return line;
}
#endif /* for_if_h */
