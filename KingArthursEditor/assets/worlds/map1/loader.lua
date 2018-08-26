local world_data = require('Map1')
local tiled = require('tiled_util')

print('Map Version: ' .. world_data.version)

-- parse layers
for i, layer in pairs(world_data.layers) do
	if layer.type == 'tilelayer' then
		if layer.visible then
			world:loadLayer(layer.data, 'images/tilesheet_complete.png', layer.width, layer.height, world_data.tilewidth)
		end
	elseif layer.type == 'objectgroup' then
		for i, object in pairs(layer.objects) do
			if object.type == 'spawner' then
				tiled.spawn_object(object)
			end
		end
	end
end

-- add world scripts
world.events:add('on_update',
	function (dt)
		if not draggingCamera() then
			local dir = player.pos - world.camera.pos
			dir = dir / 6
			world.camera.pos = world.camera.pos + dir * (dt * 60)
		end
	end
)

