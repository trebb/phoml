#include "boresight_transformation.h"

CBoresight_transformation::CBoresight_transformation(CCam_bore &cam)
{
 m_cam=cam;
 fill_params_outer_bore();
 set_car_position_utm(0.0,0.0,0.0,0.0,0.0,0.0);
}

CBoresight_transformation::CBoresight_transformation(CCam_bore &cam,double Easting,double Northing,double ell_Height,double roll,double pitch,double heading)
{
 m_cam=cam;
 fill_params_outer_bore();
 
 //save gps position of the car
 set_car_position_utm(Easting,Northing,ell_Height,roll,pitch,heading);
}

CBoresight_transformation::CBoresight_transformation(CCam_bore &cam,Gps_pos &Pos)
{
 m_cam=cam;
 fill_params_outer_bore();

 //save gps position of the car
 set_car_position_utm(Pos);
}

CBoresight_transformation::~CBoresight_transformation()
{
	
}

void CBoresight_transformation::set_car_position_utm(double Easting,double Northing,double ell_Height,double roll,double pitch,double heading)
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

void CBoresight_transformation::set_car_position_utm(Gps_pos &Pos)
{
	//save gps position of the car
	 m_Easting=Pos.get_Easting();
	 m_Northing=Pos.get_Northing();
	 m_ell_Height=Pos.get_EllH();
	 m_roll=Pos.get_Roll();
	 m_pitch=Pos.get_Pitch();
	 m_heading=Pos.get_Heading();
	 m_dEasting=Pos.get_mEasting();
	 m_dNorthing=Pos.get_mNorthing();
	 m_dell_Height=Pos.get_mEllH();
	 m_droll=Pos.get_mRoll();
	 m_dpitch=Pos.get_mPitch();
	 m_dheading=Pos.get_mHeading();

	 fill_params_utm();
}
	
void CBoresight_transformation::set_utm_koordinate(double Easting,double Northing,double ell_Height)
{
	m_pos_utm = Point(Easting,Northing,ell_Height);	
}

void CBoresight_transformation::set_utm_koordinate(Point &utm)
{
	m_pos_utm = utm;
}

void CBoresight_transformation::set_local_koordinate(double local_X,double local_Y,double local_Z)
{
	m_pos_local = Point(local_X,local_Y,local_Z);
}

void CBoresight_transformation::set_local_koordinate(Point &local)
{
	m_pos_local = local;
}


Point CBoresight_transformation::get_utm_koordinate()
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

Point CBoresight_transformation::get_local_koordinate()
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

void CBoresight_transformation::fill_params_outer_bore()
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

void CBoresight_transformation::fill_params_utm()
{
	//gps coordinate system
	//Translation
	m_translation_utm = Point(m_Easting,m_Northing,m_ell_Height,m_dEasting,m_dNorthing,m_dell_Height);
	//Rotation
	
	//TODO change the rotation
	//m_rotation_utm = Rot(m_pitch,m_roll,m_heading);
	m_rotation_utm = Rot(m_roll,m_pitch,m_heading);
	//std::cout<<std::endl<<"Rnach: "<<m_rotation_utm<<std::flush;
}
