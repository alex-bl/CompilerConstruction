project('mCc',
    'c',
    default_options: [
        'buildtype=release',
        'cpp_std=c11',
        'warning_level=2'
    ]
)

# -----------------------------------------------------------------------------

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

# -----------------------------------------------------------------------------

mCc_inc = include_directories('include')

mCc_src = [ 'src/ast.c',
            lgen.process('src/scanner.l'),
            pgen.process('src/parser.y') ]

mCc_lib = library('mCc', mCc_src,
                  include_directories: mCc_inc)

mCc_exe = executable('mCc', 'src/bin/mCc.c',
                     include_directories: mCc_inc,
                     link_with: mCc_lib)

gtest = dependency('gtest', fallback: ['gtest', 'gtest_main_dep'])

#foo_tests = ['foo_test', 'bar/baz_test']
#foreach foo_test : foo_tests
#   t = executable('ut_' + foo_test.underscorify(), 'test/' + foo_test + '.cpp',
#       include_directories: foo_inc,
#       link_with: foo_lib,
#       dependencies: gtest
#   )
#   test(foo_test, t)
#endforeach
