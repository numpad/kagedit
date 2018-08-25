
function spawnPlayer(pos)
	local e = Player.new(pos)

	local c = KeyboardController.new(e)
	c:map('left', 'Left')
	c:map('right', 'Right')
	c:map('up', 'Up')
	c:map('down', 'Down')

	e:setController(c)

	e.events:set('on_update',
		function (dt)
			e:setViewDirection(e.vel)
		end
	)

	world:spawnEntity(e)
end

local random_off = vec2.new(
	math.random() * 2 - 1,
	math.random() * 2 - 1
)
random_off = random_off:normalize() * math.random(20, 50)

spawnPlayer(player.pos + random_off)
