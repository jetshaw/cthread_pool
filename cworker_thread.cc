#include "cworker_thread.h"
#include "cthread_pool.h"
#include "cjob.h"
#include "pthread.h"
#include"debug.h"

cworker_thread::cworker_thread():m_varmutex(),m_work_mutex(),m_jobcond(&m_work_mutex)
{
    m_job = NULL;
    m_jobdata = NULL;
    m_thread_pool=NULL;
    m_is_end = false;
    //printf("pthread_id=%lu m_varmutex_addr=%p m_work_mutex_addr=%p\n",pthread_self(),&m_varmutex,&m_work_mutex);
}

cworker_thread::~cworker_thread()
{
    if( NULL != m_job)
        delete m_job;
    if(m_thread_pool != NULL )
        delete m_thread_pool;
}

void cworker_thread::run()
{
    _XDBG;
    set_thread_state(THREAD_RUNNING);
    for(;;)
    {
    _XDBG;
        //m_work_mutex->lock();
        while(m_job == NULL )
        {
    //std::cout<<"myself_thread="<<pthread_self()<<" m_work_mutex addr="<<&m_work_mutex<<"\n"<<std::endl;
            //printf("%s %d to wait now\n",__func__,__LINE__);
            m_jobcond.wait();
        }
    _XDBG;
        m_job->run(m_jobdata);
    _XDBG;
        m_job->set_work_thread(NULL);
        m_job=NULL;
        m_thread_pool->moveto_idle_list(this);
        if( m_thread_pool->m_idlelist.size() > m_thread_pool->get_avail_high_num())
        {
            m_thread_pool->delete_idle_thread(m_thread_pool->m_idlelist.size()-m_thread_pool->get_init_num()); 
        }
    _XDBG;
        m_work_mutex.unlock();
    _XDBG;
    }
}

void cworker_thread::set_job(cjob* job,void* jobdata)
{
    //printf("%s %d  pthread_ip=%lu...\n",__func__,__LINE__,pthread_self());
    //m_varmutex.lock();
    _XDBG;
    m_job = job;
    m_jobdata = jobdata;
    job->set_work_thread(this);
    _XDBG;
    //m_varmutex.unlock();
    _XDBG;
    //std::cout<<"myself_thread="<<pthread_self()<<" m_work_mutex addr="<<&m_work_mutex<<"\n"<<std::endl;
    m_jobcond.notify();
    _XDBG;
}

void cworker_thread::set_thread_pool(cthread_pool* thrpool)
{
    m_varmutex.lock();
    _XDBG;
    m_thread_pool = thrpool;
    m_varmutex.unlock();
    _XDBG;
}
