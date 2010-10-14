/*
 * applanix.h
 *
 *  Created on: 04.11.2009
 *      Author: steffen
 */

#ifndef APPLANIX_H_
#define APPLANIX_H_

#include <iostream>

//lib photogrammetrie
#include "..//position//gps_pos.h"


class CApplanix
{
public:
	CApplanix();
	virtual ~CApplanix();

	//chabge the orientation form the applanix system to the photogrammetric module and back
	//TODO !!!!!!!!

	//convertion only in one direction (old style)
	void compare_gps_coosystem_degree_to_math_coosystem_pi(double &Roll,double &Pitch,double &Heading,double &sdRoll,double &sdPitch,double &sdHeading);
	double calc_approximately_meridian_convergence_degree(double Easting, double latitude, double &Heading);

	//new functions for transformation geodetic <-> math
	Gps_pos convert_from_geodetic_applanix_grad_to_math_photogrammetric_pi(Gps_pos &gps);
	Gps_pos convert_from_math_photogrammetric_pi_to_geodetic_applanix_grad(Gps_pos &gps);

	double get_meridian_convergence_dergee();
	double get_false_easting();
	double get_smal_half_axis();

	void set_false_easting(double v);
	void set_smal_half_axis(double v);


private:
	double m_meridian_convergence_dergee;
	double m_false_easting;
	double m_smal_half_axis;
};

#endif /* APPLANIX_H_ */
