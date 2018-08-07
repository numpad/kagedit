
local seconds = 0

player.events:add('on_update',
	function (dt)
		seconds = seconds + dt
		if seconds > 0.35 then
			seconds = 0
			items:add(ItemGun.new(
				player.pos - player.vel:normalize() * 10
			))
		end
	end
)
