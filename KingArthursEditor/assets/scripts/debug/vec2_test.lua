-- testing glm::vec2 binding

v1 = vec2.new(4, 2)
v2 = vec2.new(2, 0) / 2
v3 = v1 + v2
print('Result: ' .. v3 .. ', length=' .. v3:length())
