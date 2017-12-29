project('mCc', 'c',
    default_options: [
        'buildtype=release',
        'c_std=c11',
        'cpp_std=c++14',
        'warning_level=2'
    ]
)

# ------------------------------------------------------------------ GENERATORS

flex = find_program('flex')
lgen = generator(flex,
                 output: ['@BASENAME@.c', '@BASENAME@.h'],
                 arguments: [ '--outfile=@OUTPUT0@',
                              '--header-file=@OUTPUT1@',
                              '@INPUT@' ])

bison = find_program('bison')
pgen = generator(bison,
                 output: ['@BASENAME@.tab.c', '@BASENAME@.tab.h'],
                 arguments: [ '-Wall',
                              '--output=@OUTPUT0@',
                              '--defines=@OUTPUT1@',
                              '@INPUT@' ])

# ------------------------------------------------------------------------ MAIN

mCc_inc = include_directories('include')

mCc_src = [ 'src/ast.c',
            lgen.process('src/scanner.l'),
            pgen.process('src/parser.y') ]

mCc_lib = library('mCc', mCc_src,
                  c_args: '-D_POSIX_SOURCE',
                  include_directories: mCc_inc)

mCc_exe = executable('mCc', 'src/bin/mCc.c',
                     include_directories: mCc_inc,
                     link_with: mCc_lib)

# ------------------------------------------------------------------ UNIT TESTS

gtest = dependency('gtest', fallback: ['gtest', 'gtest_main_dep'])

mCc_uts = [ 'ast_test' ]

foreach ut : mCc_uts
    t = executable('ut_' + ut.underscorify(), 'test/' + ut + '.cpp',
                   include_directories: mCc_inc,
                   link_with: mCc_lib,
                   dependencies: gtest)
    test(ut, t)
endforeach
