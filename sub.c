#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#define FIFO3 "./FIFO3"
#define FIFO4 "./FIFO4"

#include"prototype.h"

int main()
{
	int pwd,prd,ret,result;
	Request r1;
	Result rs;
	// FIFO3 for read purpose
	if(access(FIFO3,F_OK) == -1)
	{
		ret = mkfifo(FIFO3,666);
		if(ret == -1)
		{
			perror("\e[41mFIFO3\e[0m");
			exit(EXIT_FAILURE);
		}
	}
	prd = open(FIFO3,O_RDONLY);
	if(prd == -1)
	{
		perror("\e[41mOPEN\e[0m");
		exit(EXIT_FAILURE);
	}
	// FIFO4 for read purpose
	if(access(FIFO4,F_OK) == -1)
	{
		ret = mkfifo(FIFO4,666);
		if(ret == -1)
		{
			perror("\e[41mFIFO4\e[0m");
			exit(EXIT_FAILURE);
		}
	}
	pwd = open(FIFO4,O_WRONLY);
	if(pwd == -1)
	{
		perror("\e[41mOPEN\e[0m");
		exit(EXIT_FAILURE);
	}

	
	read(prd,&r1,sizeof(Request));
	rs.result = r1.oper1 - r1.oper2;
	rs.pid = r1.pid;
	printf("\e[44m%s\e[0m : Fetched values successfully:\na = %d\nb = %d\nresult = %d\n",__FILE__,r1.oper1,r1.oper2,rs.result);
	write(pwd,&rs,sizeof(Result));
	
	printf("\e[44m%s\e[0m : successfully wrote sum into the pipes stream\n",__FILE__);
	
	return 0;
}
