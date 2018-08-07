-- entities

local entities = __pointers__.entities
local p = entities:at(1)
print('Container: ' .. tostring(entities))
print('Type: ' .. tostring(p))
print('Pos: ' .. p.pos)
p.pos = camera:getPosition()
p.vel = vec2.new(0, 0)
print('New Pos: ' .. p.pos)
