/*
 * applanix.cpp
 *
 *  Created on: 04.11.2009
 *      Author: steffen
 */

#include "applanix.h"

#include <cmath>

//project reference
//#include "rot_matrix_appl.h"
//#include "rot_matrix_transportation.h"

//extern matrix lib
#include "..//basics//matrix//matrix.h"
//#include "..//basics//rot_matrix.h" //old -> deprecated!!
#include "..//basics//fix_values.h"
#include "..//basics//point.h"

//new lib 21.10.2010
#include "..//basics//rotation_matrix.h"

Applanix::Applanix()
{
	m_meridian_convergence_rad = 0.0;
	m_false_easting               = 500000.0;
	m_small_half_axis              = 6371000.8;

}

Applanix::~Applanix()
{

}

//old function deprecated!! please use convert_from_geodetic_applanix_to_photogrammetric_rotation_angles !!
void Applanix::compare_gps_coosystem_degree_to_math_coosystem_pi(double &roll,double &pitch,double &heading,double &sdroll,double &sdpitch,double &sdheading)
{

		roll=roll/180.0*PI;
		pitch=pitch/180.0*PI;
		heading=heading/180.0*PI;

		sdroll=sdroll/180.0*PI;
		sdpitch=sdpitch/180.0*PI;
		sdheading=sdheading/180.0*PI;

		//cout<<endl<<"roll pitch heading old: "<<roll<<" "<<pitch<<" "<<heading;

		//body to geographic frame
		Rotation_matrix R_appl(Rotation_matrix::geodetic,roll,pitch,heading);

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
		Rotation_matrix R_opk(M_opk);
		R_opk.get_rotation_angle(Rotation_matrix::math,roll,pitch,heading);

		//cout<<endl<<"old rot end: "<<roll<<" "<<pitch<<" "<<heading;

}

double Applanix::calc_approximately_meridian_convergence_degree(double Easting, double latitude, double &Heading)
{   /*
      //for left hand coordinate system -> input the geographic heading and get the utm projection heading back
      m_meridian_convergence_dergee = (Easting - 500000) / 6371000.8 * tan(latitude/180.0*PI);
      //m_meridian_convergence_dergee = (Easting - 500000) /  6378137 * tan(latitude/180.0*PI);
      m_meridian_convergence_dergee = m_meridian_convergence_dergee/PI * 180.0;

      cout.precision(20);
      cout<<endl<<"m_meridian_convergence_dergee old: "<<m_meridian_convergence_dergee;
    */

  //for left hand coordinate system -> input the geographic heading and get the utm projection heading back
  m_meridian_convergence_rad = (Easting - m_false_easting) / m_small_half_axis * tan(latitude/180.0*PI);

  double m_meridian_convergence_dergee = m_meridian_convergence_rad/PI*180.0;

  Heading = Heading - m_meridian_convergence_dergee;

  //cout<<endl<<"Heading old: "<<Heading;

 return m_meridian_convergence_dergee;
}

Gps_pos Applanix::convert_from_geodetic_applanix_to_photogrammetric_rotation_angles(const Gps_pos &gps)
{
 //work copy
 Gps_pos gps_new;
 gps_new=gps;
            Point pos,rot;
            pos = gps_new.get_position();
            rot = gps_new.get_rotation();

            double lat,lo;
            lat = gps_new.get_Latitude();
            lo  = gps_new.get_Longitude();

/*
            //## convert angle [roll pitch heading] from degree to radiant ##
            rot = rot.DivS(180.0).MultS(PI);
            rot.set_dXYZ( rot.get_dXYZ().DivS(180.0).MultS(PI) );

            gps_new.set_rotation(rot);
            //## end convert angle from degree to radiant ##
*/

 //#### meridian convergence approximately ####
 //todo change to a clean mathematics solution /not approximate solution

    //for left hand coordinate system -> input the geographic heading and get the utm projection heading back
    m_meridian_convergence_rad = (gps.get_Easting() - m_false_easting) / m_small_half_axis * tan(gps.get_Latitude()/180.0*PI);



    //cout.precision(20);
     //cout<<endl<<"##### begin appl #####";

     //cout << endl <<"input gps coordinate without mc :"<<gps_new;


     //transform all standard deviations into the mathematics coordinate system
     //position standard deviation
     double r=0.0/180.0*PI,p=0.0/180.0*PI,h=-m_meridian_convergence_rad;//+2*PI;

     Rotation_matrix R_mc(Rotation_matrix::geodetic,r,p,h);
     //cout<<endl<<"rotation -> angle transform -> input: "<<r<<" "<<p<<" "<<h;

     //calc back
     //R_mc.get_rotation_angle(Rotation_matrix::geodetic,r,p,h);
     //cout.precision(20);
     //cout<<endl<<"rotation -> angle transform -> calc back: "<<r<<" "<<p<<" "<<h;


     Point pos_global = gps_new.get_position().MultS(0.0) , P0 ;
     //cout<<endl<<"position -> standard deviation point -> org          : "<<pos_global;

     Point pos_global_mc = pos_global.Rotation(P0,R_mc);
     //cout<<endl<<"position -> standard deviation point -> new transform: "<<pos_global_mc;

     //Point pos_global_mc_back = pos_global_mc.RotationRueck(P0,R_mc);
     //cout<<endl<<"position -> standard deviation point -> back         : "<<pos_global_mc_back;

     //set the new standard deviation
     gps_new.set_dEasting(pos_global_mc.get_dX());
     gps_new.set_dNorthing(pos_global_mc.get_dY());
     gps_new.set_dEllH(pos_global_mc.get_dZ());
     //cout <<endl << "gps_new :" << gps_new;


    //rotation standard deviation
    Point rotation = gps_new.get_rotation();
    //cout << endl << "rotation -> origin       : "<<rotation;
    Rotation_matrix R_rotation(Rotation_matrix::geodetic,rotation.get_X(),rotation.get_Y(),rotation.get_Z());
    Rotation_matrix R_rotation_back(R_rotation.get_Matrix().MatMult(R_mc));
    R_rotation_back.get_rotation_angle(Rotation_matrix::geodetic,r,p,h);
    //todo hack with the standard deviation normally you have to transform these values
    rot = Point(r,p,h,rot.get_dX(),rot.get_dY(),rot.get_dZ());
    //cout << endl << "rotation -> new transform: "<<rot;

    //########### !!attention versions control for old calibrations!! ##############
    if( (*this).get_version() == Applanix::s0002)
    {
      gps_new.set_Heading( gps_new.get_Heading() - m_meridian_convergence_rad );
      //cout << endl << "rotation -> old transform: "<<gps_new.get_rotation();
      cout << endl <<"info CApplanix -> set the old s0002 meridian convergence with the bug";
    }
    //########### !!attention versions control for old calibrations!! ##############
    //########### !!attention versions control for old calibrations!! ##############
    if( (*this).get_version() != Applanix::s0002)
    {
     gps_new.set_rotation(rot);
     //cout << endl << "rotation -> old transform: "<<gps_new.get_rotation();
     //cout << endl <<"info CApplanix -> set the s0003 meridian convergence";
     //todo rotation std with the meridian convergence
    }
    //########### !!attention versions control for old calibrations!! ##############

    //cout << endl <<"output gps coordinate with    mc :"<<gps_new;
    //cout<<endl<<"##### end appl #####";

    //#### end meridian convergence approximately ####



    //body to geographic frame
	//Rot_appl R_appl(gps_new.get_Roll(),gps_new.get_Pitch(),gps_new.get_Heading());
    Rotation_matrix R_appl(Rotation_matrix::geodetic,gps_new.get_Roll(),gps_new.get_Pitch(),gps_new.get_Heading());
    Rotation_matrix R_appl_std(Rotation_matrix::geodetic,gps_new.get_dRoll(),gps_new.get_dPitch(),gps_new.get_dHeading());

    //cout<<endl<<"angle transform rph : "<<gps_new.get_Roll()<<" "<<gps_new.get_Pitch()<<" "<<gps_new.get_Heading();
	Matrix M_appl;
	Matrix M_appl_std;
	M_appl = R_appl.get_Matrix();
	M_appl_std = R_appl_std.get_Matrix();

	//axes transformation matrix > is the same like (180°,0°,90°) rotation in the geodetic coordinate system
	//							    			or (0°,180°,-90°) rotation in the mathematics coordinate system
	Matrix M_axes(3,3,Null);
	M_axes(0,1) = 1;
	M_axes(1,0) = 1;
	M_axes(2,2) = -1;

	Matrix M_opk,M_opk_std;

	//transformation in body frame:  M_opk = ( M_axes_rl ).MatMult(M_appl)
	//second transformation is for the car coordinate system z- up, y in drive direction and x to the right side (mathematics coordinate system)
	M_opk = M_axes.MatMult(M_appl).MatMult(M_axes);
	M_opk_std = M_axes.MatMult(M_appl_std).MatMult(M_axes);

	double roll,pitch,heading;
	double roll_std,pitch_std,heading_std;

    //get the mathematics angels from the matrix
	//Rot R_opk(M_opk);
	//R_opk.get_RotWinkel(roll,pitch,heading);
	R_appl = M_opk;
	R_appl_std = M_opk_std;

	R_appl.get_rotation_angle(Rotation_matrix::math,roll,pitch,heading);
	R_appl_std.get_rotation_angle(Rotation_matrix::math,roll_std,pitch_std,heading_std);

	rot.set_X( roll );
	rot.set_Y( pitch );
	rot.set_Z( heading );
	rot.set_dX( (roll_std) );
	rot.set_dY( (pitch_std) );
	rot.set_dZ( (heading_std) );

	gps_new.set_rotation(rot);

return gps_new;
}

Gps_pos Applanix::convert_from_photogrammetric_to_geodetic_applanix_rotation_angles(Gps_pos const &gps)
{
 Gps_pos gps_new(gps);

 Point pos,rot;
 pos = gps.get_position();
 rot = gps.get_rotation();

 double lat,lo;
 lat = gps.get_Latitude();
 lo  = gps.get_Longitude();

 //cout << endl << "mc" << gps_new.get_Heading();

 //#### transformation back #####

 //get the mathematics angels from the matrix
	//Rot R_opk(gps_new.get_Roll(),gps_new.get_Pitch(),gps_new.get_Heading());
    Rotation_matrix R_opk(Rotation_matrix::math,gps_new.get_Roll(),gps_new.get_Pitch(),gps_new.get_Heading());
    Rotation_matrix R_opk_std(Rotation_matrix::math,gps_new.get_dRoll(),gps_new.get_dPitch(),gps_new.get_dHeading());

	Matrix M_opk,M_opk_std;
    M_opk = R_opk.get_Matrix();
    M_opk_std = R_opk_std.get_Matrix();

	//axes transformation matrix > is the same like (180°,0°,90°) rotation in the geodetic coordinate system
	//							    			or (0°,180°,-90°) rotation in the mathematics coordinate system
	Matrix M_axes(3,3,Null);
	M_axes(0,1) = 1;
	M_axes(1,0) = 1;
	M_axes(2,2) = -1;


	Matrix M_appl,M_appl_std;

    //Mappl <<<<< M_opk = M_axes.MatMult(M_appl).MatMult(M_axes);
    //M_opk.MatMult(M_axes.MatInvert()) = M_axes.MatMult(M_appl);
    M_appl = M_axes.MatInvert().MatMult(M_opk).MatMult(M_axes.MatInvert());
    M_appl_std = M_axes.MatInvert().MatMult(M_opk_std).MatMult(M_axes.MatInvert());

	double roll,pitch,heading;
	double roll_std,pitch_std,heading_std;

	//cout << endl << "M_appl" << M_appl;

	//body to geographic frame
	//Rot_appl R_appl(M_appl);
	R_opk = M_appl;
	R_opk_std = M_appl_std;

	//R_appl.get_RotWinkel(roll,pitch,heading);
	R_opk.get_rotation_angle(Rotation_matrix::geodetic,roll,pitch,heading);
	R_opk_std.get_rotation_angle(Rotation_matrix::geodetic,roll_std,pitch_std,heading_std);

	//Rot_appl R_appl_(roll,pitch,heading);

	rot.set_X( roll );
	rot.set_Y( pitch );
	rot.set_Z( heading );
	rot.set_dX( (roll_std) );
    rot.set_dY( (pitch_std) );
    rot.set_dZ( (heading_std) );

	gps_new.set_rotation(rot);


    //#### meridian convergence approximately ####
      //todo change to a mathematics solution
     m_meridian_convergence_rad = (gps.get_Easting() - m_false_easting) / m_small_half_axis * tan(gps.get_Latitude()/180.0*PI);
    //#### end meridian convergence approximately ####


    //gps_new.set_rotation(rot);
    //cout.precision(20);
    //cout<<endl<<"##### begin appl #####";

    //cout << endl <<"input gps coordinate without mc :"<<gps_new;


    //transform all standard deviations into the mathematics coordinate system
    //position standard deviation
    double r=0.0/180.0*PI,p=0.0/180.0*PI,h=m_meridian_convergence_rad;//+2*PI;

    Rotation_matrix R_mc(Rotation_matrix::geodetic,r,p,h);
    //cout<<endl<<"rotation -> angle transform -> input: "<<r<<" "<<p<<" "<<h;

    //calc back
    //R_mc.get_rotation_angle(Rotation_matrix::geodetic,r,p,h);
    //cout.precision(20);
    //cout<<endl<<"rotation -> angle transform -> calc back: "<<r<<" "<<p<<" "<<h;


    Point pos_global = gps_new.get_position().MultS(0.0) , P0 ;
    //cout<<endl<<"position -> standard deviation point -> org          : "<<pos_global;

    Point pos_global_mc = pos_global.Rotation(P0,R_mc);
    //cout<<endl<<"position -> standard deviation point -> new transform: "<<pos_global_mc;

    //Point pos_global_mc_back = pos_global_mc.RotationRueck(P0,R_mc);
    //cout<<endl<<"position -> standard deviation point -> back         : "<<pos_global_mc_back;

    //set the new standard deviation
    gps_new.set_dEasting(pos_global_mc.get_dX());
    gps_new.set_dNorthing(pos_global_mc.get_dY());
    gps_new.set_dEllH(pos_global_mc.get_dZ());
    //cout <<endl << "gps_new :" << gps_new;


   //rotation standard deviation
   Point rotation = gps_new.get_rotation();
   //cout << endl << "rotation -> origin       : "<<rotation;
   Rotation_matrix R_rotation(Rotation_matrix::geodetic,rotation.get_X(),rotation.get_Y(),rotation.get_Z());
   Rotation_matrix R_rotation_back(R_rotation.get_Matrix().MatMult(R_mc));
   R_rotation_back.get_rotation_angle(Rotation_matrix::geodetic,r,p,h);
   //todo hack with the standard deviation normally you have to transform these values
   rot = Point(r,p,h,rot.get_dX(),rot.get_dY(),rot.get_dZ());
   //cout << endl << "rotation -> new transform: "<<rot;

   //########### !!attention versions control for old calibrations!! ##############
   if( (*this).get_version() == Applanix::s0002)
   {
     gps_new.set_Heading( gps_new.get_Heading() + m_meridian_convergence_rad );
     //cout << endl << "rotation -> old transform: "<<gps_new.get_rotation();
     cout << endl <<"info CApplanix -> set the old s0002 meridian convergence with the bug";
   }
   //########### !!attention versions control for old calibrations!! ##############
   //########### !!attention versions control for old calibrations!! ##############
   if( (*this).get_version() != Applanix::s0002)
   {
    gps_new.set_rotation(rot);
    //cout << endl << "rotation -> old transform: "<<gps_new.get_rotation();
    //cout << endl <<"info CApplanix -> set the s0003 meridian convergence";
    //todo rotation std with the meridian convergence
   }
   //########### !!attention versions control for old calibrations!! ##############

   //cout << endl <<"output gps coordinate with    mc :"<<gps_new;
   //cout<<endl<<"##### end appl #####";


return gps_new;
}

double Applanix::get_meridian_convergence_dergee(){return m_meridian_convergence_rad/PI*180.0;}
double Applanix::get_false_easting(){return m_false_easting;}
double Applanix::get_small_half_axis(){return m_small_half_axis;}

void Applanix::set_false_easting(double v){m_false_easting=v;}
void Applanix::set_small_half_axis(double v){m_small_half_axis=v;}

