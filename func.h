#ifndef func_h
#define func_h

//echo 的功能实现
#include "operater.h"
//存储set的字符串数值
struct B_char{
    char flag[30]; //未知数标号
    char contant[30];
}store_str[100];
static int number_str;

//存储变量
struct B_int{
    char flag[30];
    char contant[30];
}store_num[100];
static int number_num;

//%1 这种标号的数据存储
struct C_int{
    int flag;
    char contant[10];
}charater_num[10];

//寻找某个标志的变量
char *find_charater(char *str)
{
    for (int i = 0;i<number_num;i++)
    {
        if (!strcmp(store_num[i].flag,str))
        {
            return store_num[i].contant;
        }
    }
    for (int i = 0;i<number_str;i++)
    {
        if (!strcmp(store_str[i].flag,str))
        {
            return store_str[i].contant;
        }
    }
    return NULL;
}
//echo 的功能设计
void func_echo(int line)
{
    for (int i=1;i<word[line].numcount;i++)
    {
        char ch2[30];
        strcpy(ch2,word[line].mystr[1]);
        if ((ch2[0] == '%') && (ch2[strlen(ch2)-1] == '%' ))
        {
            char *ch1;
            ch1=str_cut(ch2);
            printf("%s",find_charater(ch1));
            continue;
        }
        if ((ch2[0] == '%'))
        {
            int j;
            j = char_tran(ch2[1]);
            printf("%s",charater_num[j].contant);
            continue;
        }
        printf("%s ",word[line].mystr[i]);
    }
    printf("\n");
}
//

//set中的对它是否与条件c匹配的判断 set c
//set 的格式为
//set....
int str_judge(char *str,char *judge)
{
    if (strlen(judge)>strlen(str)) return 0;
    char *judgement; //judgement 为从原来的flag的前端截取的，与judge等长的字符串
    memset(judgement, '\0', sizeof(judgement));
    judgement = strncpy(judgement, str, strlen(judge));
    if (!strcmp(judgement, judge)) return 1;  //为1符合
    return 0;
}

void func_set(int line)
{
    //输出所有已经设定好的变量的判断
    //set
    if (word[line].numcount==1)
    {
        for (int i = 0; i < number_num;i++)
        {
            printf("%s\t\t%s\n",store_num[i].flag,store_num[i].contant);
        }
        for (int i = 0; i < number_str;i++)
        {
            printf("%s\t\t%s\n",store_str[i].flag,store_str[i].contant);
        }
        return;
    }
    //输出与条件符合的设定变量的判断
    //set c
    if (word[line].numcount == 2)
    {
        char *judgestr;//set 给出的判断
        judgestr = word[line].mystr[1];
        for (int i = 0; i < number_num;i++)
        {
            if (str_judge(store_num[i].flag,judgestr))
            {
                printf("%s\t%s\n",store_num[i].flag,store_num[i].contant);
            }
        }
        for (int i = 0; i < number_str;i++)
        {
            if (judgestr == store_str[i].flag)
            {
                printf("%s\t%s\n",store_str[i].flag,store_str[i].contant);
            }
        }
        return;
    }
    //set \p var = 1234
    
    if (!strcmp(word[line].mystr[1],"\\p"))
    {
        strcpy(store_str[number_str].flag, word[line].mystr[2]);
        strcpy(store_str[number_str].contant, word[line].mystr[4]);
        number_str++;
    }
    //set \a var = 1243
    if (!strcmp(word[line].mystr[1],"\\a"))
    {
        strcpy(store_num[number_num].flag, word[line].mystr[2]);
        /*
        int x;
        x=char_tran(word[line].mystr[4]);
        store_num[number_num].contant = x;
         */
        strcpy(store_num[number_num].contant, word[line].mystr[4]);
        number_num++;
    }
}



//执行goto职能
int func_goto(char *str,int line)
{
    memset(ch, '\0', sizeof(ch));
    strcpy(ch, ":");
    strcat(ch,str);

    for (int i = 0;i<count;i++)
    {
        if (!strcmp(word[i].mystr[0],ch)) return i;
    }
    return line;
}

//执行shift职能
void func_shift_ori()
{
    char ch6;
    char *ch7;
    for (int i = 0;i<10;i++)
    {
        memset(charater_num[i].contant, '\0', sizeof(charater_num[i].contant));
        charater_num[i].flag = i;
        ch6 = int_tran(i);
        charater_num[i].contant[0]=ch6;
    }
}
void func_shift(int line)
{
    for (int i = 0;i<9;i++)
    {
        strcpy(charater_num[i].contant, charater_num[i+1].contant);
    }
}
