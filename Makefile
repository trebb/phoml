RM := rm -rf
JAVA_HOME = /usr/lib/jvm/java-6-sun-1.6.0.20/

LIB_SO_JAVA = lib/libphotogrammetrie-java.so
LIB_SO = lib/libphoml.so
C_TEST = lib/zugriff_photogrammetrie_c
JAR    = lib/photogrammetrie.jar

JAVA_DIR = java
LIB_DIR = lib

Basics = basics/ebene.cpp basics/point.cpp basics/point_nr.cpp basics/rot_matrix.cpp basics/straight_line.cpp basics/basics_exception.cpp basics/rotation_matrix.cpp
Matrix = basics/matrix/matrix.cpp
Point_nr_system = basics/point_nr_system/point_nr_list.cpp
Boreside = boresight_alignment/boresight_transformation.cpp boresight_alignment/bpoint_bore.cpp boresight_alignment/cam_bore.cpp boresight_alignment/mono_photogrammetrie.cpp boresight_alignment/forward_intersection_bore.cpp
Photo  = photo/bpoint.cpp photo/cam.cpp photo/forward_intersection.cpp
Position = position/gps_pos.cpp
Transformation = transformation/applanix.cpp transformation/rot_matrix_appl.cpp

WRAPPER_JAVA = wrapper_for_java/CBPointList.cpp wrapper_for_java/Vorwaertsschnitt_java.cpp wrapper_for_java/mainwrapperjava.cpp internal_control/CPhotogrammetrieTest.cpp
WRAPPER_C = wrapper_for_c/photoST.cpp

PHOML_SOURCES = $(Basics) $(Matrix) $(Point_nr_system) $(Boreside) $(Photo) $(Position) $(Transformation) 
JAVA_SOURCES = $(PHOML_SOURCES) $(WRAPPER_JAVA)
TEST_SOURCES = wrapper_for_c/example/zugriff_photogrammetrie_c.c

SWIG_JAVA_SOURCE = photogrammetrie-java.i
SWIG_LISP_SOURCE = phoml-lisp.i

SWIG_JAVA = photogrammetrie_wrap.cxx
SWIG_LISP = photo.lisp

HEADERS = $(wildcard */*.h)


all: $(LIB_SO) $(SWIG_LISP)

test: $(C_TEST)

clean:
	-$(RM) $(LIB_DIR) $(JAVA_DIR) $(SWIG_JAVA) $(SWIG_LISP) *.fasl

.PHONY: all clean

$(JAR): $(LIB_SO_JAVA)
	javac -encoding UTF-8 $(JAVA_DIR)/*.java
	jar cf $@ -C $(JAVA_DIR) ./

$(LIB_SO_JAVA): $(SWIG_JAVA)
	mkdir -p $(LIB_DIR)
	g++ -fpic -shared -I$(JAVA_HOME)/include  -I$(JAVA_HOME)/include/linux -o $@ $(JAVA_SOURCES)

$(LIB_SO): $(PHOML_SOURCES) $(WRAPPER_C) $(HEADERS)
	mkdir -p $(LIB_DIR)
	g++ -fpic -shared -o $@ $(PHOML_SOURCES) $(WRAPPER_C)

$(SWIG_JAVA): $(SWIG_JAVA_SOURCE) $(JAVA_SOURCES)
	mkdir -p $(JAVA_DIR)
	swig -c++ -java -package photogrammetrie -outdir $(JAVA_DIR) $(SWIG_JAVA_SOURCE)

$(SWIG_LISP): $(SWIG_LISP_SOURCE) $(PHOML_SOURCES) $(HEADERS)
	swig -cffi -outdir . $(SWIG_LISP_SOURCE)

$(C_TEST): $(LIB_SO) $(TEST_SOURCES) $(HEADERS)
	mkdir -p $(LIB_DIR)
	gcc -o $@ $(TEST_SOURCES) -L ./ $(LIB_SO)
