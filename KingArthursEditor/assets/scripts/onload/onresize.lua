-- fit camera size to window on resize

function on_resize(w, h)
	local size = vec2.new(w, h)
	camera:setSize(size)
end
