local point1 = point.new(100, 100)
point1.x = 200
print(point1)
print(tabledump(getmetatable(point)))
print(point(300, 400).x)