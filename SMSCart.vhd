--*************************************************************
--  db Mapper
--  Copyright 2015 Rene Richard
--  DEVICE : EPM3064ATC100-10
--*************************************************************
--
--  Description:
--		This is a VHDL implementation of an SMS Sega Mapper
--		it is intended to be used on the db Electronics SMS Homebrew Carts
--		Supported Flash Memory Configurations:
--			2Mbit (1x 2Mbit)
--			4Mbit (1x 4Mbit)
--			8Mbit (1x 4Mbit)
--		Support RAM Configurations
--			32KB
--
--		for a complete description of SMS Mappers, go to http://www.smspower.org/Development/Mappers
--*************************************************************
--
--		RAM and Misc. Register
--			$FFFC
--				bit 7: ROM Write Enable
--					when '1' writes to ROM (i.e. Flash) are enabled
--					when '0' writes to mapper registers are enabled
--				bit 3: RAM Enable
--					when '1' RAM will be mapped into slot 2, overriding any ROM banking via $ffff
--					when '0' ROM banking is effective
--				bit 2: RAM Bank Select
--					when '1' maps the upper 16KB of RAM into slot 2
--					when '0' maps the lower 16KB of RAM into slot 2
--*************************************************************

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity SMSCart is 

	port (
			--input from sms
			ADDR_p			:	in		std_logic_vector(15 downto 0);
			DATA_p			:	in 	std_logic_vector(7 downto 0);
			nRST_p			:	in 	std_logic;
			nWR_p				:	in		std_logic;
			nCE_p				:	in		std_logic;
			
			--output to ROM
			nROMWE_p			:	out	std_logic;
			nROMCE_p			:	out	std_logic;
			ROMADDR1914_p	:	out	std_logic_vector(5 downto 0);

			--output to serial EEPROM
			EE_CS_p			: 	out	std_logic;
			EE_SO_p			:	out	std_logic;
			EE_SI_p			:	out	std_logic;
			EE_SCK_p			:	out	std_logic;
			
			--output to SRAM
			nSRAMCE_p		:	out	std_logic;
			nSRAMWE_p		:  out   std_logic;
			SRAMADDR14_p	:	out	std_logic
	);
end entity; 

architecture SMSCart_a of SMSCart is
	
begin

	SMSMapper_inst: entity work.SMSMapper
		port map(
			ADDR_p => ADDR_p,
			DATA_p => DATA_p,
			nRST_p => nRST_p,
			nWR_p => nWR_p,
			nCE_p => nCE_p,
			nROMWE_p => nROMWE_p,
			nROMCE_p => nROMCE_p,
			ROMADDR1914_p => ROMADDR1914_p,
			EE_CS_p => EE_CS_p,
			EE_SO_p => EE_SO_p,
			EE_SI_p => EE_SI_p,
			EE_SCK_p => EE_SCK_p,
			nSRAMCE_p => nSRAMCE_p,
			nSRAMWE_p => nSRAMWE_p,
			SRAMADDR14_p => SRAMADDR14_p
		);
	
end SMSCart_a;