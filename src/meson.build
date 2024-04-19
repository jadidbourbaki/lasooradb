db_sources = ['base.c']
db_lib = static_library('liblasoora', db_sources)

base_test = executable('base_test', 'base_test.c', link_with: db_lib)
test('base_test', base_test) 


