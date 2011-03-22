(pushnew (make-pathname :directory '(:relative :up "phoml" "lib"))
         cffi:*foreign-library-directories*)
(cffi:load-foreign-library '(:default "libphoml"))

(in-package :phoml)

(setf *read-default-float-format* 'double-float)

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
  ((4.0 409.4827407936011 371.5898291349205)
   (4.5 432.90531524595804 374.95749853416373)
   (5.0 453.0234174084091 377.85977329679133)
   (5.5 470.48542755656786 380.38644115071435)
   (6.0 485.7813425731469 382.6056367806837)
   (6.5 499.28821233456733 384.56999936998375)
   (7.0 511.3007947510435 386.32083729252685)
   (7.5 522.0527641903291 387.8910168259515)
   (8.0 531.731698582578 389.3070099755683)
   (8.5 540.4898720209824 390.5903741438454)
   (9.0 548.4521589779063 391.75883951517125)
   (9.5 555.7219116900953 392.82712034888635)
   (10.0 562.3853909475243 393.8075286053437)
   (10.5 568.5151484235788 394.7104438556875)
   (11.0 574.1726383928304 395.5446772304317)
   (11.5 579.4102557447355 396.31775624097816)
   (12.0 584.2729418232641 397.0361498177192)
   (12.5 588.7994611469785 397.7054476905658)
   (13.0 593.0234249526901 398.33050455117126)
   (13.5 596.9741181515786 398.9155567972168)
   (14.0 600.6771723022542 399.464317747227)
   (14.5 604.1551169867059 399.9800558136356)
   (15.0 607.4278344296923 400.4656590848134)
   (15.5 610.5129365757738 400.92368899155747)
   (16.0 613.4260796041041 401.35642514872603)
   (16.5 616.1812276471748 401.7659030177514)
   (17.0 618.790875020272 402.15394569448256)
   (17.5 621.2662343718792 402.5221908630738)
   (18.0 623.6173966922004 402.87211375134433)
   (18.5 625.8534679649838 403.2050467621741)
   (19.0 627.9826863410598 403.52219632862887)
   (19.5 630.0125229938618 403.8246574398434)
   (20.0 631.9497729809309 404.11348907815824)
   (20.5 633.8006142768286 404.38947356454753)
   (21.0 635.5707005838284 404.6535034608685)
   (21.5 637.2651989271609 404.90633822260776)
   (22.0 638.8888451547451 405.148674373807)
   (22.5 640.4459879524347 405.3811518871288)
   (23.0 641.9406322797954 405.6042975613886)
   (23.5 643.3764559715952 405.8187791042404)
   (24.0 644.7568644672281 406.02503563147326)
   (24.5 646.0850025826717 406.2235309684054)
   (25.0 647.3637817762902 406.4146947368995)
   (25.5 648.5959013836497 406.59892544870127)
   (26.0 649.7838675766674 406.7765932692707)
   (26.5 650.9300103264325 406.94804249231464)
   (27.0 652.036498610544 407.11359375971915)
   (27.5 653.1053540731904 407.2735460569089)
   (28.0 654.138463318458 407.4281785096832)
   (28.5 655.1375889936999 407.57775200518086)
   (29.0 656.1043797995742 407.7225106567241)
   (29.5 657.0403795460263 407.8626831297968)
   (30.0 657.9470353585824 407.9984838442679)))

(rt:deftest epipolar/2
    (let ((global-car-reference-point   ; pic 13
           '(641754.64076d0 5638452.77658d0 296.79691d0
             -0.2235410d0 -0.6600010d0 214.0967730d0
             50.8803408d0 11.0150776d0)))
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
  ((4.0 1162.1348176008294 300.66918306912595)
   (4.5 1212.7459779862054 300.78209304686294)
   (5.0 1253.3827784365303 300.8943541428109)
   (5.5 1286.731567043701 300.9946937661935)
   (6.0 1314.5944947561347 301.080397118059)
   (6.5 1338.224911351075 301.1519833362925)
   (7.0 1358.5212232954789 301.2110804494263)
   (7.5 1376.1441776867096 301.2595359760495)
   (8.0 1391.5905593928244 301.29908972674315)
   (8.5 1405.241092407451 301.33126188664534)
   (9.0 1417.3924777946388 301.3573357236193)
   (9.5 1428.2793761872817 301.3783761122564)
   (10.0 1438.089831146475 301.3952593837856)
   (10.5 1446.9763065260995 301.4087043528532)
   (11.0 1455.0637302672 301.4193001965349)
   (11.5 1462.455447405564 301.4275304180558)
   (12.0 1469.2376929318007 301.43379259593934)
   (12.5 1475.4829959323051 301.4384144592164)
   (13.0 1481.25280042451 301.4416670362447)
   (13.5 1486.5995081295114 301.44377505459266)
   (14.0 1491.5680836103654 301.44492551395666)
   (14.5 1496.1973305621718 301.4452744105316)
   (15.0 1500.5209123464351 301.4449523174959)))
 
 
 
;(731651.936 5379722.405 439.69 2.138 -1.406 67.077 48.52781512940818
; 12.137770422789336)


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
