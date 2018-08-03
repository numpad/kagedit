-- testing mouse

function on_mousedown(x, y)
	-- get the mouse position as a vec2
	local pos = input.getMousePosition()
	-- get the state of a mouse button
	-- possible values: left,right,middle,x1,x2
	local buttons = {input.getMouseButton('left', 'right', 'middle')}

	print('mouse position: ' .. pos)

	for i=1,#buttons do
		print(': ' .. tostring(buttons[i]))
	end
end

