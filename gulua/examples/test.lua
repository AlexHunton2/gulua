-- test.lua
-- Random file that used to test random things during development

local rectangle2 = entitylib.create("Rectangle")
rectangle2:set_text("Rectangle!")
rectangle2:set_position(Point(500, 500))
rectangle2:set_height(100)
rectangle2:set_width(100)

local triangle = entitylib.create("Triangle")
triangle:set_text("Triangle!")
triangle:set_vertices(Point(100, 100), Point(200, 200), Point(100, 200))
triangle:set_color(Color(120, 40, 40, 80))
