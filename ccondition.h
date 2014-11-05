#ifndef _CCONDITION_H___
#define _CCONDITION_H___
#include <pthread.h>
#include "cthread_mutex.h"
#include"noncopyable.h"

class ccondition:public noncopyable
{
    private:
        pthread_cond_t m_cond;//条件变量
        cthread_mutex *m_mutex_lock;//这里的互斥锁要用指针
    public:
        ccondition(cthread_mutex* p_mutex_lock);
        ccondition();
        ~ccondition();

        //int init(pthread_condattr_t * attr);//初始化条件变量
        int destroy();//销毁条件变量
        int wait();//条件等待
        int timedwait(const struct timespec * timeout);//超时等待
        int notify();//发通知
        int notify_all();//慎用
};

#endif //_CCONDITION_H___
