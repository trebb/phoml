#ifndef CAM_BORE_H_
#define CAM_BORE_H_

//c++
#include <iostream>

//own lib
#include "../photo/cam.h"

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
					double B_ddx, double B_ddy, double B_ddz,
					double B_rotx, double B_roty, double B_rotz,
					double B_drotx, double B_droty, double B_drotz,
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

	
	//a short constructor for Christian' java ;-)
	
	CCam_bore(
				        double pix_row, double pix_col, double pix_size,
						double OX, double OY, double OZ,
					    double rotX, double rotY, double rotZ,
					    double c, double xh, double yh, 
						double A1, double A2, double A3,
						double B1, double B2, double C1,
						double C2, double r0,
						double B_dx, double B_dy, double B_dz,
						double B_ddx, double B_ddy, double B_ddz,
						double B_rotx, double B_roty, double B_rotz,
						double B_drotx, double B_droty, double B_drotz
		);
	
	CCam_bore(const CCam_bore &C);
	CCam_bore& operator=(const CCam_bore &C);
	CCam_bore& operator=(Cam &C);
	
	// convertion of "CCam_bore  >>-->  Cam"
	operator Cam () const;
	
	//get funktions
	Point  get_B()    const {Point P(m_B_dx,m_B_dy,m_B_dz); P.set_dX(m_B_ddx); P.set_dY(m_B_ddy);P.set_dZ(m_B_ddz);return P;}
	double get_B_dx() const {return m_B_dx;}
	double get_B_dy() const {return m_B_dy;}
	double get_B_dz() const {return m_B_dz;}
	
	double get_B_ddx() const {return m_B_ddx;}
	double get_B_ddy() const {return m_B_ddy;}
	double get_B_ddz() const {return m_B_ddz;}
	
	double get_B_rotx() const {return m_B_rotx;}
	double get_B_roty() const {return m_B_roty;}
	double get_B_rotz() const {return m_B_rotz;}
	
	double get_B_drotx() const {return m_B_drotx;}
	double get_B_droty() const {return m_B_droty;}
	double get_B_drotz() const {return m_B_drotz;}
		
	//set funktions
	void set_B_dx(double B_dx){m_B_dx=B_dx;}
	void set_B_dy(double B_dy){m_B_dy=B_dy;}
	void set_B_dz(double B_dz){m_B_dz=B_dz;}
	
	void set_B_ddx(double B_ddx){m_B_ddx=B_ddx;}
	void set_B_ddy(double B_ddy){m_B_ddy=B_ddy;}
	void set_B_ddz(double B_ddz){m_B_ddz=B_ddz;}
	
	void set_B_rotx(double B_rotx){m_B_rotx=B_rotx;}
	void set_B_roty(double B_roty){m_B_roty=B_roty;}
	void set_B_rotz(double B_rotz){m_B_rotz=B_rotz;}
	
	void set_B_drotx(double B_drotx){m_B_drotx=B_drotx;}
	void set_B_droty(double B_droty){m_B_droty=B_droty;}
	void set_B_drotz(double B_drotz){m_B_drotz=B_drotz;}

	//secondary get funktions
	std::string get_camera_name() const ;
	int         get_channels() const ;
	std::string get_camera_serial_number() const ;
	std::string get_objectiv_name() const ;
	std::string get_focal_length() const ;
	std::string get_objectiv_serial_number() const ;
	std::string get_calib_inner_date() const ;
	std::string get_calib_inner_person() const ;
	std::string get_calib_inner_comments() const ;
	std::string get_calib_outer_date() const ;
	std::string get_calib_outer_person() const ;
	std::string get_calib_outer_comments() const ;
	std::string get_calib_boreside_date() const ;
	std::string get_calib_boreside_person() const ;
	std::string get_calib_boreside_comments() const ;
		
	//overwrite of Cam funktions
	bool read_from_ini(const char *datname);
	bool  write_in_ini(const char *datname);
	
	bool copy_bore_side(const CCam_bore &C);
	bool copy_relative_orientation(const CCam_bore &C);

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
	
	//standart deviation translation
	double m_B_ddx;
	double m_B_ddy;
	double m_B_ddz;
	
	// rotation [rad]
	double m_B_rotx;
	double m_B_roty;
	double m_B_rotz;
	
	//standart deviation rotation
	double m_B_drotx;
	double m_B_droty;
	double m_B_drotz;
};

ostream& operator<<(ostream& s,const CCam_bore& A);


#endif /*CAM_BORE_H_*/
