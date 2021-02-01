#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

//#define debug
#define DIRNO 1
#define REGNO 2

static void find(const char* path, const char* name){
	int fd; 
	struct stat st; 
	struct dirent de;
	char buf[512]; 	
	char* p; 	
	
	if((fd = open(path, 0)) < 0){

	}
	if(fstat(fd, &st) < 0){
		
	}

	switch(st.type){
	case T_DIR:
	    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
	      printf("path too long\n");
	      break;
	    }
	    strcpy(buf, path);
	    p = buf+strlen(buf);
	    *p++ = '/';
	#ifdef debug
	printf("dir is %s\n", buf); 
	#endif
	    while(read(fd, &de, sizeof(de)) == sizeof(de)){
		      if(de.inum == 0)
			continue;
		      memmove(p, de.name, DIRSIZ); //
		#ifdef debug
		printf("file name is %s \n", buf); 
		#endif 	
		      p[DIRSIZ] = 0;
		      if(stat(buf, &st) < 0){
			printf("cannot stat %s\n", buf);
			continue;
		      }
	      
	/* buf is filename parsed in path given */
	    	     if(strcmp(de.name, name) == 0){
			printf("%s\n", buf); 
		     }
		     if(st.type == DIRNO && (strcmp(de.name, ".") == 0)){
			continue; 
		     }
		     else if(st.type == DIRNO && (strcmp(de.name, "..") == 0)){
			continue; 
		     }
		     else if(st.type == DIRNO && (strcmp(de.name, name) != 0)){
			find(buf, name); 
		     }
		}
	    break;
	  }
	  close(fd);

}




int main(int argc, char* argv[])
{
	if(argc < 3){
		fprintf(2, "usage:<dir,file>\n"); 
		exit(1); 
	}
	
	find(argv[1], argv[2]); 	
	exit(0); 	
}
