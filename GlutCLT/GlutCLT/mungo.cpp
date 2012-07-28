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
        Coords t1 = m_one->GetCoordsAtTime( time );
        Coords t2 = m_two->GetCoordsAtTime( time );
        Coords temp = ( t1 + t2 ) / 2.;
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