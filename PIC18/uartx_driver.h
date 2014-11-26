
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
//  $Rev:: 297                                            $:  Revision of last commit
//  $Author:: reneleonrichard                             $:  Author of last commit
//  $Date:: 2014-09-25 20:20:09 -0400 (Thu, 25 Sep 2014)  $:  Date of last commit
//  $HeadURL: https://subversion.assembla.com/svn/db_repository/trunk/Libraries/C18/Headers/uartx_driver.h $
//
//*************************************************************
//defines, includes, enums here
//**************************************************************

#include <GenericTypeDefs.h>

#ifndef  UARTX_DRIVER_H
#define  UARTX_DRIVER_H

/* baud rate defines */
#define DESIRED_BAUD		19200
#define FOSC_HZ				4000000
#define BRGH				16          //16 for USART_BRGH_HIGH, 64 for USART_BRGH_LOW
//#define BAUD_RATE       	(FOSC_HZ/(BRGH * DESIRED_BAUD)) - 1
#define BAUD_RATE			12          //19200 baud

/* buffer status defines */
#define UART_BUFFER_SIZE 	64			//maximum of 256, must be a power of 2
#define UART_BUFFER_MASK    UART_BUFFER_SIZE-1
#define UART_BUFFER_RDY		0
#define UART_BUFFER_FULL	1
#define UART_BUFFER_OVR		2
#define UART_BUFFER_EMPTY	4
#define UART_BUFFER_ERROR	8

/* read or peak into UART buffer */
#define UART_READ			0
#define UART_PEAK			1

/* get status defines */
#define UART_RX				0
#define UART_TX				1

//**************************************************************
//external function prototypes
//**************************************************************
unsigned char uart1_tx(unsigned char *data, unsigned char size);
unsigned char uart1_romtx(const rom unsigned char *data, unsigned char size);
unsigned char uart1_rx(unsigned char *data, unsigned char cmd);
void uart1_tx_callback(void);
void uart1_rx_callback(void);
void uart1_init_driver(void);
unsigned char uart1_get_status(unsigned char rxtx);

unsigned char uart2_tx(unsigned char *data, unsigned char size);
unsigned char uart2_romtx(const rom unsigned char *data, unsigned char size);
unsigned char uart2_rx(unsigned char *data, unsigned char cmd);
void uart2_tx_callback(void);
void uart2_rx_callback(void);
void uart2_init_driver(void);
unsigned char uart2_get_status(unsigned char rxtx);

#endif /* UARTX_DRIVER_H */