
local function closest()
	local c = nil

	for _, i in pairs(world.items) do
		if c == nil or (i.pos - player.pos):length() < (c.pos - player.pos):length() then
			c = i
		end
	end

	return c
end


player.events:add('on_update',
	function (dt)
		local i = closest()
		if i == nil then return end

		local dir = (i.pos - player.pos):normalize()
		player.acc = dir * 0.75
		player:setViewDirection(player.vel)
	end
)

