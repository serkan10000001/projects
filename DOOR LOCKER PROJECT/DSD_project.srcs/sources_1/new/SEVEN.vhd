library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity SEVEN is
port(
CLK : in std_logic;
ww : in std_logic;
w : in std_logic;
l : in std_logic;
s : in std_logic;
ss : in std_logic;
seg : out std_logic_vector(6 downto 0);
an : out std_logic_vector(3 downto 0)
);
end SEVEN;

architecture Behavioral of SEVEN is
signal reg , rex: unsigned (17 downto 0);
signal sel: std_logic_vector (1 downto 0);

begin
transition : process(CLK, ww, w, l, s, ss)
begin 
    if(rising_edge(CLK)) then 
        reg <= rex;
        if(ss = '1') then 
            case sel is 
                        when "00" => 
                            an <= "1110"; 
                            seg <= "1001000";
                        when "01" => 
                            an <= "1101";
                            seg <= "0000110";
                        when "10" => 
                            an <= "1011"; 
                            seg <= "0001100";
                        when "11" => 
                            an <= "0111";
                            seg <= "1000000";
                  end case;
        end if;
        if(l = '1') then 
            case sel is 
                        when "00" => 
                            an <= "1110"; 
                            seg <= "0100001";
                        when "01" => 
                            an <= "1101";
                            seg <= "0001000";
                        when "10" => 
                            an <= "1011"; 
                            seg <= "1000000";
                        when "11" => 
                            an <= "0111";
                            seg <= "1000111";
                  end case;
        end if;
        if(w = '1') then 
            case sel is 
                        when "00" => 
                            an <= "1110"; 
                            seg <= "1000111";
                        when "01" => 
                            an <= "1101";
                            seg <= "1001111";
                        when "10" => 
                            an <= "1011"; 
                            seg <= "0001000";
                        when "11" => 
                            an <= "0111";
                            seg <= "0001110";
                  end case;
        end if;
        if(s = '1') then 
            case sel is 
                        when "00" => 
                            an <= "1110"; 
                            seg <= "0000111";
                        when "01" => 
                            an <= "1101";
                            seg <= "0001110";
                        when "10" => 
                            an <= "1011"; 
                            seg <= "0001001";
                        when "11" => 
                            an <= "0111";
                            seg <= "0010010";
                  end case;
        end if;
        if(ww = '1') then 
            case sel is 
                        when "00" => 
                            an <= "1110"; 
                            seg <= "0000111";
                        when "01" => 
                            an <= "1101";
                            seg <= "1001111";
                        when "10" => 
                            an <= "1011"; 
                            seg <= "0001000";
                        when "11" => 
                            an <= "0111";
                            seg <= "1000001";
                  end case;
        end if;
    end if;
end process;

end Behavioral;
