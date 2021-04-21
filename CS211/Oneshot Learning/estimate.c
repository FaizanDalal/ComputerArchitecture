#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void freeMatrix(double** matrix, int n)
{
    int i;
    double* current;
    for(i = 0; i < n; i++)
    {
        current = matrix[i];
        free(current);
        current = NULL;
    }
    free(matrix);
    matrix = NULL;
}

void printMatrix(double **matrix, int n, int k){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < k; j++){
			printf("%0.0lf", matrix[i][j]);
		}
		printf("\n");
	}
	return;
}

double** transpose(double **X, int r, int c){
  int i;
  int j;
  double **A = NULL;
  A = (double**) malloc(c * sizeof(double*));
  for(i=0;i<c;i++){
    A[i] = (double*) malloc(r * sizeof(double));
  }
  for(i=0;i<r;i++){
    for(j=0;j<c;j++){
      A[j][i] = X[i][j];
    }
  }
  return A;
}

double** multiply(double**mat,int row,int col,double**mat1,int row1,int col1){

	if(col != row1){
      return NULL;
  }
  else {
    	double** result;
  		result = (double**)malloc(row*sizeof(double*));
  		for(int i=0;i<row;i++){
           result[i] = (double*)malloc(col1*sizeof(double));
		}

  		for(int i=0;i<row;i++){

  			   for(int j=0;j<col1;j++){

                 result[i][j]=0;
  				       for(int k=0;k<col;k++){

                        result[i][j]+= (mat[i][k]*mat1[k][j]);

                 }

  			   }

      }

      return result;
  }

}
double** inverse(double** matrix, int n)
{
    int i, j, k, v, count = n;
    double counter; 
    double cols= 2*n;
    double ** matrixInv;
	matrixInv = (double**) malloc(n * sizeof(double*));
		for (i = 0; i <n; i++) { 
			matrixInv[i] = (double*) malloc(cols * sizeof(double));
		}
    double ** finalinverse;
	finalinverse = (double **) malloc (n * sizeof(double*));

	for (i = 0; i < n; i++) {
		finalinverse[i] = (double*) malloc (n * sizeof(double));
	}
    for(i = 0; i < n; i++){
        for(j = 0; j < (cols); j++){
            if(j == count){
                matrixInv[i][j] = 1.000000;
            }
            else if(j > (n-1)){
                matrixInv[i][j] = 0.000000;
            }
            else{
                matrixInv[i][j] = matrix[i][j];
            }
        }
        count++;
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){   
            if(i > j){
                continue;
            }
            if(i==j && matrixInv[i][j] != 1.000000){ 
                   counter = matrixInv[i][j]; 
                   for(k = 0; k < (cols); k++){
                       matrixInv[i][k] = matrixInv[i][k] / counter;
                   }
                   continue;
            }
            else if(i!=j && matrixInv[j][i] != 0.000000){
                for(v = j; v < n; v++){   
                    counter = matrixInv[v][i];
                    for(k = 0; k < (cols); k++){
                        matrixInv[v][k] = matrixInv[v][k] + ((-1*counter)* matrixInv[j-1][k]);
                    }
                }
                continue;
            }
        }
    }
    for(i = (n-2); i > -1; i--){
        for(j = (n-1); matrixInv[i][j] != 1.000000; j--){
            for(v = i; v > -1; v--){
                counter = matrixInv[i][j];
                for(k = 0; k < (cols); k++){
                    matrixInv[v][k] = matrixInv[v][k] + ((-1*counter)* matrixInv[j][k]);
                }
            }
        }
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            finalinverse[i][j] = matrixInv[i][j+n];
        }
    }
    freeMatrix(matrixInv, n);
    return finalinverse; 
}

double** predict(double** matrix1, int n1, int m1, double** matrix2, int n2, int m2)
{
    int i,j;
    double** estimate;
    estimate=(double**) malloc(n1* sizeof(double*));

			for (i = 0; i < n1; i++)
					{
						estimate[i]=(double*) malloc(1* sizeof(double));
					}


    for(i = 0; i < n1; i++){
        for(j = 0; j < n2 ;j++){
            if(j == 0){
                estimate[i][0] = matrix2[j][0];
                continue;
            }
            else{
                estimate[i][0] += (matrix2[j][0] * matrix1[i][j-1]);
                continue;
            }
        }
    }
    return estimate;
}

int main(int argc, char *argv[]){
	if (argc != 3){
		printf("error\n");
		exit(0);
	}
	FILE *fp = fopen(argv[1], "r");
	if(fp==NULL)
	{
		exit(0);
	}
	FILE *ptr = fopen(argv[2], "r");
	if(ptr == NULL){	
		exit(0);
	}
	char word[10];
	int k, n, k1, n1, i, j;
	double number;
	fscanf(fp, "%s\n", word);
	fscanf(ptr, "%s\n", word);

	fscanf(fp, "%d\n", &k);
	fscanf(ptr, "%d\n", &k1);

	fscanf(fp, "%d\n", &n);
	fscanf(ptr, "%d\n", &n1);

	double** X;
  		X = (double**)malloc(n*sizeof(double*));
  		int a;
  		for(a=0;a<n;a++){

           X[a] = (double*)malloc((k+1)*sizeof(double));

      }
      double** Y;
  		Y = (double**)malloc(n*sizeof(double*));
  		int b;
  		for(b=0;b<n;b++){

           Y[b] = (double*)malloc(1*sizeof(double));

      }
      double** Data;
  		Data = (double**)malloc(n1*sizeof(double*));
  		int c;
  		for(c=0;c<n1;c++){

           Data[c] = (double*)malloc(k1*sizeof(double));

      }
	for(i = 0; i < n; i++){
		for(j = 0; j < k+2; j++){
			if(j == 0){	
				X[i][j] = 1.0;
				if(i < n1){
					fscanf(ptr, "%lf ", &number);
					Data[i][j] = number;
				}
			}
			else if(j == k+1){
				fscanf(fp, "%lf\n", &number);
				Y[i][0] = number;
			}else{
				fscanf(fp, "%lf ", &number);
				X[i][j] = number;
				if(i < n1 && j == k1-1){ 
					fscanf(ptr, "%lf\n", &number);
					Data[i][j] = number;				
				}
				else if(i < n1 && j < k1){ 
					fscanf(ptr, "%lf ", &number);
                    Data[i][j] = number;
				}
			}
		}
	}
	fclose(fp); fclose(ptr);

	double **transposeMatrix = transpose(X, n, k+1);
	double **multMatrix = multiply(transposeMatrix, (k+1), n, X, n, (k+1));
	double **inverseMatrix = inverse(multMatrix, k+1);
	double **finishE = multiply(inverseMatrix, k+1, k+1, transposeMatrix, k+1, n);
	double **weights = multiply(finishE, k+1, n, Y, n, 1);
	double **housePrice = predict(Data, n1, k1, weights, k+1, 1);
	printMatrix(housePrice, n1, 1);
    freeMatrix(X, n);
    freeMatrix(Y, n);
    freeMatrix(Data, n1);
    freeMatrix(transposeMatrix, k+1);
    freeMatrix(multMatrix, k+1);
    freeMatrix(inverseMatrix, k+1);
    freeMatrix(finishE, k+1);
    freeMatrix(weights, k+1);
    freeMatrix(housePrice, n1);
	return 0;
}