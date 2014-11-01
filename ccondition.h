#ifndef _CCONDITION_H___
#define _CCONDITION_H___
#include <pthread.h>
#include "cthread_mutex.h"

class ccondition
{
    private:
        pthread_cond_t m_cond;//条件变量
    public:
        ccondition();
        ccondition(pthread_cond_t cond);
        ~ccondition();

        int init(pthread_condattr_t * attr);//初始化条件变量
        int destroy();//销毁条件变量
        int wait(cthread_mutex & mutex);//条件等待
        int timedwait(cthread_mutex & mutex,const struct timespec * timeout);//超时等待
        int signal();//发信号
        int broadcast();//广播
};

#endif //_CCONDITION_H___
