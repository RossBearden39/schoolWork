#Declare variables
LDFLAGS = -g
#Compiler used
CC = gcc

#Targets for make file
TARGETS = p4static p4dynlink p4dynload

all: $(TARGETS)

#P4static target
p4static: p4a.c
	gcc $(LDFLAGS) -o $@ $< -static -L. /usr/lib/i386-linux-gnu/libpthread.a 
	@echo "* To run statichello: ./$@"
	@echo " "
#p4dynload target
p4dynlink: p4a.c
	gcc $(LDFLAGS) -o $@ $< -L. -lpthread
	@echo "* To run p4dynlink: LD_LIBRARY_PATH = 'pwd' ./$@"
	@echo " "
#p4dynload target
p4dynload: p4b.c
	gcc $(LDFLAGS) -o $@ $< -ldl
	@echo "* To run p4dynload: :D_LIBRARY_PATH='pwd' ./$@"
	@echo " "

#cleans all .o and executable files
clean:
	rm -f $(TARGETS) *.o 