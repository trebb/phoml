#ifndef CAM_BORE_H_
#define CAM_BORE_H_

//c++
#include <iostream>

//own lib
#include "cam.h"

class CCam_bore:public Cam
{
public:
	CCam_bore();
	virtual ~CCam_bore();
	CCam_bore(
			        double pix_row, double pix_col, double pix_size,
					double OX, double OY, double OZ,
				    double rotX, double rotY, double rotZ,
				    double c, double xh, double yh, 
					double A1, double A2, double A3,
					double B1, double B2, double C1,
					double C2, double r0,
					double B_dx, double B_dy, double B_dz,
					double B_rotx, double B_roty, double B_rotz,
					std::string camera_name,
					int         channels,
					std::string camera_serial_number,
					std::string objectiv_name,
					std::string focal_length,
					std::string objectiv_serial_number,
					std::string calib_inner_date,
					std::string calib_inner_person,
					std::string calib_inner_comments,
					std::string calib_outer_date,
					std::string calib_outer_person,
					std::string calib_outer_comments,
					std::string calib_boreside_date,
					std::string calib_boreside_person,
					std::string calib_boreside_comments
	);
	
	CCam_bore(const CCam_bore &C);
	CCam_bore& operator=(const CCam_bore &C);
	CCam_bore& operator=(Cam &C);
	
	// convertion of "CCam_bore  >>-->  Cam"
	operator Cam () const;
	
	//get funktions
	Point  get_B()   {return Point(m_B_dx,m_B_dy,m_B_dz);}
	double get_B_dx(){return m_B_dx;}
	double get_B_dy(){return m_B_dy;}
	double get_B_dz(){return m_B_dz;}
	
	double get_B_rotx(){return m_B_rotx;}
	double get_B_roty(){return m_B_roty;}
	double get_B_rotz(){return m_B_rotz;}
	
	//set funktions
	void set_B_dx(double B_dx){m_B_dx=B_dx;}
	void set_B_dy(double B_dy){m_B_dy=B_dy;}
	void set_B_dz(double B_dz){m_B_dz=B_dz;}
	
	void set_B_rotx(double B_rotx){m_B_rotx=B_rotx;}
	void set_B_roty(double B_roty){m_B_roty=B_roty;}
	void set_B_rotz(double B_rotz){m_B_rotz=B_rotz;}
	
	std::string get_camera_name				(){return m_camera_name;}
	int 		get_channels				(){return m_channels;}
	std::string get_camera_serial_number	(){return m_camera_serial_number;}
	std::string get_objektiv_name			(){return m_objectiv_name;}
	std::string get_string_focal_length		(){return m_focal_length;}
	std::string get_objektiv_serial_number	(){return m_objectiv_serial_number;}
	std::string get_calib_inner_date		(){return m_calib_inner_date;}
	std::string get_calib_inner_person		(){return m_calib_inner_person;}
	std::string get_calib_inner_comments	(){return m_calib_inner_comments;}
	std::string get_calib_outer_date		(){return m_calib_outer_date;}
	std::string get_calib_outer_person		(){return m_calib_outer_person;}
	std::string get_calib_outer_comments	(){return m_calib_outer_comments;}
	std::string get_calib_boreside_date		(){return m_calib_boreside_date;}
	std::string get_calib_boreside_person	(){return m_calib_boreside_person;}
	std::string get_calib_boreside_comments	(){return m_calib_boreside_comments;}
	
	//overwrite of Cam funktions
	bool read_from_ini(const char *datname);
	bool  write_in_ini(const char *datname);
	
private:
	//[GENERAL]
	std::string m_camera_name;
	int         m_channels;
	std::string m_camera_serial_number;
	
	//[OBJECTIV]
	std::string m_objectiv_name;
	//focal length in [mm]
	//this is not c!!! This is the value from the manufacturer!!
	std::string m_focal_length;
	std::string m_objectiv_serial_number;
	
	//[INNER_ORIENTATION]
	std::string m_calib_inner_date;
	std::string m_calib_inner_person;
	std::string m_calib_inner_comments;

	//[OUTER_ORIENTATION]
	std::string m_calib_outer_date;
	std::string m_calib_outer_person;
	std::string m_calib_outer_comments;
	
	//[BORESIDE_ALIGNEMENT]
	std::string m_calib_boreside_date;
	std::string m_calib_boreside_person;
	std::string m_calib_boreside_comments;
	
	// tranlation [mm]
	double m_B_dx;
	double m_B_dy;
	double m_B_dz;
	// rotation [rad]
	double m_B_rotx;
	double m_B_roty;
	double m_B_rotz;
};

#endif /*CAM_BORE_H_*/
