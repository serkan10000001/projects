library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity SIM_SR is
end SIM_SR;

architecture Behavioral of SIM_SR is
constant clk_period : time := 10ns;

component shift_register is
generic(N: integer := 12; clk : integer := 100_000_000);
port(
CLKA : in std_logic;
sw : in std_logic_vector(N-1 downto 0);
shift_start : in std_logic;
load_enable : in std_logic;
register_output : out std_logic;
reset : in std_logic;
LOADED : out std_logic;
T : out std_logic;
S : out std_logic
);
end component;


signal CLKA : std_logic := '0';
signal sw : std_logic_vector(11 downto 0) := "000000000000";
signal shift_start : std_logic := '0';
signal load_enable : std_logic := '0';
signal register_output : std_logic;
signal reset : std_logic := '0';
signal LOADED : std_logic;
signal T : std_logic;
signal S : std_logic;
begin

UUT : shift_register 
port map(
CLKA               =>   CLKA           ,
sw     =>   sw ,
shift_start        =>   shift_start    ,
load_enable        =>   load_enable    ,
register_output    =>   register_output,
reset => reset,
LOADED => LOADED, 
T => T, 
S => S
);

clk_process : process 
begin 
    CLKA <= '0';
    wait for clk_period/2;
    CLKA <= '1';
    wait for clk_period/2;
end process;

main: process 
begin 
    wait for 1ns;
    sw <= "000001111000";
    wait for 10ns;
    load_enable <= '1';
    wait for 30ns;
    load_enable <= '0';
    wait for 10ns;
    shift_start <= '1';
    wait for 10ns;
    shift_start <= '0';
    wait for 130ns;
    reset <= '1';
    wait for 10ns;
    reset <= '0';
    wait for 10ns;
    sw <= "011011001110";
    wait for 10ns;
    load_enable <= '1';
    wait for 30ns;
    load_enable <= '0';
    wait for 10ns;
    shift_start <= '1';
    wait for 10ns;
    shift_start <= '0';
    wait for 130ns;
     
    
    
end process;

end Behavioral;
