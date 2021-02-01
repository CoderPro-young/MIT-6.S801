#include "kernel/types.h"
#include "kernel/stat.h"
//#include "user/ulib.c"
#include "user/user.h"

int main(int argc,char* argv[])
{
	if(argc < 2){
		//write(3, "usage:<num>\n", 16); 
		fprintf(2, "usage:<num>\n"); 
		exit(1); 
	}

	const char* arg = argv[1]; 
	int sleepTime = atoi(arg); 
	sleep(sleepTime); 

	exit(0); 


}
