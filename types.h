//Types.h

#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <boost/multiprecision/mpfr.hpp>
#include <boost/math/constants/constants.hpp>

namespace Types{

	using float_precision = boost::multiprecision::mpfr_float_50;

}

namespace constants{
	
	//PI value
	inline const Types::float_precision pi = boost::math::constants::pi<Types::float_precision>();
		
	//Conversion from radians to degrees
	inline const Types::float_precision rad2deg = (180/pi);

}


#endif // TYPES_H_INCLUDED

