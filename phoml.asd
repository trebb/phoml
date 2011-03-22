
(defsystem :phoml
  :depends-on (:cffi)
  :version "0.1"
  :serial t
  :components
  ((:file "package")
   (:file "phoml")))

(defsystem :phoml-test
  :depends-on (:phoml :rt)
  :components
  ((:file "phoml-test")))