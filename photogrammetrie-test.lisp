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
      (values
       (get-m) (get-n)
       (get-x-local) (get-y-local) (get-z-local)
       (get-stdx-local) (get-stdy-local) (get-stdz-local)
       (get-x-global) (get-y-global) (get-z-global)
       (get-stdx-global) (get-stdy-global) (get-stdz-global)))
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
      (values
       (get-m) (get-n)
       (get-x-local) (get-y-local) (get-z-local)
       (get-stdx-local) (get-stdy-local) (get-stdz-local)
       (get-x-global) (get-y-global) (get-z-global)
       (get-stdx-global) (get-stdy-global) (get-stdz-global)))
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
      (values (get-m) (get-n)))
  756.0215947053355d0 344.8316172438852d0)

(rt:deftest rws/right
    (progn
      (del-all)
      (apply #'add-cam *cam-right*)
      (apply #'add-global-measurement-point *global-measurement-point*)
      (apply #'add-global-car-reference-point *global-car-reference-point*)
      (set-global-reference-frame)
      (calculate)
      (values (get-m) (get-n)))
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
      (values (get-m) (get-n)))
  755.9999994508227d0 345.0000006141719d0)

;(rt:deftest epipolar/1
; ... ?)

(rt:deftest multi-car-position/1
    (progn
      (del-all)
      (set-global-reference-frame)
      (apply #'add-cam *cam-left*) ; pic 13
      (add-bpoint 756d0 345d0)
      (apply #'add-global-car-reference-point-cam-set-global *global-car-reference-point*)
      (apply #'add-cam *cam-right*)
      (add-bpoint 401d0 370d0)
      (apply #'add-global-car-reference-point-cam-set-global *global-car-reference-point*)
      (let ((global-car-reference-point ; pic 12
             '(641754.9447785d0 5638453.2901614d0 296.8227930d0
               0.0109420d0 -0.9424530d0 212.0283640d0
               50.8803453d0 11.0150821d0)))
        (apply #'add-cam *cam-left*)
        (add-bpoint 715d0 325d0)
        (apply #'add-global-car-reference-point-cam-set-global global-car-reference-point)
        (apply #'add-cam *cam-right*)
        (add-bpoint 395d0 316d0)
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
      (values (get-x-local) (get-y-local) (get-z-local)
              (get-stdx-local) (get-stdy-local) (get-stdz-local)
              (get-x-global) (get-y-global) (get-z-global)
              (get-stdx-global) (get-stdy-global) (get-stdz-global)))
  nil)

