#Targets for make file
TARGETS = p6w p6r

all:		$(TARGETS)

p6w:	p6w.c
		gcc -o p6w p6w.c -lrt
		
p6r:		p6r.c
		gcc -o p6r p6r.c -lrt
		
clean:	
		rm -f $(TARGETS) *.o		