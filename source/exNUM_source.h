#ifndef _EXNUM_H_
#define _EXNUM_H_

#include "stdio.h"

typedef struct number_list_s
{
    int *list;
    int len;
}number_list;

typedef enum now_status_e
{
    INPUT = 0,
    CHOOSE,
    DISPLAY,
    SETTING,
    ERROR
}now_status;

#define p(__base__, __index__) (int)pow(__base__, __index__) 

#define handle(__token__) \
((strcmp(__token__, "D") == 0 || strcmp(__token__, "DEC") == 0 || strcmp(__token__, "10") == 0) ? "DEC" :\
 (strcmp(__token__, "H") == 0 || strcmp(__token__, "HEX") == 0 || strcmp(__token__, "16") == 0) ? "HEX" :\
 (strcmp(__token__, "O") == 0 || strcmp(__token__, "OCT") == 0 || strcmp(__token__, "8")  == 0) ? "OCT" :\
 (strcmp(__token__, "B") == 0 || strcmp(__token__, "BIN") == 0 || strcmp(__token__, "2")  == 0) ? "BIN" :\
 "ERR")


int ScanBIN(int *num, FILE* stream);
void PrintBIN(int num);

void output(int num);

void hisW(char* input_base);
void hisR(char* tem_time, char* input_base);

void write_buffer(char* str);
int read_num_buffer(char* in, int* num);

int FileEmpty(void);

void push_number(int num, number_list* list);

#endif