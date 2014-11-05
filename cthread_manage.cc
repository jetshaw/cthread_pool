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
    std::cout<<"after cthread_manage::cthread_manage ...\n"<<std::endl;
}

cthread_manage::~cthread_manage()
{
    if( NULL != m_pool)
        delete m_pool;
}

void cthread_manage::run(cjob* job,void* jobdata)
{
    std::cout<<"\ncthread_manage::run\n"<<std::endl;
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
        cxjob(){}
        ~cxjob(){}
        void run(void* jobdata)
        {
            printf("the job comes from cxjob\n");
            sleep(2);
        }
};

class cyjob:public cjob
{
    public:
        cyjob(){}
        ~cyjob(){}
        void run(void* jobdata)
        {
            printf("the job comes from cyjob\n");
        }
};



int main(int argc,char** argv)
{
    cthread_manage* manage = new cthread_manage(10);
    int i;
    std::cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"<<std::endl;
    for(i=0;i<4;i++)
    {
        std::cout<<"\nin main for i="<<i<<std::endl;
        cxjob* job = new cxjob();
        manage->run(job,NULL);
    }
    std::cout<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"<<std::endl;
    sleep(2);
    cyjob* job = new cyjob();
    manage->run(job,NULL);
    std::cout<<"after manage->run(job,NULL)\n"<<std::endl;
    std::cout<<"##########################################################################################\n"<<std::endl;
    manage->terminate_all();
    std::cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n"<<std::endl;
    return 0;
}

#endif 
