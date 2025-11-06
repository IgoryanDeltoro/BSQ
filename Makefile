NAME = bsq

GCC = cc

CFLAGS = -Wall -Wextra -Werror 

BUILD = build

MAP_FILE = map.txt

RM = rm -fr

SRC = main.c bsq.c

OBJ = $(SRC:%.c=$(BUILD)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(GCC) $(CFLAGS) $(OBJ) -o $(NAME)

$(BUILD)/%.o: %.c | $(BUILD)
	$(GCC) $(CFLAGS) -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)
	@printf '%s\n' "9 . o x" \
	"..........................." \
	"....o......................" \
	"............o.............." \
	"..........................." \
	"....o......................" \
	"...............o..........." \
	"..........................." \
	"......o..............o....." \
	"..o.......o................" > $(MAP_FILE)

clean:
	$(RM) $(BUILD) $(NAME) $(MAP_FILE)

re: clean all

.PHONY: all clean re
