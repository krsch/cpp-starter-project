import sys
sys.path.append('./build/lib')
import cpplib
print(f'add(2,3) returns {cpplib.add(2, 3)}')
p = cpplib.Pet("123")
print(p, p.name, p.NAME)
p.NAME = 'JOE'
print(p, p.NAME)
print(cpplib.pi(), type(cpplib.pi()))
p.set('ji')
p.set(3)
print(p)