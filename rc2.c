#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<signal.h>
#include<string.h>
#include"prototype.h"
#define FIFO1 "./FIFO1"
#define FIFO2 "./FIFO2"

int prd;
Result rs;
void gotit(int a)
{

	read(prd,&rs,sizeof(Result));
	if(rs.pid == getpid())
		printf("\e[42m%s :\e[0m\e[44m Result recieved successfully (Sub->Result) = %d \e[0m \n",__FILE__,rs.result);
	exit(EXIT_SUCCESS);
}
int main()
{
	int pwd,result=0,ret;
	Request r1;
	//FIFO1 for write purpose
	if(access(FIFO1,F_OK) == -1)
	{
		ret = mkfifo(FIFO1,666);
		if(ret == -1)
		{
			perror("\e[41mFIFO1\e[0m");
			exit(EXIT_FAILURE);
		}
	}
	pwd = open(FIFO1,O_WRONLY);
	if(pwd == -1)
	{
		perror("\e[41mWRONLY\e[0m");
	}
	//FIFO1 for read purpose
	if(access(FIFO2,F_OK) == -1)
	{
		ret = mkfifo(FIFO2,666);
		if(ret == -1)
		{
			perror("\e[41mFIFO2\e[0m");
			exit(EXIT_FAILURE);
		}
	}
	prd = open(FIFO2,O_RDONLY);
	if(prd == -1)
	{
		perror("\e[41mWRONLY\e[0m");
	}
	
	r1.oper = '-';
	r1.oper1= 12;
	r1.oper2= 34;
	r1.pid = getpid();
	
	write(pwd,&r1,sizeof(Request));
	signal(SIGINT,gotit);
	pause();
	return 0;
}
