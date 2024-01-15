
x_dep = dependency('x11')
sdl3_dep = dependency('sdl3')
thread_dep = dependency('threads')

executable('copy','main.cpp', include_directories : inc,
dependencies : [
    sdl3_dep,
    x_dep,
    thread_dep,
],
cpp_args : ['-Og'],

install : true,
)