
local vec2x = require('vec2_util')

spread = 18
strength = 18
extra_strength = 9
recoil = 1.78
count_min = 7
count_max = 12

local function on_mousebutton(x, y, button, pressed)
	if pressed and button == 'left' then
		local mp = world.camera:toWorldspace(vec2.new(x, y))
		local dir = mp - player.pos

		local item = ItemGun.new(player.pos + dir:normalize() * 50)
		item.acc = dir:normalize():rotate((math.random() * spread - (spread * 0.5)) * (2 * 3.1415926 / 360.0)) * (strength + math.random(extra_strength))
		player.acc = player.acc - item.acc:normalize() * recoil
		
		item.events:set('on_collected',
			function (by_entity)
				by_entity.acc = vec2x.random() * (5 + math.random() * 15)
			end
		)

		world:spawnItem(item)
	end
end

local function do_times(x, y, b, p)
	local t = math.random(count_min, count_max)
	for i=1, t do
		on_mousebutton(x, y, b, p)
	end
end

events:set('on_mousebutton', do_times)
