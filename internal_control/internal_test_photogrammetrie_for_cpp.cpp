/*
 * internal_test_photogrammetrie_for_cpp.cpp
 *
 *  Created on: 14.10.2010
 *      Author: steffen
 */

#include "internal_test_photogrammetrie_for_cpp.h"

#include <iostream>
#include <cstdlib> //for getopt and optarc
#include <fstream>
#include <string>
#include <vector>

//extern lib photogrammetrie.so
#include "..//basics//point.h"
#include "..//basics//ebene.h"
#include "..//position//gps_pos.h"
#include "..//photo//cam.h"
#include "..//photo//bpoint.h"
#include "..//photo//forward_intersection.h"
#include "..//transformation//applanix.h"
#include "..//boresight_alignment//cam_bore.h"
#include "..//boresight_alignment//boresight_transformation.h"

#include "..//basics//rotation_matrix.h"
#include "..//basics//fix_values.h"

using namespace std;


Internal_test_photogrammetrie_for_cpp::Internal_test_photogrammetrie_for_cpp()
{
  m_error=true;
  m_approach_difference = 1E-10;

  if(!test_rotations_matrix())
      m_error=false;

  if(!test_point())
      m_error=false;

  if(!test_global_photogrammetrie())
      m_error=false;

}

Internal_test_photogrammetrie_for_cpp::~Internal_test_photogrammetrie_for_cpp()
{

}

bool Internal_test_photogrammetrie_for_cpp::test_point()
{
    double omega=-180.0 , phi=-180.0 , kappa=-180.0;
    double step=10.0;
    //double omega=0.0 , phi=90.0 , kappa=-1.0;
    while(omega!=180.0+step)
    {
        //cout <<endl<<" info -> opk : "<<omega<<" "<<phi<<" "<<kappa;
        phi=0.0;
        while(phi!=180+step)
        {
            kappa=0.0;
            while(kappa!=180.0+step)
            {
                    //transform all standard deviations into the mathematics coordinate system
                    Rotation_matrix R_m(Rotation_matrix::math,omega/180.0*PI,phi/180.0*PI,kappa/180.0*PI);
                    Rotation_matrix R_g(Rotation_matrix::geodetic,omega/180.0*PI,phi/180.0*PI,kappa/180.0*PI);

                    Point pos_global(30034.09,2020.05,111.12,0.2,1.1,0.167);
                    Point P0(102.05,140.02,-9.58);

                    //test with math rotation matrix
                    Point pos_global_m = pos_global.Rotation(P0,R_m);
                    Point pos_global_m_back = pos_global_m.RotationRueck(P0,R_m);

                    double dd = pos_global.Abstand(pos_global_m_back);
                    if(dd > m_approach_difference)
                    {
                        m_cout<<endl<<"-- test point transformation -> ERROR!";
                        m_cout<<endl<<"     Rotation angel o,p,k : "<<omega <<" "<< phi <<" "<< kappa;
                        m_cout<<endl<<"     org coordinate       : "<<pos_global;
                        m_cout<<endl<<"     transform coordinate : "<<pos_global_m;
                        m_cout<<endl<<"     trans back coordinate: "<<pos_global_m_back;
                     return false;
                    }

                    //test with geodetic rotation matrix
                    Point pos_global_g = pos_global.Rotation(P0,R_g);
                    Point pos_global_g_back = pos_global_g.RotationRueck(P0,R_g);

                    dd = pos_global.Abstand(pos_global_g_back);
                    if(dd > m_approach_difference)
                    {
                        m_cout<<endl<<"-- test point transformation -> ERROR!";
                        m_cout<<endl<<"     Rotation angel o,p,k : "<<omega <<" "<< phi <<" "<< kappa;
                        m_cout<<endl<<"     org coordinate       : "<<pos_global;
                        m_cout<<endl<<"     transform coordinate : "<<pos_global_g;
                        m_cout<<endl<<"     trans back coordinate: "<<pos_global_g_back;
                     return false;
                    }

              kappa+=step;
            }
          phi+=step;
        }
      omega+=step;
    }
 m_cout<<endl<<"++ test point transformation -> OK";
 return true;
}

bool Internal_test_photogrammetrie_for_cpp::test_rotations_matrix()
{

   Rotation_matrix R(Rotation_matrix::math,30.0/180.0*PI,60/180.0*PI,1.0/180.0*PI);

   //##############################
   //Rot
   // 0.49992 -0.00873  0.86603
   // 0.44806  0.85834 -0.25000
   //-0.74116  0.51301  0.43301
   Matrix R_soll(3,3,Null);
   R_soll(0,0)=  0.49992; R_soll(0,1)= -0.00873; R_soll(0,2)= 0.86603;
   R_soll(1,0)=  0.44806; R_soll(1,1)=  0.85834; R_soll(1,2)=-0.25000;
   R_soll(2,0)= -0.74116; R_soll(2,1)=  0.51301; R_soll(2,2)= 0.43301;

   //m_cout<<endl<<"Rot_ist  :"<<R;
   //m_cout<<endl<<"Rot soll :"<<R_soll;

   if( !R.get_Matrix().NearEqual(R_soll,0.00001) )
   {
    m_cout<<endl<<"-- test rotation_matrix calc from angle to matrix (::math) -> ERROR! "<<endl<<R.get_errorstring();
    return false;
   }
   else
    m_cout<<endl<<"++ test rotation_matrix calc from angle to matrix (::math) -> OK";

   //##############################
   double r,p,h;
   //angle math: 0.52359877559829881566 1.0471975511965976313 0.017453292519943295474
   double r_m=0.52359877559829881566,p_m=1.0471975511965976313,h_m=0.017453292519943295474;
   //m_cout.precision(20);
   //m_cout<<endl<<"angle math: "<<r_m<<" "<<p_m<<" "<<h_m;

   R.get_rotation_angle(Rotation_matrix::math,r,p,h);
    //m_cout<<endl<<"angle math: "<<r<<" "<<p<<" "<<h;

   if(!( r==r_m && p==p_m && h==h_m ))
   {
      m_cout<<endl<<"-- test rotation_matrix calc from matrix to angle (::math) -> ERROR! "<<endl<<R.get_errorstring();
      return false;
   }
   else
      m_cout<<endl<<"++ test rotation_matrix calc from matrix to angle (::math) -> OK";

   //##############################
   //angle geodetic: 0.869762205377869968 0.83479598822091427568 0.7307441043260751723
   double r_g=0.869762205377869968,p_g=0.83479598822091427568,h_g=0.7307441043260751723;
   //m_cout<<endl<<"angle math: "<<r_g<<" "<<p_g<<" "<<h_g;

   R.get_rotation_angle(Rotation_matrix::geodetic,r,p,h);
   //m_cout<<endl<<"angle geodetic: "<<r<<" "<<p<<" "<<h;

   if(!( r==r_g && p==p_g && h==h_g ))
   {
      m_cout<<endl<<"-- test rotation_matrix calc from matrix to angle (::geodetic) -> ERROR! "<<endl<<R.get_errorstring();
      return false;
   }
   else
      m_cout<<endl<<"++ test rotation_matrix calc from matrix to angle (::geodetic) -> OK";

   //##############################
   //fill a new rotation matrix
   Rotation_matrix Rg(Rotation_matrix::geodetic,r,p,h);

   //m_cout<<endl<<"Rot "<<Rg;
   //m_cout<<endl<<"Rot soll :"<<R_soll;

   if( !Rg.get_Matrix().NearEqual(R_soll,0.00001) )
   {
    m_cout<<endl<<"-- test rotation_matrix calc from angle to matrix (::geodetic) -> ERROR! "<<endl<<Rg.get_errorstring();
    return false;
   }
   else
    m_cout<<endl<<"++ test rotation_matrix calc from angle to matrix (::geodetic) -> OK";

   //##############################
   Rg.get_rotation_angle(Rotation_matrix::geodetic,r,p,h);
   //m_cout<<endl<<"angle geodetic: "<<r<<" "<<p<<" "<<h;

   if(!( r==r_g && p==p_g && h==h_g ))
    {
       m_cout<<endl<<"-- test rotation_matrix calc from matrix to angle (::geodetic) -> ERROR! "<<endl<<R.get_errorstring();
       return false;
    }
    else
       m_cout<<endl<<"++ test rotation_matrix calc from matrix to angle (::geodetic) -> OK";

   //##############################
   Rg.get_rotation_angle(Rotation_matrix::math,r,p,h);
   //m_cout.precision(20);
   //m_cout<<endl<<"angle math: "<<r<<" "<<p<<" "<<h;

   //??????????? bad sin() cos() calculation ???????????????
   if(!( fabs(r-r_m)<0.00000000000001 &&  fabs(p-p_m)<0.00000000000001 && fabs(h-h_m)<0.00000000000001 ))
   {
     m_cout<<endl<<"-- test rotation_matrix calc from matrix to angle (::math) -> ERROR! "<<endl<<R.get_errorstring();
     return false;
   }
   else
     m_cout<<endl<<"++ test rotation_matrix calc from matrix to angle (::math) -> OK";

 return true;
}

bool Internal_test_photogrammetrie_for_cpp::test_global_photogrammetrie()
{


    //##################################";
    //forward intersection example 2:";

                     //info -- calculation from the calibration --
                     /* calibration
                     ###### forward intersection ########
                      picture left:  RechtsVorn_13.BMP  picture right: RechtsHinten_13.BMP
                      BP_left :126 (  756.000,  345.000)   BP_right :126 (  401.000,  370.000)
                      ###### end forward intersection ########
                      ######  Boresight transformation ########
                      car pos left  : (  641754.64076, 5638452.77658,     296.79691)  rot (0.67666,      -0.16642,     147.47308)   have pic's the same car pos :1
                      UTM global    : (  641748.32241, 5638451.20961,     299.20626)  0.00000 0.00000 0.00000
                      UTM soll P_ref: (  641748.32088, 5638451.20780,     299.20560)
                      soll - ist    : (      -0.0-1062.3945612937441,1587.5888858836174,-7728.733215755935)0153,      -0.00180,      -0.00066)
                     ###### end boresight transformation ########
                     */

        Cam_bore cam_left(      1280,960,
                                0.00645,
                                0, 0, 0,
                                0, 0, 0,
                                -5.96131, 0.09154, 0.05499,
                                -0.00392312, 5.3042e-05, 0,
                                3.41561e-05, 1.66584e-05,
                                0.000115336, 3.44961e-05,
                                3.1,
                                1.810038117, 1.997471691, 2.954505537,
                                0, 0, 0,
                                1.236546986, -0.6468711578, -0.222276496,
                                0, 0, 0
                            );

        Cam_bore cam_right(     1280,960,
                                0.00645,
                                1.694736602, -0.5066248238, 1.913592406,
                                0.06547699024, -0.02425883623, 0.01597899627,
                                -5.96062, -0.02699, 0.00748,
                                -0.00392089, 5.0132e-05, 0,
                                -2.96244e-05, -0.000116111,
                                -8.63535e-05, -7.70085e-05,
                                3.1,
                                1.886692106, -0.6072478387, 2.940466502,
                                0, 0, 0,
                                1.312015813, -0.6836290131, -0.1604868833,
                                0, 0, 0
                            );

        BPoint BP_l1(cam_left ,756.000,345.000);
        BPoint BP_r1(cam_right,401.000,370.000);

        vector<BPoint> bpoint_list;
        bpoint_list.push_back(BP_l1);
        bpoint_list.push_back(BP_r1);

        Vorwaertsschnitt vws(bpoint_list);
        Point P_vws1 = vws.get_Schnittpunkt();

        //m_cout << endl;
        //m_cout << endl << "solution forward intersection: " << P_vws1;

        //nominal coordinates
        //test if calculation forward intersection OK
        Point P_vws1_soll(0.4065545831586287,0.5052388614207152,-3.7809044494132813,0.0030916030241650407,0.004254531230252718,0.019928437349091173);
        //m_cout << endl << "nominal coordinates          : " << P_vws1_soll;

        if( P_vws1.Abstand(P_vws1_soll) > m_approach_difference )
        {
            m_cout << endl << "-- test forward intersection -> ERROR !";
            m_error=false;
        }
        else
            m_cout << endl << "++ test forward intersection -> OK";




//###########################
//boresight calibration



  //## old version ##
        double m_Easting   = 641754.64076;
        double m_Northing  = 5638452.77658;
        double m_eHeight   = 296.79691;
        double m_roll      = -0.2235410;
        double m_pitch     = -0.6600010;
        double m_heading   = 214.0967730;
        double m_latitude  = 50.8803408;
        //double m_longitude = 11.0150776;

        double m_Easting_s   = 641754.64076;
        double m_Northing_s  = 5638452.77658;
        double m_eHeight_s   = 296.79691;
        double m_roll_s      = 0.011810027164432562;
        double m_pitch_s     = -0.0029045888236222156;
        double m_heading_s   = 2.5738907324189215;
        double m_latitude_s  = 50.8803408;

        double m_droll=0.0,m_dpitch=0.0,m_dheading=0.0;

        //change the applanix rotation angels into the math rotation angels

        //old function in the c wrapper
        Applanix appl_old;
        appl_old.calc_approximately_meridian_convergence_degree(m_Easting,m_latitude,m_heading);
        appl_old.compare_gps_coosystem_degree_to_math_coosystem_pi(m_roll,m_pitch,m_heading,m_droll,m_dpitch,m_dheading);

        //## test applanix class
        if(
                m_Easting == m_Easting_s &&
                m_Northing == m_Northing_s &&
                m_eHeight == m_eHeight_s &&
                m_roll == m_roll_s &&
                m_pitch == m_pitch_s &&
                m_heading == m_heading_s &&
                m_latitude == m_latitude_s

        )
           m_cout<<endl<<"++ test convert angle geodetic to mathematics (applanix.cpp) old version deprecate -> OK"<<flush;
        else
        {
            m_cout<<endl<<"-- test convert angle geodetic to mathematics (applanix.cpp) old version deprecate -> ERROR!"<<flush;
            m_error=false;
        }

        Boresight_transformation bore_old(cam_left);
        bore_old.set_car_position_global(m_Easting,m_Northing,m_eHeight,m_roll,m_pitch,m_heading);
        bore_old.set_local_coordinate( P_vws1 );
        Point P_bore1_old = bore_old.get_global_coordinate();

        Point P_bore1_old_soll(641748.3224107784, 5638451.209601247,     299.2062569395003,  0.013175537943788337    ,   0.014391165294194564   ,  0.0066408750772648855 );


        //test if boresight calculation OK
         if( P_bore1_old.Abstand(P_bore1_old_soll)                        < m_approach_difference &&
             P_bore1_old.get_dXYZ().Abstand(P_bore1_old_soll.get_dXYZ())  < m_approach_difference
         )
             m_cout<<endl<<"++ test boresight old version deprecate -> OK"<<flush;
         if(P_bore1_old.Abstand(P_bore1_old_soll) > m_approach_difference)
           {
               m_cout<<endl<<"-- test boresight (old functions for c-wrapper) old version deprecate -> ERROR!"<<flush;
               m_error=false;
           }
         if(P_bore1_old.get_dXYZ().Abstand(P_bore1_old_soll.get_dXYZ()) > m_approach_difference)
           {
               m_cout<<endl<<"-- test boreside std (old functions for c-wrapper) old version deprecate -> ERROR!"<<flush;
               m_error=false;
           }

  //## end old version ##




  //## version s0002 ##
        Gps_pos pos1;
        pos1.set_position( Point(641754.64076,5638452.77658,296.79691,0.1,0.2,0.3));
        pos1.set_rotation( Point(-0.2235410,-0.6600010,214.0967730,0.1,0.2,0.3));
        pos1.set_Latitude(50.8803408);
        pos1.set_Longitude(11.0150776);
        pos1.convert_rotation_angles_grad_to_rad();

        //change the applanix rotation angels into the math rotation angels
        Applanix appl;
        appl.set_version(Applanix::s0002);
        Gps_pos pos1_konvert   = appl.convert_from_geodetic_applanix_to_photogrammetric_rotation_angles(pos1);
        Gps_pos pos1_konf_back = appl.convert_from_photogrammetric_to_geodetic_applanix_rotation_angles(pos1_konvert);

        //m_cout << endl;
        //m_cout << endl <<" GPS pos org : "<< pos1;
        //m_cout << endl <<" GPS pos math: "<< pos1_konvert;
        //m_cout << endl <<" GPS pos back: "<< pos1_konf_back;

        Gps_pos pos1_konvert_soll;
        pos1_konvert_soll.set_position( Point(641754.64076,5638452.77658,296.79691,0.10543377457603721,0.19718955139319472,0.3));
        pos1_konvert_soll.set_rotation( Point(0.011810027164432562,-0.0029045888236222113,2.573890732418922,0.0034997490894472347,0.0017270284031615391,-0.0052359636647952516));
        pos1_konvert_soll.set_Latitude(50.8803408);
        pos1_konvert_soll.set_Longitude(11.0150776);

        //## test applanix class
        if(pos1_konvert == pos1_konvert_soll)
            m_cout<<endl<<"++ test convert angle goedetic to mathematics (applanix.cpp) version s0002 -> OK"<<flush;
        else
        {
            m_cout<<endl<<"-- test convert angle goedetic to mathematics (applanix.cpp) version s0002 -> ERROR!"<<flush;
            m_error=false;
        }

        Boresight_transformation bore(cam_left);
        bore.set_car_position_global(pos1_konvert);
        bore.set_local_coordinate( P_vws1 );
        Point P_bore1 = bore.get_global_coordinate();
        //## end new version ##

        Point P_bore1_soll(641748.3224107784, 5638451.209601247,     299.2062569395003,   0.106642162928616270   ,   0.200644442163057520   ,  0.30032210187573810 );

        //m_cout << endl;
        //m_cout << endl << "erg bore new  : " <<P_bore1;
        //m_cout << endl << "erg bore old  : " <<P_bore1_old;
        //m_cout << endl << "erg bore soll : " <<P_bore1_soll;

        //test if boresight calculation OK
        if( P_bore1.Abstand(P_bore1_soll)                            < m_approach_difference &&
            P_bore1.get_dXYZ().Abstand(P_bore1_soll.get_dXYZ())      < m_approach_difference
        )
            m_cout<<endl<<"++ test boresight version s0002 -> OK";
        if(P_bore1.Abstand(P_bore1_soll) > m_approach_difference)
        {
            m_cout<<endl<<"-- test boresight (new functions for C++) version s0002 -> ERROR!"<<flush;
            m_error=false;
        }
        if(P_bore1.get_dXYZ().Abstand(P_bore1_soll.get_dXYZ()) > m_approach_difference)
        {
            m_cout<<endl<<"-- test boresight std (new functions for C++) version s0002 -> ERROR!"<<flush;
            m_error=false;
        }
   //## end versions0002 ##




   //## version s0003 ##
        Gps_pos pos1_s3;
        pos1_s3.set_position( Point(641754.64076,5638452.77658,296.79691,0.1,0.2,0.3));
        pos1_s3.set_rotation( Point(-0.2235410,-0.6600010,214.0967730,0.1,0.2,0.3));
        pos1_s3.set_Latitude(50.8803408);
        pos1_s3.set_Longitude(11.0150776);
        pos1_s3.convert_rotation_angles_grad_to_rad();

        //change the applanix rotation angels into the math rotation angels
        Applanix appl_s3;
        appl_s3.set_version(Applanix::s0003);
        Gps_pos pos1_s3_konvert   = appl_s3.convert_from_geodetic_applanix_to_photogrammetric_rotation_angles(pos1_s3);
        Gps_pos pos1_s3_konf_back = appl_s3.convert_from_photogrammetric_to_geodetic_applanix_rotation_angles(pos1_s3_konvert);

            //m_cout << endl;
            //m_cout << endl <<" GPS pos org : "<< pos1_s3;
            //m_cout << endl <<" GPS pos math: "<< pos1_s3_konvert;
            //m_cout << endl <<" GPS pos back: "<< pos1_s3_konf_back;

            //test back and forth calculation
            if(pos1_s3.get_position().Abstand(pos1_s3_konf_back.get_position()) > m_approach_difference )
            {
             m_cout<<endl<<"-- test convert - back and forth calculation (applanix.cpp) version s0003 -> ERROR!"<<flush;
            }


        Gps_pos pos1_s3_konvert_soll;
        pos1_s3_konvert_soll.set_position( Point(641754.64076,5638452.77658,296.79691,0.10543377457603721,0.19718955139319472,0.3));
        //old//pos1_s3_konvert_soll.set_rotation( Point(0.011810027164432562,-0.0029045888236222113,2.573890732418922,0.0034997490894472347,0.0017270284031615391,-0.0052359636647952516));
        pos1_s3_konvert_soll.set_rotation( Point(0.011726155044571314,-0.0032265694880318210,2.5738924984312757,0.0034997490894472347,0.0017270284031615391,-0.0052359636647952516));
        pos1_s3_konvert_soll.set_Latitude(50.8803408);
        pos1_s3_konvert_soll.set_Longitude(11.0150776);

        //## test applanix class
        if(pos1_s3_konvert == pos1_s3_konvert_soll)
            m_cout<<endl<<"++ test convert angle goedetic to mathematics (applanix.cpp) version s0003 -> OK"<<flush;
        else
        {
            m_cout<<endl<<"-- test convert angle goedetic to mathematics (applanix.cpp) version s0003 -> ERROR!"<<flush;
            m_error=false;
        }

        // boresight transformation left camera
        Boresight_transformation bore_s3(cam_left);
        bore_s3.set_car_position_global(pos1_s3_konvert);
        bore_s3.set_local_coordinate( P_vws1 );
        Point P_bore1_s3 = bore_s3.get_global_coordinate();

           //test boresight transformation calculation backwards
           bore_s3.set_global_coordinate(P_bore1_s3);
           Point P_bore1_s3_back = bore_s3.get_local_coordinate();

           //test boresight transformation with the right camera
           Boresight_transformation bore_s3_r(cam_right);
           bore_s3_r.set_car_position_global(pos1_s3_konvert);
           bore_s3_r.set_local_coordinate( P_vws1 );
           Point P_bore1_s3_r = bore_s3_r.get_global_coordinate();

               //test boresight transformation calculation backwards
               bore_s3_r.set_global_coordinate(P_bore1_s3_r);
               Point P_bore1_s3_r_back = bore_s3_r.get_local_coordinate();


               //test if all OK ;-)
                       //cout << endl << "boresight input     cam left  : " <<P_vws1;
                       //cout << endl << "boresight in global cam left  : " <<P_bore1_s3;
                       //cout << endl << "boresight back      cam left  : " <<P_bore1_s3_back;
                       //cout << endl << "boresight in global cam right : " <<P_bore1_s3_r;
                       //cout << endl << "boresight back      cam right : " <<P_bore1_s3_r_back<<flush;

                       //test if camera left  and right have the same solution
                       if( P_vws1.Abstand(P_bore1_s3_back) > m_approach_difference && P_vws1.Abstand(P_bore1_s3_r_back) > m_approach_difference)
                       {
                           m_cout<<endl<<"-- test boresight back and forth calculation local (new functions for C++) version s0003 -> ERROR!";
                       }
                       if( P_bore1_s3.Abstand(P_bore1_s3_r) > m_approach_difference)
                       {
                           m_cout<<endl<<"-- test boresight back and forth calculation global (new functions for C++) version s0003 -> ERROR!";
                       }


        //old1//Point P_bore1_s3_soll(641748.3224107784, 5638451.209601247 , 299.2062569395003  , 0.016115693755609103 , 0.008731787198876883 , 0.009425601705664506 );
        //old2//Point P_bore1_s3_soll(641748.3216321553, 5638451.2098160405, 299.20435386271487 , 0.016112675857266775 , 0.008732545380913434 , 0.009430057704691621 );
        Point P_bore1_s3_soll(641748.3216321553, 5638451.2098160405, 299.20435386271487 , 0.106642136909138220 , 0.200644738259331180 , 0.300322131203843050 );

        //m_cout << endl;
        //m_cout << endl << "erg bore new  : " <<P_bore1;
        //m_cout << endl << "erg bore old  : " <<P_bore1_old;
        //m_cout << endl << "erg bore soll : " <<P_bore1_soll;

        //test if boresight calculation OK
        if( P_bore1_s3.Abstand(P_bore1_s3_soll)                            < m_approach_difference &&
            P_bore1_s3.get_dXYZ().Abstand(P_bore1_s3_soll.get_dXYZ())      < m_approach_difference
        )
            m_cout<<endl<<"++ test boresight version s0003 -> OK";
        if(P_bore1_s3.Abstand(P_bore1_s3_soll) > m_approach_difference)
        {
            m_cout<<endl<<"-- test boresight (new functions for C++) version s0003 -> ERROR!"<<flush;
            m_error=false;
        }
        if(P_bore1_s3.get_dXYZ().Abstand(P_bore1_s3_soll.get_dXYZ()) > m_approach_difference)
        {
            m_cout<<endl<<"-- test boresight std (new functions for C++) version s0003 -> ERROR!"<<flush;
            m_error=false;
        }
   //## end versions0003 ##





      if(!m_error)
      {
            cerr <<endl<< "ERROR in libphotogrammetrie.so version: "<<VERSIONSNUMBER<<endl<<flush;
      }

 return m_error;
}
