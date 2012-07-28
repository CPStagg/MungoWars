//============================================================================
// Name        : mungo.h
// Author      : Professor C P Stagg
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef __MUNGO_H__
#define	__MUNGO_H__

#include "countedpointer.h"
#include "mungolist.h"

// ---------------------------------------

struct Coords
{
    Coords() : x( 0.0 ), y (0.0 ) {}
    Coords( double ix, double iy ) : x( ix ), y ( iy ) {}
    
    Coords operator + ( const Coords& xRef ) const { return Coords( x + xRef.x, y + xRef.y ); }
    Coords operator - ( const Coords& xRef ) const { return Coords( x - xRef.x, y - xRef.y ); }
    Coords operator * ( double ratio ) const { return Coords( x * ratio, y * ratio ); }
    
    double x, y;
};

// ---------------------------------------

class Mungo : public Referenced
{
public:
	Mungo();
	~Mungo();
    
    virtual Coords  GetCoordsAtTime( double time ) const = 0;

private:

	int m_UniqueID;
};

typedef CountedPtr< Mungo > MungoCPtr;

// ---------------------------------------

class MungoFactory
{
public:
	static MungoCPtr CreateStaticMungo( const Coords& );
    static MungoCPtr CreateLinearMungo( const Coords& start, const Coords& end,
                                        double startTime, double endTime );
};

// ---------------------------------------

typedef List< MungoCPtr > MungoList;

// ---------------------------------------

class MungoManager
{
public:
    void    AddMungo( MungoCPtr );
    
    int     nMungos() const;
    void    GetCoords( int iMungo, double time, Coords* ) const;
private:
    MungoList m_List;
};

#endif // __MUNGO_H__
