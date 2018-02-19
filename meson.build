project('mCc', 'c',
    default_options: [
        'buildtype=release',
        'c_std=c11',
        'cpp_std=c++14',
        'warning_level=2'
    ],
    meson_version: '>=0.44.0'
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

# --------------------------------------------------------------------- LIBRARY

mCc_inc = include_directories('include')

mCc_src = [ 'src/ast.c',
            'src/ast_print.c',
            'src/ast_visit.c',
            lgen.process('src/scanner.l'),
            pgen.process('src/parser.y') ]

mCc_lib = library('mCc', mCc_src,
                  c_args: '-D_POSIX_C_SOURCE=200809L',
                  include_directories: mCc_inc)

# ----------------------------------------------------------------- EXECUTABLES

mCc_exes = [ 'mCc', 'mC_to_dot' ]

foreach exe : mCc_exes
    executable(exe, 'src/bin/' + exe + '.c',
               include_directories: mCc_inc,
               link_with: mCc_lib)
endforeach

# ------------------------------------------------------------------ UNIT TESTS

gtest = dependency('gtest', fallback: ['gtest', 'gtest_main_dep'])

mCc_uts = [ 'parser' ]

foreach ut : mCc_uts
    t = executable('ut_' + ut.underscorify(), 'test/' + ut + '.cpp',
                   include_directories: mCc_inc,
                   link_with: mCc_lib,
                   dependencies: gtest)

    test(ut, t)
endforeach

# ------------------------------------------------------------------ BENCHMARKS

mCc_benchs = [ ['parser/binary_op',         '100000'],
               ['parser/nested_expression', '100000'] ]

foreach bench : mCc_benchs
    name = bench[0]
    reps = bench[1]

    b = executable('bench_' + name.underscorify(), 'benchmark/' + name + '.c',
                   include_directories: mCc_inc,
                   link_with: mCc_lib)

    benchmark(name + ': ' + reps, b, args: [reps])
endforeach
