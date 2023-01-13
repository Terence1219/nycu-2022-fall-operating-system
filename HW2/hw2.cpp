# include <iostream>
# include <thread>
# include <unistd.h>
using namespace std;

# define MAX 500
# define T_NUM 4

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX]; // Result of Addition
int matD[MAX][MAX]; // Result of Multiplication


void* Addition(void* number){
    // Addition -> matC

    int num = *(int*) number;
    int m = MAX/T_NUM;

    for (int i = m*(num-1); i < m*num; i++) {
        for (int j = 0; j < MAX; j++){
            matC[i][j] = matA[i][j] + matB[i][j];
        }   
    }
    pthread_exit(NULL);
}
void* Multiplication(void* number){
    // Multiplication -> matD
    
    int num = *(int*) number;
    int m = MAX/T_NUM;
    
    for (int i = m*(num-1); i < m*num; i++) {
        for (int j = 0; j < MAX; j++) {
            matD[i][j] = 0;
            for (int k = 0; k < MAX; k++) {
                matD[i][j] += matA[i][k] * matB[k][j];              
            }
        }
    }
    pthread_exit(NULL);
}

int main()
{
    //get input
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matA[i][j];
        }
    }
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matB[i][j];
        }
    }

    pthread_t t1, t2, t3, t4;    // define thread 
    
    int a[T_NUM];
    for (int i = 1; i <= T_NUM; i++)
        a[i-1] = i;
    
    //Addition    
    pthread_create(&t1,NULL,Addition,a);
    pthread_create(&t2,NULL,Addition,a+1);
    pthread_create(&t3,NULL,Addition,a+2);
    pthread_create(&t4,NULL,Addition,a+3);
    
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    
    // calculate SUM of matC
    long long sum_C = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            sum_C +=  matC[i][j];     
    }
    cout << sum_C << endl;
    
    //Multiplication
    pthread_create(&t1,NULL,Multiplication,a);
    pthread_create(&t2,NULL,Multiplication,a+1);
    pthread_create(&t3,NULL,Multiplication,a+2);
    pthread_create(&t4,NULL,Multiplication,a+3);
    
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    
    // calculate SUM of matD
    long long sum_D = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            sum_D += matD[i][j];
    }
    cout << sum_D << endl;
    
    return 0;
}