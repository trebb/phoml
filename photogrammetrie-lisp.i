%module photo

%insert("lisphead") %{
(in-package :photogrammetrie)
(cffi:load-foreign-library "bin/libphotogrammetrie.so")
%}

%feature("intern_function","1");
%feature("export");

%include "wrapper_for_c/photoST.h";
