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

local triangle1 = entitylib.create_triangle({200, 200, 300, 300, 200, 300})

function h(key)
   local speed = 10

   -- up
   local vertices = triangle1:get_vertices()
   if (string.char(key) == 'w') then
      for i=1,3 do
         vertices[i*2] = vertices[i*2] - speed
      end
   end

   -- down
   if (string.char(key) == 's') then
      for i=1,3 do
         vertices[i*2] = vertices[i*2] + speed
      end
   end

   -- left
   if (string.char(key) == 'a') then
      for i=1,3 do
         vertices[i*2-1] = vertices[i*2-1] - speed
      end
   end

   -- right
   if (string.char(key) == 'd') then
      for i=1,3 do
         vertices[i*2-1] = vertices[i*2-1] + speed
      end
   end

   triangle1:set_vertices(vertices)
end

hooklib.register_hook("movement", "KeyPress", h)