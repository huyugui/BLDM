#include "stm32f10x.h"
#include "Fatfs_Api.h"

#include <string.h>

//typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
//====================================
//#define BlockSize            512 /* Block Size in Bytes */
//#define BlockSize            128 /* Block Size in Bytes */
//#define BufferWordsSize      (BlockSize >> 2)

//#define NumberOfBlocks       2  /* For Multi Blocks operation (Read/Write) */
//#define MultiBufferWordsSize ((BlockSize * NumberOfBlocks) >> 2)
//===============================================
//uint32_t Buffer_Block_Tx[BufferWordsSize], Buffer_Block_Rx[BufferWordsSize];
//uint32_t Buffer_MultiBlock_Tx[MultiBufferWordsSize], Buffer_MultiBlock_Rx[MultiBufferWordsSize];
//volatile TestStatus EraseStatus = FAILED, TransferStatus1 = FAILED, TransferStatus2 = FAILED;

//FATFS fs;            // Work area (file system object) for logical drive
//FIL fsrc, fdst;      // file objects
//BYTE buffer[512]; // file copy buffer
//FRESULT res;         // FatFs function common result code
//UINT br, bw;         // File R/W count

//====================================
/*
FRESULT Fatfs_SearchPath(char* path)
{
	DWORD acc_size;				
	WORD acc_files, acc_dirs;
	FILINFO finfo;
	DIR dirs;
	FRESULT res;
	BYTE i;

	if ((res = f_opendir(&dirs, path)) == FR_OK) {
		i = strlen(path);
		while (((res = f_readdir(&dirs, &finfo)) == FR_OK) && finfo.fname[0]) {
			if (finfo.fattrib & AM_DIR) {
				acc_dirs++;
				*(path+i) = '/'; strcpy(path+i+1, &finfo.fname[0]);
				res = Fatfs_SearchPath(path);
				*(path+i) = '\0';
				if (res != FR_OK) break;
			} else {
				acc_files++;
				acc_size += finfo.fsize;
			}
		}
	}

	return res;
}
*/


//void Fatfs_WriteFile(void)
//{
//	unsigned int a;
//	FRESULT res;
//	FILINFO finfo;
//	DIR dirs;
//	int i;
//	char *fn;
//	char path[50]={""};  
//	char name[]={"WVO.TXT"};
//
//	Usart_Puts("\n  file system(Tini-FatFa0.07C) starting! \n");
//
//	disk_initialize(0);
//
//	f_mount(0, &fs);				                  //注册到文件系统0区
//
//	if (f_opendir(&dirs, path) == FR_OK) 			  //根目录打开成功 
//	{
//		while (f_readdir(&dirs, &finfo) == FR_OK)  	  //目录下是否有文件
//		{
//			if (finfo.fattrib & AM_ARC) 
//			{
//				if(!finfo.fname[0])	break; 
//				
//				Usart_Puts(finfo.fname);
//				res = f_open(&fsrc, finfo.fname, FA_OPEN_EXISTING | FA_READ);
//				//res = f_open(&fdst, "a3.rar", FA_CREATE_ALWAYS | FA_WRITE);
//
//				br=1;
//				a=0;
//				
//				for (;;)
//				{
//					for(a=0; a<512; a++) buffer[a]=0; 
//					
//					res = f_read(&fsrc, buffer, sizeof(buffer), &br);
//					buffer[511] = 0;
//					Usart_Puts(buffer);	
//					//printp("\r\n@@@@@res=%2d  br=%6d  bw=%6d",res,br,bw);
//					if (res || br == 0) break;   // error or eof
//					//res = f_write(&fdst, buffer, br, &bw);
//					//printp("\r\n$$$$$res=%2d  br=%6d  bw=%6d",res,br,bw);
//					//if (res || bw < br) break;   // error or disk full	
//				}
//				f_close(&fsrc);
//				//f_close(&fdst);	
//				//printf("\r\n asdasdasdasdasdasdas");	
//				//break;	                      
//			}
//		} 
//	}
//}

void SDCard_Init(void)
{
	SD_Error Status = SD_OK;
	SD_CardInfo SDCardInfo;
	/*-------------------------- SD Init ----------------------------- */
	Status = SD_Init();

	if (Status == SD_OK)
	{
		/*----------------- Read CSD/CID MSD registers ------------------*/
		Status = SD_GetCardInfo(&SDCardInfo);
	}

	if (Status == SD_OK)
	{
		/*----------------- Select Card --------------------------------*/
		Status = SD_SelectDeselect((u32) (SDCardInfo.RCA << 16));
	}

	if (Status == SD_OK)
	{
		//Status = SD_EnableWideBusOperation(SDIO_BusWide_4b);
	}

	/* Set Device Transfer Mode to DMA */
	if (Status == SD_OK)
	{  
		//    Status = SD_SetDeviceMode(SD_DMA_MODE);//oet
		//   Status = SD_SetDeviceMode(SD_POLLING_MODE);
		Status = SD_SetDeviceMode(SD_INTERRUPT_MODE);
	}

}
