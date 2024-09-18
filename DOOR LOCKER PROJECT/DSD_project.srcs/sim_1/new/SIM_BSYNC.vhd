library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
entity SIM_BSYNC is

end SIM_BSYNC;

architecture Behavioral of SIM_BSYNC is
component button_sync is
port(
CLK : in std_logic;
btn : in std_logic;
output : out std_logic
);
end component;

signal CLK : std_logic := '0';
signal btn : std_logic := '0';
signal output : std_logic;
begin
UUT : button_sync
port map(
    CLK    => CLK   ,
    btn    => btn   ,
    output => output
);
clk_process : process
begin 
    CLK <= '1';
    wait for 5ns;
    CLK <= '0';
    wait for 5ns;
end process;

button : process 
begin 
    wait for 10ns; 
    btn <= '1';
    wait for 30ns;
    btn <= '0';
    wait for 20ns;
    btn <= '1';
    wait for 10ns;
    btn <= '0';
    wait for 100ns;
end process;

end Behavioral;
