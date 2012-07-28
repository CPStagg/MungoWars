//============================================================================
// Name        : mungo.h
// Author      : Professor C P Stagg
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef __CPSASSERT_H__
#define	__CPSASSERT_H__

#include <assert.h>

// ---------------------------------------

#define ASSERT( __test ) assert( (__test ) );
#define PRE( __test ) ASSERT( __test )
#define POST( __test ) ASSERT( __test )

#endif // __CPSASSERT_H__
