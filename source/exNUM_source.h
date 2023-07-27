#ifndef _EXNUM_H_
#define _EXNUM_H_

#include "stdio.h"
#include "stdint.h"

#define INIT 0
#define ATTACH_ZERO 1
#define DIVIDE_BYTE 2

typedef enum align_mode_e
{
    NO_ALIGN = 0,
    L_ALIGN,
    R_ALIGN
}align_mode;

typedef struct num_data_s
{
    int num;
    uint8_t bin_len;
    uint8_t oct_len;
    uint8_t dec_len;
    uint8_t hex_len;
}num_data;


typedef struct number_list_s
{

    align_mode alignment;
    uint8_t display_mode;

    int len;
    num_data *arr;
    
    uint8_t bin_max_len;
    uint8_t oct_max_len;
    uint8_t dec_max_len;
    uint8_t hex_max_len;
}number_list;

typedef enum now_status_e
{
    INPUT = 0,
    CHOOSE,
    DISPLAY,
    SETTING,
    ERROR
}now_status;

//次方运算
#define p(__base__, __index__) (int)pow(__base__, __index__) 

#define max(x,y)  ({ \
typeof(x) _x = (x); \
typeof(y) _y = (y); \
_x > _y ? _x : _y; \
})

#define handle(__token__) \
((strcmp(__token__, "D") == 0 || strcmp(__token__, "DEC") == 0 || strcmp(__token__, "10") == 0) ? "DEC" :\
 (strcmp(__token__, "H") == 0 || strcmp(__token__, "HEX") == 0 || strcmp(__token__, "16") == 0) ? "HEX" :\
 (strcmp(__token__, "O") == 0 || strcmp(__token__, "OCT") == 0 || strcmp(__token__, "8")  == 0) ? "OCT" :\
 (strcmp(__token__, "B") == 0 || strcmp(__token__, "BIN") == 0 || strcmp(__token__, "2")  == 0) ? "BIN" :\
 "ERR")


int ScanBIN(int *num, FILE* stream);
void PrintBIN(int num);

void output(int index, number_list* list);

void hisW(char* input_base);
void hisR(char* tem_time, char* input_base);

void write_buffer(char* str);
int read_num_buffer(char* in, int* num);

int FileEmpty(void);

void push_number(int num, number_list* list);

#endif