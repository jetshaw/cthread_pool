#include"cjob.h"
#include<string.h>
#include<stdlib.h>
cjob::cjob():m_pwork_thread(NULL),m_jobname(NULL)
{
}

cjob::~cjob()
{
    if( NULL != m_jobname)
        free(m_jobname);
}

void cjob::set_jobname(char* jobname)
{
    if(NULL != m_jobname)
    {
        free(m_jobname);
        m_jobname=NULL;
    }
    if( NULL != jobname )
    {
        m_jobname = (char *)malloc(strlen(jobname)+1);
        if( m_jobname != NULL )
            strcpy(m_jobname,jobname);
    }
}
