#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

//#define debug
#define BUFSIZE 128 

int main(int argc,char* argv[])
{
	printf("argc is %d \n", argc); 
	
	char buf[BUFSIZE];
	char* output[MAXARG];  
	char c; 
	int f_pos = 0; 
	int argnum = 0;
	int ret = 0;  
	
	memset(buf, 0, BUFSIZE);
	while((ret = read(0, &c, 1)) != 0){
		if(c == '\n'){
			buf[f_pos++] = '\0';
			output[argnum] = malloc(BUFSIZE);  
			memcpy(output[argnum++], buf, f_pos); 
			#ifdef debug
			printf("buf is %s\n", buf); 
			#endif 
			memset(buf, 0, BUFSIZE); 
			f_pos = 0; 
			continue; 
		}
		buf[f_pos++] = c; 
	}
	
	char* input[MAXARG]; 
	
	/* argv got by command */
	for(int i = 1; i < argc; i++){
		input[i-1] = malloc(strlen(argv[i])+1); 
		memcpy(input[i-1], argv[i], strlen(argv[i])+1); 
		#ifdef debug
		printf("input[%d] is %s\n", i, input[i-1]); 
		#endif 
	}
	/* argv got by stdin transmitted with xargs */
	for(int i = 0; i < argnum; i++){
		input[i+argc-1] = malloc(strlen(output[i])+1); 
		memcpy(input[i+argc-1], output[i], strlen(output[i])+1); 
		#ifdef debug
		printf("input[%d] is %s\n", i+argc, input[i+argc-1]); 
		#endif 
	}
	input[argc+argnum] = 0; 	

	if(fork() == 0){
		#ifdef debug
		printf("exec.\n"); 
		#endif 
		exec(input[0], input); 
		exit(0); 
	}
	wait(0);
	
	exit(0);  
}
