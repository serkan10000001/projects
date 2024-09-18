library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity shift_register is
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
end shift_register;

architecture Behavioral of shift_register is
type reg is (initial, load, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12);
signal state : reg := initial;
signal state_next : reg := initial;
signal regs : std_logic_vector(12 downto 1);


constant timer_limit : integer := clk; 
signal timer : integer range 0 to timer_limit := 0;
signal timer_tick : std_logic;
signal counter : std_logic := '0';


begin


timer_s : process(CLKA) begin 
    if (rising_edge(CLKA))then 
            if (timer >= timer_limit - 1) then
                timer <= 0;
                timer_tick <= not timer_tick;
            else 
                timer <= timer + 1;
            end if;
    end if;
end process;

T <= timer_tick;

state_transition : process(timer_tick)
begin 
    if(rising_edge(timer_tick)) then 
        state <= state_next;
    end if;
end process;

output : process(shift_start, load_enable, reset, state)
begin 
    case state is 
        when initial =>
            register_output <= '0';
            LOADED <= '0';
            S <= '0';
        when load => 
            LOADED <= '1';
        when r1 =>
            LOADED <= '0';
            S <= '1';
            register_output <= regs(1);
        when r2 =>
            LOADED <= '0';
            S <= '1';
            register_output <= regs(2);
        when r3 =>
            LOADED <= '0';
            S <= '1';
            register_output <= regs(3);
        when r4 =>
            LOADED <= '0';
            S <= '1';
            register_output <= regs(4);
        when r5 =>
            LOADED <= '0';
            S <= '1';
            register_output <= regs(5);
        when r6 =>
            LOADED <= '0';
            S <= '1';
            register_output <= regs(6);
        when r7 =>
            LOADED <= '0';
            S <= '1';
            
            register_output <= regs(7);
        when r8 =>
            LOADED <= '0';
            S <= '1';
            register_output <= regs(8);
        when r9 =>
            LOADED <= '0';
            S <= '1';
            register_output <= regs(9);
        when r10 =>
            LOADED <= '0';
            S <= '1';
            register_output <= regs(10);
        when r11 =>
            LOADED <= '0';
            S <= '1';
            register_output <= regs(11);
        when r12 =>
            LOADED <= '0';
            S <= '1';
            register_output <= regs(12);

    end case;
end process;

next_state : process(shift_start, load_enable, reset, state) 
begin 
    case state is
        when initial =>  
            if(load_enable = '1') then 
                regs <= sw;
                state_next <= load;
            else 
                state_next <= initial;
            end if;
        when load =>
            if(shift_start = '1') then 
                state_next <= r1;
            else 
                state_next <= load;
            end if;
        when r1 => 
            if(reset = '1') then 
                state_next <= initial;
            else 
                state_next <= r2;
            end if;
        when r2 => 
            if(reset = '1') then 
                state_next <= initial;
            
            else 
                state_next <= r3;
            end if;
        when r3 => 
            if(reset = '1') then 
                state_next <= initial;
          
            else 
                state_next <= r4;
            end if;
        when r4 => 
            if(reset = '1') then 
                state_next <= initial;
          
            else 
                state_next <= r5;
            end if;
        when r5 => 
            if(reset = '1') then 
                state_next <= initial;
           
            else 
                state_next <= r6;
            end if;
        when r6 => 
           if(reset = '1') then 
                state_next <= initial;
            
            else 
                state_next <= r7;
            end if;
        when r7 => 
            if(reset = '1') then 
                state_next <= initial;
           
            else 
                state_next <= r8;
            end if;
        when r8 => 
            if(reset = '1') then 
                state_next <= initial;
        
            else 
                state_next <= r9;
            end if;
        when r9 => 
            if(reset = '1') then 
                state_next <= initial;
       
            else 
                state_next <= r10;
            end if;
        when r10 => 
            if(reset = '1') then 
                state_next <= initial;
           
            else 
                state_next <= r11;
            end if;
        when r11 => 
            if(reset = '1') then 
                state_next <= initial;
       
            else 
                state_next <= r12;
            end if;
        when r12 =>
            state_next <= initial;

    end case;
end process;

end Behavioral;
