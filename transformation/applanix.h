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
	void compare_gps_coosystem_degree_to_math_coosystem_pi(double &Roll,double &Pitch,double &Heading,double &sdRoll,double &sdPitch,double &sdHeading);
	double calc_approximately_meridian_convergence_degree(double Easting, double latitude, double &Heading);

	//void convert_angles_from_geographic_over_earth_frame_to_boby_frame(double &Roll,double &Pitch,double &Heading,double &sdRoll,double &sdPitch,double &sdHeading,double latitude,double longitude);

private:
	double m_meridian_convergence_dergee;
};

#endif /* APPLANIX_H_ */
