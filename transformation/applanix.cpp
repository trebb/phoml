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
#include "..//Basics//Matrix//matrix.h"
#include "..//Basics//rot_matrix.h"
#include "..//Basics//fix_values.h"
#include "..//Basics//point.h"

CApplanix::CApplanix()
{
	m_meridian_convergence_dergee = 0.0;

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

