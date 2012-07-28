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

template< class T > class MungoList
{
public:

	int	nMungos() const;

	void 	AddMungo( Mungo* );
	Mungo*	GetMungo( int index );

private:

	Mungo* m_Mungos[ 128 ];
};

#endif // __MUNGOLIST_H__
