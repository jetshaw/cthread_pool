#ifndef _CTHREAD_MUTEX_H__
#define _CTHREAD_MUTEX_H__
#include<pthread.h>
#include "noncopyable.h"

class ccondition;

class cthread_mutex:public noncopyable
{
    friend class ccondition;
    private:
        pthread_mutex_t m_mutex;
    public:
        cthread_mutex();
        ~cthread_mutex();
        int init(const pthread_mutexattr_t * attr);
        int destroy();
        int lock();
        int trylock();
        int unlock();
};

#endif //_CTHREAD_MUTEX_H__
