//============================================================================
// Name        : goodandbad.h
// Author      : Professor C P Stagg
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "goodandbad.h"

#include <iostream>
#include "CPSassert.h"

using namespace std;

bool ADefeatsB( const AbstractMonster& a,  const AbstractMonster& b )
{
	return a.OverallPower() > b.OverallPower();
}

bool ATiesB( const AbstractMonster& a,  const AbstractMonster& b )
{
	return a.OverallPower() == b.OverallPower();
}

void TriggerFight( const AbstractMonster& a, const AbstractMonster& b )
{
	cout << a.GetName() << " fights " << b.GetName() << endl;

	const AbstractMonster* pWinner;

	if( ADefeatsB( a, b ) )
	{
		pWinner = &a;
	}
	else if( ADefeatsB( b, a ) )
	{
		pWinner = &b;
	}
	else
	{
		cout << "It's a tie!" << endl;
		return;
	}

	cout << pWinner -> GetName() << " wins!" << endl;

}

void DoCalculationWithAbstractClass()
{
	DragonSeparate 	daveTheDragon( "Dave" );
	OgreSeparate	oliveTheOgre( "Olive" );
	GremlinSeparate	garyTheGremlin( "Gary" );
	WizardSeparate wallyTheWizard( "Wally");

	TriggerFight( daveTheDragon, oliveTheOgre );
	TriggerFight( garyTheGremlin, oliveTheOgre );
	TriggerFight( garyTheGremlin, daveTheDragon );
	TriggerFight( wallyTheWizard, garyTheGremlin );
}

// -----------------------------


