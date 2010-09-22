%module photo

%insert("lisphead") %{
  (in-package :photogrammetrie)
%}

%header %{
#include "wrapper_for_c/photoST.h"
#include "Basics/point.h"
#include "Photo/bpoint.h"
#include "Photo/cam.h"

#include "boreside_alignement/cam_bore.h"
#include "Photo/forward_intersection.h"
#include "transformation/applanix.h"
#include "boreside_alignement/boreside_transformation.h"
%}

%feature("intern_function","1");
%feature("export");

%include "wrapper_for_c/photoST.h";
