/*
 * mono_photogrammetrie.h
 *
 *  Created on: 14.10.2010
 *      Author: steffen
 */

#ifndef MONO_PHOTOGRAMMETRIE_H_
#define MONO_PHOTOGRAMMETRIE_H_



class Mono_photogrammetrie
{
public:
    Mono_photogrammetrie();//Ebene &E);
    virtual ~Mono_photogrammetrie();

    //calculate a
//    Point get_local_object_point(BPoint &Bp);

 //   Point get_global_object_point(BPoint &Bp, Gps_car_postion &gps);

  //  std::list<Point> get_foot_print();


private:
  //  CCam_bore *m_cam;
  //  Ebene     *m_E;


  //  std::list<Point> m_foot_print list;
};

#endif /* MONO_PHOTOGRAMMETRIE_H_ */
