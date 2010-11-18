#ifndef MAINWRAPPERJAVA_H_
#define MAINWRAPPERJAVA_H_

#include "../basics/point.h"
#include "../photo/bpoint.h"
#include "../boresight_alignment/cam_bore.h"

//Java wrapper
#include "CBPointList.h"

class CMainWrapperJava
{
public:
	CMainWrapperJava();
	virtual ~CMainWrapperJava();

	//divide into two steps local and global (utm) functions
	
	//local funktions (camera coordinate system) (in [m])
	
	//forwart intersection
	//put 2 or more BPoints into the list with differend Cameras
	//and get a 3D Point back
	Point get_3D_Point_local(CBPointList BPlist);
	
	//put a 3D Point into the funktion and get a BPoint from the camera back
	//then you can visualisation the 3D Point in the picture
	BPoint get_BPoint_from_local_3D_Point(Point P_local,Cam_bore cam);
	
	
	//global funktions (boreside in [m]) in UTM coordinates if the Car position also in UTM, angels [roll,pitch,heading] in old degree 
	//(applanix like: roll pitch in mathematic direction and heading in geodetic direction ;-))
	
	//put the local 3D Point from get_3D_Point_local(), the camera_calibration
	// cam_bore and the car position (Esting,Northing,ellHieght,roll,pitch,heading) inside
	// and get the UTM coordinate of the local Point
	Point get_3D_Point_global(Point P_local_in_m,Cam_bore cam, double Easting, double Northing, double eHeigth, double roll, double pitch, double heading);
	Point get_3D_Point_global_wMC(Point P_local_in_m,Cam_bore cam, double Easting, double Northing, double eHeigth, double roll, double pitch, double heading,double latitude,double longitude);

	//put a global 3D Point Point(Easting,Northing,eHeight), the camera_calibration
	// cam_bore and the car position (Esting,Northing,ellHieght,roll,pitch,heading) inside
	// and get the local 3D coordinates of the global Point
	Point get_3D_Point_local(Point P_global_E_N_eH_in_m,Cam_bore cam, double Easting, double Northing, double eHeigth, double roll, double pitch, double heading);
	Point get_3D_Point_local_wMC(Point P_global_E_N_eH_in_m,Cam_bore cam, double Easting, double Northing, double eHeigth, double roll, double pitch, double heading,double latitude,double longitude);

};

#endif /*MAINWRAPPERJAVA_H_*/
