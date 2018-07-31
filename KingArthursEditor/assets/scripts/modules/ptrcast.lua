-- cast lua userdata to type
local M = {}

for name, func in pairs(__pointers__.typecast) do
	M[name] = func
end

return M
