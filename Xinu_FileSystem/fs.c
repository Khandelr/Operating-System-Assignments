
#include <kernel.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <bufpool.h>

#if FS
#include <fs.h>
#define TOTAL_FILETABLE_ENTRIES 50
#define TOTAL_INODE_BLOCKS 100

static struct fsystem fsd;
struct filetable file_table[TOTAL_FILETABLE_ENTRIES];
int dev0_numblocks;
int dev0_blocksize;
char *dev0_blocks;
int dev0 = 0;
struct inode inodeTable[TOTAL_INODE_BLOCKS];	
int mkbsdev(int dev, int blocksize, int numblocks) {

  if (dev != 0) {
    printf("Unsupported device: %d\n", dev);
    return SYSERR;
  }
	
  if (blocksize != 0) {
    dev0_blocksize = blocksize;
  }
  else {
    dev0_blocksize = MDEV_BLOCK_SIZE;
  }

  if (numblocks != 0) {
    dev0_numblocks =  numblocks;
  }
  else {
    dev0_numblocks =  MDEV_NUM_BLOCKS;
  }

  if ( (dev0_blocks = memget(dev0_numblocks * dev0_blocksize)) == SYSERR) {
    printf("mkbsdev memgetfailed\n");
    return SYSERR;
  }

  return OK;

}

int mkfs(int dev, int num_inodes) {
  int i;
  int bm_blk = 0;
  
  if (dev == 0) {
    fsd.nblocks = dev0_numblocks;
    fsd.blocksz = dev0_blocksize;
  }
  else {
    printf("Unsupported device\n");
    return SYSERR;
  }

 i = fsd.nblocks;
 while ( (i % 8) != 0) {i++;}
 fsd.freemaskbytes = i / 8; 

 if ((fsd.freemask = memget(fsd.freemaskbytes)) == SYSERR) {
   printf("mkfs memget failed.\n");
   return SYSERR;
 }

 /* zero the free mask */
 for(i=0;i<fsd.freemaskbytes;i++) {
   fsd.freemask[i] = '\0';
 }

 /* write the fsystem block to block 0, mark block used */
 setmaskbit(0);
 bwrite(dev0, bm_blk, 0, &fsd, sizeof(struct fsystem));

 /* write the freemask in block 0, mark block used */
 setmaskbit(1);
 bwrite(dev0, bm_blk, 0, fsd.freemask, fsd.freemaskbytes);
 struct inode init;
 fsd.ninodes = num_inodes;
	//int i ;
	for(i=0;i<num_inodes;i++)
	{
		//init=inodeTable[i];
		inodeTable[i].id=i;
		inodeTable[i].type=-1;
		inodeTable[i].nlink=0;
		inodeTable[i].device=dev;
		inodeTable[i].size=0;

	}
	init_file_table();
	
	for(i=0;i<DIRECTORY_SIZE;i++)
			{
				fsd.root_dir.entry[i].inode_num=-1;
			} 
 return 1;
}



int 
bread(int dev, int block, int offset, void *buf, int len) {
  char *bbase;

  if (dev != 0) {
    printf("Unsupported device\n");
    return SYSERR;
  }
  if (offset >= dev0_blocksize) {
    printf("Bad offset\n");
    return SYSERR;
  }

  bbase = &dev0_blocks[block * dev0_blocksize];

  memcpy(buf, (bbase+offset), len);

  return OK;

}


int 
bwrite(int dev, int block, int offset, void * buf, int len) {
  char *bbase;
	char *buf1=(char *)buf;
	printf("dev0_blocksize %d\n",dev0_blocksize);
	char *data=(char *)malloc(dev0_blocksize*sizeof(char));
	int i;
  if (dev != 0) {
    printf("Unsupported device\n");
    return SYSERR;
  }
  if (offset >= dev0_blocksize) {
    printf("Bad offset\n");
    return SYSERR;
  }

  bbase = &dev0_blocks[block * dev0_blocksize];
/*for(i=0;i<dev0_blocksize;i++){
	printf("data %c\n",buf1[i]);
}*/
  memcpy((bbase+offset), buf1, len);
  memcpy(data,buf1,len);
/*for(i=0;i<dev0_blocksize;i++){

  //printf("data %c block number block %d\n",data[i],block);

}*/
  return OK;

}


/* specify the block number to be set in the mask */
int setmaskbit(int b) {
  int mbyte, mbit;
  mbyte = b / 8;
  mbit = b % 8;

  fsd.freemask[mbyte] |= (0x80 >> mbit);
}

/* specify the block number to be read in the mask */
int getmaskbit(int b) {
  int mbyte, mbit;
  mbyte = b / 8;
  mbit = b % 8;

  return( ( (fsd.freemask[mbyte] << mbit) & 0x80 ) >> 7);
}

/* specify the block number to be unset in the mask */
int clearmaskbit(int b) {
  int mbyte, mbit, invb;
  mbyte = b / 8;
  mbit = b % 8;

  invb = ~(0x80 >> mbit);
  invb &= 0xFF;

  fsd.freemask[mbyte] &= invb;
}

/* This is maybe a little overcomplicated since the first block is indicated in the
   high-order bit.  Shift the byte by j positions to make the match in bit7 (the 8th 
   bit) and then shift that value 7 times to the low-order bit to print.  Yes, it
   could be the other way...  */
void printfreemask(void) {
  int i,j;

  for (i=0; i < fsd.freemaskbytes; i++) {
    for (j=0; j < 8; j++) {
      printf("%d", ((fsd.freemask[i] << j) & 0x80) >> 7);
    }
    if ( (i % 8) == 7) {
      printf("\n");
    }
  }
  printf("\n");
}



int getNewInode()
	{
			int i ;
				for(i=0;i<TOTAL_INODE_BLOCKS;i++)
					{
						if(inodeTable[i].type==-1)
						  {
							return i;
						  }
					}							
						
		return SYSERR;
	}

int getFreeDirEntry()
	{
		int i ;
		for(i=0;i<DIRECTORY_SIZE;i++)
			{
				if(fsd.root_dir.entry[i].inode_num==-1)
						return i;
					
					
			}
		return SYSERR;
	}

int getFreeFileTable()
{
	int i;
	for( i=0;i<TOTAL_FILETABLE_ENTRIES;i++)
		{
			if(file_table[i].state==-1)
				return i;
		}
	return SYSERR;
}
void init_file_table()
{
	int i;
	for( i=0;i<TOTAL_FILETABLE_ENTRIES;i++)
		{
			file_table[i].state=-1;
			
		}
}
int cmpStrings(char * ptr1, char * ptr2)
{
char * a = ptr1;
char*b = ptr2;
while (*a != '\0' && *b!='\0'){
if (*a != *b)
return 1;
a++;
b++;
}
if (*a == '\0' && *b=='\0')
return 0;
else
return 1;	
}
int fcreat(char *filename, int mode)
{
	if(fsd.root_dir.numentries>DIRECTORY_SIZE)
	   
		return SYSERR;
	int i,q ;   
	for(i=0;i<DIRECTORY_SIZE;i++)
		{
			
			char *p=fsd.root_dir.entry[i].name;
			//int q=strcmp(*filename,*p);
			//if(q==0)		
			//return OK;
			 q=cmpStrings(filename,p);
			if(q==0)
				return SYSERR;
		}

	int inode_num=getNewInode();
	if(inode_num==SYSERR)
		return SYSERR;
	int dirent_index=getFreeDirEntry();
		if(dirent_index==SYSERR)
		return SYSERR;
	fsd.root_dir.entry[dirent_index].inode_num=inode_num;
	strncpy(fsd.root_dir.entry[dirent_index].name,filename,FILENAMELEN);
	printf("%d\n",fsd.root_dir.entry[dirent_index].inode_num);
	printf("%s\n",fsd.root_dir.entry[dirent_index].name);
	return OK;		


}


int fread(int fd, void *buf, int nbytes){
    char *a ;
    a =(char*)buf;
    int iNBytes  = nbytes;
    char *b = a;
    int filePtr = file_table[fd].fileptr;
    int totalSize = file_table[fd].in.size;
    int noOfBlocks = (filePtr)/2;// this returns the number of blocks before the current block
    int offset = filePtr%dev0_blocksize;
    int copyBytes =  dev0_blocksize  - offset ;
    int currInodeIndex = noOfBlocks;
// noOfBlocks is also the index of the inode to be read
    
int i = 0 ;

    for(i=currInodeIndex;i<totalSize;i++){

      if(iNBytes  < copyBytes)
        copyBytes = iNBytes;
        bread(0, file_table[fd].in.blocks[i],offset,b,copyBytes);

iNBytes = iNBytes - copyBytes;

      if(iNBytes<=0)
break;
b = &b[copyBytes];
     	copyBytes = dev0_blocksize;
     	offset = 0;
    }
        
}
syscall rread(int fd){
    char *a=(char *)malloc(file_table[fd].in.size*MDEV_BLOCK_SIZE*sizeof(char));
	int i=0;  
  if(fd==-1){
        printf("file does not exist\n");
        return SYSERR;
    }
    fread(fd,a,file_table[fd].in.size);
    //if(a[0]!=NULL){
	for(i=0;i<15;i++){
        printf("content:\n%c\n",a[i]);
}
    //}
}

int fseek(int fd, int offset){
    if(fd == -1){
        printf("File doesnot exist!!!");
        return SYSERR;
    }
    file_table[fd].fileptr = offset;
    return 1;
}
int fopen(char *filename, int flags)
{
	int fd = getFreeFileTable();
	//printf("file table%d\n",fd);
	if( fd == SYSERR)
		return SYSERR;
		int iCnt,q=0;   
	for(iCnt=0;iCnt<DIRECTORY_SIZE; iCnt++)
		{ 
			char *p=fsd.root_dir.entry[iCnt].name;
			//int q=strcmp(*filename,*p);
			//if(q==0)
			q=cmpStrings(filename,p);
			if(q==0)
				//return SYSERR;		
				{printf("found\n");
				break;}
		}
	if(iCnt == DIRECTORY_SIZE)
		return SYSERR;
	struct dirent* objDirent = &fsd.root_dir.entry[iCnt];
	struct filetable *ftb = &file_table[fd];
	ftb->state = flags;
	ftb->fileptr = 0;
	ftb->de = objDirent; 
	//printf("name %s\n",ftb->de->name);
	ftb->in = inodeTable[objDirent->inode_num]; 
	//printf("in %d\n",ftb->in);

	return fd;
}
int fwrite(int fd, void *buf, int nbytes){
int i=0;
   	char *buf1=(char *)buf;
/*for(i=0;i<15;i++){
		//a[i]=i+65;
		printf(" %c\n",buf1[i]);
	}*/
   int intTemp=0;
   int block_index = nbytes/fsd.blocksz;
   int offset = nbytes%fsd.blocksz;
   int bSize = (offset > 0)? block_index + 1 : block_index ; 
   if(block_index>INODEDIRECTBLOCKS || (block_index==INODEDIRECTBLOCKS && offset >0)){
printf("File size exceeded");
return 0;
   }
   int origSize =  file_table[fd].in.size;
	//printf("original size %d\n",file_table[fd].in.size);
	
   file_table[fd].in.size= bSize;
	//printf("bsize %d\n",file_table[fd].in.size);
		
   if(bSize<origSize ){
      int x=0;
      while(x<(origSize -bSize)){
         clearmaskbit(file_table[fd].in.blocks[bSize+x]);
         file_table[fd].in.blocks[bSize+x]='\0';
	//printf("block number free %d\n",file_table[fd].in.blocks[bSize + x]);

         x++;
      } 
   } 
   else if(bSize>origSize ){
       int x=2,y=0;
       for(y=0;y< bSize-origSize ;y++){
           for(;x<MDEV_NUM_BLOCKS;x++){
    		if(getmaskbit(x)==0)
              	   break;
           	}
           	if(x==MDEV_NUM_BLOCKS){
   			 printf("Insufficient memory");
			return 0;	
           	}
  		 else{
				file_table[fd].in.blocks[origSize + y]=x;
			//printf("block number allocated %d\n",file_table[fd].in.blocks[origSize + y]);
           }
	x++;
       }
   }
char *af = (char *)buf;
i=0;
   while(i<bSize){
      intTemp=nbytes>fsd.blocksz?fsd.blocksz:nbytes;
      bwrite(0,file_table[fd].in.blocks[i],0,af,intTemp);
      setmaskbit(file_table[fd].in.blocks[i]);
      i++;	
	af = &af[intTemp];
      if(nbytes>fsd.blocksz)
         nbytes=nbytes-fsd.blocksz;
   }
/*
   char *base=&dev0_blocks[file_table[fd].in.blocks[--i]*fsd.blocksz];
   if(nbytes<fsd.blocksz)
     memset(base+nbytes,0,(block_size-nbytes));*/

}
syscall wwrite(int fd){
    char *a=(char *)malloc(3*MDEV_BLOCK_SIZE*sizeof(char));
	int i;
	for(i=0;i<15;i++){
		a[i]='7';
		//printf("data wwrite %c\n",a[i]);
	}
    if(fd==-1){
        printf("file does not exist\n");
        return SYSERR;
    }
    fwrite(fd,a,fsd.blocksz*3);
    /*if(a[0]!=NULL){
        printf("content:\n%s\n",a);
    }*/
}


int fclose(int fd)
{
	file_table[fd].state=-1;
	file_table[fd].fileptr=0;
	
}
#endif /* FS */
