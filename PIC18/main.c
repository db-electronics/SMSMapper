
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
//  $HeadURL: https://subversion.assembla.com/svn/db_repository/trunk/Personal%20Projects/SMSHomebrew/Firmware/main.c $
//
//*************************************************************
//defines, includes, enums here, that's right!
//**************************************************************
#include <p18f86k22.h>
#include <sms_cart_interface.h>
#include <config.h>
#include <serialCmd.h>
#include <usart.h>
#include <spi.h>
#include <timers.h>
#include <uartx_driver.h>

#define loop_max 100

//SPI FLASH pins
#define spiFlashCS 		PORTCbits.RC2
#define spiFlashTrCS	TRISCbits.TRISC2
#define spiFlashSWP		PORTCbits.RC6
#define spiFlashTrSWP	TRISCbits.TRISC6
#define spiFlashSHOLD	PORTCbits.RC7
#define spiFlashTrSHOLD	TRISCbits.TRISC7
#define spiFlashTrSCK	TRISCbits.TRISC3
#define spiFlashTrMISO	TRISCbits.TRISC4
#define spiFlashTrMOSI	TRISCbits.TRISC5

//Pushbutton pin
#define PB0				PORTCbits.RC0
#define PB0Tr			TRISCbits.TRISC0

//**************************************************************
//place function prototypes here
//**************************************************************
void low_isr(void);
void high_isr(void);
void timeOutLoad(unsigned int value);

//**************************************************************
//place macros here
//**************************************************************
#define timeOutCancel() (INTCONbits.TMR0IE = 0)

//**************************************************************
//place static constants here
//**************************************************************
#pragma romdata
const rom unsigned char testdata[] = {"db Electronics SMS Burner $Rev:: 298 $:"};
#define TEST_DATA_SIZE	40

//**************************************************************
//place unitialized variables here, 256 bytes per section allowed by linker
//**************************************************************
#pragma udata udata0
unsigned char dataIn[256];

#pragma udata udata1
unsigned char dataOut[256];

#pragma udata udata2
unsigned char dataInWrPtr,dataInRdPtr,dataInSize;
unsigned char dataOutWrPtr,dataOutRdPtr,dataOutSize;
unsigned char timeOutFlag;
unsigned char i;

//**************************************************************
//place initialized variables here
//**************************************************************
#pragma idata


//**************************************************************
//All code below this line should be functions only
#pragma code
//**************************************************************
//MAIN PROGRAM STARTS HERE/
//**************************************************************
void main(void)
{
	unsigned char byteWork, readSpeed;
	unsigned char commandIn;
	unsigned char page;

	//wait for osc start up
	while(!OSCCONbits.OSTS);
	//enable PLL
	OSCTUNEbits.PLLEN = 1;

	//Analog Pins Setup, all digital
	ANCON0 = 0x00;
	ANCON1 = 0x00;
	ANCON2 = 0x00;

	//setup timer0 for command timeouts, enable only on certain commands
	//timer0 ticks every Fosc/4 * 256 = 21.3uS, 1s timeouts ~= 62500
	OpenTimer0(	TIMER_INT_OFF &
				T0_16BIT &
				T0_SOURCE_INT &
				T0_PS_1_256 );
	INTCON2bits.TMR0IP = 0;

	uart2_init_driver();
	/* PC SIDE 115200 8N1 */
	Open2USART(	USART_TX_INT_OFF &
				USART_RX_INT_ON &
				USART_ASYNCH_MODE &
				USART_EIGHT_BIT &
				USART_BRGH_HIGH,
				34);

	//sms ports
	smsSetupPorts();

	/* S25FL216K0PMFI041 on SPI1 */
	//set outputs and inputs for SPI1 module
	spiFlashTrCS = 0;
	spiFlashTrSCK = 0;
	spiFlashTrMISO = 1;
	spiFlashTrMOSI = 0;
	spiFlashTrSWP = 0;
	spiFlashTrSHOLD = 0;
	spiFlashCS = 1;
	spiFlashSWP = 0;
	spiFlashSHOLD = 1;
	OpenSPI1( SPI_FOSC_16, MODE_11, SMPEND );
	
	//Pushbutton input init
	PB0Tr = 1;

	//init done, enbale interrupts
	RCONbits.IPEN = 1;        //enable priority levels on interrupts
	INTCONbits.GIEL = 1;
	INTCONbits.GIEH = 1;      //enable high priority interrupts

	//broadcast rev # to PC as test
	uart2_romtx(testdata, TEST_DATA_SIZE);

	//main loop start here
	while(1)
	{
		//wait to receive UART data
		if ( uart2_get_status(UART_RX) == UART_BUFFER_RDY )
		{
			//read in the byte, should only be one
			dataInSize = uart2_rx(&commandIn, UART_READ);
			if ( dataInSize == 1 )
			{
				switch(commandIn)
				{
					//********** SCMD_DETECTBURNER **********
					//detect burner, answer back with with cmd and ack
					case SCMD_DETECTBURNER:
						byteWork = (SCMD_DETECTBURNER | SCMD_ACK);
						uart2_tx(&byteWork, 1);
						break;

					//********** SCMD_DETECTFLASH **********
					//detect the size of flash connected, a real game will fail this test
					case SCMD_DETECTFLASH:
						byteWork = (SCMD_DETECTFLASH | SCMD_ACK);
						uart2_tx(&byteWork, 1);
						//read the SST39F's ID bytes, if this chip is 4 Mega Power, there could be a 2nd chip
						byteWork = smsCartReadSoftwareID(SMS_FLASH_CHIP0);
						if ( byteWork == SMS_SST39F_512K )
						{
							//check for 2nd chip, can only be a 512K
							byteWork = smsCartReadSoftwareID(SMS_FLASH_CHIP1);
							if ( byteWork == SMS_SST39F_512K )
							{
								//this is an 8 Mega Power cart! Oh my!
								byteWork = 8;
							}else
							{	//else it's 4 Mega Power!
								byteWork = 4;
							}
						//else, it's 1 or 2 Mega Power, or no cart at all
						}else
						{
							switch(byteWork)
							{
								case SMS_SST39F_128K:
									byteWork = 1;
									break;
								case SMS_SST39F_256K:
									byteWork = 2;
									break;
								default:
									byteWork = 0;
									break;
							}
						}
						//return result to PC
						uart2_tx(&byteWork,1);
						break;

					//********** SCMD_READSECTOR **********
					case SCMD_READSECTOR:
						byteWork = (SCMD_READSECTOR | SCMD_ACK);	
						uart2_tx(&byteWork, 1);
						//expecting 2 more bytes for this command, start timeout
						timeOutLoad(TMR1_TIMEOUT_1S);
						while( uart2_rx(&byteWork, UART_PEAK) < 2 )
						{
							if ( timeOutFlag == 1 )
							{
								goto TimeOutLbl;
							}
						}
						timeOutCancel();
						uart2_rx(&dataIn[0], UART_READ);
						//2 bytes received indicating address of sector to read 
						//mask off last nibble and read 1 page at a time
						page = dataIn[1] & 0b11110000;
						byteWork = 0;
						while( byteWork < 16 )
						{
							//read in 256 bytes
							smsCartReadPage(dataIn[0], (page | byteWork++), &dataOut[0], readSpeed);
							//output to pc
							//wait for buffer to be empty
							//output in 32 byte chunks
							for( i=0 ; i<8 ; i++ )
							{
								//wait for tx buffer to be empty
								while( uart2_get_status(UART_TX) != UART_BUFFER_EMPTY );
								uart2_tx(&dataOut[i<<5],32);
							}
						}						
						break;
					default:
						break;
				}
			}
			//unexpected data size, restart
TimeOutLbl:
			dataInSize = 0;
			dataInWrPtr = 0;
			dataInRdPtr = 0;
			dataOutSize = 0;
			dataOutWrPtr = 0;
			dataOutRdPtr = 0;
		}		
	}
}

//**************************************************************
//MAIN PROGRAM ENDS HERE
//**************************************************************

//**************************************************************
//SUPPORTING FUNCTIONS START HERE
//**************************************************************
//FUNCTION NAME:    timeOutLoad
//ARGUMENTS:        unsigned int value - value to write to timer0
//RETURNS:          void
//DESCRIPTION:      starts a timeout for serial commands, enables
//					timer interrupts to execute timeout in case it
//					elapses
//**************************************************************
void timeOutLoad(unsigned int value)
{
	WriteTimer0(value);
	//enable interrupts
	INTCONbits.TMR0IE = 1;
	timeOutFlag = 0;
}

//**************************************************************
//INTERRUPTS
//**************************************************************
#pragma code low_vector=0x18
void interrupt_at_low_vector(void)
{
_asm GOTO low_isr _endasm
}
#pragma code /* return to the default code section */
#pragma interruptlow low_isr
void low_isr (void)
{
	INTCONbits.GIEL = 0;

	if ( INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1 )
	{
		INTCONbits.TMR0IE = 0;
		INTCONbits.TMR0IF = 0;
		timeOutFlag = 1;
	}

	INTCONbits.GIEL = 1;
}

#pragma code high_vector=0x08
void interrupt_at_high_vector(void)
{
_asm GOTO high_isr _endasm
}
#pragma code /* return to the default code section */
#pragma interrupt high_isr
void high_isr (void)
{
	INTCONbits.GIEH = 0;

	if ( PIR3bits.RC2IF == 1 )
	{
		uart2_rx_callback();
		PIR3bits.RC2IF = 0;
	}
	if ( PIR3bits.TX2IF == 1 && PIE3bits.TX2IE == 1 )
	{
		uart2_tx_callback();
		PIR3bits.TX2IF = 0;
	}

	RCONbits.IPEN = 1;        //enable priority levels on interrupts
	INTCONbits.GIEH = 1;      //enable high priority interrupts
}
