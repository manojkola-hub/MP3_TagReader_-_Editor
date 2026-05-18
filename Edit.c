#include<stdio.h>
#include<stdlib.h>
#include"mp3.h"


void edit(char *filename, Mp3_project *tags, char *tag_name, char *new_info)
{
    FILE *fp_main = fopen(filename, "rb");  //fp_main is the file pointer pointing to main file 
    FILE *fp_temp = fopen("temp.mp3", "wb"); //fp_temp is the file pointer pointing to the tempervory file
 
    if (fp_main == NULL || fp_temp == NULL)
    {
        printf("Error: File not found\n");
        return;
    }

    char Tag[5] = {0};   //to store the tags 

    if (strcmp(tag_name, "-t") == 0) //if in command line enter -t then its title
        strcpy(Tag, "TIT2");      //copy the title TIT2 in the array  names as Tag 
    else if (strcmp(tag_name, "-a") == 0)
        strcpy(Tag, "TPE1");
    else if (strcmp(tag_name, "-A") == 0)
        strcpy(Tag, "TALB");
    else if (strcmp(tag_name, "-y") == 0)
        strcpy(Tag, "TYER");
    else if (strcmp(tag_name, "-c") == 0)
        strcpy(Tag, "TCON");
    else if (strcmp(tag_name, "-m") == 0)
        strcpy(Tag, "COMM");
    else
    {
        printf("Error: Invalid Tag\n"); 
        printf("........................................Help...........................................\n");
        printf("for tag_name use only these shortcuts like \"-t\"  \"-a\" \"-A\" \"-y\" \"-c\" \"-m\" \n" );
        fclose(fp_main);  //closing the main file 
        fclose(fp_temp);   //closing the temp file
        remove("temp.mp3");
        return;
    }

    //  Reading the  MP3 header 10 bytes 
    char header[10];
    if (fread(header, 1, 10, fp_main) != 10 || strncmp(header, "ID3", 3) != 0)  //compare is header is having id3 sig or not
    {
        printf("Error: MP3 missing ID3 header\n");
        fclose(fp_main);
        fclose(fp_temp);
        remove("temp.mp3");
        return;
    }

    fwrite(header, 1, 10, fp_temp);

    int edit_tag = 0;


    while (1)
    {
        char tag[5] = {0};
        unsigned char size1[4];
        char flag[2];
        unsigned int size2 = 0;

        if (fread(tag, 1, 4, fp_main) != 4 || tag[0] == 0)
            break;

        if (fread(size1, 1, 4, fp_main) != 4)
            break;

        if (fread(flag, 1, 2, fp_main) != 2)
            break;

        unsigned char *ptr_size = (unsigned char *)&size2;
        ptr_size[0] = size1[3];
        ptr_size[1] = size1[2];
        ptr_size[2] = size1[1];
        ptr_size[3] = size1[0];
    
        if (size2 == 0 || size2 > 10000)
            break;

        if (strncmp(tag, Tag, 4) == 0)
        {
            unsigned int new_size = strlen(new_info) + 1;
            unsigned char new_size_bytes[4];

           
            unsigned char *ptr_new = (unsigned char *)&new_size;
            new_size_bytes[0] = ptr_new[3];
            new_size_bytes[1] = ptr_new[2];
            new_size_bytes[2] = ptr_new[1];
            new_size_bytes[3] = ptr_new[0];
           
            fwrite(tag, 1, 4, fp_temp);
            fwrite(new_size_bytes, 1, 4, fp_temp);
            fwrite(flag, 1, 2, fp_temp);

            fputc(0x00, fp_temp);
            fwrite(new_info, 1, strlen(new_info), fp_temp);

            fseek(fp_main, size2, SEEK_CUR);
            edit_tag = 1;

            printf("Edited tag %s with new value: %s\n", Tag, new_info);
        }
        else
        {
            fwrite(tag, 1, 4, fp_temp);
            fwrite(size1, 1, 4, fp_temp);
            fwrite(flag, 1, 2, fp_temp);

            char *info = malloc(size2);
            if (!info)
                break;

            fread(info, 1, size2, fp_main);
            fwrite(info, 1, size2, fp_temp);
            free(info);
        }
    }

    // --- Step 3: Copy rest of file (audio data) ---
    char buffer[1024];
    int byte_read;
    while ((byte_read = fread(buffer, 1, 1024, fp_main)) > 0)
        fwrite(buffer, 1, byte_read, fp_temp);

    fclose(fp_main);
    fclose(fp_temp);

    if (edit_tag)
    {
        remove(filename);
        rename("temp.mp3", filename);
        printf("File edited successfully.\n");
    }
    else
    {
        remove("temp.mp3");
        printf("Tag not found.\n");
    }
}
