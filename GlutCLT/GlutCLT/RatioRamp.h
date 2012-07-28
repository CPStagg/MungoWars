#include "CPSassert.h"

class RatioRamp
{	
public:

    RatioRamp( double min, double max )
	{
		PRE( min <= max );
		
		m_Min = min;
    	m_Max = max;
	}

    double Min() const
	{
		return m_Min;
	}
	
    double Max() const
	{
		return m_Max;	
	}

    // 
    double RatioFromValue( double value ) const
	{
		double result = 0.0;

	    if( value >= m_Min )
	    {
	        if( value >= m_Max )
	        {
	            result = 1.0f;
	        }
	        else
	        {
	            result = ( value - m_Min ) / ( m_Max - m_Min );
	        }
	    }

		POST( result >= 0.0 && result <= 1.0f );
		
		return result;
	}
    
    // 
    double ValueFromRatio( double ratio )
	{
		PRE( ratio >= 0.0 && ratio <= 1.0f );
			
		double result = m_Min + ( ratio * ( m_Max - m_Min ) );
		
		double EPSILON = 0.00000001f;
		
		ASSERT( GreaterEqualRelative( result, Min(), EPSILON ) && LessEqualRelative( result, Max(), EPSILON ) );
	
        if( result < Min() ) result = Min();
            if( result > Max() ) result = Max();
			
    	POST( result >= Min() && result <= Max() );
		
		return result;
	}
	
    // If you pass through 0.3f, will return the same value as calling ValueFromRatio( 0.7f ) 
    double ValueFromRatioComplement( double ratio )
	{
		PRE( ratio >= 0.0 && ratio <= 1.0f );
		
		double result = ValueFromRatio( 1.0f - ratio );
		
    	POST( result >= Min() && result <= Max() );
		
		return result;
	}
    
    // outputMin can be higher than outputMax; we'll just interpolate happily between the two
    static double ConvertUsingDualRamps( double inputMin, double inputMax, double outputBegin, double outputEnd, double input )
	{
		PRE( inputMax >= inputMin );
		
		RatioRamp inputRamp( inputMin, inputMax );
	    double inputAsRatio = inputRamp.RatioFromValue( input );
	    double output = 0.0;
	    
	    if( outputBegin > outputEnd )
	    {
	        RatioRamp outputRamp( outputEnd, outputBegin );
	        output = outputRamp.ValueFromRatio( 1.0f - inputAsRatio );
	    }
	    else
	    {
	        RatioRamp outputRamp( outputBegin, outputEnd );
	        output = outputRamp.ValueFromRatio( inputAsRatio );
	    }
	    
	    return output;
	}
	
	bool GreaterEqualRelative( double test, double comparison, double differenceAllowed )
	{
		return ( test - comparison ) >= -differenceAllowed;
	}
	
	bool LessEqualRelative( double test, double comparison, double differenceAllowed )
	{
		return ( test - comparison ) <= differenceAllowed;
	}

private:
    double   m_Min = 0.0;
    double   m_Max = 0.0;
};
