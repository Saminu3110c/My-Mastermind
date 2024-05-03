C=gcc
CFLAGS=-Wall -Wextra -Werror
TARGET=my_mastermind

all : $(TARGET)

$(TARGET) : $(TARGET).c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)

fclean: clean
	rm -f $(TARGET)

re: fclean all




# Makefile for my_mastermind
# CC = gcc
# CFLAGS = -Wall -Wextra -Werror

# SRCS = my_mastermind.c
# OBJS = $(SRCS:.c=.o)
# TARGET = my_mastermind

# all: $(TARGET)

# $(TARGET): $(OBJS)
#     $(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# clean:
#     rm -f $(OBJS)

# fclean: clean
#     rm -f $(TARGET)

# re: fclean all



