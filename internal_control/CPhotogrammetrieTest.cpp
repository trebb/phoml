#include "CPhotogrammetrieTest.h"
#include "..//photo//cam.h"
#include "..//photo//bpoint.h"
#include "..//photo//forward_intersection.h"
#include <vector>

CPhotogrammetrieTest::CPhotogrammetrieTest()
{
}

CPhotogrammetrieTest::~CPhotogrammetrieTest()
{
}

bool CPhotogrammetrieTest::check()
{
	
	//(double pix_row,double pix_col,double pix_size,double OX,  double OY,  double OZ,double rotX,double rotY,double rotZ,double c, double xh,  double yh, double A1,  double A2,  double A3,double B1,  double B2, double C1,double C2, double r0)
	//zeilen,spalten,pixelgr��e,�u�ere orientireung x,y,z,omega,phi,kappa,kamerakonstante(Brennweite),Hauptpunktverschiebung xh, und yh
	Cam cam_left(1040,1392,0.00465,0,0,0,0,0,0,0,0,0,0,0,0,-8.3481198,0.00089,0.00472,-0.00284666,4.33195e-05,0,1.01299e-05,-2.01898e-05,-0.000134369,-4.26305e-05,2.427375);

	
	//zeilen,spalten,pixelgr��e,�u�ere orientireung x,y,z,omega,phi,kappa,kamerakonstante(Brennweite),Hauptpunktverschiebung xh, und yh
	Cam cam_right(1040,1392,0.00465,-1114.242911,-2.313123752,-108.0708656,0,0,0,-0.006391017146,-0.1810263138,0.007287021954,0,0,0,-8.3789952,0.08349,0.00098,-0.00285721,4.69797e-05,0,8.79895e-05,6.01291e-05,3.13052e-05,-8.65479e-05,2.427375);
	
	
	//(Kamera und m und n)
	BPoint P_25_pic7_left(cam_left,272,325);
    BPoint P_25_pic7_right(cam_right,223,300);
	
	
	//Vorwärtsschnitt
    std::vector<BPoint> vBPoint;
    vBPoint.push_back(P_25_pic7_left);
    vBPoint.push_back(P_25_pic7_right);
    	
    Vorwaertsschnitt VWS(vBPoint);
    	
    Point P_25_local = VWS.get_Schnittpunkt();
    
    Point P_25_soll(-1062.3945612937441,1587.5888858836174,-7728.733215755935);
	
    double diff=P_25_soll.Abstand(P_25_local);
    
    if(diff>0.1) return false;
	
	
return true;	
}
