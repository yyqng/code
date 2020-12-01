# Introspection
examine something, typically an object, at runtime.

## dir()


```python
dir(object)
```




    ['__class__',
     '__delattr__',
     '__dir__',
     '__doc__',
     '__eq__',
     '__format__',
     '__ge__',
     '__getattribute__',
     '__gt__',
     '__hash__',
     '__init__',
     '__init_subclass__',
     '__le__',
     '__lt__',
     '__ne__',
     '__new__',
     '__reduce__',
     '__reduce_ex__',
     '__repr__',
     '__setattr__',
     '__sizeof__',
     '__str__',
     '__subclasshook__']



## type checking


```python
type(int)
```




    type




```python
int.__class__
```




    type




```python
isinstance(4, int)
```




    True




```python
issubclass(int, object)
```




    True



## inspect


```python
import inspect
inspect.isclass(int)
```




    True




```python
def foo():
    '''foo comments'''
    pass
inspect.getsource(foo)
```




    "def foo():\n    '''foo comments'''\n    pass\n"




```python
[attr for attr in dir(inspect) if attr.startswith('is')]
```




    ['isabstract',
     'isasyncgen',
     'isasyncgenfunction',
     'isawaitable',
     'isbuiltin',
     'isclass',
     'iscode',
     'iscoroutine',
     'iscoroutinefunction',
     'isdatadescriptor',
     'isframe',
     'isfunction',
     'isgenerator',
     'isgeneratorfunction',
     'isgetsetdescriptor',
     'ismemberdescriptor',
     'ismethod',
     'ismethoddescriptor',
     'ismodule',
     'isroutine',
     'istraceback']




```python
[attr for attr in dir(inspect) if attr.startswith('get')]
```




    ['getabsfile',
     'getargs',
     'getargspec',
     'getargvalues',
     'getattr_static',
     'getblock',
     'getcallargs',
     'getclasstree',
     'getclosurevars',
     'getcomments',
     'getcoroutinelocals',
     'getcoroutinestate',
     'getdoc',
     'getfile',
     'getframeinfo',
     'getfullargspec',
     'getgeneratorlocals',
     'getgeneratorstate',
     'getinnerframes',
     'getlineno',
     'getmembers',
     'getmodule',
     'getmodulename',
     'getmro',
     'getouterframes',
     'getsource',
     'getsourcefile',
     'getsourcelines']



# Reflection

string -> object

## setting attributes dynamically


```python
import os
os.environ
class Env(object):
    pass
for k, v in os.environ.items():
    setattr(Env, k, v)
dir(Env)
```




    ['ALLUSERSPROFILE',
     'APPDATA',
     'CLICOLOR',
     'COMMONPROGRAMFILES',
     'COMMONPROGRAMFILES(X86)',
     'COMMONPROGRAMW6432',
     'COMPUTERNAME',
     'COMSPEC',
     'CONDA_DEFAULT_ENV',
     'CONDA_EXE',
     'CONDA_PREFIX',
     'CONDA_PROMPT_MODIFIER',
     'CONDA_PYTHON_EXE',
     'CONDA_ROOT',
     'CONDA_SHLVL',
     'DRIVERDATA',
     'FPS_BROWSER_APP_PROFILE_STRING',
     'FPS_BROWSER_USER_PROFILE_STRING',
     'GIT_PAGER',
     'HOMEDRIVE',
     'HOMEPATH',
     'HOMESHARE',
     'IPY_INTERRUPT_EVENT',
     'IWBPATH',
     'JPY_INTERRUPT_EVENT',
     'JPY_PARENT_PID',
     'KERNEL_LAUNCH_TIMEOUT',
     'LOCALAPPDATA',
     'LOGONSERVER',
     'MPLBACKEND',
     'NUMBER_OF_PROCESSORS',
     'ONEDRIVE',
     'OS',
     'PAGER',
     'PATH',
     'PATHEXT',
     'PROCESSOR_ARCHITECTURE',
     'PROCESSOR_IDENTIFIER',
     'PROCESSOR_LEVEL',
     'PROCESSOR_REVISION',
     'PROGRAMDATA',
     'PROGRAMFILES',
     'PROGRAMFILES(X86)',
     'PROGRAMW6432',
     'PROMPT',
     'PSMODULEPATH',
     'PUBLIC',
     'PYTHONPATH',
     'SESSIONNAME',
     'SYSTEMDRIVE',
     'SYSTEMROOT',
     'TEMP',
     'TERM',
     'TMP',
     'UATDATA',
     'USERDNSDOMAIN',
     'USERDOMAIN',
     'USERDOMAIN_ROAMINGPROFILE',
     'USERNAME',
     'USERPROFILE',
     'WINDIR',
     '_JAVA_OPTIONS',
     '_JPI_VM_OPTIONS',
     '__class__',
     '__delattr__',
     '__dict__',
     '__dir__',
     '__doc__',
     '__eq__',
     '__format__',
     '__ge__',
     '__getattribute__',
     '__gt__',
     '__hash__',
     '__init__',
     '__init_subclass__',
     '__le__',
     '__lt__',
     '__module__',
     '__ne__',
     '__new__',
     '__reduce__',
     '__reduce_ex__',
     '__repr__',
     '__setattr__',
     '__sizeof__',
     '__str__',
     '__subclasshook__',
     '__weakref__']



### setting a normal method


```python
setattr(Env, 'foo', lambda cls, msg: print(msg))
Env.foo(Env, 'hello')
```

    hello
    

### setting class,instance method


```python
import types
foo1 = lambda cls, msg: print(msg)

env = Env()
env.foo1 = types.MethodType(foo1, env)
env.foo1('from foo1')

Env.foo2 = types.MethodType(foo1, env)
Env.foo2('from foo2')
```

    from foo1
    from foo2
    

## getattr


```python
def handle(action, args):
    env = Env()
    if hasattr(env, action):
        return getattr(env, action)(args)
    else:
        raise Exception('no {} handler')
```


```python
handle('foo2', 'hi')
handle('foo3', 'hi')
```

    hi
    


    ---------------------------------------------------------------------------

    Exception                                 Traceback (most recent call last)

    <ipython-input-47-417741df1b5f> in <module>
          1 handle('foo2', 'hi')
    ----> 2 handle('foo3', 'hi')
    

    <ipython-input-45-c1c59e7a7dd9> in handle(action, args)
          4         return getattr(env, action)(args)
          5     else:
    ----> 6         raise Exception('no {} handler')
    

    Exception: no {} handler


## \_\_getattr\_\_

An RPC agent demo
```python
class DbClient(object):
    def __init__(self, serve_port_no):
        self._serve_port_no = serve_port_no

    def connect(self, db_port=None):
        self.stub = ServerProxy('http://localhost:{}'.format(self._serve_port_no))
        self._update_real_db_data()
        return self.stub

    def _update_real_db_data(self):
        """ update data members like: mPlaceholder, is_sqlite, mCurrentTimestamp, ...  """
        real_db_members = self.stub.member_values()
        self.__dict__.update(real_db_members)

    def __getattr__(self, item):
        try:
            if hasattr(self.stub, item):
                return getattr(self.stub, item)
            else:
                sys.stderr.write('==DbClient cannot find item:{}\n'.format(item))
        except Exception as e:
            sys.stderr.write('==DbClient get attr error:{}\n'.format(item))
```

# Summary
Introspection is passive, the purpose is to examine; Reflection is active, and it’s not only able examine, but also to modify at runtime.

# Refer
- https://www.geeksforgeeks.org/reflection-in-python/
- https://www.bnmetrics.com/blog/introspection-reflection-in-python#:~:text=%20Introspection%3A%20Reflection%20in%20Python%20%201%20Introspection.,are%20very%20powerful%20concepts%2C%20and%20Python...%20More%20
