#include<stdio.h>
#include<string.h>
#include "mp3.h"
int main(int argc , char*argv[])
{
       
    if (argc<2)
    {
        printf("................help.............\n");
        printf("for view must pass 3 arguments like \"./a.out\"   \"-v\"  \"filename\" \n");
        printf("for edit must pass 5 arguments like \"./a.out\"   \"-e\" \"tag\" \"new info\" \"filename\"  \n");
        return 0;

    }
  //............for view argument validattion and function calling
    if(strcmp(argv[1],"-v")==0)
    {
        if(argc!=3)
        {
            printf(" enter the minimum 3 arguments for viewing\n");
            printf("................help.............\n");
            printf("for view must pass 3 arguments like \"./a.out\"   \"-v\"  \"filename\" \n");
            return 0;
        }
            

        char * dot= strstr(argv[2],".mp3");
        if(!(dot!=NULL && strcmp(dot,".mp3")==0))
        {
            printf("please Enter .mp3 file\n");
            return 0;
        }
        
        
        Mp3_project  tags={0};   //allocating the memory to the structure by using structure data type with variale name..
        //printf("Hello3\n"); 
    
        view(argv[2],&tags);
        print_tag(&tags);
    }
//for edit argument validation and function calling ...
    else if(strcmp(argv[1],"-e")==0)
    {
        if(argc!=5)
        {
            printf(" enter the minimum 5 arguments for editing\n");
            printf("................help.............\n");
            printf("for edit must pass 5 arguments like \"./a.out\"   \"-e\" \"tag\" \"new info\" \"filename\"  \n");
            return 0;
        }

        char * dot= strstr(argv[4],".mp3");
        if(!(dot!=NULL && strcmp(dot,".mp3")==0))
        {
            printf("please Enter .mp3 file\n");
            return 0;
        }

        Mp3_project  tags={0};   //allocating the memory to the structure by using structure data type with variale name..
        edit(argv[4], &tags, argv[2], argv[3]);

    }
    else  // to suggest how to give the arguments for the edit and view functions
    {
        printf("................help.............\n");
        printf("for view must pass 3 arguments like \"./a.out\"   \"-v\"  \"filename\" \n");
        printf("for edit must pass 5 arguments like \"./a.out\"   \"-e\" \"tag\" \"new info\" \"filename\"  \n");
     
    }
     return 0;
        
}

