--*************************************************************
--
--  $Rev:: 305                                            $:  Revision of last commit
--  $Author:: reneleonrichard                             $:  Author of last commit
--  $Date:: 2014-10-09 20:11:27 -0400 (Thu, 09 Oct 2014)  $:  Date of last commit
--  $HeadURL: https://subversion.assembla.com/svn/db_repository/trunk/FPGAProjects/SMSCart/src/SMSCart.vhd $
--
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
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.NUMERIC_STD.ALL;

library altera; 
use altera.altera_primitives_components.all;

entity SMSCart is 

	port (
			--input from sms
			ADDR_p			:	in		std_logic_vector(15 downto 0);
			DATA_p			:	in 	std_logic_vector(7 downto 0);
			nRST_p			:	in 	std_logic;
			nWR_p				:	in		std_logic;
			nCE_p				:	in		std_logic;
			nOE_p				:	in		std_logic;
			
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
			SRAMADDR14_p	:	out	std_logic
	);
end entity; 

architecture SMSCart_a of SMSCart is

	--internal data and address signals for easy write back if ever needed
	signal datain_s		:	std_logic_vector(7 downto 0);
	signal addr_s			:	std_logic_vector(15 downto 0);
	
	--Mapper slot registers, fitter will optimize any unused bits
	signal romSlot0_s		:	std_logic_vector(5 downto 0);
	signal romSlot1_s		:	std_logic_vector(5 downto 0);
	signal romSlot2_s		:	std_logic_vector(5 downto 0);
	signal mapAddr_s		: 	std_logic_vector(5 downto 0);
	
	--internal rom signals
	signal romWrEn_s		:	std_logic;
	signal nRomCE_s		: 	std_logic;
	signal nRomWE_s		:	std_logic;
	
	--RAM mapping signals
	signal ramEn_s			:	std_logic;
	signal ramBank_s		:	std_logic;
	
begin

	--internal data and address signals
	addr_s <= ADDR_p; 
	datain_s <= DATA_p;
	
	--output mapping to ROM and RAM
	SRAMADDR14_p <= ramBank_s;
	
	--high order address bits and WE and CE must be open-drain to meet 5V requirements
	-- 1K pull-up on each of these lines
	ROMADDR1914_p(0) <= '0' when mapAddr_s(0) = '0' else 'Z';
	ROMADDR1914_p(1) <= '0' when mapAddr_s(1) = '0' else 'Z';
	ROMADDR1914_p(2) <= '0' when mapAddr_s(2) = '0' else 'Z';
	ROMADDR1914_p(3) <= '0' when mapAddr_s(3) = '0' else 'Z';
	ROMADDR1914_p(4) <= '0' when mapAddr_s(4) = '0' else 'Z';
	ROMADDR1914_p(5) <= '0' when mapAddr_s(5) = '0' else 'Z';
	--ROM Write Gating with bit7 of $FFFC
	nRomWE_s <= nCE_p when romWrEn_s = '1' else '1';
	nROMWE_p <= '0' when nRomWE_s = '0' else 'Z';
	nROMCE_p <= '0' when nRomCE_s = '0' else 'Z';
	
	--default values for now, todo later
	EE_CS_p <= '1';
	EE_SO_p <= '1';
	EE_SI_p <= '1';
	EE_SCK_p <= '1';
	
	--RAM mapping and miscellaneous functions register
	ram0: process( nRST_p, nWR_p, nCE_p, addr_s )
	begin
		if nRST_p = '0' then
			romWrEn_s <= '0';
			ramEn_s <= '0';
			ramBank_s <= '0';
		--nWR rises before address and mreq on Z80
		elsif falling_edge(nWR_p) then
			if addr_s = x"FFFC" and  nCE_p = '0' then
				romWrEn_s <= datain_s(7);
				ramEn_s <= datain_s(3);
				ramBank_s <= datain_s(2);
			end if;
		end if;
	end process;
	
	--mapper registers
	mappers: process( nRST_p, nWR_p, nCE_p, addr_s)
	begin
		if nRST_p = '0' then
			romSlot0_s <= "000000";
			romSlot1_s <= "000001";
			romSlot2_s <= "000010";
		--nWR rises before address and mreq on Z80
		elsif falling_edge(nWR_p) then
			if nCE_p = '0' then
				case addr_s is
					when x"FFFD" => 
						romSlot0_s <= datain_s(5 downto 0);
					when x"FFFE" =>
						romSlot1_s <= datain_s(5 downto 0);
					when x"FFFF" =>
						romSlot2_s <= datain_s(5 downto 0);
					when others =>
						null;
				end case;
			end if;
		end if;
	end process;

	--banking select
	--only looks at address, this way the address setup and hold times can be respected
	banking: process( addr_s )
	begin
		mapAddr_s <= (others=>'0');
		case addr_s(15 downto 14) is
			when "00" =>
				-- first kilobyte is always from bank 0 in SEGA MAPPER
				if addr_s(13 downto 10)="0000" then
					mapAddr_s <= (others=>'0');
				else
					mapAddr_s <= romSlot0_s(5 downto 0);
				end if;
			when "01" =>
				mapAddr_s <= romSlot1_s(5 downto 0);
			when "10" =>
				mapAddr_s <= romSlot2_s(5 downto 0);
			when others =>
				mapAddr_s <= (others=>'0');
		end case;
	end process;
	
	--drive chip select lines
	chipSelect: process( addr_s, ramEn_s, nCE_p )
	begin
		nSRAMCE_p <= '1';
		nRomCE_s <= '1';
		case addr_s(15 downto 14) is
			--slot 0
			when "00" =>
				nRomCE_s <= nCE_p;
			--slot 1
			when "01" =>
				nRomCE_s <= nCE_p;
			--slot 2
			when "10" =>
				--RAM mapping has priority in Slot 2
				if ramEn_s = '1' then
					nSRAMCE_p <= nCE_p;
				else
					--select upper or lower ROM based on A19
					nRomCE_s <= nCE_p;
				end if;
			when others =>
				--don't drive anything in slot 4
				nSRAMCE_p <= '1';
				nRomCE_s <= '1';
		end case;
	end process;
	
end SMSCart_a;