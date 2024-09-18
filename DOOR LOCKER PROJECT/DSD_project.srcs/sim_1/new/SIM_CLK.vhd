library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity SIM_CLK is
end SIM_CLK;

architecture Behavioral of SIM_CLK is
component clk_divider is
generic(clk : integer := 100_000_000);
port(
clk_register : in std_logic;
tick : out std_logic
);
end component;

signal clk_register : std_logic;
signal tick : std_logic;


begin
UUT : clk_divider
port map(
clk_register => clk_register, 
tick => tick
);

CLKS : process 
begin 
    clk_register <= '0';
    wait for 5ns;
    clk_register <= '1';
    wait for 5ns;
end process;


end Behavioral;
