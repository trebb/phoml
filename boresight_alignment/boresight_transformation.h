#ifndef BORESIGHT_TRANSFORMATION_H_
#define BORESIGHT_TRANSFORMATION_H_

#include "..//basics//point.h"
#include "..//basics//matrix//matrix.h"
#include "..//basics//rot_matrix.h"
#include "..//basics//rotation_matrix.h"
#include "..//position//gps_pos.h"
#include "cam_bore.h"


class Boresight_transformation
{
	
public:
	Boresight_transformation(Cam_bore &cam);
	Boresight_transformation(Cam_bore &cam,double Easting,double Northing,double ell_Height,double roll,double pitch,double heading);//todo set to deprecate
	Boresight_transformation(Cam_bore &cam,Gps_pos &Pos);

	virtual ~Boresight_transformation();
	
	void set_car_position_global(Gps_pos &Pos);
	void set_global_coordinate(Point &utm);  //[Easting,Northing,Height,dEasting,dNorthing,dHeight]
	void set_local_coordinate(Point &local);    //[X,Y,Z,dX,dY,dZ]
	
	Point get_global_coordinate(); //[Easting,Northing,Height,dEasting,dNorthing,dHeight]
	Point get_local_coordinate();//[X,Y,Z,dX,dY,dZ]


	// begin deprecate
	//todo set to deprecate this 3 functions without standard deviation
	void set_car_position_global(double Easting,double Northing,double ell_Height,double roll,double pitch,double heading);
	void set_global_coordinate(double Easting,double Northing,double ell_Height);  //[Esting,Northing,Height]
	void set_local_coordinate(double local_X,double local_Y,double local_Z);    //[X,Y,Z]
    // end deprecate
	
	
private:
	void fill_params_outer_bore();//todo set to deprecate
	void fill_params_global();//todo set to deprecate
	
	// camera setup
	Cam_bore m_cam;
	
	// position of the car
	double m_Easting,m_Northing,m_ell_Height,m_roll,m_pitch,m_heading;
	
	//standard deviation of car position
	double m_dEasting,m_dNorthing,m_dell_Height,m_droll,m_dpitch,m_dheading;


	//local position
	Point m_pos_local; // [XYZ]

	//gps position of a point in front of the camera
	Point m_pos_global; //[Esting,Northing,Height]


// begin todo set to deprecate
	//cam koordinate system (sensor right-x , up-y  (z-> right hand )  )
	//unit: [m]
	//transformation setup
	Point  m_translation_cam;
	Matrix m_rotation_cam;
	//Rotation_matrix m_rotation_cam_rm;
	
	//car koordinate system (car plattform x-right side , y-forward (z->right hand))
	//unit: [m]
	//transformation setup
	Point  m_translation_car;
	Matrix m_rotation_car;
	//Rotation_matrix m_rotation_car_rm;
	
	//gps koordinate system (UTM WGS84 [m])
	//unit: [m]
	//transformation setup
	Point  m_translation_global;
	Matrix m_rotation_global;
	//Rotation_matrix m_rotation_global_rm;
// end todo set to deprecate
};

#endif /*BORESIDE_TRANSFORMATION_H_*/
