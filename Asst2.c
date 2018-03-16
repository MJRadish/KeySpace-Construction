#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>

typedef struct my_node{
	int occurence;
	char* word;  
	struct my_node* right;
	struct my_node* left;
	}wordNode;

typedef struct my_fileNode{
	char* name; 
	struct my_fileNode* right;
	struct my_fileNode* left;
	wordNode* next;

	}fileNode;


char buf[100];
FILE* targetFile;
fileNode* head;
wordNode* masterWordListHead;    
wordNode* outputHead; 

void printTreeWord(wordNode* ptr){//Function prints the tree starting from head in lvr order//

	if(ptr == NULL)
		return;
	printTreeWord(ptr->left);
	fprintf(targetFile,"\t\t<file name=\"%s\">",ptr->word);
	fprintf(targetFile,"%d</file>\n",ptr->occurence);
	printTreeWord(ptr->right);
}

void printTree(fileNode* ptr){//Function prints the tree starting from head in lvr order//

	if(ptr == NULL)
		return;
	printTree(ptr->left);
	printf("FILE: %s\n",ptr->name);
	printTreeWord(ptr->next);
	printf("\n");
	printTree(ptr->right);
}
void freeOutput(wordNode* ptr){

	if(ptr == NULL)
		return;

	freeOutput(ptr->left);
	freeOutput(ptr->right);
	
	free(ptr);
	}

void freeWordNodeTree(wordNode* ptr){

	if(ptr == NULL)
		return;

	freeWordNodeTree(ptr->left);
	freeWordNodeTree(ptr->right);
	free(ptr->word);
	free(ptr);
	}

void freeFileNodeTree(fileNode* ptr){

	if(ptr == NULL)
		return;

	freeFileNodeTree(ptr->left);
	freeFileNodeTree(ptr->right);

	freeWordNodeTree(ptr->next);

	free(ptr->name);
	free(ptr);
	}

int size(char* ptr){
	int count = 0;
	int index = 0;
	while(1){
		if(ptr[index] == '\0')
			return count;
		else{
			count++;
			index++;
		}
	}
}

int isLegal(char c){//returns 1 if so

	if( (c >= 97 && c <= 122) || (c >= 65 && c <= 90) || (c >= 48 && c <= 57) )
		return 1;

	return 0;
	}

fileNode* searchTree(char* fileName, fileNode* ptr){

	int check = 0;	

	while(ptr!= NULL){
		check = strcmp(fileName,ptr->name);
		if(check == 0)
			return ptr;

		if(check > 0)
			ptr = ptr->right;
		if(check < 0)
			ptr = ptr->left;
		}
	return NULL;
}

void pushTreeWordHelper(wordNode* ptr, wordNode* tmp, char* word){
	int check = 0;
	while(ptr!= NULL){

		check = strcmp(ptr->word,word); //seeing which of the two strings is larger based on the return value//

		if(check == 0){		//two strings are equal//
			free(ptr->word);
			ptr->word = word;//
			ptr->occurence += 1;
			free(tmp);	//freeing the newly created node bc its a duplicate and not needed// 	
			return;
				}
		else if(check < 0){		//input string is larger//
			if(ptr->right == NULL){// if the right child of ptr is null, then it places the node there, otherwise the while loop continues onward//
				ptr->right = tmp;
				return;
				}
			ptr = ptr->right;
			}
		else{				//input string is smaller//				
			if(ptr->left == NULL){// if the left child of ptr is null, then it places the node there, otherwise the while loop continues onward//
				ptr->left = tmp;
				return;
				}
			ptr = ptr->left;
			}

		}


}
void pushMasterWord(char* word){

		wordNode* tmp = (wordNode*)malloc(sizeof(wordNode));	
		tmp->word = word;
		tmp->occurence = 1;
		tmp->right = NULL;
		tmp->left = NULL;

		if(masterWordListHead == NULL){
			masterWordListHead = tmp;
			return;
			}
	pushTreeWordHelper(masterWordListHead,tmp,word);
	}

void pushTreeWord(char* fileName, char* word){
		
		wordNode* tmp = (wordNode*)malloc(sizeof(wordNode));	
		tmp->word = word;
		tmp->occurence = 1;
		tmp->right = NULL;
		tmp->left = NULL;
		
	fileNode * wordHead = searchTree(fileName,head);
	if(wordHead == NULL){
		printf("failure pushing word: %s on file: %s \n",word,fileName);
		return;
		}
	if(wordHead->next == NULL){
		wordHead->next = tmp;
		return;
			}

	pushTreeWordHelper(wordHead->next, tmp, word);
	}

void pushTree(char* input){//Standard push function for a tree, places the newly created node in the tree based on its word(input) value//
	
		fileNode* tmp = (fileNode*)malloc(sizeof(fileNode));	
		tmp->name = input;
		
		tmp->right = NULL;
		tmp->left = NULL;
		tmp->next = NULL;

	if(head == NULL){	//base case for when head is null//
		head = tmp;
		
		return;
		}

	int check; 
	fileNode* ptr = head;

	while(ptr!= NULL){

		check = strcmp(ptr->name,input); //seeing which of the two strings is larger based on the return value//

		if(check == 0){		//two strings are equal//
			//ptr->mult = ptr->mult + 1;
			//free(input);
			free(ptr->name);
			ptr->name = input;//
			free(tmp);	//freeing the newly created node bc its a duplicate and not needed// 	
			return;
				}
		else if(check < 0){		//input string is larger//
			if(ptr->right == NULL){// if the right child of ptr is null, then it places the node there, otherwise the while loop continues onward//
				ptr->right = tmp;
				return;
				}
			ptr = ptr->right;
			}
		else{				//input string is smaller//				
			if(ptr->left == NULL){// if the left child of ptr is null, then it places the node there, otherwise the while loop continues onward//
				ptr->left = tmp;
				return;
				}
			ptr = ptr->left;
			}

		}
	
	}

void pushIntoOutput(wordNode* tmp){
	if(outputHead == NULL){
		outputHead = tmp;
		return;
			}
	wordNode* ptr = outputHead;
	while(ptr != NULL){

		

		if(ptr->occurence <= tmp->occurence){		
			if(ptr->right == NULL){
				ptr->right = tmp;
				return;
				}
			ptr = ptr->right;
			}
		else{								
			if(ptr->left == NULL){
				ptr->left = tmp;
				return;
				}
			ptr = ptr->left;
			}
		}	
}

void search(wordNode* target,fileNode* tmpHead){
	
	wordNode* ptr = tmpHead->next;
	int check = 0;
	while(ptr!= NULL){
		check = strcmp(ptr->word,target->word); 
		if(check == 0){		
			wordNode* tmp = (wordNode*)malloc(sizeof(wordNode));
			tmp->word = tmpHead->name;
			tmp->occurence = ptr->occurence;
			tmp->right = NULL;
			tmp->left = NULL;
			pushIntoOutput(tmp);
			
			return;
				}
		else if(check < 0)		
			ptr = ptr->right;
			
		else							
			ptr = ptr->left;
		}
}

void mainAlgo2(wordNode* ptr,fileNode* tmpHead){

	if(tmpHead == NULL)
		return;
	mainAlgo2(ptr,tmpHead->left);
	search(ptr,tmpHead);
	mainAlgo2(ptr,tmpHead->right);
}
void mainAlgo1(wordNode* ptr){
	
	if(ptr == NULL)
		return;
	mainAlgo1(ptr->left);
	fprintf(targetFile,"\t<word text =\"%s\">\n",ptr->word);
	mainAlgo2(ptr,head);

	printTreeWord(outputHead);	
	fprintf(targetFile,"\t<\\word>\n");
	freeOutput(outputHead);
	outputHead = NULL;

	mainAlgo1(ptr->right);
}

void tokenize(int bytes, char* d_name){
	
	int start = 0;
	int end = 0;
	int k,j;
	for(k = 0; k < bytes; k++){
		
		if( isLegal(buf[k])){
			start = k;
			buf[k] = tolower(buf[k]);
				for(j = k; j < bytes; j++){

					if(isLegal(buf[j]) == 0){
						end = j-1;
						char* tmp = (char*)malloc( (end -start) + 2 );
						strncpy(tmp,buf + start, (end -start) + 1);

						tmp[(end -start)+1] = '\0';
						char* tmp1 = (char*)malloc( (end -start) + 2 );
						strncpy(tmp1,buf + start, (end -start) + 1);

						tmp1[(end -start)+1] = '\0';
						pushMasterWord(tmp1);
						pushTreeWord(d_name,tmp);
						k = j;
						break;
							}
					buf[j] = tolower(buf[j]);	
						}
					}
				}
	}

void clearBuf(){
	int i;
	for(i = 0; i < 100; i++){
		buf[i] = 0;
		}
		}

char* buildResult(char* d_name, char* currentDir){

	char *result = (char*)malloc( size(d_name)+size(currentDir) + 2);

	strcpy(result, currentDir);
	strcat(result,"/");
	strcat(result, d_name );
	return result;
}

void readFile(char* d_name, char* currentDir,int flag){
	
	char* result;
	if(flag == 0)
		result = buildResult(d_name,currentDir);
	else
		result = currentDir;
	printf("path for file: %s\n",result);
	printf("name: %s\n",d_name);
	int fd;
	clearBuf();
	int BUFSIZE = 100;
	int bytes;
	fd = open(result,  O_RDONLY);
    if (fd == -1) {
	printf("couldn't open file-> %s Error: %s\n",d_name,strerror(errno));
      
        return ;
    }   
   bytes = read(fd, buf, BUFSIZE);
    if (bytes == -1) {
        perror("input");
        bytes = 0;
    } else {
	buf[bytes] = '\0';
        printf("Read %d bytes string was: %s \n", bytes,buf);
    }   

	char* name = (char*)malloc( size(d_name) + 1);
	strcpy(name,d_name);
	name[size(d_name)] = '\0';
	printf("this is the name: %s \n",name);
	pushTree(name);
	
	tokenize(bytes,name); 
	if(flag == 0)
		free(result);

	int checkClose = close(fd);
	if(checkClose == -1)
		printf("couldn't close file-> %s Error: %s\n",d_name,strerror(errno));
}

void printDir(char* currentDir){

	DIR * dir;
	struct dirent *sd;
	dir = opendir(currentDir);

	if (!dir) {
	printf("Couldn't open directory-> %s Error: %s\n",currentDir,strerror(errno));
      	return;
    }
	errno = 0;

	while( (sd = readdir(dir)) != NULL){
				
		if(sd->d_type == DT_DIR ){

			if( strcmp(sd->d_name, "..") != 0 && strcmp(sd->d_name, ".") != 0 ){
			char* result = buildResult(sd->d_name,currentDir);	
			printf("Entering dir: %s\n",result);
			printDir(result);
			
			free(result);	
			}	
		}
		else if((sd->d_type == DT_REG )){// would need to put something here to stop is from reading those weird files
				readFile(sd->d_name,currentDir,0);
				}
		}
	if(errno != 0)
		printf("couldn't read file stream-> %s Error: %s\n",currentDir,strerror(errno));

	int checkClosed = closedir(dir);
	if(checkClosed == -1)
		printf("couldn't close current directory-> %s Error: %s\n",currentDir,strerror(errno));

}
int file_exist (char *filename)
{
  struct stat   buffer;   
  return (stat (filename, &buffer) == 0);
}

char* getNameOfFile(char* path){
	int last = 0;
	int size = 0;
	while(1){
		if(path[size] == '\0')
			break;
		
		if(path[size] == '/')
			last = size;
		size ++;
		}
	char* fName = (char*)malloc(sizeof(char)* (size - last)+1);
	strncpy(fName,path+last+1,(size-last));
	fName[(size-last)] = '\0';
	return fName;
	}

int main(int argc, char** argv){

	if(argc != 3){
		printf("Error: Need 2 arguments. Ending program now.\n");
		return 0;
		}
	if (file_exist (argv[1])){
		printf ("Enter the number 1 if you wish to overwrite file %s, otherwise enter whatever: ",argv[1]);
		int check;
		scanf("%d",&check);
		if(check == 1){
			printf("Ok then im overwriting I guess\n");
			FILE* fp;
			fp = fopen(argv[1],"w");
			targetFile = fp;
			}
		else{
			printf("System respects your wishes unfortunately, ending program now :(\n");
			return 0;
			}
		}	
	else{
		FILE* fp;
		fp = fopen(argv[1],"ab+");
		targetFile = fp;
		}
	struct stat sb;
	int flag = -1;
	if (stat(argv[2], &sb) == 0 && S_ISDIR(sb.st_mode))//its a dir
		flag = 0;
	if (stat(argv[2], &sb) == 0 && S_ISREG(sb.st_mode))//its a file
		flag = 1;
   		
	if(flag == -1){
		printf("Error: Did not recognize input type. Ending program now.\n");
		return 0;
		}
	head = NULL;
	masterWordListHead = NULL;
	outputHead= NULL;    

	fprintf(targetFile,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(targetFile,"</fileIndex>\n");

	if(flag == 0)
		printDir(argv[2]);
	else{
	  	char* tmp = getNameOfFile(argv[2]);
	        readFile(tmp, argv[2],1);  
		free(tmp);	
		}
	mainAlgo1(masterWordListHead);
	freeFileNodeTree(head);
	freeWordNodeTree(masterWordListHead);
	
	fprintf(targetFile,"</fileIndex>");
	fclose(targetFile);
	return 0;
}


