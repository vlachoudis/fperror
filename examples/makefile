CC      = g++
CFLAGS  = -Wall -I..

# Debug or Optimize
ifeq ($(DEBUG),yes)
	CFLAGS  += -g
else
	CFLAGS  += -O3
endif
ifeq ($(PROFILE),yes)
	CFLAGS  += -pg
endif

NAME = fp_test
SRC  = ${NAME}.cc
OBJS = ${SRC:.cc=.o}

# ******* TARGETS ********
.PHONY: all tar tags clean

all: $(NAME)

# **************************
# Compiling rule
# **************************
%.o: %.cc
	$(CC) -c $(CFLAGS) $<

# **************************
# Dependencies rule
# **************************
%.d: %.cc
	$(CC) -MM $(INC) $< > $@

${NAME}: ${OBJS}
	$(CC) -o $@ $(CFLAGS) $^

# **************************
# Generic compilation of any program
# **************************
%: %.cc
	$(CC) -o $@ $< $(CFLAGS)

# **************************
tags: *.h *.cc
	ctags *.h *.cc

tar: $(NAME).tgz

$(NAME).tgz: *.h *.cc
	tar czvf $@ $^

clean:
	rm -f ${NAME} ${OBJS}
