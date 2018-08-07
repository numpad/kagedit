
local items = __pointers__.items
local entities = __pointers__.entities

for i=1,#items do
	local item = items:at(i)
	local speed = 5.0
	local dir = vec2.normalize(vec2.new(400, 300) - item.pos) * speed
	
	item.vel = dir
end
