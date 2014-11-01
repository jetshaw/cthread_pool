#include"cthread_pool.h"
#include"cjob.h"
#include"cthread_manage.h"
#include<stdio.h>
#include<unistd.h>
#include<iostream>

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
    for(i=0;i<40;i++)
    {
        std::cout<<"\nin main for i="<<i<<std::endl;
        cxjob* job = new cxjob();
        manage->run(job,NULL);
    }
    sleep(2);
    cyjob* job = new cyjob();
    manage->run(job,NULL);
    manage->terminate_all();
    return 0;
}
