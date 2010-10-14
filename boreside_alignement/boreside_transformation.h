#ifndef BORESIDE_TRANSFORMATION_H_
#define BORESIDE_TRANSFORMATION_H_

#include "..//Basics//point.h"
#include "..//Basics//Matrix//matrix.h"
#include "..//Basics//rot_matrix.h"
#include "..//position//gps_pos.h"
#include "cam_bore.h"


class CBoreside_transformation
{
	
public:
	CBoreside_transformation(CCam_bore &cam);
	CBoreside_transformation(CCam_bore &cam,double Easting,double Northing,double ell_Height,double roll,double pitch,double heading);
	CBoreside_transformation(CCam_bore &cam,Gps_pos &Pos);

	virtual ~CBoreside_transformation();
	
	void set_car_position_utm(double Easting,double Northing,double ell_Height,double roll,double pitch,double heading);
	void set_car_position_utm(Gps_pos &Pos);
	
	void set_utm_koordinate(double Easting,double Northing,double ell_Height);  //[Esting,Northing,Height]
	void set_utm_koordinate(Point &utm);  //[Esting,Northing,Height]
	void set_local_koordinate(double local_X,double local_Y,double local_Z);    //[X,Y,Z]
	void set_local_koordinate(Point &local);    //[X,Y,Z]

	
	Point get_utm_koordinate(); //[Easting,Northing,Height]
	Point get_local_koordinate();//[X,Y,Z]
	
	
private:
	void fill_params_outer_bore();
	void fill_params_utm();
	
	// camera setup
	CCam_bore m_cam;
	
	// position of the car
	double m_Easting,m_Northing,m_ell_Height,m_roll,m_pitch,m_heading;
	
	//standard deviation of car position
	double m_dEasting,m_dNorthing,m_dell_Height,m_droll,m_dpitch,m_dheading;


	//cam koordinate system (sensor right-x , up-y  (z-> right hand )  )
	//unit: [m]
	//transformation setup
	Point  m_translation_cam;
	Matrix m_rotation_cam;
	
	//car koordinate system (car plattform x-right side , y-forward (z->right hand))
	//unit: [m]
	//transformation setup
	Point  m_translation_car;
	Matrix m_rotation_car;
	
	//gps koordinate system (UTM WGS84 [m])
	//unit: [m]
	//transformation setup
	Point  m_translation_utm;
	Matrix m_rotation_utm;
	
	//local position
	Point m_pos_local; // [XYZ]

	//gps position of a point in front of the camera
	Point m_pos_utm; //[Esting,Northing,Height]
	
};

#endif /*BORESIDE_TRANSFORMATION_H_*/
