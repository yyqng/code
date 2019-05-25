#ifndef __AUTO_CLOSE_PTR_H__
#define __AUTO_CLOSE_PTR_H__

// 自动释放指针指向的动态内�?
// 使用此类�?TypePtr 必须提供一个成员函�?Close()
template <class TypePtr>
class AutoClosePtr
{
public :
	explicit AutoClosePtr(TypePtr *p = NULL)
        : m_ptr(p)
	{
	}

	AutoClosePtr(AutoClosePtr &obj)
		: m_ptr(obj.release())
	{

	}

	~AutoClosePtr()
	{
		if(m_ptr != NULL)
		{
			try
			{
				m_ptr->Close();
			}
			catch( ... )
			{
			}

			delete m_ptr;
		}
	}

public :

	AutoClosePtr& operator= (AutoClosePtr &obj)
	{
		if( &obj != this )
		{
			if( m_ptr != NULL )
			{
				m_ptr->Close();
				delete m_ptr;
			}

			m_ptr = obj.release();
		}

		return *this;
	}

	AutoClosePtr& operator= (TypePtr *ptr)
	{
		if(m_ptr != ptr)
		{
			if(m_ptr != NULL)
			{
				m_ptr->Close();
				delete m_ptr;
			}

			m_ptr = ptr;
		}

		return *this;
	}

	bool operator != (TypePtr *ptr)
	{
		if( m_ptr != ptr )
		{
			return true;
		}

		return false;
	}

	TypePtr& operator* () const
	{
		return *m_ptr;
	}

	TypePtr* operator-> () const
	{
		return m_ptr;
	}

	TypePtr* get() const 
	{
		return m_ptr;
	}

	TypePtr* release()
	{
		TypePtr *p = m_ptr;
		m_ptr = NULL;
		return p;
	}

	void reset(TypePtr *p) 
	{
		if( m_ptr != NULL )
		{
			m_ptr->Close();
			delete m_ptr;
		}

		m_ptr = p;
	}

private :
	TypePtr *m_ptr;

};

#endif  // __AUTO_CLOSE_PTR_H__
