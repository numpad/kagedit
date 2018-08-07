
local function update(dt)
	local t = input.getMousePosition()
	local dir = t - player.pos
	
	local forward = dir:normalize()
	local sideways = vec2.new(dir.y, -dir.x):normalize()
	local ws = -player.acc.y
	local ad = -player.acc.x
	
	player.acc = vec2.new(0, 0)
	player.acc = player.acc + forward * ws
	player.acc = player.acc + sideways * ad
	player.vel = player.vel + player.acc
	player.pos = player.pos + player.vel
	player.vel = player.vel * 0.9
	player.acc = vec2.new(0, 0)
end

player.events:set('updatephysics', update)
