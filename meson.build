project('Pong', 'c', default_options: ['warning_level=everything'])

incdir = include_directories('src', 'src/core')
src = ['src/main.c', 'src/core/move.c', 'src/core/input.c', 'src/core/render.c', 'src/core/tick.c']
sdl3_dep = dependency('sdl3')

executable('pong', src, include_directories : incdir, dependencies: sdl3_dep)
