JAVA_HOME = /usr/lib/jvm/java-6-sun

VPATH = Basics GPS Matrix Photo

Swig   = photogrammetrie_wrap.cxx
Basics = ebene.cpp point.cpp rot_matrix.cpp straight_line.cpp
//GPS	   = GPS_orient.cpp picture_log.cpp
Matrix = Basics//Matrix//matrix.cpp
Photo  = bpoint.cpp cam.cpp forward_intersection.cpp
Boreside = boreside_alignement/cam_bore.cpp boreside_alignement/boreside_transformation.cpp
Wrapper = wrapper_for_java/CBPointList.cpp wrapper_for_java/Vorwaertsschnitt_java.cpp wrapper_for_java/mainwrapperjava.cpp internal_control/CPhotogrammetrieTest.cpp transformation/applanix.cpp transformation/rot_matrix_appl.cpp 

photogrammetrie:	$(Swig) $(Basics) $(GPS) $(Matrix) $(Photo) $(Boreside) $(Wrapper)
	g++ -fpic -shared -I$(JAVA_HOME)/include  -I$(JAVA_HOME)/include/linux -o bin/libphotogrammetrie.so $^
	
photogrammetrie_win:	$(Swig) $(Basics) $(GPS) $(Matrix) $(Photo) $(Boreside) $(Wrapper)
	g++ -shared -I$(JAVA_HOME)/include  -I$(JAVA_HOME)/include/win32 -o bin/photogrammetrie.dll $^