-- 11IO.lua �ļ�

--[[
-- ��ģʽ��
file = io.open("test.txt", "r")   -- ��ֻ����ʽ���ļ�
io.input(file)                    -- ����Ĭ�������ļ�Ϊ test.lua
print(io.read())                  -- ����ļ�ǰ����
print(io.read())
io.close(file)                    -- �رմ򿪵��ļ�


file = io.open("test.txt", "a")   -- �Ը��ӵķ�ʽ��ֻд�ļ�
io.output(file)                   -- ����Ĭ������ļ�Ϊ test.lua
io.write("Append 1\n")            -- ���ļ�����������
io.write("Append 2\n")
io.close(file)                    -- �رմ򿪵��ļ�
--]]


-- ��ȫģʽ��ͬʱ��ȡ����ļ������Ĳ�����ʹ����ȫģʽ���Ϊ����
file = io.open("test.txt", "r")   -- ��ֻ����ʽ���ļ�
print(file:read())                -- ����ļ�ǰ����
print(file:read())
file:seek("end",-28)
print(file:read("*a"))
file:close()                      -- �رմ򿪵��ļ�

file = io.open("test.txt", "a")   -- �Ը��ӵķ�ʽ��ֻд�ļ�
file:write("Append 3\n")          -- ���ļ�����������
file:write("Append 4\n")
file:close()                      -- �رմ򿪵��ļ�

