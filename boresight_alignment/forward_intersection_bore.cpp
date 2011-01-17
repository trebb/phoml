/*
 * forward_intersection_bore.cpp
 *
 *  Created on: 19.11.2010
 *      Author: steffen
 */

#include "forward_intersection_bore.h"

Forward_intersection_bore::Forward_intersection_bore(std::vector<BPoint_bore> &bpl):m_bpoint_bore_list_intern(&bpl)
{
}

Forward_intersection_bore::~Forward_intersection_bore()
{
}

void Forward_intersection_bore::calc()
{
    //implementation the old function "Vorwaertsschnitt"
    m_intersection_point.set_PktNr( m_bpoint_bore_list_intern->begin()->m_nr );

    std::vector<BPoint> m_bpoint_list_intern;

    //copy to the old data structure
    m_bpoint_list_intern.insert( m_bpoint_list_intern.begin() , m_bpoint_bore_list_intern->begin() , m_bpoint_bore_list_intern->end() );

    Vorwaertsschnitt m_vws(m_bpoint_list_intern);
    m_intersection_point = m_vws.get_Schnittpunkt();

    //look for standard deviations
    Point_nr std_pos;//,std_rot;

    std::vector<BPoint_bore>::iterator i_bbli = m_bpoint_bore_list_intern->begin();
    while( i_bbli != m_bpoint_bore_list_intern->end() )
    {
        std_pos = std_pos.Add( i_bbli->m_cam_bore_calc.get_O().get_dXYZ() );
       //std_rot.Add( i_bbli->m_cam_bore_calc.get_rot().get_dXYZ() );
        ++i_bbli;
    }
    m_intersection_point.set_dXYZ( m_intersection_point.get_dXYZ().Add( std_pos.DivS( m_bpoint_bore_list_intern->size() ) )  );

    //set the intersection point into the bpoint class
    i_bbli = m_bpoint_bore_list_intern->begin();
    while( i_bbli != m_bpoint_bore_list_intern->end() )
    {
        if(i_bbli->m_coordinate_calculation_option == BPoint_bore::local)
           i_bbli->m_local_measurement_point  = m_intersection_point;
        if(i_bbli->m_coordinate_calculation_option == BPoint_bore::car)
           i_bbli->m_car_measurement_point    = m_intersection_point;
        if(i_bbli->m_coordinate_calculation_option == BPoint_bore::global)
           i_bbli->m_global_measurement_point = m_intersection_point;

        ++i_bbli;
    }
}
