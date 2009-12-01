/*
 * applanix.cpp
 *
 *  Created on: 04.11.2009
 *      Author: steffen
 */

#include "applanix.h"

#include <cmath>

//project reference
#include "rot_matrix_appl.h"

//extern matrix lib
#include "..//..//Basics//Matrix//matrix.h"
#include "..//..//Basics//rot_matrix.h"
#include "..//..//Basics//fix_values.h"
#include "..//..//Basics//point.h"

CApplanix::CApplanix()
{
	m_meridian_convergence_dergee = 0.0;

}

CApplanix::~CApplanix()
{

}

void CApplanix::convert_angles_UTM_to_math_coo_system(double &roll,double &pitch,double &heading,double &sdroll,double &sdpitch,double &sdheading)
{
    roll=roll/180.0*PI;
		pitch=pitch/180.0*PI;
		heading=heading/180.0*PI;

		sdroll=sdroll/180.0*PI;
		sdpitch=sdpitch/180.0*PI;
		sdheading=sdheading/180.0*PI;


		//body to geographic frame
		Rot_appl R_appl(roll,pitch,heading);

		Matrix M_appl;
		M_appl = R_appl.get_Matrix();


		//axes right and left hand
				Matrix M_axes_rl(3,3,Null);
				M_axes_rl(0,1) = 1;
				M_axes_rl(1,0) = 1;
				M_axes_rl(2,2) = -1;

		Matrix M_opk;
		M_opk = M_axes_rl.MatMult(M_appl);

		Rot R_opk(M_opk);
		R_opk.get_RotWinkel(roll,pitch,heading);



		//transformation the standard deviation

				Rot R_math(roll,pitch,heading);
				Matrix M_math;
				M_math = R_math.get_Matrix();

				Matrix M_rot;
				M_rot = M_math.MatMult(M_appl);

				Point mP(sdroll,sdpitch,sdheading);
		        Point null;

				Point mP_new = mP.Rotation(null,M_rot);
}

double CApplanix::calc_approximately_meridian_convergence_degree(double Easting, double latitude, double &Heading)
{
  //for left hand coordinate system -> input the geographic heading and get the utm projection heading back
  m_meridian_convergence_dergee = (Easting - 500000) / 6371000.8 * tan(latitude/180.0*PI);
  //m_meridian_convergence_dergee = (Easting - 500000) /  6378137 * tan(latitude/180.0*PI);
  m_meridian_convergence_dergee = m_meridian_convergence_dergee/PI * 180.0;

  Heading = Heading + m_meridian_convergence_dergee;

 return m_meridian_convergence_dergee;
}
