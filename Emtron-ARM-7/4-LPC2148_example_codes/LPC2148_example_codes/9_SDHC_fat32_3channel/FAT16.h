#ifndef __FAT16_H

#define __FAT16_H

struct F16_BS_struct{
U8 jumpBoot[3];
U8 OEMName[8];
U16 bytesPerSec;
U8 sectorsPerCluster;
U16 reservedSec;
U8 numberOfFAT;
U16 maxRootDir;
U16 na1;
U8 mediaDesc;
U16 sectorPerFAT;
U16 sectorPerTracks;
U16 numberOfHead;
U32 numberOfHidSec;
U32 numberOfSec;
U16 logicalDriveNumber;
U8 extendedSign;
U16 serialnumberofPartition;
U8 volumeLabel[11];
U8 FATName[8];
U8 code[448];
U8 marker[2];
};



signed char F16_getDirStruct(unsigned long );
unsigned long F16_getFirstSector(unsigned long );
unsigned long F16_getClusterNumber(unsigned long, unsigned char * ,unsigned char);
unsigned long F16_getNextCluster(unsigned long );
signed char F16_readFile(char * ,unsigned long);
signed char F16_loadFile(char *,unsigned long );
signed char F16_fillBuf(char *,unsigned long, unsigned char );
unsigned char F16_ascii2hex(unsigned char, unsigned char );
void F16_getParameters(unsigned char *);


#endif