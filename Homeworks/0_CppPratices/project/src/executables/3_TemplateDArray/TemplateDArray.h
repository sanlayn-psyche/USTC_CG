#pragma once

// interfaces of Dynamic Array class DArray
template<typename T>
class TemplateDArray {
public:
	TemplateDArray(); // default constructor
	TemplateDArray(int nSize, T dValue = 0); // set an array with default values
	TemplateDArray(const TemplateDArray<T>& arr); // copy constructor
	~TemplateDArray(); // deconstructor

	void Print() const; // print the elements of the array

	int GetSize() const; // get the size of the array
	void SetSize(int nSize); // set the size of the array

	const T& GetAt(int nIndex) const; // get an element at an index
	void SetAt(int nIndex, T dValue); // set the value of an element

	T& operator[](int nIndex); // overload operator '[]'
	const T& operator[](int nIndex) const; // overload operator '[]'

	void PushBack(T dValue); // add a new element at the end of the array
	void DeleteAt(int nIndex); // delete an element at some index
	void InsertAt(int nIndex, T dValue); // insert a new element at some index

	TemplateDArray<T>& operator = (const TemplateDArray<T>& arr); //overload operator '='

private:
	T* m_pData; // the pointer to the array memory
	int m_nSize; // the size of the array
	int m_nMax;

private:
	void Init(); // initilize the array
	void Free(); // free the array
	void Reserve(int nSize); // allocate enough memory
};

template<typename T>
TemplateDArray<T>::TemplateDArray()
{
	Init();
}

template<typename T>
TemplateDArray<T>::TemplateDArray(int nSize, T tValue)
{
	m_pData	= new T [nSize];// creat a new nSize array
	m_nSize	= nSize;
	m_nMax = nSize;

	double *p_ite = m_pData;
	
	for (int i = 0; i < m_nSize; i++)
	{
		*p_ite = dValue;
		p_ite++;
	}
}

template<typename T>
TemplateDArray<T>::TemplateDArray(const TemplateDArray<T>& arr)
{
	m_pData	= new T[arr.GetSize()];
	m_nSize = arr.GetSize();
	m_nMax = m_nSize;

	for (int i = 0; i < m_nSize; i++)
	{
		this[i] = arr[i];
	}// end for
}

template<typename T>
TemplateDArray<T>::~TemplateDArray()
{
	Free();
}

// print the elements of the array
template<typename T>
void TemplateDArray<T>::Print() const
{
	T *p_ite = m_pData;
	
	if (m_nSize > 0)
	{
		for (int i = 0; i < m_nSize; i++)
		{
			std::cout << *p_ite << " ";
			p_ite++;
		}// end for
		std::cout << std::endl;
	}
	else
	{
		std::cout << "erro: empty array" <<std::endl;	
	}//end if
}

// get the size of the array
template<typename T>
int TemplateDArray<T>::GetSize() const
{
	return m_nSize;
} 

// set the size of the array
template<typename T>
void TemplateDArray<T>::SetSize(int nSize)
{
	if (nSize <= m_nMax)
	{
		m_nSize = nSize > 0 ? nSize : 0;
		return;
	}

	// creat a new array whose length is nSize and a iterator aiming to its head
	T *p_d_array	= new T [nSize];
	T *p_d_ite		= p_d_array; 
	
	//set i_min the smaller integer of m_nSize and nSize
	int i_min = nSize > m_nSize ? m_nSize : nSize;

	for (int i = 0; i < i_min; i++)
	{
		*p_d_ite = this->GetAt(i);
		p_d_ite++;
	}

	for (int i = i_min; i < nSize; i++)
	{
		*p_d_ite = 0.0;
		p_d_ite++;
	}
	
	Free();
	m_nSize = i_min;
	m_nMax = nSize;
	m_pData = p_d_array;
}

// get an element at an index
template<typename T>
const T& TemplateDArray<T>::GetAt(int nIndex) const
{
	// out-of-range check
	if ((nIndex > m_nSize) || (nIndex < 0))
	{
		std::cout << "erro: index out of range" << std::endl;
		return *(m_pData);
	}// end if

	return *(m_pData + nIndex);
}

// set the value of an element
template<typename T>
void TemplateDArray<T>::SetAt(int nIndex, T dValue)
{
	if ((nIndex > m_nSize) || (nIndex < 0))
	{
		std::cout << "erro: index out of range" << std::endl;
		return;
	}// end if

	*(m_pData + nIndex) = dValue;
}

// overload operator '[]'
template<typename T>
T& TemplateDArray<T>::operator[](int nIndex)
{
	// out-of-range check
	if ((nIndex > m_nSize) || (nIndex < 0))
	{
		std::cout << "erro: index out of range" << std::endl;
		return *m_pData;
	}// end if

	return *(m_pData + nIndex);
}

// overload operator '[]'
template<typename T>
const T& TemplateDArray<T>::operator[](int nIndex) const
{
	return GetAt(nIndex);
}

// add a new element at the end of the array
template<typename T>
void TemplateDArray<T>::PushBack(T dValue)
{
	if (m_nSize < m_nMax)
	{
		*(m_pData + m_nSize) = dValue;
		m_nSize++;
	}
	else
	{
		if (m_nMax < 1)
		{
			m_nMax = 1;
			m_nSize = 1;
			m_pData = new double(dValue);
		}
		else
		{
			this->SetSize(2*m_nMax);
			*(m_pData + m_nSize) = dValue;
			m_nSize++;
		}// end if
	}// end if
}

// delete an element at some index
template<typename T>
void TemplateDArray<T>::DeleteAt(int nIndex)
{
	// out-of-range check
	if ((nIndex < 0) || (nIndex >= m_nSize))
	{
		std::cout << "erro: out of range" << std::endl;
		return;
	}

	if (m_nSize <= 0)
	{
		std::cout << "erro: empty array, there's no element to delete" << std::endl;
		return;
	}

	T t_temp;

	for (int i = m_nSize - 1; i > nIndex; i--)	
	{
		t_temp = *(m_pData + i);
		*(m_pData + i) = *(m_pData + i - 1);
		*(m_pData + i - 1) = t_temp;
	}

	m_nSize--;
}

// insert a new element at some index
template<typename T>
void TemplateDArray<T>::InsertAt(int nIndex, T dValue)
{
	// out-of-range check
	if ((nIndex < 0) || (nIndex > m_nSize))
	{
		std::cout << "erro: index out of range" << std::endl;
		return;
	}// end if

	PushBack(dValue);
	
	// temp double for swap numbers
	T t_temp;

	// insert the last double to (nIndex)th
	for (int i = m_nSize - 1; i > nIndex; i--)
	{
		t_temp = *(m_pData + i - 1);
		*(m_pData + i - 1) = *(m_pData + i);
		*(m_pData + i) = t_temp;
	}// end for
}

// T& TemplateDArray<T>::operator[](int nIndex)
// TemplateDArray& operator = (const TemplateDArray& arr);

//overload operator '='
template<typename T>
TemplateDArray<T>& TemplateDArray<T>::operator = (const TemplateDArray<T>& arr)
{
	Free();
	m_pData	= new T[arr.GetSize()];
	m_nSize = arr.GetSize();
	m_nMax = m_nSize;

	for (int i = 0; i < m_nSize; i++)
	{
		this[i] = arr[i];
	}// end for
	return *this;
}

// initilize the array
template<typename T>
void TemplateDArray<T>::Init()
{
	m_nSize	= 0;
	m_pData	= nullptr;
	m_nMax = 0;
}

// free the array
template<typename T>
void TemplateDArray<T>::Free() 
{
	m_nSize = 0;
	m_nSize = 0;
	delete[] m_pData;
}