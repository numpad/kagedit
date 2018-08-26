-- Collection of utils for loading maps exported from tiled
local M = {}

-- .get_spawnpoints
-- .spawn_object

-- Generated spawnpoints for a spawner
M.get_spawnpoints = function (object)
	local count = object.properties.count or 1
	
	-- result
	local points = {}

	if object.shape == 'point' then
		for i=1, count do
			points[#points + 1] = vec2.new(object.x, object.y)
		end
	elseif object.shape == 'rectangle' then
		for i=1, count do
			local px = object.x + math.random() * object.width
			local py = object.y + math.random() * object.height
			points[#points + 1] = vec2.new(px, py)
		end
	elseif object.shape == 'ellipse' then
		for i=1, count do
			local rx = object.width * 0.5
			local ry = object.height * 0.5
			local cx = object.x + rx
			local cy = object.y + ry
			
			local angle = math.random() * 2 * math.pi
			local r = math.random()
			local rw = rx * math.sqrt(r)
			local rh = ry * math.sqrt(r)
			points[#points + 1] = vec2.new(
				cx + rw * math.cos(angle),
				cy + rh * math.sin(angle)
			)
		end
	end

	return points
end

-- Spawn an object
M.spawn_object = function (object)
	local spawn_points = M.get_spawnpoints(object)
	for _, p in pairs(spawn_points) do
		local entity = _G[object.properties.entity].new(p)
		
		if object.properties.entity == 'Player' then player = entity end
		
		if object.properties.entity_type == 'item' then
			world:spawnItem(entity)
		else
			world:spawnEntity(entity)
		end
	end
end

return M

