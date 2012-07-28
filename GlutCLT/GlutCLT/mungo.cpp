//============================================================================
// Name        : mungo.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "mungo.h"

#include <iostream>
using namespace std;

Mungo::Mungo()
{
	static int s_UniqueID = 0;
	m_UniqueID = s_UniqueID++;

	cout << "+++ CREATED NEW MUNGO of ID " << m_UniqueID << endl;
}

Mungo::~Mungo()
{
	cout << "--- DELETED A MUNGO of ID " << m_UniqueID << endl;
}

void Mungo::TellMeStuff()
{
	cout << "My name is Mungo" << endl;
}

void Mungo::TellMeMoreStuff()
{
	cout << "I enjoy weasels" << endl;
}

// -----------------------------

Bongo::Bongo()
{
	cout << "++++++ CREATED NEW BONGO!" << endl;
}

Bongo::~Bongo()
{
	cout << "------ DELETED A BONGO!" << endl;
}

void Bongo::TellMeMoreStuff()
{
	cout << "I enjoy raspberries" << endl;
}

// --------------------------------


// static
MungoCPtr MungoFactory::CreateBasicMungo()
{
	return new Mungo;
}
