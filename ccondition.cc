#include"ccondition.h"
#include"debug.h"
#include<iostream>

ccondition::ccondition(cthread_mutex *p_mutex_lock)
{
    m_mutex_lock = p_mutex_lock;
    /*
     *std::cout<<"ccondition::m_mutex_lock address="<<m_mutex_lock<<"\n"<<std::endl;
     *std::cout<<"ccondition::m_mutex_lock->m_mutex address="<<&m_mutex_lock->m_mutex <<"\n"<<std::endl;
     */
    pthread_cond_init(&m_cond,NULL);
}

ccondition::ccondition():m_mutex_lock(NULL)
{
    
    pthread_cond_init(&m_cond,NULL);
}


ccondition::~ccondition()
{
    pthread_cond_destroy(&m_cond);
}
/*
 *
 *int ccondition::init(pthread_condattr_t * attr)
 *{
 *    _XDBG;
 *    return pthread_cond_init(&m_cond,attr);
 *}
 *
 */
int ccondition::destroy()
{
    return pthread_cond_destroy(&m_cond);
}

int ccondition::wait()
{
    _XDBG;
    //std::cout<<"pthread_self()="<<pthread_self()<<"\n"<<std::endl;
    //std::cout<<"wait::   ... ccondition::m_mutex_lock->m_mutex address="<<&m_mutex_lock->m_mutex <<"\n"<<std::endl;
    printf("pthread_id=%lu mutex addr=%p wait...\n",pthread_self(),&m_mutex_lock->m_mutex);
    int ret =pthread_cond_wait(&m_cond,&m_mutex_lock->m_mutex);
    _XDBG;
    /*
     *if( ret == 0 )
     *    printf("pthread_cond_wait success!!!\n");
     *else
     *    printf("pthread_cond_wait failed!!!\n");
     */
    return ret;
}

int ccondition::timedwait(const struct timespec * timeout)
{
    return pthread_cond_timedwait(&m_cond,&m_mutex_lock->m_mutex ,timeout);
}

int ccondition::notify()
{
    _XDBG;
    /*
     *std::cout<<"pthread_self()="<<pthread_self()<<"\n"<<std::endl;
     *std::cout<<"notify::   ... ccondition::m_mutex_lock address="<<m_mutex_lock<<"\n"<<std::endl;
     */
    //std::cout<<"notify::   ... ccondition::m_mutex_lock->m_mutex address="<<&m_mutex_lock->m_mutex <<"\n"<<std::endl;
    int ret =pthread_cond_signal(&m_cond);
    /*
     *if( ret == 0 )
     *    printf("pthread_cond_signal success!!!\n");
     *else
     *    printf("pthread_cond_signal failed!!!\n");
     */
    _XDBG;
    return ret;
}

int ccondition::notify_all()
{
    return pthread_cond_broadcast(&m_cond);
}


