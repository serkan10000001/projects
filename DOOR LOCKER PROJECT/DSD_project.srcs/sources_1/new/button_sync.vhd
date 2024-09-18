library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
entity button_sync is
port(
CLK : in std_logic;
btn : in std_logic;
output : out std_logic
);
end button_sync;

architecture Behavioral of button_sync is
type bT_transition is (s1, s2, s3);
signal state_bT : bT_transition := s1;
signal state_bT_next : bT_transition := s1;

begin
state_transition : process(CLK)
begin 
    if(rising_edge(CLK)) then 
        state_bT <= state_bT_next;
    end if;
end process;

next_state_determination : process(btn, state_bT)
begin 
    case state_bT is
        when s1 => 
            if(btn = '1') then 
                state_bT_next <= s2;
            else
                state_bT_next <= s1;
            end if;
        when s2 =>
            state_bT_next <= s3;
        when s3 =>
            if(not(btn) = '1') then 
                state_bT_next <= s1;
            else 
                state_bT_next <= s3;
            end if;
    end case;
end process;

state_output : process(btn, state_bT) 
begin 
    case state_bT is 
        when s1 =>
            output <= '0';
        when s2 =>
            output <= '1';
        when s3 =>
            output <= '0';
    end case;
end process;
end Behavioral;
