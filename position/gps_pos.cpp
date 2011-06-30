#include "gps_pos.h"

#include <iomanip>

#define PI  3.1415926535897932384626433832795


Gps_pos::Gps_pos()
{
	 m_dtime=m_dtime_gps=m_dtime_utc
	=m_dEasting=m_dNorthing=m_dEll_Height
	=m_dmEasting=m_dmNorthing=m_dmEll_Height
	=m_dRoll=m_dPitch=m_dHeading
	=m_dmRoll=m_dmPitch=m_dmHeading
	=m_ddistance
	=m_dLatitude=m_dLongitude=m_dOrth_Height
	=0.0;

}

Gps_pos::Gps_pos(Gps_pos const &t)
{
 (*this)=t;
}

Gps_pos::~Gps_pos()
{
}

Gps_pos& Gps_pos::operator= (const Gps_pos &t)
{
	     m_dtime = t.m_dtime;//.get_Time() ;
	     m_dtime_gps = t.m_dtime_gps;//get_Time_GPS() ;
		 m_dtime_utc = t.m_dtime_utc;//get_Time_UTC() ;
		 m_dEasting = t.m_dEasting;//get_Easting() ;
		 m_dNorthing = t.m_dNorthing;//get_Northing() ;
		 m_dEll_Height = t.m_dEll_Height;//get_EllH() ;
		 m_dmEasting = t.m_dmEasting;//get_mEasting() ;
		 m_dmNorthing = t.m_dmNorthing;//get_mNorthing() ;
		 m_dmEll_Height = t.m_dmEll_Height;//get_mEllH() ;
		 m_dRoll = t.m_dRoll;//get_Roll() ;
		 m_dPitch = t.m_dPitch;//get_Pitch() ;
		 m_dHeading = t.m_dHeading;//get_Heading() ;
		 m_dmRoll = t.m_dmRoll;//get_mRoll() ;
		 m_dmPitch = t.m_dmPitch;//get_mPitch() ;
		 m_dmHeading = t.m_dmHeading;//get_mHeading();
		 m_ddistance = t.m_ddistance;//get_Distance();
	 	 m_dLatitude = t.m_dLatitude;//get_Latitude();
	 	 m_dLongitude = t.m_dLongitude;//get_Longitude();
	 	 m_dOrth_Height = t.m_dOrth_Height;//get_Orth_Height();

 return (*this);
}


bool Gps_pos::operator==( const Gps_pos& t) const
{ 
	return 	 m_dtime == t.get_Time() &&
	 m_dtime_gps == t.get_Time_GPS() &&
	 m_dtime_utc == t.get_Time_UTC() &&
	 m_dEasting == t.get_Easting() &&
	 m_dNorthing == t.get_Northing() &&
	 m_dEll_Height == t.get_EllH() &&
	 m_dmEasting == t.get_dEasting() &&
	 m_dmNorthing == t.get_dNorthing() &&
	 m_dmEll_Height == t.get_dEllH() &&
	 m_dRoll == t.get_Roll() &&
	 m_dPitch == t.get_Pitch() &&
	 m_dHeading == t.get_Heading() &&
	 m_dmRoll == t.get_dRoll() &&
	 m_dmPitch == t.get_dPitch() &&
	 m_dmHeading == t.get_dHeading() &&
	 m_ddistance == t.get_Distance() &&
	 m_dLatitude == t.get_Latitude() &&
	 m_dLongitude == t.get_Longitude() &&
	 m_dOrth_Height == t.get_Orth_Height();
}

bool Gps_pos::operator!=( const Gps_pos& t) const 
{ 
	return !operator==(t);
}

bool Gps_pos::operator<( const Gps_pos& t) const
{//time sync
 return (*this).m_dtime < t.m_dtime;
}


double Gps_pos::get_Time() const {return m_dtime;}
double Gps_pos::get_Time_GPS() const {return m_dtime_gps;}
double Gps_pos::get_Time_UTC() const {return m_dtime_utc;}

double Gps_pos::get_Easting() const {return m_dEasting;}
double Gps_pos::get_Northing() const {return m_dNorthing;}
double Gps_pos::get_EllH() const {return m_dEll_Height;}

double Gps_pos::get_dEasting() const {return m_dmEasting;}
double Gps_pos::get_dNorthing() const {return m_dmNorthing;}
double Gps_pos::get_dEllH() const {return m_dmEll_Height;}

double Gps_pos::get_Roll() const {return m_dRoll;}
double Gps_pos::get_Pitch() const {return m_dPitch;}
double Gps_pos::get_Heading() const {return m_dHeading;}

double Gps_pos::get_dRoll() const {return m_dmRoll;}
double Gps_pos::get_dPitch() const {return m_dmPitch;}
double Gps_pos::get_dHeading() const {return m_dmHeading;}

double Gps_pos::get_Distance() const {return m_ddistance;}
		
double Gps_pos::get_Latitude() const {return m_dLatitude;}
double Gps_pos::get_Longitude() const {return m_dLongitude;}
double Gps_pos::get_Orth_Height() const {return m_dOrth_Height;}


void Gps_pos::set_Time(double T){m_dtime=T;}
void Gps_pos::set_Time_GPS(double T){m_dtime_gps=T;}
void Gps_pos::set_Time_UTC(double T){m_dtime_utc=T;}


void Gps_pos::set_Easting(double E){m_dEasting=E;}
void Gps_pos::set_Northing(double N){m_dNorthing=N;}
void Gps_pos::set_EllH(double H){m_dEll_Height=H;}

void Gps_pos::set_dEasting(double mE){m_dmEasting=mE;}
void Gps_pos::set_dNorthing(double mN){m_dmNorthing=mN;}
void Gps_pos::set_dEllH(double mH){m_dmEll_Height=mH;}

void Gps_pos::set_Roll(double R){m_dRoll=R;}
void Gps_pos::set_Pitch(double P){m_dPitch=P;}
void Gps_pos::set_Heading(double Hea){m_dHeading=Hea;}

void Gps_pos::set_dRoll(double mR){m_dmRoll=mR;}
void Gps_pos::set_dPitch(double mP){m_dmPitch=mP;}
void Gps_pos::set_dHeading(double mHea){m_dmHeading=mHea;}

void Gps_pos::set_Distance(double D){m_ddistance=D;}
			
void Gps_pos::set_Latitude(double La){m_dLatitude=La;}
void Gps_pos::set_Longitude(double Lo){m_dLongitude=Lo;}
void Gps_pos::set_Orth_Height(double oH){m_dOrth_Height=oH;}

Point Gps_pos::get_position()const{return Point(m_dEasting,m_dNorthing,m_dEll_Height,m_dmEasting,m_dmNorthing,m_dmEll_Height);}
void  Gps_pos::set_position(Point P){m_dEasting=P.get_X();m_dNorthing=P.get_Y();m_dEll_Height=P.get_Z();m_dmEasting=P.get_dX();m_dmNorthing=P.get_dY();m_dmEll_Height=P.get_dZ();}

Point Gps_pos::get_rotation()const{return Point(m_dRoll,m_dPitch,m_dHeading,m_dmRoll,m_dmPitch,m_dmHeading);}
void  Gps_pos::set_rotation(Point P){m_dRoll=P.get_X();m_dPitch=P.get_Y();m_dHeading=P.get_Z();m_dmRoll=P.get_dX();m_dmPitch=P.get_dY();m_dmHeading=P.get_dZ();}


void Gps_pos::convert_rotation_angles_grad_to_rad()
{
    //## convert angle [roll pitch heading] from degree to radiant ##
    Point rot = (*this).get_rotation();

    rot = rot.DivS(180.0).MultS(PI);
    rot.set_dXYZ( rot.get_dXYZ().DivS(180.0).MultS(PI) );

    (*this).set_rotation(rot);
    //## end convert angle from degree to radiant ##
}

void Gps_pos::convert_rotation_angles_rad_to_grad()
{
    Point rot = (*this).get_rotation();

    rot = rot.DivS(PI).MultS(180.0);
    rot.set_dXYZ( rot.get_dXYZ().DivS(PI).MultS(180.0) );

    (*this).set_rotation(rot);
}


std::ostream& operator<<(std::ostream& s,const Gps_pos& A)
{
   int precision=5;       //Nachkommastellen
   int vorkommastellen=8; //Minus zhlt als Vorkommastelle

   s.setf(std::ios::fixed|std::ios::showpoint, std::ios::floatfield);//<<showpoint<<fixed
   s.setf(std::ios::right, std::ios::adjustfield);
   s.precision(precision);

   s<<" (E,N,H)("
	<<std::setfill(' ')<<std::setw(precision+vorkommastellen+1)
	<<A.get_Easting()
	<<","
	<<std::setfill(' ')<<std::setw(precision+vorkommastellen+1)
	<<A.get_Northing()
	<<","
	<<std::setfill(' ')<<std::setw(precision+vorkommastellen+1)
	<<A.get_EllH()
	<<") "

	<<" std("
	<<std::setfill(' ')<<std::setw(precision+1)
	<<A.get_dEasting()
	<<","
	<<std::setfill(' ')<<std::setw(precision+1)
	<<A.get_dNorthing()
	<<","
	<<std::setfill(' ')<<std::setw(precision+1)
	<<A.get_dEllH()
	<<") "

	<<" rot("
	<<std::setfill(' ')<<std::setw(precision+vorkommastellen+1)
	<<A.get_Roll()//PI*180.0
	<<","
	<<std::setfill(' ')<<std::setw(precision+vorkommastellen+1)
	<<A.get_Pitch()//PI*180.0
	<<","
	<<std::setfill(' ')<<std::setw(precision+vorkommastellen+1)
	<<A.get_Heading()//PI*180.0
	<<") "

    <<" rot_std("
    <<std::setfill(' ')<<std::setw(precision+1)
   	<<A.get_dRoll()//PI*180.0
   	<<","
   	<<std::setfill(' ')<<std::setw(precision+1)
   	<<A.get_dPitch()//PI*180.0
   	<<","
   	<<std::setfill(' ')<<std::setw(precision+1)
   	<<A.get_dHeading()//PI*180.0
   	<<") "

   	<<" lat_lo("
   	<<std::setfill(' ')<<std::setw(precision+vorkommastellen+1)
   	<<A.get_Latitude()
	<<"°,"
	<<std::setfill(' ')<<std::setw(precision+vorkommastellen+1)
	<<A.get_Longitude()
	<<"°) "

	<<" dist("
	<<std::setfill(' ')<<std::setw(precision+vorkommastellen+1)
	<<A.get_Distance()
	<<") "

	<<" t_user("
	<<std::setfill(' ')<<std::setw(precision+vorkommastellen+1)
	<<A.get_Time()
	<<") "

	<<" t_GPS("
	<<std::setfill(' ')<<std::setw(precision+vorkommastellen+1)
	<<A.get_Time_GPS()
	<<") "

	<<" t_UTC("
	<<std::setfill(' ')<<std::setw(precision+vorkommastellen+1)
	<<A.get_Time_UTC()
	<<") "
   	;

return s;
};


