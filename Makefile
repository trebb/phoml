RM := rm -rf
JAVA_HOME = /usr/lib/jvm/java-6-sun-1.6.0.20/
SWIG   = photogrammetrie_wrap.cxx
LIB_SO = bin/libphotogrammetrie.so
JAR    = bin/photogrammetrie.jar

JAVA_DIR = java
BIN_DIR = bin

Basics = Basics/ebene.cpp Basics/point.cpp Basics/rot_matrix.cpp Basics/straight_line.cpp
Matrix = Basics/Matrix/matrix.cpp
Photo  = Photo/bpoint.cpp Photo/cam.cpp Photo/forward_intersection.cpp
Boreside = boreside_alignement/cam_bore.cpp boreside_alignement/boreside_transformation.cpp
Wrapper = wrapper_for_java/CBPointList.cpp wrapper_for_java/Vorwaertsschnitt_java.cpp wrapper_for_java/mainwrapperjava.cpp internal_control/CPhotogrammetrieTest.cpp transformation/applanix.cpp transformation/rot_matrix_appl.cpp 
CXX_SOURCES = $(Basics) $(Matrix) $(Photo) $(Boreside) $(Wrapper)
SWIG_SOURCE = photogrammetrie.i


all: $(JAR)

clean:
	-$(RM) $(BIN_DIR) $(JAVA_DIR) $(SWIG) 

.PHONY: all clean

$(JAR): $(LIB_SO)
	javac -encoding UTF-8 $(JAVA_DIR)/*.java
	jar cf $@ -C $(JAVA_DIR) ./

$(LIB_SO): $(SWIG)
	mkdir -p $(BIN_DIR)
	g++ -fpic -shared -I$(JAVA_HOME)/include  -I$(JAVA_HOME)/include/linux -o $@ $(CXX_SOURCES)

$(SWIG): $(SWIG_SOURCE) $(CXX_SOURCES)
	mkdir -p $(JAVA_DIR)
	swig -c++ -java -package photogrammetrie -outdir $(JAVA_DIR) $(SWIG_SOURCE)
