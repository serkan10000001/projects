library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity SIM_TOP is
end SIM_TOP;

architecture Behavioral of SIM_TOP is
component TOP is
port(
    BTNL : in std_logic;
    BTNC : in std_logic;
    BTNR : in std_logic;
    sw : in std_logic_vector(11 downto 0);
    CLK100MHZ : in std_logic;
    
    LED : out std_logic_vector(11 downto 0);
    WRONG : out std_logic;
    CLK_INDICATOR : out std_logic;
    LOADED_INDICATOR : out std_logic;
    SHIFT_INDICATOR : out std_logic
);
end component;

signal BTNL_TB : std_logic  := '0'   ;
signal BTNC_TB : std_logic  := '0'   ;
signal BTNR_TB : std_logic  := '0'   ;
signal sw_TB : std_logic_vector(11 downto 0);
signal CLK100MHZ_TB : std_logic;

signal LED_TB : std_logic_vector(11 downto 0);
signal WRONG_TB : std_logic;
signal CLK_INDICATOR_TB : std_logic;
signal LOADED_INDICATOR_TB : std_logic;
signal SHIFT_INDICATOR_TB : std_logic;
begin

UUT : TOP
port map(
BTNL                => BTNL_TB             ,
BTNC                => BTNC_TB             ,
BTNR                => BTNR_TB             ,
sw                  => sw_TB               ,
CLK100MHZ           => CLK100MHZ_TB        ,
LED                 => LED_TB              ,
WRONG               => WRONG_TB            ,
CLK_INDICATOR       => CLK_INDICATOR_TB    ,
LOADED_INDICATOR    => LOADED_INDICATOR_TB ,
SHIFT_INDICATOR     => SHIFT_INDICATOR_TB  
);

CLK : process 
begin 
    CLK100MHZ_TB <= '0';
    wait for 5ns;
    CLK100MHZ_TB <= '1';
    wait for 5ns;
end process;

MAIN : process 
begin 
    BTNC_TB <= '0';
    BTNR_TB <= '0';
    BTNL_TB <= '0';
    sw_TB <= "000001111000";
    wait for 10ns;
    BTNR_TB <= '1';
    wait for 10ns;
    BTNR_TB <= '0';
    wait for 10ns;
    BTNL_TB <= '1'; 
    wait for 30ns;
    BTNL_TB <= '0'; 
    wait for 140ns;
    BTNC_TB <= '1'; 
    wait for 10ns;
    BTNC_TB <= '0';
    wait for 10ns;
    BTNC_TB <= '0';
    sw_TB <= "000011111000";
    wait for 10ns;
    BTNR_TB <= '1';
    wait for 10ns;
    BTNR_TB <= '0';
    wait for 10ns;
    BTNL_TB <= '1'; 
    wait for 10ns;
    BTNL_TB <= '0'; 
    wait for 140ns;
end process;
end Behavioral;
