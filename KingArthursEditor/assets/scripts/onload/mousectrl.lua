
local lastpos = nil

events:add('on_mousebutton',
	function (x, y, btn, press)
		if press and btn == 'right' and not lastpos then
			lastpos = vec2.new(x, y)
		else
			lastpos = nil
		end
	end
)

events:add('on_mousemove',
	function (x, y)
		if lastpos then
			local d = lastpos - vec2.new(x, y)
			camera:move(d)
			lastpos = vec2.new(x, y)
		end
	end
)

