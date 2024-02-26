    #include <stddef.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <string.h>
    #include <time.h>
    #include <math.h>
    #include "./includes/parameters.h"
    #include "./includes/functions.h"
    #include "./includes/DeepSNNinputs.h"
    #include "./includes/DeepSNNweights.h"
    #include "./includes/DeepSNNtargets.h"


    int main(int argc, char** argv){
        int fired = 0;
        clock_t start, end;
        clock_t start_1, end_1, start_2, end_2, start_3, end_3, start_4, end_4;
        double requiredTime=0, requiredTime1=0, requiredTime2=0, requiredTime3=0, requiredTime4=0;
        double timesPerDigit[2][10];

        for(int j=0; j<SAMPLES;j++){
            double output[14*14*4] = {0};
            double memTh[14*14*4] = {0};
            double output2[7*7*16] = {0};
            double memTh2[7*7*16] = {0};
            double output3[2*2*32] = {0};
            double memTh3[2*2*32] = {0};
            double output4[OUTPUT] = {0};
            double memTh4[OUTPUT] = {0};
            
            start = clock();
            for(int i=0; i<TIME_STAMP;i++){
                start_1 = clock();
                int dim = leakingConvolutionalLayer(inputSpikes[j], INPUT_IMAGE, W_FEATURE_MAP, output, OUTPUT_CNN_1, weightsCL1, W_KERNEL, PADDING, STRIDE_2, memTh, biasCL1);
                end_1 = clock();
                int rowsDim1 = sqrt(dim/OUTPUT_CNN_1);
                start_2 = clock();
                int dim2 = leakingConvolutionalLayer(output, OUTPUT_CNN_1, rowsDim1, output2, OUTPUT_CNN_2, weightsCL2, W_KERNEL, PADDING, STRIDE_2, memTh2, biasCL2);
                end_2 = clock();
                int rowsDim2 = sqrt(dim2/OUTPUT_CNN_2);
                start_3 = clock();
                int dim3 = leakingConvolutionalLayer(output2, OUTPUT_CNN_2, rowsDim2, output3, OUTPUT_CNN_3, weightsCL3, W_KERNEL, PADDING, STRIDE_4, memTh3, biasCL3);
                end_3 = clock();
                int rowsDim3 = sqrt(dim3/OUTPUT_CNN_3);
                start_4 = clock();
                fullyConnected(output3, dim3, memTh4, output4, OUTPUT_FC_4, weightsFC4);
                end_4 = clock();
            }
            end = clock();

            if(expectedOutputs[j] == getMax(output4, OUTPUT_FC_4)){
                fired++;
            }
            requiredTime += ((double)(end - start) / CLOCKS_PER_SEC);
            requiredTime1 += ((double)(end_1 - start_1) / CLOCKS_PER_SEC);
            requiredTime2 += ((double)(end_2 - start_2) / CLOCKS_PER_SEC);
            requiredTime3 += ((double)(end_3 - start_3) / CLOCKS_PER_SEC);
            requiredTime4 += ((double)(end_4 - start_4) / CLOCKS_PER_SEC);

            if(expectedOutputs[j] == getMax(output4, OUTPUT_FC_4)){
                timesPerDigit[0][expectedOutputs[j]]+= ((double) (end - start)) / CLOCKS_PER_SEC;
                timesPerDigit[1][expectedOutputs[j]] ++;
            }
        }

        printf("Accuracy: %f\n", (float)fired/SAMPLES);
        printf("Time required avarage: %lf\n", (requiredTime/SAMPLES));
        printf("Time required avarage layer 1: %lf\n", (requiredTime1/SAMPLES));
        printf("Time required avarage layer 2: %lf\n", (requiredTime2/SAMPLES));
        printf("Time required avarage layer 3: %lf\n", (requiredTime3/SAMPLES));
        printf("Time required avarage layer 4: %lf\n", (requiredTime4/SAMPLES));

        for(int i=0; i<10; i++){
            printf("Avarage time needed for whole network ofr %d: %lf\n", i, timesPerDigit[0][expectedOutputs[i]]/timesPerDigit[1][expectedOutputs[i]]);
        }

        return 0;
    }
