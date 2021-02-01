#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

static int isMultiple(int num, int base){
	if(num % base == 0){
		return 1; 
	}	
	
	return 0; 
}

static void middle_layer(int pd[]){
	close(pd[1]);
	int ret; 
	int num;

	int pd_[2];
	pipe(pd_);  
	if(fork() == 0){
		middle_layer(pd_); 		
	}

	close(pd_[0]); 	 
	while((ret = read(pd[0], &num, sizeof(int))) == 0){

	}
	printf("prime: %d\n", num); 
	int base = num; 

	while((ret = read(pd[0], &num, sizeof(int))) != 0){
		if(isMultiple(num, base)){
			continue; 
		}
		write(pd_[1], &num, sizeof(int)); 
		
	}
	
	close(pd_[1]); 
	wait(0); 
	exit(0); 
}

int main()
{
	int pd[2]; 
	pipe(pd); 
	
	if(fork() == 0){
		middle_layer(pd); 
		//exit(0); 
	}

	close(pd[0]); 
	for(int i = 2; i < 36; i++){
		write(pd[1], &i, sizeof(int)); 
	}
	close(pd[1]); 	

	wait(0); 
	exit(0); 
}

