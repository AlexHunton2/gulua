--[[
   tabledump.lua

   Utility functions for printing out table
   Found here: https://stackoverflow.com/questions/9168058/how-to-dump-a-table-to-console
   Original Author is unknown.
]]--
function tabledump(o)
   if type(o) == 'table' then
      local s = '{ '
      for k,v in pairs(o) do
         if type(k) ~= 'number' then k = '"'..k..'"' end
         s = s .. '['..k..'] = ' .. tabledump(v) .. ','
      end
      return s .. '} '
   else
      return tostring(o)
   end
end