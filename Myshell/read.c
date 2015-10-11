#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>
char commandName[1024];
char *argCommand[100];
char *argvar[100];
char *argvar2[100];
char *argback[100];
int status,i,t;
int check_back=0;
char *argarg[100];
pid_t pid;
//Displaying the prompt
void type_prompt(char *promptName){
        if(promptName!=NULL){
                printf("myshell [%s]: ",promptName);
        }
        else{
                printf("myshell: ");
        }

}
//Function for semicolon
void readsemicolon(){
        fflush(stdout);
        char delim[2]=";";
        i=0;
        int j=0;
        argvar2[0]=strtok(commandName,delim);
        while(argvar2[i] != NULL){
                i++;
                argvar2[i]=strtok(NULL,delim);
        }


}
//Reads command from the console
void readline(){
	fflush(stdout);
        char delim[2]="|";
	i=0;
	int j=0;
        argvar[0]=strtok(commandName,delim);
        while(argvar[i] != NULL){
                i++;
                argvar[i]=strtok(NULL,delim);
        }
	for(i=0;argvar[i]!=NULL;i++){
                for(j=0;argvar[i][j]!=NULL;j++){
                	if(argvar[i][j]=='"'){
                        	argvar[i][j]=' ';
                        }
                }
        }
}

/*void afterReadLine(){
        fflush(stdout);
        char delim[2]=" ";
        i=0;
        argvar[0]=strtok(commandName,delim);
        while(argvar[i] != NULL){
                //printf("inside readline for pipe %s\n",argvar[i]);
                //check_pipe=1;
                i++;
                argvar[i]=strtok(NULL,delim);
        }
        //for(i=0;argvar[i]!=NULL;i++){
        //         printf("inside afterReadline for pipe %s\n",argvar[i]);
        //}
         //printf("inside readline for pipe %s\n",argvar[i]);


}*/
//Implementing cd as shell builtin
void changeDirectory() {
	int returnValue,j=0;
  	if (argarg[1] != NULL) {
		setenv("OLDPWD", getenv("PWD"), 1);
      		returnValue = chdir(argarg[1]);
      		setenv("PWD", (char*)get_current_dir_name(),1);
  	}
		printf("Current directory: %s\n", getenv("PWD"));
}
//Basic commands executed
void process(char **argex){
       	signal(SIGCHLD, SIG_IGN);
	 if((pid=fork())!=0){
                waitpid(-1,&status,0);
        }
	else if(pid==-1){
		perror(" error in pid for process");
	}
        else{
                execvp(*argex,argex);
        }
}
//Parser
void parse(char * input, char **argex, char param[]){
        int p=0;
        while (*input != '\0'){
        	while(*input == ' ' || *input=='\t' ||*input =='\n'|| *input =='<' || *input == '>'  ){
                	if( *input=='<' || (((*input =='>')&&(*(input+1)!='>'))) ){

                        	param[p++]=*input;
                        }	
			else if( (*input =='>')&&(*(input+1)=='>')){
				param[p++]='?';
				*input = '\0';
                          	input++;
			}
                        *input = '\0';
                        input++;
                }
                *argex = input;
                argex++;
                while(*input!= '\0' && *input!=' ' && *input!='\t' && *input!='\n' && *input!='<' && *input!='>')
                	input++;
        }
        *argex = '\0';
	param[p] = '\0';
}

/*void fork_read(char **args, char *param){
     	pid = fork();
        int file;        
	int j=0;
         signal(SIGCHLD, SIG_IGN);
	if(pid<0){
          //error
        perror("error while executing the command");
        }
        else if(pid==0){
                //in child
                printf("\nIn child: %c %d", param,strcasecmp(args[0],"cat"));
                if(!strcasecmp(args[0],"cat")){
                       printf("inside cat");
                        if((*param)=='<'){
				printf("for read");
                                file = open(args[i],O_RDONLY);
                                }
                        else if((*param)=='>'){
				//printf("for write");
				//fflush(stdout);
				close(args[i]);
                                file = creat(args[i],O_WRONLY);
                                dup2(file,1);
                                }
                }
                execvp(*args,args);
        }else{
                printf("\nIn parent: %d\n",getpid());
                waitpid(-1,&status,0);
        }
}*/

/*void rec_pipe(char **args){
	printf("inside pipe function");
        int pipe_command[2];
        pipe(pipe_command);
        if((pid=fork())==0){
		//close(1);
                dup2(1,pipe_command[1]);
	//	char *tp[]={"j1",NULL};
		 execvp(*args,argvar);
        }
        else if(pid==-1){
                perror("fork");
                exit(0);
        }
        else if(pid>0){
                waitpid(-1,&status,0);
		//close(0);
                dup2(0,pipe_command[0]);
                 execvp(*argarg,argarg);
        }    
}*/
//Create a background process
void backgrounding(char **args){
                 
	switch(pid=fork()){
	case -1:
		printf("Cannot Fork\n");
		exit(-1);
	case 0:
		execvp(argarg[0],argarg);
		exit(0);
	default:
		printf("%d\n",pid);
	}
}
//InDirection
void fork_read(char **args){
        pid = fork();
        int file;
        int j=0;
	 signal(SIGCHLD, SIG_IGN);
        if(pid<0){
        	perror("error while executing the command");
        }
        else if(pid==0){
                file = open(args[i],O_RDONLY);
                execvp(*args,args);
        }
	else{
                waitpid(-1,&status,0);
        }
}
//OutDirection
void fork_write(char **args){
        
	pid = fork();
        int file;
        int j=0;
	 signal(SIGCHLD, SIG_IGN);
        if(pid<0){
	        perror("error while executing the command");
        }
        else if(pid==0){
                file = creat(args[i],0644);
		dup2(file,1);
                execvp(*args,argvar);
        }
	else{
                waitpid(-1,&status,0);
        }
}


//Append
void fork_append(char **args){

	pid = fork();
        int file;
        int j=0;
	 signal(SIGCHLD, SIG_IGN);
        if(pid<0){
	        perror("error while executing the command");
        }
        else if(pid==0){
                file = open(args[i],O_APPEND|O_WRONLY);
		dup2(file,1);
                execvp(*args,argvar);
        }
	else{
                waitpid(-1,&status,0);
        }
}
//Main function
int main(int argc, char * argv[]){
        int i=0,j=0,is,js;
	char param[100];
        while(1){
		
                fflush(stdout);
                type_prompt(argv[1]);
		gets(commandName);
		//ctrl+d to exit
		if(feof(stdin)){
			exit(0);
		}
                if(!strcasecmp(commandName,"exit")){
                        exit(0);
                }
		readsemicolon();
		for(is=0;argvar2[is]!=NULL;is++){
			for(js=0;argvar2[is][js]!=NULL;js++){
				commandName[js]=argvar2[is][js];
			}
			//param[0]='\0';
			commandName[js]='\0';
			readline();
			for(i=0;argvar[i]!=NULL;i++){
				parse(argvar[i],argarg,param);
			}
			for(i=0;argarg[i]!=NULL;i++){
				if(!(strcasecmp(argarg[i],"&"))){
					argarg[i]=NULL;
					check_back=1;	
					backgrounding(argarg);
				}
			}
			if(param[0]=='\0' && (strcasecmp(argarg[0],"cd"))&&check_back==0){
				//printf("inside process");
				process(argarg);
			}
			else if(!(strcasecmp(argarg[0],"cd"))&&check_back==0  ){
				changeDirectory();
			}
		
			for( i=0;param[i]!='\0';i++){

				if((!strcasecmp(argarg[0],"cat")) && param[i]=='<'){
					fork_read(argarg);
				}
				else if((!strcasecmp(argarg[0],"cat")) && param[i]=='>'){
					fork_write(argarg);
				}
				else if((!strcasecmp(argarg[0],"cat")) && param[i]=='?'){
                                	fork_append(argarg);
                        	}

			}
		
		}
        }

}
