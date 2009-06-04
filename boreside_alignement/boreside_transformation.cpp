#include "boreside_transformation.h"

CBoreside_transformation::CBoreside_transformation(CCam_bore &cam)
{
 m_cam=cam;
 fill_params_outer_bore();
 set_car_position_utm(0.0,0.0,0.0,0.0,0.0,0.0);
}

CBoreside_transformation::CBoreside_transformation(CCam_bore &cam,double Easting,double Northing,double ell_Height,double roll,double pitch,double heading)
{
 m_cam=cam;
 fill_params_outer_bore();
 
 //save gps position of the car
 set_car_position_utm(Easting,Northing,ell_Height,roll,pitch,heading);
}

CBoreside_transformation::~CBoreside_transformation()
{
	
}

void CBoreside_transformation::set_car_position_utm(double Easting,double Northing,double ell_Height,double roll,double pitch,double heading)
{
 //save gps position of the car
 m_Easting=Easting;
 m_Northing=Northing;
 m_ell_Height=ell_Height;
 m_roll=roll;
 m_pitch=pitch;
 m_heading=heading;
 fill_params_utm();	
}
	
void CBoreside_transformation::set_utm_koordinate(double Easting,double Northing,double ell_Height)
{
	m_pos_utm = Point(Easting,Northing,ell_Height);	
}

void CBoreside_transformation::set_local_koordinate(double local_X,double local_Y,double local_Z)
{
	m_pos_local = Point(local_X,local_Y,local_Z);
}
	
Point CBoreside_transformation::get_utm_koordinate()
{
 //calc back into the sensor coordinate system
 Point pos_local = m_pos_local.RotationRueck(m_translation_cam,m_rotation_cam);
 // test for laser line 
 //todo testing
 //Point pos_local = m_pos_local.Rotation(m_translation_cam,m_rotation_cam);
	
 //calc utm coordinate from the local cam coordinate system 
 //Point transl = m_translation_car.Add(m_translation_utm);
 //Matrix rotat = m_rotation_car.MatMult(m_rotation_utm);
 //Point P_utm = pos_local.Rotation(transl,rotat);
 
 //new
 Point P_car =  pos_local.Rotation(m_translation_car,m_rotation_car);
 Point P_utm_new = P_car.Rotation(m_translation_utm,m_rotation_utm);
 
 m_pos_utm = P_utm_new;
	
 return m_pos_utm;
}

Point CBoreside_transformation::get_local_koordinate()
{
 //calc local cam coordinate from the utm coordinate system
 //Point transl = m_translation_car.Add(m_translation_utm);
 //Matrix rotat = m_rotation_car.MatMult(m_rotation_utm);
 //Point P_local = m_pos_utm.RotationRueck(transl,rotat);
 
 //new
 Point P_car =  m_pos_utm.RotationRueck(m_translation_utm,m_rotation_utm);
 Point P_local = P_car.RotationRueck(m_translation_car,m_rotation_car);
 
 Point P_local_cam = P_local.Rotation(m_translation_cam,m_rotation_cam);
 
 m_pos_local=P_local_cam;
 
 return m_pos_local;	
}



void CBoreside_transformation::fill_params_outer_bore()
{
	//cam koordinate system
	//Translation
	m_translation_cam = m_cam.get_O();
	//Rotation
	m_rotation_cam = Rot(m_cam.get_rotX(),m_cam.get_rotY(),m_cam.get_rotZ());
	
	//car koordinate system
	//Translation
	m_translation_car = m_cam.get_B();
	//Rotation
	m_rotation_car = Rot(m_cam.get_B_rotx(),m_cam.get_B_roty(),m_cam.get_B_rotz());
}
void CBoreside_transformation::fill_params_utm()
{
	//gps coordinate system
	//Translation
	m_translation_utm = Point(m_Easting,m_Northing,m_ell_Height);
	//Rotation
	m_rotation_utm = Rot(m_pitch,m_roll,m_heading);
	//std::cout<<std::endl<<"Rnach: "<<m_rotation_utm<<std::flush;
}
