/*
 ============================================================================
 Name        : photoST.h
 Author      : Steffen Scheller
 Version     : 0.00X
 Copyright   : ©2010
 Description : C Zugriff auf Photogrammetrie (*.so,*.dll) / Code: C++, Ansi-style
 ============================================================================
*/

#ifndef __PHOTOST_h
#define __PHOTOST_h

//system includes c
#include <stdio.h>
#include <stdlib.h>

#define _MS_VB 0 //Activate __stdcall change to 1

#if defined(_MSC_VER)
#define _DLL_EXPORT __declspec(dllexport)

#if defined(_MS_VB)
#define STDCALL __stdcall
#else
#define STDCALL
#endif

#else
#define _DLL_EXPORT
#define STDCALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

  _DLL_EXPORT double STDCALL get_m();
  _DLL_EXPORT double STDCALL get_n();
  _DLL_EXPORT double STDCALL get_x_local();
  _DLL_EXPORT double STDCALL get_y_local();
  _DLL_EXPORT double STDCALL get_z_local();
  _DLL_EXPORT double STDCALL get_stdx_local();
  _DLL_EXPORT double STDCALL get_stdy_local();
  _DLL_EXPORT double STDCALL get_stdz_local();
  _DLL_EXPORT double STDCALL get_x_global();
  _DLL_EXPORT double STDCALL get_y_global();
  _DLL_EXPORT double STDCALL get_z_global();
  _DLL_EXPORT double STDCALL get_stdx_global();
  _DLL_EXPORT double STDCALL get_stdy_global();
  _DLL_EXPORT double STDCALL get_stdz_global();

  _DLL_EXPORT double STDCALL get_Easting();
  _DLL_EXPORT double STDCALL get_Northing();
  _DLL_EXPORT double STDCALL get_eHeigth();
  _DLL_EXPORT double STDCALL get_roll();
  _DLL_EXPORT double STDCALL get_pitch();
  _DLL_EXPORT double STDCALL get_heading();
  _DLL_EXPORT double STDCALL get_latitude();
  _DLL_EXPORT double STDCALL get_longitude();

  _DLL_EXPORT double STDCALL get_FP_Easting(int pos); //pos[0-3]
  _DLL_EXPORT double STDCALL get_FP_Northing(int pos);//pos[0-3]
  _DLL_EXPORT double STDCALL get_FP_eHeight(int pos); //pos[0-3]

  _DLL_EXPORT int STDCALL    addCam(int sensor_width_pix,int sensor_height_pix,double pix_size,double dx,double dy,double dz,double omega,double phi,double kappa,double c,double xh,double yh,double A1,double A2,double A3,double B1,double B2,double C1,double C2,double R0,double B_dx,double B_dy,double B_dz,double B_ddx,double B_ddy,double B_ddz,double B_rotx,double B_roty,double B_rotz,double B_drotx,double B_droty,double B_drotz);
  _DLL_EXPORT int STDCALL    addCam2(char* ini_file);
  _DLL_EXPORT int STDCALL    addBPoint(double m,double n);
  _DLL_EXPORT int STDCALL    addBPoint2(int sensor_width_pix,int sensor_height_pix,double pix_size,double dx,double dy,double dz,double omega,double phi,double kappa,double c,double xh,double yh,double A1,double A2,double A3,double B1,double B2,double C1,double C2,double R0,double B_dx,double B_dy,double B_dz,double B_ddx,double B_ddy,double B_ddz,double B_rotx,double B_roty,double B_rotz,double B_drotx,double B_droty,double B_drotz,double m,double n);
  _DLL_EXPORT void STDCALL   addGlobalCarReferencePoint(double Easting, double Northing, double Height, double roll, double pitch, double heading, double latitude, double longitude);
  _DLL_EXPORT void STDCALL   addGlobalCarReferencePoint_CamSetGlobal(double Easting, double Northing, double Height, double roll, double pitch, double heading, double latitude, double longitude);
  _DLL_EXPORT void STDCALL   addGlobalCarReferencePoint_std(double easting_sd, double northing_sd, double heigth_sd, double roll_sd, double pitch_sd, double heading_sd);
  _DLL_EXPORT int STDCALL    addGlobalMeasurementPoint(double Easting, double Northing, double Height);
  _DLL_EXPORT int STDCALL    addLocalMeasurementPoint(double X, double Y, double Z);
  _DLL_EXPORT int STDCALL    addRefGroundSurface(double nx, double ny, double nz, double d);
  _DLL_EXPORT void STDCALL   setGlobalReferenceFrame();
  _DLL_EXPORT int STDCALL    setDistanceForEpipolarLine(double d);
  _DLL_EXPORT void STDCALL   del_all();
  _DLL_EXPORT void STDCALL   showVariablesAndInfos();
  _DLL_EXPORT double STDCALL getVersionNumber();
  _DLL_EXPORT int STDCALL    calculate();

#ifdef __cplusplus
}
#endif


//intern data structure
struct intern
{
  //output parameter for backward calculation 3D to picture point
  double m_m;
  double m_n;

  //local coordinate system for the output (camera_coordinate system)
  double m_x_local;
  double m_y_local;
  double m_z_local;

  double m_stdx_local;
  double m_stdy_local;
  double m_stdz_local;

  //global coordinate system for the output (global coordinate system -> depends of the input system)
  double m_x_global;
  double m_y_global;
  double m_z_global;

  double m_stdx_global;
  double m_stdy_global;
  double m_stdz_global;

  //global reference point of the car
  double m_Easting,m_Northing,m_eHeight,m_roll,m_pitch,m_heading,m_latitude,m_longitude;
  double m_dEasting,m_dNorthing,m_deHeigth,m_droll,m_dpitch,m_dheading;

  //parameter of the geodetic reference frame
  double m_idontknow;

	//reference ground plane
	double m_nx;
	double m_ny;
	double m_nz;
	double m_d;

	//distance in front of the camera to calculate the point on the epipolarline
	double m_distance_epi;

	//foot print -> global coordinate system for the output (global coordinate system -> depends of the input system)
	double m_x_P1_global,m_x_P2_global,m_x_P3_global,m_x_P4_global;
	double m_y_P1_global,m_y_P2_global,m_y_P3_global,m_y_P4_global;
	double m_z_P1_global,m_z_P2_global,m_z_P3_global,m_z_P4_global;
};


#endif
