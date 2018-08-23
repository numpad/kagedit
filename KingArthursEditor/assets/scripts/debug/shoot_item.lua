
spread = 10
strength = 15
extra_strength = 6
recoil = 2.25

local function on_mousebutton(x, y, button, pressed)
	if pressed and button == 'left' then
		local mp = world.camera:toWorldspace(vec2.new(x, y))
		local dir = mp - player.pos

		local item = ItemGun.new(player.pos + dir:normalize() * 50)
		item.acc = dir:normalize():rotate((math.random() * spread - (spread * 0.5)) * (2 * 3.1415926 / 360.0)) * (strength + math.random(extra_strength))
		player.acc = player.acc - item.acc:normalize() * recoil
		world:spawnItem(item)
	end
end

local function do_times(x, y, b, p)
	local t = math.random(4) + 2
	for i=1, t do
		on_mousebutton(x, y, b, p)
	end
end

events:set('on_mousebutton', do_times)
