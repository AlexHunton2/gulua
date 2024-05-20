local triangle1 = entitylib.create("Triangle")
triangle1:set_vertices(point(200, 200), point(300, 300), point(200, 300))

function h(key)
   local speed = 10

   local vertices = triangle1:get_vertices()

   -- up
   if (string.char(key) == 'w') then
       for i=1,3 do
         vertices[i].y = vertices[i].y - speed
      end
   end

   -- down
   if (string.char(key) == 's') then
      for i=1,3 do
         vertices[i].y = vertices[i].y + speed
      end
   end

   -- left
   if (string.char(key) == 'a') then
      for i=1,3 do
         vertices[i].x = vertices[i].x - speed
      end
   end

   -- right
   if (string.char(key) == 'd') then
      for i=1,3 do
         vertices[i].x = vertices[i].x + speed
      end
   end

   -- delete
   if (string.char(key) == 'l') then
      entitylib.delete(triangle1)
      return
   end

   triangle1:set_vertices(vertices)
end

hooklib.register_hook("movement", "KeyPress", h)