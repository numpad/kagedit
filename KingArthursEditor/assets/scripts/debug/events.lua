-- event callbacks example

function on_joystickconnection(id, connected)
	if connected then
		print('Connected joystick #' .. id)
	else
		print('Removed joystick #' .. id)
	end
end

function on_mousefocuschange(gained_focus)
	if gained_focus then
		print('hello, cursor!')
	else
		print('bye, cursor...')
	end
end

function on_mousemove(x, y)
	print('Mouse move to ' .. vec2.new(x, y))
end

function on_mousebutton(x, y, button, pressed)
	print(button .. ' ' .. (pressed and 'press' or 'release') .. ' at ' .. vec2.new(x, y))
end

function on_mousescroll(delta, vertical)
	print('Scroll: ' .. delta .. ' vertical: ' .. tostring(vertical))
end

function on_focuschange(gained_focus)
	if gained_focus then
		print('hello, focus!')
	else
		print('bye, focus...')
	end
end

function on_resize(width, height)
	print('New window size: ' .. vec2.new(width, height))
end

function on_close()
	print('Window will close now...')
end
