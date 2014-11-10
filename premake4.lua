--
-- Premake4 build script (http://industriousone.com/premake/download)
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

    project 'benchmark'
        location 'build'
        kind 'ConsoleApp'
        uuid '31BC2F58-F374-4984-B490-F1F08ED02DD3'
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
        if os.get() == 'windows' then
        defines 
        {
            'WIN32',
            'WIN32_LEAN_AND_MEAN',
            '_WIN32_WINNT=0x0600',
            '_CRT_SECURE_NO_WARNINGS',
            '_SCL_SECURE_NO_WARNINGS',
            'NOMINMAX',
        }
        end
        
        if os.get() == 'linux' then
        buildoptions { '-std=c++11' }
        defines 
        { 
            '__STDC_LIMIT_MACROS',        
        }
        links
        {
            'rt',
        }
        end
        
