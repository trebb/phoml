/*
 * rotation_matrix.cpp
 *
 *  Created on: 15.10.2010
 *      Author: steffen
 */

#include "rotation_matrix.h"

#include "fix_values.h"

//constructor I
Rotation_matrix::Rotation_matrix(ROT_MATRIX_TYPE type,double rotation_X,double rotation_Y,double rotation_Z)
{
     isError=false;
     m_intern_test=false;

     //set the rotation angle for the matrix
     m_rot_matrix_type = type;
     m_R.create(3,3,Null);

     //mathematic rotation [x][y][z]
     if(m_rot_matrix_type == Rotation_matrix::math)
     {
         m_angle_math_rotX = rotation_X;
         m_angle_math_rotY = rotation_Y;
         m_angle_math_rotZ = rotation_Z;
         m_angle_math_drotX = 0.0;
         m_angle_math_drotY = 0.0;
         m_angle_math_drotZ = 0.0;

         set_rotation_angle_math(m_angle_math_rotX,m_angle_math_rotY,m_angle_math_rotZ);

         //calc the rotation angle of geodetic system
         get_rotation_angle_geod(m_angle_geod_rotX,m_angle_geod_rotY,m_angle_geod_rotZ);
     }

     //geodetic rotation [z][y][x]
     if(m_rot_matrix_type == Rotation_matrix::geodetic)
     {
          m_angle_geod_rotX = rotation_X;
          m_angle_geod_rotY = rotation_Y;
          m_angle_geod_rotZ = rotation_Z;
          m_angle_math_drotX = 0.0;
          m_angle_math_drotY = 0.0;
          m_angle_math_drotZ = 0.0;

          set_rotation_angle_geod(m_angle_geod_rotX,m_angle_geod_rotY,m_angle_geod_rotZ);

          //calc the rotation angle of math system
          get_rotation_angle_math(m_angle_math_rotX,m_angle_math_rotY,m_angle_math_rotZ);
      }

}

//constructor III
Rotation_matrix::Rotation_matrix(ROT_MATRIX_TYPE type,double rotation_X,double rotation_Y,double rotation_Z,double rotation_dX,double rotation_dY,double rotation_dZ)
{
     isError=false;
     m_intern_test=false;

     //set the rotation angle for the matrix
     m_rot_matrix_type = type;
     m_R.create(3,3,Null);

     //mathematic rotation [x][y][z]
     if(m_rot_matrix_type == Rotation_matrix::math)
     {
         m_angle_math_rotX = rotation_X;
         m_angle_math_rotY = rotation_Y;
         m_angle_math_rotZ = rotation_Z;
         m_angle_math_drotX = fabs(rotation_dX);
         m_angle_math_drotY = fabs(rotation_dY);
         m_angle_math_drotZ = fabs(rotation_dZ);

         set_rotation_angle_math(m_angle_math_rotX,m_angle_math_rotY,m_angle_math_rotZ);

         //calc the rotation angle of geodetic system
         get_rotation_angle_geod(m_angle_geod_rotX,m_angle_geod_rotY,m_angle_geod_rotZ);
     }

     //geodetic rotation [z][y][x]
     if(m_rot_matrix_type == Rotation_matrix::geodetic)
     {
          m_angle_geod_rotX = rotation_X;
          m_angle_geod_rotY = rotation_Y;
          m_angle_geod_rotZ = rotation_Z;
          m_angle_geod_drotX = fabs(rotation_dX);
          m_angle_geod_drotY = fabs(rotation_dY);
          m_angle_geod_drotZ = fabs(rotation_dZ);

          set_rotation_angle_geod(m_angle_geod_rotX,m_angle_geod_rotY,m_angle_geod_rotZ);

          //calc the rotation angle of math system
          get_rotation_angle_math(m_angle_math_rotX,m_angle_math_rotY,m_angle_math_rotZ);
      }

}

//constructor III
Rotation_matrix::Rotation_matrix(const Matrix& R)
{
 //(*this).m_R=R.MatCopy(); //not compiled
 (*this)=R;
}
//copy constructor
Rotation_matrix::Rotation_matrix(const Rotation_matrix& R)
{
 (*this)=R;
}
//deconstructor
Rotation_matrix::~Rotation_matrix()
{
 //R.~Matrix();
}

Rotation_matrix& Rotation_matrix::operator=(const Rotation_matrix& R)
{
 isError = R.isError;
 m_intern_test=false;
 m_errorstring = R.m_errorstring;
 m_rot_matrix_type = R.m_rot_matrix_type;
 //(*this).m_R=R.m_R; //this is not a copy!!!
 (*this).m_R=R.m_R.MatCopy();

 //calc the rotation angle
 get_rotation_angle_math(m_angle_math_rotX,m_angle_math_rotY,m_angle_math_rotZ);
 get_rotation_angle_geod(m_angle_geod_rotX,m_angle_geod_rotY,m_angle_geod_rotZ);

 //copy the angle standard deviation
 m_angle_math_drotX=R.m_angle_math_drotX;
 m_angle_math_drotY=R.m_angle_math_drotY;
 m_angle_math_drotZ=R.m_angle_math_drotZ;

 return (*this);
}

Rotation_matrix& Rotation_matrix::operator=(const Matrix& R)
{
 isError = false;
 m_intern_test=false;
 m_errorstring="";
 m_rot_matrix_type = Rotation_matrix::math;

 m_R=R.MatCopy();

 //calc the rotation angle
 get_rotation_angle_math(m_angle_math_rotX,m_angle_math_rotY,m_angle_math_rotZ);
 get_rotation_angle_geod(m_angle_geod_rotX,m_angle_geod_rotY,m_angle_geod_rotZ);

 return (*this);
}

Rotation_matrix::operator Matrix& ()
{
 return m_R;
}

Matrix Rotation_matrix::get_Matrix()
{
 return m_R.MatCopy();
}

bool Rotation_matrix::get_rotation_angle(ROT_MATRIX_TYPE type,double& rotX,double& rotY,double& rotZ) const
{
        //mathematic rotation [x][y][z]
        if(type == Rotation_matrix::math)
        {
         rotX = m_angle_math_rotX;
         rotY = m_angle_math_rotY;
         rotZ = m_angle_math_rotZ;
        }

        //geodetic rotation [z][y][x]
        if(type == Rotation_matrix::geodetic)
        {
         rotX = m_angle_geod_rotX;
         rotY = m_angle_geod_rotY;
         rotZ = m_angle_geod_rotZ;
        }


return isError;
}

bool Rotation_matrix::get_rotation_angle(ROT_MATRIX_TYPE type,double& rotX,double& rotY,double& rotZ,double& drotX,double& drotY,double& drotZ) const
{
    //mathematic rotation [x][y][z]
    if(type == Rotation_matrix::math)
    {
     rotX = m_angle_math_rotX;
     rotY = m_angle_math_rotY;
     rotZ = m_angle_math_rotZ;
     drotX = m_angle_math_drotX;
     drotY = m_angle_math_drotY;
     drotZ = m_angle_math_drotZ;
    }

    //geodetic rotation [z][y][x]
    if(type == Rotation_matrix::geodetic)
    {
     rotX = m_angle_geod_rotX;
     rotY = m_angle_geod_rotY;
     rotZ = m_angle_geod_rotZ;
     drotX = m_angle_geod_drotX;
     drotY = m_angle_geod_drotY;
     drotZ = m_angle_geod_drotZ;
    }


return isError;
}

bool Rotation_matrix::get_rotation_angle_std(ROT_MATRIX_TYPE type,double& drotX,double& drotY,double& drotZ) const
{
    //mathematic rotation [x][y][z]
      if(type == Rotation_matrix::math)
      {
       drotX = m_angle_math_drotX;
       drotY = m_angle_math_drotY;
       drotZ = m_angle_math_drotZ;
      }

      //geodetic rotation [z][y][x]
      if(type == Rotation_matrix::geodetic)
      {
       drotX = m_angle_geod_drotX;
       drotY = m_angle_geod_drotY;
       drotZ = m_angle_geod_drotZ;
      }


return isError;
}

bool Rotation_matrix::get_rotation_angle_math(double& rotX,double& rotY,double& rotZ)
{
    if(m_R.getCol()==3 && m_R.getRow()==3)
    {

          double r11 =m_R(0,0);
          double r12 =m_R(0,1);
          double r13 =m_R(0,2);
          double r21 =m_R(1,0);
          double r22 =m_R(1,1);
          double r23 =m_R(1,2);
          double r31 =m_R(2,0);
          double r32 =m_R(2,1);
          double r33 =m_R(2,2);

          double threshold = 9.99999e-13;
          if(fabs(r11)<threshold) r11=0.0;
          if(fabs(r21)<threshold) r21=0.0;
          if(fabs(r31)<threshold) r31=0.0;
          if(fabs(r12)<threshold) r12=0.0;
          if(fabs(r22)<threshold) r22=0.0;
          if(fabs(r32)<threshold) r32=0.0;
          if(fabs(r13)<threshold) r13=0.0;
          if(fabs(r23)<threshold) r23=0.0;
          if(fabs(r33)<threshold) r33=0.0;

          rotY = asin(r13);

          if(r23||r33)
           rotX = atan2(-r23,r33);
          else
           rotX = atan2(-r22,r32);


          if(r12||r11)
           rotZ = atan2(-r12,r11);
          else
           rotZ = atan2(-r22,r21);


          if(fabs(r13-1.0) < threshold || fabs(r13+1.0) < threshold)
          {
            if(r32||r22)
            {
             rotX = atan2(r32,r22);
             rotZ = 0.0;
            }
            else
            {
             rotX = 0.0;
             rotZ = atan2(r21,r22);
            }
          }

          rotX = clamp(rotX, -PI, PI);
          rotY   = clamp(rotY  , -PI, PI);
          rotZ = clamp(rotZ, -PI, PI);

    }
    else
    {
     isError=true;
     m_errorstring="No matrix available!!";
     return false;
    }
return true;
}

bool Rotation_matrix::get_rotation_angle_geod(double& rotX,double& rotY,double& rotZ)
{
    if(m_R.getCol()==3 && m_R.getRow()==3)
    {
           double r11 =m_R(0,0);
           double r12 =m_R(0,1);
           double r13 =m_R(0,2);
           double r21 =m_R(1,0);
           double r22 =m_R(1,1);
           double r23 =m_R(1,2);
           double r31 =m_R(2,0);
           double r32 =m_R(2,1);
           double r33 =m_R(2,2);

           double threshold = pow(9.99999,-13);
           if(fabs(r11)<threshold) r11=0.0;
           if(fabs(r21)<threshold) r21=0.0;
           if(fabs(r31)<threshold) r31=0.0;
           if(fabs(r12)<threshold) r12=0.0;
           if(fabs(r22)<threshold) r22=0.0;
           if(fabs(r32)<threshold) r32=0.0;
           if(fabs(r13)<threshold) r13=0.0;
           if(fabs(r23)<threshold) r23=0.0;
           if(fabs(r33)<threshold) r33=0.0;

           if(r32||r33)
           {
            rotX = atan2(r32,r33);
           }

           if(r32||r33||r31)
           {
              rotY = atan2(-r31,sqrt(r32*r32+r33*r33));
           }
           else if(r31)
           {
              rotY = -asin(r31);
           }

           if(r21||r11)
           {
            rotZ = atan2(r21,r11);
           }

           rotX = clamp(rotX, -PI, PI);
           rotY = clamp(rotY, -PI, PI);
           rotZ = clamp(rotZ, 0, 2*PI);

     }
     else
     {
      isError=true;
      m_errorstring="No rotation matrix available!!";
      return false;
     }
return true;
}


void Rotation_matrix::set_rotation_angle_math(double& rotX,double& rotY,double& rotZ)
{
    m_R(0,0) = get_math_r11();
    m_R(0,1) = get_math_r12();
    m_R(0,2) = get_math_r13();

    m_R(1,0) = get_math_r21();
    m_R(1,1) = get_math_r22();
    m_R(1,2) = get_math_r23();

    m_R(2,0) = get_math_r31();
    m_R(2,1) = get_math_r32();
    m_R(2,2) = get_math_r33();

}

void Rotation_matrix::set_rotation_angle_geod(double& rotX,double& rotY,double& rotZ)
{
    m_R(0,0) = get_geod_r11();
    m_R(0,1) = get_geod_r12();
    m_R(0,2) = get_geod_r13();

    m_R(1,0) = get_geod_r21();
    m_R(1,1) = get_geod_r22();
    m_R(1,2) = get_geod_r23();

    m_R(2,0) = get_geod_r31();
    m_R(2,1) = get_geod_r32();
    m_R(2,2) = get_geod_r33();
}

Matrix Rotation_matrix::get_differentiate_matrix(DIFFERENTIATE_ANGLE angle)
{
  Matrix diff(3,3,Null);

  //fill Matrix
  if(angle == Rotation_matrix::rotx)
  {
    diff(0,0) = (*this).get_dr11_drotx(m_rot_matrix_type);
    diff(0,1) = (*this).get_dr12_drotx(m_rot_matrix_type);
    diff(0,2) = (*this).get_dr13_drotx(m_rot_matrix_type);

    diff(1,0) = (*this).get_dr21_drotx(m_rot_matrix_type);
    diff(1,1) = (*this).get_dr22_drotx(m_rot_matrix_type);
    diff(1,2) = (*this).get_dr23_drotx(m_rot_matrix_type);

    diff(2,0) = (*this).get_dr31_drotx(m_rot_matrix_type);
    diff(2,1) = (*this).get_dr32_drotx(m_rot_matrix_type);
    diff(2,2) = (*this).get_dr33_drotx(m_rot_matrix_type);
  }

  if(angle == Rotation_matrix::roty)
  {
    diff(0,0) = (*this).get_dr11_droty(m_rot_matrix_type);
    diff(0,1) = (*this).get_dr12_droty(m_rot_matrix_type);
    diff(0,2) = (*this).get_dr13_droty(m_rot_matrix_type);

    diff(1,0) = (*this).get_dr21_droty(m_rot_matrix_type);
    diff(1,1) = (*this).get_dr22_droty(m_rot_matrix_type);
    diff(1,2) = (*this).get_dr23_droty(m_rot_matrix_type);

    diff(2,0) = (*this).get_dr31_droty(m_rot_matrix_type);
    diff(2,1) = (*this).get_dr32_droty(m_rot_matrix_type);
    diff(2,2) = (*this).get_dr33_droty(m_rot_matrix_type);

  }
  if(angle == Rotation_matrix::rotz)
  {
    diff(0,0) = (*this).get_dr11_drotz(m_rot_matrix_type);
    diff(0,1) = (*this).get_dr12_drotz(m_rot_matrix_type);
    diff(0,2) = (*this).get_dr13_drotz(m_rot_matrix_type);

    diff(1,0) = (*this).get_dr21_drotz(m_rot_matrix_type);
    diff(1,1) = (*this).get_dr22_drotz(m_rot_matrix_type);
    diff(1,2) = (*this).get_dr23_drotz(m_rot_matrix_type);

    diff(2,0) = (*this).get_dr31_drotz(m_rot_matrix_type);
    diff(2,1) = (*this).get_dr32_drotz(m_rot_matrix_type);
    diff(2,2) = (*this).get_dr33_drotz(m_rot_matrix_type);

  }

 return diff.MatCopy();
}
//############################################################

double Rotation_matrix::get_dr11_drotx(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return 0.0;
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return 0.0;
    }
return 0.0;
}

double Rotation_matrix::get_dr11_droty(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return - sin(m_angle_math_rotY) * cos(m_angle_math_rotZ);
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return -sin(m_angle_geod_rotY) * cos(m_angle_geod_rotZ);
    }
return 0.0;
}

double Rotation_matrix::get_dr11_drotz(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return -cos(m_angle_math_rotY) * sin(m_angle_math_rotZ);
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return -cos(m_angle_geod_rotY) * sin(m_angle_geod_rotZ);
    }
return 0.0;
}
//############################################################

double Rotation_matrix::get_dr12_drotx(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return 0.0;
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return cos(m_angle_geod_rotX) * sin(m_angle_geod_rotY) * cos(m_angle_geod_rotZ) + sin(m_angle_geod_rotX) * sin(m_angle_geod_rotZ);
    }
return 0.0;
}

double Rotation_matrix::get_dr12_droty(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return -sin(m_angle_math_rotY) * sin(m_angle_math_rotZ);
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return sin(m_angle_geod_rotX) * cos(m_angle_geod_rotY) * cos(m_angle_geod_rotZ);
    }
return 0.0;
}

double Rotation_matrix::get_dr12_drotz(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return -cos(m_angle_math_rotY) * cos(m_angle_math_rotZ);
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return sin(m_angle_geod_rotX) * sin(m_angle_geod_rotY) * (-sin(m_angle_geod_rotZ)) - cos(m_angle_geod_rotX) * cos(m_angle_geod_rotZ);
    }
return 0.0;
}
//############################################################

double Rotation_matrix::get_dr13_drotx(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return 0.0;
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return -sin(m_angle_geod_rotX) * sin(m_angle_geod_rotY) * cos(m_angle_geod_rotZ) + cos(m_angle_geod_rotX) * sin(m_angle_geod_rotZ);
    }
return 0.0;
}

double Rotation_matrix::get_dr13_droty(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return cos(m_angle_math_rotY);
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return cos(m_angle_geod_rotX) * cos(m_angle_geod_rotY) * cos(m_angle_geod_rotZ);
    }
return 0.0;
}

double Rotation_matrix::get_dr13_drotz(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return 0.0;
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return cos(m_angle_geod_rotX) * sin(m_angle_geod_rotY) * (-sin(m_angle_geod_rotZ)) + sin(m_angle_geod_rotX) * cos(m_angle_geod_rotZ);
    }
return 0.0;
}
//############################################################

double Rotation_matrix::get_dr21_drotx(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return -sin(m_angle_math_rotX) * sin(m_angle_math_rotZ) + cos(m_angle_math_rotX) * sin(m_angle_math_rotY) * cos(m_angle_math_rotZ);
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return 0.0;
    }
return 0.0;
}

double Rotation_matrix::get_dr21_droty(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return sin(m_angle_math_rotX) * cos(m_angle_math_rotY) * cos(m_angle_math_rotZ);
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return -sin(m_angle_geod_rotY) * sin(m_angle_geod_rotZ);
    }
return 0.0;
}

double Rotation_matrix::get_dr21_drotz(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return cos(m_angle_math_rotX) * cos(m_angle_math_rotZ) + sin(m_angle_math_rotX) * sin(m_angle_math_rotY) * (-sin(m_angle_math_rotZ));
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return cos(m_angle_geod_rotY) * cos(m_angle_geod_rotZ);
    }
return 0.0;
}
//############################################################

double Rotation_matrix::get_dr22_drotx(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return -sin(m_angle_math_rotX) * cos(m_angle_math_rotZ) - cos(m_angle_math_rotX) * sin(m_angle_math_rotY) * sin(m_angle_math_rotZ);
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return -sin(m_angle_geod_rotX) * cos(m_angle_geod_rotZ) + cos(m_angle_geod_rotX) * sin(m_angle_geod_rotY) * sin(m_angle_geod_rotZ);
    }
return 0.0;
}

double Rotation_matrix::get_dr22_droty(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return -sin(m_angle_math_rotX) * cos(m_angle_math_rotY) * sin(m_angle_math_rotZ);
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return sin(m_angle_geod_rotX) * cos(m_angle_geod_rotY) * sin(m_angle_geod_rotZ);
    }
return 0.0;
}

double Rotation_matrix::get_dr22_drotz(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return cos(m_angle_math_rotX) * (-sin(m_angle_math_rotZ)) - sin(m_angle_math_rotX) * sin(m_angle_math_rotY) * cos(m_angle_math_rotZ);
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return cos(m_angle_geod_rotX) * (-sin(m_angle_geod_rotZ)) + sin(m_angle_geod_rotX) * sin(m_angle_geod_rotY) * cos(m_angle_geod_rotZ);
    }
return 0.0;
}
//############################################################

double Rotation_matrix::get_dr23_drotx(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return cos(m_angle_math_rotX) * cos(m_angle_math_rotY);
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return -sin(m_angle_geod_rotX) * sin(m_angle_geod_rotY) * sin(m_angle_geod_rotZ) - cos(m_angle_geod_rotX) * cos(m_angle_geod_rotZ);
    }
return 0.0;
}

double Rotation_matrix::get_dr23_droty(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return sin(m_angle_math_rotX) * (-sin(m_angle_math_rotY));
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return cos(m_angle_geod_rotX) * cos(m_angle_geod_rotY) * sin(m_angle_geod_rotZ);
    }
return 0.0;
}

double Rotation_matrix::get_dr23_drotz(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return 0.0;
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return cos(m_angle_geod_rotX) * sin(m_angle_geod_rotY) * cos(m_angle_geod_rotZ) - sin(m_angle_geod_rotX) * (-sin(m_angle_geod_rotZ));
    }
return 0.0;
}
//############################################################

double Rotation_matrix::get_dr31_drotx(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return cos(m_angle_math_rotX) * sin(m_angle_math_rotZ) + sin(m_angle_math_rotX) * sin(m_angle_math_rotY) * cos(m_angle_math_rotZ);
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return 0.0;
    }
return 0.0;
}

double Rotation_matrix::get_dr31_droty(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return - cos(m_angle_math_rotX) * cos(m_angle_math_rotY) * cos(m_angle_math_rotZ);
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return -cos(m_angle_geod_rotY);
    }
return 0.0;
}

double Rotation_matrix::get_dr31_drotz(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return sin(m_angle_math_rotX) * cos(m_angle_math_rotZ) - cos(m_angle_math_rotX) * sin(m_angle_math_rotY) * (-sin(m_angle_math_rotZ));
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return 0.0;
    }
return 0.0;
}
//############################################################

double Rotation_matrix::get_dr32_drotx(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return cos(m_angle_math_rotX) * cos(m_angle_math_rotZ) + (-sin(m_angle_math_rotX)) * sin(m_angle_math_rotY) * sin(m_angle_math_rotZ);
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return cos(m_angle_geod_rotX) * cos(m_angle_geod_rotY);
    }
return 0.0;
}

double Rotation_matrix::get_dr32_droty(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return cos(m_angle_math_rotX) * cos(m_angle_math_rotY) * sin(m_angle_math_rotZ);
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return sin(m_angle_geod_rotX) * (-sin(m_angle_geod_rotY));
    }
return 0.0;
}

double Rotation_matrix::get_dr32_drotz(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return sin(m_angle_math_rotX) * (-sin(m_angle_math_rotZ)) + cos(m_angle_math_rotX) * sin(m_angle_math_rotY) * cos(m_angle_math_rotZ);
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return 0.0;
    }
return 0.0;
}
//############################################################

double Rotation_matrix::get_dr33_drotx(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return -sin(m_angle_math_rotX) * cos(m_angle_math_rotY);
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return -sin(m_angle_geod_rotX) * cos(m_angle_geod_rotY);
    }
return 0.0;
}

double Rotation_matrix::get_dr33_droty(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return cos(m_angle_math_rotX) * (-sin(m_angle_math_rotY));
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return cos(m_angle_geod_rotX) * (-sin(m_angle_geod_rotY));
    }
return 0.0;
}

double Rotation_matrix::get_dr33_drotz(ROT_MATRIX_TYPE type)
{
    if(m_rot_matrix_type == Rotation_matrix::math)
    {
        return 0.0;
    }
    if(m_rot_matrix_type == Rotation_matrix::geodetic)
    {
        return 0.0;
    }
return 0.0;
}
//############################################################

bool Rotation_matrix::test_angle_to_rotation_matrix()
{

    double threshold = pow(9.99999,-13);

        Rotation_matrix R_math(Rotation_matrix::math,m_angle_math_rotX,m_angle_math_rotY,m_angle_math_rotZ);
        if(!R_math.get_Matrix().NearEqual(m_R,threshold))
        {
            isError=true;
            m_errorstring="calculation fails!!";
            return false;
        }

        Rotation_matrix R_geod(Rotation_matrix::geodetic,m_angle_geod_rotX,m_angle_geod_rotY,m_angle_geod_rotZ);
        if(!R_geod.get_Matrix().NearEqual(m_R,threshold))
        {
         isError=true;
         m_errorstring="\nRotation_matrix --test calculation rotations_matrix geodetic fails!!";
         return false;
        }


 return true;
}


const string Rotation_matrix::get_errorstring() const
{
 return m_errorstring;
}

Rotation_matrix::ROT_MATRIX_TYPE Rotation_matrix::get_rotation_matrix_type() const
{
  return m_rot_matrix_type;
}

//ein Vielfaches von einem Winkel reduzieren
double Rotation_matrix::clamp(double& wert, double min, double max)
{
   while(wert < min)
   {
       wert += (max-min);
   }
   while(wert > max)
   {
       wert -= (max-min);
   }
   return wert;
}
