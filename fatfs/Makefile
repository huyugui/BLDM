include ../Makefile.common
CFLAGS+=-c

FATFS_SRC +=  $(wildcard $(FATFSLIB)/*.c)
FATFS_SRC +=  $(wildcard $(FATFSLIB)/fatfs/*.c)
#FATFS_SRC +=  $(wildcard $(FATFSLIB)/fatfs/option/*.c)

FATFS_OBJS = $(patsubst %.c, %.o, $(FATFS_SRC))

all: fatfs

fatfs: libfatfs.a

libfatfs.a:$(FATFS_OBJS)
	@echo "============================================="
	@echo "               $@开始编译                    "
	@echo "============================================="
	$(AR) -cr $@ $(FATFS_OBJS)
	@echo "============================================="
	@echo "               $@开始编译                    "
	@echo "============================================="

.PHONY:clean
clean:
	rm libfatfs.a
	find -type f -name '*.o' -print0 |xargs -0 rm -f
