#include <stdio.h>
#include <stdlib.h>

int performConvolution(int **filter, int **paddedInput, int **convolutionResult, int outputSize, int filterSize, int stride){
    int i, j, k, l, sum = 0;
    for(i = 0; i < outputSize; i++){
        for(j = 0; j < outputSize; j++){
            for(k = 0; k < filterSize; k++){ 
                for(l = 0; l < filterSize; l++){ 
                    sum += paddedInput[k + i * stride][l + j * stride] * filter[k][l];
                }
            }
            if(sum >= 255){
                sum = 255;
            }
            else if(sum <= 0){
                sum = 0;
            }
            convolutionResult[i][j] = sum;
            sum = 0;
        }
    }
    printf("After Convolution\n");
    for(i = 0; i < outputSize; i++){
        for(j = 0; j < outputSize; j++){
            printf("%d ", convolutionResult[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int main(){
    int i, j;
    int **inputImage; // Original input image
    int imageSize = 0; // Size of the input image
    int **filter; // Filter for convolution
    int filterSize = 0; // Size of the filter
    int **paddedInput; // Input image after padding
    int padding = 0; // Padding size
    int **convolutionResult; // Result of the convolution
    int stride = 0; // Stride for convolution
    int outputSize = 0; // Size of the convolution result
    int maxPixelValue = 0; // Maximum pixel value for PGM format

    FILE *inputFile;
    inputFile = fopen("d:/unna.pgm", "r+");
    FILE *outputFile;
    outputFile = fopen("d:/un_con.pgm", "w+");

    // Read image size and maximum pixel value from the PGM file
    fseek(inputFile, 48, SEEK_SET);
    fscanf(inputFile, "%d", &imageSize);
    printf("Image Size: %d\n", imageSize);
    fseek(inputFile, 56, SEEK_SET);
    fscanf(inputFile, "%d", &maxPixelValue);
    printf("Max Pixel Value: %d\n", maxPixelValue);

    // Memory allocation and reading the input image
    inputImage = (int **)malloc(imageSize * sizeof(int*));
    for(i = 0; i < imageSize; i++){
        inputImage[i] = (int *)malloc(imageSize * sizeof(int));
        for(j = 0; j < imageSize; j++){
            fscanf(inputFile, "%d", &inputImage[i][j]);
        }
    }

    // Reading filter size and initializing the filter
    printf("Enter filter size: ");
    scanf("%d", &filterSize);
    filter = (int **)malloc(filterSize * sizeof(int*));
    for(i = 0; i < filterSize; i++){
        filter[i] = (int *)malloc(filterSize * sizeof(int));
        for(j = 0; j < filterSize; j++){
            printf("Enter value: ");
            scanf("%d", &filter[i][j]);
        }
    }

    // Reading padding size and initializing the padded input
    printf("Enter padding size: ");
    scanf("%d", &padding);
    paddedInput = (int **)malloc((imageSize + 2 * padding) * sizeof(int*));
    for(i = 0; i < (imageSize + 2 * padding); i++){
        paddedInput[i] = (int *)malloc((imageSize + 2 * padding) * sizeof(int));
        for(j = 0; j < (imageSize + 2 * padding); j++){
            if(i >= padding && i < imageSize + padding && j >= padding && j < imageSize + padding){
                paddedInput[i][j] = inputImage[i - padding][j - padding];
            }
            else{
                paddedInput[i][j] = 0;
            }
        }
    }

    // Reading stride and calculating output size
    printf("Enter stride: ");
    scanf("%d", &stride);
    outputSize = (imageSize - filterSize + 2 * padding) / stride + 1;
    printf("Output Size: %d\n", outputSize);
    if((imageSize - filterSize + 2 * padding) % stride != 0){
        printf("Error: Invalid dimensions");
        exit(0);
    }

    // Memory allocation for convolution result
    convolutionResult = (int **)malloc(outputSize * sizeof(int*));
    for(i = 0; i < outputSize; i++){
        convolutionResult[i] = (int *)malloc(outputSize * sizeof(int));
    }

    // Perform convolution
    performConvolution(filter, paddedInput, convolutionResult, outputSize, filterSize, stride);

    // Write the convolution result to a PGM file
    fprintf(outputFile, "P2\n");
    fprintf(outputFile, "# Created by GIMP version 2.10.14 PNM plug-in\n");
    fprintf(outputFile, "%d %d\n", outputSize, outputSize);
    fprintf(outputFile, "%d\n", maxPixelValue);
    for(i = 0; i < outputSize; i++){
        for(j = 0; j < outputSize; j++){
            fprintf(outputFile, "%d\n", convolutionResult[i][j]);
        }
    }

    // Close files and free memory
    fclose(inputFile);
    fclose(outputFile);
    for(i = 0; i < imageSize; i++){
        free(inputImage[i]);
    }
    free(inputImage);
    for(i = 0; i < filterSize; i++){
        free(filter[i]);
    }
    free(filter);
    for(i = 0; i < (imageSize + 2 * padding); i++){
        free(paddedInput[i]);
    }
    free(paddedInput);
    for(i = 0; i < outputSize; i++){
        free(convolutionResult[i]);
    }
    free(convolutionResult);

    return 0;
}

