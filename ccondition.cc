#include"ccondition.h"

ccondition::ccondition():m_cond(PTHREAD_COND_INITIALIZER)
{

}

ccondition::ccondition(pthread_cond_t cond)
{
    m_cond = cond;
}

ccondition::~ccondition()
{
    pthread_cond_destroy(&m_cond);
}

int ccondition::init(pthread_condattr_t * attr)
{
    return pthread_cond_init(&m_cond,attr);
}

int ccondition::destroy()
{
    return pthread_cond_destroy(&m_cond);
}

int ccondition::wait(cthread_mutex & mutex)
{
    return pthread_cond_wait(&m_cond,&mutex.m_mutex);
}

int ccondition::timedwait(cthread_mutex &mutex,const struct timespec * timeout)
{
    return pthread_cond_timedwait(&m_cond,&mutex.m_mutex,timeout);
}

int ccondition::signal()
{
    return pthread_cond_signal(&m_cond);
}

int ccondition::broadcast()
{
    return pthread_cond_broadcast(&m_cond);
}


