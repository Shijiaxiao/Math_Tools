//
//  main.c
//  Polynomial Function Graph
//
//  Created by 史家箫 on 2021/11/16.
//  pointer is constant, else are variable.

#include <stdio.h>
#include <string.h>

#define N 7
#define Change_y 0.08
#define Change_x 0.04
#define Range_y 3.2
#define Range_x 3

void Input(int *degree,double coefficient[N+1]);
double Result_Degree(double coefficient[N+1],int degree,double *x);
void Graph(double coefficient[N+1],int *degree,double *x);

int main()
{
    double coefficient[N+1];
    double x;
    int degree;
    char end[10];
    do {
        printf("Welcome to Drogba's Polynomial Function Graph calculator!\n");
        Input(&degree, coefficient);
        Graph(coefficient, &degree, &x);
        printf("Press any character to continue, type %cquit%c to quit:",'"','"');
        scanf("%s",end);
        fflush(stdin);
    } while(strcmp(end, "quit")!=0&&strcmp(end, "Quit")!=0);
    return 0;
}

void Input(int *degree,double coefficient[N+1])
{
    int i;
    printf("Please input the maximum/minimum degree of the Polynomial Function(<=%d):",N);
    while(scanf("%d",degree)==0)
    {
        fflush(stdin);
        printf("Degree must be an integer:");
    }
    while(*degree>N)
    {
        fflush(stdin);
        printf("Degree must not exceed %d:",N);
        scanf("%d",degree);
    }
    printf("Please input the coefficient of the Polynomial Function successively:\n");
    if(*degree>=0)
    {
        for(i=*degree;i>=0;i--)
        {
            printf("The coefficient of x^%d:",i);
            while(scanf("%lf",coefficient+i)==0)
            {
                fflush(stdin);
                printf("\nWrong input!\n");
                printf("The coefficient of x^%d:",i);
            }
            //putchar('\n');
        }
    }
    else
    {
        for(i=*degree;i<=0;i++)
        {
            printf("The coefficient of x^%d:",i);
            while(scanf("%lf",coefficient-i)==0)
            {
                fflush(stdin);
                printf("\nWrong input!\n");
                printf("The coefficient of x^%d:",i);
            }
            //putchar('\n');
        }
    }
    
}

double Result_Degree(double coefficient[N+1],int degree,double *x)
{
    int i;
    double result=coefficient[0];
    if(degree>0)
    {
        result=coefficient[degree];
        for(i=0;i<degree;i++)
            result*=*x;
        return result+Result_Degree(coefficient,degree-1,x);
    }
    else if(degree<0)
    {
        result=coefficient[-degree];
        for(i=0;i>degree;i--)
            result/=*x;
        return result+Result_Degree(coefficient,degree+1,x);
    }
    else
        return result;
}

void Graph(double coefficient[N+1],int *degree,double *x)
{
    double y,judge;
    printf("The Graph of the Polynomial Function %c ",'"');
    if(*degree>=0)
    {
        for(int i=*degree;i>=0;i--)
        {
            if(i<*degree&&coefficient[i]>0)
                putchar('+');
            else if(coefficient[i]==0)
                continue;
            printf("%.2lf*x^%d",coefficient[i],i);
        }
        printf(" %c is:\n\n",'"');
    }
    else
    {
        for(int i=*degree;i<=0;i++)
        {
            if(i>*degree&&coefficient[-i]>0)
                putchar('+');
            else if(coefficient[-i]==0)
                continue;
            printf("%.2lf*x^%d",coefficient[-i],i);
        }
        printf(" %c is:\n\n",'"');
    }
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
            judge=y-Result_Degree(coefficient, *degree, x);
            if(judge>=-0.025&&judge<=0.025)
                putchar('*');
            else if(y>=-0.001&&y<=0.001)
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
            //else if(judge>0)
                //putchar('*');
            //else if(judge>=-0.03&&judge<=0.03)
                //putchar('*');
            else
                putchar(' ');
        }
        putchar('\n');
    }
    putchar('\n');
}
