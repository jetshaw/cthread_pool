#ifndef _CWORKER_THREAD_H__
#define _CWORKER_THREAD_H__

#include "cthread.h"
#include "cthread_mutex.h"
#include "ccondition.h"
#include "cjob.h"

class cthread_pool;

class cworker_thread : public cthread 
{
    private:
        cthread_pool* m_thread_pool;
        cjob* m_job;
        void* m_jobdata;
        cthread_mutex m_varmutex;
        bool m_is_end;
    protected:

    public:
        cthread_mutex m_work_mutex;
        ccondition m_jobcond;
        cworker_thread();
        virtual ~cworker_thread();
        void set_job(cjob* job,void*jobdata);
        cjob* get_job(void){return m_job;}
        void run(void);
        void set_thread_pool(cthread_pool *pool);
        cthread_pool* get_thread_pool(void){ return m_thread_pool;}
};

#endif //_CWORKER_THREAD_H__
