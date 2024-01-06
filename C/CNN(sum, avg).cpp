#include <stdio.h>
#include <stdlib.h>

int applyConvolution(int **filterMatrix, int **paddedMatrix, int **convolutionMatrix, int size, int filterSize, int stride){
    int i, j, k, l;
    int sum = 0;
    
	// ex) inputsize : 3, filtersize : 2, padding : 1, stride : 1
	// convoltion space i & j
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
        	// filter space i&j 
            for(k = 0; k < filterSize; k++){ 
                for(l = 0; l < filterSize; l++){ 
                	// multiply the same rows and columns 
                    sum = sum + paddedMatrix[k + (i * stride)][l + (j * stride)] * filterMatrix[k][l];
                }
            }
            convolutionMatrix[i][j] = sum;
            sum = 0;
        }
    }
    
    //print convolutionMatrix
    printf("Convolution result:\n");
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            printf("%d ", convolutionMatrix[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}

int main(){
    int i, j;
    int inputSize, filterSize, padding, stride;
    int tempInput, tempFilter;

    printf("Enter size of input matrix: ");
    scanf("%d", &inputSize);
	
	// create data of row[i] and column[j] space 
    int **inputMatrix = (int **)malloc(inputSize * sizeof(int*));
    for(i = 0; i < inputSize; i++){
        inputMatrix[i] = (int *)malloc(inputSize * sizeof(int));
    }

    // write and read input matrix
    for(i = 0; i < inputSize; i++){
        for(j = 0; j < inputSize; j++){
            printf("Enter value: ");
            scanf("%d", &tempInput);
            inputMatrix[i][j] = tempInput;
        }
    }

    // Print data matrix
    printf("Input matrix:\n"); 
    for(i = 0; i < inputSize; i++){
        for(j = 0; j < inputSize; j++){
            printf("%d ", inputMatrix[i][j]);    
        }
        printf("\n");
    }
	

    printf("Enter size of filter matrix: ");
    scanf("%d", &filterSize);
    
	// create filter of row[i] and column[j] space 
    int **filterMatrix = (int **)malloc(filterSize * sizeof(int*));
    for(i = 0; i < filterSize; i++){
        filterMatrix[i] = (int *)malloc(filterSize * sizeof(int));
    }

    // write and read filter matrix
    for(i = 0; i < filterSize; i++){
        for(j = 0; j < filterSize; j++){
            printf("Enter value: ");
            scanf("%d", &tempFilter);
            filterMatrix[i][j] = tempFilter;
        }
    }

    // Print filter matrix
    printf("Filter matrix:\n");
    for(i = 0; i < filterSize; i++){
        for(j = 0; j < filterSize; j++){
            printf("%d ", filterMatrix[i][j]);    
        }
        printf("\n");
    }
  
    printf("Enter padding: ");
    scanf("%d", &padding);
	
	// create padding of row[i] and column[j] space
	// padding is adding zero next to data value
    int paddedSize = inputSize + 2 * padding;
    int **paddedMatrix = (int **)malloc(paddedSize * sizeof(int*));
    for(i = 0; i < paddedSize; i++){
        paddedMatrix[i] = (int *)malloc(paddedSize * sizeof(int));
    }
    
    // Initialize of padding space
    for(i = 0; i < paddedSize; i++){
        for(j = 0; j < paddedSize; j++){
            paddedMatrix[i][j] = 0;
        }
    }

    // Apply input data to padding space.
    for(i = padding; i < inputSize + padding; i++){ 
        for(j = padding; j < inputSize + padding; j++){
            paddedMatrix[i][j] = inputMatrix[i - padding][j - padding];
        }
    }

    // Print padded matrix(real value)
    printf("Padded matrix:\n");
    for(i = 0; i < paddedSize; i++){
        for(j = 0; j < paddedSize; j++){
            printf("%d ", paddedMatrix[i][j]);    
        }
        printf("\n");
    }

    printf("Enter stride: ");
    scanf("%d", &stride);
	
	// ex) inputsize : 3, filtersize : 2, padding : 1, stride : 1
	// create inputSize, adding padding value, filtering by stride value 
	int convolutionSize = ((inputSize + (2 * padding) - filterSize) / stride) + 1;
    printf("Convolution matrix size: %d\n", convolutionSize);
    
	// Determine error by filter traverses. 
	if((inputSize + (2 * padding) - filterSize) % stride != 0){
	    printf("Error in dimensions.\n");
	    exit(0);
	}
	
	// create convolutionMatrix of row[i] and column[j] space 
    int **convolutionMatrix = (int **)malloc(convolutionSize * sizeof(int*));
    for(i = 0; i < convolutionSize; i++){
        convolutionMatrix[i] = (int *)malloc(convolutionSize * sizeof(int));
    }
    
    // Initialize convolution matrix
    for(i = 0; i < convolutionSize; i++){
        for(j = 0; j < convolutionSize; j++){
            convolutionMatrix[i][j] = 0;
        }
    }

    // Apply convolution
    applyConvolution(filterMatrix, paddedMatrix, convolutionMatrix, convolutionSize, filterSize, stride);

    // Free allocated memory
    for(i = 0; i < inputSize; i++){
        free(inputMatrix[i]);
    }
    free(inputMatrix);

    for(i = 0; i < filterSize; i++){
        free(filterMatrix[i]);
    }
    free(filterMatrix);

    for(i = 0; i < paddedSize; i++){
        free(paddedMatrix[i]);
    }
    free(paddedMatrix);

    for(i = 0; i < convolutionSize; i++){
        free(convolutionMatrix[i]);
    }
    free(convolutionMatrix);

    return 0;
}

