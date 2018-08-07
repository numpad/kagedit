function on_mousebutton(x, y, btn, pressed)
	if pressed then return end
	
	local items = __pointers__.items
	local player = __pointers__.entities:at(1)
	local d_min = 9999
	local d_i = 0

	for i=1,#items do
	  local d = player:distanceTo(items:at(i))
	  
	  if d < d_min then
		d_min = d
		d_i = i
	  end
	end

	local nearest = items:at(d_i)
	player.acc = (nearest.pos - player.pos) * 0.05
end
