#ifndef POSITION_SYSTEM_H_
#define POSITION_SYSTEM_H_

#include <iostream>
#include <string>
#include <list>

//own projekt link
#include "gps_pos.h"
#include "..//transformation//applanix.h"

class Position_system
{
public:
	Position_system();
	virtual ~Position_system();
	
	std::list<Gps_pos>& get_gps_pos_list();
	
	bool read_from_file(std::string datname);

	//interpolations functions
	enum TIME{user_time,gps_time,utc_time}; //user time is a temporary calculation time
                                            //gps_time is raw time from a position system
                                            //utc time is a calculated time of gps_time
	//for unique distance sequence
	double  get_interpolated_time_o_distance(TIME t,double distance);
	double  get_interpolated_time_o_distance(TIME t,double distance,double approx_time);

	double  get_interpolated_distance_o_time(TIME t,double time);
	Gps_pos get_interpolated_position_o_time(TIME t,double time);


	std::list<Gps_pos>& get_neighbors_o_time(std::list<Gps_pos>& G,TIME t,double time);
	std::list<Gps_pos>& get_neighbors_o_dist(std::list<Gps_pos>& G,double distance);
private:

	double  get_interpolated_time_o_distance(std::list<Gps_pos>& G,TIME t,double distance);


	void temp_read_laser_beam_structur(std::string datname);
	std::list<Gps_pos>& get_part_of_timeline(TIME t,double approx_time);

	std::list<Gps_pos> m_gps_pos_L;

	//temp list for the interpolation functions
	std::list<Gps_pos> m_temp_gps_pos_L;
	std::list<Gps_pos> m_temp_gps_pos_L_time_part;


	std::string m_search_string_applanix_file;
	std::string m_search_string_messpictures_file;
	std::string m_search_string_temp_laser_beam_file;

	bool read_applanix_file(std::string& datname);
	bool read_messpictures_log_file(std::string& datname);
	void compare_gps_coosystem_degree_to_math_coosystem_pi(Gps_pos &Pos_temp,double time,double E,double N,double H ,double latitude,double longitude,double R,double P,double Hea,double mE,double mN,double mH,double mR,double mP,double mHea);

	//Gps_pos m_Pos_temp;

	double m_average_diff_time_beetween_two_data_sets;
};

#endif /*POSITIONING_SYSTEM_H_*/
