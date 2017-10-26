#pragma once
template < class T>
class CSingleton
{protected: 
	static T* m_single;
public:
	static T* getInstance() {
		if (m_single == nullptr)
			m_single = new T;
		return m_single;
	}
	virtual~CSingleton();
};
template <class T>
T* CSingleton<T>::m_single = nullptr;

template<class T>
inline CSingleton<T>::~CSingleton()
{
}
