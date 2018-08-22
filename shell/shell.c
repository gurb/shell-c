#include <stdio.h>
#include <stdlib.h> // exit()
#include <string.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> // wait()
#include <fcntl.h>
#include "shell.h"

void clr_stdin(void){
	int ch;
	while((ch = getchar()) != '\n' && ch != EOF)
		;
}
//void fileRedirection(char c[]){}

void fileIORedirection(char *args[]){
	int fd0, fd1, i, in=0, out=0;
	char input[64], output[64];
	/*bu döngü '<' veya '>' karakterlerinin nerede olduğunu
	bulur ve bu komutun okunmaması için args[i]=NULL işlemi yapılır.*/
	for(i=0;args[i]!='\0';i++){
		if(strcmp(args[i]," <")==0)
		{
			args[i]=NULL;
			strcpy(input,args[i+1]);
			in = 1;
		}
		if(strcmp(args[i],">")==0)
		{
			args[i]=NULL;
			strcpy(output,args[i+1]);
			out = 1;
		}
	}
	
	if(in)
	{
		if((fd0 = open(input, O_RDONLY, 0600)) < 0){
			printf("Dosya açılmadı\n");
			exit(0);
		}
		dup2(fd0, STDIN_FILENO);
		close(fd0);
	}
	// eğer karakter katarında '>' bulunursa
	if(out)
	{
		if((fd1 = creat(output, 0644)) < 0){
			printf("Dosya açılmadı\n");
			exit(0);
		}
		//dup2() önceki dosya girdisindeki içeriği kopyalar.
		dup2(fd1, STDOUT_FILENO);
		close(fd1);
	}
}

int command(char c[]){
	char *args[128];
	char seperators[] = " ,.";
	char *token, *arg;
	int index = -1;
	token = strtok(c,seperators);
		/* code */
	arg = token;
	args[++index] = token;
	while(token != NULL){
		token = strtok(NULL,seperators);
		args[++index] = token;
	}
	args[++index] = '\0';
	pid = fork();
	int flag;

	fileIORedirection(args);

	if(pid==0){
		//----- giriş çıkış yönlendirme
		
		//child
		//execl("/bin/ls","ls", "-l",NULL);
		flag = execvp(arg,args);
		if(flag<0){
			//printf("hatalı\n");
		}
	}
	if(pid > 0){
		//parent
		wait(NULL);
		//printf("parent process!\n");
	}
	if(pid < 0){
		printf("fork error\n");
	}
	return 1;
}


void prompt(){
	printf("> ");
    fflush(stdout);
}

int main(int argc, char const *argv[]) {
    char cmd[max_char];
    //int sayac;
    char line[1024];
    while(true) {
    	prompt();
        memset(line, '\0', 1024);
	    if(fgets(cmd,max_char,stdin)!=NULL){
	    	if(strncmp(cmd,"quit\n",5)==0){
				fflush(stdout);
				exit(0);
			}
			printf("\n");
			fflush(stdout);
	    	if(cmd[strlen(cmd)-1] == '\n')
	    		cmd[strlen(cmd)-1] = '\0';
        	command(cmd);
	    }
        //command(cmd);
        //sleep(1);
    }
    printf("\n");
    return 0;
}