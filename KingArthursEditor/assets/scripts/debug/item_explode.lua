
local function shoot_item(pos, dir)
	local i = ItemGun.new(pos + dir:normalize() * 50)
	i.acc = dir
	world:spawnItem(i)
end

world.events:add('on_update',
	function (dt)
		if down then
			world:spawnItem(ItemGun.new(world.camera:toWorldspace(input.getMousePosition())))
		end
	end
)

events:set('on_mousebutton',
	function (x, y, btn, press)
		down = press
		mxy = vec2.new(x, y)

		if press and btn == 'middle' then
			for i=0, 359 do
				local dir = vec2.new(math.cos(i), math.sin(i))
				shoot_item(player.pos, dir * 25)
			end
		end
	end
)

