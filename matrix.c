#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    printf("[-----[Seo han bit]   [2019038043]-----]\n");

    char command;

    int row, col;
    srand(time(NULL));

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row); //create_matrix 함수를 이용하여 행렬에 동적 메모리 할당                                    

    printf("Matrix Created.\n");

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");  // 메뉴판

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {                                        //switch함수를 이용하여 각 기능 실행
        case 'z': case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a_t\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');                           //q 나 Q가 나오지 않는 이상 무한 반복
    
    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    if(row <= 0 || col <=0) {
        printf("Check the sizes of row and col!\n");          //row나 col이 정수가 아닐경우 오류라고 알려주는 전처리기
        return NULL;
    }   
    
    int **x, i;                                  //정수형 이중포인터 x와 정수형 변수 i 선언
   
    x = (int**)malloc(sizeof(int*)*row);         //이중포인터에 행을 생성하는 동적 메모리 할당

    for(i=0;i<row;i++){
        x[i] = (int*)malloc(sizeof(int)*col);    //각 행에 열을 생성하는 동적 메모리 할당
    }
    
    if(x == NULL){
        printf("Matrix not created.");           //메모리 할당이 안되었을 경우 오류라고 알려주는 후처리기
        return NULL;
    }


    return x;

}
/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col) //만들어진 행렬을 출력하는 함수
{   

    if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return;
	}
    
    int i, c;
    for(i=0;i<row;i++){

        for(c=0; c<col; c++)
            printf("%d ",matrix[i][c]);
        printf("\n");
    }
    printf("\n");
    if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return;
	}
            
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col) //동적 메모리 할당을 해제하는 함수
{    
    if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}

    int c;

    for(c=0; c<col; c++)
        free(matrix[c]);    
    free(matrix);
    return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)  //메모리 할당을 받은 2차원 배열에 랜덤으로 0부터 19까지의 숫자를 입력하는 함수
{
    if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}

    int r,c;
    
    for(r=0; r<row; r++){
        for(c=0; c<col; c++)
            matrix[r][c] = rand()%20; //%20을 해서 0부터 19까지의 랜덤의 범위를 정해줌
    }
    if(matrix == NULL){
        printf("matrix not fill ");
        return -1;
    }
  
    
    print_matrix(matrix,row,col);
    
    return 1;

}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)  //행렬끼리 덧셈을 수행하고 출력하는 함수
{
    if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}

    int r,c;
    int **result = create_matrix(row,col); //덧셈의 결과를 저장할 2차원 배열 메모리 할당

    

    for(r=0; r<row; r++){
        for(c=0; c<col; c++)
            result[r][c] = matrix_a[r][c] + matrix_b[r][c];

    }
    if (matrix_a == NULL || matrix_b == NULL || result == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
    print_matrix(result,row,col);
    free_matrix(result,row,col);             //이중포인터 result 메모리 해제

    return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col) //행렬끼리의 뺄셈을 수행하고 출력하는 함수
{
    if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    int r,c;
    int **result = create_matrix(row,col);


    for(r=0; r<row; r++){
        for(c=0; c<col; c++)
            result[r][c] = matrix_a[r][c] - matrix_b[r][c];

    }
    if (matrix_a == NULL || matrix_b == NULL || result == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
    print_matrix(result,row,col);
    free_matrix(result,row,col);

    return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)  //matrix_a를 전치행렬로 만들어 matrix_a_t에 저장하는 함수
{
    int r,c;

    for(c=0; c<col; c++){
        for(r=0; r<row; r++)
            matrix_t[r][c] = matrix[c][r];
            
    }
    return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col) //matrix_a와 matrix_a_t의 곱셈을 수행하고 출력하는 함수
{
    
    if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    int j,i,r,c,mul,mul_sum = 0;
    int **result = create_matrix(row,row);


    for(r=0; r<row; r++){
        for(i=0;i<row; i++){
           for(c=0; c<col; c++){
               mul = matrix_a[i][c] * matrix_t[c][r];
               mul_sum += mul;
           }            
        result[r][i] = mul_sum;
        mul_sum = 0; 
        }
        
    }
    if (result == NULL || matrix_t ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
    print_matrix(result,row,row);
    free_matrix(result,row,row);

    return 1;


}