#include "../filesplitter.h"
/*
    Splite a file into a collection of segments with defined size, MD5, file MD5
*/
void splitFile(char *filePath){

  FILE *fp;
	
  if((fp = fopen(filePath,"rb")) != NULL){
    int fileSize = 0;
    fseek(fp,0L,SEEK_END);

    //file size by byte
    fileSize = ftell(fp);

    printf("*****  File size is %d  bytes  *****\n",fileSize);
    printf("*****  File md5 is: ");
    getFileMD5(fp);
    printf("\n");
		
    //move file pointer to beigin position
    fseek(fp,0,SEEK_SET);

    //calculate the number of segments
    int segSize = fileSize / SEG_SIZE;

    //to ensure left bytes is writen into last segment
    int left = fileSize % SEG_SIZE;
    if(left != 0) segSize++;

    printf("Segsize value: %d \n",segSize);

    //declare a FILE pointer
    FILE *segFile = NULL;

    //store file name
    char segName[25];

    //allocate buff to store file bytes information
    unsigned char *buffer = malloc(sizeof(unsigned char) * SEG_SIZE);

    int i = 0;
    while(i < segSize){
      //move file point to the begin position of a file
      fseek(fp,i*SEG_SIZE,SEEK_SET);

      //write data into buffer,the last segment buffer size
      //may not as exactlly as SEG_SIZE, left buffer size should
      //be calculated by extra line of code
      int segmentSize = 0;
      if(i != (segSize-1)) segmentSize = SEG_SIZE;
      else                 segmentSize = fileSize - i*SEG_SIZE;
			
      int result = fread(buffer,segmentSize,1,fp);

      printf("Split file state: %d \n",result);
      //construct a relative file path include file name
      sprintf(segName,"%s%d",SEG_PATH,i);

      //open a file stream
      segFile = fopen(segName,"wb");
      printf("Segment name: %s , %d bytes \n",segName,segmentSize);
						
      //write buffer
      if(i != (segSize-1)){
	fwrite(buffer,SEG_SIZE,1,segFile);
      }else{
	fwrite(buffer,fileSize - i*SEG_SIZE,1,segFile);
      }
      fflush(segFile);
      i++;
    }

    if(segFile != NULL) fclose(segFile); //close write file
    free(buffer);    //free heap allocated memory
    fclose(fp);
    printf("\nAccomplish file split...\n\n");
  }else{
    printf("Open file fails.");
  }
}
