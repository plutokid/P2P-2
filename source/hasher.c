#include "../hasher.h"
#include "../md5.h"

/*
  To obtain MD5 of a file by input memory address
  of a file,return 16 char array. Each char stores an integer
  ranges from 0-255 and can be mapped into hex-representation 
  of stored value, such as 0xa1
*/
void
getFileMD5(FILE *fp){
	long fileSize = 0;
    fseek(fp,0L,SEEK_END);
	fileSize = ftell(fp);
    //printf("File size is: %lu \n",fileSize);

    //move file point to the begin position of a file
	fseek(fp,0L,SEEK_SET);
    //allocate buff to store file bytes information
    unsigned char *encrypt = malloc(sizeof(unsigned char)*fileSize);

	//record read file state
	int rc = -1;
	//buffer, read length, read times, file pointer
    rc = fread(encrypt,fileSize,1,fp);
	
    if(rc < 0){
	    printf("Read file error.");
	}else{
	    unsigned char decrypt[16] = "";
	    MD5_CTX md5;//MD5 structure
		MD5Init(&md5);//initialize md5
		MD5Update(&md5,encrypt,sizeof(encrypt));
		MD5Final(&md5,decrypt);
		int i = 0;
		printf("%02x",decrypt[i]);
		for(i = 0; i < 16;i++){
            printf("%02x",decrypt[i]);
			//*(depcryptBuff+i) = decrypt[i];
		}
		
	}
	free(encrypt);
}

/*
  To obtain MD5 of a char arrya each char stores an integer
  ranges from 0-255 and can be mapped into hex-representation 
  of stored value, such as 0xa1
*/
void
getCharsMD5(unsigned char *encrypt){
	unsigned char decrypt[16] = "";
	MD5_CTX md5;//MD5 structure
	MD5Init(&md5);//initialize md5
	MD5Update(&md5,encrypt,sizeof(encrypt));
	MD5Final(&md5,decrypt);
	int i = 0;
	printf("%02x",decrypt[i]);
	for(i = 0; i < 16;i++){
		printf("%02x",decrypt[i]);
		//*(depcryptBuff+i) = decrypt[i];
	}
}
