#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "exNUM_source.h"

int main()
{
    char input_base[4];

    //中间的文字，空 或 last mode record
    char centre_word[200]="";

    char input_str[50];

    int num = 0;
    now_status status = CHOOSE;

    number_list list;
    list.len = 0;
    list.bin_max_len = 0;
    list.oct_max_len = 0;
    list.dec_max_len = 0;
    list.hex_max_len = 0;
    list.alignment = NO_ALIGN;
    list.display_mode = INIT;

    char tem_time[30];

    //历史记录判断
    if (!FileEmpty()){
        status = INPUT;

        hisR(tem_time, input_base);

        strcat(centre_word, "       Last mode changed Record:\n       ");
        strcat(centre_word, tem_time);
        strcat(centre_word, "--------------------------------------\n");            
    }


    while(1)
    {
        system("cls");
        //system("clear");
        switch (status)
        {
        case INPUT : {
            printf ("--------------------------------------\n"   
                    "       exNUM  2.0  (2023/4/15)\n"            
                    "--------------------------------------\n"
                    "%s"
                    "         Input  Base: %s\n"
                    "--------------------------------------\n",centre_word,input_base);
            //清除首次打开程序时历史记录显示
            strcpy(centre_word, "");

            printf("\n(input q/Q to quit to choose a new base)\n");
            printf("(input d/D to directly go to display)\n\n");
            printf("Please input your number:\n");
            
            scanf("%s", input_str);
            //按q提出
            if (strcmp(input_str, "q") == 0 || strcmp(input_str, "Q") == 0){
                status = CHOOSE;
            }
            else if (strcmp(input_str, "d") == 0 || strcmp(input_str, "D") == 0){
                status = DISPLAY;
            }
            //输入数据（未加入纯数字检测）
            else {
                write_buffer(input_str);
                if (read_num_buffer(input_base, &num) == 0)continue;
                push_number(num, &list);
                status = DISPLAY;
            }

            break;
        }
        case CHOOSE : {
            printf ("--------------------------------------\n"   
                    "       exNUM  2.0  (2023/4/15)\n"            
                    "--------------------------------------\n"
                    "  D / DEC / 10 for decimal system\n"        
                    "  H / HEX / 16 for hexadecimal system\n"
                    "  B / BIN / 2  for binary system\n"          
                    "  O / OCT / 8  for octal system\n"           
                    "--------------------------------------\n\n");

            printf("input base?\n");
            scanf("%s",input_base);       

            while (strcmp(handle(input_base), "ERR") == 0){
                printf("invalid input!\n");
                scanf("%s",input_base);
            }

            strcpy(input_base, handle(input_base));
            hisW(input_base);
            status = INPUT;

            break;
        }  
        case SETTING : {
            printf("--------------------------------------\n"   
                    "       exNUM  2.0  (2023/4/15)\n"            
                    "--------------------------------------\n");
            printf("\n(input q/Q to quit to go back to display)\n\n");
            printf("1 to clear\n");
            printf("2 to change to no alignment mode\n");
            printf("l/L to change to left alignment mode\n");
            printf("r/R to change to right alignment mode\n");
            printf("3 to attach reference zero\n");
            printf("4 to divide number by bytes (available for bin/hex)\n");

            scanf("%s", input_str);
            if (strcmp(input_str, "q") == 0 || strcmp(input_str, "Q") == 0){
                status = DISPLAY;
            }
            else if (strcmp(input_str, "1") == 0){
                free(list.arr);
                list.len = 0;
            }
            else if (strcmp(input_str, "2") == 0){
                list.alignment= NO_ALIGN;
            }
            else if (strcmp(input_str, "r") == 0 || strcmp(input_str, "R") == 0){
                list.alignment = R_ALIGN;
            }
            else if (strcmp(input_str, "l") == 0 || strcmp(input_str, "L") == 0){
                list.alignment = L_ALIGN;
            }
            else if (strcmp(input_str, "3") == 0){
                list.display_mode |= ATTACH_ZERO;
            }
            else if (strcmp(input_str, "4") == 0){
                list.display_mode |= DIVIDE_BYTE;
            }
            break;
        }
        case DISPLAY : {
            printf("--------------------------------------\n"   
                    "       exNUM  2.0  (2023/4/15)\n"            
                    "--------------------------------------\n");

            printf("\n(input q/Q to quit to input a new number)\n");
            printf("(input s/S to enter setting mode)\n\n");
        
            for (int i = 0; i < list.len ; i++){
                output(i, &list);
            }

            scanf("%s", input_str);
            //按q回退
            if (strcmp(input_str, "q") == 0 || strcmp(input_str, "Q") == 0){
                status = INPUT;
            }
            //按s进入设置
            else if (strcmp(input_str, "s") == 0 || strcmp(input_str, "S") == 0){
                status = SETTING;
            }
            else {
                printf("invalid input\n");
                system("pause");
            }
            break;
        }
        default:
            break;
        }
    }
}

