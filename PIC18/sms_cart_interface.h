
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
//  $HeadURL: https://subversion.assembla.com/svn/db_repository/trunk/Libraries/C18/Headers/sms_cart_interface.h $
//
//**************************************************************
//defines, includes, enums here
//**************************************************************

#ifndef SMS_CART_INTERFACE
#define SMS_CART_INTERFACE

//PIC18 clocked at 48Mhz, each cycle is worth about 83ns
#define	SMS_FLASH_WRITE_DELAY	1
#define SMS_FLASH_READ_DELAY	1
#define SMS_CPLD_WRITE_DELAY	6
#define SMS_ROM_READ_DELAY		6

/* Ports Used */
#define smsADDRHIGH		PORTJ
#define smsADDRHIGHTr	TRISJ
#define smsADDRLOW		PORTH
#define smsADDRLOWTr	TRISH
#define smsDATA			PORTD
#define smsDATATr		TRISD
#define smsRD			LATEbits.LATE0
#define smsRDTr			TRISEbits.TRISE0
#define smsWR			LATEbits.LATE1
#define smsWRTr			TRISEbits.TRISE1
#define smsCE			LATEbits.LATE2
#define smsCETr			TRISEbits.TRISE2
#define smsBUSACK		PORTEbits.RE4
#define smsBUSACKTr		TRISEbits.TRISE4
#define smsJYDS			PORTEbits.RE6
#define smsJYDSTr		TRISEbits.TRISE6
#define smsWAIT			PORTEbits.RE7
#define smsWAITTr		TRISEbits.TRISE7
#define smsBUSREQ		PORTFbits.RF3
#define smsBUSREQTr		TRISFbits.TRISF3
#define smsRST			PORTFbits.RF4
#define smsRSTTr		TRISFbits.TRISF4
#define smsNMI			PORTBbits.RB0
#define smsNMITr		TRISBbits.TRISB0
#define smsMREQ			PORTBbits.RB1
#define smsMREQTr		TRISBbits.TRISB1
#define smsIORQ			PORTBbits.RB2
#define smsIORQTr		TRISBbits.TRISB2
#define smsJREAD		PORTBbits.RB3
#define smsJREADTr		TRISBbits.TRISB3
#define smsM1			PORTBbits.RB4
#define smsM1Tr			TRISBbits.TRISB4
#define smsINT			PORTBbits.RB5
#define smsINTTr		TRISBbits.TRISB5
#define smsPRES			PORTAbits.RA0
#define smsPRESTr		TRISAbits.TRISA0

//SEGA MAPPER CTRL REGISTER
#define SMS_ROM_WRITE_ENABLE	0x80
#define SMS_ROM_WRITE_DISABLE	0x00
#define SMS_SEGAMP_CTRL		0xFFFC
#define SMS_SEGAMP_SLOT0	0xFFFD
#define SMS_SEGAMP_SLOT1	0xFFFE
#define SMS_SEGAMP_SLOT2	0xFFFF

#define SMS_SLOT0			0
#define SMS_SLOT1			1
#define SMS_SLOT2			2

#define SMS_FLASH_CHIP0		0
#define SMS_FLASH_CHIP1		1

#define SMS_SECTOR_SIZE		4096
#define SMS_PAGE_SIZE		256

#define SMS_SST39F_128K		0xB5
#define SMS_SST39F_256K		0xB6
#define SMS_SST39F_512K		0xB7

//**************************************************************
//external function prototypes
//**************************************************************

void smsSetupPorts(void);
void smsWriteByte(unsigned char addrh, unsigned char addrl, unsigned char data, unsigned char delay);
unsigned char smsReadByte(unsigned char addrh, unsigned char addrl, unsigned char delay);
void smsSetCtrlAsInputs(void);
void smsSetCtrlAsOutputs(void);
void smsCartSectorErase(unsigned char sectorAddr);
void smsCartSetMapperSlot(unsigned char slotAddress, char slot);
void smsCartSetMapperCtrl(unsigned char data);
unsigned char smsCartConvSectorAddr(unsigned char sectorAddr, unsigned char slot);
void smsCartChipErase(unsigned char chip);
unsigned char smsCartReadSoftwareID(unsigned char chip);
void smsCartByteProgram(unsigned char addrh, unsigned char addrm, unsigned addrl, unsigned char data);
unsigned char smsCartIsFlashOpDone(unsigned char chip);
unsigned long smsCartCalcAdler32Sector(unsigned char sector);
void smsCartReadPage(unsigned char addrh, unsigned char addrm, unsigned char *data, unsigned char delay);

#endif /* SMS_CART_INTERFACE */