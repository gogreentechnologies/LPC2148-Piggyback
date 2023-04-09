#include <LPC214X.h>

#include "stdio.h"
#include "type.h"
#include "Serial.h"
#include "FAT.h"
#include "FAT32.c"
#include "FAT16.c"

/// FAT16 to be included

#define FAT16 0
#define FAT32 1

extern U8 sd_buf[512];
extern unsigned char SD_version, cardType, SDHC_flag;
U8 FATType;

void displaySize(unsigned long int sz){
	float fsize=sz;
	unsigned char sizeUnit;
	char buf[16];

	while(fsize>1000)
  	{
   	fsize=fsize/1024;
	sizeUnit++;
  	}

	sprintf((char *)buf,"%.02f ",fsize);
    uart0_puts((char *)buf);
    if(sizeUnit==1)
  		uart0_puts("Kb");
    else if(sizeUnit==2)
 	   uart0_puts("Mb");
    else if(sizeUnit==3)
  	   uart0_puts("GB");
}


signed char getBSData(void){
	signed char resp;
	struct MBR_struct *mbr;
//	struct BS_struct *bs;
	U32 firstSec=0,uliTemp;
//	struct partition_struct *part;
	char buf[16];

	resp=sd_readSector(0,SD_SECSIZE);
	//uart0_dump(sd_buf,512,16);
	if(resp==-1)
		return resp;

	//bs=(struct BS_struct *)sd_buf;

	//if(bs->jumpBoot[0]!=0xE9 && bs->jumpBoot[0]!=0xEB)
	if(sd_buf[0]!=0xE9 && sd_buf[0]!=0xEB)
	{
	//	 sprintf((char *)buf,"%02x %02x ",bs->sig[0],bs->sig[1]);
	//	 uart0_puts((char *)buf);

	//	 sprintf((char *)buf,"%d ",sizeof(*bs));
	//	 uart0_puts((char *)buf);
		//if(bs->sig[0]==0x55 && bs->sig[1]==0xAA)   //It is MBR
		if(sd_buf[510]==0x55 && sd_buf[511]==0xAA)
		{
			mbr=(struct MBR_struct *)sd_buf;
			//part=(struct partition_struct *)mbr->partitionData;
			//sprintf((char *)buf,"%ld",(mbr->partitionData[11]<<24)|(mbr->partitionData[10]<<16)|(mbr->partitionData[9]<<8)|(mbr->partitionData[8]));
			//uart0_puts((char *)buf);
			firstSec=(mbr->partitionData[11]<<24)|(mbr->partitionData[10]<<16)|(mbr->partitionData[9]<<8)|(mbr->partitionData[8]);
			//firstSec=firstSec/512;

			resp=sd_readSector(firstSec,SD_SECSIZE);
			
		//	sprintf((char *)buf,"%d\n\r",firstSec);
	  	//    uart0_puts((char *)buf);
	
			//uart0_dump(sd_buf,512,16); 	
			
			//bs=(struct BS_struct *)sd_buf;
		}
		else
			return -1;				//NOT BS nor MBR
	}

	//uart0_dump(sd_buf,512,16);

	if(sd_buf[0x52+3]=='3')
	{
		FATType=FAT32;
		uart0_puts("\n\rVOLUME Label: ");
		for(resp=0;resp<11;resp++)
			uart0_putc(sd_buf[0x47+resp]);

		uart0_puts("\n\rFAT Type:");
		for(resp=0;resp<8;resp++)
			uart0_putc(sd_buf[0x52+resp]);

		F32_getParameters(sd_buf,firstSec);
	}
	else
	{
		FATType=FAT16;
		//FATType=FAT32;
		uart0_puts("\n\rVOLUME Label: ");
		for(resp=0;resp<11;resp++)
			uart0_putc(sd_buf[0x2b+resp]);

		uart0_puts("\n\rFAT Type:");
		for(resp=0;resp<8;resp++)
			uart0_putc(sd_buf[0x36+resp]);
		F16_getParameters(sd_buf);
	}
	   
   	return 0;
}

/*****************************************************************/
signed char getDirStruct(unsigned long clusterN ,unsigned char *strBuf)
{
 	if(FATType=FAT32)
		return F32_getDirStruct(clusterN,strBuf);
	else
		return F16_getDirStruct(clusterN);
}

/*****************************************************************/
unsigned long getFirstSector(unsigned long cluster)
{
	if(FATType==FAT32)
		return F32_getFirstSector(cluster);
}

/*****************************************************************/
unsigned long getClusterNumber(unsigned long cluster,unsigned char *nam,unsigned char fileOrDir)
{
	if(FATType==FAT32)
		return F32_getClusterNumber(cluster,nam,fileOrDir);
}

/*****************************************************************/
unsigned long getNextCluster(unsigned long ccluster)
{

	if(FATType==FAT32)
		return F32_getNextCluster(ccluster);
}
/*****************************************************************/
unsigned long int getFreeCluster()
{
 	if(FATType==FAT32)
		return F32_getFreeCluster();
}

/*****************************************************************/
signed char readFile(char *filename,unsigned long curCluster,unsigned int offset,unsigned char *dataBuf)
{
 	if(FATType==FAT32)
		return F32_readFile(filename,curCluster,offset,dataBuf);
}

/*****************************************************************
signed char loadFile(char *filename,unsigned long curCluster)
{
   	if(FATType==FAT32)
		return F32_loadFile(filename,curCluster);
}
*/

signed char writeFile(char *filename,unsigned long curCluster,unsigned long int fileSize,unsigned char *data,unsigned char flags)
{
 	if(FATType==FAT32)
		return F32_writeFile(filename,curCluster,fileSize,data,flags);
}

void writeTest()
{
 	unsigned long int secNum;
	
	secNum=F32_getFirstSector(8);
	sd_writeSector(secNum,sd_buf);
	uart0_dump(sd_buf,512,32);
	uart0_puts("\n\r");
	sd_readSector(secNum,512);
	uart0_dump(sd_buf,512,32);
}