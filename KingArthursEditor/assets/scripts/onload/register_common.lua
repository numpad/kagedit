-- register common functions / variables
local cast = require('ptrcast')

function entities_count() return #__pointers__.entities end
function get_entity(i)
	return cast.toEntity(__pointers__.entities:at(1))
end

function items_count() return #__pointers__.items end
function get_item(i)
	return cast.toEntity(__pointers__.items:at(1))
end
