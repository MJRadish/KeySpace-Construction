#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>

typedef struct Occurrences_{
char* Name;
int Occurrence;
char* FileName;
struct Occurrences_* Next;

} Occurrences;

//Insert Directory, fileName, after filename is read
void Insert(char* Dir, char* FileName, char** Names);
//
void PrintList(char* arg1);
//
void PUT(FILE*F,int type, char* Name,int count);
//
void DeleteList();
//
void PrevPath(char** C,int Next);
//
void CatDir(char* app,char** C);
//
void CatFile(char* app,char**C);
//
void PutFile( FILE* F);
//
void ReadDir(char* P,char* P2,bool BASE);
//
char* toString( char* C);
//
bool FileinDir(char* path);
//
int countOcc(char* N, char** C);
//
int IncrOcc(Occurrences** OCC, char* W,char* F);
//
bool isVisited(char** V,char* entry, int i);
//
void freeVisited(char** V, int length);
//

Occurrences * MSort(Occurrences* top);
 ////Sorts pieces of the list and returns pointer to the sortedl list.
Occurrences * MG(Occurrences* O, Occurrences* P);
////Gets the middle or closest to middle node.
Occurrences * GM (Occurrences* H);
////
//
//




Occurrences * O =NULL;





#endif
