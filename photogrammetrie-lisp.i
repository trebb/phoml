// -*- Lisp -*-

%module photo

%feature("intern_function","1");
%feature("export");

%include "wrapper_for_c/photoST.h";

%insert("lisphead") %{

(in-package :photogrammetrie)
;;(pushnew (make-pathname :directory '(:relative :up "photogrammetrie" "lib"))
;;         cffi:*foreign-library-directories*)
;;(cffi:load-foreign-library '(:default "libphotogrammetrie"))

%}
