-- register common functions / variables

for k, v in pairs(__pointers__) do
	_G[k] = v
end

player = entities:at(1)

