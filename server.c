#include"header.h"
#include"prototype.h"
#include"declaration.h"
#define FIFO1 "./FIFO1"
#define FIFO2 "./FIFO2"
#define FIFO3 "./FIFO3"
#define FIFO4 "./FIFO4"
int main()
{
	int ret,ret1,ret2,ret3,ret4,rfork,result,ec,i=0;
	Request rr;
	Result rs;
	Result *r2;
	r2 = NULL;
	
	printf("\e[44m%s\e[0m : Initiating Server.\n",__FILE__);
	//FIFO1 for read purpose
	if(access(FIFO1,F_OK) == -1)
	{
		ret = mkfifo(FIFO1,666);
		if(ret == -1)
		{
			perror("\e[41mFIFO1\e[0m");
			exit(EXIT_FAILURE);
		}
	}
	ret1 = open(FIFO1,O_RDONLY);
	if(ret1 == -1)
	{
		perror("\e[41mOPEN\e[0m");
		exit(EXIT_FAILURE);
	}
	printf("\e[42mCONNECTION ESTABLISHED SUCCESSFULLY [RDONLY]\e[0m\n");

	//FIFO2 for write purpose
	if(access(FIFO2,F_OK) == -1)
	{
		ret = mkfifo(FIFO2,666);
		if(ret == -1)
		{
			perror("\e[41mFIFO2\e[0m");
			exit(EXIT_FAILURE);
		}
	}
	ret2 = open(FIFO2,O_WRONLY);
	if(ret2 == -1)
	{
		perror("\e[41mOPEN\e[0m");
		exit(EXIT_FAILURE);
	}
	printf("\e[42mCONNECTION ESTABLISHED SUCCESSFULLY [WRONLY]\e[0m\n");
	

	printf("\e[44m%s\e[0m : \e[38mWaiting for Requesting Client.\e[0m\n",__FILE__);
	while(1)
	while(read(ret1,&rr,sizeof(Request)))
	{
	printf("\e[44m%s\e[0m : Request recieved \n[ PROCESSING.. ]\n",__FILE__);
	rfork = fork();
	switch(rfork)
	{
		case -1:
		perror("\e[41mfork\e[0m");
		exit(EXIT_FAILURE);
		case  0:
		switch(rr.oper)
		{
			case '+':
					
					execl("./sum","sum.c",NULL);
			case '-':
					execl("./sub","sub.c",NULL);
			case '*':
					execl("./mul","mul.c",NULL);
			case '/':
					execl("./div","div.c",NULL);
			default :
					printf("\e[41mnot found\e[0m\n");
		}
		default:
			//FIFO3 for write purpose
			if(access(FIFO3,F_OK) == -1)
			{
				ret = mkfifo(FIFO3,666);
				if(ret == -1)
				{
					perror("\e[41mFIFO3\e[0m");
					exit(EXIT_FAILURE);
				}
			}
			ret3 = open(FIFO3,O_WRONLY);
			if(ret3 == -1)
			{
				perror("\e[41mOPEN\e[0m");
				exit(EXIT_FAILURE);
			}
			printf("\e[42mCONNECTION ESTABLISHED SUCCESSFULLY [ WRONLY ]\e[0m\n");
			
			//FIFO4 for read purpose
			if(access(FIFO4,F_OK) == -1)
			{
				ret = mkfifo(FIFO4,666);
				if(ret == -1)
				{
					perror("\e[41mFIFO4\e[0m");
					exit(EXIT_FAILURE);
				}
			}
			ret4 = open(FIFO4,O_RDONLY);
			if(ret4 == -1)
			{
				perror("\e[41mOPEN\e[0m");
				exit(EXIT_FAILURE);
			}
			printf("\e[42mCONNECTION ESTABLISHED SUCCESSFULLY [ RDONLY ]\e[0m\n");
			write(ret3,&rr,sizeof(Request));
			read(ret4,&rs,sizeof(Result));
		/*	r2 = realloc(r2,i+1);
			*(r2+i) = rs;
				
		*/	printf("\e[44m%s\e[0m : The result successfully fetched in server!\n",__FILE__);
			kill(rs.pid,SIGINT);
			write(ret2,&rs,sizeof(Result));
			printf("\e[43m%s : %d pid served!\e[0m\n",__func__,rs.pid);
	}

	}
	printf("\e[44m%s\e[0m : Ends\n",__FILE__);
	//return 0;
}
