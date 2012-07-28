 //============================================================================
// Name        : countedpointer.h
// Author      : 
// Version     :
// Copyright   : Professor C.P.Stagg
// Description : I am great
//============================================================================

#ifndef __COUNTEDPOINTER_H__
#define	__COUNTEDPOINTER_H__

#include "CPSassert.h"

// ---------------------------------------

class Referenced
{
public:
						Referenced			();
	virtual				~Referenced			();

	bool				HasReference		() const;
	int					ReferenceCount		() const;

	int					AddReference		( void* );
	bool				ReleaseReference	( void* );

private:
	// Data members
	int				mReferenceCount;
	virtual         void DoAddReference( void*, int /*newReferences*/ ) {}
    virtual         void DoReleaseReference( void*, int /*newReferences*/ ) {}
};

//--------------------------------------------------------------------------
// Referenced
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
inline Referenced::Referenced()
: mReferenceCount(0)
{
    // empty
}

//--------------------------------------------------------------------------
inline Referenced::~Referenced()
{
	// ASSERT(!HasReference() || !Axiom::Memory::IsMemoryInAddressSpace(this));
}

//--------------------------------------------------------------------------
inline bool Referenced::HasReference() const
{
	return 0 != mReferenceCount;
}

//--------------------------------------------------------------------------
inline int Referenced::ReferenceCount() const
{
	return mReferenceCount;
}

// #define CALL_DEBUG_TRACKING_METHODS

//--------------------------------------------------------------------------
inline int Referenced::AddReference( void* /*pVoid*/ )
{
	/*
#ifdef CALL_DEBUG_TRACKING_METHODS
    DoAddReference( pVoid, mReferenceCount + 1 );
#endif
	*/
	return ++mReferenceCount;
}

//--------------------------------------------------------------------------
inline bool Referenced::ReleaseReference( void* /*pVoid*/ )
{
	/*
#ifdef CALL_DEBUG_TRACKING_METHODS
    DoReleaseReference( pVoid, mReferenceCount - 1 );
#endif
	*/

	ASSERT(mReferenceCount > 0);
	const int count = --mReferenceCount;
	return 0 == count;
}

// ---------------------------------------

template <typename T> class CountedPtr
{
public:

    CountedPtr();
    CountedPtr( T* pT );
    CountedPtr( const CountedPtr& xRef );
	CountedPtr<T>& operator = ( const CountedPtr<T>& xRef );

	~CountedPtr();

	void			Set( T* pT );
	void			Clear();
	void			ClearPointerWithoutDeleting();

    bool			IsValid() const;

    bool			operator == ( const CountedPtr<T>& xRef ) const;
    bool            operator != ( const CountedPtr<T>& xRef ) const;

    inline const T*		pVal() const;
    inline T*			pVal();

	// PRE( IsValid() )
    const T&		Val() const;

    T*				operator->();
    T*				operator->() const;

	// PRE( IsValid() )
    const T&		operator * () const;
    T&		        operator * ();

private:

    void			AddRefIfNotNull();
    void			ReleaseIfNotNull();

	// Data member..
    T*				m_pT;

};


//-------------------------------------------------------------------------------------------------------------
template<typename T>
CountedPtr<T>::CountedPtr()
:   m_pT( NULL )
{
    // Empty method body
}

//-------------------------------------------------------------------------------------------------------------
template<typename T>
CountedPtr<T>::CountedPtr( T* pT )
:   m_pT( pT )
{
    AddRefIfNotNull();
}

//-------------------------------------------------------------------------------------------------------------
template<typename T>
CountedPtr<T>::CountedPtr( const CountedPtr& xRef )
{
    m_pT = xRef.m_pT;
    AddRefIfNotNull();
}

//-------------------------------------------------------------------------------------------------------------
template<typename T>
CountedPtr<T>::~CountedPtr()
{
    ReleaseIfNotNull();
}

//-------------------------------------------------------------------------------------------------------------
template<typename T> bool CountedPtr<T>::IsValid() const
{
    return m_pT != NULL;
}

//-------------------------------------------------------------------------------------------------------------
template<typename T> CountedPtr<T>& CountedPtr<T>::operator = ( const CountedPtr<T>& xRef )
{
    ReleaseIfNotNull();
    m_pT = xRef.m_pT;
    AddRefIfNotNull();
    return *this;

    /////////////
}

//-------------------------------------------------------------------------------------------------------------

template<typename T>
void CountedPtr<T>::Set( T* pT )
{
    ReleaseIfNotNull();
    m_pT = pT;
    AddRefIfNotNull();
}

template<typename T>
void CountedPtr<T>::Clear()
{
    ReleaseIfNotNull();
    m_pT = NULL;
}

template<typename T>
void CountedPtr<T>::ClearPointerWithoutDeleting()
{
    m_pT = NULL;
}

//-------------------------------------------------------------------------------------------------------------
template<typename T> bool CountedPtr<T>::operator == ( const CountedPtr<T>& xRef ) const
{
    return m_pT == xRef.m_pT;
}

//-------------------------------------------------------------------------------------------------------------
template<typename T>
bool CountedPtr<T>::operator != ( const CountedPtr<T>& xRef ) const
{
    return m_pT != xRef.m_pT;
}

//-------------------------------------------------------------------------------------------------------------
template<typename T>
const T* CountedPtr<T>::pVal() const
{
    return m_pT;
}

//-------------------------------------------------------------------------------------------------------------
template<typename T>
T* CountedPtr<T>::pVal()
{

    return m_pT;
}

//-------------------------------------------------------------------------------------------------------------
template<typename T>
const T& CountedPtr<T>::Val() const
{
    PRE( IsValid() );
    return *m_pT;
}

//-------------------------------------------------------------------------------------------------------------
template<typename T>
T* CountedPtr<T>::operator->()
{
	ASSERT(IsValid());
    return m_pT;
}

//-------------------------------------------------------------------------------------------------------------
template<typename T>
T* CountedPtr<T>::operator->() const
{
	ASSERT(IsValid());
    return m_pT;
}

//-------------------------------------------------------------------------------------------------------------
template<typename T>
const T& CountedPtr<T>::operator * () const
{
    PRE( IsValid() );
    return Val();
}

//-------------------------------------------------------------------------------------------------------------
template<typename T>
T& CountedPtr<T>::operator * ()
{
    PRE( IsValid() );
    return *( pVal() );
}

//-------------------------------------------------------------------------------------------------------------
template<typename T>
void CountedPtr<T>::AddRefIfNotNull()
{
    if( IsValid() )
    {
        m_pT->AddReference( this );
    }
}

//-------------------------------------------------------------------------------------------------------------
template<typename T>
void CountedPtr<T>::ReleaseIfNotNull()
{
    if( IsValid() && m_pT->ReleaseReference( this ) )
    {
		// ASSERT( Axiom::Memory::IsMemoryInAddressSpace(m_pT) );

		delete( m_pT );
    }
}

#endif // __COUNTEDPOINTER_H__
