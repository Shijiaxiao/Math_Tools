//
//  main.c
//  The Graph of Rational Polynomial Function and its Derivative Function
//
//  Created by 史家箫 on 2021/11/17.
// 0.1 0.05 4 3.75

#include <stdio.h>
#include <string.h>
#include <math.h>

#define N 7
#define Change_y 0.1
#define Change_x 0.05
#define Range_y 4
#define Range_x 3.75

//Polynomial Function.
void Input(int *degree_M,int *degree_m,double coefficient_M[N+1],double coefficient_m[N+1]);
double Result_Degree_M(double coefficient_M[N+1],int degree_M,double *x);
double Result_Degree_m(double coefficient_m[N+1],int degree_m,double *x);
double Result_Degree(double coefficient_M[N+1],double coefficient_m[N+1],int degree_M,int degree_m,double *x);
void Graph(double coefficient_M[N+1],double coefficient_m[N+1],int *degree_M,int *degree_m,double *x);

//Derivative.
double Square(double coefficient_m[N+1],int degree_m,double *x);
double Derivative_Degree_M(double coefficient_M[N+1],int degree_M,double *x);
double Derivative_Degree_m(double coefficient_m[N+1],int degree_m,double *x);
double Derivative_Degree(double coefficient_M[N+1],double coefficient_m[N+1],int degree_M,int degree_m,double *x);
void Graph_Derivative(double coefficient_M[N+1],double coefficient_m[N+1],int *degree_M,int *degree_m,double *x);

int main()
{
    double coefficient_M[N+1],coefficient_m[N+1];
    double x;
    int degree_M,degree_m;
    char end[10];
    do {
        printf("Welcome to Drogba's Rational Polynomial Function Graph calculator!\n");
        Input(&degree_M,&degree_m,coefficient_M,coefficient_m);
        Graph(coefficient_M,coefficient_m,&degree_M,&degree_m,&x);
        Graph_Derivative(coefficient_M,coefficient_m,&degree_M,&degree_m,&x);
        printf("Press any character to continue, type %cquit%c to quit:",'"','"');
        scanf("%s",end);
        fflush(stdin);
    } while(strcmp(end, "quit")!=0&&strcmp(end, "Quit")!=0);
    return 0;
}

void Input(int *degree_M,int *degree_m,double coefficient_M[N+1],double coefficient_m[N+1])
{
    int i;
    //max
    printf("Please input the maximum degree of the Rational Polynomial Function[0,%d]:",N);
    while(scanf("%d",degree_M)==0)
    {
        fflush(stdin);
        printf("Degree must be an integer:");
    }
    while(*degree_M>N||*degree_M<0)
    {
        fflush(stdin);
        printf("Degree must be in the range of[0,%d]:",N);
        scanf("%d",degree_M);
    }
    //min
    printf("Please input the minimum degree of the Rational Polynomial Function[%d,0]:",-N);
    while(scanf("%d",degree_m)==0)
    {
        fflush(stdin);
        printf("Degree must be an integer:");
    }
    while(*degree_m<-N||*degree_m>0)
    {
        fflush(stdin);
        printf("Degree must be in the range of[%d,0]:",-N);
        scanf("%d",degree_m);
    }
    printf("Please input the coefficient of the Rational Polynomial Function successively:\n");
    //operate
    printf("Let's finish the numerator part first!\n");
    for(i=*degree_M;i>=0;i--)
    {
        printf("The coefficient of x^%d:",i);
        while(scanf("%lf",coefficient_M+i)==0)
        {
            fflush(stdin);
            printf("\nWrong input!\n");
            printf("The coefficient of x^%d:",i);
        }
        //putchar('\n');
    }
    printf("Let's finish the denominator part then!\n");
    for(i=-*degree_m;i>=0;i--)
    {
        printf("The coefficient of x^%d:",i);
        while(scanf("%lf",coefficient_m+i)==0)
        {
            fflush(stdin);
            printf("\nWrong input!\n");
            printf("The coefficient of x^%d:",i);
        }
        //putchar('\n');
    }
    //if(coefficient_m[0]==0)
        //coefficient_m[0]=0.00000001;
    
}

double Result_Degree_M(double coefficient_M[N+1],int degree_M,double *x)
{
    int i;
    double result_M=coefficient_M[0];
    //result=coefficient_M[degree];
    if(degree_M>0)
    {
        result_M=coefficient_M[degree_M];
        for(i=0;i<degree_M;i++)
            result_M*=*x;
        return result_M+Result_Degree_M(coefficient_M,degree_M-1,x);
    }
    else
        return result_M;
}
    
double Result_Degree_m(double coefficient_m[N+1],int degree_m,double *x)
{
    int i;
    double result_m=coefficient_m[0];
    //result=coefficient_M[degree];
    if(degree_m<0)
    {
        result_m=coefficient_m[-degree_m];
        for(i=0;i<-degree_m;i++)
            result_m*=*x;
        return result_m+Result_Degree_m(coefficient_m,degree_m+1,x);
    }
    else
        return result_m;
}

double Result_Degree(double coefficient_M[N+1],double coefficient_m[N+1],int degree_M,int degree_m,double *x)
{
    double result=Result_Degree_M(coefficient_M,degree_M,x)/Result_Degree_m(coefficient_m,degree_m,x);
    return result;
}

void Graph(double coefficient_M[N+1],double coefficient_m[N+1],int *degree_M,int *degree_m,double *x)
{
    double y,judge;
    printf("The Graph of the Rational Polynomial Function %c (",'"');
    //max
    for(int i=*degree_M;i>=0;i--)
    {
        if(i<*degree_M&&coefficient_M[i]>0)
            putchar('+');
        else if(coefficient_M[i]==0)
            continue;
        printf("%.2lf*x^%d",coefficient_M[i],i);
    }
    //min
    printf(") ➗ (");
    for(int i=-*degree_m;i>=0;i--)
    {
        if(i<*degree_m&&coefficient_m[i]>0)
            putchar('+');
        else if(coefficient_m[i]==0)
            continue;
        printf("%.2lf*x^%d",coefficient_m[i],i);
    }
    printf(") %c is:\n\n",'"');
    for(*x=-Range_x;*x<=Range_x;*x+=Change_x)
    {
        if(*x>=-0.001&&*x<=0.001)
            putchar('y');
        else
            putchar(' ');
    }
    putchar('\n');
    for(y=Range_y;y>=-Range_y;y-=Change_y)
    {
        for(*x=-Range_x;*x<=Range_x;*x+=Change_x)
        {
            judge=y-Result_Degree(coefficient_M,coefficient_m,*degree_M,*degree_m,x);
            //if(judge>=-0.025&&judge<=0.025)
            if(y>=-0.001&&y<=0.001)
            {
                if(*x>=-0.001&&*x<=0.001)
                    putchar('o');
                else if(*x>=Range_x-0.04&&*x<=Range_x+0.04)
                    printf(">x");
                else
                    putchar('-');
            }
            else if(*x>=-0.001&&*x<=0.001)
            {
                if(y>=Range_y-0.001&&y<=Range_y+0.001)
                    putchar('^');
                else
                    putchar('|');
            }
            else if(judge>0)
                putchar('*');
            //else if(judge>=-0.03&&judge<=0.03)
                //putchar('*');
            else
                putchar(' ');
        }
        putchar('\n');
    }
    putchar('\n');
}


double Square(double coefficient_m[N+1],int degree_m,double *x)
{
    double square;
    square=pow(Result_Degree_m(coefficient_m, degree_m, x),2);
    return square;
}

double Derivative_Degree_M(double coefficient_M[N+1],int degree_M,double *x)
{
    int i;
    double result_M=coefficient_M[1];
    if(degree_M>0)
    {
        result_M=degree_M*coefficient_M[degree_M];
        for(i=0;i<degree_M-1;i++)
            result_M*=*x;
        return result_M+Derivative_Degree_M(coefficient_M,degree_M-1,x);
    }
    else
        return 0;
}

double Derivative_Degree_m(double coefficient_m[N+1],int degree_m,double *x)
{
    int i;
    double result_m=coefficient_m[1];
    if(degree_m<0)
    {
        result_m=-degree_m*coefficient_m[-degree_m];
        for(i=0;i<-degree_m-1;i++)
            result_m*=*x;
        return result_m+Derivative_Degree_m(coefficient_m,degree_m+1,x);
    }
    else
        return 0;
}

double Derivative_Degree(double coefficient_M[N+1],double coefficient_m[N+1],int degree_M,int degree_m,double *x)
{
    double result;
    double result_up_l,result_up_r,result_down;
    result_up_l=Derivative_Degree_M(coefficient_M,degree_M,x)*Result_Degree_m(coefficient_m,degree_m,x);
    result_up_r=Derivative_Degree_m(coefficient_m,degree_m,x)*Result_Degree_M(coefficient_M,degree_M,x);
    result_down=Square(coefficient_m,degree_m,x);
    result=(result_up_l-result_up_r)/result_down;
    return result;
}

void Graph_Derivative(double coefficient_M[N+1],double coefficient_m[N+1],int *degree_M,int *degree_m,double *x)
{
    double y,judge;
    printf("The Graph of the Rational Polynomial's Derivative Function %c { ",'"');
    
    //up left left.
    for(int i=*degree_M;i>=1;i--)
    {
        if(i<*degree_M&&coefficient_M[i]>0)
            putchar('+');
        else if(coefficient_M[i]==0)
            continue;
        printf("%.2lf*x^%d",coefficient_M[i]*i,i-1);
    }
    printf(")*(");
    
    //up left right
    for(int i=-*degree_m;i>=0;i--)
    {
        if(i<-*degree_m&&coefficient_m[i]>0)
            putchar('+');
        else if(coefficient_m[i]==0)
            continue;
        printf("%.2lf*x^%d",coefficient_m[i],i);
    }
    printf(")-(");
    
    //up right left
    for(int i=-*degree_m;i>=1;i--)
    {
        if(i<*degree_m&&coefficient_m[i]>0)
            putchar('+');
        else if(coefficient_m[i]==0)
            continue;
        printf("%.2lf*x^%d",coefficient_m[i]*i,i-1);
    }
    printf(")*(");
    
    //up right right.
    for(int i=*degree_M;i>=0;i--)
    {
        if(i<*degree_M&&coefficient_M[i]>0)
            putchar('+');
        else if(coefficient_M[i]==0)
            continue;
        printf("%.2lf*x^%d",coefficient_M[i],i);
    }
    printf(") ➗ (");
    
    //down
    for(int i=-*degree_m;i>=0;i--)
    {
        if(i<-*degree_m&&coefficient_m[i]>0)
            putchar('+');
        else if(coefficient_m[i]==0)
            continue;
        printf("%.2lf*x^%d",coefficient_m[i],i);
    }
    printf(")^2");
    
    printf(" } %c is:\n\n",'"');
    for(*x=-Range_x;*x<=Range_x;*x+=Change_x)
    {
        if(*x>=-0.001&&*x<=0.001)
            putchar('y');
        else
            putchar(' ');
    }
    putchar('\n');
    for(y=Range_y;y>=-Range_y;y-=Change_y)
    {
        for(*x=-Range_x;*x<=Range_x;*x+=Change_x)
        {
            judge=y-Derivative_Degree(coefficient_M,coefficient_m,*degree_M,*degree_m,x);
            //if(judge>=-0.025&&judge<=0.025)
            if(y>=-0.001&&y<=0.001)
            {
                if(*x>=-0.001&&*x<=0.001)
                    putchar('o');
                else if(*x>=Range_x-0.04&&*x<=Range_x+0.04)
                    printf(">x");
                else
                    putchar('-');
            }
            else if(*x>=-0.001&&*x<=0.001)
            {
                if(y>=Range_y-0.001&&y<=Range_y+0.001)
                    putchar('^');
                else
                    putchar('|');
            }
            else if(judge>0)
                putchar('*');
            //else if(judge>=-0.03&&judge<=0.03)
                //putchar('*');
            else
                putchar(' ');
        }
        putchar('\n');
    }
    putchar('\n');
}























































