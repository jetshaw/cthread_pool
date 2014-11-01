#include "cworker_thread.h"
#include "cthread_pool.h"
#include "cjob.h"
#include "pthread.h"

cworker_thread::cworker_thread()
{
    m_job = NULL;
    m_jobdata = NULL;
    m_thread_pool=NULL;
    m_is_end = false; 
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
    set_thread_state(THREAD_RUNNING);
    for(;;)
    {
        while(m_job == NULL )
            m_jobcond.wait(m_work_mutex);
        m_job->run(m_jobdata);
        m_job->set_work_thread(NULL);
        m_job=NULL;
        m_thread_pool->moveto_idle_list(this);
        if( m_thread_pool->m_idlelist.size() > m_thread_pool->get_avail_high_num())
        {
            m_thread_pool->delete_idle_thread(m_thread_pool->m_idlelist.size()-m_thread_pool->get_init_num()); 
        }
        m_work_mutex.unlock();
    }
}

void cworker_thread::set_job(cjob* job,void* jobdata)
{
    m_varmutex.lock();
    m_job = job;
    m_jobdata = jobdata;
    job->set_work_thread(this);
    m_varmutex.unlock();
    m_jobcond.signal();
}

void cworker_thread::set_thread_pool(cthread_pool* thrpool)
{
    m_varmutex.lock();
    m_thread_pool = thrpool;
    m_varmutex.unlock();
}
