#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define XOS "WIN"

//Para usar no dev++, clique em tools/Compiler Options e adicione o parametro -std=c99 ao lado de -static-libgcc, ficando assim : -static-libgcc -std=c99

void showMatrix(int **matrix, int row, int column, char *matrixName);
void executeOption(char *name, int option, int r, int c, int **matrixA, int **matrixB);
void sumMatrix(int **matrixA, int **matrixB, int row, int column);
void subtractMatrix(int **matrixA, int **matrixB, int row, int column);
void multiplyMatrix(int **matrixA, int **matrixB, int row, int column);
void populateMatrix(int **matrix, int yLength, int xLength);
void cleanScreen();
void flush();

void main(void) {
    char ra[] = "1234067";
    char name[100];
    int option;
    int r=5;
    int c=5;
    int **matrixA;
    int **matrixB;
    int valid;

    matrixA = malloc(r*sizeof(int*));
    for(int i=0; i<r; i++) {
        matrixA[i] = (int*)malloc(c*sizeof(int));
    }

    matrixB = malloc(r*sizeof(int*));
    for(int i=0; i<r; i++) {
        matrixB[i] = (int*)malloc(c*sizeof(int));
    }

    do{
        printf("\t\tMaicon Almeida, RA: %s", ra);
        printf("\n\nDigite o seu nome:");
        scanf("%s", name);
    } while(strlen(name) == 0);

    printf("=====================================================\n");

    printf("Matrix A\n");
    populateMatrix(matrixA, r, c);

    printf("Matrix B\n");
    populateMatrix(matrixB, r, c);
    
    do{
        valid = 0;
        cleanScreen();
        printf("%s, digite uma opção\n", name);
        printf("1 - A + B\n");
        printf("2 - A - B\n");
        printf("3 - B - A\n");
        printf("4 - A x B\n");
        printf("5 - Det A\n");
        printf("6 - Det B\n");
        printf("7 - Sair\n");
        valid = scanf("%d", &option);
        flush();
        if(!valid) {
            printf("%s, digite uma opcao valida\n", name);
            printf("\nPresione ENTER para continuar");
            scanf("c\n");
            continue;
        }

        executeOption(name, option, r, c, matrixA, matrixB);
    } while(option != 7);
}

void flush() {
    if(XOS == "WIN") {
        fflush(stdin);
    } else {
        __fpurge(stdin);
    }
}

void cleanScreen(){
    if(XOS == "WIN")
        system("cls");
    else        
        system("clear");
}

void multiplyMatrix(int **matrixA, int **matrixB, int row, int column) {
    int **matrixResult;
    matrixResult = malloc(row*sizeof(int*));
    for(int i=0; i<row; i++) {
        matrixResult[i] = (int*)malloc(column*sizeof(int));
    }
    
   	int i, j, k;
	for(i = 0; i < row; ++i)
	{
		for(j = 0; j < column; ++j)
		{
			matrixResult[i][j] = 0;
		}
	}

	for(i = 0; i < row; ++i)
	{
		for(j = 0; j < column; ++j)
		{
			for(k=0; k< column; ++k)
			{
				matrixResult[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}

    cleanScreen();
    showMatrix(matrixA, row, column, "A");  
    printf("\n");
    showMatrix(matrixB, row, column, "B");  
    printf("\n");
    showMatrix(matrixResult, row, column, "resultado");  
    free(matrixResult);  
}

void populateMatrix(int **matrix, int yLength, int xLength) {
    for(int i = 0; i < yLength; i++) {
        for(int j = 0; j < xLength; j++) {
            int num = 0;
            printf("\nDigite um numero para a posicao: %d, %d\n", i, j);
            if(scanf("%d", &num) != 1) {
                printf("\nDigite um numero por favor\n");
                j--;
                num=0;
                flush();
                continue;
            }

            matrix[i][j] = num;
        }
    }
}

void executeOption(char *name, int option, int r, int c, int **matrixA, int **matrixB) {
    switch(option) {
        case 1: {
            sumMatrix(matrixA, matrixB, r, c);
        }
        break;
        case 2: {
            subtractMatrix(matrixA, matrixB, r, c);
        }
        break;
        case 3: {
            subtractMatrix(matrixB, matrixA, r, c);
        }
        break;
        case 4: {
            multiplyMatrix(matrixA, matrixB, r, c);
        }
        break;        
        case 5: {
            cleanScreen();
            showMatrix(matrixA, r, c, "A");
        }
        break;
        case 6: {
            cleanScreen();
            showMatrix(matrixB, r, c, "B");
        }
        break;
        case 7:
            printf("%s, obrigado por usar o sistema\n", name);
            return;
        default:
            printf("%s, digite uma opcao valida\n", name);
        break;
    }

    printf("\nPresione ENTER para continuar");
    scanf("c\n");
}

void showMatrix(int **matrix, int row, int column, char *matrixName) {
    printf("Matriz %s\n", matrixName);
    for (int i = 0; i < row; i++) {
      printf("\n|");
      for (int j = 0 ; j < column; j++) {
         printf("%d|", matrix[i][j]);
      }

      printf("\n");
   }
}

void sumMatrix(int **matrixA, int **matrixB, int row, int column) {
    int **matrixResult;
    matrixResult = malloc(row*sizeof(int*));
    for(int i=0; i<row; i++) {
        matrixResult[i] = (int*)malloc(column*sizeof(int));
    }

    for (int i = 0; i < row; i++) {
      for (int j = 0 ; j < column; j++) {
         matrixResult[i][j] = matrixA[i][j] + matrixB[i][j];
      }
   }

    cleanScreen();
    showMatrix(matrixA, row, column, "A");  
    printf("\n");
    showMatrix(matrixB, row, column, "B");  
    printf("\n");
    showMatrix(matrixResult, row, column, "resultado");  
    free(matrixResult);  
}

void subtractMatrix(int **matrixA, int **matrixB, int row, int column) {
    int **matrixResult;
    matrixResult = malloc(row*sizeof(int*));
    for(int i=0; i<row; i++) {
        matrixResult[i] = (int*)malloc(column*sizeof(int));
    }

    for (int i = 0; i < row; i++) {
      for (int j = 0 ; j < column; j++) {
         matrixResult[i][j] = matrixA[i][j] - matrixB[i][j];
      }
   }

   cleanScreen();
    showMatrix(matrixA, row, column, "A");  
    printf("\n");
    showMatrix(matrixB, row, column, "B");  
    printf("\n");
    showMatrix(matrixResult, row, column, "resultado");  
   free(matrixResult);
}

