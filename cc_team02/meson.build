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
mCc_test_inc = include_directories('test/include')


mCc_ast_src = ['src/ast/basis/ast_assignment.c','src/ast/basis/ast_declaration.c','src/ast/basis/ast_expression.c','src/ast/basis/ast_function.c',
'src/ast/basis/ast_identifier.c','src/ast/basis/ast_literal.c','src/ast/basis/ast_program.c','src/ast/basis/ast_statement.c' ]


mCc_visit_src = ['src/ast/visit/ast_visit_assignment.c',
'src/ast/visit/ast_visit_declaration.c',
'src/ast/visit/ast_visit_expression.c',
'src/ast/visit/ast_visit_function.c',							
'src/ast/visit/ast_visit_identifier.c',							
'src/ast/visit/ast_visit_literal.c',
'src/ast/visit/ast_visit_program.c',
'src/ast/visit/ast_visit_statement.c']


mCc_print_src = ['src/ast/print/ast_basic_printing.c',
'src/ast/print/ast_print.c', 
'src/ast/print/ast_print_assignment.c',
'src/ast/print/ast_print_declaration.c', 
'src/ast/print/ast_print_expression.c',
'src/ast/print/ast_print_function.c',							
'src/ast/print/ast_print_identifier.c',							
'src/ast/print/ast_print_literal.c',
'src/ast/print/ast_print_program.c',
'src/ast/print/ast_print_statement.c']

# test utils
mCc_test_src = ['test/bin/mCc_test_utils.c']


mCc_lib = library('mCc', mCc_ast_src, mCc_visit_src, mCc_print_src, lgen.process('src/scanner.l'),
            pgen.process('src/parser.y'),
                  c_args: '-D_POSIX_C_SOURCE=200809L',
                  include_directories: mCc_inc)

# test utils
mCc_test_lib = library('mCc_test', mCc_test_src,
                  include_directories: [mCc_inc,mCc_test_inc],
                  link_with: mCc_lib)

# ----------------------------------------------------------------- EXECUTABLES

mCc_exes = [ 'mCc', 'mC_to_dot' ]

foreach exe : mCc_exes
    executable(exe, 'src/bin/' + exe + '.c',
               include_directories: mCc_inc,
               link_with: mCc_lib)
endforeach

# ------------------------------------------------------------------ UNIT TESTS

gtest = dependency('gtest', fallback: ['gtest', 'gtest_main_dep'])

mCc_uts = [ 'parser','builder','printer' ]

foreach ut : mCc_uts
    t = executable('ut_' + ut.underscorify(), 'test/' + ut + '.cpp',
                   include_directories: [mCc_inc, mCc_test_inc],
                   link_with: [mCc_lib, mCc_test_lib],
                   dependencies: gtest)

    test(ut, t)
endforeach

# -------------------------------------------------------------------- INTEGRATION TESTS

integration = run_target('integration_test',
  command : ['test/meson_integration_target',meson.current_build_dir()])

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

# --------------------------------------------------------------------- DOXYGEN

doxygen = find_program('doxygen', required: false)

if doxygen.found()
        doxyconf = configuration_data()
        doxyconf.set('ROOT', meson.source_root())
        doxyconf.set('BUILDDIR', meson.build_root())

        doxyfile = configure_file(input: '.doxyfile',
                                  output: 'doxyfile',
                                  configuration: doxyconf)

        html_doc = run_target('doc', command: [doxygen, doxyfile])
endif
