#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv){
    FILE *wCL1File;
    FILE *wCL2File;
    FILE *wCL3File;
    FILE *wFC4File;
    FILE *targets;
    char fileName[100];
    char fileName2[100];
    FILE * inputFile;
    double value;
    int data;
/* 
    wFC4File = fopen("fc4Weights.txt", "r");
    targets = fopen("DeepSNNweightsFC4.txt", "w");
    //retrieving weights of first convolutional layer
    for(int k=0; k< 1280; k++){ //for each weight file in the CNN lacolumners
        fscanf(wFC4File, "%lf", &value);
        fprintf(targets, "%lf, ", value);
        if(k%9==0 && k!=0){
            fprintf(targets, "\n");
        }
    }
    fclose(wFC4File);
    fclose(targets);
    
    wCL3File = fopen("con3Weights.txt", "r");
    targets = fopen("DeepSNNweightsCL3.txt", "w");
    //retrieving weights of first convolutional layer
    for(int k=0; k< 4608; k++){ //for each weight file in the CNN lacolumners
        fscanf(wCL3File, "%lf", &value);
        fprintf(targets, "%lf, ", value);
        if(k%9==0 && k!=0){
            fprintf(targets, "\n");
        }
    }
    fclose(wCL3File);
    fclose(targets);

    wCL2File = fopen("con2Weights.txt", "r");
    targets = fopen("DeepSNNweightsCL2.txt", "w");
    //retrieving weights of first convolutional layer
    for(int k=0; k< 576; k++){ //for each weight file in the CNN lacolumners
        fscanf(wCL2File, "%lf", &value);
        fprintf(targets, "%lf, ", value);
        if(k%9==0 && k!=0){
            fprintf(targets, "\n");
        }
    }
    fclose(wCL2File);
    fclose(targets);

    wCL1File = fopen("con1Weights.txt", "r");
    targets = fopen("DeepSNNweightsCL1.txt", "w");
    //retrieving weights of first convolutional layer
    for(int k=0; k< 36; k++){ //for each weight file in the CNN lacolumners
        fscanf(wCL1File, "%lf", &value);
        fprintf(targets, "%lf, ", value);
        if(k%9==0 && k!=0){
            fprintf(targets, "\n");
        }
    }
    fclose(wCL1File);
    fclose(targets);

    inputFile = fopen("targets.txt", "r");
    targets = fopen("DeepSNNtargets.txt", "w");
    //retrieving weights of first convolutional layer
    for(int k=0; k< 128; k++){ //for each weight file in the CNN lacolumners
        fscanf(inputFile, "%lf", &value);
        fprintf(targets, "%d, ", (int)value);
        if(k%7==0 && k!=0){
            fprintf(targets, "\n");
        }
    }
    fclose(inputFile);
    fclose(targets);


    inputFile = fopen("con1Bias.txt", "r");
    targets = fopen("DeepSNNbias1.txt", "w");
    //retrieving weights of first convolutional layer
    for(int k=0; k< 4; k++){ //for each weight file in the CNN lacolumners
        fscanf(inputFile, "%lf", &value);
        fprintf(targets, "%lf, ", value);
        if(k%7==0 && k!=0){
            fprintf(targets, "\n");
        }
    }
    fclose(inputFile);
    fclose(targets);

    inputFile = fopen("con2Bias.txt", "r");
    targets = fopen("DeepSNNbias2.txt", "w");
    //retrieving weights of first convolutional layer
    for(int k=0; k< 16; k++){ //for each weight file in the CNN lacolumners
        fscanf(inputFile, "%lf", &value);
        fprintf(targets, "%lf, ", value);
        if(k%7==0 && k!=0){
            fprintf(targets, "\n");
        }
    }
    fclose(inputFile);
    fclose(targets);

    inputFile = fopen("con3Bias.txt", "r");
    targets = fopen("DeepSNNbias3.txt", "w");
    //retrieving weights of first convolutional layer
    for(int k=0; k< 32; k++){ //for each weight file in the CNN lacolumners
        fscanf(inputFile, "%lf", &value);
        fprintf(targets, "%lf, ", value);
        if(k%7==0 && k!=0){
            fprintf(targets, "\n");
        }
    }
    fclose(inputFile);
    fclose(targets);

    inputFile = fopen("fc4Bias.txt", "r");
    targets = fopen("DeepSNNbias4.txt", "w");
    //retrieving weights of first convolutional layer
    for(int k=0; k< 10; k++){ //for each weight file in the CNN lacolumners
        fscanf(inputFile, "%lf", &value);
        fprintf(targets, "%lf, ", value);
        if(k%7==0 && k!=0){
            fprintf(targets, "\n");
        }
    }
    fclose(inputFile);
    fclose(targets); */

    for(int i=16; i<128; i++){
        sprintf(fileName, "./inputs/input%d.txt", i);
        sprintf(fileName2, "DeepSNNbinput%d.txt", i);
        inputFile = fopen(fileName, "r");
        targets = fopen(fileName2, "w");
        //retrieving weights of first convolutional layer
        for(int k=0; k< 784; k++){ //for each weight file in the CNN lacolumners
            fscanf(inputFile, "%lf", &value);
            fprintf(targets, "%lf, ", value);
            if(k%14==0 && k!=0){
                fprintf(targets, "\n");
            }
        }
        fclose(inputFile);
        fclose(targets);
    }

    return 0;
}