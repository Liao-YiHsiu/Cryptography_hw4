.PHONY: clean

#LDFLAGS+=-lntl -lm -lgmp # link to math library
LDLIBS+= -lntl 

TARGET=knapsack

all: $(TARGET)
# type make/make all to compile test_hmm

o3: CPPFLAGS+=-o3
o3: all

debug: CPPFLAGS+=-g
debug: all

run: all
	./knapsack knap.in

clean:
	$(RM) $(TARGET)   # type make clean to remove the compiled file
