-- spawns a few test items

positions = {
	vec2.new(400, 300),
	vec2.new(400, 350),
	vec2.new(400, 400)
}

for i=1,#positions do
	local v = positions[i]
	local item = ItemGun.new(v)
	item.name = "entity_item$"
	world:spawnItem(item)
end

