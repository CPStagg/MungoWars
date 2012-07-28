//============================================================================
// Name        : mungo.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "mungo.h"
#include "ratioramp.h"

#include <iostream>
#include <math.h>
using namespace std;

Mungo::Mungo()
{
	static int s_UniqueID = 0;
	m_UniqueID = s_UniqueID++;

	// cout << "+++ CREATED NEW MUNGO of ID " << m_UniqueID << endl;
}

Mungo::~Mungo()
{
	// cout << "--- DELETED A MUNGO of ID " << m_UniqueID << endl;
}

// -----------------------------

class OrbitAroundMungo: public Mungo
{
public:
    OrbitAroundMungo( const MungoCPtr& planet, double radius, double period )
    {
        m_planet = planet;
        m_radius = radius;
        m_period = period;
    }
    
    virtual Coords GetCoordsAtTime( double time ) const
    {
        double timePeriod = fmod( time, m_period );
        double angle = ( timePeriod / m_period ) * 3.1412 * 2.0;
        
        Coords p1 = m_planet->GetCoordsAtTime( time );
        double xval = cos( angle ) * m_radius;
        double yval = sin( angle ) * m_radius; 
        Coords relative_position = Coords(xval, yval);
        Coords temp = p1 + relative_position;
        return temp;
    }
private:
    MungoCPtr m_planet;
    double m_radius, m_period;
};

// -----------------------------

class HalfWayBetweenMungo: public Mungo
{
public:
    HalfWayBetweenMungo( const MungoCPtr& one, const MungoCPtr& two)
    {
        m_one = one;
        m_two = two;
    }
    
    virtual Coords GetCoordsAtTime( double time ) const
    {
        Coords m1 = m_one->GetCoordsAtTime( time );
        Coords m2 = m_two->GetCoordsAtTime( time );
        Coords temp = ( m1 + m2 ) / 2.;
        return temp;
    }
    
private:
    MungoCPtr m_one;
    MungoCPtr m_two;
};

// -----------------------------

class StaticMungo : public Mungo
{
public:
    StaticMungo( const Coords& coords )
    {
        m_Coords = coords;
    }
    
    virtual Coords GetCoordsAtTime( double time ) const { return m_Coords; }
    
private:
    Coords m_Coords;
};

// -----------------------------

class LinearMoveMungo : public Mungo
{
public:
    LinearMoveMungo( const Coords& start, const Coords& finish, 
                     double startTime, double endTime )
    {
        m_Start = start;
        m_Finish = finish;
        m_StartTime = startTime;
        m_EndTime = endTime; 
    }
    
    virtual Coords GetCoordsAtTime( double time ) const
    {
        RatioRamp timeRamp( m_StartTime, m_EndTime );
        double ratio = timeRamp.RatioFromValue( time );
        Coords shift = m_Finish - m_Start;
        return m_Start + ( shift * ratio );
    }
    
private:
    Coords m_Start, m_Finish;
    double m_StartTime, m_EndTime;
};

// --------------------------------

class TemporalOffset : public Mungo
{
public:
    TemporalOffset( MungoCPtr offsetTarget, double timeOffset )
    :   m_Target( offsetTarget ), m_Offset( timeOffset ) {}
    
    virtual Coords GetCoordsAtTime( double time ) const
    {
        return m_Target->GetCoordsAtTime( time + m_Offset );
    }
    
private:
    MungoCPtr   m_Target;
    double      m_Offset;
};

// --------------------------------

void MungoManager::AddMungo( MungoCPtr ptr )
{
    m_List.AddItem(ptr);
}
    
int MungoManager::nMungos() const
{
    return m_List.nEntries();
}

void MungoManager::GetCoords( int iMungo, double time, Coords* pCoords ) const
{
    *pCoords = m_List.GetItem( iMungo )->GetCoordsAtTime( time );
}

// ----------------------------

// static
MungoCPtr MungoFactory::CreateStaticMungo( const Coords& coords )
{
    return new StaticMungo( coords );
}

// static
MungoCPtr MungoFactory::CreateLinearMungo( const Coords& start, const Coords& end,
                                        double startTime, double endTime )
{
    return new LinearMoveMungo( start, end, startTime, endTime );
}

// static
MungoCPtr MungoFactory::CreateTemporalOffset( MungoCPtr offsetTarget, double timeOffset )
{
    return new TemporalOffset( offsetTarget, timeOffset );
}

// static
MungoCPtr MungoFactory::CreateHalfWayBetween( MungoCPtr one, MungoCPtr two )
{
    return new HalfWayBetweenMungo( one, two );
}

// static
MungoCPtr MungoFactory::CreateOrbitAroundMungo( MungoCPtr planet, double radius, double period )
{
    return new OrbitAroundMungo( planet, radius, period );
}