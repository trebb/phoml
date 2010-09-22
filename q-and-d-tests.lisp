(in-package :cl-user)

(defpackage :photogrammetrie
  (:use :common-lisp :cffi))

(cffi:load-foreign-library "bin/libphotogrammetrie-lisp.so")

;; load bindings here (delete fasl)

(in-package :photogrammetrie) 

;;; q&d tests

(apply #'add-cam 1040 1392
       (mapcar #'(lambda (x) (coerce x 'double-float))
               '(0.00465 0 0 0 0 0 0 -8.3481198 0.00089 0.00472 -0.00284666 4.33195e-05 0 1.01299e-05 -2.01898e-05 -0.000134369 -4.26305e-05 2.427375 
                 0 0 0 0 0 0 0 0 0 0 0 0)))

(apply #'add-cam 1040 1392
       (mapcar #'(lambda (x) (coerce x 'double-float))
               '(0.00465 -1114.242911 -2.313123752 -108.0708656 -0.006391017146 -0.1810263138 0.007287021954 -8.3789952 0.08349 0.00098 -0.00285721 4.69797e-05 0 8.79895e-05 6.01291e-05 3.13052e-05 -8.65479e-05 2.427375
                 0 0 0 0 0 0 0 0 0 0 0 0)))


(apply #'add-bpoint-2 1040 1392
       (mapcar #'(lambda (x) (coerce x 'double-float))
               '(0.00465 0 0 0 0 0 0 -8.3481198 0.00089 0.00472 -0.00284666 4.33195e-05 0 1.01299e-05 -2.01898e-05 -0.000134369 -4.26305e-05 2.427375 
                 0 0 0 0 0 0 0 0 0 0 0 0 272 325)))

(apply #'add-bpoint-2 1040 1392
       (mapcar #'(lambda (x) (coerce x 'double-float))
               '(0.00465 -1114.242911 -2.313123752 -108.0708656 -0.006391017146 -0.1810263138 0.007287021954 -8.3789952 0.08349 0.00098 -0.00285721 4.69797e-05 0 8.79895e-05 6.01291e-05 3.13052e-05 -8.65479e-05 2.427375
                 0 0 0 0 0 0 0 0 0 0 0 0 223 300)))



(apply #'add-cam 1040 1392
       (mapcar #'(lambda (x) (coerce x 'double-float))
               '(0.00465 0 0 0 0 0 0 -8.3481198 0.00089 0.00472 -0.00284666 4.33195e-05 0 1.01299e-05 -2.01898e-05 -0.000134369 -4.26305e-05 2.427375 
                 0 0 0 0 0 0 0 0 0 0 0 0)))

(apply #'add-bpoint (mapcar #'(lambda (x) (coerce x 'double-float)) '(272 325)))

(apply #'add-cam 1040 1392
       (mapcar #'(lambda (x) (coerce x 'double-float))
               '(0.00465 -1114.242911 -2.313123752 -108.0708656 -0.006391017146 -0.1810263138 0.007287021954 -8.3789952 0.08349 0.00098 -0.00285721 4.69797e-05 0 8.79895e-05 6.01291e-05 3.13052e-05 -8.65479e-05 2.427375
                 0 0 0 0 0 0 0 0 0 0 0 0)))

(apply #'add-bpoint (mapcar #'(lambda (x) (coerce x 'double-float)) '(223 300)))



(caclulate)

(format t "~A ~A ~% ~A ~A ~A  ~% ~A ~A ~A  ~% ~A ~A ~A  ~% ~A ~A ~A "
        (get-m)
        (get-n)
        (get-x-local)
        (get-y-local)
        (get-z-local)
        (get-stdx-local)
        (get-stdy-local)
        (get-stdz-local)
        (get-x-global)
        (get-y-global)
        (get-z-global)
        (get-stdx-global)
        (get-stdy-global)
        (get-stdz-global)) 