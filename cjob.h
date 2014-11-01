#ifndef _CJOB_H_______
#define _CJOB_H_______

#include"cthread.h"


class cjob
{
    private:
        int m_jobno;//任务序号
        char* m_jobname;//任务名称
        cthread* m_pwork_thread;//执行该任务的线程
    public:
        cjob();
        virtual ~cjob();
        int get_jobno() const {return m_jobno;}
        void set_jobno(int jobno){m_jobno = jobno;}
        char* get_jobname()const {return m_jobname;}
        void set_jobname(char* jobname);
        cthread *get_work_thread(){return m_pwork_thread;}
        void set_work_thread(cthread* pworkthread){m_pwork_thread=pworkthread;}
        virtual void run(void *ptr)=0;//执行入口
};

#endif //_CJOB_H______
