CC = g++
LD = g++ 
CFLAGS= -g
LDFLAGS= -lpthread
TARGET=pooltest
SRCS =  cthread_pool.cc ccondition.cc cthread_mutex.cc cthread.cc cthread_manage.cc cjob.cc cworker_thread.cc
OBJS =  cthread_pool.o ccondition.o cthread_mutex.o cthread.o cthread_manage.o cjob.o cworker_thread.o
all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRCS) -o $(TARGET)
clean:
	rm -rf *.o $(TARGET)

