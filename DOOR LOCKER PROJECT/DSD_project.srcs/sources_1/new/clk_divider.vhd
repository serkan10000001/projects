library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity clk_divider is
generic(clk : integer := 100_000_000);
port(
clk_register : in std_logic;
tick : out std_logic
);
end clk_divider;

architecture Behavioral of clk_divider is

constant timer_limit : integer := clk; 
signal timer : integer range 0 to timer_limit := 0;
signal timer_tick : std_logic;
signal counter : std_logic := '0';

begin
timer_s : process(clk_register) begin 
    if (rising_edge(clk_register))then 
            if (timer >= timer_limit - 1) then
                timer <= 0;
                timer_tick <= not timer_tick;
            else 
                timer <= timer + 1;
            end if;
    end if;
end process;
tick <= timer_tick;
end Behavioral;
