#include"cthread_mutex.h"

cthread_mutex::cthread_mutex():m_mutex(PTHREAD_MUTEX_INITIALIZER)
{
}

cthread_mutex::cthread_mutex(pthread_mutex_t mutex)
{
    m_mutex = mutex;
}

cthread_mutex::~cthread_mutex()
{
    pthread_mutex_destroy(&m_mutex);
}

int cthread_mutex::init(const pthread_mutexattr_t * attr)
{
    return pthread_mutex_init(&m_mutex,attr);
}

int cthread_mutex::destroy()
{
    return pthread_mutex_destroy(&m_mutex);
}

int cthread_mutex::lock()
{
    return pthread_mutex_lock(&m_mutex);
}

int cthread_mutex::trylock()
{
    return pthread_mutex_trylock(&m_mutex);
}

int cthread_mutex::unlock()
{
    return pthread_mutex_unlock(&m_mutex);
}


