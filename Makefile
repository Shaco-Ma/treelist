#AllDirs := $(shell ls -R | grep '^\./.*:$$' | awk '{gsub(":","");print}') .
CUR_DIR = $(shell pwd)
OBJ_DIR = $(CUR_DIR)/build
BIN_DIR = $(CUR_DIR)/bin
AllDirs := $(CUR_DIR)
AllDirs += $(CUR_DIR)/app/src
Sources := $(foreach n,$(AllDirs) , $(wildcard $(n)/*.c))
ALL_INC_DIR = $(CUR_DIR)/app/include
Objs := $(patsubst %.c,%.o, $(Sources))
Deps := $(patsubst %.c,%.d, $(Sources))
StaticLib :=
DynamicLib :=
Bin := $(BIN_DIR)/treelist
#AllLibs : $(DynamicLib)
#AllLibs : $(StaticLib) 
#AllLibs : $(Bin)

CROSS_COMPILE :=
CC = $(CROSS_COMPILE)gcc
CPP = $(CROSS_COMPILE)g++
AR = $(CROSS_COMPILE)ar
MKDIR = mkdir -p


$(foreach dirname,$(sort $(OBJ_DIR) $(BIN_DIR)),$(shell $(MKDIR) $(dirname)))

CFLAGS = -g -O2 -fPIC -Wall
CFLAGS += $(addprefix -I,$(ALL_INC_DIR))
#LDFLAGS += -lpthread
#CPPFLAGS = $(foreach n,$(AllDirs) , -I$(n))
#LDFLAGS := -lssl -lcrypto 

#$(StaticLib) : $(Objs)
#	AR rcs $@ $^
#
#$(DynamicLib) : $(Objs)
#	CPP -shared -o $@ $^ $(LDFLAGS)

$(Bin) : $(Objs)
	$(CC) -o $@ $(Objs) $(LDFLAGS)
	mv $(Objs) $(OBJ_DIR)
	cp $(Sources) $(OBJ_DIR)

%.o : %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

sinclude $(Deps)
.PHONY : clean
clean: 
	rm -rf $(Deps) $(StaticLib) $(DynamicLib) $(BIN_DIR) $(OBJ_DIR) $(Objs)

