db_sources = ['base.c', 'persist.c']
db_lib = static_library('lasoora', db_sources)

base_test = executable('base_test', 'base_test.c', link_with: db_lib)
test('base_test', base_test) 

persist_test = executable('persist_test', 'persist_test.c', link_with: db_lib)
test('persist_test', persist_test)


