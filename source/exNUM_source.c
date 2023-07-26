#include "exNUM_source.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//2 to 10
//从流stream中读
int ScanBIN(int *num, FILE* stream)
{
    char tem;
    int ans = 0;
    int flag = 0;

    //char end = (stream == stdin) ? '\n' : '\0'

    while((tem = getc(stream)) != '\n'){
        //第一个是'-'
        if (tem == '-' && flag == 0){
            flag = 1;
            continue;
        }
        //第一个字符已过
        else if (flag == 0){
            flag = 2;
        }
        //不是数字
        else if (tem < '0' || tem > '9'){
            printf("invalid input!\n");
            return 0;
        }
        
        ans *= 2;
        ans += (tem - '0') ;
    }
    if(flag == 1)ans *= -1;
    *num = ans;
    return 1;
}

//10 to 2
//无换行
void PrintBIN(int num)
{
    int power = 0;

    //找到最大次数
    while(p(2,power++) <= num);
    power -= 2;

    for (int i = power; i >= 0; i--){
        int cond = num / p(2, i);
        printf("%d", cond);
        if(cond)num -= p(2, i);
    }
}

int read_num_buffer(char* in, int *num)
{
    int sta = 1;
    FILE* f1 = fopen("buffer.txt", "r");

    if (strcmp(in, "OCT") == 0 || strcmp(in, "O") == 0 || strcmp(in, "8") == 0) fscanf(f1, "%o",num);
    else if (strcmp(in, "HEX") == 0 || strcmp(in, "H") == 0 || strcmp(in, "16") == 0) fscanf(f1, "%x",num);
    else if (strcmp(in, "DEC") == 0 || strcmp(in, "D") == 0 || strcmp(in, "10") == 0) fscanf(f1, "%d",num);
    else if (strcmp(in, "BIN") == 0 || strcmp(in, "B") == 0 || strcmp(in, "2") == 0) sta = ScanBIN(num, f1);
    fclose(f1);
    return sta;
}

void write_buffer(char* str)
{
    FILE* f3 = fopen("buffer.txt", "w");
    fprintf(f3, "%s\n", str);
    fclose(f3);
}


void output(int num)
{
    PrintBIN(num);
    printf("  %o  %d  0x%X\n", num, num, num);
}

//文件是否为空
int FileEmpty()
{
    FILE *f1 = fopen("history.txt","r");
    int tem = fgetc(f1);
    fclose(f1);
    if (tem == EOF) return 1;
    else return 0;
}

//写入历史记录
void hisW(char *input_base)
{
    FILE *f1 = fopen("history.txt","w");
    fprintf(f1,"%s\n", input_base);

    time_t now;
    time(&now);
    fprintf(f1, "%s", asctime(localtime(&now)));

    fclose(f1);
}

//读取历史记录
void hisR(char *tem_time, char *input_base)
{
    FILE *f2 = fopen("./backup/history.txt","r");

    fscanf(f2, "%3s\n", input_base);
    fgets(tem_time,100,f2);

    fclose(f2);
}

void push_number(int num, number_list* list)
{
    if (list->len == 0){
        list->list = (int*)malloc(sizeof(int));
        list->list[0] = num;
        list->len = 1;
    }
    else {
        int len = list->len;
        list->list = realloc(list->list, (len + 1) * sizeof(int));
        list->list[len] = num;
        list->len ++;
    }   
}