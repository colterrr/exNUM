# 编译相关
CC = gcc -Wall
CFLAGS =

# 中间文件夹名
BUILD_DIR = build

# 最终文件名
TARGET = exNUM

#源文件目录
C_PATH = source

#中间文件名 (不带目录)
O_FILE = $(notdir $(C_FILE:.c=.o))

#源文件名 (带目录)
C_FILE = $(wildcard $(addsuffix /*.c,$(C_PATH)))

$(TARGET) : $(O_FILE)
	$(CC) -o $@ $(addprefix $(BUILD_DIR)/,$(O_FILE))

vpath %.c $(C_PATH)
%.o : %.c | $(BUILD_DIR)
	$(CC) -c $< -o $(BUILD_DIR)/$@

$(BUILD_DIR) :
	mkdir $(BUILD_DIR)

.PHONY : clean

clean:
	-rm -rf $(BUILD_DIR)