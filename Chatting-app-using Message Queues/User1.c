#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/msg.h>
#include<sys/ipc.h>
struct msg
{
	long type;
	char msgbuff[100];
};
int main()
{
  struct msg obj,obj1;
  int m_id,pid;
  obj.type=1;
  char s[100];
  if(m_id=msgget((key_t) 123,0666|IPC_CREAT)==-1)
  {
    printf("Message queue creation error");
    return 0;
  }
  pid=fork();
  if(pid==0)
  {
    while(1)
    {
      printf("You: ");
      fgets(s,100,stdin);
      strcpy(obj.msgbuff,s);
      msgsnd(m_id,(struct msg *)&obj,100,0);
    }
  }
  else
  {
    while(1)
    {
      if(msgrcv(m_id,(struct msg *)&obj1,100,2,0)<0)
      {
        printf("message receive error");
          return 0;
      }
      printf("\rSender: %s\n",obj1.msgbuff);
      printf("You: ");
      fflush(stdout);
    }
  }
  return 0;
}
