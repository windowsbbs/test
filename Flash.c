#include "Flash.h"
#include "main.h"

//#define FLASH_TYPEPROGRAM_HALFWORD             0x01U  /*!<Program a half-word (16-bit) at a specified address.*/
//#define FLASH_TYPEPROGRAM_WORD                 0x02U  /*!<Program a word (32-bit) at a specified address.*/
//#define FLASH_TYPEPROGRAM_DOUBLEWORD           0x03U  /*!<Program a double word (64-bit) at a specified address*/

/*
//addr 默认是 可以写
uint16_t Flash_Write_Buf2(uint32_t addr,uint8_t *buf,uint16_t buf_len)
{
	uint16_t wdata = 0xFFFF;
	uint16_t wcount = 0;
	uint16_t i = 0;
	HAL_FLASH_Unlock();//解锁Flash
	
	wcount = buf_len / 2;
	for(i=0;i<wcount;i++)
	{
		wdata = (buf[2*i]<<8)|buf[2*i+1];
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,addr+2*i,wdata); 
	}
	if( wcount*2 < buf_len) //奇数
	{
		wdata = (buf[2*i]<<8)| 0xFF;
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,addr+2*i,wdata);
	} 
	///HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, Robot_Num_Flash_Add, Write_Flash_Data); //?Flash????,FLASH_TYPEPROGRAM_HALFWORD ?????Flash???16??,????32??64????,????HAL??????
	HAL_FLASH_Lock(); //上锁Flash
	
	return wcount;
}


uint16_t Flash_Read_Buf2(uint32_t addr,uint8_t *buf,uint16_t buf_len)
{
	uint16_t rdata = 0xFFFF;
	uint16_t rcount = 0;
	uint16_t i = 0;
	rcount = buf_len / 2;
	for(i=0;i<rcount;i++)
	{ 
		rdata = *(__IO uint16_t*)( addr+ 2*i );
		buf[2*i] = ((rdata&0xFF00)>>8);//默认高位在前
		buf[2*i+1] = (rdata&0xFF);
	}
	if(rcount*2 < buf_len)
	{
		rdata = *(__IO uint16_t*)( addr+2*i );
		buf[2*i] = ((rdata&0xFF00)>>8); 
	}  
	return buf_len;
}
*/

uint16_t Flash_Write_Buf(uint32_t addr,uint8_t *buf,uint16_t buf_len)
{
	uint16_t wdata = 0xFFFF;
	uint16_t wcount = 0;
	uint16_t i = 0;
	//uint16_t *buf16 = NULL;
	HAL_FLASH_Unlock();//解锁Flash
	//buf16 = (uint16_t *) buf;
	wcount = buf_len / 2;
	for(i=0;i<wcount;i++)
	{
		wdata = (buf[2*i+1]<<8)|buf[2*i];
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,addr+2*i,wdata); 
	}
	if( wcount*2 < buf_len) //奇数
	{
		//wdata = (buf[2*i-1]<<8) | 0xFF;
		wdata =  0xFF00 | buf[2*i];
		//i++;
		RTT_printf("wdata=0x%04X\n",wdata);
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,addr+2*i,wdata);
	} 
	///HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, Robot_Num_Flash_Add, Write_Flash_Data); //?Flash????,FLASH_TYPEPROGRAM_HALFWORD ?????Flash???16??,????32??64????,????HAL??????
	HAL_FLASH_Lock(); //上锁Flash
	
	return wcount;
}
uint16_t Flash_Read_Buf(uint32_t addr,uint8_t *buf,uint16_t buf_len)
{
	uint16_t rdata = 0xFFFF;
	uint16_t rcount = 0;
	uint16_t i = 0;
	rcount = buf_len / 2;
	for(i=0;i<rcount;i++)
	{ 
		rdata = *(__IO uint16_t*)( addr+ 2*i );
		buf[2*i+1] = ((rdata&0xFF00)>>8);//默认高位在前
		buf[2*i] = (rdata&0xFF);
	}
	if(rcount*2 < buf_len)
	{
		rdata = *(__IO uint16_t*)( addr+2*i );
		
		buf[2*i] = (rdata&0xFF);
		RTT_printf("rdata=0x%04X  buf[%d]=%02X\n",rdata,2*i,buf[2*i]);
	}  
	return buf_len;
}


//addr 默认是 可以写
uint16_t Flash_Write_HalfWordBuf(uint32_t addr,uint16_t *buf,uint16_t buf_len)
{
	uint16_t wdata = 0xFFFF;
	uint16_t wcount = 0;
	uint16_t i = 0;
	uint16_t index = 0;
	HAL_FLASH_Unlock();//解锁Flash
	
	wcount = buf_len / 2;
	for(i=0;i<wcount;i++)
	{
		
		wdata = (buf[index]<<8)|buf[index+1];
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,addr+index,wdata); 
		index = index + 2;
	}
	if( (wcount*2) < buf_len)
	{
		wdata = (buf[index]<<8)| 0xFF;
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,addr+index,wdata);
	} 
	///HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, Robot_Num_Flash_Add, Write_Flash_Data); //?Flash????,FLASH_TYPEPROGRAM_HALFWORD ?????Flash???16??,????32??64????,????HAL??????
	HAL_FLASH_Lock(); //上锁Flash
	return wcount;
}

//读每次读2字字
uint16_t Flash_Read_HalfWordBuf(uint32_t addr,uint16_t *buf,uint16_t buf_len)
{
	uint16_t rdata = 0xFFFF;
	uint16_t rcount = 0;
	uint16_t i = 0;
	uint16_t *pbuf = NULL;
	pbuf = buf;
	if((addr>=FLASH_BASE)&&((addr+buf_len*2)<FLASH_END))
	{  
		for(i=0;i<buf_len;i++)
		{ 
			rdata = *(__IO uint16_t*)( addr + 2*i );
			*pbuf++ = rdata; 
		} 
		rcount = i;
	}
	return rcount;
}

uint32_t Flash_GetSector(uint32_t addr)
{
    uint32_t Sector = 0xFFFF;
	if((addr>= 0x08000000 )&&(addr < 0x8004000))//16KB
	{
	  // Sector =  FLASH_SECTOR_0  ;
	}else if((addr>= 0x08004000 )&&(addr< 0x08008000))//16KB
	{
	  // Sector =  FLASH_SECTOR_1  ;
	}else if((addr>= 0x08008000 )&&(addr<0x0800C000)) //16KB
	{
	   Sector =  FLASH_SECTOR_2  ;
	}else if((addr>= 0x0800C000 )&&(addr<0x08010000)) //16KB
	{
	   Sector =  FLASH_SECTOR_3  ;
	}else if((addr>= 0x08010000 )&&(addr<0x08020000)) //64KB
	{
	   Sector =  FLASH_SECTOR_4  ;
	}else if((addr>= 0x08020000 )&&(addr<0x08040000))//128KB
	{
	   Sector =  FLASH_SECTOR_5  ;
	}else if((addr>= 0x08040000 )&&(addr<0x08060000))
	{
	   Sector =  FLASH_SECTOR_6  ;
	}else if((addr>= 0x08060000 )&&(addr<0x08080000))
	{
	   Sector =  FLASH_SECTOR_7  ;
	}else if((addr>= 0x08080000 )&&(addr<0x080A0000 ))
	{
	   Sector =  FLASH_SECTOR_8  ;
	}else if((addr>= 0x080A0000 )&&(addr<0x080C0000))
	{
	   Sector =  FLASH_SECTOR_9  ;
	}else if((addr>= 0x080C0000 )&&(addr<0x080E0000))
	{
	   Sector =  FLASH_SECTOR_10  ;
	}else if((addr>= 0x080E0000 )&&(addr<0x08100000))
	{
	   Sector =  FLASH_SECTOR_11  ;
	}
	return Sector;
}

uint32_t Flash_Erase(uint32_t addr)
{
   uint32_t err;
	int err_count = 0;
	HAL_StatusTypeDef status = HAL_ERROR;
   FLASH_EraseInitTypeDef pEraseInit;
   pEraseInit.Banks = FLASH_BANK_1; ///STM32F405RGT6
   pEraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
   
   pEraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;
   pEraseInit.Sector = Flash_GetSector(addr);// FLASH_SECTOR_4;
   pEraseInit.NbSectors = 1;
   HAL_FLASH_Unlock();//解锁Flash
	err = 0x1234; 
	//FLASH->ACR &=~(1<<10);//FLASH disable code fetch
   status = HAL_FLASHEx_Erase( &pEraseInit ,&err);
   while( ((status != HAL_OK) || (err == 0x1234))&&(err_count<2) ) //如果第一次擦除失败 则继续第二次擦除
   {
	 RTT_printf("HAL_FLASHEx_Erase retry\n");
     status = HAL_FLASHEx_Erase( &pEraseInit ,&err);
	 RTT_printf("Flash_Erase err=0x%08X status=0x%02X\n",err,status);  
	 HAL_Delay(10);
	   err_count++;
   } 
   //FLASH->ACR |=(1<<10);//FLASH enable code fetch
   HAL_FLASH_Lock(); //上锁Flash
	
	return 0;
}


void Flash_Test(void)
{
	uint32_t addr = 0x8010000;
	uint16_t i = 0;
	uint8_t flashBuf[32];
	
	for(i=0;i<32;i++)
	{
	   flashBuf[i]=i;
	}
	
   	Flash_Write_Buf( addr  , flashBuf, 32 );
    Flash_Read_Buf(addr,flashBuf,32);
    RTT_printf_hex("Flash_Test1:",flashBuf,32);
    Flash_Erase(addr) ;
	Flash_Read_Buf(addr,flashBuf,32);
	RTT_printf_hex("Flash_Test2:",flashBuf,32);
	
}
