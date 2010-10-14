#ifndef GPS_POS_H_
#define GPS_POS_H_

#include <iostream>

//intern lib photogrammetrie
#include "..//Basics//point.h"

class Gps_pos
{
public:
	Gps_pos();

	virtual ~Gps_pos();
	
	bool operator==( const Gps_pos& t) const ;
	bool operator!=( const Gps_pos& t) const ;

	Gps_pos& operator= (const Gps_pos &t);
	Gps_pos(Gps_pos const &t);

	
	double get_Time() const;
	double get_Time_GPS() const;
	double get_Time_UTC() const;

	double get_Easting() const;
	double get_Northing() const;
	double get_EllH() const;

	double get_mEasting() const;
	double get_mNorthing() const;
	double get_mEllH() const;

	double get_Roll() const;
	double get_Pitch() const;
	double get_Heading() const;

	double get_mRoll() const;
	double get_mPitch() const;
	double get_mHeading() const;

	double get_Distance() const;
			
	double get_Latitude() const;
	double get_Longitude() const;
	double get_Orth_Height() const;

	
	void set_Time(double T);
	void set_Time_GPS(double T);
	void set_Time_UTC(double T);

	void set_Easting(double E);
	void set_Northing(double N);
	void set_EllH(double H);

	void set_mEasting(double mE);
	void set_mNorthing(double mN);
	void set_mEllH(double mH);

	void set_Roll(double R);
	void set_Pitch(double P);
	void set_Heading(double Hea);

	void set_mRoll(double mR);
	void set_mPitch(double mP);
	void set_mHeading(double mHea);

	void set_Distance(double D);
			
	void set_Latitude(double La);
	void set_Longitude(double Lo);
	void set_Orth_Height(double oH);

	
	//structure elements
    Point get_position_geod();
    void  set_position_geod(Point P);

    Point get_rotation();
    void  set_rotation(Point P);

	
private:

		//local time (user) [sek]
		double m_dtime;
		//GPS time [sek] (reseted weekly)
		double m_dtime_gps;
		//UTC time in seconds since 1970 [sek]
		double m_dtime_utc;

		//position WGS84 UTM Coordinates [m]
		double m_dEasting;
		double m_dNorthing;
		double m_dEll_Height;

		//standard deviation [m]
		double m_dmEasting;
		double m_dmNorthing;
		double m_dmEll_Height;

		//rotation of the plattform in [rad]
		double m_dRoll;
		double m_dPitch;
		double m_dHeading;

	    //standart deviation [rad]
		double m_dmRoll;		
		double m_dmPitch;
		double m_dmHeading;
		
		//add aditional params for laserline calc
		//distance from the pos system
		double m_ddistance;
		
		//position WGS84 UTM Coordinates [m]
		double m_dLatitude;
		double m_dLongitude;
		double m_dOrth_Height;

		
		
		

};

std::ostream& operator<<(std::ostream& s,const Gps_pos& A);

#endif /*GPS_POS_H_*/
