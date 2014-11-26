
/*                                .ssssssssss         `ssssssssss                                   
                                  -MMMMMMMMMN         .MMMMMMMMMM                                   
                                  -MMMMMMMMMN         .MMMMMMMMMM                                   
                                  -MMMMMMMMMN         .MMMMMMMMMM                                   
                                  -MMMMMMMMMN         .MMMMMMMMMM                                   
                                  -MMMMMMMMMN         .MMMMMMMMMM                                   
                                  -MMMMMMMMMN         .MMMMMMMMMM                                   
                 .-:/+//:-`       -MMMMMMMMMN         .MMMMMMMMMM        .-:////:-`                 
            `/ydNMMMMMMMMMMNds:`  -MMMMMMMMMN         .MMMMMMMMMM   `/sdNMMMMMMMMMMNds:`            
         `/dMMMMMMMMMMMMMMMMMMMNy-:MMMMMMMMMN         .MMMMMMMMMM`/hMMMMMMMMMMMMMMMMMMMNy:          
       `+NMMMMMMMMMMMMMMMMMMMMMMMMmMMMMMMMMMN         .MMMMMMMMMMmMMMMMMMMMMMMMMMMMMMMMMMMd:        
      -mMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN         .MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMh.      
     /MMMMMMMMMMMMmy+/----:+smMMMMMMMMMMMMMMN         .MMMMMMMMMMMMMMMds/:----/ohNMMMMMMMMMMMN-     
    /MMMMMMMMMMMy-            .oNMMMMMMMMMMMN         .MMMMMMMMMMMMm+`           `:hMMMMMMMMMMN-    
   .NMMMMMMMMMm-                .hMMMMMMMMMMN         .MMMMMMMMMMMs`                /NMMMMMMMMMd    
   sMMMMMMMMMm`                   hMMMMMMMMMN         .MMMMMMMMMMo                   -NMMMMMMMMM/   
   mMMMMMMMMM:                    `NMMMMMMMMN         .MMMMMMMMMd                     sMMMMMMMMMy   
  .MMMMMMMMMM                      dMMMMMMMMN         .MMMMMMMMMs                     :MMMMMMMMMm   
  .MMMMMMMMMM                      dMMMMMMMMN         .MMMMMMMMMs                     :MMMMMMMMMN   
  `NMMMMMMMMM-                    `NMMMMMMMMN         .MMMMMMMMMh                     +MMMMMMMMMh   
   hMMMMMMMMMh                    oMMMMMMMMMN         .MMMMMMMMMM:                   .NMMMMMMMMM+   
   -MMMMMMMMMMy`                 +MMMMMMMMMMN         .MMMMMMMMMMN:                 .mMMMMMMMMMN`   
    oMMMMMMMMMMm+`             :dMMMMMMMMMMMN         .MMMMMMMMMMMMy.             `oNMMMMMMMMMM:    
     sMMMMMMMMMMMNy/.      .:omMMMMMMMMMMMMMN         .MMMMMMMMMMMMMMdo-`     `-+hNMMMMMMMMMMN/     
      /NMMMMMMMMMMMMMMNNNNMMMMMMMMMMMMMMMMMMN         .MMMMMMMMMMMMMMMMMMNNNNNMMMMMMMMMMMMMMm-      
       `sMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN         .MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNo`       
         .sNMMMMMMMMMMMMMMMMMMMMNy+MMMMMMMMMN         .MMMMMMMMMM:hMMMMMMMMMMMMMMMMMMMMMm+`         
            :smMMMMMMMMMMMMMMNy/` -MMMMMMMMMN         .MMMMMMMMMM  `+hNMMMMMMMMMMMMMMdo-            
               `-/osyhhyys+:.     `----------          ----------      ./+syyhyyso/-                
                                                                                                    
*/
//*************************************************************
//
//  $Rev:: 298                                            $:  Revision of last commit
//  $Author:: reneleonrichard                             $:  Author of last commit
//  $Date:: 2014-09-25 23:03:43 -0400 (Thu, 25 Sep 2014)  $:  Date of last commit
//  $HeadURL: https://subversion.assembla.com/svn/db_repository/trunk/Libraries/C18/Source/sms_cart_interface.c $
//
//**************************************************************
//defines, includes, enums here
//**************************************************************
#include <sms_cart_interface.h>
#include <p18f86k22.h>

//**************************************************************
//static constants
//**************************************************************
#pragma romdata

//**************************************************************
//unitialized variables
//**************************************************************
#pragma udata

//**************************************************************
//place initialized variables here
//**************************************************************
#pragma idata

//**************************************************************
//internal function prototypes here
//**************************************************************


//**************************************************************
//All code below this line should be functions only
#pragma code

//**************************************************************
//SUPPORTING FUNCTIONS START HERE
//**************************************************************
//FUNCTION NAME:    smsSetupPorts
//ARGUMENTS:        void
//RETURNS:          void
//DESCRIPTION:      initializes sms ports, ensure bus is taken by
//					burner if connected to console by holding RST
//**************************************************************
void smsSetupPorts(void)
{	
	//hurry and check if connected to SMS, if so hold in reset for all signals to tri-state
	//SMS Presence pin = input
	smsPRESTr = 1;
	smsRSTTr = 0;
	if ( smsPRES == 1 )
	{
		smsRST = 0;
	}else
	{
		smsRST = 1;
	}

	//address output ports
	smsADDRHIGHTr = 0x00;
	smsADDRHIGH = 0x00;
	smsADDRLOWTr = 0x00;
	smsADDRLOW = 0x00;

	//data port as input until otherwise specified
	smsDATATr = 0xFF;

	//interrupt pins, all input
	TRISB = 0xFF;

	//control signal outputs for burn mode
	smsRDTr = 0;
	smsRD = 1;	//inactive
	smsWRTr = 0;
	smsWR = 1;	//inactive
	smsCETr = 0;
	smsCE = 1;	//inactive
	//configured as output to sim open drain output
	smsBUSREQTr = 1;	
	smsJYDSTr = 1;

	smsWAITTr = 1;
}

//**************************************************************
//FUNCTION NAME:    smsWriteByte
//ARGUMENTS:        unsigned int addr - 16 bit address destination
//					unsigned char data - 8 bit data to write
//					unsigned char delay - write hold delay
//RETURNS:          void
//DESCRIPTION:      writes sms data to a 16 bit addr, does not
//					take any mapping into consideration, also
//					assume the CTRL TRIS registers are properly set
//					and that the bus is in correct idle state
//**************************************************************
void smsWriteByte(unsigned char addrh, unsigned char addrl, unsigned char data, unsigned char delay)
{
	smsADDRHIGH = addrh;
	smsADDRLOW = addrl;
	Nop();
	Nop();
	smsDATATr = 0x00;
	smsDATA = data;
	smsCE = 0;
	Nop();
	Nop();
	Nop();
	Nop();
	smsWR = 0;
	Nop();
	Nop();
	Nop();
	Nop();
	smsWR = 1;
	smsCE = 1;
	smsDATATr = 0xFF;
}

//**************************************************************
//FUNCTION NAME:    smsReadByte
//ARGUMENTS:        unsigned int addr - 16 bit address destination
//					unsigned char delay - read hold delay
//RETURNS:          unsigned char data - data at address
//DESCRIPTION:      read sms data to a 16 bit addr, does not
//					take any mapping into consideration, also
//					assume the CTRL TRIS registers are properly set
//					and that the bus is in correct idle state
//**************************************************************
unsigned char smsReadByte(unsigned char addrh, unsigned char addrl, unsigned char delay)
{
	unsigned char data;

	smsDATATr = 0xFF;
	smsADDRHIGH = addrh;
	smsADDRLOW = addrl;
	Nop();
	Nop();
	smsCE = 0;
	smsRD = 0;
	Nop();
	Nop();
	Nop();
	Nop();
	data = smsDATA;
	smsRD = 1;
	smsCE = 1;
	return data;
}

//**************************************************************
//FUNCTION NAME:    smsSetCtrlAsInputs
//ARGUMENTS:        void
//RETURNS:          void
//DESCRIPTION:      set sms control signals (WR, RD, etc...) as
//					inputs
//**************************************************************
void smsSetCtrlAsInputs(void)
{
	smsWRTr = 1;
	smsRDTr = 1;
	smsCETr = 1;
}

//**************************************************************
//FUNCTION NAME:    smsSetCtrlAsOutputs
//ARGUMENTS:        void
//RETURNS:          void
//DESCRIPTION:      set sms control signals (WR, RD, etc...) as
//					outputs
//**************************************************************
void smsSetCtrlAsOutputs(void)
{
	//control signal outputs for burn mode
	smsRDTr = 0;
	smsRD = 1;	//inactive
	smsWRTr = 0;
	smsWR = 1;	//inactive
	smsCETr = 0;
	smsCE = 1;	//inactive
}

//**************************************************************
//FUNCTION NAME:    smsCartSectorErase
//ARGUMENTS:        unsigned char sectorAddr - one of 256 possible
//					flash sectors
//RETURNS:          void
//DESCRIPTION:      erase the flash sector specified
//**************************************************************
void smsCartSectorErase(unsigned char sectorAddr)
{
	//there are 128 4KB sector per ICs on the largest chips
	//if sectorAddr > 127 then this is targeting the 2nd chip

	//A19 A18 A17 A16 A15 A14 A13 A12 -> specify the sector
	// c   m   m   m   m   m   a   a
	// c = chip select
	// m = mapper select
	// a = address select

	//build the real high byte of the addr which will specify the correct sector in slot 2
	unsigned char realAddrh;
	realAddrh = smsCartConvSectorAddr(sectorAddr, SMS_SLOT2);
	
	//clear ROM Write Enable
	//use slot 0 and slot 1 for write algorithm since it requires A14 -> A0, least significant bit of slots is A14
	smsCartSetMapperCtrl(SMS_ROM_WRITE_DISABLE);
	if (sectorAddr > 0x7F)
	{
		//slot 0 and 1 point to lower 2nd ROM chip
		smsCartSetMapperSlot(0x20, SMS_SLOT0);
		smsCartSetMapperSlot(0x21, SMS_SLOT1);
	}else{
		//slot 0 and 1 point to lower 1st ROM chip
		smsCartSetMapperSlot(0x00, SMS_SLOT0);
		smsCartSetMapperSlot(0x00, SMS_SLOT1);
	}
	//use slot 2 for sector address to erase
	smsCartSetMapperSlot(sectorAddr>>2, SMS_SLOT2);
	
	//enable writes to ROM
	smsCartSetMapperCtrl(SMS_ROM_WRITE_ENABLE);
	//sector erase algorithm write to ROM
	smsWriteByte(0x55, 0x55, 0xAA, SMS_FLASH_WRITE_DELAY);
	smsWriteByte(0x2A, 0xAA, 0x55, SMS_FLASH_WRITE_DELAY);
	smsWriteByte(0x55, 0x55, 0x80, SMS_FLASH_WRITE_DELAY);
	smsWriteByte(0x55, 0x55, 0xAA, SMS_FLASH_WRITE_DELAY);
	smsWriteByte(0x2A, 0xAA, 0x55, SMS_FLASH_WRITE_DELAY);
	//last part of algorithm is to place the sector address on the most significant bits (Ams -> A12)
	smsWriteByte(realAddrh, 0x00, 0x30, SMS_FLASH_WRITE_DELAY);
	smsCartSetMapperCtrl(SMS_ROM_WRITE_DISABLE);
}

//**************************************************************
//FUNCTION NAME:    smsCartChipErase
//ARGUMENTS:        unsigned char chip - chip 0 or chip 1
//RETURNS:          void
//DESCRIPTION:      erase the flash chip specified
//**************************************************************
void smsCartChipErase(unsigned char chip)
{
	//clear ROM Write Enable
	//use slot 0 and slot 1 for write algorithm since it requires A14 -> A0, least significant bit of slots is A14
	smsCartSetMapperCtrl(SMS_ROM_WRITE_DISABLE);
	if (chip == SMS_FLASH_CHIP1)
	{
		//slot 0 and 1 point to lower 2nd ROM chip
		smsCartSetMapperSlot(0x20, SMS_SLOT0);
		smsCartSetMapperSlot(0x21, SMS_SLOT1);
	}else{
		//slot 0 and 1 point to lower 1st ROM chip
		smsCartSetMapperSlot(0x00, SMS_SLOT0);
		smsCartSetMapperSlot(0x00, SMS_SLOT1);
	}
	
	//enable writes to ROM
	smsCartSetMapperCtrl(SMS_ROM_WRITE_ENABLE);
	//sector erase algorithm write to ROM
	smsWriteByte(0x55, 0x55, 0xAA, SMS_FLASH_WRITE_DELAY);
	smsWriteByte(0x2A, 0xAA, 0x55, SMS_FLASH_WRITE_DELAY);
	smsWriteByte(0x55, 0x55, 0x80, SMS_FLASH_WRITE_DELAY);
	smsWriteByte(0x55, 0x55, 0xAA, SMS_FLASH_WRITE_DELAY);
	smsWriteByte(0x2A, 0xAA, 0x55, SMS_FLASH_WRITE_DELAY);
	smsWriteByte(0x55, 0x55, 0x10, SMS_FLASH_WRITE_DELAY);
	smsCartSetMapperCtrl(SMS_ROM_WRITE_DISABLE);	
}

//**************************************************************
//FUNCTION NAME:    smsCartSetMapperSlot
//ARGUMENTS:        unsigned char slotAddress - address of slot
//					char slot - which slot to modify
//RETURNS:          void
//DESCRIPTION:      set the mapper slot (SEGA MAPPER)
//**************************************************************
void smsCartSetMapperSlot(unsigned char slotAddress, char slot)
{
	switch(slot)
	{
		case SMS_SLOT0:
			smsWriteByte(0xFF, 0xFD, slotAddress, SMS_CPLD_WRITE_DELAY);
			break;
		case SMS_SLOT1:
			smsWriteByte(0xFF, 0xFE, slotAddress, SMS_CPLD_WRITE_DELAY);
			break;
		case SMS_SLOT2:
			smsWriteByte(0xFF, 0xFF, slotAddress, SMS_CPLD_WRITE_DELAY);
			break;
		default:
			break;
	}
}

//**************************************************************
//FUNCTION NAME:    smsCartSetMapperCtrl
//ARGUMENTS:        unsigned char data - data to write
//RETURNS:          void
//DESCRIPTION:      write to SEGA mapper control register
//**************************************************************
void smsCartSetMapperCtrl(unsigned char data)
{
	smsWriteByte(0xFF, 0xFC, data, SMS_CPLD_WRITE_DELAY);
}

//**************************************************************
//FUNCTION NAME:    smsCartConvSectorAddr
//ARGUMENTS:        unsigned char sectorAddr - the sector number
//					unsigned char slot - the slot number in which
//					the sector is to be mapped
//RETURNS:          unsigned char addrh - the high byte of the real
//					address to use in writes
//DESCRIPTION:      takes a sector number from 0 to 255 and converts
//					it to the high byte of the 16 bit address, you
//					still need to write sectorAddr>>2 to the mapper
//**************************************************************
unsigned char smsCartConvSectorAddr(unsigned char sectorAddr, unsigned char slot)
{
	//A19 A18 A17 A16 A15 A14 A13 A12 -> specify the sector
	// c   m   m   m   m   m   a   a
	// c = chip select
	// m = mapper select
	// a = address select

	//build the real high byte of the addr which will specify the correct sector in the slot
	unsigned char addrh;
	//slot specified by A15,A14
	//1 of 4 sectors specified by the two least significant bits of sector address argument

	//keep only last two bits (as shown above)
	addrh = sectorAddr & 0b00000011;
	//shift up to A13 and A12	
	addrh <<= 4;						
	//add slot offset to two most significant bits
	switch(slot)
	{
		case SMS_SLOT1:
			addrh |= 0x40;
			break;
		case SMS_SLOT2:
			addrh |= 0x80;
			break;
		default:
			break;
	}						
	return addrh;
}

//**************************************************************
//FUNCTION NAME:    smsCartReadSoftwareID
//ARGUMENTS:        unsigned char chip - which chip to read ID
//RETURNS:          unsigned char ID - ID of chip
//DESCRIPTION:      read the ID of the SST39SFxx chip
//**************************************************************
unsigned char smsCartReadSoftwareID(unsigned char chip)
{
	unsigned char softwareID;
	unsigned char delay = 2;

	//clear ROM Write Enable
	//use slot 0 and slot 1 for write algorithm since it requires A14 -> A0, least significant bit of slots is A14
	smsCartSetMapperCtrl(SMS_ROM_WRITE_DISABLE);
	if (chip == SMS_FLASH_CHIP1)
	{
		//slot 0 and 1 point to lower 2nd ROM chip
		smsCartSetMapperSlot(0x20, SMS_SLOT0);
		smsCartSetMapperSlot(0x21, SMS_SLOT1);
	}else{
		//slot 0 and 1 point to lower 1st ROM chip
		smsCartSetMapperSlot(0x00, SMS_SLOT0);
		smsCartSetMapperSlot(0x00, SMS_SLOT1);
	}
	
	//enable writes to ROM
	smsCartSetMapperCtrl(SMS_ROM_WRITE_ENABLE);
	//software id algorithm write to ROM
	smsWriteByte(0x55, 0x55, 0xAA, SMS_FLASH_WRITE_DELAY);
	smsWriteByte(0x2A, 0xAA, 0x55, SMS_FLASH_WRITE_DELAY);
	smsWriteByte(0x55, 0x55, 0x90, SMS_FLASH_WRITE_DELAY);

	//wait Tida (SST39SFxx datasheet page 17)
	while(delay--);
	softwareID = smsReadByte(0x00, 0x00, SMS_FLASH_READ_DELAY);
	softwareID = smsReadByte(0x00, 0x01, SMS_FLASH_READ_DELAY);

	//exit software id algorithm
	smsWriteByte(0x55, 0x55, 0xAA, SMS_FLASH_WRITE_DELAY);
	smsWriteByte(0x2A, 0xAA, 0x55, SMS_FLASH_WRITE_DELAY);
	smsWriteByte(0x55, 0x55, 0xF0, SMS_FLASH_WRITE_DELAY);
	smsCartSetMapperCtrl(SMS_ROM_WRITE_DISABLE);

	return softwareID;
}

//**************************************************************
//FUNCTION NAME:    smsCartByteProgram
//ARGUMENTS:        unsigned char addrh
//					unsigned char addrm
//					unsigned char addrl
//					unsigned char data
//RETURNS:          void
//DESCRIPTION:      byte one byte into flash, must have erased the
//					corresponding sector first
//**************************************************************
void smsCartByteProgram(unsigned char addrh, unsigned char addrm, unsigned addrl, unsigned char data)
{
	unsigned char realAddrh;
	unsigned char slot2map;
	//there are 128 4KB sector per ICs on the largest chips
	//if addrh > 0x07 then this is targeting the second chip

	// h3  h2  h1  h0  m7  m6  m5  m4  m3  m2  m1  m0  l7  l6  l5  l4  l3  l2  l1  l0
	//A19 A18 A17 A16 A15 A14 A13 A12 A11 A10 A09 A08 A07 A06 A05 A04 A03 A02 A01 A00
	// c   m   m   m   m   m   a   a   a   a   a   a   a   a   a   a   a   a   a   a
	// c = chip select
	// m = mapper select
	// a = address select

	//build the real high byte of the addr which will specify the correct sector in slot 2
	//chop off top two bits
	realAddrh = 0b00111111 & addrm;
	//set top two bits as slot 2
	realAddrh |= 0b10000000;

	//build the value to input into slot 2 mapper register to target the right byte
	slot2map = (addrh << 2);
	//chop off unecessary bits
	slot2map &= 0b00111100;
	//add two MSb's from addrm into the slot2map's 2 LSb's
	slot2map |= ((addrm >> 6) & 0b00000011);
	
	//clear ROM Write Enable
	//use slot 0 and slot 1 for write algorithm since it requires A14 -> A0, least significant bit of slots is A14
	smsCartSetMapperCtrl(SMS_ROM_WRITE_DISABLE);
	if (addrh > 0x07)
	{
		//slot 0 and 1 point to lower 2nd ROM chip
		smsCartSetMapperSlot(0x20, SMS_SLOT0);
		smsCartSetMapperSlot(0x21, SMS_SLOT1);
	}else{
		//slot 0 and 1 point to lower 1st ROM chip
		smsCartSetMapperSlot(0x00, SMS_SLOT0);
		smsCartSetMapperSlot(0x00, SMS_SLOT1);
	}
	//use slot 2 for byte to program
	smsCartSetMapperSlot(slot2map, SMS_SLOT2);
	
	//enable writes to ROM
	smsCartSetMapperCtrl(SMS_ROM_WRITE_ENABLE);
	//byte program algorithm write to ROM
	smsWriteByte(0x55, 0x55, 0xAA, SMS_FLASH_WRITE_DELAY);
	smsWriteByte(0x2A, 0xAA, 0x55, SMS_FLASH_WRITE_DELAY);
	smsWriteByte(0x55, 0x55, 0xA0, SMS_FLASH_WRITE_DELAY);
	smsWriteByte(realAddrh, addrl, data, SMS_FLASH_WRITE_DELAY);
	smsCartSetMapperCtrl(SMS_ROM_WRITE_DISABLE);
}

//**************************************************************
//FUNCTION NAME:    smsCartIsFlashOpDone
//ARGUMENTS:        unsigned char chip - which flash chip to check
//RETURNS:          unsigned char done
//DESCRIPTION:      reads the toggle bit for flash operation completion
//**************************************************************
unsigned char smsCartIsFlashOpDone(unsigned char chip)
{
	//read any byte in the flash for toggle bit, if two consecutive reads
	//are identical in bit 6, then flash operation is done
	
	unsigned char byte0, byte1, result=0;
	
	//clear ROM Write Enable
	//use slot 0
	smsCartSetMapperCtrl(SMS_ROM_WRITE_DISABLE);
	if (chip == SMS_FLASH_CHIP1)
	{
		//slot 0 points to lower 2nd ROM chip
		smsCartSetMapperSlot(0x20, SMS_SLOT0);
	}else{
		//slot 0 points to lower 1st ROM chip
		smsCartSetMapperSlot(0x00, SMS_SLOT0);
	}
	//read two bytes from the Flash
	byte0 = smsReadByte(0x00, 0x00, SMS_FLASH_READ_DELAY);
	byte1 = smsReadByte(0x00, 0x00, SMS_FLASH_READ_DELAY);

	//if bit6 is identical in both byte then operation is complete
	byte0 &= 0b01000000;
	byte1 &= 0b01000000;
	if ( byte0 == byte1 )
	{
		result = 1;
	}
	return result;
}

//**************************************************************
//FUNCTION NAME:    smsCartCalcAdlerSector
//ARGUMENTS:        unsigned char sector - the sector to calculate
//RETURNS:          unsigned long
//DESCRIPTION:      calculates the Adler32 checksum of a sector
//**************************************************************
unsigned long smsCartCalcAdler32Sector(unsigned char sector)
{
	//there are 128 4KB sector per ICs on the largest chips
	//if sectorAddr > 127 then this is targeting the 2nd chip

	//A19 A18 A17 A16 A15 A14 A13 A12 -> specify the sector
	// c   m   m   m   m   m   a   a
	// c = chip select
	// m = mapper select
	// a = address select

	unsigned char realAddrh, addrl = 0;
	unsigned int sumA=1, sumB=0;
	unsigned int i=0;
	unsigned long result;
	
	//build the real high byte of the addr which will specify the correct sector in slot 2
	smsCartSetMapperSlot(sector>>2, SMS_SLOT2);
	realAddrh = smsCartConvSectorAddr(sector, SMS_SLOT2);
	
	for( i=0 ; i<SMS_SECTOR_SIZE ; i++ )
	{
		//do the Adler thingy		
		sumA += ((unsigned int)smsReadByte(realAddrh, addrl, SMS_FLASH_READ_DELAY)) % 65521;
		sumB += (sumA) % 65521;
		//inc addrh and addrl
		if (++addrl == 0)											
		{
			realAddrh++;
		}
	}
	//concatenate result
	result = (unsigned long)sumB;
	result <<= 16;
	result |= (unsigned long)sumA;
	
	return result;
}

//**************************************************************
//FUNCTION NAME:    smsCartByteProgram
//ARGUMENTS:        unsigned char addrh
//					unsigned char addrm
//					unsigned char addrl
//					unsigned char data
//RETURNS:          void
//DESCRIPTION:      byte one byte into flash, must have erased the
//					corresponding sector first
//**************************************************************
void smsCartReadPage(unsigned char addrh, unsigned char addrm, unsigned char *data, unsigned char delay)
{
	unsigned char realAddrh;
	unsigned char addrl=0;
	unsigned char slot2map;

	//there are 4096 possible pages (256 bytes) in 1MB (largest ROM size)
	//therefore the page is specified by addrh and addrm

	//there are 128 4KB sector per ICs on the largest chips
	//if addrh > 0x07 then this is targeting the second chip

	// h3  h2  h1  h0  m7  m6  m5  m4  m3  m2  m1  m0  l7  l6  l5  l4  l3  l2  l1  l0
	//A19 A18 A17 A16 A15 A14 A13 A12 A11 A10 A09 A08 A07 A06 A05 A04 A03 A02 A01 A00
	// c   m   m   m   m   m   a   a   a   a   a   a   a   a   a   a   a   a   a   a
	// c = chip select
	// m = mapper select
	// a = address select

	//build the real high byte of the addr which will specify the correct sector in slot 2
	//chop off top two bits
	realAddrh = 0b00111111 & addrm;
	//set top two bits as slot 2
	realAddrh |= 0b10000000;

	//build the value to input into slot 2 mapper register to target the right byte
	slot2map = (addrh << 2);
	//chop off unecessary bits
	slot2map &= 0b00111100;
	//add two MSb's from addrm into the slot2map's 2 LSb's
	slot2map |= ((addrm >> 6) & 0b00000011);
	smsCartSetMapperSlot(slot2map, SMS_SLOT2);
	
	//read page into buffer
	do
	{
		*(data++) = smsReadByte(realAddrh, addrl++, delay);
	}while(addrl);
}