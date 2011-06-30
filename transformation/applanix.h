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
#include "..//basics//fix_values.h"
#include "..//position//gps_pos.h"


class Applanix : public Fix_values
{
public:
	Applanix();
	virtual ~Applanix();

	//convertion only in one direction (old style)
	void compare_gps_coosystem_degree_to_math_coosystem_pi(double &Roll,double &Pitch,double &Heading,double &sdRoll,double &sdPitch,double &sdHeading);
	double calc_approximately_meridian_convergence_degree(double Easting, double latitude, double &Heading);

	//new functions for transformation geodetic <-> math
	Gps_pos convert_from_geodetic_applanix_to_photogrammetric_rotation_angles(const Gps_pos &gps);
	Gps_pos convert_from_photogrammetric_to_geodetic_applanix_rotation_angles(const Gps_pos &gps);

	double get_meridian_convergence_dergee();

	//get/set values for the current coordinate system (default UTM-WGS84) to calculate the approximate meridian convergence
	double get_false_easting();
	double get_small_half_axis();

	void set_false_easting(double v);
	void set_small_half_axis(double v);


private:
	double m_meridian_convergence_rad;
	double m_false_easting;
	double m_small_half_axis;
};

#endif /* APPLANIX_H_ */
