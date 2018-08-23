
local lastpos = nil

__pointers__.events:add('on_mousebutton',
	function (x, y, btn, press)
		if press and btn == 'right' and not lastpos then
			lastpos = vec2.new(x, y)
		else
			lastpos = nil
		end
	end
)

__pointers__.events:add('on_mousemove',
	function (x, y)
		if lastpos then
			local d = lastpos - vec2.new(x, y)
			world.camera:move(d)
			lastpos = vec2.new(x, y)
		end
	end
)

