#include <stdio.h>
#include "for_for.h"
#include "for_if.h"
void tran()
{
    
}
int main() {
    
    FILE *fp = NULL;
    char buff[664];
    count = 0;
    char doc[30];
    printf("the file input:");
    scanf("%s",doc);
    fp = fopen(doc,"r");
    //读入 
    do
    {
        fgets(buff, 255, (FILE*)fp);
        if (!feof(fp))
        {
            strcpy(word[count].sentence, buff);
            del_char(word[count].sentence, '\n');
            seperate(word[count].sentence,count);
            count++;
        }
    }while (!feof(fp));
    //初始化
    func_shift_ori();
    /*
    for (int i = 0;i<count;i++)
    {
        printf("%s",word[count].sentence);
    }
     */
    //printf("count:%d",count);
    fclose(fp);
    for (int i = 0;i<count;i++)
    {
        if (!strcmp(word[i].mystr[0],"echo"))
        {
            func_echo(i);
            continue;
        }
        if (!strcmp(word[i].mystr[0],"set")) func_set(i);
        //for 的各种职能，在for_if 中进行实现
        if (!strcmp(word[i].mystr[0],"for"))
        {
            func_for(i);
        }
        if (!strcmp(word[i].mystr[0],"if"))
        {
            //如果中间含有goto需要返回line值
            if (goto_if(i))
            {
                i = func_if_goto(i);
            }
            else{
                func_if(i);
            }
            
        }
        if (!strcmp(word[i].mystr[0],"shift"))
        {
            func_shift(i);
        }
        if (!strcmp(word[i].mystr[0],"goto"))
        {
            i = func_goto(word[i].mystr[1],i);
        }
    }
    
    return 0;
}
