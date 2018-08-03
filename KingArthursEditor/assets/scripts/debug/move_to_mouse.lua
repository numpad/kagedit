
acc_speed = 0.375
drag = 0.9615
radius = 14

local points = {}
local i_next = 1

function on_mousebutton(x, y, btn, press)
	if press and btn == 'left' then
		points[#points + 1] = camera:toWorldSpace(vec2.new(x, y))
	end
end

function run_to_mouse(dt)
	if i_next > #points then
		points = {}
		i_next = 1
		player.vel = player.vel + player.acc
		player.pos = player.pos + player.vel
		player:setViewDirection(player.vel)
		player.vel = player.vel * drag
		player.acc = vec2.new(0, 0)
	end
	if #points == 0 then return end

	local p = points[i_next]
	local dir = p - player.pos
	
	player.acc = dir:normalize() * acc_speed
	player.vel = player.vel + player.acc
	player.pos = player.pos + player.vel
	player:setViewDirection(player.vel)
	player.vel = player.vel * drag
	player.acc = vec2.new(0, 0)

	if vec2.length(p - player.pos) <= radius then
		i_next = i_next + 1
	end
end

player.events:set('updatephysics', run_to_mouse)

