#ifndef __FIX_VALUES_h
#define __FIX_VALUES_h

#define VERSIONSNUMBER 0.004

#define PI static_cast<double>(3.1415926535897932384626433832795)
//static const double PI=3.1415926535897932384626433832795;

class Fix_values
{
public:
    enum status_version{s0002,s0003};

    Fix_values(){/*standard*/m_version = Fix_values::s0002;}
    ~Fix_values(){};

    enum status_version get_version() const {return m_version;}
    void                set_version(enum status_version sv){m_version=sv;}

    //for handling internal bug -> to handle old calibrations
    //s0002 with the meridian convergence bug -> depends on the boresight calibration
    //s0003 without the meridian convergence bug
private:
    status_version m_version;
};

//Fix_values Version;

#endif
