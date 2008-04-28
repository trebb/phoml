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
					std::string m_camera_name,
					int         m_channels,
					std::string m_camera_serial_number,
					std::string m_objectiv_name,
					std::string m_focal_length,
					std::string m_objectiv_serial_number,
					std::string m_calib_inner_date,
					std::string m_calib_inner_person,
					std::string m_calib_inner_comments,
					std::string m_calib_outer_date,
					std::string m_calib_outer_person,
					std::string m_calib_outer_comments,
					std::string m_calib_boreside_date,
					std::string m_calib_boreside_person,
					std::string m_calib_boreside_comments
	);
	
	CCam_bore(const CCam_bore &C);
	CCam_bore& operator=(const CCam_bore &C);
	CCam_bore& operator=(Cam &C);
	
	// convertion of "CCam_bore  >>-->  Cam"
	operator Cam () const;
	
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
	double B_dx;
	double B_dy;
	double B_dz;
	// rotation [rad]
	double B_rotx;
	double B_roty;
	double B_rotz;
};

#endif /*CAM_BORE_H_*/
