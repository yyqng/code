-- 13Debug.lua �ļ�

mytable = {"apple", "orange", "banana"}
print(collectgarbage("count"))           --���� Lua ʹ�õ����ڴ���( KB )
mytable = nil
print(collectgarbage("count"))
print(collectgarbage("collect"))         --��һ�������������ռ�ѭ����ͨ������ opt ���ṩ��һ�鲻ͬ�Ĺ���
print(collectgarbage("count"))