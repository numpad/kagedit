
local e = Player.new(vec2.new(10))
local c = KeyboardController.new(e)
c:map('left', 'Left')
c:map('right', 'Right')
c:map('up', 'Up')
c:map('down', 'Down')
e:setController(c)
world:spawnEntity(e)

