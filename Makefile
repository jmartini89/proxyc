NAME = proxy
CC = gcc
CFLAGS =
DEBUG = -g fsanitize=thread

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES = $(shell find $(SRCDIR) -name "*.c")
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
TARGET = $(BINDIR)/$(NAME)

all : $(TARGET)

$(NAME) : all

clean :
	@$(RM) $(TARGET) $(OBJECTS)
	@echo "\033[33m"$(NAME)" clean completed\033[0m"

fclean : clean
	@$(RM) -r $(OBJDIR) $(BINDIR)
	@echo "\033[33mfull clean completed\033[0m"

re : clean all

debug : CFLAGS += $(DEBUG)
debug : all
	@echo "\033[31mDEBUG\033[0m"

#Link
$(TARGET) : $(OBJECTS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ $^ $(INCLUDE)
	@echo "\033[32m"$@" compiled successfully\033[0m"

#Compile
$(OBJECTS) : $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[34m"$<" compiled successfully\033[0m"