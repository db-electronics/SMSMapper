
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
//  $HeadURL: https://subversion.assembla.com/svn/db_repository/trunk/Personal%20Projects/SMSHomebrew/Firmware/serialCmd.h $
//
//*************************************************************
//defines, includes, enums here
//**************************************************************

#ifndef SERIALCMD_H
#define SERIALCMD_H

#define TMR1_TIMEOUT_1S		62500

// s7  s6  s5  s4  s3  s2  s1  s0
// h3  h2  h1  h0  m7  m6  m5  m4  m3  m2  m1  m0  l7  l6  l5  l4  l3  l2  l1  l0
//A19 A18 A17 A16 A15 A14 A13 A12 A11 A10 A09 A08 A07 A06 A05 A04 A03 A02 A01 A00
// c   m   m   m   m   m   a   a   a   a   a   a   a   a   a   a   a   a   a   a
// c = chip select
// m = mapper select
// a = address select
// s = sector address

//**************************************************************
//COMMAND ACKNOWLEDGE
//all commands sent to the burner are acknowledged by returning
//the command byte with bit7 set. Inherently, commands all have
//bit7 cleared.
//
//example:
//send detect command 0x40, the burner will respond with 0xC0
//**************************************************************
#define SCMD_ACK			0x80

//**************************************************************
//LEGEND (point of view of PC)
//cc:				command
//ac:				acknowledged command
//ah:				address high byte 
//am:				address mid byte
//rb:				byte received from the burner
//**************************************************************

//**************************************************************
//COMMAND NAME:		Detect Burner
//PARAMETERS:		None
//RETURNS:			ack
//FORMAT:			cc, ac
//DESCRIPTION:		test if burner is present
//**************************************************************
#define	SCMD_DETECTBURNER	0x40

//**************************************************************
//COMMAND NAME:		Detect Flash Chips
//PARAMETERS:		None
//RETURNS:			ack
//					flash size (0, 1, 2, 4 or 8) as unsigned char
//FORMAT:			cc, ac, rb
//DESCRIPTION:		detect the size of flash cart attached
//**************************************************************
#define SCMD_DETECTFLASH	0x41

//**************************************************************
//COMMAND NAME:		Read Sector
//PARAMETERS:		addrh, addrm of sector
//RETURNS:			ack, sector data
//FORMAT:			cc, ac, ah, am, rb[0], ..., rb[4095]
//DESCRIPTION:		reads a 4KB sector from flash
//**************************************************************
#define SCMD_READSECTOR		0x42


//**************************************************************
//place function prototypes here
//**************************************************************

#endif /*SERIALCMD_H*/




