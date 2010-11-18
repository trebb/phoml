#include "boresight_transformation.h"

Boresight_transformation::Boresight_transformation(Cam_bore &cam)
{
 m_cam=cam;
 fill_params_outer_bore();
 set_car_position_global(0.0,0.0,0.0,0.0,0.0,0.0);
}

Boresight_transformation::Boresight_transformation(Cam_bore &cam,double Easting,double Northing,double ell_Height,double roll,double pitch,double heading)
{//todo set to deprecate
 m_cam=cam;
 fill_params_outer_bore();
 
 //save gps position of the car
 set_car_position_global(Easting,Northing,ell_Height,roll,pitch,heading);
}

Boresight_transformation::Boresight_transformation(Cam_bore &cam,Gps_pos &Pos)
{
 m_cam=cam;
 //fill_params_outer_bore();

 //save gps position of the car
 set_car_position_global(Pos);
}

Boresight_transformation::~Boresight_transformation()
{
	
}

void Boresight_transformation::set_car_position_global(Gps_pos &Pos)
{
	//save gps position of the car
	 m_Easting=Pos.get_Easting();
	 m_Northing=Pos.get_Northing();
	 m_ell_Height=Pos.get_EllH();
	 m_roll=Pos.get_Roll();
	 m_pitch=Pos.get_Pitch();
	 m_heading=Pos.get_Heading();
	 m_dEasting=Pos.get_dEasting();
	 m_dNorthing=Pos.get_dNorthing();
	 m_dell_Height=Pos.get_dEllH();
	 m_droll=Pos.get_dRoll();
	 m_dpitch=Pos.get_dPitch();
	 m_dheading=Pos.get_dHeading();

	 fill_params_global();
}
	

void Boresight_transformation::set_global_coordinate(Point &global)
{
	m_pos_global = global;
}


void Boresight_transformation::set_local_coordinate(Point &local)
{
	m_pos_local = local;
}


Point Boresight_transformation::get_global_coordinate()
{
    //new calculation with rotation_matrix
    // -> delete all fill_params functions

    //1. transform
    //first transformation transform back from the relative orientation into the camera coordinate system
    //Solution is the measurement point is transformed back into the given camera (constructor)
        Point           translation_cam = m_cam.get_O();
        Rotation_matrix rotation_cam(Rotation_matrix::math, m_cam.get_rotX(), m_cam.get_rotY(), m_cam.get_rotZ());

    //cout<<endl<<"# boreside transformation -> function get_global_coordinate()";
    //cout<<endl<<"in cam coordinate system";
    Point positon_in_cam_coo = m_pos_local.RotationRueck_with_std(translation_cam,rotation_cam);

    //2. transform
    //second transformation transform from the camera coordinate system into the car coordinate system
        Point           translation_car = m_cam.get_B();
        Rotation_matrix rotation_car(Rotation_matrix::math,m_cam.get_B_rotx(),m_cam.get_B_roty(),m_cam.get_B_rotz());

    //cout<<endl<<"in car coordinate system";
    Point positon_in_car_coo = positon_in_cam_coo.Rotation_with_std(translation_car,rotation_car);


    //3. transform
    //third transformation transform from the car coordinate system into the global coordinate system
        Point           translation_global(m_Easting,m_Northing,m_ell_Height,m_dEasting,m_dNorthing,m_dell_Height);
        Rotation_matrix rotation_global(Rotation_matrix::math,m_roll,m_pitch,m_heading,m_droll,m_dpitch,m_dheading);

    //cout<<endl<<"in global coordinate system";
    Point positon_in_car_global = positon_in_car_coo.Rotation_with_std(translation_global,rotation_global);


    return positon_in_car_global;//m_pos_global;


/*
 //calc back into the sensor coordinate system
 Point pos_local = m_pos_local.RotationRueck(m_translation_cam,m_rotation_cam);
 // test for laser line 

 //Point pos_local = m_pos_local.Rotation(m_translation_cam,m_rotation_cam);
	
 //calc global coordinate from the local cam coordinate system
 //Point transl = m_translation_car.Add(m_translation_global);
 //Matrix rotat = m_rotation_car.MatMult(m_rotation_global);
 //Point P_global = pos_local.Rotation(transl,rotat);
 
 //new
 Point P_car =  pos_local.Rotation(m_translation_car,m_rotation_car);
 Point P_global_new = P_car.Rotation(m_translation_global,m_rotation_global);
 
 m_pos_global = P_global_new;
	
 return m_pos_global;
*/
}

Point Boresight_transformation::get_local_coordinate()
{
  //3. transform
  //third transformation transform from the car coordinate system into the global coordinate system
         Point           translation_global(m_Easting,m_Northing,m_ell_Height,m_dEasting,m_dNorthing,m_dell_Height);
         Rotation_matrix rotation_global(Rotation_matrix::math,m_roll,m_pitch,m_heading,m_droll,m_dpitch,m_dheading);

     //cout<<endl<<"# boreside transformation -> function get_local_coordinate()";
     //cout<<endl<<"in global coordinate system";
     Point positon_in_car_global = m_pos_global.RotationRueck_with_std(translation_global,rotation_global);


  //2. transform
  //second transformation transform from the camera coordinate system into the car coordinate system
        Point           translation_car = m_cam.get_B();
        Rotation_matrix rotation_car(Rotation_matrix::math,m_cam.get_B_rotx(),m_cam.get_B_roty(),m_cam.get_B_rotz());

    //cout<<endl<<"in car coordinate system";
    Point positon_in_car_coo = positon_in_car_global.RotationRueck_with_std(translation_car,rotation_car);


  //1. transform
  //first transformation transform back from the relative orientation into the camera coordinate system
  //Solution is the measurement point is transformed back into the given camera (constructor)
        Point           translation_cam = m_cam.get_O();
        Rotation_matrix rotation_cam(Rotation_matrix::math, m_cam.get_rotX(), m_cam.get_rotY(), m_cam.get_rotZ());

    //cout<<endl<<"in cam coordinate system";
    Point positon_in_cam_coo = positon_in_car_coo.Rotation_with_std(translation_cam,rotation_cam);

return positon_in_cam_coo;

/*
 //calc local cam coordinate from the global coordinate system
 //Point transl = m_translation_car.Add(m_translation_global);
 //Matrix rotat = m_rotation_car.MatMult(m_rotation_global);
 //Point P_local = m_pos_global.RotationRueck(transl,rotat);
 
 //new
 Point P_car =  m_pos_global.RotationRueck(m_translation_global,m_rotation_global);
 Point P_local = P_car.RotationRueck(m_translation_car,m_rotation_car);
 
 Point P_local_cam = P_local.Rotation(m_translation_cam,m_rotation_cam);
 
 m_pos_local=P_local_cam;
 
 return m_pos_local;
 */
}


//####################################################
void Boresight_transformation::set_car_position_global(double Easting,double Northing,double ell_Height,double roll,double pitch,double heading)
{//todo set to deprecate
 //save gps position of the car
 m_Easting=Easting;
 m_Northing=Northing;
 m_ell_Height=ell_Height;
 m_roll=roll;
 m_pitch=pitch;
 m_heading=heading;
 fill_params_global();
}
void Boresight_transformation::set_global_coordinate(double Easting,double Northing,double ell_Height)
{//todo set to deprecate
	m_pos_global = Point(Easting,Northing,ell_Height);
}
void Boresight_transformation::set_local_coordinate(double local_X,double local_Y,double local_Z)
{//todo set to deprecate
	m_pos_local = Point(local_X,local_Y,local_Z);
}


void Boresight_transformation::fill_params_outer_bore()
{ //todo change Rotation
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

void Boresight_transformation::fill_params_global()
{//todo change Rotation
	//gps coordinate system
	//Translation
	m_translation_global = Point(m_Easting,m_Northing,m_ell_Height,m_dEasting,m_dNorthing,m_dell_Height);
	//Rotation
	

	//m_rotation_global = Rot(m_pitch,m_roll,m_heading);
	m_rotation_global = Rot(m_roll,m_pitch,m_heading);
	//std::cout<<std::endl<<"Rnach: "<<m_rotation_global<<std::flush;
}
