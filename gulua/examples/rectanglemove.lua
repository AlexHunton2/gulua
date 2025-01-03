-- rectanglemove.lua
-- Examples demostrates: creating a objects (square, movable rectangle, triangle),
-- coloring, and ordering of objects (newest object are on the front)

local rectangle2 = entitylib.create("Rectangle")
rectangle2:set_position(Point(500, 500))
rectangle2:set_height(100)
rectangle2:set_width(100)

local rectangle1 = entitylib.create("Rectangle")
rectangle1:set_position(Point(200, 200))
rectangle1:set_color(Color(255, 218, 76, 80))
rectangle1:set_height(100)
rectangle1:set_width(200)
rectangle1:set_text("kill kai")
rectangle1:set_textcolor(Color(255, 0, 0, 100))

local triangle = entitylib.create("Triangle")
triangle:set_vertices(Point(100, 100), Point(200, 200), Point(100, 200))
triangle:set_color(Color(255, 0, 0, 80))

function h(key)
	local speed = 20

	local position = rectangle1:get_position()

	-- up
	if string.char(key) == "w" then
		position.y = position.y - speed
	end

	-- down
	if string.char(key) == "s" then
		position.y = position.y + speed
	end

	-- left
	if string.char(key) == "a" then
		position.x = position.x - speed
	end

	-- right
	if string.char(key) == "d" then
		position.x = position.x + speed
	end

	-- delete
	if string.char(key) == "l" then
		entitylib.delete(rectangle1)
		return
	end

	local color = rectangle1:get_color()

	-- more blue
	if string.char(key) == "i" then
		color.b = color.b + 10
	end

	-- less blue
	if string.char(key) == "k" then
		color.b = color.b - 10
	end

	rectangle1:set_color(color)
	rectangle1:set_position(position)
end

hooklib.register_hook("movement", "KeyPress", h)
