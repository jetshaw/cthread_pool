#include"cthread_mutex.h"
#include"debug.h"
#include<iostream>

cthread_mutex::cthread_mutex()
{
    //std::cout<<"cthread_mutex::cthread_mutex()\n"<<std::endl;
    pthread_mutex_init(&m_mutex,NULL);
    _XDBG;
}

cthread_mutex::~cthread_mutex()
{
    pthread_mutex_destroy(&m_mutex);
}

int cthread_mutex::init(const pthread_mutexattr_t * attr)
{
    _XDBG;
    return pthread_mutex_init(&m_mutex,attr);
}

int cthread_mutex::destroy()
{
    return pthread_mutex_destroy(&m_mutex);
}

int cthread_mutex::lock()
{
    //printf("pthread_ip=%lu mutex_addr=%p lock...\n",pthread_self(),&m_mutex);
    return pthread_mutex_lock(&m_mutex);
    //printf("pthread_ip=%lu mutex_addr=%p after ... lock...\n",pthread_self(),&m_mutex);
}

int cthread_mutex::trylock()
{
    return pthread_mutex_trylock(&m_mutex);
}

int cthread_mutex::unlock()
{
    return pthread_mutex_unlock(&m_mutex);
}


