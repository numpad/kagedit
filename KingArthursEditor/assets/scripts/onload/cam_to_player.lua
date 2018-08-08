-- Camera follows player

__pointers__.events:add('on_load',
	function ()
		player.events:add('on_update',
			function (dt)
				camera.pos = player.pos
			end
		)
	end
)
