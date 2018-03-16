#include "FUNC.c"

int main(int argc, char** argv){

if(argc<2||strlen(argv[1])==0||strlen(argv[2])==0){
printf("Not Enough Arguments");
return -1;
}

//Try to open a file as a directory, if it is a directory, skip if statement to other case
//If it is a file, U is NULL and open the file in current directory for the inverted index
DIR* U = opendir(argv[2]);

if(access(argv[2],R_OK)==0&&U==NULL){
//Create XML IN . DIR
printf("ACCEESSED");
//Insert one file
char* FileName=malloc(3*sizeof(char));
FileName[0]='.';
FileName[1]='/';
FileName[2]='\0';
strcat(FileName,argv[2]);
//Create path to file name.
printf("FILE: %s",FileName);
Insert(FileName,FileName,NULL);

O=MSort(O);

PrintList(argv[1]);

char c = 'y';
if(access(argv[1],R_OK)==0){

printf("\nAre you sure you want to delete this file? Enter y for yes, anything else for no.\n");
scanf("%c",&c);
}
if(c=='y'){

FILE* F = fopen(argv[1],"w+");
PutFile(F);

}
return 0;
}
closedir(U);
char* c = malloc(3*sizeof(char));
c[0]='.';
c[1]='/';
c[2]='\0';

strcat(c,argv[2]);

char* P = malloc(2*sizeof(char));
P[0]='.';
P[1]='\0';

ReadDir(P,c,false);

//return 0;
//DeleteList();
//exit(0);

O=MSort(O);

PrintList(argv[1]);

printf("\n FINALE \n");

char d = 'y';

if(access(argv[1],R_OK)==0){
printf("\nAre you sure you want to delete this file? Enter y for yes, anything else for no.\n");
scanf("%c",&d);
}

if(d=='y'){

FILE* F = fopen(argv[1],"w+");
if(F==NULL){
printf("\nERROR, CANNOT OPEN FILE!\n");
DeleteList();
return 0;
}
PutFile(F);

}


//exit
DeleteList();
//
return 0;
}
