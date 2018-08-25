
local function closest()
	local c = nil

	for j = 1, #world.items do
		local i = world.items[j]
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

