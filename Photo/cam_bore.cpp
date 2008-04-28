#include "cam_bore.h"

CCam_bore::CCam_bore():Cam()
{
	m_camera_name="unknown";
	m_channels=0;
	m_camera_serial_number="unknown";
	m_objectiv_name="unknown";
	m_focal_length="unknown";
	m_objectiv_serial_number="unknown";
	m_calib_inner_date="unknown";
	m_calib_inner_person="unknown";
	m_calib_inner_comments="unknown";
	m_calib_outer_date="unknown";
	m_calib_outer_person="unknown";
	m_calib_outer_comments="unknown";
	m_calib_boreside_date="unknown";
	m_calib_boreside_person="unknown";
	m_calib_boreside_comments="unknown";
	B_dx=0;
	B_dy=0;
	B_dz=0;
	B_rotx=0;
	B_roty=0;
	B_rotz=0;
}

CCam_bore::CCam_bore(
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
		)://m_pix_size(pix_size),m_pix_row(pix_row),m_pix_col(pix_col),
		  //m_O(OX,OY,OZ),
		  //m_rotX(rotX),m_rotY(rotY),m_rotZ(rotZ),
		  //m_c(c),m_xh(xh),m_yh(yh),
		  //m_A1(A1),m_A2(A2),
		  //m_A3(A3),m_B1(B1),m_B2(B2),
		  //m_C1(C1),m_C2(C2),m_r0(r0),
				        m_camera_name(camera_name),
						m_channels(channels),
						m_camera_serial_number(camera_serial_number),
						m_objectiv_name(objectiv_name),
						m_focal_length(focal_length),
						m_objectiv_serial_number(objectiv_serial_number),
						m_calib_inner_date(calib_inner_date),
						m_calib_inner_person(calib_inner_person),
						m_calib_inner_comments(calib_inner_comments),
						m_calib_outer_date(calib_outer_date),
						m_calib_outer_person(calib_outer_person),
						m_calib_outer_comments(calib_outer_comments),
						m_calib_boreside_date(calib_boreside_date),
						m_calib_boreside_person(calib_boreside_person),
						m_calib_boreside_comments(calib_boreside_comments)
{
			          m_pix_size=pix_size;
			          m_pix_row=pix_row;
			          m_pix_col=pix_col;
					  m_O=Point(OX,OY,OZ);
					  m_rotX=rotX;
					  m_rotY=rotY;
					  m_rotZ=rotZ;
					  m_c=c;
					  m_xh=xh;
					  m_yh=yh;
					  m_A1=A1;
					  m_A2=A2;
					  m_A3=A3;
					  m_B1=B1;
					  m_B2=B2;
					  m_C1=C1;
					  m_C2=C2;
					  m_r0=r0;						
}

CCam_bore::~CCam_bore()
{
}

CCam_bore& CCam_bore::operator=(const CCam_bore &C)
{	
	 (*this).m_pix_row = C.m_pix_row;
	 (*this).m_pix_col = C.m_pix_col;
	 (*this).m_pix_size= C.m_pix_size;
	 (*this).m_O      = C.m_O;
     (*this).m_rotX = C.m_rotX;
	 (*this).m_rotY = C.m_rotY;
	 (*this).m_rotZ = C.m_rotZ;
	 (*this).m_c    = C.m_c;
	 (*this).m_xh   = C.m_xh;
	 (*this).m_yh   = C.m_yh;
	 (*this).m_A1   = C.m_A1;
	 (*this).m_A2   = C.m_A2;
	 (*this).m_A3   = C.m_A3;
	 (*this).m_B1   = C.m_B1;
	 (*this).m_B2   = C.m_B2;
	 (*this).m_C1   = C.m_C1;
	 (*this).m_C2   = C.m_C2;
	 (*this).m_r0   = C.m_r0;
	 
	 (*this).m_camera_name=C.m_camera_name;
	 (*this).m_channels=C.m_channels;
	 (*this).m_camera_serial_number=C.m_camera_serial_number;
	 (*this).m_objectiv_name=C.m_objectiv_name;
	 (*this).m_focal_length=C.m_focal_length;
	 (*this).m_objectiv_serial_number=C.m_objectiv_serial_number;
	 (*this).m_calib_inner_date=C.m_calib_inner_date;
	 (*this).m_calib_inner_person=C.m_calib_inner_person;
	 (*this).m_calib_inner_comments=C.m_calib_inner_comments;
	 (*this).m_calib_outer_date=C.m_calib_outer_date;
	 (*this).m_calib_outer_person=C.m_calib_outer_person;
	 (*this).m_calib_outer_comments=C.m_calib_outer_comments;
	 (*this).m_calib_boreside_date=C.m_calib_boreside_date;
	 (*this).m_calib_boreside_person=C.m_calib_boreside_person;
	 (*this).m_calib_boreside_comments=C.m_calib_boreside_comments;

 return (*this);
}

CCam_bore::CCam_bore(const CCam_bore &C)
{
		(*this)=C;
}

CCam_bore& CCam_bore::operator=(Cam &C)
{	
	 (*this).m_pix_row = C.get_pix_row();//m_pix_row;
	 (*this).m_pix_col = C.get_pix_col();//m_pix_col;
	 (*this).m_pix_size= C.get_pix_size();//m_pix_size;
	 (*this).m_O      = C.get_O();//.m_O;
     (*this).m_rotX = C.get_rotX();//.m_rotX;
	 (*this).m_rotY = C.get_rotY();//.m_rotY;
	 (*this).m_rotZ = C.get_rotZ();//.m_rotZ;
	 (*this).m_c    = C.get_c();//m_c;
	 (*this).m_xh   = C.get_xh();//m_xh;
	 (*this).m_yh   = C.get_yh();//m_yh;
	 (*this).m_A1   = C.get_A1();
	 (*this).m_A2   = C.get_A2();
	 (*this).m_A3   = C.get_A3();
	 (*this).m_B1   = C.get_B1();
	 (*this).m_B2   = C.get_B2();
	 (*this).m_C1   = C.get_C1();
	 (*this).m_C2   = C.get_C2();
	 (*this).m_r0   = C.get_r0();
	 
	 return (*this);
}

CCam_bore::operator Cam() const
{
 return Cam(m_pix_row,m_pix_col,m_pix_size,
		    m_O.get_X(),m_O.get_Y(),m_O.get_Z(),
		    m_rotX,m_rotY,m_rotZ,
		    m_c,m_xh,m_yh,
		    m_A1,m_A2,m_A3,
		    m_B1,m_B2,
		    m_C1,m_C2,
		    m_r0
		    );
}


bool CCam_bore::read_from_ini(const char *datname)
{
	
	return true;
}
bool  CCam_bore::write_in_ini(const char *datname)
{
	
    return true;
}

