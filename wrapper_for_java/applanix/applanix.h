/*
 * applanix.h
 *
 *  Created on: 04.11.2009
 *      Author: steffen
 */

#ifndef APPLANIX_H_
#define APPLANIX_H_

#include <iostream>


class CApplanix
{
public:
	CApplanix();
	virtual ~CApplanix();

	//chabge the orientation form the applanix system to the photogrammetric module and back
	//TODO !!!!!!!!

	//convertion only in one direction
	void convert_angles_UTM_to_math_coo_system(double &Roll,double &Pitch,double &Heading,double &sdRoll,double &sdPitch,double &sdHeading);
	double calc_approximately_meridian_convergence_degree(double Easting, double latitude, double &Heading);

private:
	double m_meridian_convergence_dergee;
};

#endif /* APPLANIX_H_ */
