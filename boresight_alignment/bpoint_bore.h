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
#include <vector>
#include <exception>

//libphotogrammetrie.so
#include "cam_bore.h"
#include "..//basics//point.h"
#include "..//basics//point_nr.h"
#include "..//basics//ebene.h"
#include "..//photo//bpoint.h"
#include "..//position//gps_pos.h"


class BPoint_bore
{
public:
    enum coordinate_calculation_option{relative,local,car,global};
    //constructor I - only inner/outer/boresight orientation parameters + position of the car
    BPoint_bore(Cam_bore &cam_bore,Gps_pos &car_pos, unsigned int nr);
    //constructor II - inner/outer/boresight orientation parameters + position of the car + picture coordinates
    BPoint_bore(Cam_bore &cam_bore,Gps_pos &car_pos,unsigned int nr,double m,double n);
    //constructor III - inner/outer/boresight orientation parameters + position of the car + global point in front of the camera
    BPoint_bore(Cam_bore &cam_bore,Gps_pos &car_pos,Point_nr &global_measurement_point,const enum coordinate_calculation_option& global_measurement_point_cco);
    //deconstructor
    virtual ~BPoint_bore();

    BPoint_bore(const BPoint_bore &BPb); //use the standard copy constructor
    BPoint_bore& operator=(const BPoint_bore &BPb);

    // convertion of "BPoint_bore  >>-->  BPoint"
    operator BPoint () const;

    enum coordinate_calculation_option const get_calculation_option() const;
    void set_calculation_option(const enum coordinate_calculation_option& co);

    Point_nr get_measurement_point(const enum coordinate_calculation_option& co) const;


    //get picture coordinate on the epipolar geometrie (condition: set all values of constructor II and set a second camera with its car_position)
    BPoint_bore& get_picture_coordinate_on_the_epipolar_geometrie( BPoint_bore& BPb, double s);

    //mono photogrammetry global (condition: set all values of constructor II)
    //Ebene E is set to or ist transforn into car coordinate system
    Point_nr calc_mono_cam_to_plane_intersection(Ebene &E,const enum coordinate_calculation_option& E_cco);

    //get and set functions

    unsigned int get_point_number() const;
    void         set_point_number(unsigned int nr);

    double get_m() const;
    double get_n() const;
    double get_dm() const;
    double get_dn() const;

    Cam_bore& get_cam_bore();
    Gps_pos&  get_car_pos();

    friend class Forward_intersection_bore;
    friend ostream& operator<<(ostream& s,const BPoint_bore& A);

    //it is a kind of mono photogrammetry
    Point_nr calc_footprint_point(Ebene &E,const enum coordinate_calculation_option& E_cco,double distance_cut);

private:
    //internal functions
    void set_values_from_BPoint_class();
    void set_values_from_cam_bore_calc_member();
    void reset_rellativ_orientation_cam_bore_calc_member();
    void set_measurement_point(Point_nr& p_nr, const enum coordinate_calculation_option& co);

    void transform_measurement_point(const enum coordinate_calculation_option& cco);

    //camera calibration original
    Cam_bore *m_cam_bore;

    //position of the car in global coordinates
    Gps_pos  *m_car_pos;

    //camera calibration for calculation and transformation
    Cam_bore m_cam_bore_calc;

    //picture coordinates original
    unsigned int m_nr; //point number
    double m_m,m_n;
    double m_dm,m_dn;

    //picture point without boresight calibration
    BPoint m_BP;


    //picture coordinates for the backward calculation -> after the forward intersection/bundle adjustment
    double m_m_cb,m_n_cb;
    double m_dm_cb,m_dn_cb;

    //the same points were measured in different coordinate systems -> after the forward intersection/bundle adjustment
    Point_nr     m_local_measurement_point;
    Point_nr     m_car_measurement_point;
    Point_nr     m_global_measurement_point;

    coordinate_calculation_option m_coordinate_calculation_option;

    //for updating changes on camera
    enum INPUT_TYPE{none,picture,object,calculation_fwi,calculation_bundle};
    INPUT_TYPE m_input_type;
};

ostream& operator<<(ostream& s,const BPoint_bore& A);

#endif /* BPOINT_BORE_H_ */
