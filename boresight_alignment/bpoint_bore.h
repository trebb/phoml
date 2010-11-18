//============================================================================
// Name        : bpoint_bore.h
// Author      : Steffen Scheller
// Version     : 0.00x
// Copyright   : ©2010
// Description : mobile mapping photogrammetry program C++, ANSI-style
//============================================================================
#ifndef BPOINT_BORE_H_
#define BPOINT_BORE_H_

#include <iostream>

//libphotogrammetrie.so
#include "cam_bore.h"
#include "..//basics//point.h"
#include "..//basics//ebene.h"
#include "..//photo//bpoint.h"
#include "..//position//gps_pos.h"


class BPoint_bore
{
public:
    enum calculation_option{rell,absolute};
    //constructor I - only inner/outer/boresight orientation parameters + position of the car
    BPoint_bore(Cam_bore &cam_bore,Gps_pos &car_pos);
    //constructor II - inner/outer/boresight orientation parameters + position of the car + picture coordinates
    BPoint_bore(Cam_bore &cam_bore,Gps_pos &car_pos,double m,double n);
    //constructor III - inner/outer/boresight orientation parameters + position of the car + global point in front of the camera
    BPoint_bore(Cam_bore &cam_bore,Gps_pos &car_pos,Point &global_measurement_point);
    //deconstructor
    virtual ~BPoint_bore();

    BPoint_bore(const BPoint_bore &BPb); //use the standard copy constructor
    BPoint_bore& operator=(const BPoint_bore &BPb);

    // convertion of "BPoint_bore  >>-->  BPoint"
    operator BPoint () const;

    enum calculation_option const get_calculation_option() const;
    void set_calculation_option(const enum calculation_option& co);

    //get picture coordinate on the epipolar geometrie (condition: set all values of constructor II and set a second camera with its car_position)
    BPoint get_picture_coordinate_on_the_epipolar_geometrie( Cam_bore &cam_bore, Gps_pos &car_pos, double s );

    //mono photogrammetry global (condition: set all values of constructor II)
    Point calc_mono_cam_to_plane_intersection(Ebene &E);

    friend ostream& operator<<(ostream& s,const BPoint_bore& A);
private:

    //camera calibration
    Cam_bore *m_cam_bore;

    //position of the car in global coordinates
    Gps_pos  *m_car_pos;

    //camera calibration for calculation and transformation
    Cam_bore m_cam_bore_calc;

    //picture point without boresight calibration
    BPoint m_BP;

    //picture coordinates for the backward calculation -> after the forward intersection/bundle adjustment
    double m_m_cb,m_n_cb;
    double m_dm_cb,m_dn_cb;



    //the same points were measured in different coordinate systems
    Point     m_local_measurement_point;
    Point     m_global_measurement_point;

    calculation_option m_calculation_option;
};

ostream& operator<<(ostream& s,const BPoint_bore& A);

#endif /* BPOINT_BORE_H_ */
