#include <stdio.h>
#include <stdlib.h>

// Function to perform max pooling
int max(int **inputMatrix, int **filter, int **maxPoolingMatrix, int stride, int poolingSize, int filterSize){
    int i, j, k, l;
    int maxVal = 0;
    for(i = 0; i < poolingSize; i++){
        for(j = 0; j < poolingSize; j++){
            // Reset max value for each pooling window
		    maxVal = 0; 
		    
            // Iterate over the filter window
            for(k = 0; k < filterSize; k++){
                for(l = 0; l < filterSize; l++){
                    // Compare and store the maximum value in the window
                    if(inputMatrix[k + i * stride][l + j * stride] > maxVal){
                        maxVal = inputMatrix[k + i * stride][l + j * stride];
                    }
                }
            }
            // Assign the max value to the pooling matrix
            maxPoolingMatrix[i][j] = maxVal; 
        }
    }
    // Print the resulting max pooling matrix
    for(i = 0; i < poolingSize; i++){
        for(j = 0; j < poolingSize; j++){
            printf("%d ", maxPoolingMatrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}

// Function to perform average pooling
int ave(int **inputMatrix, int **filter, int **averagePoolingMatrix, int stride, int poolingSize, int filterSize){
    int i, j, k, l;
    int sum = 0;
    for(i = 0; i < poolingSize; i++){
        for(j = 0; j < poolingSize; j++){
        	// Reset sum for each pooling window
            sum = 0;
            
            // Iterate over the filter window
            for(k = 0; k < filterSize; k++){
                for(l = 0; l < filterSize; l++){
                    // Sum up the values in the window
                    sum += inputMatrix[k + i * stride][l + j * stride];
                }
            }
            // Calculate and store the average value in the window
            averagePoolingMatrix[i][j] = sum / (filterSize * filterSize);
        }
    }
    // Print the resulting average pooling matrix
    for(i = 0; i < poolingSize; i++){
        for(j = 0; j < poolingSize; j++){
            printf("%d ", averagePoolingMatrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int main(){
    int i, j;
    int **inputMatrix; // Input image matrix
    int imageSize = 0; // Size of input image
    int tempValue = 0; // Temporary input value

    int **filterMatrix; // Filter matrix
    int filterSize = 0; // Size of the filter
    int stride = 0; // Stride for pooling

    int **maxPoolingMatrix; // Result of max pooling
    int **averagePoolingMatrix; // Result of average pooling

    // File pointers for reading and writing images
    FILE *inputFile = fopen("d:/unna.pgm", "r+");
    FILE *maxOutputFile = fopen("d:/un_max.pgm", "w+");
    FILE *aveOutputFile = fopen("d:/un_ave.pgm", "w+");

    // Reading image size and maximum brightness from the file
    fseek(inputFile, 49, SEEK_SET);
    fscanf(inputFile, "%d", &imageSize);
    printf("Image size: %d\n", imageSize);

    int maxBrightness = 0;
    fseek(inputFile, 56, SEEK_SET);
    fscanf(inputFile, "%d", &maxBrightness);
    printf("Max brightness: %d\n", maxBrightness);

    // Memory allocation and reading the image
    inputMatrix = (int **)malloc(imageSize * sizeof(int*));
    for(i = 0; i < imageSize; i++){
        inputMatrix[i] = (int *)malloc(imageSize * sizeof(int));
    }
    for(i = 0; i < imageSize; i++){
        for(j = 0; j < imageSize; j++){
            fscanf(inputFile, "%d", &inputMatrix[i][j]);
        }
    }

    // Input filter size and allocate memory for filter
    printf("Enter filter size: ");
    scanf("%d", &filterSize);
    filterMatrix = (int **)malloc(filterSize * sizeof(int*));
    for(i = 0; i < filterSize; i++){
        filterMatrix[i] = (int *)malloc(filterSize * sizeof(int));
    }

    // Enter stride for pooling
    printf("Enter stride: ");
    scanf("%d", &stride);

    // Calculate pooling size and validate dimensions
    int poolingSize = (imageSize - filterSize) / stride + 1;
    printf("Pooling size: %d\n", poolingSize);
    if((imageSize - filterSize) % stride != 0){
        printf("Error in dimensions.\n");
        exit(0);
    }

    // Allocate memory for max and average pooling matrices
    maxPoolingMatrix = (int **)malloc(poolingSize * sizeof(int*));
    averagePoolingMatrix = (int **)malloc(poolingSize * sizeof(int*));
    for(i = 0; i < poolingSize; i++){
        maxPoolingMatrix[i] = (int *)malloc(poolingSize * sizeof(int));
        averagePoolingMatrix[i] = (int *)malloc(poolingSize * sizeof(int));
    }

    // Perform max pooling and average pooling
    max(inputMatrix, filterMatrix, maxPoolingMatrix, stride, poolingSize, filterSize);
    ave(inputMatrix, filterMatrix, averagePoolingMatrix, stride, poolingSize, filterSize);

    // Write max pooling result to file
    fprintf(maxOutputFile, "P2\n");
    fprintf(maxOutputFile, "# Created by GIMP version 2.10.14 PNM plug-in\n");
    fprintf(maxOutputFile, "%d %d\n", poolingSize, poolingSize);
    fprintf(maxOutputFile, "%d\n", maxBrightness);
    for(i = 0; i < poolingSize; i++){
        for(j = 0; j < poolingSize; j++){
            fprintf(maxOutputFile, "%d\n", maxPoolingMatrix[i][j]);
        }
    }

    // Write average pooling result to file
    fprintf(aveOutputFile, "P2\n");
    fprintf(aveOutputFile, "# Created by GIMP version 2.10.14 PNM plug-in\n");
    fprintf(aveOutputFile, "%d %d\n", poolingSize, poolingSize);
    fprintf(aveOutputFile, "%d\n", maxBrightness);
    for(i = 0; i < poolingSize; i++){
        for(j = 0; j < poolingSize; j++){
            fprintf(aveOutputFile, "%d\n", averagePoolingMatrix[i][j]);
        }
    }

    // Close files and free memory
    fclose(inputFile);
    fclose(maxOutputFile);
    fclose(aveOutputFile);
    for(i = 0; i < imageSize; i++){
        free(inputMatrix[i]);
    }
    free(inputMatrix);
    for(i = 0; i < filterSize; i++){
        free(filterMatrix[i]);
    }
    free(filterMatrix);
    for(i = 0; i < poolingSize; i++){
        free(maxPoolingMatrix[i]);
        free(averagePoolingMatrix[i]);
    }
    free(maxPoolingMatrix);
    free(averagePoolingMatrix);

    return 0;
}

