#ifndef _FLASH_H
#define	_FLASH_H
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#define FLASH_SMARTBOX_BOOT_ADDR (0x08000000)  // Bootloader地址  占用32KB

#define FLASH_SMARTBOX_CONFIG_ADDR (0x08008000) // APP LEN + MD5  16KB

#define FLASH_SMARTBOX_INFO_ADDR (0x0800C000) // 信息地址 BOXID server IP等  16KB

#define FLASH_SMARTBOX_TYPE_ADDR (0x08010000)  // 机型保存 地址  64KB

#define FLASH_SMARTBOX_APP_ADDR (0x08020000)  // APP 地址     128KB

#define FLASH_SMARTBOX_TICKET_ADDR (0x08040000)  // 票面存放地址   (1024-256)KB






#ifdef	__cplusplus
extern "C" {
#endif
	
uint16_t Flash_Write_Buf(uint32_t addr,uint8_t *buf,uint16_t buf_len);

uint16_t Flash_Read_Buf(uint32_t addr,uint8_t *buf,uint16_t buf_len);

//uint16_t Flash_Write_Buf2(uint32_t addr,uint8_t *buf,uint16_t buf_len);
//uint16_t Flash_Read_Buf2(uint32_t addr,uint8_t *buf,uint16_t buf_len);

//addr 默认是 可以写
uint16_t Flash_Write_HalfWordBuf(uint32_t addr,uint16_t *buf,uint16_t buf_len);
//读每次读2字字
uint16_t Flash_Read_HalfWordBuf(uint32_t addr,uint16_t *buf,uint16_t buf_len);

uint32_t Flash_Erase(uint32_t addr);

void Flash_Test(void);

#ifdef	__cplusplus
}
#endif 

#endif
