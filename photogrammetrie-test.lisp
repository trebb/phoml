(in-package :photogrammetrie) 

(rt:deftest vws/1
    (progn
      (del-all)
      (add-cam
       1392 1040                        ; PIX_ROW PIX_COL
       0.00465d0                        ; PIX_SIZE 
       0d0 0d0 0d0                      ; DX DY DZ
       0d0 0d0 0d0                      ; OMEGA PHI KAPPA
       -8.3481198d0 0.00089d0 0.00472d0 ; C XH YH
       -0.00284666d0 4.33195d-05 0d0    ; A1 A2 A3
       1.01299d-05 -2.01898d-05         ; B1 B2
       -0.000134369d0 -4.26305d-05      ; C1 C2 
       2.427375d0                       ; R0
       0d0 0d0 0d0 0d0 0d0 0d0 0d0 0d0 0d0 0d0 0d0 0d0)
      (add-bpoint 272d0 325d0)
      (add-cam
       1392 1040                                    ; PIX_ROW PIX_COL
       0.00465d0                                    ; PIX_SIZE 
       -1114.242911d0 -2.313123752d0 -108.0708656d0 ; DX DY DZ
       -0.006391017146d0 -0.1810263138d0 0.007287021954d0 ; OMEGA PHI KAPPA
       -8.3789952d0 0.08349d0 0.00098d0                   ; C XH YH
       -0.00285721d0 4.69797d-05 0d0                      ; A1 A2 A3
       8.79895d-05 6.01291d-05                            ; B1 B2
       3.13052d-05 -8.65479d-05                           ; C1 C2 
       2.427375d0                                         ; R0
       0d0 0d0 0d0 0d0 0d0 0d0 0d0 0d0 0d0 0d0 0d0 0d0)
      (add-bpoint 223d0 300d0)
      (calculate)
      (multiple-value-prog1 
          (values
           (get-m) (get-n)
           (get-x-local) (get-y-local) (get-z-local)
           (get-stdx-local) (get-stdy-local) (get-stdz-local)
           (get-x-global) (get-y-global) (get-z-global)
           (get-stdx-global) (get-stdy-global) (get-stdz-global))
        (del-all)))
  223.0d0 300.0d0
  -1062.3945612937443d0 1587.5888858836176d0 -7728.733215755937d0
  5.473015866381161d0 12.58146038763985d0 57.68237735678784d0
  0.0d0 0.0d0 0.0d0
  0.0d0 0.0d0 0.0d0)

(defparameter *cam-left*
  '(960 1280                                ; PIX_ROW PIX_COL
    0.00645d0                               ; PIX_SIZE 
    0d0 0d0 0d0                             ; DX DY DZ
    0d0 0d0 0d0                             ; OMEGA PHI KAPPA
    -5.96131d0 0.09154d0 0.05499d0          ; C XH YH
    -0.00392312d0 5.3042d-05 0d0            ; A1 A2 A3
    3.41561d-05 1.66584d-05                 ; B1 B2
    0.000115336d0 3.44961d-05               ; C1 C2 
    3.1d0                                   ; R0
    1.810038117d0 1.997471691d0 2.954505537d0 ; B_DX B_DY B_DZ
    0d0 0d0 0d0                               ; B_DDX B_DDY B_DDZ
    1.236546986d0 -0.6468711578d0 -0.222276496d0 ; B_ROTX B_ROTY B_ROTZ
    0d0 0d0 0d0))                       ; B_DROTX B_DROTY B_DROTZ
(defparameter *cam-right*
  '(960 1280                                         ; PIX_ROW PIX_COL
    0.00645d0                                        ; PIX_SIZE 
    1.694736602d0 -0.5066248238d0 1.913592406d0      ; DX DY DZ
    0.06547699024d0 -0.02425883623d0 0.01597899627d0 ; OMEGA PHI KAPPA
    -5.96062d0 -0.02699d0 0.00748d0                  ; C XH YH
    -0.00392089d0 5.0132d-05 0d0                     ; A1 A2 A3
    -2.96244d-05 -0.000116111d0                      ; B1 B2
    -8.63535d-05 -7.70085d-05                        ; C1 C2 
    3.1d0                                            ; R0
    1.886692106d0 -0.6072478387d0 2.940466502d0      ; B_DX B_DY B_DZ
    0d0 0d0 0d0                                   ; B_DDX B_DDY B_DDZ
    1.312015813d0 -0.6836290131d0 -0.1604868833d0 ; B_ROTX B_ROTY B_ROTZ
    0d0 0d0 0d0))                       ; B_DROTX B_DROTY B_DROTZ
(defparameter *global-car-reference-point*
  '(641754.64076d0 5638452.77658d0          ; EASTING NORTHING
    296.79691d0                             ; EHEIGTH 
    -0.2235410d0 -0.6600010d0 214.0967730d0 ; ROLL PITCH HEADING
    50.8803408d0 11.0150776d0))             ; LATITUDE LONGITUDE

(rt:deftest vws/2
    (progn
      (del-all)
      (apply #'add-cam *cam-left*)
      (add-bpoint 756d0 345d0)
      (apply #'add-cam *cam-right*)
      (add-bpoint 401d0 370d0)
      (apply #'add-global-car-reference-point *global-car-reference-point*)
      (set-global-reference-frame)
      (calculate)
      (multiple-value-prog1
          (values
           (get-m) (get-n)
           (get-x-local) (get-y-local) (get-z-local)
           (get-stdx-local) (get-stdy-local) (get-stdz-local)
           (get-x-global) (get-y-global) (get-z-global)
           (get-stdx-global) (get-stdy-global) (get-stdz-global))
        (del-all)))
  401.0d0 370.0d0
  0.4065545831586287d0 0.5052388614207152d0 -3.7809044494132813d0
  0.0030916030241650407d0 0.004254531230252718d0 0.019928437349091173d0
  641748.3224107784d0 5638451.209601247d0 299.2062569395003d0
  0.0d0 0.0d0 0.0d0)

(defparameter *global-measurement-point* ; actually calculated in test vws/2
  '(641748.3224107784d0                  ; x-global
    5638451.209601247d0                  ; y-global
    299.2062569395003d0))                ; z-global

(rt:deftest rws/left
    (progn
      (del-all)
      (apply #'add-cam *cam-left*)
      (apply #'add-global-measurement-point *global-measurement-point*)
      (apply #'add-global-car-reference-point *global-car-reference-point*)
      (set-global-reference-frame)
      (calculate)
      (multiple-value-prog1
          (values (get-m) (get-n))
        (del-all)))
  756.0215947053355d0 344.8316172438852d0)

(rt:deftest rws/right
    (progn
      (del-all)
      (apply #'add-cam *cam-right*)
      (apply #'add-global-measurement-point *global-measurement-point*)
      (apply #'add-global-car-reference-point *global-car-reference-point*)
      (set-global-reference-frame)
      (calculate)
      (multiple-value-prog1
          (values (get-m) (get-n))
        (del-all)))
  400.96040801712263d0 370.25506200401304d0)

(rt:deftest mono/1
    (progn
      (del-all)
      (apply #'add-cam *cam-left*)
      (add-bpoint 756.000d0 345.000d0)
      (add-ref-ground-surface 0d0 0d0 1.0d0 2.44d0)
      (apply #'add-global-car-reference-point *global-car-reference-point*)
      (set-global-reference-frame)
      (calculate)
      (multiple-value-prog1
          (values (get-m) (get-n)
                  (get-x-local) (get-y-local) (get-z-local)
                  (get-x-global) (get-y-global) (get-z-global))
        (del-all)))
  755.9999994508227d0 345.0000006141719d0
  0.41075965074325677d0 0.5098961375789827d0 -3.8208460421855737d0
  641748.2834246102d0 5638451.200894518d0 299.20001392632093d0)

(rt:deftest epipolar/1
    (progn
      (del-all)
      (apply #'add-cam *cam-left*)
      (add-bpoint 756d0 345d0)
      (apply #'add-cam *cam-right*)
      (prog1
          (loop
             for i from 4d0 upto 30d0 by .5d0
             do
               (set-distance-for-epipolar-line i)
               (calculate)
             collect (list i (get-m) (get-n)))
        (del-all)))
  ((3.0d0 348.8838003312308d0 362.92922097055947d0)
   (10.0d0 562.3853909475243d0 393.8075286053437d0)
   (17.0d0 618.790875020272d0 402.15394569448256d0)
   (24.0d0 644.7568644672281d0 406.02503563147326d0)
   (31.0d0 659.6776642730952d0 408.2577629003564d0)
   (38.0d0 669.3626651434224d0 409.71025002804396d0)
   (45.0d0 676.1558194809563d0 410.7305574257181d0)))

(rt:deftest epipolar/2
    (let ((global-car-reference-point   ; pic 13
           '(641754.64076d0 5638452.77658d0 296.79691d0
             -0.2235410d0 -0.6600010d0 214.0967730d0
             50.8803408d0 11.0150776d0)))
      (setf *read-default-float-format* 'double-float)
      (del-all)
      (add-cam 1500 1700 0.007397
               0.0 0.0 0.0
               0.0 0.0 0.0
               -10.18083 -0.08149 0.19289
               -9.13833e-4 1.04652e-5 0.0
               -5.35737e-5 9.49128e-5
               -1.33724e-4 2.11705e-4 4.715882
               -1.477057713 1.534101279 2.022740812 0.0 0.0 0.0
               1.451034299 -0.08489628795 -0.001997345786 0.0 0.0 0.0)
      (add-bpoint 609.765625 855.46875)
      (apply #'add-global-car-reference-point-cam-set-global global-car-reference-point)
      (add-cam 1500 1700 0.007397
               1118.63068e-3 2.83904e-3 -93.05154e-3
               -0.00133668 0.17822421 0.02194869
               -10.19408 -0.00529 0.23262
               -9.22005e-4 1.0648e-5 0.0
               -6.0248e-5 -1.31699e-5
               -1.15248e-4 1.95328e-4 4.715882
               -0.3475010749 1.532254309 2.021913699 0.0 0.0 0.0
               1.450387893 0.09424800356 0.02078575518 0.0 0.0 0.0)
      (apply #'add-global-car-reference-point-cam-set-global global-car-reference-point)
      (prog1
          (loop
             for i from 5d0 upto 15d0 by .5d0
             do
             (set-distance-for-epipolar-line i)
             (calculate)
             collect (list i (get-m) (get-n)))
        (del-all)))
  ((5.0 560.3336044680696 838.1549041802012)
   (5.5 587.6587886072139 839.0703000450521)
   (6.0 610.5471648862741 839.8318211754861)
   (6.5 629.9965424991101 840.474921802958)
   (7.0 646.7266732818262 841.0250277486987)
   (7.5 661.2697595238944 841.5008218975725)
   (8.0 674.0277701931817 841.9163263993768)
   (8.5 685.3099510880472 842.2822638916546)
   (9.0 695.3580911279768 842.6069648785107)
   (9.5 704.363941570364 842.8970023841142)
   (10.0 712.4815192203931 843.1576272114963)
   (10.5 719.83594571957 843.3930841214614)
   (11.0 726.5299154395236 843.6068408897249)
   (11.5 732.6485017533915 843.8017578589506)
   (12.0 738.2627786928527 843.9802150938192)
   (12.5 743.432584827391 844.1442087542648)
   (13.0 748.2086580593791 844.2954254775873)
   (13.5 752.6343011475074 844.4352999006019)
   (14.0 756.7466949303281 844.56505998819)
   (14.5 760.5779428663861 844.685762945345)
   (15.0 764.1559084493797 844.7983237485788)))


(rt:deftest epipolar/3
    (let ((global-car-reference-point
           '(731651.936 5379722.405 439.69
             2.138 -1.406 67.077
             48.52781512940818 12.137770422789336)))
      (setf *read-default-float-format* 'double-float)
      (del-all)
      (add-cam 1500 1700 0.007397
               0.0 0.0 0.0
               0.0 0.0 0.0
               -10.18083 -0.08149 0.19289
               -9.13833e-4 1.04652e-5 0.0
               -5.35737e-5 9.49128e-5
               -1.33724e-4 2.11705e-4 4.715882
               -1.477057713 1.534101279 2.022740812 0.0 0.0 0.0
               1.451034299 -0.08489628795 -0.001997345786 0.0 0.0 0.0)
      (add-bpoint 1313.44921875 321.73046875)
      (apply #'add-global-car-reference-point-cam-set-global global-car-reference-point)
      (add-cam 1500 1700 0.007397
               1.1186306799999999 0.0028390399999999997 -0.09305154
               -0.00133668 0.17822421 0.02194869
               -10.19408 -0.00529 0.23262
               -9.22005e-4 1.0648e-5 0.0
               -6.0248e-5 -1.31699e-5
               -1.15248e-4 1.95328e-4 4.715882
               -0.3475010749 1.532254309 2.021913699 0.0 0.0 0.0
               1.450387893 0.09424800356 0.02078575518 0.0 0.0 0.0)
      (apply #'add-global-car-reference-point-cam-set-global global-car-reference-point)
      (prog1
          (loop
             for i from 4d0 upto 15d0 by .5d0
             do
             (set-distance-for-epipolar-line i)
             (calculate)
             collect (list i (get-m) (get-n)))
        (del-all)))
nil)
 
 
 
(731651.936 5379722.405 439.69 2.138 -1.406 67.077 48.52781512940818
 12.137770422789336)


(rt:deftest multi-car-position/1
    (progn
      (del-all)
      (set-global-reference-frame)
      (let ((global-car-reference-point ; pic 13
             '(641754.64076d0 5638452.77658d0 296.79691d0
               -0.2235410d0 -0.6600010d0 214.0967730d0
               50.8803408d0 11.0150776d0)))
        (apply #'add-cam *cam-left*)
        (add-bpoint 756d0 345d0)
        (apply #'add-global-car-reference-point-cam-set-global global-car-reference-point)
        (apply #'add-cam *cam-right*)
        (add-bpoint 401d0 370d0)
        (apply #'add-global-car-reference-point-cam-set-global global-car-reference-point))
      (let ((global-car-reference-point ; pic 12
             '(641754.9447785d0 5638453.2901614d0 296.8227930d0
               0.0109420d0 -0.9424530d0 212.0283640d0
               50.8803453d0 11.0150821d0)))
        (apply #'add-cam *cam-left*)
        (add-bpoint 715d0 325d0)
        (apply #'add-global-car-reference-point-cam-set-global global-car-reference-point)
        (apply #'add-cam *cam-right*)
        (add-bpoint 395d0 360d0)
        (apply #'add-global-car-reference-point-cam-set-global global-car-reference-point))
      (let ((global-car-reference-point ; pic 10
             '(641753.5016304d0 5638454.2034647d0 296.7935520d0
               -0.1139750d0 -0.5450980d0 190.7414720d0
               50.8803539d0 11.0150620d0)))
        (apply #'add-cam *cam-left*)
        (add-bpoint 985d0 369d0)
        (apply #'add-global-car-reference-point-cam-set-global global-car-reference-point)
        (apply #'add-cam *cam-right*)
        (add-bpoint 506d0 381d0)
        (apply #'add-global-car-reference-point-cam-set-global global-car-reference-point))
      (let ((global-car-reference-point ; pic 1
             '(641755.4308509d0 5638456.1936776d0 296.8429180d0
               -0.2612280d0 -1.5055340d0 219.9422050d0
               50.8803713d0 11.0150901d0)))
        (apply #'add-cam *cam-left*)
        (add-bpoint 65d0 305d0)
        (apply #'add-global-car-reference-point-cam-set-global global-car-reference-point))
      (calculate)
      (multiple-value-prog1
          (values (get-x-local) (get-y-local) (get-z-local)
                  (get-stdx-local) (get-stdy-local) (get-stdz-local)
                  (get-x-global) (get-y-global) (get-z-global)
                  (get-stdx-global) (get-stdy-global) (get-stdz-global))
        (del-all)))
  641748.3095247374d0 5638451.210544314d0 299.20795568520276d0
  0.02327612548040077d0 0.01276520778633635d0 0.0065087018321247185d0
  641748.3095247374d0 5638451.210544314d0 299.20795568520276d0
  0.02327612548040077d0 0.01276520778633635d0 0.0065087018321247185d0)
