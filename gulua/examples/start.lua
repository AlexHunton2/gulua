function dump(o)
   if type(o) == 'table' then
      local s = '{ '
      for k,v in pairs(o) do
         if type(k) ~= 'number' then k = '"'..k..'"' end
         s = s .. '['..k..'] = ' .. dump(v) .. ','
      end
      return s .. '} '
   else
      return tostring(o)
   end
end

function f(x, y)
	local z = x * y
	return z
end

local triangle2 = entitylib.create_triangle({100, 100, 200, 200, 100, 200})

local vertices = triangle2:get_verticies()
vertices[1] = 600
triangle2:set_verticies(vertices)
print(dump(triangle2:get_verticies()))
