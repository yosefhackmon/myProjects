CC=gcc

TARGET = main
#TARGET = linux-scalability

#MYFLAGS =  -g -O0 -Wall -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free

#uncomment this line to compile the $(TARGET) with standatd memory allocator
MYFLAGS = -g -O0 -Wall

OBJS = extract_operations archive_operations validiation_operations
#MYLIBS = libmtmm.a
#MYLIBS = libmtmmSSol.a

#
#all: $(TARGET)
#

all: main
#all: $(TARGET) $(MYLIBS) bct

#extract_operations.c archive_operations.c validiation_operations.c
#libmtmm.a: core_memory_allocator.c cpu_heap.c memory_allocator.c size_class.c 
#	$(CC) $(MYFLAGS) -c core_memory_allocator.c cpu_heap.c memory_allocator.c size_class.c 
#	ar rcu libmtmm.a core_memory_allocator.o cpu_heap.o memory_allocator.o size_class.o 
#	ranlib libmtmm.a

main: print_operations.c FuncWrappers_operations.c directory_operations.c string-operations.c extract_tree.c extract_operations.c archive_operations.c validiation_operations.c other_operations.c general_operations.c main_operations.c
	$(CC) $(MYFLAGS)  print_operations.c FuncWrappers_operations.c string-operations.c  directory_operations.c extract_tree.c extract_operations.c  archive_operations.c validiation_operations.c other_operations.c general_operations.c main_operations.c -o mkbkp
	
#$(OBJS): $(OBJS).c
#	$(CC) $(MYFLAGS) -c $(OBJS).c

#
#$(TARGET): $(TARGET).c 
#	$(CC) $(CCFLAGS) $(MYFLAGS) $(TARGET).c  -o $(TARGET) 
#

#$(TARGET): $(TARGET).c $(MYLIBS)
#	$(CC) $(CCFLAGS) $(MYFLAGS) $(TARGET).c $(MYLIBS) -o $(TARGET) -lpthread -lm


# bct: $(MYLIBS)
#	gcc -g -O0 -Wall -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free big-chanks.c libmtmm.a -o big-chanks -lm 

clean:
	rm -f $(TARGET)  *.o
	rm -f *.o 
	rm -f a.out
	rm -f *~
	rm -f *a 
	rm -f *.bkp
#	rm -f $(TARGET)  *.o  libmtmm.a a.out
