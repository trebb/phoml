//============================================================================
// Name        : bpoint_bore.cpp
// Author      : Steffen Scheller
// Version     : 0.00x
// Copyright   : ©2010
// Description : mobile mapping photogrammetry program C++, ANSI-style
//============================================================================

#include "bpoint_bore.h"

#include "boresight_transformation.h"
#include "..//basics//rotation_matrix.h"

BPoint_bore::BPoint_bore(Cam_bore &cam_bore,Gps_pos &car_pos)
            :m_cam_bore(&cam_bore),
             m_car_pos(&car_pos),
             m_cam_bore_calc(cam_bore),
             m_BP(m_cam_bore_calc),
             m_calculation_option(BPoint_bore::rell)
{


}

BPoint_bore::BPoint_bore(Cam_bore &cam_bore,Gps_pos &car_pos,double m,double n)
            :m_cam_bore(&cam_bore),
             m_car_pos(&car_pos),
             m_cam_bore_calc(cam_bore),
             m_BP(cam_bore,m,n),
             m_calculation_option(BPoint_bore::rell)
{

}

BPoint_bore::BPoint_bore(Cam_bore &cam_bore,Gps_pos &car_pos,Point &global_measurement_point)
            :m_cam_bore(&cam_bore),
             m_car_pos(&car_pos),
             m_cam_bore_calc(cam_bore),
             m_BP(m_cam_bore_calc),
             m_global_measurement_point(global_measurement_point),
             m_calculation_option(BPoint_bore::rell)
{

}

BPoint_bore::~BPoint_bore()
{
}
/*
BPoint_bore::BPoint_bore(const BPoint_bore &BPb)
            :m_cam_bore(BPb.m_cam_bore),
             m_car_pos(BPb.m_car_pos),
             m_cam_bore_calc(BPb.m_cam_bore),
             m_global_measurement_point(BPb.m_global_measurement_point),
             m_calculation_option(BPb.m_calculation_option),
             m_BP(m_cam_bore_calc)
{
}
*/
BPoint_bore::BPoint_bore(const BPoint_bore &BPb)
            :m_BP(BPb)
{
    (*this) = BPb;
    m_cam_bore = BPb.m_cam_bore;
    m_car_pos  = BPb.m_car_pos;
    m_global_measurement_point = BPb.m_global_measurement_point;
    m_calculation_option=BPb.m_calculation_option;
}

BPoint_bore& BPoint_bore::operator=(const BPoint_bore &BPb)
{
    BPoint_bore (*this) = (BPb);
    /*
        (*this) = BPb; //to copy the included BPoint class
        m_cam_bore = BPb.m_cam_bore;
        m_car_pos  = BPb.m_car_pos;
        m_global_measurement_point = BPb.m_global_measurement_point;
        m_calculation_option=BPb.m_calculation_option;
        */
    return  (*this);
}

// convertion of "BPoint_bore  >>-->  BPoint"
BPoint_bore::operator BPoint () const
{
 return m_BP;
}

enum BPoint_bore::calculation_option const BPoint_bore::get_calculation_option() const
{
 return m_calculation_option;
}

void BPoint_bore::set_calculation_option( const enum calculation_option& co)
{
    if(co != m_calculation_option)
    {
         if(co == BPoint_bore::absolute)
         {
             //calculation the outer orientation into the global coordinate system
             //transform camera calibration

             //bore-sight transformation
             Point BT = m_cam_bore->get_B();
             Rotation_matrix BR(     Rotation_matrix::math,
                                     m_cam_bore->get_B_rotx(),
                                     m_cam_bore->get_B_roty(),
                                     m_cam_bore->get_B_rotz(),
                                     m_cam_bore->get_B_drotx(),
                                     m_cam_bore->get_B_droty(),
                                     m_cam_bore->get_B_drotz()
             );

             //global transformation
             Point GT  = m_car_pos->get_position();
             Point GR_ = m_car_pos->get_rotation();
             Rotation_matrix GR(     Rotation_matrix::math,
                                     GR_.get_X(),
                                     GR_.get_Y(),
                                     GR_.get_Z(),
                                     GR_.get_dX(),
                                     GR_.get_dY(),
                                     GR_.get_dZ());


             Point P0_cam(0.0,0.0,0.0); //new coordinate center of the camera  (camera coordinate system)
             Point P_car,P_global;

             P_car = P0_cam.Rotation_with_std(BT,BR);
             P_global = P_car.Rotation_with_std(GT,GR);

             Rotation_matrix R_global( GR.get_Matrix().MatMult(BR) );
             //todo standard deviation transformation fail!!!
             double r=0.0,p=0.0,h=0.0,dr=0.0,dp=0.0,dh=0.0;
             R_global.get_rotation_angle(Rotation_matrix::math,r,p,h,dr,dp,dh);

             m_cam_bore->set_O(P_global);
             m_cam_bore->set_rotX(r);
             m_cam_bore->set_rotY(p);
             m_cam_bore->set_rotZ(h);
             m_cam_bore->set_drotX(dr);
             m_cam_bore->set_drotY(dp);
             m_cam_bore->set_drotZ(dh);

         }

         if(co == BPoint_bore::rell)
         {
             //calculation the outer orientation into the local coordinate system
             //transform camera calibration

         }

      //set the new option
      m_calculation_option = co;
     }
}


ostream& operator<<(ostream& s,const BPoint_bore& A)
{
       s.precision(10);
       s.setf(ios::left,ios::showpoint);
       s.setf(ios::showbase);

       s<<" ### BPoint_bore ###";
       s<<std::endl<<*A.m_cam_bore;
       s<<std::endl<<"  car positon: "<<*A.m_car_pos;
       s<<std::endl<<"  measurment : "<<A.m_global_measurement_point;
       s<<std::endl<<" ### end BPoint_bore ###";
return s;
}
