#include "mainwrapperjava.h"

#include "..//photo//forward_intersection.h"
#include "..//boresight_alignment//boresight_transformation.h"
#include "..//basics//fix_values.h"
#include "..//transformation//applanix.h"

CMainWrapperJava::CMainWrapperJava()
{
}

CMainWrapperJava::~CMainWrapperJava()
{
}

Point CMainWrapperJava::get_3D_Point_local(CBPointList BPlist)
{
	Vorwaertsschnitt FWS(BPlist.m_BPoint_List);

	return FWS.get_Schnittpunkt().DivS(1000.0);
}

BPoint CMainWrapperJava::get_BPoint_from_local_3D_Point(Point P_local,Cam_bore cam)
{
  return BPoint(cam,P_local.get_X()*1000.0,P_local.get_Y()*1000.0,P_local.get_Z()*1000.0);
}

Point CMainWrapperJava::get_3D_Point_global(Point P_local_in_m,Cam_bore cam, double E, double N, double eH, double roll, double pitch, double heading)
{
	Boresight_transformation bore(cam);

	double mroll=0.0,mpitch=0.0,mheading=0.0;

	Applanix appl;
	//appl.calc_approximately_meridian_convergence_degree(E,latitude,Hea);
	appl.compare_gps_coosystem_degree_to_math_coosystem_pi(roll,pitch,heading,mroll,mpitch,mheading);

	//bore.set_car_position_global(E,N,eH,rroll,rpitch,rheading);
	bore.set_car_position_global(E,N,eH,roll,pitch,heading);

	bore.set_local_coordinate(P_local_in_m.get_X(),P_local_in_m.get_Y(),P_local_in_m.get_Z());

 return bore.get_global_coordinate();
}

Point CMainWrapperJava::get_3D_Point_local(Point P_global_E_N_eH_in_m,Cam_bore cam, double E, double N, double eH, double roll, double pitch, double heading)
{
	Boresight_transformation bore(cam);

	double mroll=0.0,mpitch=0.0,mheading=0.0;

	Applanix appl;
	//appl.calc_approximately_meridian_convergence_degree(E,latitude,Hea);
	appl.compare_gps_coosystem_degree_to_math_coosystem_pi(roll,pitch,heading,mroll,mpitch,mheading);


	//bore.set_car_position_global(E,N,eH,rroll,rpitch,rheading);
	bore.set_car_position_global(E,N,eH,roll,pitch,heading);

	bore.set_global_coordinate(P_global_E_N_eH_in_m.get_X(),P_global_E_N_eH_in_m.get_Y(),P_global_E_N_eH_in_m.get_Z());

	return bore.get_local_coordinate();
}

//new functions with approximately meridian convergence 27/11/2009

Point CMainWrapperJava::get_3D_Point_global_wMC(Point P_local_in_m,Cam_bore cam, double E, double N, double eH, double roll, double pitch, double heading,double latitude,double longitude)
{
	Boresight_transformation bore(cam);

	double mroll=0.0,mpitch=0.0,mheading=0.0;

	Applanix appl;
	appl.calc_approximately_meridian_convergence_degree(E,latitude,heading);
	appl.compare_gps_coosystem_degree_to_math_coosystem_pi(roll,pitch,heading,mroll,mpitch,mheading);

	bore.set_car_position_global(E,N,eH,roll,pitch,heading);

	bore.set_local_coordinate(P_local_in_m.get_X(),P_local_in_m.get_Y(),P_local_in_m.get_Z());

 return bore.get_global_coordinate();
}

Point CMainWrapperJava::get_3D_Point_local_wMC(Point P_global_E_N_eH_in_m,Cam_bore cam, double E, double N, double eH, double roll, double pitch, double heading,double latitude,double longitude)
{
	Boresight_transformation bore(cam);

	double mroll=0.0,mpitch=0.0,mheading=0.0;

	Applanix appl;
	appl.calc_approximately_meridian_convergence_degree(E,latitude,heading);
	appl.compare_gps_coosystem_degree_to_math_coosystem_pi(roll,pitch,heading,mroll,mpitch,mheading);

	bore.set_car_position_global(E,N,eH,roll,pitch,heading);

	bore.set_global_coordinate(P_global_E_N_eH_in_m.get_X(),P_global_E_N_eH_in_m.get_Y(),P_global_E_N_eH_in_m.get_Z());

	return bore.get_local_coordinate();
}

