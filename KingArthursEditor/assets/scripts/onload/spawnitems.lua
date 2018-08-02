-- spawns a few test items

local function inrect(center, size)
	local rad = size * 0.5
	local vec = vec2.new(math.random(size.x) - rad.x, math.random(size.y) - rad.y)
	return center + vec
end

positions = {
	vec2.new(400, 300),
	vec2.new(400, 350),
	vec2.new(400, 400)
}

for i=1,#positions do
	local v = positions[i]
	local item = ItemGun.new(v)
	item.name = "entity_item$"
	items:add(item)
end

