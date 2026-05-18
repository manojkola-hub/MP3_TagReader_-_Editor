#include "mp3.h"
#include<stdlib.h>

void view(char*filename,Mp3_project * tags) 
{

    int frame_size=0;


    FILE*fp=fopen(filename,"r");

    if(fp==NULL)
    {
        printf("error file is not opening");
        return ;
    }
    char header[10]={0};  //this is for 10 bytes of header 


    if(fread(header,1,10,fp)!=10)    //reading 10 bytes of date  from the file 
    {
        printf("header should contain 10 bytes\n");
        fclose(fp);
        return ;
    }
    if( strncmp(header,"ID3",3)!=0)   //checking if the header is having id3 or not 
    {
        printf("header should always contain ID3 SIGNATURE\n");
        fclose(fp);
        return ;   
    }

    while(!feof(fp))
    {

        char frame_id[5]={0};   //storing the frame id from the given mp3 file 
        fread(frame_id,1,4,fp);
        frame_id[4]='\0';


       
        unsigned char frame_size_bytes[4]={0};
       
        fread(frame_size_bytes,1,4,fp);

        char*ptr_size=(unsigned char*)&frame_size; // file will having in big endian format before stroing we need to convert it into little endian format
        
        ptr_size[0]= frame_size_bytes[3];
        ptr_size[1]= frame_size_bytes[2];
        ptr_size[2]= frame_size_bytes[1];
        ptr_size[3]= frame_size_bytes[0];
       // printf("%d\n",ptr_size[0]);


        if(frame_size<=0 || frame_size>10000)
        {
            break;
        }

        fseek(fp,2,SEEK_CUR);   // to skip the 2 bytes of flag 


        fgetc(fp);   // to skip the encoded 



        char*information=malloc(frame_size);  // copy the information from the file 
        if(!information)
        {
            printf("malloc not allocated ");
            break;
        }
        fread(information,1,frame_size-1,fp);  //here size-1 because we already skipping the encoded data 

        if (strcmp(frame_id, "TIT2") == 0)
        {
            strncpy(tags->title, information, sizeof(tags->title)-1);
            tags->title[sizeof(tags->title)-1]='\0';
        }

        else if (strcmp(frame_id, "TPE1") == 0)
        {
            strncpy(tags->artist, information, sizeof(tags->artist)-1);
            tags->artist[sizeof(tags->artist)-1]='\0';
        }

        
        else if (strcmp(frame_id, "TALB") == 0)
        {
            strncpy(tags->album, information, sizeof(tags->album)-1);
            tags->album[sizeof(tags->album)-1]='\0';
        }
            
        else if (strcmp(frame_id, "TYER") == 0)
        {
            strncpy(tags->year, information, sizeof(tags->year)-1);
            tags->year[sizeof(tags->year)-1]='\0';
        }
            
        else if (strcmp(frame_id, "COMM") == 0)
        {
            strncpy(tags->comment , information, sizeof(tags->comment)-1);
            tags->comment [sizeof(tags->comment)-1]='\0';
        }
            
        else if (strcmp(frame_id, "TCON") == 0)
        {
            strncpy(tags->content_type, information, sizeof(tags->content_type)-1);
            tags->content_type[sizeof(tags->content_type)-1]='\0';
        }
        else
        {
            break;
        }
       
    

        free(information);
 
    }

        
    fclose(fp);
}
void print_tag( Mp3_project * tags)
    {
        printf("...................................................\n");
        printf("...............MP3 VIEW............................\n");
        printf("Title         :   %s\n", tags->title);
        printf("Artist        :   %s\n", tags->artist);
        printf("Album         :   %s\n", tags->album);
        printf("Year          :   %s\n", tags->year);
        printf("comment       :   %s\n", tags->comment);
        printf("Content_type  :   %s\n", tags->content_type);
        printf("...................................................\n");
    }







   




   


    

