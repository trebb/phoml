
#include "position_system.h"

#include <fstream>
#include <sstream>
#include <vector>

#include "..//basics//fix_values.h"
#include "..//basics//basics_exception.h"
#include "..//basics//straight_line.h"

Position_system::Position_system()
{
	m_search_string_applanix_file="(time in Sec,"; //the last line of the decription of the Applanix file
	m_search_string_messpictures_file="cam;channels;compressed;dataSize;height;picture_no;width;gain"; //first line of the messpictures log file
	m_search_string_temp_laser_beam_file="\"id\";\"messfahrtid\";\"timestamp\";\"latitude\"";
	        //"\"id\";\"messfahrtid\";\"timestamp\";\"latitude\";\"longitude\";\"height\""; //\"roll\";\"pitch\";\"heading\";\"q1\";\"q2\";\"q3\";\"q4\";\"q5\";\"q6\";\"q7\";\"q8\";\"q9\";\"q10\";\"q11\";\"q12\";\"q13\";\"q14\";\"q15\";\"q16\";\"q17\";\"q18\";\"q19\";\"q20\";\"q21\";\"q22\";\"q23\";\"q24\";\"q25\";\"q26\";\"q27\";\"q28\";\"q29\";\"q30\";\"q31\";\"q32\";\"q33\";\"q34\";\"q35\";\"distance\";\"the_geom\";\"the_geom_utm\";\"tp_eben_fehler\";\"kruemmung\";\"v_fahrzeug\";\"abstand\";\"q_links_eingeklappt\";\"q_rechts_eingeklappt\";\"messung_nr\";\"h_wgs\";";

	m_average_diff_time_beetween_two_data_sets=5.0;
}

Position_system::~Position_system()
{
}

std::list<Gps_pos>& Position_system::get_gps_pos_list()
{
return m_gps_pos_L;	
}

bool Position_system::read_from_file(std::string datname)
{
	 std::ifstream SET_TXT;  
	 SET_TXT.open(datname.c_str()); 
	 if(!SET_TXT) {
	      throw EX("file load error",DEBUG_LOCATION,"Position_system::temp_read_laser_beam_structur(std::string& datname) -> could not load "+datname+"-> error");
	      return false;
	 }
	 
	 std::string hilf;
	 int icase=0;
	 int max_line = 50, iline = 0;
	 //search of the beginning string
	  while(getline(SET_TXT,hilf))
	  {
	    size_t find_0_1=0;
	    find_0_1=hilf.find(m_search_string_applanix_file.c_str())+1;  //find ist ein vordefinierter Befehl in der Klasse string!            
	    if(find_0_1){ icase=1; break; }
	    
	    size_t find_0_2=0;
	    find_0_2=hilf.find(m_search_string_messpictures_file.c_str())+1;  //find ist ein vordefinierter Befehl in der Klasse string!            
	    if(find_0_2){ icase=2; break; }
	    
	    size_t find_0_3=0;
        find_0_3=hilf.find(m_search_string_temp_laser_beam_file.c_str())+1;  //find ist ein vordefinierter Befehl in der Klasse string!
        if(find_0_3){ icase=3; break; }

	    ++iline;
	    if(iline>max_line){break;}
	  }
	  
	  SET_TXT.close();
	  SET_TXT.clear();
	  
	  if(icase==1)
	  {
		return read_applanix_file(datname);
	  }
	  if(icase==2)
	  {
		return read_messpictures_log_file(datname);
	  }
      if(icase==3)
      {
       (*this).temp_read_laser_beam_structur(datname);
       return true;
      }
	 
	  
	  
return false;	  
}

double Position_system::get_interpolated_time_o_distance(TIME t,double distance)
{
  return get_interpolated_time_o_distance(m_gps_pos_L,t,distance);
}

double Position_system::get_interpolated_time_o_distance(std::list<Gps_pos>& GP,TIME t,double distance)
{
    std::list<Gps_pos> &L = get_neighbors_o_dist(GP,distance);

        //distance(y) - time(x) diagram
        Gerade G;
        Point PS;

            list<Point> st_L;
            Point temp;

            std::list<Gps_pos>::iterator iL = L.begin();
            while(iL != L.end())
            {
             if(t == Position_system::user_time)
                       temp=Point(iL->get_Time(),iL->get_Distance(),0.0);
             else if(t == Position_system::gps_time)
                       temp=Point(iL->get_Time_GPS(),iL->get_Distance(),0.0);
             else if(t == Position_system::utc_time)
                       temp=Point(iL->get_Time_UTC(),iL->get_Distance(),0.0);
             else
                 throw EX("time error",DEBUG_LOCATION,"Position_system::get_interpolated_time_o_distance(TIME t,double distance) -> get time not def-> error");
             st_L.push_back(temp);
             ++iL;
            }

        //case two points or more
        if(st_L.size()==2)
        {
         G.set_P1_P2(*st_L.begin(),*(++st_L.begin()));
        }
        else
        {
         G.calc_average_straight_line(st_L);
        }

         Gerade Gy0;
                Gy0.set_O_R( Point(0.0,distance,0.0) , Point(1.0,0.0,0.0) );
         PS = G.Schnitt(Gy0);

    return PS.get_X();
}

double Position_system::get_interpolated_time_o_distance(TIME t,double distance,double approx_time)
{
 return get_interpolated_time_o_distance( get_part_of_timeline(t,approx_time) , t , distance );
}

double Position_system::get_interpolated_distance_o_time(TIME t,double time)
{
     std::list<Gps_pos> &L = get_neighbors_o_time(m_gps_pos_L,t,time);

     //distance(y) - time(x) diagram
     Gerade Gd;
     Point PS;

         list<Point> st_L;
         Point temp;

         std::list<Gps_pos>::iterator iL = L.begin();
         while(iL != L.end())
         {
             if(t == Position_system::user_time)
                    temp=Point(iL->get_Time(),iL->get_Distance(),0.0);
             else if(t == Position_system::gps_time)
                    temp=Point(iL->get_Time_GPS(),iL->get_Distance(),0.0);
             else if(t == Position_system::utc_time)
                    temp=Point(iL->get_Time_UTC(),iL->get_Distance(),0.0);
             else
              throw EX("time error",DEBUG_LOCATION,"Position_system::get_interpolated_distance_o_time(TIME t,double time_meinb) -> get time not def-> error");
          st_L.push_back(temp);
          ++iL;
         }

     //case two points or more
     if(st_L.size()==2)
     {
      Gd.set_P1_P2(*st_L.begin(),*(++st_L.begin()));
     }
     else
     {
      Gd.calc_average_straight_line(st_L);
     }

      Gerade Gy0;
             Gy0.set_O_R( Point(time,0.0,0.0) , Point(0.0,1.0,0.0) );
      PS = Gd.Schnitt(Gy0);

 return PS.get_Y();
}

Gps_pos Position_system::get_interpolated_position_o_time(TIME t,double time)
{
    std::list<Gps_pos> &L = get_neighbors_o_time(m_gps_pos_L,t,time);
    double distance = get_interpolated_distance_o_time(t,time);

             list<Point> st_L;
             list<double> st_L_dist;
             Point temp;
             Gerade G;

             std::list<Gps_pos>::iterator iL = L.begin();
             while(iL != L.end())
             {
                 temp = iL->get_position();
                 st_L_dist.push_back(iL->get_Distance());
                 st_L.push_back(temp);
              ++iL;
             }

             //case two points or more
              if(st_L.size()==2)
              {
               G.set_P1_P2(*st_L.begin(),*(++st_L.begin()));
              }
              else
              {
                  throw EX("not implement",DEBUG_LOCATION,"Position_system::get_interpolated_position_o_time(TIME t,double time) -> not implement jet");
                  //G.calc_average_straight_line(st_L);
              }

       //get the direction of the straight line to calculate the new point
       //ask for 2 point and interpolate !end!
       Point P1 = st_L.begin()->Add(G.get_R().MultS(distance - *(st_L_dist.begin())) );
       Point P2 = (++st_L.begin())->Subt(G.get_R().MultS(*(++st_L_dist.begin()) - distance));

       Gps_pos GPO;

       if( P1.Abstand(*st_L.begin()) + P1.Abstand(*(++st_L.begin())) <= st_L.begin()->Abstand(*(++st_L.begin())) )
         GPO.set_position(P1);
       else
         GPO.set_position(P2);

       //fill Gps_pos
       GPO.set_Distance(distance);
       GPO.set_Time(time);

 return GPO;
}


std::list<Gps_pos>& Position_system::get_neighbors_o_time(std::list<Gps_pos>& G,TIME t,double time)
{
    //del old var
    m_temp_gps_pos_L.clear();

    double min_time=0.0,max_time=0.0;

                 if(t == Position_system::user_time)
                 {  min_time = (G.begin()->get_Time());
                    max_time = ((--G.end())->get_Time());
                 }
                 else if(t == Position_system::gps_time)
                 {  min_time = (G.begin()->get_Time_GPS());
                    max_time = ((--G.end())->get_Time_GPS());
                 }
                 else if(t == Position_system::utc_time)
                 {  min_time = (G.begin()->get_Time_UTC());
                    max_time = ((--G.end())->get_Time_UTC());
                 }
                 else
                  throw EX("time error",DEBUG_LOCATION,"Position_system::get_neighbors_o_time(TIME t,double time) -> get time not def-> error");

    //first tests
    if(time < min_time)
      throw EX("time error",DEBUG_LOCATION,"Position_system::get_neighbors_o_time() -> get time is out of the time line -> error");

    if(time > max_time)
      throw EX("time error",DEBUG_LOCATION,"Position_system::get_neighbors_o_time() -> get time is out of the time line -> error");

    bool memv=true,memr=true;

    std::list<Gps_pos>::iterator itv = G.begin();
    std::list<Gps_pos>::reverse_iterator itr = G.rbegin();
    while(itv != G.end())
    {
        //case for the different time
        double itv_time=0.0;
        double itr_time=0.0;
                         if(t == Position_system::user_time)
                         {    itv_time = itv->get_Time();
                              itr_time = itr->get_Time();
                         }
                         else if(t == Position_system::gps_time)
                         {    itv_time = itv->get_Time_GPS();
                              itr_time = itr->get_Time_GPS();
                         }
                         else if(t == Position_system::utc_time)
                         {    itv_time = itv->get_Time_UTC();
                              itr_time = itr->get_Time_UTC();
                         }

     if( (time < itv_time) && memv )
     {//fund the first position
         m_temp_gps_pos_L.push_back(*itv);
         memv=false;
         //cout<<endl<<"itv OK!";
     }
     if( (time >= itr_time) && memr )
     {//fund the first position
              m_temp_gps_pos_L.push_back(*itr);
              memr=false;
              //cout<<endl<<"itr OK!";
     }
     if(!memv && !memr)
     {   //cout<<endl<<"memv: "<<memv<<"  memr: "<<memr;
         //cout<<endl<<"break";
         break;
     }
     //cout<<endl<<itv->get_Time()<<"  "<<time<<"  "<<itr->get_Time();
     ++itv;
     ++itr;
    }

    //search for neighbours
    //todo search for neighbours


    (*this).m_temp_gps_pos_L.sort();

        //test id the time difference plausible
        bool err=false;
        std::list<Gps_pos>::iterator iv = ++m_temp_gps_pos_L.begin();
        std::list<Gps_pos>::iterator ir = m_temp_gps_pos_L.begin();
        while(iv != m_temp_gps_pos_L.end())
        {
         if( fabs(iv->get_Time()     - ir->get_Time())     > m_average_diff_time_beetween_two_data_sets) err=true;
         if( fabs(iv->get_Time_GPS() - ir->get_Time_GPS()) > m_average_diff_time_beetween_two_data_sets) err=true;
         if( fabs(iv->get_Time_UTC() - ir->get_Time_UTC()) > m_average_diff_time_beetween_two_data_sets) err=true;
         //cout<<endl<<"out g_n_o_t v: "<<*iv;
         //cout<<endl<<"out g_n_o_t r: "<<*ir;
         //cout<<endl<<"err: "<<err;
         //cout<<endl<<"diff: "<<iv->get_Time_UTC() - ir->get_Time_UTC();
         ++iv;
         ++ir;
        }
        if(err)
         throw EX("time gab or ambiguously",DEBUG_LOCATION,"Position_system::get_neighbors_o_dist() -> time steps are ambiguously -> error");



return (*this).m_temp_gps_pos_L;
}

std::list<Gps_pos>& Position_system::get_neighbors_o_dist(std::list<Gps_pos>& G,double distance)
{
    //del old var
    m_temp_gps_pos_L.clear();

    //first tests
    if(distance < (G.begin())->get_Distance())
      throw EX("distance error",DEBUG_LOCATION,"Position_system::get_neighbors_o_dist() -> get dist is out of the time line -> error");

    if(distance > (--G.end())->get_Distance())
      throw EX("distance error",DEBUG_LOCATION,"Position_system::get_neighbors_o_dist() -> get dist is out of the time line -> error");

    bool memv=true,memr=true;

    std::list<Gps_pos>::iterator itv = G.begin();
    std::list<Gps_pos>::reverse_iterator itr = G.rbegin();
    while(itv != G.end())
    {
     if( (distance < itv->get_Distance()) && memv )
     {//fund the first position
         m_temp_gps_pos_L.push_back(*itv);
         memv=false;
         //cout<<endl<<"itv OK!";
     }
     if( (distance >= itr->get_Distance()) && memr )
     {//fund the first position
              m_temp_gps_pos_L.push_back(*itr);
              memr=false;
              //cout<<endl<<"itr OK!";
     }
     if(!memv && !memr)
     {   //cout<<endl<<"memv: "<<memv<<"  memr: "<<memr;
         //cout<<endl<<"break";
         break;
     }
     //cout<<endl<<itv->get_Time()<<"  "<<distance<<"  "<<itr->get_Time();
     ++itv;
     ++itr;
    }

    //search for neighbours
    //todo search for neighbours


    (*this).m_temp_gps_pos_L.sort();

    //test id the time difference plausible
    bool err=false;
    std::list<Gps_pos>::iterator iv = ++m_temp_gps_pos_L.begin();
    std::list<Gps_pos>::iterator ir = m_temp_gps_pos_L.begin();
    while(iv != m_temp_gps_pos_L.end())
    {
     if( fabs( iv->get_Time()     - ir->get_Time()    ) > m_average_diff_time_beetween_two_data_sets) err=true;
     if( fabs( iv->get_Time_GPS() - ir->get_Time_GPS()) > m_average_diff_time_beetween_two_data_sets) err=true;
     if( fabs( iv->get_Time_UTC() - ir->get_Time_UTC()) > m_average_diff_time_beetween_two_data_sets) err=true;

     ++iv;
     ++ir;
    }
    if(err)
     throw EX("distance ambiguously",DEBUG_LOCATION,"Position_system::get_neighbors_o_dist() -> distance steps are ambiguously -> error");

return (*this).m_temp_gps_pos_L;
}

bool Position_system::read_applanix_file(std::string& datname)
{
 std::ifstream SET_TXT;  
 SET_TXT.open(datname.c_str()); 
 if(!SET_TXT) { return false; }

 std::string hilf;
 int j=0;

 //Gps_pos Pos;
 double time_appl,
  		distance,
  		easting,northing,ellipsoid_height,
  		latitude,longitude,ellipsoid_height_wgs84,
  		roll,pitch,heading,
  		east_velocity,north_velocity,up_velocity,
  		east_sd,north_sd,height_sd,
  		roll_sd,pitch_sd,heading_sd;

 //search of the beginning string
 while(getline(SET_TXT,hilf))
 {
   size_t find_0_1=0;
   find_0_1=hilf.find(m_search_string_applanix_file.c_str())+1;  //find ist ein vordefinierter Befehl in der Klasse string!            
   if(find_0_1){ break; }
 }

 while(getline(SET_TXT,hilf))
 {                   
	        //if(line>=m_ibegin_txt_pos_applanix)
			if(hilf.length()>0 )
			if(hilf.at(j)!='\r')
			if(hilf.at(j)!='\n')
			if(hilf.at(j)!='#' )
			if(hilf.at(j)!='[' )
			{
			 std::stringstream stream; 
			 stream<<hilf.c_str();
			 hilf.erase();
			 stream>>time_appl>>distance
			       >>easting>>northing>>ellipsoid_height
			       >>latitude>>longitude>>ellipsoid_height_wgs84
			       >>roll>>pitch>>heading
			       >>east_velocity>>north_velocity>>up_velocity
			       >>east_sd>>north_sd>>height_sd
			       >>roll_sd>>pitch_sd>>heading_sd;

			 //todo update for the new data structure POS -> lat,long,h,distance
			 Gps_pos Pos_;
			 (*this).compare_gps_coosystem_degree_to_math_coosystem_pi(
					             Pos_,
								 time_appl,easting,northing,ellipsoid_height,
								 latitude,longitude,
								 roll,pitch,heading,
								 east_sd,north_sd,height_sd,
								 roll_sd,pitch_sd,heading_sd);

			     Pos_.set_Time_GPS(time_appl);
                 Pos_.set_Distance(distance);
                 Pos_.set_Latitude(latitude);
                 Pos_.set_Longitude(longitude);
                 Pos_.set_Orth_Height(ellipsoid_height_wgs84);

			 m_gps_pos_L.push_back(Pos_);
			}
 }
 SET_TXT.close();
 SET_TXT.clear();

 
 return true;
}

bool Position_system::read_messpictures_log_file(std::string& datname)
{
 std::ifstream SET_TXT;  
 SET_TXT.open(datname.c_str()); 
 if(!SET_TXT) { return false; }

 std::string hilf;
 int j=0;

 Gps_pos Pos;
 
 //data structur of the log file
 //cam;channels;compressed;dataSize;height;picture_no;width;gain;shutter;time;timeTrigger;whiteBalance;time_appl;time_appl_utc;distance;easting;northing;ellipsoid_height;latitude;longitude;ellipsoid_height_wgs84;roll;pitch;heading;east_velocity;north_velocity;up_velocity;east_sd;north_sd;height_sd;roll_sd;pitch_sd;heading_sd;filename
 int cam,channels,compressed,dataSize,height,picture_no,width;
 double gain,shutter,
 		time,timeTrigger,
 		whiteBalance,
 		time_appl,time_appl_utc,
 		distance,
 		easting,northing,ellipsoid_height,
 		latitude,longitude,ellipsoid_height_wgs84,
 		roll,pitch,heading,
 		east_velocity,north_velocity,up_velocity,
 		east_sd,north_sd,height_sd,
 		roll_sd,pitch_sd,heading_sd;
 std::string filename;
 
     //####line offset of the input file
 	 //int lineoffset=1;
 	 //int count=0;
 	 //while(count++!=lineoffset)
 	 //	 getline(SET_TXT,hilf);
 	 //####
 	 
 	//search of the beginning string
 	while(getline(SET_TXT,hilf))
 	{
 	   size_t find_0_1=0;
 	   find_0_1=hilf.find(m_search_string_messpictures_file.c_str())+1;  //find ist ein vordefinierter Befehl in der Klasse string!            
 	   if(find_0_1){ break; }
 	}
 
 while(getline(SET_TXT,hilf))
 {                   
	        //if(line>=m_ibegin_txt_pos_applanix)
			if(hilf.length()>0 )
			if(hilf.at(j)!='#' )
			{
									  //####
					 				  //replace ";" to " "
					 				  std::string search(";");
					 				  std::string replace(" ");
					 				
					 				  size_t pos = hilf.find(search);
					 				  while(pos!=std::string::npos)
					 				  {
					 			     	hilf.replace(hilf.find(search),1,replace);	
					 			   	    pos = hilf.find(search,pos+replace.length());
					 				  }
					 				  //#####
					 				  
			 
			 std::stringstream stream; 
			 stream<<hilf.c_str();
			 hilf.erase();
			 stream >>cam>>channels>>compressed>>dataSize
			 		>>height>>picture_no>>width>>gain>>shutter
			 		>>time>>timeTrigger
			 		>>whiteBalance
			 		>>time_appl>>time_appl_utc
			 		>>distance
			 		>>easting>>northing>>ellipsoid_height
			 		>>latitude>>longitude>>ellipsoid_height_wgs84
			 		>>roll>>pitch>>heading
			 		>>east_velocity>>north_velocity>>up_velocity
			 		>>east_sd>>north_sd>>height_sd
			 		>>roll_sd>>pitch_sd>>heading_sd
			 		>>filename;

			 compare_gps_coosystem_degree_to_math_coosystem_pi(
					 Pos,
					 time_appl,easting,northing,ellipsoid_height,
					 latitude,longitude,
					 roll,pitch,heading,
					 east_sd,north_sd,height_sd,
					 roll_sd,pitch_sd,heading_sd);

			 Pos.set_Time_GPS(time_appl);
			 Pos.set_Time_UTC(time_appl_utc);
			 Pos.set_Distance(distance);
			 Pos.set_Latitude(latitude);
			 Pos.set_Longitude(longitude);
			 Pos.set_Orth_Height(ellipsoid_height_wgs84);
			 
			 if( easting && northing && ellipsoid_height )
				 m_gps_pos_L.push_back(Pos);
			}
 }

 SET_TXT.close();
 SET_TXT.clear();

 
 return true;
}

void Position_system::compare_gps_coosystem_degree_to_math_coosystem_pi(Gps_pos& Pos_temp,double time,double E,double N,double H ,double latitude,double longitude,double R,double P,double Hea,double mE,double mN,double mH,double mR,double mP,double mHea)
{
	

	             // set the position
	             Pos_temp.set_Time(time);
				 Pos_temp.set_Easting(E);
				 Pos_temp.set_Northing(N);
				 Pos_temp.set_EllH(H);

				 //set the standard deviation of the Pos_tempition
				 Pos_temp.set_dEasting(mE);
				 Pos_temp.set_dNorthing(mN);
				 Pos_temp.set_dEllH(mH);

									 /*
									 // hack for laserline!!! -R and -P (normal +R and +P)
									 Pos_temp.set_Roll((-R)/180.0*PI);
									 Pos_temp.set_Pitch((-P)/180.0*PI);
									 if(Hea<180.0)
									  Pos_temp.set_Heading((-Hea)/180.0*PI);
									 else
									  Pos_temp.set_Heading((360.0-Hea)/180.0*PI);
									 */


				 //-> went to the applanix class
				 //Pos_temp.set_Roll((R)/180.0*PI);
				 //Pos_temp.set_Pitch((P)/180.0*PI);
				 //Pos_temp.set_Heading((-Hea)/180.0*PI); // Negative sign is OK -> change the axis form down to upwards

				 //change the angle values to the mathematic standart coordinate system
				 //Pos_temp.set_mRoll((mR)/180.0*PI);
				 //Pos_temp.set_mPitch((mP)/180.0*PI);
				 //Pos_temp.set_mHeading((mHea)/180.0*PI);


				 // extern applanix class

				 Applanix appl;
				 appl.calc_approximately_meridian_convergence_degree(E,latitude,Hea);
				 //appl.convert_angles_UTM_to_math_coo_system(R,P,Hea,mR,mP,mHea);
                 appl.compare_gps_coosystem_degree_to_math_coosystem_pi(R,P,Hea,mR,mP,mHea);//,latitude,longitude);

				 Pos_temp.set_Roll(R);
				 Pos_temp.set_Pitch(P);
				 Pos_temp.set_Heading(Hea);

				 Pos_temp.set_dRoll(mR);
				 Pos_temp.set_dPitch(mP);
				 Pos_temp.set_dHeading(mHea);

}

void Position_system::temp_read_laser_beam_structur(std::string datname)
{
    std::ifstream FILE;
    FILE.open(datname.c_str());
    if(!FILE)  throw EX("file load error",DEBUG_LOCATION,"Position_system::temp_read_laser_beam_structur(std::string& datname) -> could not load "+datname+"-> error");



    int j=0;
     std::string hilf;

     while(getline(FILE,hilf))
     {
         bool intern=false;

                if(hilf.length()>0 )
                if(hilf.at(j)!='\r')
                if(hilf.at(j)!='\n')
                if(hilf.at(j)!='#' )
                if(hilf.at(j)!='[' )
                if(hilf.at(j)!='"' )
                if(hilf.at(j)!=' ' )
                if(hilf.length()>1 ) //one character is nothing
                if(hilf.at(j)!='/' && hilf.at(j+1)!='/')
                {
                    intern=true;
                    //####
                                                          //replace ";" to " "
                                                          std::string search(";");
                                                          std::string replace(" ");

                                                          size_t pos = hilf.find(search);
                                                          while(pos!=std::string::npos)
                                                          {
                                                            hilf.replace(hilf.find(search),1,replace);
                                                            pos = hilf.find(search,pos+replace.length());
                                                          }
                                                          //#####
                 //cout<<endl<<hilf;

                 std::stringstream stream;
                              stream<<hilf.c_str();
                              hilf.erase();

                              //"id";"messfahrtid";"timestamp";"latitude";"longitude";"height";"roll";"pitch";"heading";
                              //"q1";"q2";"q3";"q4";"q5";"q6";"q7";"q8";"q9";"q10";"q11";"q12";"q13";"q14";"q15";"q16";"q17";"q18";"q19";"q20";"q21";"q22";"q23";"q24";"q25";"q26";"q27";"q28";"q29";"q30";"q31";"q32";"q33";"q34";"q35";
                              //"distance";
                              //"the_geom";"the_geom_utm";"tp_eben_fehler";"kruemmung";"v_fahrzeug";"abstand";"q_links_eingeklappt";"q_rechts_eingeklappt";
                              //"messung_nr";"h_wgs"
                              std::vector<double> temp(56);
                              int i=1;
                              while(i!=55)
                              {
                               stream >> temp.at(i);
                               //cout<<endl<<stream;
                               ++i;
                              }

                              double sum=0;
                              for(int i=10;i<45;++i)
                              {
                                  sum+=temp[i];
                              }

                              if(sum)
                              {
                                  /*
                                  m_profile.lup_id = temp.at(1);
                                  m_profile.lup_messfahrt = temp.at(2);
                                  m_profile.time_meinberg_ttl = temp.at(3);
                                  m_profile.pos_save_frame.set_Latitude( temp.at(4) );
                                  m_profile.pos_save_frame.set_Longitude(temp.at(5) );
                                  m_profile.pos_save_frame.set_EllH(     temp.at(6) );
                                  m_profile.pos_save_frame.set_Roll(temp.at(7) );
                                  m_profile.pos_save_frame.set_Pitch(temp.at(8) );
                                  m_profile.pos_save_frame.set_Heading(temp.at(9) );
                                  m_profile.pos_save_frame.set_Distance( temp.at(45) );
                                  m_profile.lup_distance = temp.at(45);
                                  */
                                  Gps_pos Pos_temp;
                                  Pos_temp.set_Time_UTC( temp.at(3) );
                                  Pos_temp.set_Latitude( temp.at(4) );
                                  Pos_temp.set_Longitude( temp.at(5) );
                                  Pos_temp.set_EllH( temp.at(6) );
                                  Pos_temp.set_Roll( temp.at(7) );
                                  Pos_temp.set_Pitch( temp.at(8) );
                                  Pos_temp.set_Heading( temp.at(9) );
                                  Pos_temp.set_Distance( temp.at(45) );

                                  (*this).m_gps_pos_L.push_back(Pos_temp);

                              }
                }
     }


}

std::list<Gps_pos>& Position_system::get_part_of_timeline(TIME t,double approx_time)
{
     m_temp_gps_pos_L_time_part.clear();
     double min = approx_time - m_average_diff_time_beetween_two_data_sets;
     double max = approx_time + m_average_diff_time_beetween_two_data_sets;

     list<Gps_pos>::iterator iL = m_gps_pos_L.begin();
     while(iL != m_gps_pos_L.end())
     {
         if(t == Position_system::user_time)
                   if(min < iL->get_Time() && iL->get_Time() < max)
                    m_temp_gps_pos_L_time_part.push_back(*iL);
         if(t == Position_system::gps_time)
                   if(min < iL->get_Time_GPS() && iL->get_Time_GPS() < max)
                    m_temp_gps_pos_L_time_part.push_back(*iL);
         if(t == Position_system::utc_time)
                   if(min < iL->get_Time_UTC() && iL->get_Time_UTC() < max)
                    m_temp_gps_pos_L_time_part.push_back(*iL);
      ++iL;
     }

     if(!m_temp_gps_pos_L_time_part.size())
         throw EX("approx time error",DEBUG_LOCATION,"Position_system::get_part_of_timeline(double approx_time) -> approximate time not found-> error");

 return m_temp_gps_pos_L_time_part;
}
