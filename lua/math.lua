local function formatTime(time)  
    local hour = math.floor(time/3600);  
    local minute = math.fmod(math.floor(time/60), 60)  
    local second = math.fmod(time, 60)  
    local rtTime = string.format("%s:%s:%s", hour, minute, second)  
    return rtTime  
end 

print("15%4 = ",math.fmod(15,4))
print("3.1%1.5 = ",math.fmod(3.1,1.5))
print("-2%3 = ",math.fmod(-2,3))
