 //============================================================================
// Name        : mungolist.h
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef __SIMPLEARRAY_H__
#define	__SIMPLEARRAY_H__

#include "CPSassert.h"

// ---------------------------------------

#define MAX_SIZE 128

template< class T > class SimpleArray
{
public:

	SimpleArray()
	:	m_Count( 0 )
	{

	}

	int		Count() const
	{
		return m_Count;
	}

	void 	Add( T* pT )
	{
		PRE( m_Count < MAX_SIZE )

		m_Elements[ m_Count++ ] == pT;
	}

	T*			pGet( int index )
	{
		PRE( index < Count() )
		PRE( index >= 0 )

		return m_Elements[ index ];
	}
	const T&	Get( int index ) const
	{
		SimpleArray< T >* pNonConstThis = const_cast< SimpleArray<T>* >( this );
		return *( pNonConstThis->pGet( index ) );
	}

private:

	T* 		m_Elements[ MAX_SIZE ];
	int		m_Count;
};

#endif // __SIMPLEARRAY_H__
