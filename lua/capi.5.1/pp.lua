-- configuration file for program `pp'
-- define window size

--require "os"
--
--if os.getenv("DISPLAY") == ":0.0" then
--    width = 9000; height= 1.2e3
--else
--    width = 200; height = 200
--end

hello= "Hello from pp.lua"
print(hello)

BLUE = {r=0.1, g=0.1, b=1}
RED = {r=1, g=0.1, b=0}
background = BLUE
background = RED

function Luaf(x, y)
    return (x^2 )/(1 - y)
--    return (x^2 * math.sin(y))/(1 - x)
end
