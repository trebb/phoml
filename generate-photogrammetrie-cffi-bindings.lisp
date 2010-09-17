(in-package :verrazano)

(defun system-relative-pathname (system path)
  "Return a pathname relative to the given asdf system."
  (pathname (directory-namestring (merge-pathnames path (asdf:component-pathname (asdf:find-system system))))))

(in-package :verrazano-user)

(defun generate-binding* (name headers &rest args
                          &key (working-directory (verrazano::system-relative-pathname
                                                   :verrazano "example-bindings/"))
                          (gccxml-flags "-I/usr/include")
                          &allow-other-keys)
  (format *debug-io* "~%~%; *** Processing binding ~S~%" name)
  (remove-from-plistf args :working-directory :gccxml-flags)
  (block try
    (handler-bind ((serious-condition
                    (lambda (error)
                      (warn "Failed to generated binding for ~S, error: ~A" name error)
                      (return-from try))))
      (let ((*print-right-margin* 100))
        (generate-binding (append
                           (list :cffi
                                 :package-name name
                                 :input-files headers
                                 :working-directory working-directory
                                 :gccxml-flags gccxml-flags)
                           args)
                          :keep-temporary-files nil))))
  (values))

(generate-binding*
 :photogrammetrie-cffi-bindings
 '("/home/bertb/clbuild/source/photogrammetrie/Photo/cam.h"
   "/home/bertb/clbuild/source/photogrammetrie/Photo/bpoint.h"
   "/home/bertb/clbuild/source/photogrammetrie/wrapper_for_lisp/CBPointList.h"
   "vector")
 :working-directory #P"/home/bertb/clbuild/source/photogrammetrie/")

