#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__
////////////////////////////////////////////////////////////////////////////////
///
/// @file Singleton.hpp
///
/// @brief TSingletonClass class declaration.
///
/// TSingletonClass class is used to declare a singleton class.
///
////////////////////////////////////////////////////////////////////////////////


#include <pthread.h>

////////////////////////////////////////////////////////////////////////////////
///
/// @class TSingletonClass
///
/// This class is a common method to declare a singletion class.
///
////////////////////////////////////////////////////////////////////////////////
template <class T>
class TSingletonClass
{
    
public:
    
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Get class instance
    /// @return a reference of call instance
    ////////////////////////////////////////////////////////////////////////////
    static T& GetInstance()
    {
        // use the "double checked locking pattern"
        if (NULL == m_instance)
        {
            pthread_mutex_lock(&m_mutex);
            if (NULL == m_instance)
            {
                m_instance = new T;
            }
            pthread_mutex_unlock(&m_mutex);
        }
        return *m_instance;
    
    }
    
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Delete class instance. It is for test.
    /// @return none
    ////////////////////////////////////////////////////////////////////////////
    static void DeleteInstance()
    {
        // use the "double checked locking pattern"
        if (m_instance != NULL)
        {
            pthread_mutex_lock(&m_mutex);
            if (m_instance != NULL)
            {
                delete m_instance;
                m_instance = 0;
            }
            pthread_mutex_unlock(&m_mutex);
        }
    }

private:
    
    /// Forbid default constructor
    TSingletonClass();
    /// Forbid copy constructor
    TSingletonClass(const TSingletonClass&);
    /// Forbid assignment operator
    TSingletonClass& operator=(const TSingletonClass&);
    /// Forbid default destructor
    virtual ~TSingletonClass() {}

    /// unique class instance
    static T* volatile m_instance;

    /// pthread mutex
    static pthread_mutex_t m_mutex;
};

/// singleton class definition
#define SINGLETON_CLASS_INIT(T)\
template class TSingletonClass<T>;\
template<> T* volatile TSingletonClass<T>::m_instance=0;\
template<> pthread_mutex_t TSingletonClass<T>::m_mutex=PTHREAD_MUTEX_INITIALIZER;




#endif // __SINGLETON_HPP__

