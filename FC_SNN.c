#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "./includes/parameters.h"
#include "./includes/functions.h"
#include "./includes/FC_SNN_inputs.h"
#include "./includes/FC_SNNweights.h"
#include "./includes/FC_SNNbatchTest.h"


clock_t start[3], end[3], timesSum[3];
double timesPerDigit[2][10];


int main (int argc, char** argv){
    int fired = 0;
        
    //should initialize the matrix of weights (read weight.txt), the 3d matrix of the layers, where each layer is a matrix[n][2], with the first row of membrane potential and the second one of output 
    for(int k=0; k< SAMPLES; k++){ //for each sample of the batch
        //initialize the arrays to zero at rach new sample
        double memthI[INPUTS] = {0};
        double memthH[HIDDEN] = {0};
        double memthO[OUTPUT] = {0};
        double outputO[OUTPUT]= {0};
        double outputH[HIDDEN] = {0};

        //getting the time at the start of the fc layers
        start[0] = clock();
        for(int t=0; t< TIME_STAMP; t++){ //for each time step
            //Starting fc1 of the network
            start[1] = clock();
            fullyConnected(inputSpikes[k][t], INPUTS, memthH, outputH, HIDDEN, weightsFC1);
            end[1] = clock();
            //Starting fc2 of the network
            start[2] = clock();
            fullyConnected(outputH, HIDDEN, memthO, outputO, OUTPUT, weightsFC2);
            end[2] = clock();
        }
        //getting the time at the end of the fc layers
        end[0] = clock();
        if(expectedOutputs[k] == getMax(outputO, OUTPUT)){
            fired++;
            timesPerDigit[0][expectedOutputs[k]]+= ((double) (end[0] - start[0])) / CLOCKS_PER_SEC;
            timesPerDigit[1][expectedOutputs[k]] ++;
        }
    }
    
    printf("Accuracy: %f\n", (float)fired/SAMPLES);
    printf("Time needed whole: %lf\n", ((double) (end[0] - start[0])) / CLOCKS_PER_SEC);
    printf("Time needed first fc layer: %lf\n", ((double) (end[1] - start[1])) / CLOCKS_PER_SEC);
    printf("Time needed second fc layer: %lf\n", ((double) (end[2] - start[2])) / CLOCKS_PER_SEC);

    for(int i=0; i<10; i++){
        printf("Avarage time needed for whole network: %lf\n", timesPerDigit[0][expectedOutputs[i]]/timesPerDigit[1][expectedOutputs[i]]);
    }

    return 0;
}
