--*************************************************************
--
--  $Rev:: 305                                            $:  Revision of last commit
--  $Author:: reneleonrichard                             $:  Author of last commit
--  $Date:: 2014-10-09 20:11:27 -0400 (Thu, 09 Oct 2014)  $:  Date of last commit
--  $HeadURL: https://subversion.assembla.com/svn/db_repository/trunk/FPGAProjects/SMSCart/src/SMSCart.vhd $
--
--*************************************************************
--  db Mapper
--  Copyright 2014 Rene Richard
--  DEVICE : EPM3064ATC100-10
--*************************************************************
--
--  Description:
--		This is a VHDL implementation of a hybrid Sega + Codemasters SMS ROM mapper - the db Mapper
--		it is intended to be used on the db Electronics SMS Homebrew Carts
--		Supported Flash Memory Configurations:
--			1Mbit (1x 1Mbit)
--			2Mbit (1x 2Mbit)
--			4Mbit (1x 4Mbit)
--			8Mbit (2x 4Mbit)
--		Support RAM Configurations
--			32KB
--
--		for a complete description of SMS Mappers, go to http://www.smspower.org/Development/Mappers
--*************************************************************
--
--	Hybridization Features:
--		Register Merging:
--			$0000 (CM) merged with $FFFD (SEGA)
--			$4000 (CM) merged with $FFFE (SEGA)
--			$8000 (CM) merged with $FFFF (SEGA)
--			both addresses are valid
--		RAM and Misc. Register
--			$FFFC
--				bit 7: ROM Write Enable
--					when '1' writes to ROM (i.e. Flash) are enabled
--					when '0' writes to mapper registers are enabled
--				bit 3: RAM Enable
--					when '1' RAM will be mapped into slot 2, overriding any ROM banking via $ffff/$8000
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
			ADDR_p		:	in		std_logic_vector(15 downto 0);
			DATA_p		:	in 	std_logic_vector(7 downto 0);
			nRST_p		:	in 	std_logic;
			nWR_p			:	in		std_logic;
			nMREQ_p		:	in		std_logic;
			
			--output to ROM
			nROMWR_p			:	out	std_logic;
			nROMCE0_p		:	out	std_logic;
			nROMCE1_p		:	out 	std_logic;
			ROMADDR1814_p	:	out	std_logic_vector(4 downto 0);

			--output to SRAM
			nSRAMCE_p		:	out	std_logic;
			SRAMADDR14_p	:	out	std_logic
	);
end entity; 

architecture SMSCart_a of SMSCart is

	--internal data and address signals for easy write back if ever needed
	signal datain_s		:	std_logic_vector(7 downto 0);
	signal addr_s			:	std_logic_vector(15 downto 0);
	signal mapAddr_s		:  std_logic_vector(5 downto 0);
	signal mapAddrShift_s	:  std_logic_vector(5 downto 0);
	
	--Mapper slot registers, fitter will optimize any unused bits
	signal romSlot0_s		:	std_logic_vector(5 downto 0);
	signal romSlot1_s		:	std_logic_vector(5 downto 0);
	signal romSlot2_s		:	std_logic_vector(5 downto 0);

	--Bank Shift
	signal bankShiftCode_s	:	std_logic_vector(5 downto 0);
	signal bankShift_s	:	std_logic_vector(3 downto 0);
	signal bankShiftEn_s	:	std_logic;
	
	--internal write signals
	signal romWrEn_s		:	std_logic;
	
	--RAM mapping signals
	signal ramEn_s			:	std_logic;
	signal ramBank_s		:	std_logic;
	
begin

	--internal data and address signals
	addr_s <= ADDR_p; 
	datain_s <= DATA_p;
	
	--output mapping to ROM and RAM
	--	internally it is handled as 1x 1MB, externally it is 2x 512KB chips
	--chip select to both ROMs handled in chipSelect process below
	ROMADDR1814_p <= mapAddrShift_s(4 downto 0);
	SRAMADDR14_p <= ramBank_s;
	
	--ROM Write Gating with bit7 of $FFFC
	nROMWR_p <= nWR_p when romWrEn_s = '1' else '1';
	
	--RAM mapping and miscellaneous functions register
	ram0: process( nRST_p, nWR_p, nMREQ_p, addr_s )
	begin
		if nRST_p = '0' then
			romWrEn_s <= '0';
			ramEn_s <= '0';
			ramBank_s <= '0';
		elsif rising_edge(nWR_p) then
			if addr_s = x"FFFC" and  nMREQ_p = '0' then
				romWrEn_s <= datain_s(7);
				ramEn_s <= datain_s(3);
				ramBank_s <= datain_s(2);
				if bankShiftEn_s = '0' then
					bankShift_s(3) <= datain_s(6);
					bankShift_s(2) <= datain_s(5);
					bankShift_s(1) <= datain_s(1);
					bankShift_s(0) <= datain_s(0);
				end if;
			end if;
		end if;
	end process;
	

	--bank shifting register
	bankshift: process( nRST_p, nWR_p, nMREQ_p, addr_s)
	begin
		if nRST_p = '0' then
			bankShiftCode_s <= "000000";
			bankShiftEn_s <= '0';
		elsif rising_edge(nWR_p) then
			if nMREQ_p = '0' then 
				case addr_s is
					when x"FFFC" =>
						if bankShiftCode_s = "101101" then
							bankShiftEn_s <= '0';
						end if;
					when x"FFFD" => 
						bankShiftCode_s(1 downto 0) <= datain_s(7 downto 6);
					when x"FFFE" =>
						bankShiftCode_s(3 downto 2) <= datain_s(7 downto 6);
					when x"FFFF" =>
						bankShiftCode_s(5 downto 4) <= datain_s(7 downto 6);
					when others =>
						null;
				end case;
			end if;
		end if;
	end process;
	
	--mapper registers
	mappers: process( nRST_p, nWR_p, nMREQ_p, addr_s)
	begin
		if nRST_p = '0' then
			romSlot0_s <= "000000";
			romSlot1_s <= "000001";
			romSlot2_s <= "000010";
		elsif rising_edge(nWR_p) then
			if nMREQ_p = '0' then
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
				-- first kilobyte is always from bank 0 in SEGA MAPPER mode
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
	
	--apply bankshifting if bankShiftEn_s = '1'
	--mapAddrShift_s <= (bankShift_s or mapAddr_s(5 downto 2)) & mapAddr_s(1 downto 0) when bankShiftEn_s = '1' else
	--						mapAddr_s;
	mapAddrShift_s <= (bankShift_s + mapAddr_s(5 downto 2)) & mapAddr_s(1 downto 0) when bankShiftEn_s = '1' else
							mapAddr_s;
	
	--drive chip select lines
	chipSelect: process( addr_s, mapAddrShift_s, ramEn_s, nMREQ_p )
	begin
		nSRAMCE_p <= '1';
		nROMCE0_p <= '1';
		nROMCE1_p <= '1';
		case addr_s(15 downto 14) is
			--slot 0
			when "00" =>
				--select upper or lower ROM based on A19 (mapAddrShift_s(5))
				if mapAddrShift_s(5) = '0' then
					nROMCE0_p <= nMREQ_p;
				else
					nROMCE1_p <= nMREQ_p;
				end if;
			--slot 1
			when "01" =>
				--select upper or lower ROM based on A19
				if mapAddrShift_s(5) = '0' then
					nROMCE0_p <= nMREQ_p;
				else
					nROMCE1_p <= nMREQ_p;
				end if;
			--slot 2
			when "10" =>
				--RAM mapping has priority in Slot 2
				if ramEn_s = '1' then
					nSRAMCE_p <= nMREQ_p;
				else
					--select upper or lower ROM based on A19
					if mapAddrShift_s(5) = '0' then
						nROMCE0_p <= nMREQ_p;
					else
						nROMCE1_p <= nMREQ_p;
					end if;
				end if;
			when others =>
				--don't drive anything in slot 4
				nSRAMCE_p <= '1';
				nROMCE0_p <= '1';
				nROMCE1_p <= '1';
		end case;
	end process;
	
end SMSCart_a;