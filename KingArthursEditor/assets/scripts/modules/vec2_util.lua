
-- collection of additional vec2 utility functions

---- Documentation ----
--[[
usage:
	local vec2x = require('vec2_util')

	local rand_dir = vec2x.random() -- Returns a random direction vector with length 1.
]]

local M = {}

M.random = function ()
	local random_angle = math.random() * 2 * math.pi
	return vec2.new(
		math.cos(random_angle),
		math.sin(random_angle)
	)
end

M.clamp = function (vec, min_len, max_len)
	local len = vec2.length(vec)
	
	if len < min_len then
		len = min_len
	elseif len > max_len then
		len = max_len
	end
	
	return vec:normalize() * len
end

return M
