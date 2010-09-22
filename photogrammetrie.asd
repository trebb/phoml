
(defsystem :photogrammetrie
  :depends-on (:cffi)
  :version "0.0"
  :serial t
  :components
  ((:file "package")
   (:file "photogrammetrie")
   (:file "photo")))

(defsystem :photogrammetrie-test
  :depends-on (:photogrammetrie :rt)
  :components
  ((:file "photogrammetrie-test")))