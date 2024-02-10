local triangle1 = entitylib.create_triangle({200, 200, 300, 300, 200, 300})

function h(key)
   -- up
   if (string.char(key) == 'w') then
      entitylib.delete_triangle(triangle1)
   end
end

hooklib.register_hook("movement", "KeyPress", h)