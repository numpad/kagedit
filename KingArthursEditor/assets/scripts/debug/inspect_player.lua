
player.events:add('on_update',
	function (dt)
		imgui.TextUnformatted('Name: ' .. player.name)
		imgui.TextUnformatted('Pos: ' .. player.pos)
		imgui.SameLine()
		if imgui.Button('Reset') then player.pos = camera.pos end
		imgui.TextUnformatted('Vel: ' .. player.vel .. ' (' .. player.vel:length() .. ')')
		imgui.TextUnformatted('Acc: ' .. player.acc .. ' (' .. player.acc:length() .. ')')
	end
)

