db_sources = ['base.c', 'persist.c']
db_lib = static_library('lasoora', db_sources)

base_test = executable('base_test', 'base_test.c', link_with: db_lib)
test('base_test', base_test) 

persist_test = executable('persist_test', 'persist_test.c', link_with: db_lib)
test('persist_test', persist_test)

stress = executable('stress', 'stress.c', link_with: db_lib)
test('stress', stress)

db_main = executable('db', 'db.c', link_with: db_lib)


