-- loads all startup scripts

__pointers__.events:add('on_start',
	function ()
		print('--- script event ---')
	end
)


package.path = './assets/scripts/modules/?.lua;' .. package.path

scripts = list_files('scripts/onload/') -- path relative to './assets/'

for i = 1, #scripts do
	dofile('assets/scripts/onload/' .. scripts[i])
end

print('Loaded ' .. #scripts .. ' script(s)!')
