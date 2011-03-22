// -*- Lisp -*-

%module phoml

%feature("intern_function","1");
%feature("export");

%include "wrapper_for_c/photoST.h";

%insert("lisphead") %{

(in-package :phoml)
;;(pushnew (make-pathname :directory '(:relative :up "phoml" "lib"))
;;         cffi:*foreign-library-directories*)
;;(cffi:load-foreign-library '(:default "libphoml"))

%}
