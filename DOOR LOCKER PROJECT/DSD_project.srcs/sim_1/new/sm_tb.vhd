
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity sm_tb is
end sm_tb;

architecture Behavioral of sm_tb is
component password_checker is
port(
CLK : in std_logic;
pass_in : in std_logic;
pass_out: out std_logic_vector(11 downto 0);
reset : in std_logic;
start_progress : in std_logic;
wrong_indicator : out std_logic

);
end component;

signal CLK : std_logic;
signal pass_in : std_logic;
signal pass_out : std_logic_vector(11 downto 0); 
signal reset : std_logic;
signal start_progress : std_logic;
signal wrong_indicator : std_logic;
begin

UUT : password_checker 
port map(
CLK             => CLK            ,
pass_in         => pass_in        ,
pass_out        => pass_out       ,
reset           => reset          ,
start_progress  => start_progress ,
wrong_indicator => wrong_indicator
);
-- 000001111000
CLKS : process 
begin 
    CLK <= '0'; 
    wait for 5ns;
    CLK <= '1';
    wait for 5ns;
end process;

MAIN : process 
begin 
    start_progress <= '0';
    wait for 10ns;
    start_progress <= '1';
    wait for 10ns;
    start_progress <= '0';
    pass_in <= '0';
    wait for 10ns;
    pass_in <= '0';
    wait for 10ns;
    pass_in <= '0';
    wait for 10ns;
    pass_in <= '1';
    wait for 10ns;
    pass_in <= '1';
    wait for 10ns;
    pass_in <= '1';
    wait for 10ns;
    pass_in <= '1';
    wait for 10ns;
    pass_in <= '0';
    wait for 10ns;
    pass_in <= '0';
    wait for 10ns;
    pass_in <= '0';
    wait for 10ns;
    pass_in <= '0';
    wait for 10ns;
    pass_in <= '0';
    wait for 10ns;
    reset <= '1';
    wait for 10ns;
    reset <= '0';
    wait for 10ns;
    
    start_progress <= '1';
    wait for 10ns;
    start_progress <= '0';
    pass_in <= '0';
    wait for 10ns;
    pass_in <= '0';
    wait for 10ns;
    pass_in <= '0';
    wait for 10ns;
    pass_in <= '1';
    wait for 10ns;
    pass_in <= '1';
    wait for 10ns;
    pass_in <= '1';
    wait for 10ns;
    pass_in <= '1';
    wait for 10ns;
    pass_in <= '0';
    wait for 10ns;
    pass_in <= '1';
    wait for 10ns;
    pass_in <= '0';
    wait for 10ns;
    pass_in <= '0';
    wait for 10ns;
    pass_in <= '0';
    wait for 10ns;
end process;

end Behavioral;
