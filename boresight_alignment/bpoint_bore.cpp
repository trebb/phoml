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
#include "..//basics//basics_exception.h"

BPoint_bore::BPoint_bore(Cam_bore &cam_bore,Gps_pos &car_pos,unsigned int nr)
            :m_cam_bore(&cam_bore),
             m_car_pos(&car_pos),
             m_cam_bore_calc(cam_bore),
             m_nr(nr),
             m_BP(m_cam_bore_calc),
             m_coordinate_calculation_option(BPoint_bore::local)
{
    m_input_type = BPoint_bore::none;

}

BPoint_bore::BPoint_bore(Cam_bore &cam_bore,Gps_pos &car_pos,unsigned int nr,double m,double n)
            :m_cam_bore(&cam_bore),
             m_car_pos(&car_pos),
             m_cam_bore_calc(cam_bore),
             m_nr(nr),
             m_m(m),
             m_n(n),
             m_dm(0.0),
             m_dn(0.0),
             m_BP(cam_bore,m,n),
             m_coordinate_calculation_option(BPoint_bore::local)
{
    m_input_type = BPoint_bore::picture;

}

BPoint_bore::BPoint_bore(Cam_bore &cam_bore,Gps_pos &car_pos,Point_nr &global_measurement_point,const enum coordinate_calculation_option& cco)
            :m_cam_bore(&cam_bore),
             m_car_pos(&car_pos),
             m_cam_bore_calc(cam_bore),
             m_nr(global_measurement_point.get_PktNr()),
             m_BP(m_cam_bore_calc),
             m_global_measurement_point(global_measurement_point),
             m_coordinate_calculation_option(BPoint_bore::local)
{
    (*this).set_calculation_option( cco );
    m_BP.set_XYZObjKoo(global_measurement_point);
    set_values_from_BPoint_class();
    set_measurement_point( global_measurement_point , cco);
    m_input_type = BPoint_bore::object;
}

BPoint_bore::~BPoint_bore()
{
}

BPoint_bore::BPoint_bore(const BPoint_bore &BPb)
            :m_BP(BPb)
{
    (*this) = BPb;
}

BPoint_bore& BPoint_bore::operator=(const BPoint_bore &BPb)
{
           (*this).m_BP = BPb; //to copy the included BPoint class only temp structure
           m_cam_bore = BPb.m_cam_bore;
           m_car_pos  = BPb.m_car_pos;

           m_nr = BPb.m_nr;
           m_m = BPb.m_m;
           m_n = BPb.m_n;
           m_dm= BPb.m_dm;
           m_dn= BPb.m_dn;

           m_cam_bore_calc = BPb.m_cam_bore_calc;

           m_m_cb = BPb.m_m_cb;
           m_n_cb = BPb.m_n_cb;
           m_dm_cb= BPb.m_dm_cb;
           m_dn_cb= BPb.m_dn_cb;

           m_local_measurement_point  = BPb.m_local_measurement_point;
           m_car_measurement_point    = BPb.m_car_measurement_point;
           m_global_measurement_point = BPb.m_global_measurement_point;

           m_coordinate_calculation_option=BPb.m_coordinate_calculation_option;
           m_input_type = BPb.m_input_type;

    return  (*this);
}

// convertion of "BPoint_bore  >>-->  BPoint"
BPoint_bore::operator BPoint () const
{
 return m_BP;
}

enum BPoint_bore::coordinate_calculation_option const BPoint_bore::get_calculation_option() const
{
 return m_coordinate_calculation_option;
}

void BPoint_bore::set_calculation_option( const enum coordinate_calculation_option& cco)
{
    if(cco != m_coordinate_calculation_option)
    {

        if(cco == BPoint_bore::relative)
        {
                     //calculation the outer orientation into the local coordinate system
                     //transform camera calibration

                     //set "original local" Camera into the BPoint class
                     m_BP.set_Cam(*m_cam_bore);
                     m_cam_bore_calc = *m_cam_bore;
         }

         if(cco == BPoint_bore::local)
         {
             //calculation the outer orientation into the local coordinate system
             //transform camera calibration

             //set "original local" Camera into the BPoint class
             m_BP.set_Cam(*m_cam_bore);
             m_cam_bore_calc = *m_cam_bore;
             (*this).reset_rellativ_orientation_cam_bore_calc_member();
         }

         if(cco == BPoint_bore::car)
         {
             //todo !!!!! function is untested !!!!!!!!

                      //set "original local" Camera into the BPoint class
                      m_BP.set_Cam(*m_cam_bore);
                      m_cam_bore_calc = *m_cam_bore;

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

                     Point P0_cam(0.0,0.0,0.0); //new coordinate center of the camera  (camera coordinate system)
                     Point P_car,P_global;

                     P_car = P0_cam.Rotation_with_std(BT,BR);

                     //todo standard deviation transformation fail!!!
                      double r=0.0,p=0.0,h=0.0,dr=0.0,dp=0.0,dh=0.0;
                      BR.get_rotation_angle(Rotation_matrix::math,r,p,h,dr,dp,dh);

                      m_cam_bore_calc.set_O(P_car);
                      m_cam_bore_calc.set_rotX(r);
                      m_cam_bore_calc.set_rotY(p);
                      m_cam_bore_calc.set_rotZ(h);
                      m_cam_bore_calc.set_drotX(dr);
                      m_cam_bore_calc.set_drotY(dp);
                      m_cam_bore_calc.set_drotZ(dh);

                      //set new Camera into the BPoint class
                      m_BP.set_Cam(m_cam_bore_calc);

         }

         if(cco == BPoint_bore::global)
         {
             //set "original local" Camera into the BPoint class
             m_BP.set_Cam(*m_cam_bore);
             m_cam_bore_calc = *m_cam_bore;

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

             //set standard deviation manual
             double GR_dr=0.0,GR_dp=0.0,GR_dh=0.0,BR_dr=0.0,BR_dp=0.0,BR_dh=0.0;
             GR.get_rotation_angle_std(Rotation_matrix::math,GR_dr,GR_dp,GR_dh);
             BR.get_rotation_angle_std(Rotation_matrix::math,BR_dr,BR_dp,BR_dh);

             dr = sqrt(GR_dr*GR_dr+BR_dr*BR_dr);
             dp = sqrt(GR_dp*GR_dp+BR_dp*BR_dp);
             dh = sqrt(GR_dh*GR_dh+BR_dh*BR_dh);


             m_cam_bore_calc.set_O(P_global);
             m_cam_bore_calc.set_rotX(r);
             m_cam_bore_calc.set_rotY(p);
             m_cam_bore_calc.set_rotZ(h);
             m_cam_bore_calc.set_drotX(dr);
             m_cam_bore_calc.set_drotY(dp);
             m_cam_bore_calc.set_drotZ(dh);

             //set new Camera into the BPoint class
             m_BP.set_Cam(m_cam_bore_calc);

         }

      //set the new option
      m_coordinate_calculation_option = cco;
     }
}

Point_nr BPoint_bore::get_measurement_point(const enum coordinate_calculation_option& cco) const
{
    if(cco == BPoint_bore::local)
     return m_local_measurement_point;
    else if(cco == BPoint_bore::car)
     return m_car_measurement_point;
    else if(cco == BPoint_bore::global)
     return m_global_measurement_point;
    else
     throw b_ex("input error <coordinate_calculation_option>",DEBUG_LOCATION,"BPoint_bore::get_measurement_point -> input error");
}

BPoint_bore& BPoint_bore::get_picture_coordinate_on_the_epipolar_geometrie( BPoint_bore& BPb, double s)
{
    //test if have both data sets the same coordinate_calculation_option
    if( (*this).get_calculation_option() != BPb.get_calculation_option() )
        throw b_ex("Different coordinate_calculation_option",DEBUG_LOCATION,"BPoint_bore::get_picture_coordinate_on_the_epipolar_geometrie -> error Different coordinate_calculation_option");

    //temp copy values
    double ss = s;
    Cam C = BPb.get_cam_bore();
    //call function and copy to the handover variable BPb
    BPb.m_BP = (*this).m_BP.get_KernlinenPunkt(C,ss);
    //write back values from the bpoint class
    BPb.set_values_from_BPoint_class();

  return BPb;
}

Point_nr BPoint_bore::calc_mono_cam_to_plane_intersection(Ebene &E,const enum coordinate_calculation_option& E_cco_t)
{
   //ask for into the different coordinate systems
   //transform plain into the right coordinate system
   Ebene Et = E;
   coordinate_calculation_option E_cco = E_cco_t;


   //bore-sight transformation
   Point BT = ((*this).m_cam_bore_calc.get_B());
   Rotation_matrix BR(     Rotation_matrix::math,
                           (*this).m_cam_bore_calc.get_B_rotx(),
                           (*this).m_cam_bore_calc.get_B_roty(),
                           (*this).m_cam_bore_calc.get_B_rotz(),
                           (*this).m_cam_bore_calc.get_B_drotx(),
                           (*this).m_cam_bore_calc.get_B_droty(),
                           (*this).m_cam_bore_calc.get_B_drotz());

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


   if(      (*this).m_coordinate_calculation_option == BPoint_bore::local  && E_cco == BPoint_bore::car    )
   {       Et = E.RotationRueck(BT,BR);
           E_cco = BPoint_bore::local;
   }
   else if( (*this).m_coordinate_calculation_option == BPoint_bore::car    && E_cco == BPoint_bore::local  )
   {       Et = E.Rotation(BT,BR);
           E_cco = BPoint_bore::car;
   }
   else if( (*this).m_coordinate_calculation_option == BPoint_bore::car    && E_cco == BPoint_bore::global )
   {       Et = E.RotationRueck(GT,GR);
           E_cco = BPoint_bore::car;
   }
   else if( (*this).m_coordinate_calculation_option == BPoint_bore::global && E_cco == BPoint_bore::car    )
   {       Et = E.RotationRueck(GT,GR);
           E_cco = BPoint_bore::global;
           //Ebene E_( Et.get_N(), Et.get_D() );
           //Et = E_;
           //test
           //Point O((*this).m_cam_bore_calc.get_O());
           //Point pt = Et.LotFussP(O);
           //double pa = Et.Abstand(O);
           //cout<<endl<<"O         :"<<O;
           //cout<<endl<<"p lot     :"<<pt;
           //cout<<endl<<"p abstand :"<<pa;
   }
   else if( (*this).m_coordinate_calculation_option == BPoint_bore::local  && E_cco == BPoint_bore::global )
   {       Et = E.RotationRueck(BT,BR).RotationRueck(GT,GR);
           E_cco = BPoint_bore::local;
   }
   else if( (*this).m_coordinate_calculation_option == BPoint_bore::global && E_cco == BPoint_bore::local  )
   {       Et = E.Rotation(BT,BR).Rotation(GT,GR);
           E_cco = BPoint_bore::global;
   }


    //both camera position and plain have to be the same coordinate system
   if( (*this).m_coordinate_calculation_option == E_cco )
   {
    Point_nr Pt((*this).m_nr,0.0,0.0,0.0);

    (*this).set_values_from_cam_bore_calc_member();
    (*this).reset_rellativ_orientation_cam_bore_calc_member();

    Pt = (*this).m_BP.calc_mono_cam_to_plane_intersection(Et) ;
    (*this).set_measurement_point(  Pt  ,  (*this).m_coordinate_calculation_option  );
    //cout << " ++calc mono++ ";
   }
   else
    throw b_ex("Different coordinate_calculation_option",DEBUG_LOCATION,"BPoint_bore::calc_mono_cam_to_plane_intersection -> error Different coordinate_calculation_option");

 return (*this).get_measurement_point((*this).m_coordinate_calculation_option );
}

unsigned int BPoint_bore::get_point_number() const
{
 return m_nr;
}
void         BPoint_bore::set_point_number( unsigned int nr)
{
 m_nr =  nr;
}

double BPoint_bore::get_m() const
{
 return m_m;
}

double BPoint_bore::get_n() const
{
 return m_n;
}

double BPoint_bore::get_dm() const
{
 return m_dm;
}

double BPoint_bore::get_dn() const
{
 return m_dn;
}

Cam_bore& BPoint_bore::get_cam_bore()
{
 return *m_cam_bore;
}

Gps_pos&  BPoint_bore::get_car_pos()
{
 return *m_car_pos;
}

void BPoint_bore::set_values_from_BPoint_class()
{
 m_m = m_BP.get_m();
 m_n = m_BP.get_n();

}

Point_nr  BPoint_bore::calc_footprint_point(Ebene &E,const enum coordinate_calculation_option& E_cco,double distance_cut)
{
 (*this).calc_mono_cam_to_plane_intersection(E,E_cco);

 //test point in front of the cam
 if(m_local_measurement_point.get_Z() > 0)
 {
   //cout<<endl<<"point is not in front of the cam!!";
   Gerade G( (*this).m_cam_bore_calc.get_O() , (*this).m_BP );
   Point_nr PK;
   PK = G.get_O().Add( G.get_R().MultS( distance_cut ) );
   //cout<<endl<<"P in front: "<<PK;
   (*this).set_measurement_point(PK, (*this).m_coordinate_calculation_option );
   Point_nr Pcoo = (*this).get_measurement_point(E_cco);
   //cout<<endl<<"P coo car: "<<Pcoo;
   Point_nr PE;
   PE = E.LotFussP(Pcoo);
   //cout<<endl<<"P perp E: "<<PE;
   (*this).set_measurement_point(PE, E_cco );
 }

 return (*this).get_measurement_point((*this).m_coordinate_calculation_option );
}

void BPoint_bore::set_values_from_cam_bore_calc_member()
{
 (*this).m_BP.get_Cam() = m_cam_bore_calc;
}

void BPoint_bore::reset_rellativ_orientation_cam_bore_calc_member()
{
  //todo change hack for relative orientation
  m_cam_bore_calc = *m_cam_bore;
  m_cam_bore_calc.set_O(Point(0.0,0.0,0.0));
  m_cam_bore_calc.set_rotX(0.0);
  m_cam_bore_calc.set_rotY(0.0);
  m_cam_bore_calc.set_rotZ(0.0);
  m_BP.set_Cam(m_cam_bore_calc);
}

void BPoint_bore::set_measurement_point(Point_nr& p_nr, const enum coordinate_calculation_option& cco)
{
    if(cco == BPoint_bore::local)
     m_local_measurement_point = p_nr;
    else if(cco == BPoint_bore::car)
     m_car_measurement_point = p_nr;
    else if(cco == BPoint_bore::global)
     m_global_measurement_point = p_nr;
    else
     throw b_ex("input error <coordinate_calculation_option>",DEBUG_LOCATION,"BPoint_bore::set_measurement_point -> input error");

    transform_measurement_point(cco);
}

void BPoint_bore::transform_measurement_point(const enum coordinate_calculation_option& cco)
{
    //bore-sight transformation
    Point BT = ((*this).m_cam_bore_calc.get_B());
    Rotation_matrix BR(     Rotation_matrix::math,
                            (*this).m_cam_bore_calc.get_B_rotx(),
                            (*this).m_cam_bore_calc.get_B_roty(),
                            (*this).m_cam_bore_calc.get_B_rotz(),
                            (*this).m_cam_bore_calc.get_B_drotx(),
                            (*this).m_cam_bore_calc.get_B_droty(),
                            (*this).m_cam_bore_calc.get_B_drotz());

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

    if(cco == BPoint_bore::local)
    {
      //calculation from local to car to global coordinate system
      m_car_measurement_point    = m_local_measurement_point.Rotation_with_std(BT,BR);
      m_global_measurement_point = m_car_measurement_point.Rotation_with_std(GT,GR);
    }

    if(cco == BPoint_bore::car)
    {
      //calculation from local to car to global coordinate system
      m_local_measurement_point = m_car_measurement_point.RotationRueck_with_std(BT,BR);
      m_global_measurement_point = m_car_measurement_point.Rotation_with_std(GT,GR);
    }

    if(cco == BPoint_bore::global)
    {
     //calculation from local to car to global coordinate system
     m_car_measurement_point = m_global_measurement_point.RotationRueck_with_std(GT,GR);
     m_local_measurement_point = m_car_measurement_point.RotationRueck_with_std(BT,BR);
    }

    m_local_measurement_point.set_PktNr(m_nr);
    m_car_measurement_point.set_PktNr(m_nr);
    m_global_measurement_point.set_PktNr(m_nr);
}

ostream& operator<<(ostream& s,const BPoint_bore& A)
{
       s.precision(10);
       s.setf(ios::left,ios::showpoint);
       s.setf(ios::showbase);

       //enum coordinate_calculation_option{relative,local,car,global};
       string scoo;
       if(A.m_coordinate_calculation_option == BPoint_bore::relative) scoo = "(relative)";
       if(A.m_coordinate_calculation_option == BPoint_bore::local)   scoo = "(local)";
       if(A.m_coordinate_calculation_option == BPoint_bore::car)     scoo = "(car)";
       if(A.m_coordinate_calculation_option == BPoint_bore::global)  scoo = "(global)";

       s<<" ### BPoint_bore ###"
        <<std::endl<< *A.m_cam_bore

        <<std::endl<<"  picture coordinates nr(m,n) std(dm,dn) : " << A.get_point_number()<<"("<<A.get_m()<<","<<A.get_n()<<") std("<<A.get_dm()<<","<<A.get_dn()<<")"
        <<std::endl<<"  transformed outer orientation point    : " << BPoint(A).get_Cam().get_O()
        <<std::endl<<"  car position                           : " << *A.m_car_pos
        <<std::endl<<"  relevant measurement                   : " << A.get_measurement_point( A.get_calculation_option() )<<" "<<scoo
        <<std::endl<<" ### end BPoint_bore ###";
return s;
}
