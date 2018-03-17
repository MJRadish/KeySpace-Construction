#include "HEADER.h"


//Read the directory given the path
void ReadDir(char* Path,char* Path2, bool BASE){
DIR* currentDir = NULL;
struct dirent* currentThing=NULL;
//Structures specifically designed to open directories

//If not within base directory, or the preceeding path's name exists.
if(strlen(Path2)>0||BASE==false){
currentDir= opendir(Path2);
//Check if path can be accessed, if not, free all used parameters and return.
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
  
//Set directory pointer to NULL

currentThing=NULL;
}
  
else{
//Case where within base directory.
currentDir= opendir(Path);
//Check if path can be accessed, if not, free all used parameters and return.
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
//Set directory pointer to NULL.
currentThing=NULL;
}

//char*'s used for string concatenations of pathname key characters like "." and "/".
char* i=NULL;
char* i2=NULL;

do{
if(currentDir!=NULL)
currentThing=readdir(currentDir);
//If readdir(currentDir) returns NULL, no more directories to read or an error occurred reading a directory.
if(currentThing==NULL){
printf("\nEnd of directory reading\n");
break;
}
  
//d_type's used will be DT_REG, which is a file, and DT_DIR, which is a directory.

if(currentThing->d_type==DT_REG){
//printf("\nFOUND A FILE\n");

printf("\n %s \n",currentThing->d_name);
  
//If within the base directory.
if(BASE==true){
//Free Path Name
if(strlen(Path)>0&&Path!=NULL&&sizeof(Path)>0){
free(Path);
Path=NULL;
}
//Set static d_name to a freeable string.  
Path = toString(currentThing->d_name);
  
char* u = malloc(3*sizeof(char));
u[0]='.';
u[1]='/';
u[2]='\0';

strcat(u,Path);
free(Path);
Path=NULL;
Path=u;

if(access(Path,R_OK)==0){

printf("\nReadable File: %s\n",u);

i = toString(Path);
i2 = toString(Path);
//"i" and "i2" used to insert char*'s into a linkes list which would later be freed, also Path is freed, so this is used to
//not free data twice.
//Takes copies of i and i2 char*'s, opens the path to filename, and inserts all tokens in a file into a linked list.
Insert(i, i2, NULL);

//Free the copied variables of Path.  
i=NULL;
free(i2);
i2=NULL;
}
else{

//An unreadable file has been found.
printf("\nUnreadable file\n");
  
}

}
else{
//Dont free Path Name.
char* c = toString(currentThing->d_name);

printf("PATH2 ACCESS:%s",Path2);
char* u = NULL;
if(Path2[strlen(Path2)-1]!='/'){
u=malloc(2*sizeof(char));
u[0]='/';
u[1]='\0';
//Create path outside of the base to the current file
CatFile(u,&c);
}

//Extend the path further
strcat(Path2,c);
  
int k=countOcc("/",&Path2)-1;


//If the file does not exist in the next directory, go to the previous directory and try again, until reach the base directory.
while(access(Path2,R_OK)!=0&&k>1){
printf("\nUnreadable file...\n");
PrevPath(&Path2,k);
k=countOcc("/",&Path2)-1;
strcat(Path2,c);
}
//Check if file is readable  
if(access(Path2,R_OK)==0){
printf("\nReadable File... Using %s\n",Path2);

//Create copies of the file path name
i = toString(Path2);
i2 = toString(Path2);
//Insert the file path name copies into linked list
Insert(i, i2, NULL);

i=NULL;
free(i2);
i2=NULL;
}
else{
//File could not be found given the path.
printf("\nFile cannot be read\n");
}
printf("\n FILE THAT IS NOT IN BASE: %s\n", Path2);
printf("NUMBER OF /:%d",countOcc("/",&Path2));
free(c);
c=NULL;
//If the file does not exist in the next directory, go to the previous directory and try again, until reach the base directory.
PrevPath(&Path2,countOcc("/",&Path2));
printf("DECREASED PATH2:%s",Path2);
}
}


else if(currentThing->d_type==DT_DIR){
printf("\n%s\n",currentThing->d_name);
//When hit next Dir outside of BASE
if(strcmp(currentThing->d_name,".")==0||strcmp(currentThing->d_name,"..")==0){
continue;
}

if(BASE==true){
//Create a string of the directory name
char* s = toString(currentThing->d_name);

//Concatenate the next path to the directory name
strcat(Path2,s);

//Free copy of s
free(s);
s=NULL;

printf("PATH2: %s",Path2);

//If the last character of the path does not contain a '/', concatenate a "./" to the path. 
if(Path2[strlen(Path2)-1]!='/'){

char* u = malloc(3*sizeof(char));

u[0]='.';
u[1]='/';
u[2]='\0';

strcat(u,Path2);
free(Path2);
Path2=NULL;
Path2=u;
}
//Recursively iterate to the next directory, while still iteratig through all other directories
//and files not visited within current directory, false flag for BASE, because just opened another directory.
ReadDir(toString(Path),toString(Path2),false);
}

else{
//Copy static directory name to a character pointer.
char* c = toString(currentThing->d_name);
//If the path does not contain a '/' at the end, now concatenate a / to the path.
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
printf("\nNo Path to go to next.\n");
break;
}
printf("\n\nPATH 2: %s\n\n",Path2);

//Recursive iteration to next directory.
ReadDir(toString(Path),toString(Path2),false);
}
}

printf("\n\n");
}while(currentThing!=NULL);
//While directory pointer is not NULL.

//Free variables used for copying strings if they are not freed already.
if(i2!=NULL){
free(i2);
i2=NULL;
}
if(i!=NULL){
free(i);
i=NULL;
}
//Free variables used for copying strings if they are not freed already.
if(Path!=NULL){
free(Path);
Path=NULL;
}
if(Path2!=NULL){
free(Path2);
Path2=NULL;
}

//Close the directory iterated upon
closedir(currentDir);
//
return;
}
//Concatinates a string to the second argument string provided.
void CatDir(char* app, char** C){
  
if(C==NULL){
return;
}
if(*C==NULL){

return;
}
//Concatenate the string to the second argument
strcat(app,*C);
free(*C);
return;
}

//Concatenate a string to the second argument string provided.
void CatFile(char* app, char** C){
  
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
}

//Returns true if the file path is in the directory, false if not.
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

//Go to the previous directory string given the count of directories by int NextL.
void PrevPath(char**C,int NextL){
int occ=0;
int i=strlen(*C);
printf("LENGTH: %d",i);
int j=0;
  
char* e = malloc(2*sizeof(char));
e[0] =(*C)[j];
e[1]='\0';
  
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

//Counts the occurrences of a character or string, argument 1, within a string, argument 2.
int countOcc(char* n, char**C){
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
//An error occurred while opening the file.
if(F==NULL){
printf("ERROR, CANNOT READ FILE");
return;
}

//variable that is used to append pieces of tokens into a token word.
char* app = malloc(2*sizeof(char));
app[0]=' ';
app[1]='\0';

//Word which will be a complete token to be inserted into a linked list.
char* Word = malloc(sizeof(char));
Word[0]='\0';

int wordSize = 1;

bool isReadable = true;

//Check if the file contains all readable characters.  
while(fscanf(F, "%c", &(app[0])) != EOF){
if((int)app[0]<0||(int)app[0]>126){
printf("\nError, file is not readable\n");
isReadable=false;
break;
}


}

fclose(F);

//If the file is readable, proceed to read the file.
if(isReadable==true){

printf("\n File: %s is readable, reading...\n",FileName);

F=fopen(FileName,"r");
//If the file cannot be opened
if(F==NULL){
printf("Error, cannot read file");
return;
}
//Use fscanf to read through file character by character and read all tokens which are characters in the alphabet, or numbers.
//Delimiters will be any character that does not fall under the category of a token.
while(fscanf(F, "%c", &(app[0])) != EOF){

printf("%c",app[0]);

if(isalpha(app[0])||isdigit(app[0])){

app[0]=tolower(app[0]);
Word=realloc(Word,2*sizeof(char));
Word[wordSize-1]='\0';
strcat(Word,app);
wordSize++;
//TOKENS
}

else if(Word[0]!='\0'){
//FOUND A WORD

char c = '/';

//Compress string to be just the filename, IncrOcc checks if the filename already was found and just adds and increments
//The word could of the word. If the word is also the same, it increments the word count of that word.
//IncrOcc returns 0 when there is a new word found, and not 0 when the same word is found.
if(IncrOcc(&O,Word,strrchr(strrchr(FileName,c),(strrchr(FileName,c)[1])))==0){
//NEW WORD
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

//Clear Word and set it to size 1 again.
free(Word);
Word=NULL;
Word = malloc(sizeof(char));
Word[0]='\0';
wordSize=1;
//If not a char or a num, it's a delimiter!
}

}
}
else{
printf("\n File: %s is not readable\n",FileName);
}

printf("\n\nEND FILE STREAM\n\n");
//Free the word and appender data
free(Word);
Word=NULL;
free(app);
app=NULL;
//Finished with file
fclose(F);
}

}

else if(*D==NULL){
//Found a new file to read.
printf("\nCREATE NEW LIST\n");
//Create a new list.

//If the file can be accessed.
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
//Check if file contains all readable characters, if not, set isReadable flag to false.
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

//Only read through file if the file is completely readable.
if(isReadable==true){

printf("\n File: %s is readable, reading...\n",FileName);

F=fopen(FileName,"r");

if(F==NULL){
printf("ERROR, CANNOT READ FILE");
return;
}


int wordSize = 1;
//Use fscanf to read through file character by character and read all tokens which are characters in the alphabet, or numbers.
//Delimiters will be any character that does not fall under the category of a token.
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
//Compress string to be just the filename, IncrOcc checks if the filename already was found and just adds and increments
//The word could of the word. If the word is also the same, it increments the word count of that word.
//IncrOcc returns 0 when there is a new word found, and not 0 when the same word is found.
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

//Free char* arrays used to store copies of word tokens of a particular file into linked list.
free(Word);
Word=NULL;

free(app);
app=NULL;
//Finished with file
fclose(F);
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
  
printf("\nPRINT LIST\n\n");

Occurrences** OCC =&O;
  
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
//JUST PUT STRINGS INTO A FILE.

char** Visited = malloc(sizeof(char**));
int i=0;

bool V = false;

Occurrences** U = &O;
PUT(F,1,NULL,0);
PUT(F,2,NULL,0);
//Put header information into desired file.
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
//If the file was not already visited, under the strings desired outputted files, place the information of the file and the token(s)
//Found along with how many times they occurred.
if(V==false){
PUT(F,4,NULL,0);
PUT(F,6,(*U)->Name,(*U)->Occurrence);
}


while((*U)!=NULL){
//If the file was not already visited, under the strings desired outputted files, place the information of the file and the token(s)
//Found along with how many times they occurred.
if(strcmp((*U)->Name,ALL)==0&&isVisited(Visited,(*U)->Name,i)==false){
PUT(F,7,(*U)->Name,(*U)->Occurrence);

PUT(F,6,(*U)->FileName,(*U)->Occurrence);

PUT(F,8,(*U)->FileName,(*U)->Occurrence);

PUT(F,9,(*U)->Name,(*U)->Occurrence);

}
//Next Occurrences* address.
U=&((*U)->Next);
}
//If the file was not visited, write </file>
if(V==false)
PUT(F,5,NULL,0);

//Add more data visited list and zero out the new space.
Visited[i]=malloc((strlen(ALL)+1)*sizeof(char));
bzero(Visited[i],(strlen(ALL)+1));
//Copy the string of the next file to the list of visited files.
strcpy(Visited[i],ALL);
printf("\n\nVISITED COPIED: %s\n\n",Visited[i]);
//Increment i to prepare for the next visited entry.
i++;
//Visited[i]=malloc(sizeof(char*));
U=Back;
}
//Write to file </fileIndex>
PUT(F,3,NULL,0);
return;
}

//Puts certain strings into a file specified by the type, the name of file or token used, and the count of the tokens
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
}
else if(type==6){
c=Name[0];
i=0;

while(c!='\0'){
fputc(c,F);
i++;
c=Name[i];
}

fputc('\"',F);
fputc('>',F);
  
}
else if(type==7){
c=l[0];
i=0;
  
fputc('\n',F);
fputc('\t',F);
fputc('\t',F);

while(c!='\0'){
fputc(c,F);
i++;
c=l[i];
}
  
}
else if(type==8){
c=m[0];
i=0;
fprintf(F,"%d",count);
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
