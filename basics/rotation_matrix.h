/*
 * rotation_matrix.h
 *
 *  Created on: 15.10.2010
 *      Author: steffen
 */

#ifndef ROTATION_MATRIX_H_
#define ROTATION_MATRIX_H_

#include <iostream>
#include <cmath>

#include "matrix//matrix.h"

class Rotation_matrix
{
public:
    //type for the rotation / it divide into different rotation sets
    enum ROT_MATRIX_TYPE{math,geodetic};
    enum DIFFERENTIATE_ANGLE{rotx,roty,rotz};

    Rotation_matrix(ROT_MATRIX_TYPE type,double rotX,double rotY,double rotZ);
    Rotation_matrix(ROT_MATRIX_TYPE type,double rotX,double rotY,double rotZ,double drotX,double drotY,double drotZ);
    Rotation_matrix(const Matrix& R);
    Rotation_matrix(const Rotation_matrix& R);
    virtual ~Rotation_matrix();

    Rotation_matrix& operator=(const Rotation_matrix& R);
    Rotation_matrix& operator=(const Matrix& R);

    //convert into the basic class matrix
    operator Matrix& ();

    //Matrix R;
    Matrix get_Matrix();

    bool get_rotation_angle(ROT_MATRIX_TYPE type,double& rotX,double& rotY,double& rotZ) const;
    bool get_rotation_angle(ROT_MATRIX_TYPE type,double& rotX,double& rotY,double& rotZ,double& drotX,double& drotY,double& drotZ) const;
    bool get_rotation_angle_std(ROT_MATRIX_TYPE type,double& drotX,double& drotY,double& drotZ) const;

    Matrix get_differentiate_matrix(DIFFERENTIATE_ANGLE angle);

    //derivative of rotations matrix (math and geodetic)
    double get_dr11_drotx(ROT_MATRIX_TYPE type);
    double get_dr11_droty(ROT_MATRIX_TYPE type);
    double get_dr11_drotz(ROT_MATRIX_TYPE type);

    double get_dr12_drotx(ROT_MATRIX_TYPE type);
    double get_dr12_droty(ROT_MATRIX_TYPE type);
    double get_dr12_drotz(ROT_MATRIX_TYPE type);

    double get_dr13_drotx(ROT_MATRIX_TYPE type);
    double get_dr13_droty(ROT_MATRIX_TYPE type);
    double get_dr13_drotz(ROT_MATRIX_TYPE type);

    double get_dr21_drotx(ROT_MATRIX_TYPE type);
    double get_dr21_droty(ROT_MATRIX_TYPE type);
    double get_dr21_drotz(ROT_MATRIX_TYPE type);

    double get_dr22_drotx(ROT_MATRIX_TYPE type);
    double get_dr22_droty(ROT_MATRIX_TYPE type);
    double get_dr22_drotz(ROT_MATRIX_TYPE type);

    double get_dr23_drotx(ROT_MATRIX_TYPE type);
    double get_dr23_droty(ROT_MATRIX_TYPE type);
    double get_dr23_drotz(ROT_MATRIX_TYPE type);

    double get_dr31_drotx(ROT_MATRIX_TYPE type);
    double get_dr31_droty(ROT_MATRIX_TYPE type);
    double get_dr31_drotz(ROT_MATRIX_TYPE type);

    double get_dr32_drotx(ROT_MATRIX_TYPE type);
    double get_dr32_droty(ROT_MATRIX_TYPE type);
    double get_dr32_drotz(ROT_MATRIX_TYPE type);

    double get_dr33_drotx(ROT_MATRIX_TYPE type);
    double get_dr33_droty(ROT_MATRIX_TYPE type);
    double get_dr33_drotz(ROT_MATRIX_TYPE type);

    bool test_angle_to_rotation_matrix();

    const string get_errorstring() const;
    ROT_MATRIX_TYPE get_rotation_matrix_type() const;


private:
    //help funktion
    double clamp(double& wert, double min, double max);

    //functions for the different rotation matrix
    //mathematic rotation [x][y][z]
    double get_math_r11(){return   cos( m_angle_math_rotY) * cos( m_angle_math_rotZ) ;}
    double get_math_r12(){return - cos( m_angle_math_rotY) * sin( m_angle_math_rotZ);}
    double get_math_r13(){return   sin( m_angle_math_rotY);}

    double get_math_r21(){return   cos( m_angle_math_rotX) * sin( m_angle_math_rotZ) + sin( m_angle_math_rotX) * sin( m_angle_math_rotY) * cos( m_angle_math_rotZ);}
    double get_math_r22(){return   cos( m_angle_math_rotX) * cos( m_angle_math_rotZ) - sin( m_angle_math_rotX) * sin( m_angle_math_rotY) * sin( m_angle_math_rotZ);}
    double get_math_r23(){return - sin( m_angle_math_rotX) * cos( m_angle_math_rotY);}

    double get_math_r31(){return sin( m_angle_math_rotX) * sin( m_angle_math_rotZ) - cos( m_angle_math_rotX) * sin( m_angle_math_rotY) * cos( m_angle_math_rotZ);}
    double get_math_r32(){return sin( m_angle_math_rotX) * cos( m_angle_math_rotZ) + cos( m_angle_math_rotX) * sin( m_angle_math_rotY) * sin( m_angle_math_rotZ);}
    double get_math_r33(){return cos( m_angle_math_rotX) * cos( m_angle_math_rotY);}

    //functions for the different rotation matrix
    //geodetic rotation [z][y][x]
    double get_geod_r11(){return cos(m_angle_geod_rotY) * cos(m_angle_geod_rotZ) ;}
    double get_geod_r12(){return sin(m_angle_geod_rotX) * sin(m_angle_geod_rotY) * cos(m_angle_geod_rotZ) - cos(m_angle_geod_rotX) * sin(m_angle_geod_rotZ) ;}
    double get_geod_r13(){return cos(m_angle_geod_rotX) * sin(m_angle_geod_rotY) * cos(m_angle_geod_rotZ) + sin(m_angle_geod_rotX) * sin(m_angle_geod_rotZ) ;}

    double get_geod_r21(){return cos(m_angle_geod_rotY) * sin(m_angle_geod_rotZ) ;}
    double get_geod_r22(){return cos(m_angle_geod_rotX) * cos(m_angle_geod_rotZ) + sin(m_angle_geod_rotX) * sin(m_angle_geod_rotY) * sin(m_angle_geod_rotZ) ;}
    double get_geod_r23(){return cos(m_angle_geod_rotX) * sin(m_angle_geod_rotY) * sin(m_angle_geod_rotZ) - sin(m_angle_geod_rotX) * cos(m_angle_geod_rotZ) ;}

    double get_geod_r31(){return -sin(m_angle_geod_rotY) ;}
    double get_geod_r32(){return sin(m_angle_geod_rotX) * cos(m_angle_geod_rotY) ;}
    double get_geod_r33(){return cos(m_angle_geod_rotX) * cos(m_angle_geod_rotY) ;}

    //get the rotation angle (without calculation)
    bool get_rotation_angle_math(double& rotX,double& rotY,double& rotZ);
    bool get_rotation_angle_geod(double& rotX,double& rotY,double& rotZ);

    //create/calculate the rotation matrix
    void set_rotation_angle_math(double& rotX,double& rotY,double& rotZ);
    void set_rotation_angle_geod(double& rotX,double& rotY,double& rotZ);



    ROT_MATRIX_TYPE m_rot_matrix_type;

    //angle invariant
    Matrix m_R;

    //different angle for different rotation order of the angle
    double m_angle_math_rotX,m_angle_math_rotY,m_angle_math_rotZ;
    double m_angle_geod_rotX,m_angle_geod_rotY,m_angle_geod_rotZ;

    double m_angle_math_drotX,m_angle_math_drotY,m_angle_math_drotZ;
    double m_angle_geod_drotX,m_angle_geod_drotY,m_angle_geod_drotZ;

    bool isError;
    string m_errorstring;

    //for testing the backward calculation in function "get_rotation_angle_*()"
    bool m_intern_test;
};

#endif /* ROTATION_MATRIX_H_ */
