#ifndef _CTHREAD_H_______
#define _CTHREAD_H_______
#include<pthread.h>
#include<string.h>
#include<stdexcept>

enum threadstate{
    THREAD_IDLE,
    THREAD_RUNNING,
    THREAD_PAUSE,
    THREAD_END
};

class cthread
{
    private:
        int m_errcode;
        //semaphore m_thread_semaphore;
        pthread_t m_thread_id;//线程ID
        bool m_detach;//线程属性之一，是否为分离线程
        bool m_create_suspended;//线程属性之一，是否为阻塞线程
        char* m_thread_name;//线程名称
        threadstate m_thread_state;//线程状态,分为四种：空闲，忙碌，挂起（暂停，Linux线程库不支持挂起操作），终止（包括正常退出和非正常退出），
    protected:
        void set_errcode(int errcode){m_errcode=errcode;}
        static void* thread_func(void *);//线程函数，
    public:
        cthread();
        cthread(bool createsuspended,bool detach);
        virtual ~cthread();
        virtual void run(void)=0;//执行线程函数
        void set_thread_state(threadstate state){m_thread_state=state;}//设置线程状态
        bool terminate(void);//终止线程函数
        bool start(void);//线程的执行入口，它将调用thread_function函数，
        void exit(void);//线程退出函数
        bool wake_up(void);//线程唤醒函数

        threadstate get_thread_state(void){return m_thread_state;}
        int get_last_error(void){return m_errcode;}
        void set_thread_name(char* thrname){strcpy(m_thread_name,thrname);}
        char* get_thread_name(void){return m_thread_name;}
        int get_thread_id(void){return m_thread_id;}
        bool set_priority(int priority);//设置线程优先级
        int get_priority(void);//获取线程优先级
        int get_concurrency(void);//获取线程并行级别
        void set_concurrency(int num);//设置线程并行级别
        bool detach(void);//是否为分离线程
        bool join(void);//是否为正常状态
        bool yield(void);//是否为丢弃状态
        pthread_t self(void);
};

#endif //_CTHREAD_H_______
