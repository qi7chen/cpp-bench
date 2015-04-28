--
-- Premake script (http://premake.github.io)
--

solution 'cpp-bench'
    configurations  {'Debug', 'Release'}
    language        'C++'
    flags           'ExtraWarnings'
    targetdir       'bin'

    filter 'configurations:Debug'
        defines     { 'DEBUG' }
        flags       { 'Symbols' }

    filter 'configurations:Release'
        defines     { 'NDEBUG' }
        flags       { 'Symbols' }
        optimize    'On'

    filter 'action:vs*'
        defines
        {
            'WIN32',
            'WIN32_LEAN_AND_MEAN',
            '_WIN32_WINNT=0x0600',
            '_CRT_SECURE_NO_WARNINGS',
            '_SCL_SECURE_NO_WARNINGS',
            '_WINSOCK_DEPRECATED_NO_WARNINGS',
            'NOMINMAX',
        }

    filter 'action:gmake'
        buildoptions    '-std=c++11'
        defines         '__STDC_LIMIT_MACROS'

    filter 'system:linux'
        links   'rt'

    project 'benchmark_itoa'
        targetname  'benchmark_itoa'
        location    'build'
        kind        'ConsoleApp'
        files
        {
            'src/*.h',
            'src/*.cpp',
            'test/*.h',
            'test/*.cpp',
        }
        includedirs
        {
            'src',
        }
