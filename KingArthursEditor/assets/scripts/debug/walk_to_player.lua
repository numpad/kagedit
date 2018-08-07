
player.events:add('updatephysics',
  function ()
	local run = input.getMouseButton('right')
    local mp = input.getMousePosition()
    local speed = run and 3.25 or 0
    
    local dir = mp - player.pos
    dir = dir:normalize()
    player.pos = player.pos + dir * speed
  end
)
