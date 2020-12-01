import sys
from types import ModuleType

def foo(msg):
    print(msg)
    
class VerboseModule(ModuleType):
    def __repr__(self):
        return f'Verbose {self.__name__}'

    def __getattr__(self, name):
        import numpy as np
        print(f'turn to numpy.{name}')
        return getattr(np, name)

    def __dir__(self):
        return [foo]

sys.modules[__name__].__class__ = VerboseModule