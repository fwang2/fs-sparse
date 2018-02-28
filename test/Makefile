SRC := $(wildcard *.cc)
OBJS := $(SRC:.cc=.o)
BINS := $(SRC:.cc=)
DEPS := $(SRC:.cc=.d)

all: $(BINS)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(DEPS) $(BINS)

