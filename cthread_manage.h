#ifndef _CTHREAD_MANAGE_H__
#define _CTHREAD_MANAGE_H__
#include"cjob.h"

class cthread_pool;
//线程池管理器,用于创建并管理线程池
class cthread_manage
{
    private:
        cthread_pool* m_pool;//线程池
        int m_num_of_thread;//初始创建时允许创建的并发的线程数量
    protected:
    public:
        void set_parallel_num(int num);//设置并发线程数量
        cthread_manage();//
        cthread_manage(int num);//
        virtual ~cthread_manage();//

        void run(cjob* job,void* jobdata);//运行线程
        void terminate_all(void);//终止线程

};

#endif //_CTHREAD_MANAGE_H__
