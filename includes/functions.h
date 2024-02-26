#include "parameters.h"

/**
 * FUNCITON THAT COMPUTES THE FULLY CONNECTED LAYER
*/
void fullyConnected(double input[], int i , double outputMemTH[], double output[], int o, double w[HIDDEN*INPUTS]);

/**
 * FUNCITON THAT COMPUTES THE CONVOLUTIONAL LAYER
*/
int convolutionalLayerWithoutLeaking(double inputIMG[], int inChannels, int inputRowLenght,  double output[], int outChannels, double weights[], int kernelsRowLenght, int padding, int stride, double memTh[], double bias[]);

/**
 * FUNCITON THAT COMPUTES THE CONVOLUTIONAL LAYER AND THE LEAKING
*/
int leakingConvolutionalLayer(double inputIMG[], int inChannels, int inputRowLenght,  double output[], int outChannels, double weights[], int kernelsRowLenght, int padding, int stride, double memTh[], double bias[]);

/**
 * FUNCITON THAT GETS THE MAXIMUM VALUE IN AN ARRAY
*/
int getMax(double data[], int n);