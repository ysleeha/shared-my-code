#include <stdio.h>
#include <stdlib.h>

// Function maxPooling: Performs max pooling on the input matrix
// inputMatrix: The input matrix, filterMatrix: The filter matrix (currently unused),
// maxPoolingMatrix: Matrix to store the max pooling results, stride: The stride value,
// poolingSize: Size of the pooling result matrix, filterSize: Size of the filter
int maxPooling(int **inputMatrix, int **filterMatrix, int **maxPoolingMatrix, int stride, int poolingSize, int filterSize){
    int i, j, k, l, maxValue = 0;
    
    for(i = 0; i < poolingSize; i++){
        for(j = 0; j < poolingSize; j++){
            for(k = 0; k < filterSize; k++){
                for(l = 0; l < filterSize; l++){
                    // Find the maximum value in the current window
                    if(inputMatrix[k + i * stride][l + j * stride] > maxValue){
                        maxValue = inputMatrix[k + i * stride][l + j * stride];
                    }
                }
            }
            // Store the maximum value in the pooling matrix
            maxPoolingMatrix[i][j] = maxValue;
            maxValue = 0; // Reset the maximum value
        }
    }

    // Print the max pooling results
    printf("Max Pooling Values\n");
    for(i = 0; i < poolingSize; i++){
        for(j = 0; j < poolingSize; j++){
            printf("%d ", maxPoolingMatrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}

// Function averagePooling: Performs average pooling on the input matrix
// inputMatrix: The input matrix, filterMatrix: The filter matrix (currently unused),
// averagePoolingMatrix: Matrix to store the average pooling results, stride: The stride value,
// poolingSize: Size of the pooling result matrix, filterSize: Size of the filter
int averagePooling(int **inputMatrix, int **filterMatrix, int **averagePoolingMatrix, int stride, int poolingSize, int filterSize){
    int i, j, k, l, sumValue = 0;
    
    for(i = 0; i < poolingSize; i++){
        for(j = 0; j < poolingSize; j++){
            for(k = 0; k < filterSize; k++){
                for(l = 0; l < filterSize; l++){
                    // Sum up the values in the current window
                    sumValue += inputMatrix[k + i * stride][l + j * stride];
                }
            }
            // Calculate the average and store it in the pooling matrix
            averagePoolingMatrix[i][j] = sumValue / (filterSize * filterSize);
            sumValue = 0; // Reset the sum
        }
    }

    // Print the average pooling results
    printf("Average Pooling Values\n");
    for(i = 0; i < poolingSize; i++){
        for(j = 0; j < poolingSize; j++){
            printf("%d ", averagePoolingMatrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int main(){
    int inputSize, filterSize, stride, inputValue, poolingSize = 0;
    int **inputMatrix, **filterMatrix, **maxPoolingMatrix, **averagePoolingMatrix;
    int i, j = 0;

    // Get the size of the input matrix from the user
    printf("Enter input matrix size: ");
    scanf("%d", &inputSize);

    // Allocate memory for the input matrix
    inputMatrix = (int **)malloc(inputSize * sizeof(int*));
    for(i = 0; i < inputSize; i++){
        inputMatrix[i] = (int *)malloc(inputSize * sizeof(int));
    }

    // Fill the input matrix with user-provided values
    for(i = 0; i < inputSize; i++){
        for(j = 0; j < inputSize; j++){
            printf("Enter value: ");
            scanf("%d", &inputValue);
            inputMatrix[i][j] = inputValue;
        }
    }

    // Print the input matrix
    printf("Input Matrix\n");
    for(i = 0; i < inputSize; i++){
        for(j = 0; j < inputSize; j++){
            printf("%d ", inputMatrix[i][j]);
        }
        printf("\n");
    }

    // Get the filter size from the user
    printf("Enter filter size: ");
    scanf("%d", &filterSize);

    // Allocate memory for the filter matrix
    filterMatrix = (int **)malloc(filterSize * sizeof(int*));
    for(i = 0; i < filterSize; i++){
        filterMatrix[i] = (int *)malloc(filterSize * sizeof(int));
    }

    // Get the stride value from the user
    printf("Enter stride: ");
    scanf("%d", &stride);

    // Calculate the size of the pooling result matrix
    poolingSize = (inputSize - filterSize) / stride + 1;
    printf("Pooling size: %d\n", poolingSize);

    // Check for valid dimensions
    if((inputSize - filterSize) % stride != 0){
        printf("Error: Invalid dimensions");
        exit(0); 
    }

    // Allocate memory for the max and average pooling matrices
    maxPoolingMatrix = (int **)malloc(poolingSize * sizeof(int*));
    for(i = 0; i < poolingSize; i++){
        maxPoolingMatrix[i] = (int *)malloc(poolingSize * sizeof(int));
    }

    averagePoolingMatrix = (int **)malloc(poolingSize * sizeof(int*));
    for(i = 0; i < poolingSize; i++){
        averagePoolingMatrix[i] = (int *)malloc(poolingSize * sizeof(int));
    }

    // Perform max and average pooling
    maxPooling(inputMatrix, filterMatrix, maxPoolingMatrix, stride, poolingSize, filterSize);
    averagePooling(inputMatrix, filterMatrix, averagePoolingMatrix, stride, poolingSize, filterSize);

    // Free allocated memory
    for(i = 0; i < inputSize; i++){
        free(inputMatrix[i]);
    }
    free(inputMatrix);

    for(i = 0; i < filterSize; i++){
        free(filterMatrix[i]);
    }
    free(filterMatrix);

    for(i = 0; i < poolingSize; i++){
        free(maxPoolingMatrix[i]);
    }
    free(maxPoolingMatrix);

    for(i = 0; i < poolingSize; i++){
        free(averagePoolingMatrix[i]);
    }
    free(averagePoolingMatrix);

    return 0;
}

