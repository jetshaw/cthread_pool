#ifndef __CTHREAD_POOL_H___
#define __CTHREAD_POOL_H___
#include "ccondition.h"
#include "cthread_mutex.h"
#include "cjob.h"
#include<pthread.h>
#include<vector>
#include"cworker_thread.h"
using namespace std;

//线程池
class cthread_pool
{
    friend class cworker_thread;
    private:
        unsigned int m_maxnum;// 池中线程总数            当前线程池中所允许并发存在的线程的最大数量
        unsigned int m_availlow;// 池中可用余额下限      当前线程池中所允许存在的空闲线程的最小数量
        unsigned int m_availhigh;//池中可用余额上限      当前线程池中所允许的空闲的线程的最大数量
        unsigned int m_availnum;//池中可用余额实际值     当前线程池中实际存在的线程的数量,始终处于 low 和high之间即叫平衡，此时不需要创建 也不需要删除
        unsigned int m_initnum;//初始创建时线程池中的线程的个数
    protected:
        cworker_thread* get_idle_thread(void);//获取一个空闲线程
        void appendto_idle_list(cworker_thread* jobthread);//将一个线程加入空闲线程链表中
        void moveto_busy_list(cworker_thread* idlethread);//将一个线程移入忙碌线程链表中
        void moveto_idle_list(cworker_thread* busythread);//将一个线程移入空闲线程链表中
        void delete_idle_thread(int num);//删除一定数量的空闲线程
        void create_idle_thread(int num);//创建一定数量的空闲线程
    public:
        mutable cthread_mutex m_busymutex;//
        mutable cthread_mutex m_idlemutex;//
        mutable cthread_mutex m_jobmutex;//
        mutable cthread_mutex m_varmutex;//
        mutable ccondition m_busycond;//
        mutable ccondition m_idlecond;//
        mutable ccondition m_idlejobcond;//
        mutable ccondition m_maxnumcond;//
    public:
        vector< cworker_thread *> m_threadlist;//
        vector< cworker_thread *> m_busylist;//空闲链表
        vector< cworker_thread *> m_idlelist;//忙碌链表

        cthread_pool();//
        cthread_pool(int initnum);//
        virtual ~cthread_pool();

        void set_maxnum(int maxnum){m_maxnum = maxnum;}
        int get_maxnum(void){return m_maxnum;}
        void set_avail_low_num(int minnum){m_availlow=minnum;}
        int get_avail_low_num(void){return m_availlow;}
        void set_avail_high_num(int highnum){m_availhigh = highnum;}
        int get_avail_high_num(void){return m_availhigh;}
        int get_actual_availnum(void){return m_availnum;}
        int get_all_num(void){return m_threadlist.size();}
        int get_busy_num(void){return m_busylist.size();}
        void set_init_num(int initnum){m_initnum = initnum;}
        int get_init_num(void){return m_initnum;}
        void terminate_all(void);//
        void run(cjob* job,void* jobdata);//

};

#endif //__CTHREAD_POOL_H___
