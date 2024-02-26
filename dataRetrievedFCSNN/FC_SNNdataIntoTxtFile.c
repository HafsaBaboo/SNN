#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "parameters.h"
//#include "DeepSNNinputs.h"
//#include "DeepSNNtargets.h"

int main(int argc, char** argv){
    FILE *wFC1File;
    FILE *wFC2File;
    FILE *targets;
    char fileName[100];
    FILE * inputFile;
    double value;

    wFC1File = fopen("../FC_SNN_weights/weightsFC1.txt", "r");
    targets = fopen("FC_SNN_weights.txt", "w");
    fprintf(targets, "\t ");
    //retrieving weights of first fully connected layer
    for(size_t j=0; j< HIDDEN*INPUTS; j++){         
        fscanf(wFC1File, "%lf", &value);
        fprintf(targets, "%lf, ", value); 
    }
    fprintf(targets, "\n\n\n ");
    fprintf(targets, "\t ");
    //retrieving weights of second fully connected  layer
    wFC2File = fopen("../FC_SNN_weights/weightsFC2.txt", "r");
    for(size_t j=0; j< OUTPUT*HIDDEN; j++){
        fscanf(wFC2File, "%lf", &value);
        fprintf(targets, "%lf, ", value);
    }
    fclose(wFC1File);
    fclose(wFC2File);
    fclose(targets);

    targets = fopen("FC_SNN_inputs.txt", "w");
    fprintf(targets, "{\n ");
    for(int k=0; k< SAMPLES; k++){ //for each sample in the batch
        fprintf(targets, " {\n ");
        for(int i =0; i<TIME_STAMP; i++){ //for each time stamp 
            sprintf(fileName, "../FC_SNNinputs/sample%d/inpute%d_%d.txt", k, k, i);
            inputFile = fopen(fileName, "r");
            fprintf(targets, "\t{");
            for(int j =0; j<INPUTS; j++){ //for each inputIMG pixel in the sample
            fscanf(inputFile, "%lf", &value);
                if(j%9==0){
                    fprintf(targets, "\n\t ");
                }
                if(j==(INPUTS-1) && i==(TIME_STAMP-1)){
                        fprintf(targets, "%lf }\n\t},", value);
                }else{
                    if(j==(INPUTS-1)){
                        fprintf(targets, "%lf } ,", value);
                    }else{
                        fprintf(targets, "%lf, ", value);
                    }
                }
            }
            fclose(inputFile);
        }    
    }
    fprintf(targets, "}");
    fclose(targets);
 
    targets = fopen("FC_SNNbatchTest.txt", "w");
    inputFile = fopen("../FC_SNNbatchTest.txt", "r");
    fprintf(targets, "\t ");
    for(size_t j=0; j< SAMPLES; j++){
        fscanf(inputFile, "%lf", &value); 
        if(j%9==0){
                fprintf(targets, "\n\t ");
            }
        fprintf(targets, "%d, ", (int)value);
    }
    fclose(inputFile);
    fclose(targets);
 
    return 0;
}