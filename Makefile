RM := rm -rf
JAVA_HOME = /usr/lib/jvm/java-6-sun-1.6.0.20/
SWIG_JAVA   = photogrammetrie_wrap.cxx
LIB_SO_JAVA = bin/libphotogrammetrie-java.so
LIB_SO_LISP = bin/libphotogrammetrie-lisp.so
LIB_SO = bin/libphotogrammetrie.so
JAR    = bin/photogrammetrie.jar

JAVA_DIR = java
BIN_DIR = bin

Basics = Basics/ebene.cpp Basics/point.cpp Basics/rot_matrix.cpp Basics/straight_line.cpp
Matrix = Basics/Matrix/matrix.cpp
Photo  = Photo/bpoint.cpp Photo/cam.cpp Photo/forward_intersection.cpp
Boreside = boreside_alignement/cam_bore.cpp boreside_alignement/boreside_transformation.cpp
WRAPPER_JAVA = wrapper_for_java/CBPointList.cpp wrapper_for_java/Vorwaertsschnitt_java.cpp wrapper_for_java/mainwrapperjava.cpp internal_control/CPhotogrammetrieTest.cpp transformation/applanix.cpp transformation/rot_matrix_appl.cpp
WRAPPER_LISP = wrapper_for_lisp/photoST.cpp   transformation/applanix.cpp transformation/rot_matrix_appl.cpp
CXX_SOURCES = $(Basics) $(Matrix) $(Photo) $(Boreside) $(WRAPPER_JAVA)
PHOTOGRAMMETRIE_SOURCES = $(Basics) $(Matrix) $(Photo) $(Boreside)
TEST_SOURCES = internal_control/CPhotogrammetrieTest.cpp

LISP_DIR = .
SWIG_SOURCE = photogrammetrie.i
SWIG_LISP_SOURCE = photogrammetrie-lisp.i
SWIG_LISP   = photogrammetrie-lisp_wrap.cxx


all: $(JAR) $(LIB_SO_LISP)

clean:
	-$(RM) $(BIN_DIR) $(JAVA_DIR) $(LISP_DIR) $(SWIG_JAVA) $(SWIG_LISP)

.PHONY: all clean

$(JAR): $(LIB_SO_JAVA)
	javac -encoding UTF-8 $(JAVA_DIR)/*.java
	jar cf $@ -C $(JAVA_DIR) ./

$(LIB_SO_JAVA): $(SWIG_JAVA)
	mkdir -p $(BIN_DIR)
	g++ -fpic -shared -I$(JAVA_HOME)/include  -I$(JAVA_HOME)/include/linux -o $@ $(CXX_SOURCES)

$(LIB_SO_LISP): $(PHOTOGRAMMETRIE-SOURCES) $(SWIG_LISP)
	mkdir -p $(BIN_DIR)
	g++ -fpic -shared -o $@ $(PHOTOGRAMMETRIE_SOURCES) $(WRAPPER_LISP) $(SWIG_LISP)

$(LIB_SO): $(PHOTOGRAMMETRIE_SOURCES) $(SWIG_LISP)
	mkdir -p $(BIN_DIR)
	g++ -fpic -shared -o $@ $(PHOTOGRAMMETRIE_SOURCES)

$(SWIG_JAVA): $(SWIG_SOURCE) $(CXX_SOURCES)
	mkdir -p $(JAVA_DIR)
	swig -c++ -java -package photogrammetrie -outdir $(JAVA_DIR) $(SWIG_SOURCE)

$(SWIG_LISP): $(SWIG_LISP_SOURCE) $(PHOTOGRAMMETRIE_SOURCES)
	mkdir -p $(LISP_DIR)
	swig -c++ -cffi -outdir $(LISP_DIR) $(SWIG_LISP_SOURCE)
