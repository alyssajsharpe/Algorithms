EXEC = itemMenu
OBJS = ${EXEC}.o item.o itemDB.o
CCFLAGS  = -g -Wall
COMP = gcc

ALLOBJS = ${OBJS}

all: ${EXEC}

${EXEC}: ${ALLOBJS}
	${COMP} $(CCFLAGS) $(EXPORT) -o ${EXEC} ${ALLOBJS} $(LDLIBS)

.c.o:
	${COMP} -c $< $(CCFLAGS)

link:
	${COMP} $(CCFLAGS) $(EXPORT) -o ${EXEC} ${ALLOBJS} $(LDLIBS)

clean:
	rm -rf *.o ${EXEC} ${OBJS} core

# DO NOT DELETE THIS LINE -- make depend depends on it.

