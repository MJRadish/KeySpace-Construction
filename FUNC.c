#include "HEADER.h"



void ReadDir(char* Path,char* Path2, bool BASE){
DIR* currentDir = NULL;
struct dirent* currentThing=NULL;
//if(access(Path2,R_OK)
if(strlen(Path2)>0||BASE==false){
currentDir= opendir(Path2);
if(access(Path2,R_OK)!=0){

if(Path!=NULL){
free(Path);
Path=NULL;
}
if(Path2!=NULL){
free(Path2);
Path2=NULL;
}

closedir(currentDir);
return;
}
currentThing=NULL;
}
else{
currentDir= opendir(Path);
if(access(Path,R_OK)!=0){

if(Path!=NULL){
free(Path);
Path=NULL;
}
if(Path2!=NULL){
free(Path2);
Path2=NULL;
}

closedir(currentDir);
return;
}
currentThing=NULL;
}

char* i=NULL;
char* i2=NULL;

do{
if(currentDir!=NULL)
currentThing=readdir(currentDir);
if(currentThing==NULL){
printf("\nEnd of directory reading\n");
break;
}
if(currentThing->d_type==DT_REG){
//printf("\nFOUND A FILE\n");

printf("\n %s \n",currentThing->d_name);
//Only have to append /!!
//CatFile
if(BASE==true){
//Free Path Name

if(strlen(Path)>0&&Path!=NULL&&sizeof(Path)>0){
free(Path);
Path=NULL;
}

//char** D = &(currentThing->d_name);
//CatDir("./",D);
Path = toString(currentThing->d_name);

char* u = malloc(3*sizeof(char));
u[0]='.';
u[1]='/';
u[2]='\0';
//CatDir(u,&Path);
strcat(u,Path);
free(Path);
Path=NULL;
Path=u;


//printf("PATH2 ACCESS:%s",Path2);

if(access(Path,R_OK)==0){

printf("\nReadable File: %s\n",u);

i = toString(Path);
i2 = toString(Path);

Insert(i, i2, NULL);
i=NULL;

free(i2);
i2=NULL;

//PrintList(".");

//DeleteList();

//exit(0);
}
else{

printf("\nUnreadable file\n");

}

}
else{
//Dont free Path Name
char* c = toString(currentThing->d_name);

printf("PATH2 ACCESS:%s",Path2);
char* u = NULL;
if(Path2[strlen(Path2)-1]!='/'){
u=malloc(2*sizeof(char));
u[0]='/';
u[1]='\0';
CatFile(u,&c);
}
strcat(Path2,c);
///////////////////
/*
if(c!=NULL){
free(c);
c=NULL;
}
*/
int k=countOcc("/",&Path2)-1;

while(access(Path2,R_OK)!=0&&k>1){
printf("\nUnreadable file...\n");
PrevPath(&Path2,k);
k=countOcc("/",&Path2)-1;
strcat(Path2,c);
}
if(access(Path2,R_OK)==0){
printf("\nReadable File... Using %s\n",Path2);

i = toString(Path2);
i2 = toString(Path2);

Insert(i, i2, NULL);

//free(i);
i=NULL;
free(i2);
i2=NULL;
}
else{
printf("\nUNABLE TO FIND FILE,ERROR\n");
break;
}
printf("\n FILE THAT IS NOT IN BASE: %s\n", Path2);
printf("NUMBER OF /:%d",countOcc("/",&Path2));
free(c);
c=NULL;
//return;
PrevPath(&Path2,countOcc("/",&Path2));
//return;
printf("DECREASED PATH2:%s",Path2);
//return;
//exit(0);
}
}


else if(currentThing->d_type==DT_DIR){
printf("\n%s\n",currentThing->d_name);
//Wher Hit next Dir outside of BAS)E
if(strcmp(currentThing->d_name,".")==0||strcmp(currentThing->d_name,"..")==0){
continue;
}

//str
if(BASE==true){
// Append 
//if(strlen(Path2)>1){
//Delete Path

/*
free(Path2);
Path2=NULL;
//char* q =NULL;
Path2= malloc(sizeof(char));
Path2[0]='\0';
*/
//Path2[0]='\0';
//Path2=toString("\0");
//}

char* s = toString(currentThing->d_name);

strcat(Path2,s);

free(s);
s=NULL;

//Path2=q;
printf("PATH2: %s",Path2);

if(Path2[strlen(Path2)-1]!='/'){

char* u = malloc(3*sizeof(char));

u[0]='.';
u[1]='/';
u[2]='\0';

//
//CatDir(u,&Path2);
strcat(u,Path2);
free(Path2);
Path2=NULL;
Path2=u;
}

ReadDir(toString(Path),toString(Path2),false);
//free(Path2);
//Path2=NULL;
}


else{

// Append / to next Dir!
//CatFile("/",&Path2);
char* c = toString(currentThing->d_name);

if(Path2[strlen(Path2)-1]!='/'){
char* u = malloc(2*sizeof(char));
u[0]='/';
u[1]='\0';
CatFile(u,&c);
}
if(Path2!=NULL){
strcat(Path2,c);
free(c);
c=NULL;
}
else{
break;}
printf("\n\nPATH 2: %s\n\n",Path2);
//exit(0);
//ReadDir(Path,Path2,false);
//exit(0);
//closedir(currentDir);

//STRING VERY IMPORTANT
//ReadDir((Path),(Path2),false);
ReadDir(toString(Path),toString(Path2),false);
//TO STRING FTW
}

}

//printf("PATH 2:%s",Path2);
printf("\n\n");
}while(currentThing!=NULL);

if(i2!=NULL){
free(i2);
i2=NULL;
}
if(i!=NULL){
free(i);
i=NULL;
}

if(Path!=NULL){
free(Path);
Path=NULL;
}
if(Path2!=NULL){
free(Path2);
Path2=NULL;
}

closedir(currentDir);

//exit(0);
return;
}
//
//void CatDir(char* app,char** C);
//
//void CatFile(char* app,char**C);
//
//
void CatDir(char* app, char** C){

if(C==NULL){
return;
}
if(*C==NULL){

return;
}

//int i = strlen(*C);
//char* z = malloc(strlen(app)*sizeof(char));

//strcpy(z,app);
strcat(app,*C);
/*
if(strlen(*C)>0){
free(*C);
(*C)=NULL;
}
*/
free(*C);
/*
(*C)=NULL;
(*C)=app;
*/
return;
}


void CatFile(char* app, char** C){
//char*z=malloc(strlen(app)*sizeof(char));
//z[strlen(app)-1]='\0';
//strcpy(z,app);
//z[strlen(app)-1]='\0';
//free(app);
//app=NULL;

//strcat(z,(*C));
strcat(app,(*C));

free(*C);

*C=NULL;
*C=app;

return;
}

char* toString(char* C){

char* v = malloc((strlen(C)+1)*sizeof(char));
bzero(v,strlen(C)+1);
int i=0;
char u = C[i];
while(u!='\0'){
v[i]=u;
i++;
u=C[i];
}

return v;
//free(v);
}


bool FileinDir(char* Path){
struct dirent* currentThing;
DIR* Directory = opendir(".");

do{
if(Directory!=NULL)
currentThing=readdir(Directory);
if(currentThing==NULL){
printf("\nDone Reading Directory\n");
break;
}
if(strcmp(currentThing->d_name,Path)==0&&currentThing->d_type==DT_REG){
printf("\n\nFOUND A MATCH!\n\n");
return true;
}
}while(currentThing!=NULL);



return false;
}

//Go to the NextLth line!!
void PrevPath(char**C,int NextL){
int occ=0;
int i=strlen(*C);
printf("LENGTH: %d",i);
//char c = (*C)[i];
int j=0;
char* e = malloc(2*sizeof(char));
e[0] =(*C)[j];
e[1]='\0';
//int countL = 0;


char* g=malloc(sizeof(char));
g[0]='\0';


while(e[0]!='\0'){
if(e[0]=='/'){
occ++;
}
if(occ==NextL){
printf("\nFOUND THE LAST LINKER\n");

break;
}
strcat(g,e);
j++;
e[0]=(*C)[j];
}

free(*C);
*C=NULL;

*C=g;

free(e);
e=NULL;


return;
}

int countOcc(char* n, char**C){
//int i = strlen(n);
int j=0;
int k=0;
int count=0;
char c = (*C)[j];
while(c!='\0'){
if(c==n[k]){
k++;
}
else{
k=0;
}
if(n[k]=='\0'){
k=0;
count++;
}
j++;
c = (*C)[j];
}

return count;

}

//Will READ EVERY FILE
void Insert(char* Dir, char* FileName, char** Names){
//Dir and filename go hand in hand
Occurrences** D =&O;

//Occurrences ** OCC = D;

//Occurrences ** OCC2=D;

while(*D!=NULL){
if(strcmp((*D)->FileName,FileName)==0){
//ADD THIS ONTO IT
printf("\nDUPLICATE FILE\n");
break;
}
D=&((*D)->Next);
}

if(*D!=NULL){
//FOUND SAME FILE!
if(strcmp((*D)->FileName,FileName)==0){
//ADD THIS FileName onto same filename list, just increase (Names)
//BE SURE TO USE PATH NAME TO OPEN FILE
FILE* F = fopen(FileName,"r");
if(F==NULL){
printf("ERROR, CANNOT READ FILE");
return;
}

char* app = malloc(2*sizeof(char));
app[0]=' ';
app[1]='\0';

char* Word = malloc(sizeof(char));
Word[0]='\0';

int wordSize = 1;

bool isReadable = true;

while(fscanf(F, "%c", &(app[0])) != EOF){
if((int)app[0]<0||(int)app[0]>126){
printf("\nError, file is not readable\n");
isReadable=false;
break;
}


}

fclose(F);

if(isReadable==true){

printf("\n File: %s is readable, reading...\n",FileName);

F=fopen(FileName,"r");
if(F==NULL){
printf("Error, cannot read file");
return;
}

while(fscanf(F, "%c", &(app[0])) != EOF){



printf("%c",app[0]);

if(isalpha(app[0])||isdigit(app[0])){

app[0]=tolower(app[0]);
Word=realloc(Word,2*sizeof(char));
Word[wordSize-1]='\0';
strcat(Word,app);
wordSize++;
//TOKENZ
}

else if(Word[0]!='\0'){
//FOUND A WORD

char c = '/';
if(IncrOcc(&O,Word,strrchr(strrchr(FileName,c),(strrchr(FileName,c)[1])))==0){
//Found none, NEW WORD
while(*D!=NULL){
D=&((*D)->Next);
}
(*D)=malloc(sizeof(Occurrences));
(*D)->Name=malloc(sizeof(char));
(*D)->Name[wordSize-1]='\0';
strcpy((*D)->Name,Word);
char* d = strrchr(strrchr(FileName,c),(strrchr(FileName,c)[1]));
(*D)->FileName=malloc(strlen(d+1)*sizeof(char));
(*D)->FileName[strlen(d)]='\0';
printf("\n\n\n\n FILE TO STRING: %s\n\n\n", d);
strcpy((*D)->FileName,d);
//First Occurrence EVER
(*D)->Occurrence=1;
(*D)->Next=NULL;
D=&((*D)->Next);

PrintList("");

}


free(Word);
Word=NULL;
Word = malloc(sizeof(char));
Word[0]='\0';
wordSize=1;
//IncrOcc(OCC,Word);
//FIND OUT IF ALREADY EXISTS
//Not a char or a num... Potentially a space!
}

}
}
else{
printf("\n File: %s is not readable\n",FileName);
}

printf("\n\nEND FILE STREAM\n\n");
free(Word);
Word=NULL;
free(app);
app=NULL;
//Finished with file
fclose(F);
}

}

else if(*D==NULL){

printf("\nCREATE NEW LIST\n");
//Create a new

if(access(FileName,R_OK)==0){

printf("\nSEARCH FILENAME: %s IN DIRECTORY: %s\n",FileName,Dir);
//NOW MUST SEARCH THE FILE*
//BE SURE TO USE PATH NAME TO OPEN FILE
FILE* F = fopen(FileName,"r");

if(F==NULL){
printf("ERROR, CANNOT READ FILE");
return;
}
char* app = malloc(2*sizeof(char));
app[0]=' ';
app[1]='\0';


bool isReadable=true;

while(fscanf(F, "%c", &(app[0])) != EOF){
if((int)app[0]<0||(int)app[0]>126){
printf("\nFile is not readable\n\n");
isReadable=false;
break;
}
}

fclose(F);

char* Word = malloc(sizeof(char));
Word[0]='\0';


if(isReadable==true){

printf("\n File: %s is readable, reading...\n",FileName);

F=fopen(FileName,"r");

if(F==NULL){
printf("ERROR, CANNOT READ FILE");
return;
}


int wordSize = 1;
while(fscanf(F, "%c", &(app[0])) != EOF){


printf("%c",app[0]);

if(isalpha(app[0])||isdigit(app[0])){

app[0]=tolower(app[0]);
Word=realloc(Word,2*sizeof(char));
Word[wordSize-1]='\0';
strcat(Word,app);
wordSize++;
//TOKENZ
}

else if(Word[0]!='\0'){
//FOUND A WORD
char c = '/';
if(IncrOcc(&O,Word,strrchr(strrchr(FileName,c),(strrchr(FileName,c)[1])))==0){
//Found none, NEW WORD
(*D)=malloc(sizeof(Occurrences));
(*D)->Name=malloc(sizeof(char));
(*D)->Name[wordSize-1]='\0';
strcpy((*D)->Name,Word);
//char c = '/';
char* d = strrchr(FileName,c);
char* e = strrchr(d,d[1]);
printf("\n\nSTRING PIECE: %s\n\n",e);
//(*D)->FileName=malloc((strlen(e)+1)*sizeof(char));
//(*D)->FileName[strlen(e)]='\0';
printf("\n\n\n\n FILE TO STRING: %s\n\n\n", e);
(*D)->FileName=toString(e);
//free(e);
//e=NULL;
(*D)->Occurrence=1;

(*D)->Next=NULL;
D=&((*D)->Next);

PrintList("");



}

free(Word);
Word=NULL;
Word = malloc(sizeof(char));
Word[0]='\0';
wordSize=1;
}
}

}
else{
printf("\n File: %s is not readable\n",FileName);
}
printf("\n\nEND FILE STREAM\n\n");

free(Word);
Word=NULL;

free(app);
app=NULL;
//Finished with file
fclose(F);

//exit(0);
}
else{
printf("\nHAVE NO ACCESS TO FILE: %s\n",FileName);
}

}


if(Dir!=NULL)
free(Dir);
printf("\nReturning with FILENAME: %s\n",FileName);
return;
}

void PrintList(char* arg1){
//FILE*F = fopen

printf("\nPRINT LIST\n\n");

Occurrences** OCC =&O; //&((*G)->Occurrence);
while(*OCC!=NULL){
if((*OCC)!=NULL){
if((*OCC)->Name!=NULL){
printf("NAME: %s, IN FILE:%s ",(*OCC)->Name,(*OCC)->FileName);
}
}
printf("Number of Repeats: %d\n",(*OCC)->Occurrence);
OCC=&((*OCC)->Next);
}



}

void DeleteList(){

Occurrences* OCC;
Occurrences* OCC2; 

OCC = O;
while((OCC)!=NULL){
OCC2=((OCC)->Next);

if((OCC)->Name!=NULL){
free((OCC)->Name);
(OCC)->Name=NULL;
}


if((OCC)->FileName!=NULL){
free((OCC)->FileName);
(OCC)->FileName=NULL;
}


free((OCC));
(OCC)=NULL;

OCC=OCC2;
}

printf("Freed all of List");

return;
}

int IncrOcc(Occurrences** OCC, char* Word,char* FileName){
int count=0;
//If same word is found, increment the occurrence!
while(*OCC!=NULL){
if(strcmp((*OCC)->Name,Word)==0&&strcmp((*OCC)->FileName,FileName)==0){
//FOUND
(*OCC)->Occurrence++;
return (*OCC)->Occurrence;
//INCREMENTED BY ONE {WORD}
}
OCC=&((*OCC)->Next);
}


return count;
}

void PutFile(FILE*F){
//JUST A FILE

char** Visited = malloc(sizeof(char**));
//Visited[0]=malloc(sizeof(char*));
int i=0;

bool V = false;

Occurrences** U = &O;
PUT(F,1,NULL,0);
PUT(F,2,NULL,0);
char* ALL;
Occurrences** Back = &O;
while(*U!=NULL){
ALL = (*U)->Name;
Back=&((*U)->Next);

if(i>0){
if(isVisited(Visited,(*U)->Name,i)==false){
V=false;
}
else{
V=true;
}
}

if(V==false){
PUT(F,4,NULL,0);
PUT(F,6,(*U)->Name,(*U)->Occurrence);
}


while((*U)!=NULL){

if(strcmp((*U)->Name,ALL)==0&&isVisited(Visited,(*U)->Name,i)==false){
PUT(F,7,(*U)->Name,(*U)->Occurrence);

PUT(F,6,(*U)->FileName,(*U)->Occurrence);

PUT(F,8,(*U)->FileName,(*U)->Occurrence);

PUT(F,9,(*U)->Name,(*U)->Occurrence);

}
U=&((*U)->Next);
}
if(V==false)
PUT(F,5,NULL,0);

Visited[i]=malloc((strlen(ALL)+1)*sizeof(char));
bzero(Visited[i],(strlen(ALL)+1));
//Visited[i]=ALL;
strcpy(Visited[i],ALL);
printf("\n\nVISITED COPIED: %s\n\n",Visited[i]);
i++;
Visited[i]=malloc(sizeof(char*));
U=Back;
}
PUT(F,3,NULL,0);
//free(Visited);
//freeVisited
return;
}

void PUT(FILE*F, int type, char* Name, int count){
char* g = "<?xml version= \"1.0\" encoding=\"UTF-8\"?>";
char* f = "<fileIndex>";
char* h = "</fileIndex>";
char* k = "<word text =\"";
char* j = "</word>";
char* l = "<file name = \"";
char* m = "<";
char* n = "</file>";
char c = ' ';
c=g[0];
int i=0;

if(type==1){
c=g[0];
i=0;
while(c!='\0'){
fputc(c,F);
i++;
c=g[i];
}
fputc('\n',F);
}
else if(type==2){
c=f[0];
i=0;
while(c!='\0'){
fputc(c,F);
i++;
c=f[i];
}
//fputc('\n',F);
//fputc('\t',F);
}else if(type==3){
c=h[0];
i=0;

fputc('\n',F);
while(c!='\0'){
fputc(c,F);
i++;
c=h[i];
}
fputc('\n',F);
}
else if(type==4){
c=k[0];
i=0;

fputc('\n',F);

fputc('\t',F);

while(c!='\0'){
fputc(c,F);
i++;
c=k[i];
}
//fputc('\n',F);

//fputc('\t',F);

//fputc('\t',F);

}else if(type==5){
c=j[0];
i=0;
fputc('\n',F);
fputc('\t',F);

while(c!='\0'){
fputc(c,F);
i++;
c=j[i];
}
//fputc('\n',F);

//fputc('\t',F);

}
else if(type==6){
c=Name[0];
i=0;
//fputc('\"',F);


while(c!='\0'){
fputc(c,F);
i++;
c=Name[i];
}

fputc('\"',F);
fputc('>',F);

//fputc('\n',F);

//fputc('\t',F);

}
else if(type==7){
c=l[0];
i=0;

//fputc('\t',F);

fputc('\n',F);
fputc('\t',F);
fputc('\t',F);

while(c!='\0'){
fputc(c,F);
i++;
c=l[i];
}
//fprintf(F,"%d",count);



}
else if(type==8){
c=m[0];
i=0;

/*while(c!='\0'){
fputc(c,F);
i++;
c=m[i];
}
*/


fprintf(F,"%d",count);

//fputc('<',F);
//fprintf(F,"%d",count);

}

else if(type==9){
c=n[0];
i=0;

while(c!='\0'){
fputc(c,F);
i++;
c=n[i];
}
//
//fputc('\n',F);
//fputc('\t',F);
}
//
return;
}


//Recursive Merge Sort.
Occurrences* MSort(Occurrences* T){
//next
if(T==NULL||(T)->Next==NULL){
return (T);
}
//Set Middle node which is the end of the first half of the separated lists.
Occurrences* M;// = malloc(sizeof(Occurrences));
M=GM(T);
//Second half of the separated lists is always set to the next node of middle.
Occurrences* SH;// = malloc(sizeof(Occurrences));
SH=M->Next; 
//Set M->next to NULL in order to end the first half of the lists, Second half of the lists already has a NULL at the end.
M->Next=NULL;
//Implement merge function which takes multiple halves of the list using the head and then the second half. First the nodes are separated until there are pairs and either 1 extra node or not, then these pairs are compared first, then they are connected and compared until the entire list is connected and the list is then sorted.
return MG(MSort(T),MSort(SH));
//return NULL;
}

//Merge 
Occurrences* MG(Occurrences* O, Occurrences* P){
//Initialize nodes which point to the same address.
Occurrences * D = malloc(sizeof(Occurrences));
Occurrences * C;// = malloc(sizeof(Occurrences));
C=D;
//While Havent reached end of first and second half
while(O!=NULL&&P!=NULL){
//If the node entry of the first piece is equivalent or of less weight that the node entry of the second piece, set the next node of C to the first node. If the size of both pieces of the list are 1, then C would be NULL.
if(strcmp((O)->Name,(P)->Name)<=0){
C->Next=O;
O=((O)->Next);
}
//If node entry is of greater weight than the entry it is compared to, set C to the node that the first node is compared to. again, if the size of each piece is 1, C will be NULL.
else{ 
C->Next = P; 
P=((P)->Next);
}
C=C->Next;
}

//If the first node is NULL, then set the next node of C to P, otherwise, set the next node of C to O.
//Example case1:  
//		O->entry= "H"
//		P->entry= "h"
//		C->next->entry="h"
//		C->next->next->entry="H"
//		D->next->entry="H"
//
C->Next=(O==NULL) ? P:O;

//printf("\n\nCurrent is: %s\n\n",C->entry);
//Return the greater part of the block
return D->Next;
}

//Get middle node
Occurrences* GM(Occurrences* H){
if(H==NULL){return H;}
//Initialize a node which is located at the current head that goes to next node each iteration..
//Initialize node to head that goes to next next node each iteration.
//By the time the F node reaches end of list, S node will always be in the middle or appropriate location of the list in order to merge sort to work.
Occurrences* S;// = malloc(sizeof(Occurrences));
Occurrences* F;// = malloc(sizeof(Occurrences));
S=F=H;
//Iterate through list.
while(F->Next!=NULL&&F->Next->Next!=NULL){
S=S->Next;
F=F->Next->Next;
}
//Return the Node which arrived at the middle.
return S;
}

bool isVisited(char**V, char* entry, int i){
int j=0;

while(j<i){
if(strcmp(entry,V[j])==0){
return true;
}
j++;
}


return false;
}

/*
void freeVisited(char**V,int length){
//char* u = V[0];
int i=0;

//free(V);
//V=NULL;

while(i<length){
if(u!=NULL){
free(u);
u=NULL;
}
i++;
u=V[i];
}

//free(V);
//V=NULL;

return;
}
*/
