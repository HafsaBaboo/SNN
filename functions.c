#include <stdio.h>
#include "./includes/parameters.h"
#include "./includes/functions.h"


void fullyConnected(double input[], int i , double outputMemTH[], double output[], int o, double w[HIDDEN*INPUTS]){ //first row is the membrane potential value, the second one is the otput value
    int j, k;
    for(j=0; j<o; j++){ //for each output 
        //Initializing the outputs value of the output layer neuron to 0
        output[j]= 0; 
        for(k=0; k<i; k++){ //for each input 
        //Checking if a input neuron fired
            if(input[k]){
                //Summing weight
                outputMemTH[j] += w[j*i+k];
            }
            //Checking if overcomed memth
            if(outputMemTH[j] >= MEM_TH){
                //Initializing output to 1 --> firing the neuron
                output[j] ++;
                //Resetting memth
                outputMemTH[j] -= MEM_TH; //and reset the membrane potential value 
                break;
            }
        }
        //Decaying
        outputMemTH[j] *= DECAY; //calculate the decay of the outputs membrane potential
    }
}

int convolutionalLayerWithoutLeaking(double inputIMG[], int inChannels, int inputRowLenght,  double output[], int outChannels, double weights[], int kernelsRowLenght, int padding, int stride, double memTh[], double bias[]){
    int outDim =0;
    int cnt, cntO =0;
    int row, column, weightsRow, weightsColumn, outputChannel, inputChannel;
    float sum[OUTPUT_CNN_3*2*2*OUTPUT_FC_4] = {0};
    int inputColumnLenght = inputRowLenght;
    int kernelsColumnLenght = kernelsRowLenght;

    int outRowsNumber= ((inputRowLenght+2*padding-kernelsRowLenght)/stride)+1; //height of the output feature map
    int outColumsNumber= ((inputColumnLenght+2*padding-kernelsColumnLenght)/stride)+1; //width of the output feature map
    
    int weightsDim = kernelsRowLenght*kernelsColumnLenght; //dimention of the kernel/weight matrix
    int inputDim = inputRowLenght*inputColumnLenght; //dimention of the input matrix
    int outputDim = outRowsNumber*outColumsNumber; //dimention of the output feature map matrix

    outDim = outRowsNumber*outColumsNumber*outChannels;

    //computation of the convoluiton
    for(outputChannel=0; outputChannel<outChannels; outputChannel++){ //for each output feature map
        for(inputChannel=0; inputChannel<inChannels; inputChannel++){ //for each input channel
            for(row=0; row<outRowsNumber*stride; row+=stride){ //for each row in the output feature map
                for(column=0; column<outColumsNumber*stride; column+=stride){ //for each column in the output feature map
                    for(weightsRow=0; weightsRow<kernelsRowLenght; weightsRow++){ //for each row in the weight matrix
                        for(weightsColumn=0; weightsColumn<kernelsColumnLenght; weightsColumn++){ //for each column in the weight matrix
                            if((row+weightsRow)<padding || (row+weightsRow)>= padding+inputColumnLenght || (column+weightsColumn)< padding || (column+weightsColumn)>= padding+inputRowLenght){ 
                                //in case of padding, skip the padding 
                                continue;
                            }else{
                                //compute the convolution
                                output[(row/stride)*outColumsNumber+(column/stride)+(outputDim*outputChannel)] += inputIMG[(row+weightsRow-padding)*inputColumnLenght+column+weightsColumn-padding+(inputChannel*inputDim)]*weights[weightsRow*kernelsColumnLenght+weightsColumn+(inputChannel*weightsDim)+(outputChannel*weightsDim*inChannels)]; /*+= nelle SNN*/
                            }
                        }
                    }
                }
            }
        }
    }

    for(outputChannel=0; outputChannel<outChannels; outputChannel++){
        for(int out=0; out<outputDim; out++){
            output[out+outputChannel*outputDim] +=bias[outputChannel];
        }
    }

    return outDim;
}

int leakingConvolutionalLayer(double inputIMG[], int inChannels, int inputRowLenght,  double output[], int outChannels, double weights[], int kernelsRowLenght, int padding, int stride, double memTh[], double bias[]){
    int outDim =0;
    int cnt, cntO =0;
    int row, column, weightsRow, weightsColumn, outputChannel, inputChannel;
    float sum[OUTPUT_CNN_3*2*2*OUTPUT_FC_4] = {0};
    int inputColumnLenght = inputRowLenght;
    int kernelsColumnLenght = kernelsRowLenght;

    int outRowsNumber= ((inputRowLenght+2*padding-kernelsRowLenght)/stride)+1; //height of the output feature map
    int outColumsNumber= ((inputColumnLenght+2*padding-kernelsColumnLenght)/stride)+1; //width of the output feature map
    
    int weightsDim = kernelsRowLenght*kernelsColumnLenght; //dimention of the kernel/weight matrix
    int inputDim = inputRowLenght*inputColumnLenght; //dimention of the input matrix
    int outputDim = outRowsNumber*outColumsNumber; //dimention of the output feature map matrix

    outDim = outputDim*outChannels; //dimention of all feature maps

    //setting the outputs to 0
    for(outputChannel=0; outputChannel<outChannels; outputChannel++){
        for(row=0; row<outRowsNumber; row++){
            for( column=0; column<outColumsNumber; column++){
                output[(row*outColumsNumber)+column+(outputDim*outputChannel)] = 0;
            }
        }
    }

    //computing the convolution 
    for(outputChannel=0; outputChannel<outChannels; outputChannel++){
        for(inputChannel=0; inputChannel<inChannels; inputChannel++){
            for(row=0; row<outRowsNumber*stride; row+=stride){
                for(column=0; column<outColumsNumber*stride; column+=stride){
                    for(weightsRow=0; weightsRow<kernelsRowLenght; weightsRow++){
                        for(weightsColumn=0; weightsColumn<kernelsColumnLenght; weightsColumn++){
                            if((row+weightsRow)<padding || (row+weightsRow)>= padding+inputColumnLenght || (column+weightsColumn)< padding || (column+weightsColumn)>= padding+inputRowLenght){
                                continue;
                            }else{
                                memTh[(row/stride)*outColumsNumber+(column/stride)+(outputDim*outputChannel)] += inputIMG[(row+weightsRow-padding)*inputColumnLenght+column+weightsColumn-padding+(inputChannel*inputDim)]*weights[weightsRow*kernelsColumnLenght+weightsColumn+(inputChannel*weightsDim)+(outputChannel*weightsDim*inChannels)];    
                            }
                        }
                    }
                }
            }
        }
    }

    //adding the bias value for each feature map
    for(outputChannel=0; outputChannel<outChannels; outputChannel++){
        for(int out=0; out<outputDim; out++){
            memTh[out+outputChannel*outputDim] +=bias[outputChannel];
        }
    }
    
    //charck if the neurons fired and compute the decay of the membrane potential
    for(outputChannel=0; outputChannel<outChannels; outputChannel++){
        for(int out=0; out<outputDim; out++){
            if(memTh[out+outputChannel*outputDim] >= MEM_TH){
                output[out+outputChannel*outputDim] = 1;
                memTh[out+outputChannel*outputDim] -= MEM_TH;
            }
            memTh[(row*outColumsNumber)+column+(outputDim*outputChannel)] *= DECAY;
        }
    }
    return outDim;
}


int getMax(double data[], int n){
    int max=0;
    int j=0;

    for(int i=0; i<n; i++){
        if(data[i]>max){
            max=data[i];
            j=i;
        }
    }

    return j;
}

