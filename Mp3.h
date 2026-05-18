#ifndef MP3_PROJECT_H
#define MP3_PROJECT_H
#include<stdio.h>
#include<string.h>

typedef struct 
{ 
    char title[31];           // TIT2 //FOR 4BYTES OF FRAME_ID
    char artist[31];          //TPE1     // to holds the different types of tags into a single structure. 
    char album[31];           //TALB
    char year[5];             //TYER
    char comment[31];         //comm
    char content_type[31];    //TCON
} Mp3_project;                //new datatype to  the structure 

void view(char* filename,Mp3_project * tags );
void print_tag( Mp3_project * tags);
void edit(char *filename, Mp3_project *tags, char *tag_name, char *new_info);
#endif