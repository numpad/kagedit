-- loads all startup scripts

scripts = list_files('scripts/onload/') -- path relative to './assets/'

for i = 1, #scripts do
	dofile('assets/scripts/onload/' .. scripts[i])
end

print('Loaded ' .. #scripts .. ' script(s)!')
