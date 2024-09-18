library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity TOP is
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

end TOP;

architecture Behavioral of TOP is

component password_checker is
port(
CLK : in std_logic;
pass_in : in std_logic;
pass_out: out std_logic_vector(12 downto 1);
reset : in std_logic;
start_progress : in std_logic;
wrong_indicator : out std_logic
);
end component;

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

component clk_divider is
generic(clk : integer := 100_000_000);
port(
clk_register : in std_logic;
tick : out std_logic
);
end component;

signal divided_clk : std_logic;
signal shifted : std_logic;
signal error : std_logic;
begin

CLK_DIV : clk_divider
port map (
    clk_register => CLK100MHZ, 
    tick => divided_clk
);

SHIFT : shift_register 
port map(
    CLKA => CLK100MHZ,
    sw => sw,
    shift_start => BTNL,
    load_enable => BTNR,
    register_output => shifted,
    reset => BTNC,
    LOADED => LOADED_INDICATOR,
    T => CLK_INDICATOR,
    S => SHIFT_INDICATOR
);

PASS : password_checker 
port map (
    CLK => divided_clk,
    pass_in => shifted,
    pass_out => LED,
    reset => BTNC,
    start_progress => BTNL,
    wrong_indicator => WRONG
);



end Behavioral;
