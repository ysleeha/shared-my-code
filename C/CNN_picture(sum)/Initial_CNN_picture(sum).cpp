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
			if(sum>=255){
				sum=255;
				con[i][j]=sum;
			}
			else if(sum<=0){
				sum=0;
				con[i][j]=sum;
			}
			else{
				con[i][j]=sum;
			}
			sum=0;
		}
	}
	printf("바뀌고 난후\n");
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
	
	int a=0;
	int max=0;
	int d=0;
	
	FILE *fp;
	fp=fopen("d:/unna.pgm", "r+");
	FILE *fpp;
	fpp=fopen("d:/un_con.pgm", "w+");
	
	fseek(fp,48,SEEK_SET);
	fscanf(fp,"%d",&a);
	printf("w : %d\n",a);
	fseek(fp,56,SEEK_SET);
	fscanf(fp,"%d",&max);
	printf("max : %d\n",max);
	
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
	//WxW 할 때  
	
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
			printf("값 입력:");
			scanf("%d", &w1);
			e[i][j]=w1;
		}
	}
	printf("f의 값\n");
	for(i=0;i<f;i++){
		for(j=0;j<f;j++){
			printf("%d ",e[i][j]);	
		}
		printf("\n");
	}
	//fxf 할 때  
	
	printf("패딩 입력:");
	scanf("%d",&pad);
	t=(int **)malloc((a+(2*pad))*sizeof(int*));
	for(i=0;i<(a+(2*pad));i++){
		*(t+i)=(int *)malloc((a+(2*pad))*sizeof(int));
	}
	for(i=0;i<(a+(2*pad));i++){
		for(j=0;j<(a+(2*pad));j++){
			t[i][j]=0;
		}
	}
	printf("바뀌고 난 후\n");
	for(i=pad; i<a+pad; i++){ 
		for(j=pad; j<a+pad; j++){
			t[i][j]=p[i-pad][j-pad];
		}
	}
	for(i=0;i<(a+(2*pad));i++){
		for(j=0;j<(a+(2*pad));j++){
			printf("%d ",t[i][j]);	
		}
		printf("\n");
	}
	// padding 입력 
	
	printf("Stride 입력:");
	scanf("%d",&s);
	int size=(a-f+2*pad)/s+1;
	printf("size : %d\n", size);
	// stride 입력
	if((a-f+2*pad)%(s) != 0){
		printf("error");
		exit(0);
	}
	//에러
	 
	con=(int **)malloc(size*sizeof(int*));
	for(i=0;i<size;i++){
		*(con+i)=(int *)malloc(size*sizeof(int));
	}
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			con[i][j]=0;
		}
	}
	
	conv(e, t, con, size, f, s);

	fprintf(fpp, "P2\n");
	fprintf(fpp, "# Created by GIMP version 2.10.14 PNM plug-in\n");
	fprintf(fpp, "%d %d\n", size, size);
	fprintf(fpp, "%d\n", max);
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			fprintf(fpp, "%d\n", con[i][j]);
		}
	}
	fclose(fp);
	fclose(fpp);
	
	for(i=0;i<a;i++){
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
