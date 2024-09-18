library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity password_checker is
port(
CLK : in std_logic;
pass_in : in std_logic;
pass_out: out std_logic_vector(11 downto 0);
reset : in std_logic;
start_progress : in std_logic;
wrong_indicator : out std_logic

);
end password_checker;

architecture Behavioral of password_checker is
type passwordCH is (start_t,wai_t, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, success, fail);
signal state_pass : passwordCH := start_t;
signal state_pass_next : passwordCH := start_t;
signal last_failed_state : std_logic_vector(11 downto 0);
signal Q : std_logic_vector(11 downto 0);


--1078
--0001 000001111000

begin
reg : process(CLK) 
begin 
    if(rising_edge(CLK)) then 
        Q <= last_failed_state;
    end if;
end process; 

state_transition : process(CLK)
begin 
    if(rising_edge(CLK)) then 
        state_pass <= state_pass_next;
    end if;
end process;

 state_output : process(state_pass, reset, start_progress, pass_in)
    begin
        if reset = '1' then
            pass_out <= (others => '0');
            wrong_indicator <= '0';
        else
            case state_pass is
                when start_t =>
                    pass_out <= (others => '0');
                    wrong_indicator <= '0';
                when wai_t =>
                    pass_out <= (others => '0');
                when p1 =>
                    pass_out <= Q;
                when p2 =>
                    pass_out <= Q;
                when p3 =>
                    pass_out <= Q;
                when p4 =>
                    pass_out <= Q;
                when p5 =>
                    pass_out <= Q;
                when p6 =>
                    pass_out <= Q;
                when p7 =>
                    pass_out <= Q;
                when p8 =>
                    pass_out <= Q;
                when p9 =>
                    pass_out <= Q;
                when p10 =>
                    pass_out <= Q;
                when p11 =>
                    pass_out <= Q;
                when success =>
                    pass_out <= Q;
                when fail =>
                    wrong_indicator <= '1';
                    -- pass_out remains unchanged in the fail state
                    pass_out <= Q;
            end case;
        end if;
    end process;

next_state_determination : process(pass_in, state_pass, reset, start_progress)
begin 
    case state_pass is 
        when start_t =>
            
            if(start_progress = '1') then 
                state_pass_next <= wai_T;
                last_failed_state <= "000000000000";
            else 
                state_pass_next <= start_t;
                
                last_failed_state <= "000000000000";
            end if;
        when wai_t =>
            if(pass_in = '0') then 
                state_pass_next <= p1;
                last_failed_state <= "000000000001";
                 
            elsif(pass_in = '1') then 
                last_failed_state <= "000000000000";
               
                state_pass_next <= fail;
                
            end if;
        when p1 =>
            
            if(pass_in = '0') then 
                state_pass_next <= p2;
                last_failed_state <= "000000000011";
             
            elsif(pass_in = '1') then 
                last_failed_state <= "000000000001";
                state_pass_next <= fail;
            
            end if;
        when p2 => 
            
            if(pass_in = '0') then 
                state_pass_next <= p3;
                last_failed_state <= "000000000111";
            elsif(pass_in = '1') then 
                last_failed_state <= "000000000011";
                state_pass_next <= fail;
          
            end if;
        when p3 =>
            
            if(pass_in = '1') then 
                state_pass_next <= p4;
               last_failed_state <= "000000001111";
          
            elsif(pass_in = '0') then 
                last_failed_state <= "000000000111";
                state_pass_next <= fail;
              
            end if;
        when p4 =>
            
            if(pass_in = '1') then 
                state_pass_next <= p5;
                last_failed_state <= "000000011111";
          
            elsif(pass_in = '0') then 
                last_failed_state <= "000000001111";
                state_pass_next <= fail;
          
            end if;
        when p5 =>
           
            if(pass_in = '1') then 
                state_pass_next <= p6;
           
                 last_failed_state <= "000000111111";
            elsif(pass_in = '0') then 
                 last_failed_state <= "000000011111";
                state_pass_next <= fail;
           
            end if;
        when p6 =>
            
            if(pass_in = '1') then 
                state_pass_next <= p7;
               
               last_failed_state <= "000001111111";
            elsif(pass_in = '0') then 
                last_failed_state <= "000000111111";
                state_pass_next <= fail;
             
            end if;
        when p7 =>
            
            if(pass_in = '0') then 
                state_pass_next <= p8;
                last_failed_state <= "000011111111";
                
            elsif(pass_in = '1') then 
                last_failed_state <= "000001111111";
                state_pass_next <= fail;
               
            end if;
        when p8 =>
            
            if(pass_in = '0') then 
                state_pass_next <= p9;
                last_failed_state <= "000111111111";
             
            elsif(pass_in = '1') then 
                last_failed_state <= "000011111111";
                state_pass_next <= fail;
                
            end if;
        when p9 =>
            
            if(pass_in = '0') then 
                state_pass_next <= p10;
                last_failed_state <= "001111111111";
            
            elsif(pass_in = '1') then 
                last_failed_state <= "000111111111";
                state_pass_next <= fail;
              
            end if;
        when p10 =>
            
            if(pass_in = '0') then 
                state_pass_next <= p11;
                last_failed_state <= "011111111111";
            
            elsif(pass_in = '1') then 
                last_failed_state <= "001111111111";
                state_pass_next <= fail;
            
            end if;
        when p11 =>
            
            if(pass_in = '0') then 
                state_pass_next <= success;
                last_failed_state <= "111111111111";
            
            elsif(pass_in = '1') then 
                last_failed_state <= "011111111111";
                state_pass_next <= fail;
           
            end if;
        when success =>
            
            if(reset = '1') then 
                state_pass_next <= start_t;
                 last_failed_state <= "000000000000";
            else 
                state_pass_next <= success;
                last_failed_state <= "111111111111";
            end if;
        when fail =>
            if(reset = '1') then
                state_pass_next <= start_t;

            else 
                state_pass_next <= fail;
                last_failed_state <= Q;
            end if;
    end case;
end process;

end Behavioral;
