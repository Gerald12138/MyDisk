#ifndef for_for_h
#define for_for_h
#include "operater.h"
#include "func.h"

//for " " /d %%i in (？？？) do echo a;
//可以缺省
//对文件夹的寻找
void func_for_d(int line)
{
    char ch22[30];
    strcpy(ch22,word[line].mystr[1]);
    char *ch11;
    char *ch33;
    if (ch22[0] == '/')
    {
        ch11 = str_cut(word[line].mystr[4]);
        find_doc3();
    }
    else
    {
        ch33=str_cut(ch22);
        find_doc4(ch33);
    }
}
//for /d %%i in
//对文件的寻找 需要到下一级
void func_for_r(int line)
{
    char ch22[30];
    strcpy(ch22,word[line].mystr[1]);
    char *ch11;
    char *ch33;
    if (ch22[0] == '/')
    {
        ch11 = str_cut(word[line].mystr[4]);
        find_doc1(ch11);
    }
    else
    {
        ch33=str_cut(ch22);
        ch11 = str_cut(word[line].mystr[5]);
        find_doc2(ch33, ch22);
    }
}
//for %%i in (a,b,c) do echo %%i
//直接在后面跟变量
void func_for_i(int line)
{
    char  *f;
    f=word[line].mystr[2];
    f = f+2;
    char istr;
    istr = *f;
    char strspilit[30];
    strcpy(strspilit, str_cut(word[line].mystr[3]));
    if ( !strcmp(word[line].mystr[5],"echo"))
    {
        for (int i = 0;i<strlen(strspilit);i++)
        {
            if (strspilit[i]==',')
            {
                printf("\n");
                continue;
            }
            printf("%c",strspilit[i]);
        }
    }
    printf("\n");
}
//专门为 /l配置的分配函数
int tran_tria(char *str)
{
    char ch2;
    ch2 = *(str+1);
    return char_tran(ch2);
}
int tran_trib(char *str)
{
    char ch2;
    ch2 = *(str+3);
    return char_tran(ch2);
}
int tran_tric(char *str)
{
    char ch2;
    ch2 = *(str+5);
    return char_tran(ch2);
}
//for /L %%i in (1,1,5) do md d:\aa %%i
//建立文件夹
//这里使用echo
//for /l %%i in (1,1,5) do echo %%i;
void func_for_l(int line)
{
    int a,b,c;
    a = tran_tria(word[line].mystr[4]);
    b = tran_trib(word[line].mystr[4]);
    c = tran_tric(word[line].mystr[4]);
    for (int i = a;i<=c;i=i+b)
    {
        printf("%d\t",i);
    }
    printf("\n");
    return;
}
//for /f %c in (abc.txt) do @echo %c
//缺省条件下的判断
//自动按照空格判断
void func_for_f1(int line,char *doc)
{
    char buff[255];
    FILE *filein = NULL;
    filein = fopen(doc,"r");
    if (filein==NULL) return;
    fscanf(filein, "%s", buff);
    do
    {
        
        printf("%s\n",buff);
        fgets(buff,255,(FILE*)filein);
        fscanf(filein, "%s", buff);
    }while (!feof(filein));
    
    fclose(filein);
    return;
}
//

int tran_tri(char *str,int n)
{
    char ch2;
    ch2 = *(str+n);
    int i;
    i = char_tran(ch2);
    return i;
}
//for /f “skip=1 tokens=1,4 delims= ” %c in (d:\abc.txt) do @echo %c %d
//delims为分割字符
void func_for_f2(int line,char *doc)
{
    int skip;
    skip=tran_tri(word[line].mystr[3], 7);
    int token[5];
    int num;
    num = strlen(word[line].mystr[3]);
    num = num/2-3;
    for (int i = 0 ;i<num;i++)
    {
        
        token[i]=tran_tri(word[line].mystr[3], (7+2*i));
    }
    //取出 delim delim为分割方式
    char delim[2];
    char delimain[10];
    strcpy(delimain, word[line].mystr[4]);
    if (strlen(delimain)==7)
    {
        //delim = ' ';
        strcpy(delim," ");
        doc = str_cut(word[line].mystr[8]);
    }
    else{
        //delim=*(word[line].mystr[4]+7);
        char ch5;
        ch5=*(word[line].mystr[4]+7);
        strcpy(delim,ch5);
    }
    
    //验证性的代码段
    //printf("%c\n",delim);
    
    //扫描到哪个token[]
    int tokens_flag;
    //扫描到哪个部分
    int tokens_num;
    
    FILE *filein = NULL;
    char buff[664];
    count = 0;
    filein = fopen(doc,"r");
    char str_sen[60];
    do
    {
        fgets(buff, 255, (FILE*)filein);
        if (!feof(filein))
        {
            strcpy(str_sen, buff);
            del_char(str_sen, '\n');
            //第一个的token值就是1
            //从1开始方便计数
            //这里真的不好写函数所以不写了，看起来很乱，不愧是我
            //tokens_num = 0;
            //tokens_flag = 1;
            /*逐个字符的扫描，不适用
            for (int i = 0;i<strlen(str_sen);i++)
            {
                if ((token[tokens_num]==tokens_flag) && (str_sen[i] == delim))
                {
                    //如果上一个是对应的token
                    tokens_num ++; //换到下一个token[]
                    tokens_flag ++; //换到下一个token
                    if (tokens_num==num) break;
                    continue;
                }
                //在上一个不相同的情况下扫描到了下一个token
                if (str_sen[i] == delim)
                {
                    tokens_flag++;
                    //将相邻两个数字隔开
                    printf("\t");
                    continue;
                }
                //如果符合，在同一个框框内
                if (token[tokens_num]==tokens_flag)
                {
                    printf("%s",str_sen[i]);
                }
            }
             */
            char *tokenchar;
            
            /* 获取第一个子字符串 */
            tokenchar = strtok(str_sen, delim);
            tokens_num = 0;
            tokens_flag = 1;
            /* 继续获取其他的子字符串 */
            while( tokenchar != NULL ) {
                if (token[tokens_num]==tokens_flag)
                {
                    printf("%s\t",tokenchar);
                    tokens_num++;
                }
                
                tokens_flag++;
                if (tokens_num==num) break;
                tokenchar = strtok(NULL, delim);
            }
            printf("\n");
            //一行扫描结束，换行并进行下一行的扫描
                
        }
    }while (!feof(filein));
    return;
}
//判断该为f后该怎么做
//for /f %c in (abc.txt) do @echo %c
//for /f “skip=1 tokens=1,4 delims= ” %c in (abc.txt) do @echo %c %d
void func_for_f(int line)
{
    //第三个元素，判断是哪一种
    char ch3[10];
    strcpy(ch3, word[line].mystr[2]);
    //取出文件的名字
    char chr[30];
    char *ch4;
    if (ch3[0]=='%')
    {
        strcpy(chr,str_cut(word[line].mystr[4]));
        ch4 = str_cut(chr);
        func_for_f1(line, ch4);
        return;
    }
    if (ch3[0]=='"')
    {
        strcpy(chr,str_cut(word[line].mystr[7]));
        ch4 = str_cut(chr);
        func_for_f2(line, ch4);
        return;
    }
}
//执行for职能
//for " " /r %%i in (???) do echo a;
//for " " /d %%i in (???) do echo a;
//for %%i in (???) do echo a;
//for /L %%i in (1,1,5) do md d:\aa %%i
//for /f %c in (abc.txt) do @echo %c
//for /f “skip=1 tokens=1,4 delims= ” %c in (abc.txt) do @echo %c %d
void func_for(int line)
{
    char ch2[30];
    strcpy(ch2,word[line].mystr[1]);
    if (ch2[0]=='%')
    {
        //for %%i in (???) do echo a;
        func_for_i(line);
        return;
    }
    if (ch2[0] == '"')
    {
        char ch3[4];
        strcpy(ch3, word[line].mystr[2]);
        if (ch3[1]=='r')
        {
            func_for_r(line);
            return;
        }
        if (ch3[1]=='d')
        {
            func_for_d(line);
            return;
        }
        printf("Unknown type of%c\n",ch3[1]);
    }
    if (ch2[0] == '/')
    {
        if (ch2[1]=='l')
        {
            func_for_l(line);
            return;
        }
        if (ch2[1] == 'f')
        {
            func_for_f(line);
            return;
        }
        if (ch2[1] == 'd')
        {
            func_for_d(line);
            return;
        }
        if (ch2[1] == 'r')
        {
            func_for_r(line);
            return;
        }
    }
    //strcpy(ch,)
}


#endif /* for_for_h */
