//============================================================================
// Name        : test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "mungo.h"
#include "goodandbad.h"

#include <iostream>
using namespace std;

// Foward declare auxilliary functions
void DoStuffWithCountedPointers();
void DoStuffWithMungos();
void DoStuffWithMungoList();

// --------------------------

int main() {

	DoStuffWithCountedPointers();

	// DoStuffWithMungos();
        // DoCalculationWithAbstractClass();

	return 0;
}

// --------------------------

// --------------------------

void PrintMessage( int n = 5 )
{
	cout << "Your number was " << n << endl;
}

// --------------------------

void DoStuffWithMungos()
{
	cout << "!!!Hello World eeee!!!" << endl; // prints !!!Hello World!!!
	Mungo m;
	m.TellMeStuff();
	m.TellMeMoreStuff();
	Bongo b;
	b.TellMeStuff();
	b.TellMeMoreStuff();

	Mungo* pMungo1 = new Mungo();

	delete pMungo1;
}

// --------------------------

void CreateSecondMungo()
{
	MungoCPtr cpMungo2 = MungoFactory::CreateBasicMungo();

	cpMungo2->TellMeStuff();
}

void DoStuffWithCountedPointers()
{
	MungoCPtr cpMungo1 = MungoFactory::CreateBasicMungo();

	CreateSecondMungo();
}


