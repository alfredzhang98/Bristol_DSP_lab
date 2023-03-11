//************************ DSP Course Work Group 5 ********************************
// Author1: Qingyu Zhang; vn22984@bristol.ac.uk
// Author2: Shuran Yang; rw22242@bristol.ac.uk
// Author3: Ruilong Liu; hx22195@bristol.ac.uk
// Date: 08/02/2023
//*********************************************************************************

/* gtz.h */


#ifndef GTZ_H_
#define GTZ_H_

#define SAMPLING_RATE  8000.0
#define TICK_PERIOD    (1/SAMPLING_RATE)  /*125us set in clock.cfg */
#define TIMEOUT        1
#define NO_OF_SAMPLES  (206*8)
#define PI             3.1415926535897932384626433832795

#define DTMF_NUM 8
#define DTMF_HALF_NUM DTMF_NUM/2

#define THRESHOLD_POWER 50000
//#define THRESHOLD_POWER 200
#define N_VAL 206

#endif /* GTZ_H_ */
