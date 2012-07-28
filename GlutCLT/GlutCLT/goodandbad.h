//============================================================================
// Name        : goodandbad.h
// Author      : Professor C P Stagg
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef __GOODANDBAD_H__
#define	__GOODANDBAD_H__

#include <string>

// ------------------ NOT SO VERY BAD ---------------------

class AbstractMonster
{
public:
	AbstractMonster( const std::string& name ) : m_Name( name ) {}
    virtual int 	OverallPower() const = 0;
	std::string		GetName() const { return m_Name; }
private:
	std::string		m_Name;
};

class DragonSeparate : public AbstractMonster
{
public:
	DragonSeparate( const std::string& name )
	: 	AbstractMonster( name )
	{}
	virtual int OverallPower() const { return 10; }
};

class GremlinSeparate : public AbstractMonster
{
public:
	GremlinSeparate( const std::string& name )
	: 	AbstractMonster( name )
	{}
	virtual int OverallPower() const { return 8; }
};

class OgreSeparate : public AbstractMonster
{
public:
	OgreSeparate( const std::string& name )
	: 	AbstractMonster( name )
	{}
	virtual int OverallPower() const { return 6; }
};

class WizardSeparate : public AbstractMonster
{
public:
	WizardSeparate( const std::string& name )
	: 	AbstractMonster( name )
	{}
	virtual int OverallPower() const { return 4; }
};

void DoCalculationWithAbstractClass();


#endif // __GOODANDBAD_H__
