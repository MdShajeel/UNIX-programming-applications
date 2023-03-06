#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<stdlib.h>
int ticfill(int ticmat[][3],int pos,int u,int check[])
{
    int i,j,count=1,flag=0;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(count==pos && check[pos-1]==0)
            {
                check[pos-1]==1;
                if(u==1)
                ticmat[i][j]=1;
                if(u==0)
                ticmat[i][j]=0;
                flag=1;
                break;
            }
            else
            count++;
        }
        if(flag==1)
        break;
    }
}
int pwc(int ticmat[][3],int u)
{
    int i,j,check=0;
    for(i=0;i<3;i++)
    {
        check=0;
        for(j=0;j<3;j++)
        if(ticmat[i][j]==u)
        check++;
        if(check==3)
        return u;
    }
    for(i=0;i<3;i++)
    {
        check=0;
        for(j=0;j<3;j++)
        if(ticmat[j][i]==u)
        check++;
        if(check==3)
        return u;
    }
    if(ticmat[0][0]==u && ticmat[1][1]==u && ticmat[2][2]==u)
    return u;
    if(ticmat[0][2]==u && ticmat[1][1]==u && ticmat[2][0]==u)
    return u;
    return -1;
}
void ticmatprint(int ticmat[][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(ticmat[i][j]==0)
            printf("X\t");
            else if(ticmat[i][j]==1)
            printf("O\t");
            else
            printf("-\t");
        }
        printf("\n");
    }
}
struct msg
{
    long type;
    char msgbuff[100];
};
