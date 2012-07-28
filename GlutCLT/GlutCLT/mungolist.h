//============================================================================
// Name        : mungolist.h
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef __MUNGOLIST_H__
#define	__MUNGOLIST_H__
// ---------------------------------------

template< class T > class List
{
public:

    List() : m_Size( 0 ) {}

	int	nEntries() const
    {
        return m_Size;
    }

	void 	AddItem( T t )
    {
        m_Elements[ m_Size++ ] = t;
    }
    // PRE( index < nEntries() );
	const T&      GetItem( int index ) const
    {
        PRE( index < nEntries() );
        
        return m_Elements[ index ];
    }

private:

	T   m_Elements[ 128 ];
    int m_Size;
};

#endif // __MUNGOLIST_H__
