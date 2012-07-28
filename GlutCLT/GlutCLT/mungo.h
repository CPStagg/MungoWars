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
    Coords operator / ( double divisor ) const { return Coords( x / divisor, y / divisor); }
    
    double x, y;
};

struct TimePosPair
{
    Coords m_Pos;
    double m_Time;
};

typedef List< TimePosPair > TimePosSequence;

// ---------------------------------------

struct MColor
{
    MColor() : r(0.0), g(0.0), b(0.0) {}
    MColor( double ir, double ig, double ib ) : r( ir ), g ( ig ), b( ib ) {}

    double r,g,b;
};


// ---------------------------------------

class Mungo : public Referenced
{
public:
	Mungo();
	~Mungo();
    
    virtual Coords  GetCoordsAtTime( double time ) const = 0;
    
    void    AssignColor( MColor col ) { m_Color = col; }
    MColor  GetColor() const { return m_Color; }

private:

	int m_UniqueID;
    MColor m_Color;
};

typedef CountedPtr< Mungo > MungoCPtr;

// ---------------------------------------

class MungoFactory
{
public:
    static MungoCPtr CreatePathFollower( const TimePosSequence& );
	static MungoCPtr CreateStaticMungo( const Coords& );
    static MungoCPtr CreateLinearMungo( const Coords& start, const Coords& end,
                                        double startTime, double endTime );
    static MungoCPtr CreateTemporalOffset( MungoCPtr offsetTarget, double timeOffset );
    static MungoCPtr CreateHalfWayBetween( MungoCPtr one, MungoCPtr two );

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
    
    // PRE( iMungo < nMungos() );
    const Mungo& GetMungo( int iMungo ) const;
    
    
private:
    MungoList m_List;
};

#endif // __MUNGO_H__
