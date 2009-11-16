#include "mainwrapperjava.h"

#include "../Photo/forward_intersection.h"
#include "../boreside_alignement/boreside_transformation.h"
#include "../Basics/fix_values.h"

#include "applanix//applanix.h"

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

BPoint CMainWrapperJava::get_BPoint_from_local_3D_Point(Point P_local,CCam_bore cam)
{
  return BPoint(cam,P_local.get_X()*1000.0,P_local.get_Y()*1000.0,P_local.get_Z()*1000.0);   	
}

Point CMainWrapperJava::get_3D_Point_global(Point P_local_in_m,CCam_bore cam, double E, double N, double eH, double roll, double pitch, double heading)
{
	CBoreside_transformation bore(cam);
/*
	double rroll,rpitch,rheading;
	rroll	= -(roll)/180.0*PI;	
	rpitch	= -(pitch)/180.0*PI;
	
		if(heading<=180.0)
			rheading= (-heading);
		else
			rheading= (360.0-heading);
		
	rheading= (rheading)/180.0*PI;
*/
	double mroll=0.0,mpitch=0.0,mheading=0.0;
	
	CApplanix appl;
	//appl.calc_approximately_meridian_convergence_degree(E,latitude,Hea);
	appl.convert_angles_UTM_to_math_coo_system(roll,pitch,heading,mroll,mpitch,mheading);

	//bore.set_car_position_utm(E,N,eH,rroll,rpitch,rheading);
	bore.set_car_position_utm(E,N,eH,roll,pitch,heading);
		
	bore.set_local_koordinate(P_local_in_m.get_X(),P_local_in_m.get_Y(),P_local_in_m.get_Z());
	
 return bore.get_utm_koordinate();
}

Point CMainWrapperJava::get_3D_Point_local(Point P_global_E_N_eH_in_m,CCam_bore cam, double E, double N, double eH, double roll, double pitch, double heading)
{
	CBoreside_transformation bore(cam);
/*
	double rroll,rpitch,rheading;
	rroll	= -(roll)/180.0*PI;	
	rpitch	= -(pitch)/180.0*PI;
	
		if(heading<=180.0)
			rheading= (-heading);
		else
			rheading= (360.0-heading);
		
	rheading= (rheading)/180.0*PI;
*/
	double mroll=0.0,mpitch=0.0,mheading=0.0;

	CApplanix appl;
	//appl.calc_approximately_meridian_convergence_degree(E,latitude,Hea);
	appl.convert_angles_UTM_to_math_coo_system(roll,pitch,heading,mroll,mpitch,mheading);

	
	//bore.set_car_position_utm(E,N,eH,rroll,rpitch,rheading);
	bore.set_car_position_utm(E,N,eH,roll,pitch,heading);
	
	bore.set_utm_koordinate(P_global_E_N_eH_in_m.get_X(),P_global_E_N_eH_in_m.get_Y(),P_global_E_N_eH_in_m.get_Z());
	
	return bore.get_local_koordinate();
}
	
