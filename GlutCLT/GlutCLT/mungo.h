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

// ---------------------------------------

class Mungo : public Referenced
{
public:
	Mungo();
	~Mungo();

	void TellMeStuff();
	virtual void TellMeMoreStuff();

private:

	int	m_nFeet;
	int m_UniqueID;
};

typedef CountedPtr< Mungo > MungoCPtr;

class MungoFactory
{
public:
	static MungoCPtr CreateBasicMungo();
};

// ---------------------------------------

class Bongo : public Mungo
{
public:
	Bongo();
	~Bongo();

	virtual void TellMeMoreStuff();

private:

	int	m_nHeads;
};

#endif // __MUNGO_H__
