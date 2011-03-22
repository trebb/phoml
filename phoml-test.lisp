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
  ((4.0 1517.9814099559253 542.411902896527)
   (4.5 1370.0090167023513 519.3329376471311)
   (5.0 1270.0836296127266 503.52518372619704)
   (5.5 1197.059429649286 491.9235314685701)
   (6.0 1141.0999999845753 483.02910820246996)
   (6.5 1096.774235011709 475.99180269613504)
   (7.0 1060.7717930863914 470.2865395758554)
   (7.5 1030.943771955305 465.56965539128475)
   (8.0 1005.8273399810996 461.6062593131482)
   (8.5 984.3891502361864 458.23026626914185)
   (9.0 965.8778755213599 455.3209080322782)
   (9.5 949.7339587484745 452.78826279369883)
   (10.0 935.5318000130269 450.56402861406383)
   (10.5 922.9419369860111 448.5954069645473)
   (11.0 911.7053437360022 446.8409520089408)
   (11.5 901.6155674660362 445.2676836363163)
   (12.0 892.5060430576191 443.8490372363247)
   (12.5 884.2409124508129 442.5633805774158)
   (13.0 876.7082677568299 441.39292306906657)
   (13.5 869.8151026378208 440.3229015822801)
   (14.0 863.483488359565 439.3409644641142)
   (14.5 857.6476414128333 438.4366997460718)
   (15.0 852.2516493156265 437.6012697116428)
   (15.5 847.24768852645 436.8271249098099)
   (16.0 842.5946146205852 436.10777820265395)
   (16.5 838.2568371119241 435.4376246658027)
   (17.0 834.2034140979272 434.8117968587752)
   (17.5 830.4073319408726 434.22604656373403)
   (18.0 826.8448527818592 433.6766529838169)
   (18.5 823.4950991598336 433.1603393561784)
   (19.0 820.33959683681 432.6742109526655)
   (19.5 817.3619479503266 432.21570063555976)
   (20.0 814.5475475838089 431.78252386420786)
   (20.5 811.8833454877444 431.372640908514)
   (21.0 809.3576447836282 430.9842249592676)
   (21.5 806.9599311278116 430.61563509022676)
   (22.0 804.6807270940996 430.2653932330957)
   (22.5 802.5114675392542 429.93216448811756)
   (23.0 800.4443925091307 429.61474022043035)
   (23.5 798.4724548733839 429.3120234934352)
   (24.0 796.5892403800758 429.02301647110085)
   (24.5 794.7888982257879 428.7468094858608)
   (25.0 793.0660805632219 428.48257152097267)
   (25.5 791.4158896330802 428.22954189853033)
   (26.0 789.8338314228755 427.98702299879193)
   (26.5 788.3157749320911 427.7543738646895)
   (27.0 786.8579162684922 427.53100456856225)
   (27.5 785.4567469204527 427.31637123728007)
   (28.0 784.1090256497159 427.10997164776927)
   (28.5 782.8117535318593 426.9113413181276)
   (29.0 781.5621517409575 426.7200500305178)
   (29.5 780.3576417329551 426.53569873124076)
   (30.0 779.1958275310751 426.35791676113536)))

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
  ((5.0 1189.8765735369068 857.1036745282792)
   (5.5 1160.3579323766671 856.3098454852801)
   (6.0 1135.7992388010507 855.6445436889177)
   (6.5 1115.0485682565031 855.0785682966862)
   (7.0 1097.2849380050554 854.591072539169)
   (7.5 1081.907406992937 854.1667059868955)
   (8.0 1068.4659929868074 853.7939035431085)
   (8.5 1056.6170853893418 853.463777150726)
   (9.0 1046.0937811381523 853.1693789732603)
   (9.5 1036.685620624324 852.9051965603242)
   (10.0 1028.2244243304553 852.6667989251918)
   (10.5 1020.5741890313352 852.4505829479814)
   (11.0 1013.6237477882358 852.2535880040582)
   (11.5 1007.2813512751051 852.0733586012439)
   (12.0 1001.4706089502553 851.9078423905036)
   (12.5 996.1274016591127 851.7553052718499)
   (13.0 991.1975195316995 851.6142789562232)
   (13.5 986.6348162832575 851.4835076705504)
   (14.0 982.3997651831407 851.3619119765395)
   (14.5 978.4583138794798 851.2485588993751)
   (15.0 974.7809684039989 851.1426377750339)))


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
  ((4.0 2185.641221277864 278.00173975817273)
   (4.5 2107.0188889733527 284.9477584167683)
   (5.0 2050.1181162054627 288.9110449640179)
   (5.5 2006.2270936304756 291.452817932483)
   (6.0 1971.0505776511159 293.20415777376905)
   (6.5 1942.100072060279 294.4727867539168)
   (7.0 1917.7939477268806 295.4268900915506)
   (7.5 1897.0636917125144 296.16585259518524)
   (8.0 1879.1547305795402 296.75199468384756)
   (8.5 1863.516034546094 297.22618326343405)
   (9.0 1849.7341754447282 297.6162594886258)
   (9.5 1837.4921206313218 297.941757192141)
   (10.0 1826.5421929186016 298.21675038920546)
   (10.5 1816.6878120519425 298.4516074091876)
   (11.0 1807.7707980258156 298.65411569453653)
   (11.5 1799.6623253897478 298.83022465169427)
   (12.0 1792.256348672663 298.984548519549)
   (12.5 1785.464736395396 299.1207144989469)
   (13.0 1779.21361078038 299.241608765306)
   (13.5 1773.4405586369148 299.3495530552822)
   (14.0 1768.092475212501 299.44643386904994)
   (14.5 1763.1238820129565 299.53379797767457)
   (15.0 1758.495597160134 299.61292430932843)))
 
 
 
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
