# Motor control
* ESP idf
* ADC control / reading / callibrating
* Manual PWM through high precision timer

## Home for lesson 2.2 (reading poteciometer signal delays)
other project https://github.com/lyuboychuk/esp-relay/

## Homework for Lesson 2.2 (Motor control with ACD)
in <ins>platformio.ini</inc> 
- ***build_flags*** must be set as follows   ***build_flags = -D CNTL_ON***

## Home for lesson 3.1 (calibrating ADC)
in <ins>platformio.ini</inc> 
- ***build_flags*** must be set as follows   ***build_flags = -D TRACE_ON***

| RAW  | U_cali (mV) | U_manual(mV) | Error(%) |
| ---- | ----------- | ------------ | -------- |
| 4095 | 3152        | 3152         | \-1.70%  |
| 4023 | 3122        | 3122         | \-2.50%  |
| 3745 | 2991        | 2991         | \-5.00%  |
| 3547 | 2878        | 2878         | \-6.20%  |
| 3385 | 2774        | 2774         | \-6.80%  |
| 3277 | 2701        | 2701         | \-7.10%  |
| 3148 | 2609        | 2609         | \-7.30%  |
| 3027 | 2520        | 2520         | \-7.40%  |
| 2895 | 2419        | 2419         | \-7.30%  |
| 2738 | 2295        | 2295         | \-7.20%  |
| 2632 | 2210        | 2210         | \-7.10%  |
| 2504 | 2107        | 2107         | \-6.80%  |
| 2366 | 1994        | 1994         | \-6.50%  |
| 2229 | 1879        | 1879         | \-6.20%  |
| 2073 | 1750        | 1750         | \-5.80%  |
| 1906 | 1610        | 1610         | \-5.40%  |
| 1744 | 1475        | 1475         | \-5.00%  |
| 1582 | 1340        | 1340         | \-4.60%  |
| 1418 | 1203        | 1203         | \-4.20%  |
| 1255 | 1068        | 1068         | \-3.80%  |
| 1070 | 915         | 915          | \-3.40%  |
| 866  | 745         | 745          | \-2.90%  |
| 670  | 582         | 582          | \-2.40%  |
| 486  | 426         | 426          | \-1.90%  |
| 260  | 231         | 231          | \-1.10%  |
| 61   | 54          | 54           | \-0.30%  |
| 0    | 0           | 0            | 0.00%    |
