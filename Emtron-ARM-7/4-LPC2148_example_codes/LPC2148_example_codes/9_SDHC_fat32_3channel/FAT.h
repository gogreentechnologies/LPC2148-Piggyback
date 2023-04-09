#ifndef __FAT
#define __FAT


void displaySize(unsigned long int);
signed char getBSData(void );
signed char getDirStruct(unsigned long ,unsigned char *);
unsigned long getFirstSector(unsigned long );
unsigned long getClusterNumber(unsigned long ,unsigned char* ,unsigned char );
unsigned long getNextCluster(unsigned long );
signed char readFile(char *,unsigned long ,unsigned int ,unsigned char *);
signed char loadFile(char *,unsigned long );

struct partiton_struct{
unsigned char state;
unsigned char beg_H;
unsigned short beg_CS;
unsigned char partitionType;
unsigned char end_H;
unsigned char end_CS;
unsigned int firstSector;
unsigned int numberofSec;
};


struct MBR_struct{
unsigned char	nothing[446];		//ignore, placed here to fill the gap in the structure
unsigned char	partitionData[64];	//partition records (16x4)
//struct partiotn_struct part[4];
unsigned int	signature;		//0xaa55
};


#define SD_SECSIZE 512

#define DIR 1
#define FILE 0

#endif