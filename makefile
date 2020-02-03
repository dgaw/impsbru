# Windows version of VBCC requires absolute path in all .h files
# e.g. timer manager has to refer to timer.h by absolute path

# TODO: refactor so 'make' without args won't recompile whole ACE

# Multi-platform
ifdef ComSpec
	# Windows
	RM = del
	CP = copy
	SLASH = \\
	CURR_DIR=$(shell chdir)
	ECHO = @echo
	NEWLINE = @echo.
	QUIETCOPY = > NUL
else
	# Linux/Amiga
	RM = rm
	CP = cp
	SLASH = /
	CURR_DIR = $(shell pwd)
	ECHO = @echo
	NEWLINE = @echo " "
	QUIETCOPY =
endif
SL= $(strip $(SLASH))
SRC_DIR = $(CURR_DIR)$(SL)src

TARGET_DEFINES =
TARGET ?= RELEASE
ifeq ($(TARGET), debug)
	ACE_TARGET = debug
else
	ACE_TARGET = release
endif

# Directories
TMP_DIR = $(CURR_DIR)$(SL)build
ACE_DIR = $(CURR_DIR)$(SL)deps$(SL)ace

# Compiler stuff
IMPSBRU_CC ?= m68k-amigaos-gcc

INCLUDES = -I$(SRC_DIR) -I$(ACE_DIR)/include
CC_FLAGS_COMMON = $(INCLUDES) -DAMIGA $(TARGET_DEFINES)
ifeq ($(IMPSBRU_CC), vc)
	CC_FLAGS = $(CC_FLAGS_COMMON) +kick13 -c99
	ACE_AS = vc
	AS_FLAGS = +kick13 -c
	OBJDUMP =
else ifeq ($(IMPSBRU_CC), m68k-amigaos-gcc)
	CC_FLAGS = $(CC_FLAGS_COMMON) -std=gnu11 -noixemul -Wall -Wextra \
		-fomit-frame-pointer -fstack-protector-all -O3
	ACE_AS = vasm
	AS_FLAGS = -quiet -x -m68010 -Faout
	OBJDUMP = m68k-amigaos-objdump -S -d $@ > $@.dasm
endif

# File list
IMPSBRU_MAIN_FILES = $(wildcard $(SRC_DIR)/*.c)
IMPSBRU_MAIN_OBJS = $(addprefix $(TMP_DIR)$(SL)imps_, $(notdir $(IMPSBRU_MAIN_FILES:.c=.o)))

IMPSBRU_MENU_FILES = $(wildcard $(SRC_DIR)/gamestates/menu/*.c)
IMPSBRU_MENU_OBJS = $(addprefix $(TMP_DIR)$(SL)imps_menu_, $(notdir $(IMPSBRU_MENU_FILES:.c=.o)))

IMPSBRU_EDITOR_FILES = $(wildcard $(SRC_DIR)/gamestates/editor/*.c)
IMPSBRU_EDITOR_OBJS = $(addprefix $(TMP_DIR)$(SL)imps_editor_, $(notdir $(IMPSBRU_EDITOR_FILES:.c=.o)))

IMPSBRU_FILES = $(IMPSBRU_MAIN_FILES) $(IMPSBRU_MENU_FILES) $(IMPSBRU_EDITOR_FILES)
IMPSBRU_OBJS = $(IMPSBRU_MAIN_OBJS) $(IMPSBRU_MENU_OBJS) $(IMPSBRU_EDITOR_OBJS)

ACE_OBJS = $(wildcard $(ACE_DIR)/build/*.o)

ace: $(ACE_OBJS)
	-make -C $(ACE_DIR) all ACE_CC=$(IMPSBRU_CC) TARGET=$(ACE_TARGET)
	$(NEWLINE)
	$(ECHO) Copying ACE objs
	@$(CP) $(ACE_DIR)$(SL)build$(SL)*.o $(TMP_DIR) $(QUIETCOPY)
	$(NEWLINE)

impsbru: $(IMPSBRU_OBJS)
	$(NEWLINE)
	$(ECHO) Linking...
	@$(IMPSBRU_CC) $(CC_FLAGS) -lamiga -o $@ $^ $(ACE_OBJS)

# Main files
$(TMP_DIR)$(SL)imps_%.o: $(SRC_DIR)/%.c
	$(ECHO) Building $<
	@$(IMPSBRU_CC) $(CC_FLAGS) -c -o $@ $<

# Menu
$(TMP_DIR)$(SL)imps_menu_%.o: $(SRC_DIR)/gamestates/menu/%.c
	$(ECHO) Building $<
	@$(IMPSBRU_CC) $(CC_FLAGS) -c -o $@ $<

# Editor
$(TMP_DIR)$(SL)imps_editor_%.o: $(SRC_DIR)/gamestates/editor/%.c
	$(ECHO) Building $<
	@$(IMPSBRU_CC) $(CC_FLAGS) -c -o $@ $<

all: clear ace impsbru install

clean: clear # Just an alias

clear:
	$(ECHO) "a" > $(TMP_DIR)$(SL)foo.o
	$(ECHO) "a" > $(TMP_DIR)$(SL)foo.dasm
	@$(RM) $(TMP_DIR)$(SL)*.o
	@$(RM) $(TMP_DIR)$(SL)*.dasm

# TODO: @dgaw. This is specific to my config. Make it general.
install: impsbru
	$(ECHO) Installing in FS-UAE...
	@$(CP) impsbru ~/FS-UAE/Hard\ Drives/Imps/impsbru/bin/

run:
	fs-uae ~/FS-UAE/Configurations/impsbru.fs-uae
