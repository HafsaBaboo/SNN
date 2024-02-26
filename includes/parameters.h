/**
 * GENERAL AND COMMON MACROS 
*/

#define TIME_STAMP 25 // time stamps
#define SAMPLES 128 //epoch samples in a batch
#define DECAY 0.95 // decay factor
#define MEM_TH 1 //threshold membrane potential


/**
 * SPECIFIC MACROS FOR THE DEEP SNN
*/
#define INPUT_IMAGE 1 // inmage inputIMG

#define W_KERNEL 3 // p
#define H_KERNEL 3 // h

#define OUTPUT_CNN_1 4 // output of the first CNN layer
#define OUTPUT_CNN_2 16 // output of the second CNN layer
#define OUTPUT_CNN_3 32 // output of the third CNN layer
#define OUTPUT_FC_4 10 // output fc lacolumner

#define W_FEATURE_MAP 28 // row
#define H_FEATURE_MAP 28 // column

#define PADDING 1 // padding value
#define STRIDE_2 2 // stiding value for the first two layers
#define STRIDE_4 4 // stiding value for the last layer


/**
 * SPECIFIC MACROS FOR THE FULLY CONNECTED SNN
*/

#define LAYERS 3 //number of layers
#define INPUTS 784 //number of input neurons
#define HIDDEN 1000 //number of neurons in the hidden layer
#define OUTPUT 10 //number of output neurons