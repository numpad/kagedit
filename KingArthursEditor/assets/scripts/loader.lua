-- loads all startup scripts

-- prefer the folder 'assets/scripts/modules/' for _require()_
package.path = './assets/scripts/modules/?.lua;' .. package.path

-- print all events that have been registered on startup
__pointers__.events:add('on_start',
	function ()
		print('Registered events:')
		for _, name, count in pairs(__pointers__.events:list()) do
			print(' ' .. name .. ': ' .. count .. 'x')
		end
	end
)

-- execute all onload scripts
scripts = list_files('scripts/onload/')
for i = 1, #scripts do
	print('[loader] Loading \'' .. scripts[i] .. '\'...')
	dofile('assets/scripts/onload/' .. scripts[i])
end

print('[loader] Finished! Loaded ' .. #scripts .. ' script(s)!')

