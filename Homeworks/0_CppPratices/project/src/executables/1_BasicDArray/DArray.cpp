// implementation of class DArray
#include "DArray.h"
#include <iostream>

// default constructor
DArray::DArray() 
{
	Init();
}

// set an array with default values
DArray::DArray(int nSize, double dValue) 
{
	m_pData	= new double [nSize];// creat a new nSize array
	m_nSize	= nSize;

	double *p_ite = m_pData;
	
	for (int i = 0; i < m_nSize; i++)
	{
		*p_ite = dValue;
		p_ite++;
	}
}

// copy constructor
DArray::DArray(const DArray& arr) 
{
	m_pData	= new double[arr.GetSize()];
	m_nSize = arr.GetSize();

	for (int i = 0; i < m_nSize; i++)
	{
		this[i] = arr[i];
	}// end for
}

// deconstructor
DArray::~DArray() 
{
	Free();
}

// display the elements of the array
void DArray::Print() const 
{
	double *p_ite = m_pData;
	
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

// initilize the array
void DArray::Init() 
{
	m_nSize	= 0;
	m_pData	= nullptr;
}

// free the array
void DArray::Free() 
{
	m_nSize = 0;
	delete[] m_pData;
}

// get the size of the array
int DArray::GetSize() const 
{
	return m_nSize;
}

// set the size of the array
void DArray::SetSize(int nSize) 
{
	if (nSize == m_nSize)
	{
		return;
	}

	//when nSize <= 0, delete the array
	if (nSize <= 0)
	{
		Free();
		return;
	}

	// creat a new array whose length is nSize and a iterator aiming to its head
	double *p_d_array	= new double [nSize];
	double *p_d_ite		= p_d_array; 
	
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
	m_nSize = nSize;
	m_pData = p_d_array;
}

// get an element at an index
const double& DArray::GetAt(int nIndex) const 
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
void DArray::SetAt(int nIndex, double dValue) 
{
	if ((nIndex > m_nSize) || (nIndex < 0))
	{
		std::cout << "erro: index out of range" << std::endl;
		return;
	}// end if

	*(m_pData + nIndex) = dValue;
}

// overload operator '[]'
const double& DArray::operator[](int nIndex) const 
{
	return GetAt(nIndex);
}

// add a new element at the end of the array
void DArray::PushBack(double dValue) 
{
	SetSize(m_nSize + 1);
	*(m_pData + m_nSize - 1) = dValue;
}

// delete an element at some index
void DArray::DeleteAt(int nIndex) 
{
	SetSize(m_nSize - 1);
}

// insert a new element at some index
void DArray::InsertAt(int nIndex, double dValue) 
{
	// out-of-range check
	if ((nIndex < 0) || (nIndex > m_nSize))
	{
		std::cout << "erro: index out of range" << std::endl;
		return;
	}// end if

	PushBack(dValue);
	
	// temp double for swap numbers
	double temp = 0.0;

	// insert the last double to (nIndex)th
	for (int i = m_nSize - 1; i > nIndex; i--)
	{
		temp = *(m_pData + i - 1);
		*(m_pData + i - 1) = *(m_pData + i);
		*(m_pData + i) = temp;
	}// end for
}

// overload operator '='
DArray& DArray::operator = (const DArray& arr) 
{
	Free();
	return *this;
}
