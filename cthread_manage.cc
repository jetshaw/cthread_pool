#include "cthread_manage.h"
#include"cjob.h"
#include "cthread_pool.h"
#include<iostream>

cthread_manage::cthread_manage()
{
    m_num_of_thread = 10;
    m_pool = new cthread_pool(m_num_of_thread);
}

cthread_manage::cthread_manage(int num)
{
    m_num_of_thread = num;
    m_pool = new cthread_pool(m_num_of_thread);
}

cthread_manage::~cthread_manage()
{
    if( NULL != m_pool)
        delete m_pool;
}

void cthread_manage::run(cjob* job,void* jobdata)
{
    std::cout<<"\ncthread_manage::run\n"<<std::endl;
    m_pool->run(job,jobdata);
}

void cthread_manage::terminate_all(void)
{
    m_pool->terminate_all();
}

void cthread_manage::set_parallel_num(int num)
{
    m_num_of_thread = num;
}
