#include <stdio.h>
#include <stdlib.h>

int max(int **p, int **e, int **pol, int s, int size, int f){
		
	int i=0;
	int j=0;
	int k=0;
	int l=0;
		
	int mm=0;
	
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			for(k=0; k<f; k++){
				for(l=0; l<f; l++){
					if(p[k+i*s][l+j*s]>mm){
						mm=p[k+i*s][l+j*s];
					}
				}
			}
			pol[i][j]=mm;
			mm=0;
		}
	}
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			printf("%d ", pol[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}

int ave(int **p, int **e, int **average, int s, int size, int f){
		
	int i=0;
	int j=0;
	int k=0;
	int l=0;
		
	int sum=0;
	
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			for(k=0; k<f; k++){
				for(l=0; l<f; l++){
					sum=sum+p[k+i*s][l+j*s];
				}
			}
			sum=sum/(f*f);
			average[i][j]=sum;
			sum=0;
		}
	}
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			printf("%d ", average[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int main(){
	
	int a=0;
	int b=0;
	int i=0;
	int j=0;
	
	int **p; //4x4
	int w=0;	
	int q=0; 
		
	int **e; //필터
	int f=0; 	
	int w1=0;
	
	int **pol; //max pooling 
	int s=0;
	
	int **average;
	
	FILE *fp;
	fp=fopen("d:/unna.pgm", "r+");
	
	FILE *fpp;
	fpp=fopen("d:/un_max.pgm", "w+");
	
	FILE *fppp;
	fppp=fopen("d:/un_ave.pgm", "w+");
	
	fseek(fp,49,SEEK_SET);
	fscanf(fp,"%d",&a);
	printf("w : %d\n",a);
	
	fseek(fp,56,SEEK_SET);
	fscanf(fp,"%d",&b);
	printf("max : %d\n",b);
	
	p=(int **)malloc(a*sizeof(int*));
	for(i=0;i<a; i++){
		*(p+i)=(int *)malloc(a*sizeof(int));
	}
	
	for(i=0;i<a;i++){
		for(j=0;j<a;j++){
			fscanf(fp,"%d",&p[i][j]);
		}
	}
//	for(i=0;i<a;i++){
//		for(j=0;j<a;j++){
//			printf("%d ",p[i][j]);	
//		}
//		printf("\n");
//	}	
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

	printf("Stride 입력:");
	scanf("%d",&s);
	
	int size=(a-f)/s+1;
	printf("pooling size : %d\n", size);
	if((a-f)%(s) != 0){
		printf("error");
		exit(0); 
	}
	
	pol=(int **)malloc(size*sizeof(int*));
	for(i=0;i<size;i++){
		*(pol+i)=(int *)malloc(size*sizeof(int));
	}
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			pol[i][j]=0;
		}
	}
	
	average=(int **)malloc(size*sizeof(int*));
	for(i=0;i<size;i++){
		*(average+i)=(int *)malloc(size*sizeof(int));
	}
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			average[i][j]=0;
		}
		printf("\n");
	}
	
    max(p, e, pol, s, size, f);
    printf("\n");
    ave(p, e, average, s, size, f);

	fprintf(fpp, "P2\n");
	fprintf(fpp, "# Created by GIMP version 2.10.14 PNM plug-in\n");
	fprintf(fpp, "%d %d\n", size, size);
	fprintf(fpp, "%d\n", b);
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			fprintf(fpp, "%d\n", pol[i][j]);
		}
	}
	
	fprintf(fppp, "P2\n");
	fprintf(fppp, "# Created by GIMP version 2.10.14 PNM plug-in\n");
	fprintf(fppp, "%d %d\n", size, size);
	fprintf(fppp, "%d\n", b);
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			fprintf(fppp, "%d\n", average[i][j]);
		}
	}	
	fclose(fp);
	fclose(fpp);
	fclose(fppp);
	
	for(i=0;i<a;i++){
		free(*(p+i));
	}
		free(p);	
	for(i=0;i<f;i++){
		free(*(e+i));
	}
		free(e);
	for(i=0;i<size;i++){
		free(*(pol+i));
	}	
		free(pol);
	for(i=0;i<size;i++){
		free(*(average+i));
	}
		free(average);	
	return 0;
}
