#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
using namespace std;
void scan_matrix(int m,int n,char *a);
void clean_matrix(int m,int n,char *a);

int gameover(int m,int n,char *a)
{
    for(int j=0;j<n;j++)   //since only need to check 1st row
    {
        if(*(a+j)!='-')
            return 1;
    }
    return 0;
}
void draw_matrix(int m,int n,char *a)
{
    system("cls");
     for(int i=0;i<m;i++,cout<<"\n\n")
       for (int j=0;j<n;j++)
         cout<<(*(a+(i*n)+j))<<"\t";

}
void clean_matrix(int m,int n,char *a)
{
    //cheking for all elements
    //cout<<"CLEANING..\n";
    char *tmp;
    for(int i=0;i<m;i++)
       for (int j=0;j<n;j++)
        {

          tmp=(a+i*n+j);
          //Check right
          if( j%n < n-1 && *tmp!='-' && *(tmp)== *(tmp+1) )
             {
                 *(tmp)=*(tmp+1)='-';
                 draw_matrix(m,n,a);Sleep(100);
             }
          // Check left
          if( j%n > 0 && *tmp!='-' && *(tmp)==*(tmp-1))
              {
                  *(tmp)=*(tmp-1)='-';
                  draw_matrix(m,n,a);Sleep(100);
              }
          //Check Up
          if( i%m > 0 && *tmp!='-' && *(tmp)==*(tmp-m))
              {
                  *(tmp)=*(tmp-m)='-';
                  draw_matrix(m,n,a);Sleep(100);
              }
          //Check down
          if( i%m < m-1 && *tmp!='-' && *(tmp)==*(tmp+m))
              {
                  *(tmp)=*(tmp+m)='-';
                  draw_matrix(m,n,a);Sleep(100);
              }
        }
    scan_matrix(m,n,a);

}
void scan_matrix(int m,int n,char *a)
{
    //cout<<"\nSCANNING...\n";
    char *tmp;
    char t;
    int flag=0;
    for(int i=m-1;i>=0;i--)        //  to check until one row before
       for (int j=0;j<n;j++)
          {
              tmp=(a+i*n+j);
              if(*(tmp) == '-')
               {
                   for(int k=i;k>=0;k--)
                   {
                        if(*tmp!='-')
                          {
                            t=*tmp;
                            *tmp='-';
                            tmp=(a+i*n+j);
                            *tmp=t;
                            flag++;       //movement occurs so reclear it
                            draw_matrix(m,n,a);Sleep(100);
                            break;
                          }
                          tmp=tmp-n;
                   }
               }
          }
    if(flag)
      clean_matrix(m,n,a);
}
int main()
{
    int m=6,n=6;
    char *a=(char *)(malloc(m*n*sizeof(char)));
    int pos=0;
    int count=0;
    char data;

    for(int i=0;i<m;i++)
       for(int j=0;j<n;j++)
          *(a+(i*n)+j)='-';

        draw_matrix(m,n,a);

     while(!gameover(m,n,a))
     {
        cout<<"Enter the position:";
        cin>>pos;
        pos--;       //human readable
        cout<<"Enter the Randomn string data:";
        getchar();
        while((data=getchar()) != '\n' && count <= m*n)
        {
            for(int i=m-1;i>=0;i--)
            {
                if(*(a+(i*n)+pos)== '-')
                {
                *(a+(i*n)+pos)=data;
                pos++;
                pos=pos%n;
                //cout<<"POSITION"<<i*n<<" "<<pos<<"\n";
                break;
                }
            }
            count++;
        }
        draw_matrix(m,n,a);
        clean_matrix(m,n,a);
     }
     if(count==m*n)
     {
         while((data=getchar()) != '\n')   ;    // just to wait still \n   a fix for the game.
     }
    count=0;
    for(int i=0;i<m;i++)
       for(int j=0;j<n;j++)
          if(*(a+i*n+j)=='-')
             count++;

    cout<<"\n\t\tREMAINING BLANK SPACES IS "<<count;
    cout<<"\t\tGAME OVER";
    return 0;
}
