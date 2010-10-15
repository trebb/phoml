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
//#include "rot_matrix_transportation.h"

//extern matrix lib
#include "..//basics//matrix//matrix.h"
#include "..//basics//rot_matrix.h"
#include "..//basics//fix_values.h"
#include "..//basics//point.h"

CApplanix::CApplanix()
{
	m_meridian_convergence_dergee = 0.0;
	m_false_easting               = 500000;
	m_smal_half_axis              = 6371000.8;

}

CApplanix::~CApplanix()
{

}

void CApplanix::compare_gps_coosystem_degree_to_math_coosystem_pi(double &roll,double &pitch,double &heading,double &sdroll,double &sdpitch,double &sdheading)
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


															//test variable
														  // double w1,w2,w3;

								/*
															R_appl.get_RotWinkel(w1,w2,w3);
															cout<<endl<< "   roll    :"<<w1/PI*180.0;
																  cout<< "   pitch   :"<<w2/PI*180.0;
																  cout<< "   heading :"<<w3/PI*180.0;
								*/

										/*

												  //test
												  Rot_appl R_appl_w(M_appl);
												  R_appl_w.get_RotWinkel(w1,w2,w3);
													cout<<endl<< "   roll    :"<<w1/PI*180.0;
														  cout<< "   pitch   :"<<w2/PI*180.0;
														  cout<< "   heading :"<<w3/PI*180.0;

										*/
										/*
										//test
										//geographic frame to earth frame -> is included in the applanix output file not necessary
										Rot_transport R_transport( longitude,latitude );
										Matrix M_transport;
										M_transport = R_transport.get_Matrix();


														  Rot_transport R_transport_w(M_transport);
														  R_transport_w.get_RotWinkel(w1,w2);
															cout<<endl<< "   lat    :"<<w1/PI*180.0;
																  cout<< "   lon   :"<<w2/PI*180.0;

																  Rot_appl R_appl_tranport(M_transport);
																R_appl_tranport.get_RotWinkel(w1,w2,w3);

																cout<<endl<< "   roll    :"<<w1/PI*180.0;
																	  cout<< "   pitch   :"<<w2/PI*180.0;
																	  cout<< "   heading :"<<w3/PI*180.0;

										*/


		//axes transformation matrix > is the same like (180°,0°,90°) rotation in the geodetic coordinate system
		//							    			or (0°,180°,-90°) rotation in the mathematics coordinate system
		Matrix M_axes(3,3,Null);
		M_axes(0,1) = 1;
		M_axes(1,0) = 1;
		M_axes(2,2) = -1;


		//Rot_appl R_n90(180.0/180.0*PI ,0.0/180.0*PI ,90.0/180.0*PI );
		//Matrix M_n90 = R_n90.get_Matrix();

		Matrix M_opk;

		//transformation in body frame:  M_opk = ( M_axes_rl ).MatMult(M_appl)
		//second transformation is for the car coordinate system z- up, y in drive direction and x to the right side (mathematics coordinate system)
		M_opk = M_axes.MatMult(M_appl).MatMult(M_axes);

        //get the mathematics angels from the matrix
		Rot R_opk(M_opk);
		R_opk.get_RotWinkel(roll,pitch,heading);

}

double CApplanix::calc_approximately_meridian_convergence_degree(double Easting, double latitude, double &Heading)
{
  //for left hand coordinate system -> input the geographic heading and get the utm projection heading back
  m_meridian_convergence_dergee = (Easting - 500000) / 6371000.8 * tan(latitude/180.0*PI);
  //m_meridian_convergence_dergee = (Easting - 500000) /  6378137 * tan(latitude/180.0*PI);
  m_meridian_convergence_dergee = m_meridian_convergence_dergee/PI * 180.0;

  Heading = Heading - m_meridian_convergence_dergee;

 return m_meridian_convergence_dergee;
}

Gps_pos CApplanix::convert_from_geodetic_applanix_grad_to_math_photogrammetric_pi(Gps_pos &gps)
{
 Gps_pos gps_new(gps);

 Point pos,rot;
 pos = gps.get_position_geod();
 rot = gps.get_rotation();

 double lat,lo;
 lat = gps.get_Latitude();
 lo  = gps.get_Longitude();

 rot.set_X( rot.get_X() / 180.0*PI );
 rot.set_Y( rot.get_Y() / 180.0*PI );
 rot.set_Z( rot.get_Z() / 180.0*PI );
 rot.set_dX( rot.get_dX() / 180.0*PI );
 rot.set_dY( rot.get_dY() / 180.0*PI );
 rot.set_dZ( rot.get_dZ() / 180.0*PI );

 gps_new.set_rotation(rot);

    //body to geographic frame
	Rot_appl R_appl(gps_new.get_Roll(),gps_new.get_Pitch(),gps_new.get_Heading());

	Matrix M_appl;
	M_appl = R_appl.get_Matrix();

	cout << endl << "M_appl" << M_appl;

	//axes transformation matrix > is the same like (180°,0°,90°) rotation in the geodetic coordinate system
	//							    			or (0°,180°,-90°) rotation in the mathematics coordinate system
	Matrix M_axes(3,3,Null);
	M_axes(0,1) = 1;
	M_axes(1,0) = 1;
	M_axes(2,2) = -1;

	Matrix M_opk;

	//transformation in body frame:  M_opk = ( M_axes_rl ).MatMult(M_appl)
	//second transformation is for the car coordinate system z- up, y in drive direction and x to the right side (mathematics coordinate system)
	M_opk = M_axes.MatMult(M_appl).MatMult(M_axes);

	//cout << endl << "M_opk" << M_opk;

	double roll,pitch,heading;

    //get the mathematics angels from the matrix
	Rot R_opk(M_opk);
	R_opk.get_RotWinkel(roll,pitch,heading);

	rot.set_X( roll );
	rot.set_Y( pitch );
	rot.set_Z( heading );
	gps_new.set_rotation(rot);

	//cout << endl << "mc" << gps_new.get_Heading();

	//#### meridian convergence approximately ####

	  //for left hand coordinate system -> input the geographic heading and get the utm projection heading back
	  m_meridian_convergence_dergee = (gps.get_Easting() - m_false_easting) / m_smal_half_axis * tan(gps.get_Latitude()/180.0*PI);
	  m_meridian_convergence_dergee = m_meridian_convergence_dergee/PI * 180.0;

	  gps_new.set_Heading( gps_new.get_Heading() - m_meridian_convergence_dergee );


return gps_new;
}

Gps_pos CApplanix::convert_from_math_photogrammetric_pi_to_geodetic_applanix_grad(Gps_pos &gps)
{
 Gps_pos gps_new(gps);

 Point pos,rot;
 pos = gps.get_position_geod();
 rot = gps.get_rotation();

 double lat,lo;
 lat = gps.get_Latitude();
 lo  = gps.get_Longitude();

 m_meridian_convergence_dergee = (gps.get_Easting() - m_false_easting) / m_smal_half_axis * tan(gps.get_Latitude()/180.0*PI);
 m_meridian_convergence_dergee = m_meridian_convergence_dergee/PI * 180.0;

 gps_new.set_Heading( gps_new.get_Heading() + m_meridian_convergence_dergee );

 //cout << endl << "mc" << gps_new.get_Heading();

 //#### transformation back #####

 //get the mathematics angels from the matrix
	Rot R_opk(gps_new.get_Roll(),gps_new.get_Pitch(),gps_new.get_Heading());

	Matrix M_opk;
    M_opk = R_opk.get_Matrix();

    //cout << endl << "M_opk" << M_opk;


	//axes transformation matrix > is the same like (180°,0°,90°) rotation in the geodetic coordinate system
	//							    			or (0°,180°,-90°) rotation in the mathematics coordinate system
	Matrix M_axes(3,3,Null);
	M_axes(0,1) = 1;
	M_axes(1,0) = 1;
	M_axes(2,2) = -1;


	Matrix M_appl;

	//transformation in body frame:  M_opk = ( M_axes_rl ).MatMult(M_appl)
	//second transformation is for the car coordinate system z- up, y in drive direction and x to the right side (mathematics coordinate system)
//umstellen nach Mappl <<<<< M_opk = M_axes.MatMult(M_appl).MatMult(M_axes);
    //M_opk.MatMult(M_axes.MatInvert()) = M_axes.MatMult(M_appl);
    M_appl = M_axes.MatInvert().MatMult(M_opk).MatMult(M_axes.MatInvert());

	double roll,pitch,heading;

	cout << endl << "M_appl" << M_appl;

	//body to geographic frame
	Rot_appl R_appl(M_appl);
	R_appl.get_RotWinkel(roll,pitch,heading);

	Rot_appl R_appl_(roll,pitch,heading);

	cout << endl << "M_appl_rück" << R_appl_;


	rot.set_X( roll );
	rot.set_Y( pitch );
	rot.set_Z( heading );
	gps_new.set_rotation(rot);


	 rot.set_X( rot.get_X() / PI*180.0 );
	 rot.set_Y( rot.get_Y() / PI*180.0 );
	 rot.set_Z( rot.get_Z() / PI*180.0 );
	 rot.set_dX( rot.get_dX() / PI*180.0 );
	 rot.set_dY( rot.get_dY() / PI*180.0 );
	 rot.set_dZ( rot.get_dZ() / PI*180.0 );

	 gps_new.set_rotation(rot);


return gps_new;
}

double CApplanix::get_meridian_convergence_dergee(){return m_meridian_convergence_dergee;}
double CApplanix::get_false_easting(){return m_false_easting;}
double CApplanix::get_smal_half_axis(){return m_smal_half_axis;}

void CApplanix::set_false_easting(double v){m_false_easting=v;}
void CApplanix::set_smal_half_axis(double v){m_smal_half_axis=v;}

