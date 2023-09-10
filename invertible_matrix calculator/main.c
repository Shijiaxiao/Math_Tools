//
//  main.c
//  Invertible Matrix Calculator
//
//  Created by 史家箫 on 2021/11/14.
//  23 SPACE
//  53 STARS
//  Row,column is not neccesary to be parameters (changes in loops all the time).
//  But 2D arrays must be!(to be modified, operated, so we must give address as parameters!

#include <stdio.h>

#define N 100

void swap(double A[][N],int row,int r,int *n);
void Get_matrix(double A[][N],int *n);
void Create_standard(double E[][N],int *n);
int Judge(double A[][N],int *n);
void Up_down(double A[][N],double E[][N],int *n);
void Down_up(double A[][N],double E[][N],int *n);
void Simplify(double A[][N],double E[][N],int *n);
void Output(double E[][N],int *n);

int main()
{
    double A[N][N]={0.0};
    double E[N][N]={0.0};
    int n;
    printf("Welcome to Drogba's Invertible Matrix Calculator!\n");
    Get_matrix(A,&n);
    Create_standard(E,&n);
    if(!Judge(A,&n))
    {
        printf("\nThe matrix is uninvertible!\n\n");
        return 0;
    }
    Up_down(A,E,&n);
    Down_up(A,E,&n);
    Simplify(A,E,&n);
    Output(E,&n);
    return 0;
}

void swap(double A[][N],int row,int r1,int *n)//*row not neccesary, variable 'row' won't be modified.
{
    int c;
    float temp;
    for(c=0;c<*n;c++)
    {
        temp=A[row][c];
        A[row][c]=A[r1][c];
        A[r1][c]=temp;
    }
}

void Get_matrix(double A[][N],int *n)
{
    int row,column;
    printf("Please input the order(rank) of the matrix:");
    scanf("%d",n);
    printf("Now please input the matrix(%d*%d):\n\n",*n,*n);
    while(1)
    {
        int flag=1;
        for(row=0;row<*n;row++)
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
}

void Create_standard(double E[][N],int *n)
{
    int row,column;
    for(row=0;row<*n;row++)
        for(column=0;column<*n;column++)
            if(row==column)
                E[row][column]=1.0;
}

int Judge(double A[][N],int *n)
{
    double J[N][N];
    int i,row,column,r1;
    float k;
    for(row=0;row<*n;row++)
        for(column=0;column<*n;column++)
            J[row][column]=A[row][column];
    for(row=0;row<*n;row++)
    {
        if(J[row][row]<=0.01&&J[row][row]>=-0.01)
        {
            int flag=0;
            for(r1=row+1;r1<*n;r1++)
                if(J[r1][row]!=0)
                {
                    swap(J,row,r1,n);//n is already a pointer.
                    flag=1;
                    break;
                }
            if(!flag)
                return 0;
        }
        for(i=1;i<*n-row;i++)
        {
            k=J[row+i][row]/J[row][row];
            for(column=0;column<*n;column++)
                J[row+i][column]-=k*J[row][column];
        }
    }
    return 1;
}

void Up_down(double A[][N],double E[][N],int *n)
{
    int i,row,column,r1;
    int r,c;
    float k;
    printf("\n**************************************************************************************************************\n\n");
    for(row=0;row<*n;row++)
    {
        if(row==*n/2-1)
            printf("    === Start! ===>>>     ");
        else
            printf("                          ");
        printf("( ");
        for(column=0;column<*n;column++)
            printf("% 7.4f ",A[row][column]);
        printf("| ");
        for(column=0;column<*n;column++)
            printf("% 7.4f ",E[row][column]);
        printf(")\n");
    }
    putchar('\n');
    for(row=0;row<*n-1;row++)
    {
        if(A[row][row]<=0.01&&A[row][row]>=-0.01)
        {
            for(r1=row+1;r1<*n;r1++)
                if(A[r1][row]!=0)
                {
                    swap(A,row,r1,n);
                    break;
                }
            for(r=0;r<*n;r++)
            {
                if(r==*n/2-1)
                    printf("    === r%d<->r%d ===>>>    ",row+1,r1+1);
                else
                    printf("                          ");
                printf("( ");
                for(c=0;c<*n;c++)
                    printf("% 7.4lf ",A[r][c]);
                printf("| ");
                for(c=0;c<*n;c++)
                    printf("% 7.4lf ",E[r][c]);
                printf(")\n");
            }
            putchar('\n');
        }
        for(i=1;i<*n-row;i++)
        {
            k=A[row+i][row]/A[row][row];
            if(k==0)
                continue;
            for(column=0;column<*n;column++)
            {
                A[row+i][column]-=k*A[row][column];
                E[row+i][column]-=k*E[row][column];
            }
            if(A[row+i][column]<=0.01&&A[row+i][column]>=-0.01)
                A[row+i][column]=0;
            if(E[row+i][column]<=0.01&&E[row+i][column]>=-0.01)
                E[row+i][column]=0;
            for(r=0;r<*n;r++)
            {
                if(r==*n/2-1)
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
                for(c=0;c<*n;c++)
                    printf("% 7.4lf ",E[r][c]);
                printf(")\n");
            }
            putchar('\n');
        }
    }
}

void Down_up(double A[][N],double E[][N],int *n)
{
    int i,row,column,r1;
    int r,c;
    float k;
    for(row=*n-1;row>0;row--)
    {
        if(A[row][row]<=0.01&&A[row][row]>=-0.01)
        {
            for(r1=row-1;r1>=0;r1--)
                if(A[r1][row]!=0)
                {
                    swap(A,row,r1,n);
                    break;
                }
            for(r=0;r<*n;r++)
            {
                if(r==*n/2-1)
                    printf("    === r%d<->r%d ===>>>    ",row+1,r1+1);
                else
                    printf("                          ");
                printf("( ");
                for(c=0;c<*n;c++)
                    printf("% 7.4lf ",A[r][c]);
                printf("| ");
                for(c=0;c<*n;c++)
                    printf("% 7.4lf ",E[r][c]);
                printf(")\n");
            }
            putchar('\n');
        }
        for(i=1;i<=row;i++)
        {
            k=A[row-i][row]/A[row][row];
            if(k==0)
                continue;
            for(column=0;column<*n;column++)
            {
                A[row-i][column]-=k*A[row][column];
                E[row-i][column]-=k*E[row][column];
            }
            if(A[row-i][column]<=0.01&&A[row-i][column]>=-0.01)
                A[row-i][column]=0;
            if(E[row-i][column]<=0.01&&E[row-i][column]>=-0.01)
                E[row-i][column]=0;
            for(r=0;r<*n;r++)
            {
                if(r==*n/2-1)
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
                for(c=0;c<*n;c++)
                    printf("% 7.4lf ",E[r][c]);
                printf(")\n");
            }
            putchar('\n');
        }
    }
}

void Simplify(double A[][N],double E[][N],int *n)
{
    int row,column;
    int r,c,flag=0;
    float k;
    for(row=0;row<*n;row++)
    {
        k=A[row][row];
        A[row][row]=1.0;
        if(k<=1.01&&k>=0.09)
            continue;
        else
            flag=1;
        for(column=0;column<*n;column++)
        {
            E[row][column]/=k;
            if(E[row][column]<=0.01&&E[row][column]>=-0.01)
                E[row][column]=0;
        }
    }
    if(!flag)
    {
        printf("**************************************************************************************************************\n\n");
        return;
    }
    for(r=0;r<*n;r++)
    {
        if(r==*n/2-1)
            printf("   === Simplify ===>>>    ");
        else
            printf("                          ");
        printf("( ");
        for(c=0;c<*n;c++)
            printf("% 7.4lf ",A[r][c]);
        printf("| ");
        for(c=0;c<*n;c++)
            printf("% 7.4lf ",E[r][c]);
        printf(")\n");
    }
    printf("\n**************************************************************************************************************\n\n");
}

void Output(double E[][N],int *n)
{
    int row,column;
    printf("The result is:\n\n");
    for(row=0;row<*n;row++)
    {
        printf(" ( ");
        for(column=0;column<*n;column++)
            printf("% 7.4lf ",E[row][column]);
        printf(")\n");
    }
    putchar('\n');
}




















































