project('Pong', 'c', 
    default_options: [
    'warning_level=everything',
    'c_std=c11',
    'buildtype=minsize',
    'optimization=s',
    'debug=false',
    'b_lto=true',
    'b_vscrt=static_library',
    'default_library=static',
    'strip=true',
    'unity=on',
    'unity_size=0'
  ])

cc = meson.get_compiler('c')

if cc.get_argument_syntax() == 'gcc'
  add_project_link_arguments('-Wl,--gc-sections', language: 'c')
elif cc.get_argument_syntax() == 'msvc'
  add_project_link_arguments('/OPT:REF', language: 'c')
endif

add_project_arguments('-ffunction-sections', '-fdata-sections', '-nostdlib', '-DNDEBUG', language: 'c')

incdir = include_directories('src', 'src/core')
src = ['src/main.c', 'src/core/move.c', 'src/core/input.c', 'src/core/render.c', 'src/core/tick.c']

sdl3_dep = dependency('sdl3', static: true)

executable('pong', src, include_directories : incdir, dependencies: sdl3_dep)
