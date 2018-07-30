-- Change drag by scrolling

local player = __pointers__.toEntity(__pointers__.entities:at(1))
local drag = 0.9;

function on_mousescroll(d)
	drag = drag + 0.0125 * d;
	print('player.drag = ' .. drag)
	player:setDrag(drag)
end
