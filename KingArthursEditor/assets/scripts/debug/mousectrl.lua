local cast = require('ptrcast')
local p = cast.toEntity(__pointers__.entities:at(1))
local lastpos = nil
local currpos = nil
local isdown = false

function on_mousemove(x, y)
	if isdown then
		local pos = vec2.new(x, y)
		if lastpos == nil then lastpos = pos end
		
		camera:move(lastpos - pos)
		
		lastpos = pos
	end
end

function on_mousebutton(x, y, btn, pressed)
	if pressed and btn == 'right' then
		local pos = vec2.new(x, y)
		p.pos = pos
		p.vel = vec2.new(0, 0)
		print('begin')
	elseif not pressed and btn == 'right' then
		local pos = vec2.new(x, y)
		p.vel = (p.pos - pos) * 0.075
		print('release')
	end
	
	if pressed and btn == 'left' then
		isdown = true
        lastpos = nil
	elseif not pressed and btn == 'left' then
		isdown = false
	end
end
