//
//  main.c
//  Solving Linear Equations
//
//  Created by 史家箫 on 2021/11/27.
//

#include <stdio.h>
#include <ctype.h>

#define N 100

void swap(double A[][N],double B[N],int row,int r,int *n);
void Get_matrix(double A[][N],double B[N],int *m,int *n);
void Up_down(double A[][N],double B[N],int *m,int *n);
void Down_up(double A[][N],double B[N],int *m,int *n);
void Simplify(double A[][N],double B[N],int *m,int *n);
void Output(double A[][N],double B[N],int *m,int *n);
void Rank(double A[][N],double B[N],int *m,int *n,int *rank_coe,int *rank_aug);
void Solution(double A[][N],double B[N],int *m,int *n,int *rank_coe,int *rank_aug);

int main()
{
    double A[N][N],B[N];
    int m,n,rank_coe,rank_aug;
    printf("Welcome to Drogba's 'Solving Linear Equations' Calculator!\n");
    Get_matrix(A, B, &m, &n);
    Up_down(A, B, &m, &n);
    Down_up(A, B, &m, &n);
    Simplify(A, B, &m, &n);
    Output(A, B, &m, &n);
    Rank(A, B, &m, &n,&rank_coe,&rank_aug);
    Solution(A, B, &m, &n,&rank_coe,&rank_aug);
    printf("Done!\n\n");
    return 0;
}

void swap(double A[][N],double B[N],int row,int r1,int *n)//*row not neccesary, variable 'row' won't be modified.
{
    int c;
    double temp;
    for(c=0;c<*n;c++)
    {
        temp=A[row][c];
        A[row][c]=A[r1][c];
        A[r1][c]=temp;
    }
    temp=B[row];
    B[row]=B[r1];
    B[r1]=temp;
}

void Get_matrix(double A[][N],double B[N],int *m,int *n)
{
    int row,column,flag=1;
    char result;
    printf("Please input the degree of the equations:");
    scanf("%d",n);
    printf("How many equoations does the group consists:");
    scanf("%d",m);
    printf("Now please input the coefficient matrix(%d*%d):\n",*m,*n);
    while(1)
    {
        flag=1;
        for(row=0;row<*m;row++)
        {
            for(column=0;column<*n;column++)
                if(scanf("%lf",A[row]+column)==0)
                {
                    flag=0;
                    break;
                }
            if(!flag)
                break;
        }
        if(flag)
            break;
        else
            printf("Please check your input:\n");
        fflush(stdin);
        //while(getchar()!='\n');
        //scanf("%*[^\n]");
        //2 traditional ways of disposing wrong input.
    }
    printf("The equations are (A)homogeneous or (B)hydrodynamics:");
    scanf("%*[^a-zA-Z]%c",&result);
    if(toupper(result)=='A')
        for(row=0;row<*n;row++)
            B[row]=0;
    else
    {
        printf("Please input the constant number matrix(%d*1):\n",*m);
        while(1)
        {
            int flag=1;
            for(row=0;row<*m;row++)
            {
                if(scanf("%lf",B+row)==0)
                {
                    flag=0;
                    break;
                }
                if(!flag)
                    break;
            }
            if(flag)
                break;
            else
                printf("Please check your input:\n");
            fflush(stdin);
        }
    }
    
}

void Up_down(double A[][N],double B[N],int *m,int *n)
{
    int i,j=0,row,column,r1;
    int r,c,flag1=0,flag2=0;
    double k;
    printf("\n**************************************************************************************************************\n\n");
    for(row=0;row<*m;row++)
    {
        if(row==*m/2-1)
            printf("    === Start! ===>>>     ");
        else
            printf("                          ");
        printf("( ");
        for(column=0;column<*n;column++)
            printf("% 7.4lf ",A[row][column]);
        printf("| ");
        printf("% 7.4lf ",B[row]);
        printf(")\n");
    }
    putchar('\n');
    for(row=0;row<((*m<*n) ? *m : *n)-1;row++)
    {
        flag1=0;
        for(;row+j<*n;j++)//j should be remember(ever-changing), so it mustn't initialized every time when entering the for loop.
        {
            flag2=0;
            if(A[row][row+j]<=0.01&&A[row][row+j]>=-0.01)
            {
                flag2=1;//if there is a zreo, flag2 -> 1.
                for(r1=row+1;r1<*m;r1++)
                    if(A[r1][row]!=0)//0 is modified.
                    {
                        swap(A,B,row,r1,n);
                        flag1=1;//if swapped.
                        break;
                    }
                if(flag1)//if did swap, enter the next row++ loop(break the column one).
                {
                    for(r=0;r<*m;r++)
                    {
                        if(r==*m/2-1)
                            printf("    === r%d<->r%d ===>>>    ",row+1,r1+1);
                        else
                            printf("                          ");
                        printf("( ");
                        for(c=0;c<*n;c++)
                            printf("% 7.4lf ",A[r][c]);
                        printf("| ");
                        printf("% 7.4lf ",B[r]);
                        printf(")\n");
                    }
                    putchar('\n');
                    break;
                }
            }
            else//if is not zero, enter the next row++ loop.
                break;
        }
        if(!flag1&&flag2)
            break;//if didn't swap during the whole j++ loop && the last element is zero -> the rest rows are all zero. Break!
        for(i=1;i<*m-row;i++)
        {
            k=A[row+i][row+j]/A[row][row+j];//utilize the remembered j modified in tha last j++ loop.
            if(k==0)
                continue;
            for(column=0;column<*n;column++)
                A[row+i][column]-=k*A[row][column];
            B[row+i]-=k*B[row];
            if(A[row+i][column]<=0.01&&A[row+i][column]>=-0.01)
                A[row+i][column]=0;
            if(B[row+i]<=0.01&&B[row+i]>=-0.01)
                B[row+i]=0;
            for(r=0;r<*m;r++)
            {
                if(r==*m/2-1)
                {
                    if(k<0)
                        printf(" === r%d+%7.4lf*r%d ===>>> ",row+i+1,-k,row+1);
                    else
                        printf(" === r%d-%7.4lf*r%d ===>>> ",row+i+1,k,row+1);
                }
                else
                    printf("                          ");
                printf("( ");
                for(c=0;c<*n;c++)
                    printf("% 7.4lf ",A[r][c]);
                printf("| ");
                printf("% 7.4lf ",B[r]);
                printf(")\n");
            }
            putchar('\n');
        }
    }
}

void Down_up(double A[][N],double B[N],int *m,int *n)
{
    int i,j=0,row,column;
    int r,c,flag=0;
    double k;
    for(row=1;row<((*m<*n) ? *m : *n);row++)
    {
        flag=0;
        for(;row+j<*n;j++)
        {
            if(A[row][row+j]<=0.01&&A[row][row+j]>=-0.01)//==0 seems ok but a little risky I guess.
            {
                A[row][row+j]=0;
                continue;
            }
            else
            {
                flag=1;
                break;
            }
        }
        if(!flag)//is zero.
            continue;
        for(i=1;i<=row;i++)
        {
            k=A[row-i][row+j]/A[row][row+j];
            if(k==0)
                continue;
            for(column=0;column<*n;column++)
                A[row-i][column]-=k*A[row][column];
            B[row-i]-=k*B[row];
            if(A[row-i][column]<=0.01&&A[row-i][column]>=-0.01)
                A[row-i][column]=0;
            if(B[row-i]<=0.01&&B[row-i]>=-0.01)
                B[row-i]=0;
            for(r=0;r<*m;r++)
            {
                if(r==*m/2-1)
                {
                    if(k<0)
                        printf(" === r%d+%7.4lf*r%d ===>>> ",row-i+1,-k,row+1);
                    else
                        printf(" === r%d-%7.4lf*r%d ===>>> ",row-i+1,k,row+1);
                }
                else
                    printf("                          ");
                printf("( ");
                for(c=0;c<*n;c++)
                    printf("% 7.4lf ",A[r][c]);
                printf("| ");
                printf("% 7.4lf ",B[r]);
                printf(")\n");
            }
            putchar('\n');
        }
    }
}

void Simplify(double A[][N],double B[N],int *m,int *n)
{
    int row,column;
    int r,c,j=0,flag1,flag2=0;
    double k;
    for(row=0;row<((*m<*n) ? *m : *n);row++)
    {
        flag1=0;
        for(;row+j<*n;j++)
        {
            if(A[row][row+j]<=0.01&&A[row][row+j]>=-0.01)//==0 seems ok but a little risky I guess.
                A[row][row+j]=0;
            else
            {
                flag1=1;
                break;
            }
        }
        if(!flag1)//the rest rows are all zero!
            break;
        k=A[row][row+j];
        A[row][row+j]=1;
        if(k<=1.01&&k>=0.99)
            continue;
        else//need simplify.
            flag2=1;
        for(column=row+j+1;column<*n;column++)
        {
            A[row][column]/=k;
            if(A[row][column]<=0.01&&A[row][column]>=-0.01)
                A[row][column]=0;
        }
        B[row]/=k;
        if(B[row]<=0.01&&B[row]>=-0.01)
            B[row]=0;
    }
    if(!flag2)
    {
        printf("**************************************************************************************************************\n\n");
        return;
    }
    for(r=0;r<*m;r++)
    {
        if(r==*m/2-1)
            printf("   === Simplify ===>>>    ");
        else
            printf("                          ");
        printf("( ");
        for(c=0;c<*n;c++)
            printf("% 7.4lf ",A[r][c]);
        printf("| ");
        printf("% 7.4lf ",B[r]);
        printf(")\n");
    }
    printf("\n**************************************************************************************************************\n\n");
}

void Output(double A[][N],double B[N],int *m,int *n)
{
    int row,column;
    printf("The Canonical form of the augmented matrix is:\n\n");
    for(row=0;row<*m;row++)
    {
        printf(" ( ");
        for(column=0;column<*n;column++)
            printf("% 7.4lf ",A[row][column]);
        printf("| ");
        printf("% 7.4lf ",B[row]);
        printf(")\n");
    }
    putchar('\n');
}

void Rank(double A[][N],double B[N],int *m,int *n,int *rank_coe,int *rank_aug)
{
    int flag=0,row,column;
    for(row=0;row<((*m<*n) ? *m : *n);row++)
    {
        flag=0;
        for(column=0;column<*n;column++)
        {
            if(A[row][column]!=0)
            {
                flag=1;
                (*rank_coe)++;
                (*rank_aug)++;
                break;
            }
        }
        if(!flag)//the row of the coefficient matrix is all zero.
        {
            if(B[row]!=0)
                (*rank_aug)++;
            else
                break;
        }
    }
    printf("The rank of the coefficient matrix is %d.\n",*rank_coe);
    printf("The rank of the augmented matrix is %d.\n\n",*rank_aug);
}

void Solution(double A[][N],double B[N],int *m,int *n,int *rank_coe,int *rank_aug)
{
    int i,j=0,k,flag=0,row,column;
    //it's realy hard to find the special solution for AX=B(B!=0) >_<
    double e[N][N]={0};//fundamental system of solutions
    if(*rank_coe!=*rank_aug)
        printf("The linear equations have no solution!\n\n");
    else if(*rank_coe==*n)
        printf("The linear equations have only 0 as solution!\n\n");
    else
    {
        flag=0;
        for(row=0;row<((*m<*n) ? *m : *n);row++)
        {
            for(;row+j<*n;j++)//rank<n.
            {
                if(A[row][row+j]!=0)
                {
                    if(row==*m-1)//the last row consist non-zero element!
                    {
                        for(i=0;i<*m;i++)
                            for(k=i;k<row+j+1;j++)
                                if(A[i][k]!=0)
                                {
                                    e[k][row+j+1]=-A[i][row+j+1];//row+j+1 stands for Xn within e(); k stands for (Xn).
                                    break;
                                }
                        e[row+j+1][row+j+1]=1;
                        continue;
                    }
                    else
                        break;
                }
                else
                {
                    for(i=0;i<row;i++)//distinguish row with row-1
                        for(k=i;k<row+j;k++)
                            if(A[i][k]!=0)
                            {
                                e[k][row+j]=-A[i][row+j];//row+j+1 stands for Xn within e(); k stands for (Xn).
                                break;
                            }
                    e[row+j][row+j]=1;
                }
            }
            for(k=0;k<*n;k++)
            {
                if(A[row][k]!=0)
                {
                    flag=1;
                    break;
                }
            }
            if(!flag)//the rest rows are all zero!
                break;
        }
        printf("The fundamental system of solutions for AX=0 are:\n\n");
        for(row=0;row<*n;row++)
        {
            for(column=0,j=0;column<*n && j<*n-*rank_coe;column++)
            {
                for(i=0;i<*n;i++)
                {
                    if(e[i][column]!=0)
                    {
                        if(row==*n/2-1)
                        {
                            if(j++==0)
                                putchar(' ');
                            else
                                putchar('+');
                            printf("X%d",column+1);
                        }
                        else
                            printf("   ");
                        printf("(% 7.4lf )",e[row][column]);
                        break;
                    }
                }
            }
            putchar('\n');
        }
        putchar('\n');
    }
}





































/*
void Solution(double A[][N],double B[N],int *m,int *n,int *rank_coe,int *rank_aug)
{
    int i,j,k=0,flag=0,row,column;
    //it's realy hard to find the special solution for AX=B(B!=0) >_<
    double e[N][N]={0};//fundamental system of solutions
    if(*rank_coe!=*rank_aug)
        printf("The linear equations have no solution!\n\n");
    else if(*rank_coe==*n)
        printf("The linear equations have only 0 as solution!\n\n");
    else
    {
        flag=0;
        for(row=0;row<((*m<*n) ? *m : *n);row++)
        {
            for(column=row+k;column<*n;column++)//rank<n.
            {
                if(A[row][column]!=0)
                {
                    if(row==*m-1)
                    {
                        for(i=0;i<*m;i++)
                            for(j=i;j<column+1;j++)
                                if(A[i][j]!=0)
                                {
                                    e[j][column+1]=-A[i][column+1];//column stands for Xn.
                                    break;
                                }
                        e[column+1][column+1]=1;
                    }
                    else
                    {
                        k=column-row;//avoid repeatence!
                        break;
                    }
                }
                else
                {
                    for(i=0;i<row;i++)//distinguish row with row-1
                        for(j=i;j<column;j++)
                            if(A[i][j]!=0)
                            {
                                e[j][column]=-A[i][column];//column stands for Xn.
                                break;
                            }
                    e[column][column]=1;
                }
            }
            for(j=0;j<*n;j++)
            {
                if(A[row][j]!=0)
                {
                    flag=1;
                    break;
                }
            }
            if(!flag)
                break;
        }
        printf("The fundamental system of solutions for AX=0 are:\n\n");
        for(row=0;row<*n;row++)
        {
            for(column=0,j=0;column<*n && j<*n-*rank_coe;column++)
            {
                for(i=0;i<*n;i++)
                {
                    if(e[i][column]!=0)
                    {
                        if(row==*n/2-1)
                        {
                            if(j++==0)
                                putchar(' ');
                            else
                                putchar('+');
                            printf("X%d",column+1);
                        }
                        else
                            printf("   ");
                        printf("(% 7.4lf )",e[row][column]);
                        break;
                    }
                }
            }
            putchar('\n');
        }
        putchar('\n');
    }
}

void Down_up(double A[][N],double B[N],int *m,int *n)
{
    int i,j,row,column;
    int r,c,flag=0;
    double k;
    for(row=((*m<*n) ? *m : *n)-1;row>0;row--)
    {
        flag=0;
        for(j=0;row+j<*n;j++)
        {
            if(A[row][row+j]<=0.01&&A[row][row+j]>=-0.01)//==0 seems ok but a little risky I guess.
            {
                A[row][row+j]=0;
                continue;
            }
            else
            {
                flag=1;
                break;
            }
        }
        if(!flag)
            continue;
        for(i=1;i<=row;i++)
        {
            k=A[row-i][row+j]/A[row][row+j];
            if(k==0)
                continue;
            for(column=0;column<*n;column++)
            {
                A[row-i][column]-=k*A[row][column];
                B[row-i]-=k*B[row-i];
            }
            if(A[row-i][column]<=0.01&&A[row-i][column]>=-0.01)
                A[row-i][column]=0;
            if(B[row-i]<=0.01&&B[row-i]>=-0.01)
                B[row-i]=0;
            for(r=0;r<*m;r++)
            {
                if(r==*m/2-1)
                {
                    if(k<0)
                        printf(" === r%d+%7.4lf*r%d ===>>> ",row-i+1,-k,row+1);
                    else
                        printf(" === r%d-%7.4lf*r%d ===>>> ",row-i+1,k,row+1);
                }
                else
                    printf("                          ");
                printf("( ");
                for(c=0;c<*n;c++)
                    printf("% 7.4lf ",A[r][c]);
                printf("| ");
                printf("% 7.4lf ",B[r]);
                printf(")\n");
            }
            putchar('\n');
        }
    }
}
*/
