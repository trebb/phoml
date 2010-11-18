/*
 * internal_test_photogrammetrie_for_cpp.h
 *
 *  Created on: 14.10.2010
 *      Author: steffen
 */

#ifndef INTERNAL_TEST_PHOTOGRAMMETRIE_FOR_CPP_H_
#define INTERNAL_TEST_PHOTOGRAMMETRIE_FOR_CPP_H_

#include "iostream"
#include "sstream"

class Internal_test_photogrammetrie_for_cpp
{
public:
    Internal_test_photogrammetrie_for_cpp();
    virtual ~Internal_test_photogrammetrie_for_cpp();

    bool testing(){return m_error;}; // 0 -> error and 1 -> all OK
    const std::string get_error_messages(){return m_cout.str();};

private:
    bool test_matrix();
    bool test_point();
    bool test_rotations_matrix();
    bool test_global_photogrammetrie();
    //bool test_forward_intersection();
    //bool test_coordconvertion_applanix();
    //bool test_boreside_transformation();

    bool m_error;
    std::stringstream m_cout;

    double m_approach_difference;
};

#endif /* INTERNAL_TEST_PHOTOGRAMMETRIE_FOR_CPP_H_ */
