#include "cthread_manage.h"
#include"cjob.h"
#include "cthread_pool.h"
#include<iostream>
#include"debug.h"
#include<stdio.h>
#include<unistd.h>
#define _TEST_POOL_ 1
cthread_manage::cthread_manage()
{
    _XDBG;
    m_num_of_thread = 10;
    m_pool = new cthread_pool(m_num_of_thread);
    _XDBG;
}

cthread_manage::cthread_manage(int num)
{
    _XDBG;
    m_num_of_thread = num;
    m_pool = new cthread_pool(m_num_of_thread);
    _XDBG;
}

cthread_manage::~cthread_manage()
{
    if( NULL != m_pool)
        delete m_pool;
}

void cthread_manage::run(cjob* job,void* jobdata)
{
    _XDBG;
    m_pool->run(job,jobdata);
    _XDBG;
}

void cthread_manage::terminate_all(void)
{
    m_pool->terminate_all();
}

void cthread_manage::set_parallel_num(int num)
{
    m_num_of_thread = num;
}

/*
 *test 
 *
 * */
#if _TEST_POOL_

class cxjob:public cjob
{
    public:
        cxjob();
        ~cxjob(){}
        void run(void* jobdata)
        {
            printf("\n.................pthread_id=%lu the job comes from cxjob....jobno=%d....\n",pthread_self(),get_jobno());
            sleep(2);
        }
};

cxjob::cxjob():cjob(){}

class cyjob:public cjob
{
    public:
        cyjob();
        ~cyjob(){}
        void run(void* jobdata)
        {
            printf("\n.................pthread_id=%lu the job comes from cyjob....jobno=%d....\n",pthread_self(),get_jobno());
        }
};

cyjob::cyjob():cjob(){}

cthread_manage* manage; 
int main(int argc,char** argv)
{
    int i;
    manage = new cthread_manage(10);
    for(i=0;i<44;i++)
    {
        cxjob* job = new cxjob();
        job->set_jobno(i);
        manage->run(job,NULL);
    }
    sleep(2);
    cyjob* job = new cyjob();
    job->set_jobno(i);
    manage->run(job,NULL );
    printf("2: idle_nums=%d busy_nums=%d total=%d\n",manage->m_pool->m_idlelist.size(),manage->m_pool->m_busylist.size(),manage->m_pool->get_all_num());
    manage->terminate_all();
    printf("3: idle_nums=%d busy_nums=%d total=%d\n",manage->m_pool->m_idlelist.size(),manage->m_pool->m_busylist.size(),manage->m_pool->get_all_num());
    return 0;
}

#endif 
