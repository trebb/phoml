// photoST.cpp : Definiert den Einstiegspunkt f�r die DLL-Anwendung.

//system includes c++
#include <iostream>
#include <vector>
#include <string>

//for gcc compiler
#include "../Basics/point.h"
#include "../Photo/bpoint.h"
#include "../boreside_alignement/cam_bore.h"
#include "../Photo/forward_intersection.h"

//include boreside_transformation
#include "../transformation/applanix.h"
#include "../boreside_alignement/boreside_transformation.h"

//#endif

//set the compiler specific calls for the interface export
#if defined(_MSC_VER)
#include <windows.h>
#endif

//own header with the "C" export interface
#include "photoST.h"

//declaration is included in the header file
#if defined(_MSC_VER)
#define _DLL_EXPORT

#if defined(_MS_VB)
#define STDCALL __stdcall
#else
#define STDCALL
#endif

#else
#define _DLL_EXPORT
#define STDCALL
#endif


using namespace std;


//###################################
//cpp values for save data structures

// //intern data structure
static intern I;

//cam list for the input
static std::vector<CCam_bore> lCam_bore;

//picure point list for the input
static std::vector<BPoint> lBPoint;


//controll values
static int m_saved_cams = 0;
static int m_used_cams  = 0;

static bool m_is_set_mn										=false;
static bool m_is_set_LocalMeasurementPoint					=false;
static bool m_is_set_GlobalMeasurementPoint					=false;
static bool m_is_set_GlobalCarReferencePoint				=false;
static bool m_is_set_GlobalCarReferencePoint_std			=false;
static bool m_is_set_GlobalReferenceFrame					=false;
static bool m_is_set_RefGroundSurface						=false;
static bool m_is_set_GlobalCarReferencePoint_CamSetGlobal	=false;
static bool m_is_set_distance_epi							=false;

static bool m_is_calc_vws							=false;
static bool m_is_calc_bore							=false;
static bool m_is_calc_lokal_RefGroundSurface		=false;
static bool m_is_calc_epipolarline					=false;




//#### c style funktions ####


//#### picture koordinates #####

_DLL_EXPORT double STDCALL get_m()
{
  return I.m_m;
}

_DLL_EXPORT double STDCALL get_n()
{
  return I.m_n;
}


//#### local ####

_DLL_EXPORT double STDCALL get_x_local()
{
  return I.m_x_local;
}

_DLL_EXPORT double STDCALL get_y_local()
{
  return I.m_y_local;
}

_DLL_EXPORT double STDCALL get_z_local()
{
  return I.m_z_local;
}

_DLL_EXPORT double STDCALL get_stdx_local()
{
  return I.m_stdx_local;
}

_DLL_EXPORT double STDCALL get_stdy_local()
{
  return I.m_stdy_local;
}

_DLL_EXPORT double STDCALL get_stdz_local()
{
  return I.m_stdz_local;
}


//#### global ####

_DLL_EXPORT double STDCALL get_x_global()
{
  return I.m_x_global;
}

_DLL_EXPORT double STDCALL get_y_global()
{
  return I.m_y_global;
}

_DLL_EXPORT double STDCALL get_z_global()
{
  return I.m_z_global;
}

_DLL_EXPORT double STDCALL get_stdx_global()
{
  return I.m_stdx_global;
}

_DLL_EXPORT double STDCALL get_stdy_global()
{
  return I.m_stdy_global;
}

_DLL_EXPORT double STDCALL get_stdz_global()
{
  return I.m_stdz_global;
}

// #### Car Reference Point

_DLL_EXPORT double STDCALL get_Easting()
{
  return I.m_Easting;
}

_DLL_EXPORT double STDCALL get_Northing()
{
  return I.m_Northing;
}

_DLL_EXPORT double STDCALL get_eHeigth()
{
  return I.m_eHeigth;
}

_DLL_EXPORT double STDCALL get_roll()
{
  return I.m_roll;
}

_DLL_EXPORT double STDCALL get_pitch()
{
  return I.m_pitch;
}

_DLL_EXPORT double STDCALL get_heading()
{
  return I.m_heading;
}

_DLL_EXPORT double STDCALL get_latitude()
{
  return I.m_latitude;
}

_DLL_EXPORT double STDCALL get_longitude()
{
  return I.m_longitude;
}


//funktion for photogrammetrie lib

_DLL_EXPORT int STDCALL addCam( int pix_col,
                                int pix_row,
                                double pix_size,
                                double dx,
                                double dy,
                                double dz,
                                double omega,
                                double phi,
                                double kappa,
                                double c,
                                double xh,
                                double yh,
                                double A1,
                                double A2,
                                double A3,
                                double B1,
                                double B2,
                                double C1,
                                double C2,
                                double R0,
                                double B_dx,
                                double B_dy,
                                double B_dz,
                                double B_ddx,
                                double B_ddy,
                                double B_ddz,
                                double B_rotx,
                                double B_roty,
                                double B_rotz,
                                double B_drotx,
                                double B_droty,
                                double B_drotz
                                )
{
  if(lCam_bore.size() && ( m_saved_cams == (m_used_cams+2)))
    m_saved_cams = m_used_cams;

  CCam_bore cam(
                pix_row,pix_col,pix_size,
                dx,dy,dz,
                omega,phi,kappa,
                c,xh,yh,
                A1,A2,A3,
                B1,B2,
                C1,C2,
                R0,
                B_dx, B_dy, B_dz,
                B_ddx, B_ddy, B_ddz,
                B_rotx, B_roty, B_rotz,
                B_drotx, B_droty, B_drotz);

  //cout << endl <<endl <<endl << "#### cam " << lCam_bore.size() << "  #####" <<endl<<endl;
  //cout << cam << flush;

  //todo cam value test -> only then save into the list
  lCam_bore.push_back(cam);

  m_saved_cams+=1;
  return 1;
}

_DLL_EXPORT int STDCALL addCam2(char* psz_ini_file)
{
  if(lCam_bore.size() && ( m_saved_cams == (m_used_cams+2)))
    m_saved_cams = m_used_cams;

  //todo test the input parameter!

  //create a boreside cam
  CCam_bore cam;
  //load the ini file
  bool t = cam.read_from_ini(psz_ini_file);
  //add to the cam list
  lCam_bore.push_back(cam);

  //cout << cam << flush;


  //control
  m_saved_cams+=1;

  return static_cast<int>(t);
}

_DLL_EXPORT int STDCALL addBPoint(double m, double n)
{	
  if( lCam_bore.size() && ( m_saved_cams == (m_used_cams+1) ) )
    {
      //create a new picture point
      CCam_bore cam_bore(*lCam_bore.rbegin());
      Cam *cam=new Cam(cam_bore);

      BPoint bp(*cam,m,n);

      //set the values temporary into the intern data structure (not necessary)
      I.m_m = m;
      I.m_n = n;

      //cout << endl <<endl << "BP mn(" << bp.get_m() << " , " << bp.get_n()<< ")";
      //cout << endl <<endl << "BP cam(" << bp.get_Cam();

      //save the picture into the global list
      lBPoint.push_back( bp );

      //control
      m_is_set_mn = true;
      m_used_cams+=1;

      return true;
    }
  else
    {
      //todo error string
      cerr << "ERROR -> create BPoint not possible!";
      return false;
    }
}

_DLL_EXPORT int STDCALL addBPoint2( int pix_col,
                                    int pix_row,
                                    double pix_size,
                                    double dx, 
                                    double dy,
                                    double dz,
                                    double omega,
                                    double phi,
                                    double kappa,
                                    double c,
                                    double xh, 
                                    double yh, 
                                    double A1,
                                    double A2,
                                    double A3,
                                    double B1,
                                    double B2,
                                    double C1,
                                    double C2,
                                    double R0,
                                    double B_dx,
                                    double B_dy,
                                    double B_dz,
                                    double B_ddx,
                                    double B_ddy,
                                    double B_ddz,
                                    double B_rotx,
                                    double B_roty,
                                    double B_rotz,
                                    double B_drotx,
                                    double B_droty,
                                    double B_drotz,
                                    double m,
                                    double n
                                    )
{
  //create cam
  CCam_bore cam_t(
                  pix_row,pix_col,pix_size,
                  dx,dy,dz,
                  omega,phi,kappa,
                  c,xh,yh,
                  A1,A2,A3,
                  B1,B2,
                  C1,C2,
                  R0,
                  B_dx, B_dy, B_dz,
                  B_ddx, B_ddy, B_ddz,
                  B_rotx, B_roty, B_rotz,
                  B_drotx, B_droty, B_drotz);
	
  lCam_bore.push_back(cam_t);

  CCam_bore cam_bore(*lCam_bore.rbegin());
  Cam *cam=new Cam(cam_bore);

  //create a new picture point
  BPoint bp(*cam,m,n);

  //set the values temporary into the intern data structure (not necessary)
  I.m_m = m;
  I.m_n = n;

  //save the picture point into the global list
  lBPoint.push_back( bp );

  //control
  m_is_set_mn = true;
  m_saved_cams+=1;
  m_used_cams+=1;

  //todo error handling for the different classes
  return 1;
}

_DLL_EXPORT void STDCALL addGlobalCarReferencePoint(double Easting, double Northing, double eHeigth, double roll, double pitch, double heading, double latitude, double longitude)
{
  I.m_Easting 	= Easting;
  I.m_Northing 	= Northing;
  I.m_eHeigth 	= eHeigth;
  I.m_roll 		= roll;
  I.m_pitch 	= pitch;
  I.m_heading 	= heading;
  I.m_latitude 	= latitude;
  I.m_longitude = longitude;

  //todo test the data values

  //change the applanix rotation angels into the math rotation angels
  CApplanix appl;
  appl.calc_approximately_meridian_convergence_degree(I.m_Easting,I.m_latitude,I.m_heading);
  appl.compare_gps_coosystem_degree_to_math_coosystem_pi(I.m_roll,I.m_pitch,I.m_heading,I.m_droll,I.m_dpitch,I.m_dheading);

  m_is_set_GlobalCarReferencePoint	=true;
}

_DLL_EXPORT void STDCALL addGlobalCarReferencePoint_CamSetGlobal(double Easting, double Northing, double eHeigth, double roll, double pitch, double heading, double latitude, double longitude)
{
  //todo test if cam initialize



  I.m_Easting 	= Easting;
  I.m_Northing 	= Northing;
  I.m_eHeigth 	= eHeigth;
  I.m_roll 		= roll;
  I.m_pitch 	    = pitch;
  I.m_heading 	= heading;
  I.m_latitude 	= latitude;
  I.m_longitude   = longitude;

  //todo test the data values

  //change the applanix rotation angels into the math rotation angels
  CApplanix appl;
  appl.calc_approximately_meridian_convergence_degree(I.m_Easting,I.m_latitude,I.m_heading);
  appl.compare_gps_coosystem_degree_to_math_coosystem_pi(I.m_roll,I.m_pitch,I.m_heading,I.m_droll,I.m_dpitch,I.m_dheading);



  //set the new camera orientation in global coordinates

  //bore-sight transformation
  Point BT;
  BT = (lCam_bore.rbegin())->get_B();
  Rot BR(lCam_bore.rbegin()->get_B_rotx(),lCam_bore.rbegin()->get_B_roty(),lCam_bore.rbegin()->get_B_rotz());

  //global transformation
  Point GT(I.m_Easting,I.m_Northing,I.m_eHeigth);
  Rot GR(I.m_roll,I.m_pitch,I.m_heading);

  Point P0_cam(0.0,0.0,0.0); //new coordinate center of the camera  (camera coordinate system)
  Point P_car,P_global;

  P_car = P0_cam.Rotation(BT,BR);
  P_global = P_car.Rotation(GT,GR);

  Rot R_global( GR.get_Matrix().MatMult(BR) );
  double r=0.0,p=0.0,h=0.0;
  R_global.get_RotWinkel(r,p,h);

  cout<<endl<<"Pos/rot CAM:"<<P_global<<" / "<<r<<","<<p<<","<<h;

  //global cam list
  lCam_bore.rbegin()->set_O(P_global);
  lCam_bore.rbegin()->set_rotX(r);
  lCam_bore.rbegin()->set_rotY(p);
  lCam_bore.rbegin()->set_rotZ(h);

  lBPoint.rbegin()->get_Cam_Ref().set_O(P_global);
  lBPoint.rbegin()->get_Cam_Ref().set_rotX(r);
  lBPoint.rbegin()->get_Cam_Ref().set_rotY(p);
  lBPoint.rbegin()->get_Cam_Ref().set_rotZ(h);

  m_is_set_GlobalCarReferencePoint = true;
  m_is_set_GlobalCarReferencePoint_CamSetGlobal = true;
}

_DLL_EXPORT void STDCALL addGlobalCarReferencePoint_std(double dEasting, double dNorthing, double deHeigth, double droll, double dpitch, double dheading)
{
  I.m_dEasting 	= dEasting;
  I.m_dNorthing = dNorthing;
  I.m_deHeigth 	= deHeigth;
  I.m_droll 	= droll;
  I.m_dpitch 	= dpitch;
  I.m_dheading 	= dheading;

  //todo test the data values

  m_is_set_GlobalCarReferencePoint_std=true;
}

_DLL_EXPORT void STDCALL setGlobalReferenceFrame()
{
  m_is_set_GlobalReferenceFrame = true;
  //todo have to be create
}

_DLL_EXPORT int STDCALL addGlobalMeasurementPoint(double Easting, double Northing, double eHeigth)
{
  I.m_x_global 	= Easting;
  I.m_y_global 	= Northing;
  I.m_z_global 	= eHeigth;

  m_is_set_GlobalMeasurementPoint	= true;

  return 1;
}

_DLL_EXPORT int STDCALL addLocalMeasurementPoint(double X, double Y, double Z)
{
  I.m_x_local 	= X;
  I.m_y_local 	= Y;
  I.m_z_local 	= Z;

  m_is_set_LocalMeasurementPoint	= true;

  return 1;
}

_DLL_EXPORT int STDCALL addRefGroundSurface(double nx, double ny, double nz, double d)
{
  I.m_nx = nx;
  I.m_ny = ny;
  I.m_nz = nz;
  I.m_d  = d;

  m_is_set_RefGroundSurface = true;

 return 1;
}

_DLL_EXPORT int STDCALL setDistanceForEpipolarLine(double d)
{
 if(d>0 && d<100000)
 {
  I.m_distance_epi = d;
  m_is_set_distance_epi = true;
  return 1;
 }
 else
 {
  cerr<<"Error in epipolar distance!";
  return 0;
 }
}

//delete all parameters
_DLL_EXPORT void STDCALL del_all()
{
	I.m_m=0.0;
	I.m_n=0.0;

	I.m_x_local=0.0;
	I.m_y_local=0.0;
	I.m_z_local=0.0;

	I.m_stdx_local=0.0;
	I.m_stdy_local=0.0;
	I.m_stdz_local=0.0;

	I.m_x_global=0.0;
	I.m_y_global=0.0;
	I.m_z_global=0.0;

	I.m_stdx_global=0.0;
	I.m_stdy_global=0.0;
	I.m_stdz_global=0.0;

	//car reference positon
	I.m_Easting=0.0;
	I.m_Northing=0.0;
	I.m_eHeigth=0.0;
	I.m_roll=0.0;
	I.m_pitch=0.0;
	I.m_heading=0.0;
	I.m_latitude=0.0;
	I.m_longitude=0.0;

	I.m_dEasting=0.0;
	I.m_dNorthing=0.0;
	I.m_deHeigth=0.0;
	I.m_droll=0.0;
	I.m_dpitch=0.0;
	I.m_dheading=0.0;

	//parameter of the geodetic reference frame
	I.m_idontknow=0.0;

		//reference ground plane
	I.m_nx=0.0;
	I.m_ny=0.0;
	I.m_nz=0.0;
	I.m_d=0.0;

	lCam_bore.erase(lCam_bore.begin(),lCam_bore.end());
	lCam_bore.clear();

	//hack not very nice
	vector<BPoint>::iterator iBP = lBPoint.begin();
		while(iBP !=lBPoint.end())
		{
			delete &iBP->get_Cam();
			++iBP;
		}
	lBPoint.erase(lBPoint.begin(),lBPoint.end());
	lBPoint.clear();


	//controll values
	m_saved_cams = 0;
	m_used_cams  = 0;

	m_is_set_mn										=false;
	m_is_set_LocalMeasurementPoint					=false;
	m_is_set_GlobalMeasurementPoint					=false;
	m_is_set_GlobalCarReferencePoint				=false;
	m_is_set_GlobalCarReferencePoint_std			=false;
	m_is_set_GlobalReferenceFrame					=false;
	m_is_set_RefGroundSurface						=false;
	m_is_set_GlobalCarReferencePoint_CamSetGlobal	=false;
	m_is_set_distance_epi							=false;

	m_is_calc_vws							=false;
	m_is_calc_bore							=false;
	m_is_calc_lokal_RefGroundSurface		=false;
	m_is_calc_epipolarline					=false;



}

_DLL_EXPORT void STDCALL show_variabes_and_infos()
{
	//test
	cout.precision(15);
	cout.setf(ios::left,ios::showpoint);
	cout.setf(ios::showbase);

	cout<<endl;
    cout<<endl<<"#### Begin - output / input values of the photogrammetrie library ########";

	cout<<endl;
	cout<<endl<<" size of the camera list (lCam_bore)  :"<<lCam_bore.size();

	cout<<endl<<" size of the BPoint list (lBPoint)    :"<<lBPoint.size();

	cout<<endl<<" m_is_set_mn bool:"<<m_is_set_mn;
	if(m_is_set_mn)
	{
		if(lBPoint.size())
		{
		        int i=1;
		        cout<<endl;

		        vector<BPoint>::iterator iBP = lBPoint.begin();
				while(iBP !=lBPoint.end())
				{
					cout<<endl<<"  pixel pair "<<i<<" : ( "<<iBP->get_m()<<" , "<<iBP->get_n()<<" )";
					++iBP;
					++i;
				}
		}
		else
		{
			cout<<endl;
			cout<<endl<<"  pixel pair :( "<<I.m_m<<" , "<<I.m_n<<" )";
		}
		cout<<endl<<flush;

	}


	cout<<endl<<" m_is_set_LocalMeasurementPoint bool  :"<<m_is_set_LocalMeasurementPoint;
    if(m_is_set_LocalMeasurementPoint)
    {
    	    cout<<endl;
    	    //local coordinate system for the output (camera_coordinate system)
    		cout<<endl<<"  m_x_local      :"<<I.m_x_local;
    		cout<<endl<<"  m_y_local      :"<<I.m_y_local;
    		cout<<endl<<"  m_z_local      :"<<I.m_z_local;

    		cout<<endl<<"  m_stdx_local   :"<<I.m_stdx_local;
    		cout<<endl<<"  m_stdy_local   :"<<I.m_stdy_local;
    		cout<<endl<<"  m_stdz_local   :"<<I.m_stdz_local;
    		cout<<endl<<flush;
    }

	cout<<endl<<" m_is_set_GlobalMeasurementPoint bool :"<<m_is_set_GlobalMeasurementPoint;
	if(m_is_set_GlobalMeasurementPoint)
	{
		cout<<endl;
		//global coordinate system for the output (global coordinate system -> depends of the input system)
		cout<<endl<<"  m_x_global     :"<<I.m_x_global;
		cout<<endl<<"  m_y_global     :"<<I.m_y_global;
		cout<<endl<<"  m_z_global     :"<<I.m_z_global;

		cout<<endl<<"  m_stdx_global  :"<<I.m_stdx_global;
		cout<<endl<<"  m_stdy_global  :"<<I.m_stdy_global;
		cout<<endl<<"  m_stdz_global  :"<<I.m_stdz_global;
		cout<<endl<<flush;
	}

	cout<<endl<<" m_is_set_GlobalCarReferencePoint bool:"<<m_is_set_GlobalCarReferencePoint;
	if(m_is_set_GlobalCarReferencePoint)
	{
		cout<<endl;
		//global reference point of the car
		cout<<endl<<"  m_Easting      :"<<I.m_Easting;
		cout<<endl<<"  m_Northing     :"<<I.m_Northing;
		cout<<endl<<"  m_eHeigth      :"<<I.m_eHeigth;
		cout<<endl<<"  m_roll         :"<<I.m_roll;
		cout<<endl<<"  m_pitch        :"<<I.m_pitch;
		cout<<endl<<"  m_heading      :"<<I.m_heading;
		cout<<endl<<"  m_latitude     :"<<I.m_latitude;
		cout<<endl<<"  m_longitude    :"<<I.m_longitude;
		cout<<endl<<flush;
	}

	cout<<endl<<" m_is_set_GlobalCarReferencePoint_std bool:"<<m_is_set_GlobalCarReferencePoint_std;
    if(m_is_set_GlobalCarReferencePoint_std)
    {
    	cout<<endl;
    	cout<<endl<<"  m_dEasting     :"<<I.m_dEasting;
		cout<<endl<<"  m_dNorthing    :"<<I.m_dNorthing;
		cout<<endl<<"  m_deHeigth     :"<<I.m_deHeigth;
		cout<<endl<<"  m_droll        :"<<I.m_droll;
		cout<<endl<<"  m_dpitch       :"<<I.m_dpitch;
		cout<<endl<<"  m_dheading     :"<<I.m_dheading;
		cout<<endl<<flush;

	}

	cout<<endl<<" m_is_set_GlobalReferenceFrame bool:"<<m_is_set_GlobalReferenceFrame;
	if(m_is_set_GlobalReferenceFrame)
	{
		cout<<endl;
		//todo variable coordinate systems
		cout<<endl<<"  WGS 84 / UTM";
		cout<<endl<<flush;
	}

	cout<<endl<<" m_is_set_RefGroundSurface bool:"<<m_is_set_RefGroundSurface;
	if(m_is_set_RefGroundSurface)
	{
		cout<<endl;
		cout<<endl<<"  reference ground plane: ("<<I.m_nx<<","<<I.m_ny<<","<<I.m_nz<<") p: "<<I.m_d;
		cout<<endl<<flush;
	}

	cout<<endl<<" m_is_set_GlobalCarReferencePoint_CamSetGlobal bool:"<< m_is_set_GlobalCarReferencePoint_CamSetGlobal ;
	if(m_is_set_GlobalCarReferencePoint_CamSetGlobal)
	{
		cout<<endl;
		//global reference point of the car
		cout<<endl<<"  m_Easting      :"<<I.m_Easting;
		cout<<endl<<"  m_Northing     :"<<I.m_Northing;
		cout<<endl<<"  m_eHeigth      :"<<I.m_eHeigth;
		cout<<endl<<"  m_roll         :"<<I.m_roll;
		cout<<endl<<"  m_pitch        :"<<I.m_pitch;
		cout<<endl<<"  m_heading      :"<<I.m_heading;
		cout<<endl<<"  m_latitude     :"<<I.m_latitude;
		cout<<endl<<"  m_longitude    :"<<I.m_longitude;
		cout<<endl<<flush;
	}

	cout<<endl<<" m_is_set_distance_epi bool:"<< m_is_set_distance_epi;
	if(m_is_set_distance_epi)
	{
		cout<<endl;
		cout<<endl<<"  distance for calculation a point on the epipolar line:   d: "<<I.m_distance_epi;
		cout<<endl<<flush;
	}

	cout<<endl;
	cout<<endl<<"#### End - output / input values of the photogrammetrie library ########";
	cout<<endl<<flush;
}


//calc
_DLL_EXPORT int STDCALL calculate()
{
  bool info = false;



  //calc local measurement point -> forward intersection
  if(lBPoint.size() > 1)
    {
      //calc forward intersection with min. 2 picture points
      Vorwaertsschnitt vws(lBPoint);
      Point p;
      p=vws.get_Schnittpunkt();

      //cout<<endl<<"intern P local:"<<p<<endl;

      if(vws.get_is_error())
        {
          cerr << endl << endl;
          cerr << "error in forward intersection!" <<flush;
        }
      else
        {

          I.m_x_local	=p.get_X();
          I.m_y_local	=p.get_Y();
          I.m_z_local	=p.get_Z();
          I.m_stdx_local=p.get_dX();
          I.m_stdy_local=p.get_dY();
          I.m_stdz_local=p.get_dZ();

          //control
          info=true;
          m_is_calc_vws=true;
          m_is_set_LocalMeasurementPoint=true;
        }
    }

	//calculate a point on the epipolarline
	if( 	lCam_bore.size() == 2 && lBPoint.size() == 1 &&
			m_is_set_distance_epi
			)
	{
	  Cam *cam = new Cam(*lCam_bore.rbegin());

	  BPoint bp = lBPoint.begin()->get_KernlinenPunkt( *cam , I.m_distance_epi );

	  delete cam;

	  I.m_m = bp.get_m();
	  I.m_n = bp.get_n();


	  m_is_set_distance_epi = false;
	  m_is_calc_epipolarline =true;
	  info=true;
	}

	//forward intersection from a pixel coordinate to a object ray into a plane
	//for e.g. mono photogrammetrie with one cam and informations about the ground surface
	if( 	lCam_bore.size() == 1 &&
			m_is_set_RefGroundSurface
			)
	{
			//create a plane
			Ebene E(I.m_nx,I.m_ny,I.m_nz,I.m_d);

			//rotation parameter boreside
			Point BT;
			BT = (lCam_bore.rbegin())->get_B();
			Rot BR(lCam_bore.rbegin()->get_B_rotx(),lCam_bore.rbegin()->get_B_roty(),lCam_bore.rbegin()->get_B_rotz());

			E=E.RotationRueck(BT,BR);

			Cam *cam = new Cam(*lCam_bore.rbegin());

			BPoint bp(*cam,I.m_m,I.m_n);

			Point p;
			p = bp.calc_mono_cam_to_plane_intersection(E);

			I.m_x_local	=p.get_X();
			I.m_y_local	=p.get_Y();
			I.m_z_local	=p.get_Z();
			I.m_stdx_local=p.get_dX();
			I.m_stdy_local=p.get_dY();
			I.m_stdz_local=p.get_dZ();

			delete cam;

			//control
			info=true;
			m_is_set_LocalMeasurementPoint=true;
			m_is_calc_lokal_RefGroundSurface=true;
	}


	//calc global measurement point > boreside calibration
	if( m_is_set_LocalMeasurementPoint && m_is_set_GlobalCarReferencePoint && m_is_set_GlobalReferenceFrame)
	{
		Point p;

		if(!m_is_set_GlobalCarReferencePoint_CamSetGlobal)
		{
			CBoreside_transformation bore(*lCam_bore.begin());

			if(!m_is_set_GlobalCarReferencePoint_std)
				I.m_dEasting=I.m_dNorthing=I.m_deHeigth=I.m_droll=I.m_dpitch=I.m_dheading=0.0;

			//cout<<endl<<"carpos: E: "<<m_Easting<<"  N:"<<m_Northing<<"  H:"<<m_eHeigth<<"  r:"<<m_roll<<"  p:"<<m_pitch<<"  h:"<<m_heading;
			bore.set_car_position_utm(I.m_Easting,I.m_Northing,I.m_eHeigth,I.m_roll,I.m_pitch,I.m_heading);

			//cout<<endl<<"intern P local: "<<m_x_local <<" "<< m_y_local <<" "<<  m_z_local;
			bore.set_local_koordinate( I.m_x_local , I.m_y_local , I.m_z_local );

			p=bore.get_utm_koordinate();
		}
		else
		{
			//for global coordinate into the forwardintersection function -- boresight transformation is not necessary
			Point tmp(I.m_x_local , I.m_y_local , I.m_z_local);
			tmp.set_dX(I.m_stdx_local);
			tmp.set_dY(I.m_stdy_local);
			tmp.set_dZ(I.m_stdz_local);
			//I=p;
			p=tmp;
		}

		I.m_x_global		=p.get_X();
		I.m_y_global		=p.get_Y();
		I.m_z_global		=p.get_Z();
		I.m_stdx_global	    =p.get_dX();
		I.m_stdy_global	    =p.get_dY();
		I.m_stdz_global	    =p.get_dZ();

		//control
		m_is_calc_bore = true;
		m_is_set_GlobalMeasurementPoint=true;
	}


	//backward calculation from a global point back to pixel coordinate
	//for e.g. paint the global Point XYZ into the picture
	if( 	lCam_bore.size() == 1 &&
			m_is_set_GlobalCarReferencePoint &&
			m_is_set_GlobalReferenceFrame &&
			m_is_set_GlobalMeasurementPoint
			)
	{
		    //calc the bore side transformation with the global car position
		    CBoreside_transformation bore(*lCam_bore.rbegin());

			CApplanix appl;
			//appl.calc_approximately_meridian_convergence_degree(I.m_Easting,I.m_latitude,I.m_heading);
			//appl.compare_gps_coosystem_degree_to_math_coosystem_pi(I.m_roll,I.m_pitch,I.m_heading,I.m_droll,I.m_dpitch,I.m_dheading);

			bore.set_car_position_utm(I.m_Easting,I.m_Northing,I.m_eHeigth,I.m_roll,I.m_pitch,I.m_heading);

			bore.set_utm_koordinate(I.m_x_global,I.m_y_global,I.m_z_global);

			Point P_local;
			P_local = bore.get_local_koordinate();

			Cam *cam = new Cam(*lCam_bore.rbegin());
		    BPoint bp(*cam,P_local.get_X(),P_local.get_Y(),P_local.get_Z());

		    I.m_m = bp.get_m();
		    I.m_n = bp.get_n();

		    delete cam;

			//control
			info=true;
			m_is_set_mn=true;
	}


	//backward calculation from a local point back to pixel coordinate
	//for e.g. paint the local Point XYZ into the picture
	if( 	lCam_bore.size() == 1 &&
			m_is_set_LocalMeasurementPoint
			)
	{
			Cam *cam = new Cam(*lCam_bore.rbegin());
		    BPoint bp(*cam, I.m_x_local , I.m_y_local , I.m_z_local );

		    I.m_m = bp.get_m();
		    I.m_n = bp.get_n();

		    delete cam;

		    //control
			info=true;
			m_is_set_mn=true;
	}



  return static_cast<int>(info);
}
