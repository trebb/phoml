VPATH = Basics GPS Matrix Photo

Swig   = photogrammetrie_wrap.cxx
Basics = ebene.cpp point.cpp rot_matrix.cpp straight_line.cpp
//GPS	   = GPS_orient.cpp picture_log.cpp
Matrix = Basics//Matrix//matrix.cpp
Photo  = bpoint.cpp cam.cpp forward_intersection.cpp
Wrapper = CBPointList.cpp Vorwaertsschnitt_java.cpp

photogrammetrie:	$(Swig) $(Basics) $(GPS) $(Matrix) $(Photo) $(Wrapper)
	g++ -fpic -shared -I$(JAVA_HOME)/include  -I$(JAVA_HOME)/include/linux -o bin/libphotogrammetrie.so $^