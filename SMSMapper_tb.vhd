library std;
use std.env.all;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity SMSMapper_tb is
end SMSMapper_tb;

architecture rtl of SMSMapper_tb is
--input from sms
	signal	ADDR			:		std_logic_vector(15 downto 0);
	signal	DATA			:	 	std_logic_vector(7 downto 0);
	signal	nRST			:	 	std_logic;
	signal	nWR			:		std_logic;
	signal	nCE			:		std_logic;

--output to ROM
	signal	nROMWE		:		std_logic;
	signal	nROMCE		:		std_logic;
	signal	ROMADDR1914	:		std_logic_vector(5 downto 0);

--output to serial EEPROM
	signal	EE_CS			: 		std_logic;
	signal	EE_SO			:		std_logic;
	signal	EE_SI			:		std_logic;
	signal	EE_SCK		:		std_logic;

--output to SRAM
	signal	nSRAMCE		:		std_logic;
	signal	nSRAMWE		:     std_logic;
	signal	SRAMADDR14	:		std_logic;
begin
	
	SMSMapper_u0: entity work.SMSMapper
		port map(
			ADDR_p => ADDR,
			DATA_p => DATA,
			nRST_p => nRST,
			nWR_p => nWR,
			nCE_p => nCE,
			nROMWE_p => nROMWE,
			nROMCE_p => nROMCE,
			ROMADDR1914_p => ROMADDR1914,
			EE_CS_p => EE_CS,
			EE_SO_p => EE_SO,
			EE_SI_p => EE_SI,
			EE_SCK_p => EE_SCK,
			nSRAMCE_p => nSRAMCE,
			nSRAMWE_p => nSRAMWE,
			SRAMADDR14_p => SRAMADDR14
		);
	
	sim: process
		begin
			nRST <= '0';
			DATA <= ( others => 'Z');
			nROMWE <= 'H';
			nROMCE <= 'H';
			ROMADDR1914 <= (others => 'H');
			ADDR <= ( others => '1');
			nCE <= '1';
			nWR <= '1';
			wait for 10 ns;
			
			nRST <= '1';
			DATA <= x"04";
			ADDR <= x"FFFD";
			wait for 5 ns;
			
			nCE <= '0';
			nWR <= '0';
			wait for 15 ns;
			
			nCE <= '1';
			nWR <= '1';
			wait for 5 ns;
			
			ADDR <= x"2000";
			wait for 5 ns;
			
			nCE <= '0';
			wait for 15 ns;
			
			nCE <= '1';
			wait for 5 ns;
			
			stop(0);
		end process;
	
end architecture;