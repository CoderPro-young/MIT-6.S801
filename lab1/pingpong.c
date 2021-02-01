#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
	int pd[2]; 
	char buf[64]; 
	pipe(pd); 
	
	if(!fork()){
		printf("%d: received ping\n", getpid()); 
		write(pd[1], "hello world\n", 12); 
		exit(0); 
	}
	
	read(pd[0], buf, 63); 
	write(pd[1], "hello world\n", 12); 
	printf("%d: received pong\n", getpid()); 
	exit(0); 
}
