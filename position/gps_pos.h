#ifndef GPS_POS_H_
#define GPS_POS_H_

#include <iostream>

//intern lib photogrammetrie
#include "..//basics//point.h"

class Gps_pos
{
public:
	Gps_pos();
	Gps_pos(Gps_pos const &t);
	virtual ~Gps_pos();
	
	Gps_pos& operator= (const Gps_pos &t);

	bool operator==( const Gps_pos& t) const ;
	bool operator!=( const Gps_pos& t) const ;
	
	bool operator<( const Gps_pos& t) const ;

	double get_Time() const;
	double get_Time_GPS() const;
	double get_Time_UTC() const;

	double get_Easting() const;
	double get_Northing() const;
	double get_EllH() const;

	double get_dEasting() const;
	double get_dNorthing() const;
	double get_dEllH() const;

	double get_Roll() const;
	double get_Pitch() const;
	double get_Heading() const;

	double get_dRoll() const;
	double get_dPitch() const;
	double get_dHeading() const;

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

	void set_dEasting(double mE);
	void set_dNorthing(double mN);
	void set_dEllH(double mH);

	void set_Roll(double R);
	void set_Pitch(double P);
	void set_Heading(double Hea);

	void set_dRoll(double mR);
	void set_dPitch(double mP);
	void set_dHeading(double mHea);

	void set_Distance(double D);
			
	void set_Latitude(double La);
	void set_Longitude(double Lo);
	void set_Orth_Height(double oH);

	
	//structure elements
    Point get_position() const;
    void  set_position(Point P);

    Point get_rotation() const;
    void  set_rotation(Point P);

    void convert_rotation_angles_grad_to_rad();
    void convert_rotation_angles_rad_to_grad();

	
protected:

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
