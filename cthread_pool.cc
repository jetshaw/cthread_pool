#include"cthread_pool.h"
#include<vector>
#include<iostream>
#include<assert.h>
#include<stdio.h>
#include<algorithm>
#include"debug.h"

cthread_pool::cthread_pool():m_busymutex(),m_idlemutex(),m_jobmutex(),m_varmutex(),m_busycond(&m_busymutex),m_idlecond(&m_idlemutex),m_idlejobcond(&m_jobmutex),m_maxnumcond(&m_varmutex)
{
    //printf("^^^^^^^^^^^^^^^^^^^^^^^^^^pthread_id=%lu m_busymutex_addr=%p m_idlemutex_addr=%p m_jobmutex_addr=%p m_varmutex_addr=%p ^^^^^^^^^^\n",pthread_self(),&m_busymutex,&m_idlemutex,&m_jobmutex,&m_varmutex);
    m_maxnum = 50;
    m_availlow = 5;
    m_initnum = m_availnum = 10;
    m_availhigh = 20;
    m_busylist.clear();
    m_idlelist.clear();
        int i;
    for(i=0;i<m_initnum;i++)
    {
    _XDBG;
        //std::cout<<"**********new cworker_thread*****************\n"<<std::endl;
        cworker_thread* thr = new cworker_thread();
    _XDBG;
        thr->set_thread_pool(this);
        appendto_idle_list(thr);
    _XDBG;
        thr->start();
    _XDBG;
    }
}

cthread_pool::cthread_pool(int initnum):m_busymutex(),m_idlemutex(),m_jobmutex(),m_varmutex(),m_busycond(&m_busymutex),m_idlecond(&m_idlemutex),m_idlejobcond(&m_jobmutex),m_maxnumcond(&m_varmutex)
{
    //printf("^^^^^^^^^^^^^^^^^^^^^^^^^^pthread_id=%lu m_busymutex_addr=%p m_idlemutex_addr=%p m_jobmutex_addr=%p m_varmutex_addr=%p ^^^^^^^^^^\n",pthread_self(),&m_busymutex,&m_idlemutex,&m_jobmutex,&m_varmutex);
    _XDBG;
    assert(initnum>0&&initnum<=30);
    m_maxnum = 30;
    m_availlow = initnum-10>0?initnum-10:3;
    m_initnum = m_availnum = initnum;
    m_availhigh = initnum+10;

    m_busylist.clear();
    m_idlelist.clear();
    int i;
    for(i=0;i<m_initnum;i++)
    {
    _XDBG;
        //std::cout<<"**********new cworker_thread*****************\n"<<std::endl;
        cworker_thread* thr = new cworker_thread();
    _XDBG;
        appendto_idle_list(thr);
        thr->set_thread_pool(this);
    _XDBG;
        thr->start();
    _XDBG;
    }
}

cthread_pool::~cthread_pool()
{
    terminate_all();
}

cworker_thread * cthread_pool::get_idle_thread(void)
{
    while(m_idlelist.size()==0)
        m_idlecond.wait();
    m_idlemutex.lock();
    if(m_idlelist.size()>0)
    {
        cworker_thread* thr = (cworker_thread*)m_idlelist.front();
        //printf("get idle thread %d\n",thr->get_thread_id());
        m_idlemutex.unlock();
        return thr;
    }
    m_idlemutex.unlock();
    return NULL;
}

void cthread_pool::appendto_idle_list(cworker_thread* jobthread)
{
    m_idlemutex.lock();
    m_idlelist.push_back(jobthread);
    m_threadlist.push_back(jobthread);
    m_idlemutex.unlock();
}

void cthread_pool::moveto_busy_list(cworker_thread* idlethread)
{
    m_busymutex.lock();
    m_busylist.push_back(idlethread);
    m_availnum--;
    m_busymutex.unlock();
    m_idlemutex.lock();
    vector<cworker_thread*>::iterator pos;
    pos = find(m_idlelist.begin(),m_idlelist.end(),idlethread);
    
    if(pos != m_idlelist.end())
        m_idlelist.erase(pos);
    m_idlemutex.unlock();
}

void cthread_pool::moveto_idle_list(cworker_thread* busythread)
{
    m_idlemutex.lock();
    m_idlelist.push_back(busythread);
    m_availnum++;
    m_idlemutex.unlock();
    m_busymutex.lock();
    vector<cworker_thread*>::iterator pos;
    pos = find(m_busylist.begin(),m_busylist.end(),busythread);
    if(pos != m_busylist.end())
        m_busylist.erase(pos);
    m_busymutex.unlock();
    m_idlecond.notify();
    m_maxnumcond.notify();
}

void cthread_pool::delete_idle_thread(int num)
{
    //std::cout<<"Enter into cthread_pool::delete_idle_thread \n"<<std::endl;
    m_idlemutex.lock();
    //std::cout<<"delete num is "<<num <<"\n"<<std::endl;
    int i;
    for(i=0;i<num;i++)
    {
        cworker_thread* thr=NULL;
        if(m_idlelist.size()>0)
        {
            thr = (cworker_thread*)m_idlelist.front();
            //std::cout<<"Get idle thread "<<thr->get_thread_id()<<"\n"<<std::endl;
        }
        vector<cworker_thread*>::iterator pos;
        pos = find(m_idlelist.begin(),m_idlelist.end(),thr);
        if( pos!= m_idlelist.end())
            m_idlelist.erase(pos);
        m_availnum--;
        //std::cout<<"the idle thread available num: "<<m_availnum<<"\n"<<std::endl;
        //std::cout<<"the idlelist num: "<<m_idlelist.size()<<"\n"<<std::endl;
    }
    m_idlemutex.unlock();
}

void cthread_pool::create_idle_thread(int num)
{
    int i;
    for(i=0;i<num;i++)
    {
        cworker_thread* thr = new cworker_thread();
        thr->set_thread_pool(this);
        appendto_idle_list(thr);
        m_varmutex.lock();
        m_availnum++;
        m_varmutex.unlock();
        thr->start();
    }
}

void cthread_pool::terminate_all()
{
    int i;
    for(i=0;i<m_threadlist.size();i++)
    {
        cworker_thread* thr = m_threadlist[i];
        thr->join();
    }
    return;
}

void cthread_pool::run(cjob* job,void* jobdata)
{
    //std::cout<<"\ncthread_pool::run\n"<<std::endl;
    assert(job != NULL);
    if(get_busy_num()==m_maxnum)
        m_maxnumcond.wait();
        _XDBG; 
    if(m_idlelist.size()<m_availlow)
    {
        _XDBG;
        //std::cout<<"又要创建线程\n"<<std::endl;
        if( get_all_num()+m_initnum-m_idlelist.size()<m_maxnum)
            create_idle_thread(m_initnum-m_idlelist.size());
        else
            create_idle_thread(m_maxnum-get_all_num());
    }
    cworker_thread* idlethr = get_idle_thread();
    if( idlethr != NULL)
    {
        idlethr->m_work_mutex.lock();
        _XDBG; 
        moveto_busy_list(idlethr);
        _XDBG; 
        idlethr->set_thread_pool(this);
        _XDBG; 
        job->set_work_thread(idlethr);
        //std::cout<<"jobisset to thread "<<idlethr->get_thread_id()<<"\n"<<std::endl;
        _XDBG; 
        idlethr->set_job(job,jobdata);
        idlethr->m_work_mutex.unlock();
        _XDBG; 
    }
    //std::cout<<"\ncthread_pool::run leave now\n"<<std::endl;
}


