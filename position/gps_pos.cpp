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

Gps_pos::~Gps_pos()
{
}


bool Gps_pos::operator==( const Gps_pos& t) const
{ 
	return 	 m_dtime == t.get_Time() &&
	 m_dtime_gps == t.get_Time_GPS() &&
	 m_dtime_utc == t.get_Time_UTC() &&
	 m_dEasting == t.get_Easting() &&
	 m_dNorthing == t.get_Northing() &&
	 m_dEll_Height == t.get_EllH() &&
	 m_dmEasting == t.get_mEasting() &&
	 m_dmNorthing == t.get_mNorthing() &&
	 m_dmEll_Height == t.get_mEllH() &&
	 m_dRoll == t.get_Roll() &&
	 m_dPitch == t.get_Pitch() &&
	 m_dHeading == t.get_Heading() &&
	 m_dmRoll == t.get_mRoll() &&
	 m_dmPitch == t.get_mPitch() &&
	 m_dmHeading == t.get_mHeading() &&
	 m_ddistance == t.get_Distance() &&
	 m_dLatitude == t.get_Latitude() &&
	 m_dLongitude == t.get_Longitude() &&
	 m_dOrth_Height == t.get_Orth_Height();
}

bool Gps_pos::operator!=( const Gps_pos& t) const 
{ 
	return !operator==(t);
}


Gps_pos& Gps_pos::operator= (const Gps_pos &t)
{
	     m_dtime = t.get_Time() ;
	     m_dtime_gps = t.get_Time_GPS() ;
		 m_dtime_utc = t.get_Time_UTC() ;
		 m_dEasting = t.get_Easting() ;
		 m_dNorthing = t.get_Northing() ;
		 m_dEll_Height = t.get_EllH() ;
		 m_dmEasting = t.get_mEasting() ;
		 m_dmNorthing = t.get_mNorthing() ;
		 m_dmEll_Height = t.get_mEllH() ;
		 m_dRoll = t.get_Roll() ;
		 m_dPitch = t.get_Pitch() ;
		 m_dHeading = t.get_Heading() ;
		 m_dmRoll = t.get_mRoll() ;
		 m_dmPitch = t.get_mPitch() ;
		 m_dmHeading = t.get_mHeading();
		 m_ddistance = t.get_Distance();
	 	 m_dLatitude = t.get_Latitude();
	 	 m_dLongitude = t.get_Longitude();
	 	 m_dOrth_Height = t.get_Orth_Height();
	 
 return (*this);
}

Gps_pos::Gps_pos(Gps_pos const &t)
{
 (*this)=t;
}


double Gps_pos::get_Time() const {return m_dtime;}
double Gps_pos::get_Time_GPS() const {return m_dtime_gps;}
double Gps_pos::get_Time_UTC() const {return m_dtime_utc;}

double Gps_pos::get_Easting() const {return m_dEasting;}
double Gps_pos::get_Northing() const {return m_dNorthing;}
double Gps_pos::get_EllH() const {return m_dEll_Height;}

double Gps_pos::get_mEasting() const {return m_dmEasting;}
double Gps_pos::get_mNorthing() const {return m_dmNorthing;}
double Gps_pos::get_mEllH() const {return m_dmEll_Height;}

double Gps_pos::get_Roll() const {return m_dRoll;}
double Gps_pos::get_Pitch() const {return m_dPitch;}
double Gps_pos::get_Heading() const {return m_dHeading;}

double Gps_pos::get_mRoll() const {return m_dmRoll;}
double Gps_pos::get_mPitch() const {return m_dmPitch;}
double Gps_pos::get_mHeading() const {return m_dmHeading;}

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

void Gps_pos::set_mEasting(double mE){m_dmEasting=mE;}
void Gps_pos::set_mNorthing(double mN){m_dmNorthing=mN;}
void Gps_pos::set_mEllH(double mH){m_dmEll_Height=mH;}

void Gps_pos::set_Roll(double R){m_dRoll=R;}
void Gps_pos::set_Pitch(double P){m_dPitch=P;}
void Gps_pos::set_Heading(double Hea){m_dHeading=Hea;}

void Gps_pos::set_mRoll(double mR){m_dmRoll=mR;}
void Gps_pos::set_mPitch(double mP){m_dmPitch=mP;}
void Gps_pos::set_mHeading(double mHea){m_dmHeading=mHea;}

void Gps_pos::set_Distance(double D){m_ddistance=D;}
			
void Gps_pos::set_Latitude(double La){m_dLatitude=La;}
void Gps_pos::set_Longitude(double Lo){m_dLongitude=Lo;}
void Gps_pos::set_Orth_Height(double oH){m_dOrth_Height=oH;}

Point Gps_pos::get_position_geod(){return Point(m_dEasting,m_dNorthing,m_dEll_Height,m_dmEasting,m_dmNorthing,m_dmEll_Height);}
void  Gps_pos::set_position_geod(Point P){m_dEasting=P.get_X();m_dNorthing=P.get_Y();m_dEll_Height=P.get_Z();m_dmEasting=P.get_dX();m_dmNorthing=P.get_dY();m_dmEll_Height=P.get_dZ();}

Point Gps_pos::get_rotation(){return Point(m_dRoll,m_dPitch,m_dHeading,m_dmRoll,m_dmPitch,m_dmHeading);}
void  Gps_pos::set_rotation(Point P){m_dRoll=P.get_X();m_dPitch=P.get_Y();m_dHeading=P.get_Z();m_dmRoll=P.get_dX();m_dmPitch=P.get_dY();m_dmHeading=P.get_dZ();}


std::ostream& operator<<(std::ostream& s,const Gps_pos& A)
{
   int precision=5;       //Nachkommastellen
   int vorkommastellen=8; //Minus zhlt als Vorkommastelle

   s.setf(std::ios::fixed|std::ios::showpoint, std::ios::floatfield);//<<showpoint<<fixed
   s.setf(std::ios::right, std::ios::adjustfield);
   s.precision(precision);

   s<<" ("
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
	<<A.get_mEasting()
	<<","
	<<std::setfill(' ')<<std::setw(precision+1)
	<<A.get_mNorthing()
	<<","
	<<std::setfill(' ')<<std::setw(precision+1)
	<<A.get_mEllH()
	<<") "

	<<" rot("
	<<std::setfill(' ')<<std::setw(precision+vorkommastellen+1)
	<<A.get_Roll()//PI*180.0
	<<"°,"
	<<std::setfill(' ')<<std::setw(precision+vorkommastellen+1)
	<<A.get_Pitch()//PI*180.0
	<<"°,"
	<<std::setfill(' ')<<std::setw(precision+vorkommastellen+1)
	<<A.get_Heading()//PI*180.0
	<<"°) "

    <<" rot_std("
    <<std::setfill(' ')<<std::setw(precision+1)
   	<<A.get_mRoll()//PI*180.0
   	<<"°,"
   	<<std::setfill(' ')<<std::setw(precision+1)
   	<<A.get_mPitch()//PI*180.0
   	<<"°,"
   	<<std::setfill(' ')<<std::setw(precision+1)
   	<<A.get_mHeading()//PI*180.0
   	<<"°) "

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
	<<A.get_Time()
	<<") "

	<<" t_UTC("
	<<std::setfill(' ')<<std::setw(precision+vorkommastellen+1)
	<<A.get_Time()
	<<") "
   	;

return s;
};

