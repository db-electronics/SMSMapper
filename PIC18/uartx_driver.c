
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
//  $HeadURL: https://subversion.assembla.com/svn/db_repository/trunk/Libraries/C18/Source/uartx_driver.c $
//
//**************************************************************
//defines, includes, enums here
//**************************************************************

//#include <p18f4620.h>

#include <usart.h>
#include <uartx_driver.h>

//**************************************************************
//static constants
//**************************************************************
#pragma romdata

//**************************************************************
//unitialized variables
//**************************************************************

struct uart_buffer{
	unsigned char data[UART_BUFFER_SIZE];
	unsigned char inptr;
	unsigned char outptr;
	unsigned char status;
	unsigned char size;
};
#pragma udata uart_ram0
struct uart_buffer tx1, tx2;
#pragma udata uart_ram1
struct uart_buffer rx1, rx2;

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
//FUNCTION NAME:    uart1_init_driver  
//ARGUMENTS:        
//RETURNS:          
//DESCRIPTION:      initializes the uart interrupts and associated buffers
//**************************************************************
void uart1_init_driver(void){

	/* initialize tx and rx buffers */
	tx1.inptr = 0;
	rx1.inptr = 0;
	tx1.outptr = 0;
	rx1.outptr = 0;
	tx1.status = UART_BUFFER_EMPTY;
	rx1.status = UART_BUFFER_EMPTY;

}
//**************************************************************
//FUNCTION NAME:    uart2_init_driver  
//ARGUMENTS:        
//RETURNS:          
//DESCRIPTION:      initializes the uart interrupts and associated buffers
//**************************************************************
void uart2_init_driver(void){

	/* initialize tx and rx buffers */
	tx2.inptr = 0;
	rx2.inptr = 0;
	tx2.outptr = 0;
	rx2.outptr = 0;
	tx2.status = UART_BUFFER_EMPTY;
	rx2.status = UART_BUFFER_EMPTY;

}

//**************************************************************
//FUNCTION NAME:    uart1_tx   
//ARGUMENTS:        unsigned char *data - pointer to data string
//					unsigned char size - size of data string to add to txbuffer 
//RETURNS:          status of tx buffer
//DESCRIPTION:      puts data into the uart transmit queue
//**************************************************************
unsigned char uart1_tx(unsigned char *data, unsigned char size){

	unsigned char i;

	/* check if data can fit in buffer, this doesn't check if the buffer's current
	   current pointers will allow (size) data to fit because it may be emptying 
	   concurrently through interupts */
	if (size > UART_BUFFER_SIZE){
		tx1.status = UART_BUFFER_ERROR; 
	}else if(size == 0){
		/* null */
	}else{
		/* put data in trasmit buffer */
		for(i=0;i<size;i++){
			tx1.data[tx1.inptr++] = *(data++);
			tx1.inptr &= UART_BUFFER_MASK;
			/* check for buffer full */
			if(tx1.inptr == tx1.outptr){
				tx1.status = UART_BUFFER_FULL;
				/* return index value which caused buffer full */
				tx1.status |= i;
				/* end for loop */
				break;
			}
		}
		/* initiate first tranfer, subsequent transfers are handled by interrupt */
		tx1.status = UART_BUFFER_RDY;
		Write1USART(tx1.data[tx1.outptr++]);
		tx1.outptr &= UART_BUFFER_MASK;
		/* enable tx interrupts */
		PIE1bits.TX1IE = 1;
	}
	return tx1.status;
}

//**************************************************************
//FUNCTION NAME:    uart1_tx   
//ARGUMENTS:        const rom unsigned char *data - pointer to data string
//					unsigned char size - size of data string to add to txbuffer 
//RETURNS:          status of tx buffer
//DESCRIPTION:      puts data into the uart transmit queue
//**************************************************************
unsigned char uart1_romtx(const rom unsigned char *data, unsigned char size){

	unsigned char i;

	/* check if data can fit in buffer, this doesn't check if the buffer's current
	   current pointers will allow (size) data to fit because it may be emptying 
	   concurrently through interupts */
	if (size > UART_BUFFER_SIZE){
		tx1.status = UART_BUFFER_ERROR; 
	}else if(size == 0){
		/* null */
	}else{
		/* put data in trasmit buffer */
		for(i=0;i<size;i++){
			tx1.data[tx1.inptr++] = *(data++);
			tx1.inptr &= UART_BUFFER_MASK;
			/* check for buffer full */
			if(tx1.inptr == tx1.outptr){
				tx1.status = UART_BUFFER_FULL;
				/* return index value which caused buffer full */
				tx1.status |= i;
				/* end for loop */
				break;
			}
		}
		/* initiate first tranfer, subsequent transfers are handled by interrupt */
		tx1.status = UART_BUFFER_RDY;
		Write1USART(tx1.data[tx1.outptr++]);
		tx1.outptr &= UART_BUFFER_MASK;
		/* enable tx interrupts */
		PIE1bits.TX1IE = 1;
	}
	return tx1.status;
}

//**************************************************************
//FUNCTION NAME:    uart2_tx   
//ARGUMENTS:        unsigned char *data - pointer to data string
//					unsigned char size - size of data string to add to txbuffer 
//RETURNS:          status of tx buffer
//DESCRIPTION:      puts data into the uart transmit queue
//**************************************************************
unsigned char uart2_tx(unsigned char *data, unsigned char size){

	unsigned char i;

	/* check if data can fit in buffer, this doesn't check if the buffer's current
	   current pointers will allow (size) data to fit because it may be emptying 
	   concurrently through interupts */
	if (size > UART_BUFFER_SIZE){
		tx2.status = UART_BUFFER_ERROR; 
	}else if(size == 0){
		/* null */
	}else{
		/* put data in trasmit buffer */
		for(i=0;i<size;i++){
			tx2.data[tx2.inptr++] = *(data++);
			tx2.inptr &= UART_BUFFER_MASK;
			/* check for buffer full */
			if(tx2.inptr == tx2.outptr){
				tx2.status = UART_BUFFER_FULL;
				/* return index value which caused buffer full */
				tx2.status |= i;
				/* end for loop */
				break;
			}
		}
		/* initiate first tranfer, subsequent transfers are handled by interrupt */
		tx2.status = UART_BUFFER_RDY;
		Write2USART(tx2.data[tx2.outptr++]);
		tx2.outptr &= UART_BUFFER_MASK;
		/* enable tx interrupts */
		PIE3bits.TX2IE = 1;
	}
	return tx2.status;
}

//**************************************************************
//FUNCTION NAME:    uart2_tx   
//ARGUMENTS:        const rom unsigned char *data - pointer to data string
//					unsigned char size - size of data string to add to txbuffer 
//RETURNS:          status of tx buffer
//DESCRIPTION:      puts data into the uart transmit queue
//**************************************************************
unsigned char uart2_romtx(const rom unsigned char *data, unsigned char size){

	unsigned char i;

	/* check if data can fit in buffer, this doesn't check if the buffer's current
	   current pointers will allow (size) data to fit because it may be emptying 
	   concurrently through interupts */
	if (size > UART_BUFFER_SIZE){
		tx2.status = UART_BUFFER_ERROR; 
	}else if(size == 0){
		/* null */
	}else{
		/* put data in trasmit buffer */
		for(i=0;i<size;i++){
			tx2.data[tx2.inptr++] = *(data++);
			tx2.inptr &= UART_BUFFER_MASK;
			/* check for buffer full */
			if(tx2.inptr == tx2.outptr){
				tx2.status = UART_BUFFER_FULL;
				/* return index value which caused buffer full */
				tx2.status |= i;
				/* end for loop */
				break;
			}
		}
		/* initiate first tranfer, subsequent transfers are handled by interrupt */
		tx2.status = UART_BUFFER_RDY;
		Write2USART(tx2.data[tx2.outptr++]);
		tx2.outptr &= UART_BUFFER_MASK;
		/* enable tx interrupts */
		PIE3bits.TX2IE = 1;
	}
	return tx2.status;
}

//**************************************************************
//FUNCTION NAME:    uart1_rx   
//ARGUMENTS:        unsigned char *data - pointer to data string
//					unsigned char cmd - read or peak (peak doesn't empty buffer) 
//RETURNS:          unsigned char - size of data that was read
//DESCRIPTION:      reads or peaks the rx buffer
//**************************************************************
unsigned char uart1_rx(unsigned char *data, unsigned char cmd){

	unsigned char size=0;
	unsigned char outptr = rx1.outptr;

	/* read until buffer is empty */
	if(cmd == UART_READ){
		/* read with rx.outptr */
		while(!(rx1.outptr == rx1.inptr)){
			*(data++) = rx1.data[rx1.outptr++];
			rx1.outptr &= UART_BUFFER_MASK;
			rx1.status = UART_BUFFER_RDY;
			size++;
		}
		rx1.status = UART_BUFFER_EMPTY;
	}else{
		/* read with outptr, don't affect any status or pointers */
		while(!(outptr == rx1.inptr)){
			*(data++) = rx1.data[outptr++];
			outptr &= UART_BUFFER_MASK;
			size++;
		}
	}
	return size;
}
//**************************************************************
//FUNCTION NAME:    uart2_rx   
//ARGUMENTS:        unsigned char *data - pointer to data string
//					unsigned char cmd - read or peak (peak doesn't empty buffer) 
//RETURNS:          unsigned char - size of data that was read
//DESCRIPTION:      reads or peaks the rx buffer
//**************************************************************
unsigned char uart2_rx(unsigned char *data, unsigned char cmd){

	unsigned char size=0;
	unsigned char outptr = rx2.outptr;

	/* read until buffer is empty */
	if(cmd == UART_READ){
		/* read with rx.outptr */
		while(!(rx2.outptr == rx2.inptr)){
			*(data++) = rx2.data[rx2.outptr++];
			rx2.outptr &= UART_BUFFER_MASK;
			rx2.status = UART_BUFFER_RDY;
			size++;
		}
		rx2.status = UART_BUFFER_EMPTY;
	}else{
		/* read with outptr, don't affect any status or pointers */
		while(!(outptr == rx2.inptr)){
			*(data++) = rx2.data[outptr++];
			outptr &= UART_BUFFER_MASK;
			size++;
		}
	}
	return size;
}

//**************************************************************
//FUNCTION NAME:    uart1_get_status   
//ARGUMENTS:        unsigned char rxtx -  
//RETURNS:          unsigned char - returns the buffer's status unsigned char
//DESCRIPTION:      returns the rx or tx buffer's status unsigned char
//**************************************************************
unsigned char uart1_get_status(unsigned char rxtx){

	unsigned char status = tx1.status;

	if(rxtx == UART_RX){
		status = rx1.status;
	}
	return status;
}
//**************************************************************
//FUNCTION NAME:    uart2_get_status   
//ARGUMENTS:        unsigned char rxtx -  
//RETURNS:          unsigned char - returns the buffer's status unsigned char
//DESCRIPTION:      returns the rx or tx buffer's status unsigned char
//**************************************************************
unsigned char uart2_get_status(unsigned char rxtx){

	unsigned char status = tx2.status;

	if(rxtx == UART_RX){
		status = rx2.status;
	}
	return status;
}

//**************************************************************
//FUNCTION NAME:    uart1_rx_callback   
//ARGUMENTS:        
//RETURNS:          
//DESCRIPTION:      handles the uart rx interrupts
//**************************************************************
void uart1_rx_callback(void){

	unsigned char dummy;

	/* if buffer is full, read into dummy and set error in status */
	if(rx1.status == UART_BUFFER_FULL){
		dummy = Read1USART();
		rx1.status = UART_BUFFER_ERROR;
	}else{
		rx1.data[rx1.inptr++] = Read1USART();
		rx1.inptr &= UART_BUFFER_MASK;
		rx1.status = UART_BUFFER_RDY;
		if(rx1.outptr == rx1.inptr){
			rx1.status = UART_BUFFER_FULL;
		}
	}
}
//**************************************************************
//FUNCTION NAME:    uart2_rx_callback   
//ARGUMENTS:        
//RETURNS:          
//DESCRIPTION:      handles the uart rx interrupts
//**************************************************************
void uart2_rx_callback(void){

	unsigned char dummy;

	/* if buffer is full, read into dummy and set error in status */
	if(rx2.status == UART_BUFFER_FULL){
		dummy = Read2USART();
		rx2.status = UART_BUFFER_ERROR;
	}else{
		rx2.data[rx2.inptr++] = Read2USART();
		rx2.inptr &= UART_BUFFER_MASK;
		rx2.status = UART_BUFFER_RDY;
		if(rx2.outptr == rx2.inptr){
			rx2.status = UART_BUFFER_FULL;
		}
	}
}

//**************************************************************
//FUNCTION NAME:    uart1_tx_callback   
//ARGUMENTS:        
//RETURNS:          
//DESCRIPTION:      handles the uart rx interrupts
//**************************************************************
void uart1_tx_callback(void){

	/* check if all data in buffer has been transmitted */
	if(tx1.outptr == tx1.inptr){
		tx1.status = UART_BUFFER_EMPTY;
		/* disable interrupts since buffer is empty */
		PIE1bits.TX1IE = 0;
	}else if(tx1.status == UART_BUFFER_RDY){
		Write1USART(tx1.data[tx1.outptr++]);
		tx1.outptr &= UART_BUFFER_MASK;
	}
}
//**************************************************************
//FUNCTION NAME:    uart2_tx_callback   
//ARGUMENTS:        
//RETURNS:          
//DESCRIPTION:      handles the uart rx interrupts
//**************************************************************
void uart2_tx_callback(void){

	/* check if all data in buffer has been transmitted */
	if(tx2.outptr == tx2.inptr){
		tx2.status = UART_BUFFER_EMPTY;
		/* disable interrupts since buffer is empty */
		PIE3bits.TX2IE = 0;
	}else if(tx2.status == UART_BUFFER_RDY){
		Write2USART(tx2.data[tx2.outptr++]);
		tx2.outptr &= UART_BUFFER_MASK;
	}
}