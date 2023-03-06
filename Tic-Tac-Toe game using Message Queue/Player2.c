#include<stdio.h>
#include "tictactoe.h"
int main()
{
    struct msg obj,obj1;
    int m_id,pos,count=0,cw;
    obj1.type=2;
    int ticmat[3][3],check[9]={0};
    char s[100];
    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
    ticmat[i][j]=-1;
    if(m_id=msgget((key_t) 1213,0666|IPC_CREAT)==-1)
    {
        printf("Message queue creation error");
        return 0;
    }
    while(1)
    {
        if(msgrcv(m_id,(struct msg *)&obj,100,1,0)==-1)
        {
            printf("message receive error");
            return 0;
        }
        pos=atoi(obj.msgbuff);
        ticfill(ticmat,pos,0,check);
        printf("Opponent: %d\n",pos);
        ticmatprint(ticmat);
        if(count>=3)
        {
            cw=pwc(ticmat,0);
            if(cw==0)
            {
              printf("*-*-*-*- Opponent Won *-*-*-*");
              return 0;
            }
        }
        printf("You: ");
        fgets(s,100,stdin);
        printf("\n");
        strcpy(obj1.msgbuff,s);
        pos=atoi(s);
        ticfill(ticmat,pos,1,check);
        msgsnd(m_id,(struct msg *)&obj1,100,0);
        ticmatprint(ticmat);
        if(count>=3)
        {
            cw=pwc(ticmat,1);
            if(cw==1)
            {
              printf("*-*-*-*- You Won *-*-*-*");
              return 0;
            }
        }
        count++;
    }
    return 0;
}
