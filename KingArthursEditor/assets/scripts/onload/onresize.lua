-- fit camera size to window on resize

local function resize_camera(w, h)
	camera.size = vec2.new(w, h)
end

__pointers__.events:add('on_resize', resize_camera)

