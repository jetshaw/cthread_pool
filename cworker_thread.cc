#include "cworker_thread.h"
#include "cthread_pool.h"
#include "cjob.h"
#include "pthread.h"
#include"debug.h"

cworker_thread::cworker_thread(cthread_mutex* work_lock,cthread_mutex*var_lock,ccondition* job_cond)
{
    m_job = NULL;
    m_jobdata = NULL;
    m_thread_pool=NULL;
    m_is_end = false;
    m_work_mutex = work_lock;
    m_varmutex = var_lock;
    m_jobcond = job_cond;
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
        //m_work_mutex.lock();
        while(m_job == NULL )
            m_jobcond->wait();
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
        m_work_mutex->unlock();
    _XDBG;
    }
}

void cworker_thread::set_job(cjob* job,void* jobdata)
{
    m_varmutex->lock();
    _XDBG;
    m_job = job;
    m_jobdata = jobdata;
    job->set_work_thread(this);
    _XDBG;
    m_varmutex->unlock();
    _XDBG;
    m_jobcond->notify();
    _XDBG;
}

void cworker_thread::set_thread_pool(cthread_pool* thrpool)
{
    m_varmutex->lock();
    _XDBG;
    m_thread_pool = thrpool;
    m_varmutex->unlock();
    _XDBG;
}
