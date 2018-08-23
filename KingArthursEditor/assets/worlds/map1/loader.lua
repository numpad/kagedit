local world_data = require('Map1')

----------------------
-- useful functions --
----------------------

function get_spawnpoints(object)
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
	end

	return points
end

function spawn_object(object)
	local spawn_points = get_spawnpoints(object)
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
print('Map Version: ' .. world_data.version)

-- parse layers
for i, layer in pairs(world_data.layers) do
	if layer.type == 'tilelayer' then
		world:loadLayer(layer.data, 'assets/worlds/map1/images/tilesheet_complete.png', 64, 64, 64)
	elseif layer.type == 'objectgroup' and layer.name == 'Spawn Areas' then
		for i, object in pairs(layer.objects) do
			if object.type == 'spawner' then
				spawn_object(object)
			end
		end
	end
end

-- add world scripts
world.events:add('on_update',
	function (dt)
		world.camera.pos = player.pos
	end
)

