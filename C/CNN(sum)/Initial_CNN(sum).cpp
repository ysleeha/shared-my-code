#include <stdio.h>
#include <stdlib.h>

int conv(int **e, int **t, int **con, int size, int f, int s){
		
	int i=0;
	int j=0;
	int k=0;
	int l=0;
	int sum=0;
	
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			for(k=0; k<f; k++){ 
				for(l=0; l<f; l++){ 
					sum=sum+t[k+i*s][l+j*s]*e[k][l];
				}
			}
			con[i][j]=sum;
			sum=0;
		}
	}
	printf("convolution 계산 후\n");
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			printf("%d ", con[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}

int main(){
	
	int i=0;
	int j=0;
	
	int **p; //4x4
	int w=0;	
	int q=0; 
		
	int **e; //필터
	int f=0; 	
	int w1=0;
		 
	int **t; //padding 
	int pad=0;
	
	int **con; //컨볼 
	int s=0;

	printf("w 사이즈 입력:");
	scanf("%d", &w);
	
	p=(int **)malloc(w*sizeof(int*));
	for(i=0;i<w; i++){
		*(p+i)=(int *)malloc(w*sizeof(int));
	}
	for(i=0;i<w;i++){
		for(j=0;j<w;j++){
			p[i][j]=0;
		}
	}
	for(i=0;i<w;i++){
		for(j=0;j<w;j++){
			printf("값 입력:");
			scanf("%d", &q);
			p[i][j]=q;
		}
	}
	printf("w의 값\n"); 
	for(i=0;i<w;i++){
		for(j=0;j<w;j++){
			printf("%d ",p[i][j]);	
		}
		printf("\n");
	}	
	//4x4
	
	printf("f사이즈 입력:");
	scanf("%d", &f);
	
	e=(int **)malloc(f*sizeof(int*));
	for(i=0;i<f;i++){
		*(e+i)=(int *)malloc(f*sizeof(int));
	}
	for(i=0;i<f;i++){
		for(j=0;j<f;j++){
			e[i][j]=0;
		}
	}
	for(i=0;i<f;i++){
		for(j=0;j<f;j++){
			printf("값 입력");
			scanf("%d", &w1);
			e[i][j]=w1;
		}
	}
	for(i=0;i<f;i++){
		for(j=0;j<f;j++){
			printf("%d ",e[i][j]);	
		}
		printf("\n");
	}
	
	//3x3
	
	printf("패딩 입력:");
	scanf("%d",&pad);
	t=(int **)malloc((w+(2*pad))*sizeof(int*));
	for(i=0;i<(w+(2*pad));i++){
		*(t+i)=(int *)malloc((w+(2*pad))*sizeof(int));
	}
	for(i=0;i<(w+(2*pad));i++){
		for(j=0;j<(w+(2*pad));j++){
			t[i][j]=0;
		}
	}
//	for(i=0;i<(w+(2*pad));i++){
//		for(j=0;j<(w+(2*pad));j++){
//			printf("%d ",t[i][j]);	
//		}
//		printf("\n");
//	}
	
	printf("바뀌고 난 후\n");
	for(i=pad; i<w+pad; i++){ 
		for(j=pad; j<w+pad; j++){
			t[i][j]=p[i-pad][j-pad];
		}
	}
	for(i=0;i<(w+(2*pad));i++){
		for(j=0;j<(w+(2*pad));j++){
			printf("%d ",t[i][j]);	
		}
		printf("\n");
	}
	
	printf("Stride 입력:");
	scanf("%d",&s);
	
	int size=(w-f+2*pad)/s+1;
	printf("size : %d\n", size);
	if((w-f+2*pad)%(s) != 0){
		printf("error");
		exit(0);
	}
	
	con=(int **)malloc(size*sizeof(int*));
	for(i=0;i<size;i++){
		*(con+i)=(int *)malloc(size*sizeof(int));
	}
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			con[i][j]=0;
		}
	}
	printf("convolution 계산 전\n");
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			printf("%d ", con[i][j]);
		}
		printf("\n");
	}
	
	conv(e, t, con, size, f, s);
	
	for(i=0;i<w;i++){
		free(*(p+i));
	}
		free(p);		
	for(i=0;i<f;i++){
		free(*(e+i));
	}
		free(e);		
	for(i=0;i<(w+(2*pad));i++){
		free(*(t+i));
	}
		free(t);
	for(i=0;i<size;i++){
		free(*(con+i));
	}	
		free(con);
	
	return 0;
}
