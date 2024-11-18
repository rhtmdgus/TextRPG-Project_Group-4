/*

   유한차분법을 사용하여 두 점 경계값 문제의 해를 구하는 프로그램:

     y''=p(x)y'(x)+q(x)y(x)+r(x), x는 구간 [a,b]에 속함
     y(a)=g1, y(b)=g2

   초기화:
     a, b, g1, g2, n (==> h=(b-a)/n) 및
     p(x), q(x), r(x)

   출력: 다음과 같은 내용을 파일로 출력한다. (참고로 x[0]=a, x[n]=b, y[0]=g1, y[n]=g2이다.)
     x[0] y[0]
     x[1] y[1]
       ......
     x[n] y[n]

   아래 예에서는

      p(x)= -2x/(1+x*x), q(x)=1, r(x)=2/(1+x*x)-ln(1+x*x)
      a=0, b=1, g1=0, g2=ln(2), n=100

   을 사용하였으며 이 미분방정식의 실제해는 ln(1+x*x)이다.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ITER 100

void tridiag(int n, double* l, double* d, double* u, double* f, double* y);
double p(double x);
double q(double x);
double r(double x);

void main()
{
    double* l, * d, * u, * f, * y;
    double h, h2, hh, temp, a, b, x;
    int i, n, nm1, nm2;
    FILE* output;
    output = fopen("output_FDM.txt", "w");

    n = 100;
    a = 0.;
    b = 1;
    h = (b - a) / (double)n;
    h2 = h / 2.;
    hh = h * h;

    nm1 = n - 1;
    nm2 = n - 2;
    y = (double*)malloc(nm1 * sizeof(double)); // 첨자: 1 ~ n-1
    y--;
    l = (double*)malloc(nm2 * sizeof(double)); // 첨자: 2 ~ n-1
    l -= 2;
    d = (double*)malloc(nm1 * sizeof(double)); // 첨자: 1 ~ n-1
    d--;
    u = (double*)malloc(nm2 * sizeof(double)); // 첨자: 1 ~ n-2
    u--;
    f = (double*)malloc(nm1 * sizeof(double)); // 첨자: 1 ~ n-1
    f--;

    // 3중대각행렬 및 우변벡터의 구성
    x = a + h;
    d[1] = 2.0 + hh * q(x);
    temp = h2 * p(x);
    u[1] = temp - 1.0;
    f[1] = -hh * r(x);
    for (i = 2; i <= nm2; i++) {
        x = a + i * h;
        temp = h2 * p(x);
        l[i] = -1.0 - temp;
        d[i] = 2.0 + hh * q(x);
        u[i] = temp - 1.0;
        f[i] = -hh * r(x);
    }
    x = a + nm1 * h;
    temp = h2 * p(x);
    l[nm1] = -1.0 - temp;
    d[nm1] = 2.0 + hh * q(x);
    f[nm1] = -hh * r(x);

    // 삼중대각 연립방정식의 해를 구함
    tridiag(nm1, l, d, u, f, y);

    printf("[유한차분 방법]\n");
    printf("출력은 'output_FDM.txt'에 저장되었습니다.\n");
    fprintf(output, "%.2f   %f\n", a, 0.0);
    for (i = 1; i <= nm1; i++) {
        fprintf(output, "%.2f   %f\n", a + i * h, y[i]);
    }
    fprintf(output, "%.2f   %f\n", b, 0.0);
    fclose(output);

    free(y + 1);
    free(l + 2);
    free(d + 1);
    free(u + 1);
    free(f + 1);
}

// 삼중대각 연립방정식을 푸는 부함수
void tridiag(int m, double* l, double* d, double* u, double* f, double* y)
{
    int mm = m - 1, j, jm;
    for (j = 2; j <= m; j++) {
        jm = j - 1;
        l[j] = l[j] / d[jm];
        d[j] = d[j] - l[j] * u[jm];
        f[j] = f[j] - l[j] * f[jm];
    }
    y[m] = f[m] / d[m];
    for (j = mm; j >= 1; j--)
        y[j] = (f[j] - u[j] * y[j + 1]) / d[j];
}

// p(x) 함수 정의
double p(double x)
{
    return 2.0 * x;
}

// q(x) 함수 정의
double q(double x)
{
    return x;
}

// r(x) 함수 정의
double r(double x)
{
    return x * (3.0 * x * x - 5.0) * exp(x);
}