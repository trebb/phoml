RM := rm -rf
JAVA_HOME = /usr/lib/jvm/java-6-sun-1.6.0.20/

LIB_SO_JAVA = bin/libphotogrammetrie-java.so
LIB_SO_LISP = bin/libphotogrammetrie-lisp.so
LIB_SO = bin/libphotogrammetrie.so
C_TEST = bin/zugriff_photogrammetrie_c
JAR    = bin/photogrammetrie.jar

JAVA_DIR = java
LISP_DIR = .
BIN_DIR = bin

Basics = Basics/ebene.cpp Basics/point.cpp Basics/rot_matrix.cpp Basics/straight_line.cpp
Matrix = Basics/Matrix/matrix.cpp
Photo  = Photo/bpoint.cpp Photo/cam.cpp Photo/forward_intersection.cpp
Boreside = boreside_alignement/cam_bore.cpp boreside_alignement/boreside_transformation.cpp

WRAPPER_JAVA = wrapper_for_java/CBPointList.cpp wrapper_for_java/Vorwaertsschnitt_java.cpp wrapper_for_java/mainwrapperjava.cpp internal_control/CPhotogrammetrieTest.cpp transformation/applanix.cpp transformation/rot_matrix_appl.cpp
WRAPPER_C = wrapper_for_c/photoST.cpp   transformation/applanix.cpp transformation/rot_matrix_appl.cpp
WRAPPER_LISP = $(WRAPPER_C)

PHOTOGRAMMETRIE_SOURCES = $(Basics) $(Matrix) $(Photo) $(Boreside)
JAVA_SOURCES = $(PHOTOGRAMMETRIE_SOURCES) $(WRAPPER_JAVA)
TEST_SOURCES = wrapper_for_c/example/zugriff_photogrammetrie_c.c

SWIG_JAVA_SOURCE = photogrammetrie-java.i
SWIG_LISP_SOURCE = photogrammetrie-lisp.i

SWIG_JAVA = photogrammetrie_wrap.cxx
SWIG_LISP = photogrammetrie-lisp_wrap.cxx

HEADERS = $(wildcard */*.h)


all: $(LIB_SO_LISP) $(C_TEST)

clean:
	-$(RM) $(BIN_DIR) $(JAVA_DIR) $(LISP_DIR) $(SWIG_JAVA) $(SWIG_LISP) *.fasl photo.lisp photo-clos.lisp

.PHONY: all clean

$(JAR): $(LIB_SO_JAVA)
	javac -encoding UTF-8 $(JAVA_DIR)/*.java
	jar cf $@ -C $(JAVA_DIR) ./

$(LIB_SO_JAVA): $(SWIG_JAVA)
	mkdir -p $(BIN_DIR)
	g++ -fpic -shared -I$(JAVA_HOME)/include  -I$(JAVA_HOME)/include/linux -o $@ $(JAVA_SOURCES)

$(LIB_SO_LISP): $(PHOTOGRAMMETRIE-SOURCES) $(WRAPPER_LISP) $(SWIG_LISP) $(HEADERS)
	mkdir -p $(BIN_DIR)
	g++ -fpic -shared -o $@ $(PHOTOGRAMMETRIE_SOURCES) $(WRAPPER_LISP) $(SWIG_LISP)

$(LIB_SO): $(PHOTOGRAMMETRIE_SOURCES) $(WRAPPER_C) $(HEADERS)
	mkdir -p $(BIN_DIR)
	g++ -fpic -shared -o $@ $(PHOTOGRAMMETRIE_SOURCES) $(WRAPPER_C)

$(SWIG_JAVA): $(SWIG_JAVA_SOURCE) $(JAVA_SOURCES)
	mkdir -p $(JAVA_DIR)
	swig -c++ -java -package photogrammetrie -outdir $(JAVA_DIR) $(SWIG_JAVA_SOURCE)

$(SWIG_LISP): $(SWIG_LISP_SOURCE) $(PHOTOGRAMMETRIE_SOURCES) $(HEADERS)
	mkdir -p $(LISP_DIR)
	swig -c++ -cffi -outdir $(LISP_DIR) $(SWIG_LISP_SOURCE)

$(C_TEST): $(LIB_SO) $(TEST_SOURCES) $(HEADERS)
	mkdir -p $(BIN_DIR)
	gcc -o $@ $(TEST_SOURCES) -L ./ $(LIB_SO)
