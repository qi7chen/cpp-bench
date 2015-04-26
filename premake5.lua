--
-- Premake script (http://premake.github.io)
--

solution 'cpp-bench'
    configurations {'Debug', 'Release'}
    language 'C++'
    --flags {'ExtraWarnings'}
    targetdir 'bin'
    platforms {'x32','x64'}

    configuration 'Debug'
        defines { 'DEBUG' }
        flags { 'Symbols' }

    configuration 'Release'
        defines { 'NDEBUG' }
        flags { 'Symbols', 'Optimize' }

    configuration 'vs*'
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
    configuration 'gmake'
        buildoptions '-std=c++11'
        defines
        {
            '__STDC_LIMIT_MACROS',
        }
        links 'rt'
        
    project 'benchmark_itoa'
        location 'build'
        kind 'ConsoleApp'
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
