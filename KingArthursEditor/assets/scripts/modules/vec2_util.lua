
local M = {}

M.random = function()
	local random_angle = math.random() * 2 * math.pi
	return vec2.new(
		math.cos(random_angle),
		math.sin(random_angle)
	)
end 

return M
