//
//  main.c
//  Matrix mutiply
//
//  Created by 史家箫 on 2021/11/12.
//

#include <stdio.h>
#include <string.h>

void Get_matrix(int a[][100],int b[][100],int *r1,int *c1,int *r2,int *c2);
void Multiply_matrix(int a[][100],int b[][100],int c[][100],int *r1,int *c1,int *r2,int *c2);
void Output(int c[][100],int *r1,int *c1,int *r2,int *c2);
int Again(void);

int row,column;

int main()
{
    printf("Welcome to the Matrix multiplication calculator!\n");
    int a[100][100],b[100][100];
    int r1,c1,r2,c2;
    do{
        int c[100][100]={0};
        Get_matrix(a,b,&r1,&c1,&r2,&c2);
        Multiply_matrix(a,b,c,&r1,&c1,&r2,&c2);
        Output(c,&r1,&c1,&r2,&c2);
        printf("Enter %cquit%c to quit, press any character to continue:",'"','"');
    } while(Again());
    return 0;
}

void Get_matrix(int a[][100],int b[][100],int *r1,int *c1,int *r2,int *c2)
{
    while(1)
    {
        printf("Please enter the parameters of the first matrix(m*n):");
        while(scanf(" %d%*c%d",r1,c1)!=2)
        {
            scanf("%*s");//filter wrong/unread input.
            printf("The parameters must be integers!\n");
            printf("Please enter the parameters of the first matrix(m*n):");
        }
        if(*r1<=0||*c1<=0)
            printf("The parameters must be positive!(such as 3)\n");
        else
            break;
    }
    while(1)
    {
        printf("Please enter the parameters of the second matrix(%d*r):",*c1);
        while(scanf(" %d%*c%d",r2,c2)!=2)
        {
            scanf("%*s");
            printf("The parameters must be integers!\n");
            printf("Please enter the parameters of the first matrix(m*n):");
        }
        if(*r2<=0||*c2<=0)
            printf("The parameters must be positive!(such as 3)\n");
        else if(*c1!=*r2)
            printf("The row of the second matrix must equals %d! You idiot!\n",*c1);
        else
            break;
    }
    printf("Please input the first matrix(%d*%d):\n",*r1,*c1);
    for(row=0;row<*r1;row++)
        for(column=0;column<*c1;column++)
            scanf("%d%*c",a[row]+column);
    printf("Please input the second matrix(%d*%d):\n",*r2,*c2);
    for(row=0;row<*r2;row++)
        for(column=0;column<*c2;column++)
            scanf("%d%*c",b[row]+column);
    return;
}

void Multiply_matrix(int a[][100],int b[][100],int c[][100],int *r1,int *c1,int *r2,int *c2)
{
    int i;
    for(row=0;row<*r1;row++)
        for(column=0;column<*c2;column++)
            for(i=0;i<*c1;i++)
                c[row][column]+=a[row][i]*b[i][column];
    return;
}

void Output(int c[][100],int *r1,int *c1,int *r2,int *c2)
{
    printf("The result is(%d*%d):\n",*r1,*c2);
    for(row=0;row<*r1;row++)
    {
        for(column=0;column<*c2;column++)
            printf("%3d ",c[row][column]);
        putchar('\n');
    }
    return;
}

int Again(void)
{
    char end[5];
    scanf("%s",end);
    return (strcmp(end, "quit")==0) ? 0 : 1 ;
}


























