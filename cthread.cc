#include"cthread.h"
#include"pthread.h"
#include"debug.h"
#include<iostream>
cthread::cthread():m_thread_id(0)
{
    m_detach = false;
    m_create_suspended = false;
}

cthread::~cthread()
{
}


cthread::cthread(bool createsuspended,bool detach)
{
    m_detach = detach;
    m_create_suspended = createsuspended;
}

bool cthread::terminate(void)
{
    int ret;
    ret = pthread_cancel(m_thread_id);
    return true;
}

bool cthread::start(void)
{
    //std::cout<<"\ncthread::start\n"<<std::endl;
    _XDBG;
    pthread_create(&m_thread_id,NULL,cthread::thread_func,this);
    _XDBG;
    //std::cout<<"after pthread_create\n"<<std::endl;
}

void cthread::exit()
{
    pthread_exit(NULL);
}

bool cthread::wake_up()
{

}

void *cthread::thread_func(void *arg)
{
    cthread* p_thread = static_cast<cthread*>(arg);
    _XDBG;
    p_thread->run();
    _XDBG;
}

bool cthread::set_priority(int priority)
{
    int ret;
    ret = pthread_setschedprio(m_thread_id,priority);
    return true;
}

int cthread::get_priority(void)
{
    int ret;
}

int cthread::get_concurrency(void)
{
    return pthread_getconcurrency();
}

void cthread::set_concurrency(int num)
{
    pthread_setconcurrency(num);
}

bool cthread::detach()
{
    int ret;
    ret = pthread_detach(m_thread_id);
    return true;
}

bool cthread::join()
{
    int ret;
    ret = pthread_join(m_thread_id,NULL);
    return true;
}

bool cthread::yield()
{
    int ret;
    ret = pthread_yield();
    return true;
}

pthread_t cthread::self(void)
{
    return pthread_self(); 
}

