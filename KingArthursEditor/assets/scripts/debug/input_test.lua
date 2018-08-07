-- test input

pos = input.getMousePosition()
down = input.getMouseButton('right')

print('Mouse Pos: ' .. pos)
print('Down: ' .. (down and 'true' or 'false'))
