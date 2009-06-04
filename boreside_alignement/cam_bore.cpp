#include "cam_bore.h"

//c++
#include <fstream>
#include <sstream>
#include <cmath>

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
	m_B_dx=0;
	m_B_dy=0;
	m_B_dz=0;
	m_B_ddx=0;
	m_B_ddy=0;
	m_B_ddz=0;
	m_B_rotx=0;
	m_B_roty=0;
	m_B_rotz=0;
	m_B_drotx=0;
	m_B_droty=0;
	m_B_drotz=0;
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
					  m_B_dx=B_dx;
					  m_B_dy=B_dy;
					  m_B_dz=B_dz;
					  m_B_ddx=B_ddx;
					  m_B_ddy=B_ddy;
					  m_B_ddz=B_ddz;
					  m_B_rotx=B_rotx;
					  m_B_roty=B_roty;
					  m_B_rotz=B_rotz;
					  m_B_drotx=B_drotx;
					  m_B_droty=B_droty;
					  m_B_drotz=B_drotz;
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
				double B_ddx, double B_ddy, double B_ddz,
				double B_rotx, double B_roty, double B_rotz,
				double B_drotx, double B_droty, double B_drotz
				)		        
		{
					        m_camera_name.assign("unknow");
							m_camera_serial_number.assign("unknow");
							m_objectiv_name.assign("unknow");
							m_focal_length.assign("unknow");
							m_objectiv_serial_number.assign("unknow");
							m_calib_inner_date.assign("unknow");
							m_calib_inner_person.assign("unknow");
							m_calib_inner_comments.assign("unknow");
							m_calib_outer_date.assign("unknow");
							m_calib_outer_person.assign("unknow");
							m_calib_outer_comments.assign("unknow");
							m_calib_boreside_date.assign("unknow");
							m_calib_boreside_person.assign("unknow");
							m_calib_boreside_comments.assign("unknow");
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
							  m_B_dx=B_dx;
							  m_B_dy=B_dy;
							  m_B_dz=B_dz;
							  m_B_ddx=B_ddx;
							  m_B_ddy=B_ddy;
							  m_B_ddz=B_ddz;
							  m_B_rotx=B_rotx;
							  m_B_roty=B_roty;
							  m_B_rotz=B_rotz;
							  m_B_drotx=B_drotx;
							  m_B_droty=B_droty;
							  m_B_drotz=B_drotz;
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
	 
	 (*this).m_B_dx = C.m_B_dx;
	 (*this).m_B_dy = C.m_B_dy;
	 (*this).m_B_dz = C.m_B_dz;
	 (*this).m_B_ddx = C.m_B_ddx;
	 (*this).m_B_ddy = C.m_B_ddy;
	 (*this).m_B_ddz = C.m_B_ddz;
	 (*this).m_B_rotx = C.m_B_rotx;
	 (*this).m_B_roty = C.m_B_roty;
	 (*this).m_B_rotz = C.m_B_rotz;
	 (*this).m_B_drotx = C.m_B_drotx;
	 (*this).m_B_droty = C.m_B_droty;
	 (*this).m_B_drotz = C.m_B_drotz;
	 	 
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
	ifstream SET_TXT;  
	 SET_TXT.open(datname); 
	 if(!SET_TXT) { return false; }
	  
	 string hilf;
	 int j=0;
	   

	 			   //[GENERAL]
	               char s_0_1[]="SENSOR_WIDTH_PIX=";

				   char s_0_2[]="SENSOR_HEIGHT_PIX=";
					
				   char s_0_3[]="PIXELSIZE=";
				   
				   char s_0_4[]="CAMERA_NAME=";
				   
				   char s_0_5[]="CHANNELS=";
				   
				   char s_0_6[]="CAMERA_SERIAL_NUMBER=";
				   
				   
				   //[OBJEKTIV]
				   char s_0_61[]="OBJECTIV_NAME=";
				   
				   char s_0_62[]="FOCAL_LENGTH=";
				   
				   char s_0_63[]="OBJECTIV_SERIAL_NUMBER=";
				   
				   
				   //[INNER_ORIENTATION]
				   char s_0_81[]="CALIB_INNER_DATE=";
				   
				   char s_0_82[]="CALIB_INNER_PERSON=";
				   
				   char s_0_83[]="CALIB_INNER_COMMENTS=";
				   
	               char s_0_9[]="c=";
	               
				   char s_1_0[]="xh=";
				  
				   char s_1_1[]="yh=";
	               
				   char s_2_1[]="a1=";
				    
				   char s_2_2[]="a2=";
	               
				   char s_2_3[]="a3=";

				   char s_3_1[]="b1=";

				   char s_3_2[]="b2=";

				   char s_4_1[]="c1=";
			       
				   char s_4_2[]="c2=";

				   char s_5_1[]="r0=";

				   
				   //[OUTER_ORIENTATION]
				   char s_6_01[]="CALIB_OUTER_DATE=";
				   
				   char s_6_02[]="CALIB_OUTER_PERSON=";
				   
				   char s_6_03[]="CALIB_OUTER_COMMENTS=";
				   
				   char s_6_1[]="dx=";

				   char s_6_2[]="dy=";

				   char s_6_3[]="dz=";

				   char s_7_1[]="rotx=";

				   char s_7_2[]="roty=";

				   char s_7_3[]="rotz=";
				   
				   
				   //[BORESIDE_ALIGNEMENT]
				   char s_8_1[]="CALIB_BORESIDE_DATE=";
				   
				   char s_8_2[]="CALIB_BORESIDE_PERSON=";
				   
				   char s_8_3[]="CALIB_BORESIDE_COMMENTS=";
				   
				   char s_8_4[]="B_dx=";
				   
				   char s_8_5[]="B_dy=";
				   
				   char s_8_6[]="B_dz=";
				   
				   char s_8_7[]="B_rotx=";
				   
				   char s_8_8[]="B_roty=";
				   
				   char s_8_9[]="B_rotz=";
				   

	//count if all values once read
	int count=0;
		
	 while(getline(SET_TXT,hilf))
	 {					
				if(hilf.length()>0 )
				if(hilf.at(j)!='#' )
				if(hilf.at(j)!='/' && hilf.at(j+1)!='/')
				if(hilf.at(j)!='[')
				{                  		   
				
					//[GENERAL]
					   size_t find_0_1=0;
	              	      find_0_1=hilf.find(s_0_1)+1;  
	              
						  if(find_0_1)
						  {hilf.erase(0,(find_0_1-2)+sizeof(s_0_1));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); 	   stream>>m_pix_row;
						   ++count;
						  }
	              

					  size_t find_0_2=0;
						  find_0_2=hilf.find(s_0_2)+1;
					  
						  if(find_0_2)
						  {hilf.erase(0,(find_0_2-2)+sizeof(s_0_2));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); 	   stream>>m_pix_col;
						   ++count;
						  }
						  

					  size_t find_0_3=0;
						  find_0_3=hilf.find(s_0_3)+1;
					  
						  if(find_0_3)
						  {hilf.erase(0,(find_0_3-2)+sizeof(s_0_3));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); 	   stream>>m_pix_size;
						   ++count;
						  }

					  //char s_0_4[]="CAMERA_NAME=";
					  size_t find_0_4=0;
  						  find_0_4=hilf.find(s_0_4)+1;
  					  
  						  if(find_0_4)
  						  {hilf.erase(0,(find_0_4-2)+sizeof(s_0_4));
  						   stringstream stream; stream<<hilf.c_str();
  						   hilf.erase(); m_camera_name=stream.str();
  						   ++count;
  						  }  
  						  
					  //char s_0_5[]="CHANNELS=";
					  size_t find_0_5=0;
						  find_0_5=hilf.find(s_0_5)+1;
					  
						  if(find_0_5)
						  {hilf.erase(0,(find_0_5-2)+sizeof(s_0_5));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); 	   stream>>m_channels;
  						   ++count;
						  }

										   
					  //char s_0_6[]="CAMERA_SERIAL_NUMBER=";
					  size_t find_0_6=0;
						  find_0_6=hilf.find(s_0_6)+1;
					  
						  if(find_0_6)
						  {hilf.erase(0,(find_0_6-2)+sizeof(s_0_6));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); m_camera_serial_number=stream.str();
  						   ++count;
						  }
					   
					   
					   //[OBJEKTIV]
					  //char s_0_61[]="OBJECTIV_NAME=";
					  size_t find_0_61=0;
						  find_0_61=hilf.find(s_0_61)+1;
					  
						  if(find_0_61)
						  {hilf.erase(0,(find_0_61-2)+sizeof(s_0_61));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); m_objectiv_name=stream.str();
  						   ++count;
						  }
				   
					  //char s_0_62[]="FOCAL_LENGTH=";
					  size_t find_0_62=0;
						  find_0_62=hilf.find(s_0_62)+1;
					  
						  if(find_0_62)
						  {hilf.erase(0,(find_0_62-2)+sizeof(s_0_62));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); m_focal_length=stream.str();
  						   ++count;
						  }
 
					  //char s_0_63[]="OBJECTIV_SERIAL_NUMBER=";
					  size_t find_0_63=0;
						  find_0_63=hilf.find(s_0_63)+1;
					  
						  if(find_0_63)
						  {hilf.erase(0,(find_0_63-2)+sizeof(s_0_63));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); m_objectiv_serial_number=stream.str();
  						   ++count;
						  }
					   
					   
					   //[INNER_ORIENTATION]
					  //char s_0_81[]="CALIB_INNER_DATE=";
					  size_t find_0_81=0;
						  find_0_81=hilf.find(s_0_81)+1;
					  
						  if(find_0_81)
						  {hilf.erase(0,(find_0_81-2)+sizeof(s_0_81));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); m_calib_inner_date=stream.str();
  						   ++count;
						  }
					   
					  //char s_0_82[]="CALIB_INNER_PERSON=";
					  size_t find_0_82=0;
						  find_0_82=hilf.find(s_0_82)+1;
					  
						  if(find_0_82)
						  {hilf.erase(0,(find_0_82-2)+sizeof(s_0_82));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); m_calib_inner_person=stream.str();
  						   ++count;
						  }
					   
					  //char s_0_83[]="CALIB_INNER_COMMENTS=";
					  size_t find_0_83=0;
						  find_0_83=hilf.find(s_0_83)+1;
					  
						  if(find_0_83)
						  {hilf.erase(0,(find_0_83-2)+sizeof(s_0_83));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); m_calib_inner_comments=stream.str();
  						   ++count;
						  }
					   

					
					  size_t find_0_9=0;
						  find_0_9=hilf.find(s_0_9)+1;
					  
						  if(find_0_9)
						  {hilf.erase(0,(find_0_9-2)+sizeof(s_0_9));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); 	   stream>>m_c;
						   m_c=-fabs(m_c);
  						   ++count;
						  }


					  size_t find_1_0=0;
	              	      find_1_0=hilf.find(s_1_0)+1;
	              
						  if(find_1_0)
						  {hilf.erase(0,(find_1_0-2)+sizeof(s_1_0));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); 	   stream>>m_xh;
  						   ++count;
						  }
	              

					  size_t find_1_1=0;
						  find_1_1=hilf.find(s_1_1)+1;
					  
						  if(find_1_1)
						  {hilf.erase(0,(find_1_1-2)+sizeof(s_1_1));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); 	   stream>>m_yh;
  						   ++count;
						  }          
						  
					  size_t find_2_1=0;
						  find_2_1=hilf.find(s_2_1)+1;
					  
						  if(find_2_1)
						  {hilf.erase(0,(find_2_1-2)+sizeof(s_2_1));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); 	   stream>>m_A1;
  						   ++count;
						  }              


					  size_t find_2_2=0;
						  find_2_2=hilf.find(s_2_2)+1;
					  
						  if(find_2_2)
						  {hilf.erase(0,(find_2_2-2)+sizeof(s_2_2));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); 	   stream>>m_A2;
  						   ++count;
						  } 

						  
					  size_t find_2_3=0;
						  find_2_3=hilf.find(s_2_3)+1;
					  
						  if(find_2_3)
						  {hilf.erase(0,(find_2_3-2)+sizeof(s_2_3));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); 	   stream>>m_A3;
  						   ++count;
						  } 


					 size_t find_3_1=0;
						  find_3_1=hilf.find(s_3_1)+1;
					  
						  if(find_3_1)
						  {hilf.erase(0,(find_3_1-2)+sizeof(s_3_1));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); 	   stream>>m_B1;
  						   ++count;
						  }              


					  size_t find_3_2=0;
						  find_3_2=hilf.find(s_3_2)+1;
					  
						  if(find_3_2)
						  {hilf.erase(0,(find_3_2-2)+sizeof(s_3_2));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); 	   stream>>m_B2;
  						   ++count;
						  } 


					  size_t find_4_1=0;
						  find_4_1=hilf.find(s_4_1)+1;
					  
						  if(find_4_1)
						  {hilf.erase(0,(find_4_1-2)+sizeof(s_4_1));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); 	   stream>>m_C1;
  						   ++count;
						  }              


					  size_t find_4_2=0;
						  find_4_2=hilf.find(s_4_2)+1;
					  
						  if(find_4_2)
						  {hilf.erase(0,(find_4_2-2)+sizeof(s_4_2));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); 	   stream>>m_C2;
  						   ++count;
						  }
						  

					  size_t find_5_1=0;
						  find_5_1=hilf.find(s_5_1)+1;
					  
						  if(find_5_1)
						  {hilf.erase(0,(find_5_1-2)+sizeof(s_5_1));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); 	   stream>>m_r0;
  						   ++count;
						  }

                   //[OUTER_ORIENTATION]
  				   //char s_6_01[]="CALIB_OUTER_DATE=";
					  size_t find_6_01=0;
						  find_6_01=hilf.find(s_6_01)+1;
					  
						  if(find_6_01)
						  {hilf.erase(0,(find_6_01-2)+sizeof(s_6_01));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); m_calib_outer_date=stream.str();
  						   ++count;
						  }              
 				   
  				   //char s_6_02[]="CALIB_OUTER_PERSON=";
					  size_t find_6_02=0;
						  find_6_02=hilf.find(s_6_02)+1;
					  
						  if(find_6_02)
						  {hilf.erase(0,(find_6_02-2)+sizeof(s_6_02));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); m_calib_outer_person=stream.str();
  						   ++count;
						  }              
  				   
  				   //char s_6_03[]="CALIB_OUTER_COMMENTS=";	  
					  size_t find_6_03=0;
						  find_6_03=hilf.find(s_6_03)+1;
					  
						  if(find_6_03)
						  {hilf.erase(0,(find_6_03-2)+sizeof(s_6_03));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); m_calib_outer_comments=stream.str();
  						   ++count;
						  }              

					  size_t find_6_1=0;
						  find_6_1=hilf.find(s_6_1)+1;
					  
						  if(find_6_1==1)
						  {hilf.erase(0,(find_6_1-2)+sizeof(s_6_1));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); double m_OX=0.0;   stream>>m_OX;
						   m_O.set_X(m_OX);
  						   ++count;
						  }              


					  size_t find_6_2=0;
						  find_6_2=hilf.find(s_6_2)+1;
					  
						  if(find_6_2==1)
						  {hilf.erase(0,(find_6_2-2)+sizeof(s_6_2));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); double m_OY=0.0;   stream>>m_OY;
						   m_O.set_Y(m_OY);
  						   ++count;
						  } 

						  
					  size_t find_6_3=0;
						  find_6_3=hilf.find(s_6_3)+1;
					  
						  if(find_6_3==1)
						  {hilf.erase(0,(find_6_3-2)+sizeof(s_6_3));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); double m_OZ=0.0;  stream>>m_OZ;
						   m_O.set_Z(m_OZ);
  						   ++count;
						  } 


					  size_t find_7_1=0;
						  find_7_1=hilf.find(s_7_1)+1;
					  
						  if(find_7_1==1)
						  {hilf.erase(0,(find_7_1-2)+sizeof(s_7_1));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); 	   stream>>m_rotX;
  						   ++count;
						  }              


					  size_t find_7_2=0;
						  find_7_2=hilf.find(s_7_2)+1;
					  
						  if(find_7_2==1)
						  {hilf.erase(0,(find_7_2-2)+sizeof(s_7_2));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); 	   stream>>m_rotY;
  						   ++count;
						  } 

						  
					  size_t find_7_3=0;
						  find_7_3=hilf.find(s_7_3)+1;
					  
						  if(find_7_3==1)
						  {hilf.erase(0,(find_7_3-2)+sizeof(s_7_3));
						   stringstream stream; stream<<hilf.c_str();
						   hilf.erase(); 	   stream>>m_rotZ;
  						   ++count;
						  } 


	               //[BORESIDE_ALIGNEMENT]
				   //char s_8_1[]="CALIB_BORESIDE_DATE=";
				   size_t find_8_1=0;
  						  find_8_1=hilf.find(s_8_1)+1;
				  					  
  						  if(find_8_1)
  						  {hilf.erase(0,(find_8_1-2)+sizeof(s_8_1));
  						   stringstream stream; stream<<hilf.c_str();
  						   hilf.erase(); 	   m_calib_boreside_date=stream.str();;
  						   ++count;
  						  } 
				   
				   //char s_8_2[]="CALIB_BORESIDE_PERSON=";
				   size_t find_8_2=0;
  						  find_8_2=hilf.find(s_8_2)+1;
				  					  
  						  if(find_8_2)
  						  {hilf.erase(0,(find_8_2-2)+sizeof(s_8_2));
  						   stringstream stream; stream<<hilf.c_str();
  						   hilf.erase(); 	   m_calib_boreside_person=stream.str();;
  						   ++count;
  						  } 
  						  
				   //char s_8_3[]="CALIB_BORESIDE_COMMENTS=";
				   size_t find_8_3=0;
  						  find_8_3=hilf.find(s_8_3)+1;
				  					  
  						  if(find_8_3)
  						  {hilf.erase(0,(find_8_3-2)+sizeof(s_8_3));
  						   stringstream stream; stream<<hilf.c_str();
  						   hilf.erase(); 	  m_calib_boreside_comments=stream.str();
  						   ++count;
  						  } 
  						  
				   //char s_8_4[]="B_dx=";
				   size_t find_8_4=0;
  						  find_8_4=hilf.find(s_8_4)+1;
				  					  
  						  if(find_8_4)
  						  {hilf.erase(0,(find_8_4-2)+sizeof(s_8_4));
  						   stringstream stream; stream<<hilf.c_str();
  						   hilf.erase(); 	   stream>>m_B_dx;
  						   ++count;
  						  }
  						  
				   //char s_8_5[]="B_dy=";
				   size_t find_8_5=0;
  						  find_8_5=hilf.find(s_8_5)+1;
				  					  
  						  if(find_8_5==1)
  						  {hilf.erase(0,(find_8_5-2)+sizeof(s_8_5));
  						   stringstream stream; stream<<hilf.c_str();
  						   hilf.erase(); 	   stream>>m_B_dy;
  						   ++count;
  						  } 
  						  
				   //char s_8_6[]="B_dz=";
				   size_t find_8_6=0;
  						  find_8_6=hilf.find(s_8_6)+1;
				  					  
  						  if(find_8_6==1)
  						  {hilf.erase(0,(find_8_6-2)+sizeof(s_8_6));
  						   stringstream stream; stream<<hilf.c_str();
  						   hilf.erase(); 	   stream>>m_B_dz;
  						   ++count;
  						  } 
  						  
				   //char s_8_7[]="B_rotx=";
				   size_t find_8_7=0;
  						  find_8_7=hilf.find(s_8_7)+1;
				  					  
  						  if(find_8_7==1)
  						  {hilf.erase(0,(find_8_7-2)+sizeof(s_8_7));
  						   stringstream stream; stream<<hilf.c_str();
  						   hilf.erase(); 	   stream>>m_B_rotx;
  						   ++count;
  						  } 
  						  
				   //char s_8_8[]="B_roty=";
				   size_t find_8_8=0;
  						  find_8_8=hilf.find(s_8_8)+1;
				  					  
  						  if(find_8_8==1)
  						  {hilf.erase(0,(find_8_8-2)+sizeof(s_8_8));
  						   stringstream stream; stream<<hilf.c_str();
  						   hilf.erase(); 	   stream>>m_B_roty;
  						   ++count;
  						  }
  						  
				   //char s_8_9[]="B_rotz=";
				   size_t find_8_9=0;
  						  find_8_9=hilf.find(s_8_9)+1;
				  					  
  						  if(find_8_9==1)
  						  {hilf.erase(0,(find_8_9-2)+sizeof(s_8_9));
  						   stringstream stream; stream<<hilf.c_str();
  						   hilf.erase(); 	   stream>>m_B_rotz;
  						   ++count;
  						  } 
			  							
				}//END if....
	 }//END while()

	 SET_TXT.close();
	 SET_TXT.clear();
	 
	 if(count!=41)
		 return false;

	return true;
}

bool  CCam_bore::write_in_ini(const char *datname)
{
 ofstream SET_TXT(datname,ios_base::out);  
	 
 //SET_TXT.open(datname); 
 if(!SET_TXT) { return false; }
 else
 {  
	SET_TXT.precision(10);
	SET_TXT.setf(ios::left,ios::showpoint);
	SET_TXT.setf(ios::showbase);
		
	SET_TXT<<"[GENERAL]";
	SET_TXT<<std::endl<<"CAMERA_NAME="				<<(*this).m_camera_name;
	SET_TXT<<std::endl<<"//in [pixel]";
	SET_TXT<<std::endl<<"SENSOR_WIDTH_PIX="			<<(*this).m_pix_row;
	SET_TXT<<std::endl<<"SENSOR_HEIGHT_PIX="		<<(*this).m_pix_col;
	SET_TXT<<std::endl<<"CHANNELS="					<<(*this).m_channels;
	SET_TXT<<std::endl<<"CAMERA_SERIAL_NUMBER="		<<(*this).m_camera_serial_number;
	SET_TXT<<std::endl<<"//pixel size in [mm]";
	SET_TXT<<std::endl<<"PIXELSIZE="				<<(*this).m_pix_size;
	SET_TXT<<std::endl<<"";
	SET_TXT<<std::endl<<"[OBJECTIV]";
	SET_TXT<<std::endl<<"OBJECTIV_NAME="			<<(*this).m_objectiv_name;
	SET_TXT<<std::endl<<"//focal length in [mm]";
	SET_TXT<<std::endl<<"FOCAL_LENGTH="				<<(*this).m_focal_length;
	SET_TXT<<std::endl<<"OBJECTIV_SERIAL_NUMBER="	<<(*this).m_objectiv_serial_number;
	SET_TXT<<std::endl<<"";
	SET_TXT<<std::endl<<"[INNER_ORIENTATION]";
	SET_TXT<<std::endl<<"CALIB_INNER_DATE="			<<(*this).m_calib_inner_date;
	SET_TXT<<std::endl<<"CALIB_INNER_PERSON="		<<(*this).m_calib_inner_person;
	SET_TXT<<std::endl<<"CALIB_INNER_COMMENTS="		<<(*this).m_calib_inner_comments;
	SET_TXT<<std::endl<<"//focal length calibrated [mm]";
	SET_TXT<<std::endl<<"c=-"						<<fabs((*this).m_c);
	SET_TXT<<std::endl<<"//principal point [mm]";
	SET_TXT<<std::endl<<"xh="						<<(*this).m_xh;
	SET_TXT<<std::endl<<"yh="						<<(*this).m_yh;
	SET_TXT<<std::endl<<"//distorsion radial";
	SET_TXT<<std::endl<<"a1="						<<(*this).m_A1;
	SET_TXT<<std::endl<<"a2="						<<(*this).m_A2;
	SET_TXT<<std::endl<<"a3="						<<(*this).m_A3;
	SET_TXT<<std::endl<<"//distorsion asymmetric and tangential"; 
	SET_TXT<<std::endl<<"b1="						<<(*this).m_B1;
	SET_TXT<<std::endl<<"b2="						<<(*this).m_B2;
	SET_TXT<<std::endl<<"//distorsion affinity and shearing";
	SET_TXT<<std::endl<<"c1="						<<(*this).m_C1;
	SET_TXT<<std::endl<<"c2="						<<(*this).m_C2;
	SET_TXT<<std::endl<<"//r0-parameter";
	SET_TXT<<std::endl<<"r0="						<<(*this).m_r0;
	SET_TXT<<std::endl<<"";
	SET_TXT<<std::endl<<"[OUTER_ORIENTATION]";
	SET_TXT<<std::endl<<"CALIB_OUTER_DATE="			<<(*this).m_calib_outer_date;
	SET_TXT<<std::endl<<"CALIB_OUTER_PERSON="		<<(*this).m_calib_outer_person;
	SET_TXT<<std::endl<<"CALIB_OUTER_COMMENTS="		<<(*this).m_calib_outer_comments;
	SET_TXT<<std::endl<<"// principal point [mm]";
	SET_TXT<<std::endl<<"dx="						<<(*this).m_O.get_X();
	SET_TXT<<std::endl<<"dy="						<<(*this).m_O.get_Y();
	SET_TXT<<std::endl<<"dz="						<<(*this).m_O.get_Z();		
	SET_TXT<<std::endl<<"rotx="						<<(*this).get_rotX();
	SET_TXT<<std::endl<<"roty="						<<(*this).get_rotY();
	SET_TXT<<std::endl<<"rotz="						<<(*this).get_rotZ();
	SET_TXT<<std::endl<<"";
	SET_TXT<<std::endl<<"[BORESIDE_ALIGNEMENT]";
	SET_TXT<<std::endl<<"CALIB_BORESIDE_DATE="		<<(*this).m_calib_boreside_date;
	SET_TXT<<std::endl<<"CALIB_BORESIDE_PERSON="	<<(*this).m_calib_boreside_person;
	SET_TXT<<std::endl<<"CALIB_BORESIDE_COMMENTS="  <<(*this).m_calib_boreside_comments;
	SET_TXT<<std::endl<<"// translation [mm]";
	SET_TXT<<std::endl<<"B_dx="						<<(*this).m_B_dx;
	SET_TXT<<std::endl<<"B_dy="						<<(*this).m_B_dy;
	SET_TXT<<std::endl<<"B_dz="						<<(*this).m_B_dz;
	SET_TXT<<std::endl<<"// orientation angle [rad]";
	SET_TXT<<std::endl<<"B_rotx="					<<(*this).m_B_rotx;
	SET_TXT<<std::endl<<"B_roty="					<<(*this).m_B_roty;
	SET_TXT<<std::endl<<"B_rotz="					<<(*this).m_B_rotz;

  SET_TXT.close();
  SET_TXT.clear();
 }
	
 return true;
}
