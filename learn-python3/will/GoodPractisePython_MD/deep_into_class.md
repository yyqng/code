<h1>Table of Contents<span class="tocSkip"></span></h1>
<div class="toc"><ul class="toc-item"><li><span><a href="#Definition" data-toc-modified-id="Definition-1"><span class="toc-item-num">1&nbsp;&nbsp;</span>Definition</a></span><ul class="toc-item"><li><span><a href="#1.MRO" data-toc-modified-id="1.MRO-1.1"><span class="toc-item-num">1.1&nbsp;&nbsp;</span>1.MRO</a></span><ul class="toc-item"><li><span><a href="#A-Demo" data-toc-modified-id="A-Demo-1.1.1"><span class="toc-item-num">1.1.1&nbsp;&nbsp;</span>A Demo</a></span></li></ul></li><li><span><a href="#2.Determining-the-appropriate-metaclass" data-toc-modified-id="2.Determining-the-appropriate-metaclass-1.2"><span class="toc-item-num">1.2&nbsp;&nbsp;</span>2.Determining the appropriate metaclass</a></span></li><li><span><a href="#3.Preparing-the-class-namespace" data-toc-modified-id="3.Preparing-the-class-namespace-1.3"><span class="toc-item-num">1.3&nbsp;&nbsp;</span>3.Preparing the class namespace</a></span></li><li><span><a href="#4.Executing-the-class-body" data-toc-modified-id="4.Executing-the-class-body-1.4"><span class="toc-item-num">1.4&nbsp;&nbsp;</span>4.Executing the class body</a></span></li><li><span><a href="#5.Creating-the-class-object" data-toc-modified-id="5.Creating-the-class-object-1.5"><span class="toc-item-num">1.5&nbsp;&nbsp;</span>5.Creating the class object</a></span></li></ul></li><li><span><a href="#Special-methods" data-toc-modified-id="Special-methods-2"><span class="toc-item-num">2&nbsp;&nbsp;</span>Special methods</a></span><ul class="toc-item"><li><span><a href="#Basic-customization" data-toc-modified-id="Basic-customization-2.1"><span class="toc-item-num">2.1&nbsp;&nbsp;</span>Basic customization</a></span></li><li><span><a href="#Customizing-attribute-access" data-toc-modified-id="Customizing-attribute-access-2.2"><span class="toc-item-num">2.2&nbsp;&nbsp;</span>Customizing attribute access</a></span></li><li><span><a href="#Emulating-callable-objects" data-toc-modified-id="Emulating-callable-objects-2.3"><span class="toc-item-num">2.3&nbsp;&nbsp;</span>Emulating callable objects</a></span></li><li><span><a href="#Emulating-container-types" data-toc-modified-id="Emulating-container-types-2.4"><span class="toc-item-num">2.4&nbsp;&nbsp;</span>Emulating container types</a></span></li><li><span><a href="#Emulating-numeric-types" data-toc-modified-id="Emulating-numeric-types-2.5"><span class="toc-item-num">2.5&nbsp;&nbsp;</span>Emulating numeric types</a></span></li><li><span><a href="#With-Statement-Context-Managers" data-toc-modified-id="With-Statement-Context-Managers-2.6"><span class="toc-item-num">2.6&nbsp;&nbsp;</span>With Statement Context Managers</a></span><ul class="toc-item"><li><span><a href="#Another-method" data-toc-modified-id="Another-method-2.6.1"><span class="toc-item-num">2.6.1&nbsp;&nbsp;</span>Another method</a></span></li></ul></li></ul></li><li><span><a href="#Magic-functions" data-toc-modified-id="Magic-functions-3"><span class="toc-item-num">3&nbsp;&nbsp;</span>Magic functions</a></span><ul class="toc-item"><li><span><a href="#__slots__" data-toc-modified-id="__slots__-3.1"><span class="toc-item-num">3.1&nbsp;&nbsp;</span>__slots__</a></span></li></ul></li><li><span><a href="#Multiple-consturctor" data-toc-modified-id="Multiple-consturctor-4"><span class="toc-item-num">4&nbsp;&nbsp;</span>Multiple consturctor</a></span></li></ul></div>

# Definition


```python
class A:
    def self_foo(self):
        pass
    @staticmethod
    def static_new():
        pass
    @classmethod
    def classmethod_new(cls):
        pass

```

When a class definition is executed, the following steps occur:
1. MRO entries are resolved;
2. the appropriate metaclass is determined;
3. the class namespace is prepared;
4. the class body is executed;
5. the class object is created.


## 1.MRO
Method Resolution Order is the order in which base classes are searched for a member during lookup. See [Python 2.3 Method Resolution Order](https://www.python.org/download/releases/2.3/mro/) for details.
### A Demo


```python
from socketserver import ThreadingMixIn
from wsgiref.simple_server import WSGIServer

class ThreadingServer(ThreadingMixIn, WSGIServer):
    pass
```


```python
class ThreadingMixIn:
    """Mix-in class to handle each request in a new thread."""

    # Decides how threads will act upon termination of the
    # main process
    daemon_threads = False

    def process_request_thread(self, request, client_address):
        """Same as in BaseServer but as a thread.

        In addition, exception handling is done here.

        """
        try:
            self.finish_request(request, client_address)
            self.shutdown_request(request)
        except:
            self.handle_error(request, client_address)
            self.shutdown_request(request)

    def process_request(self, request, client_address):
        """Start a new thread to process the request."""
        t = threading.Thread(target = self.process_request_thread,
                             args = (request, client_address))
        t.daemon = self.daemon_threads
        t.start()
```

ThreadingMinIn only have 2 methods, but calls 4 methods.


```python
list(filter(lambda attr: not attr.startswith('_'), dir(WSGIServer)))
```


```python
ThreadingServer.__mro__
```




    (__main__.ThreadingServer,
     socketserver.ThreadingMixIn,
     wsgiref.simple_server.WSGIServer,
     http.server.HTTPServer,
     socketserver.TCPServer,
     socketserver.BaseServer,
     object)



## 2.Determining the appropriate metaclass

## 3.Preparing the class namespace
- namespace = metaclass.\_\_prepare\_\_(name, bases, **kwds), should be a dict
- The namespace returned by \_\_prepare\_\_ is passed in to \_\_new\_\_, 
- but when the final class object is created the namespace is copied into a new dict.

## 4.Executing the class body
- The class body is executed (approximately) as exec(body, globals(), namespace). 

- A `exec` demo


```python
tmp_namespace = {}
def say_hi():
    return 'hi'
tmp_global = {'say_hi': say_hi}
exec('a=1; b=2; hi=say_hi();print(4+5*2)', tmp_global, tmp_namespace)
print('---tmp_namespace', tmp_namespace)
# print('---tmp_global:', tmp_global)
```

    14
    ---tmp_namespace {'a': 1, 'b': 2, 'hi': 'hi'}
    

exec(object[, globals[, locals]])
- If globals and locals are given, they are used for the global and local variables, respectively. 
- Remember that at module level, globals and locals are the same dictionary. 
- If exec gets two separate objects as globals and locals, the code will be executed as if it were embedded in a class definition

## 5.Creating the class object
- The class object is created by calling metaclass(name, bases, namespace, **kwds)
- After the class object is created, it is passed to the class decorators included in the class definition (if any) and the resulting object is bound in the local namespace as the defined class.

- A demo: create class object manually


```python
def foo1(self):
    print("foo1")
    pass
tmp_namespace = {'foo1':foo1, 'name': 'hi'}
FooClass=type('FooClass', (object,), tmp_namespace)
```


```python
f = FooClass()
f.foo1()
print(f.name)
```

    foo1
    hi
    

# Special methods

## Basic customization

1. **object.\_\_new\_\_(cls[, ...])**
- If \_\_new\_\_() is invoked during object construction and it returns an instance or subclass of cls, then the new instance’s \_\_init\_\_() method will be invoked like \_\_init\_\_(self[, ...]), where self is the new instance and the remaining arguments are the same as were passed to the object constructor.
- If \_\_new\_\_() does not return an instance of cls, then the new instance’s \_\_init\_\_() method will not be invoked.
- \_\_new_\_() is intended mainly to allow subclasses of immutable types (like int, str, or tuple) to customize instance creation. It is also commonly overridden in custom metaclasses in order to customize class creation.

2. object.\_\_del\_\_(self)
- Called when the instance is about to be destroyed.
- If a base class has a __del__() method, the derived class’s __del__() method, if any, must explicitly call it to ensure proper deletion of the base class part of the instance.

3. object.\_\_repr\_\_(self)
- Called by the repr() built-in function to compute the “official” string representation of an object
- If a class defines __repr__() but not __str__(), then __repr__() is also used when an “informal” string representation of instances of that class is required.

4. object.\_\_str\_\_(self)
- Called by str(object) and the built-in functions format() and print() to compute the “informal” or nicely printable string representation of an object
- The default implementation defined by the built-in type object calls object.\_\_repr\_\_().

5. “rich comparison” methods
- object.\_\_lt\_\_(self, other)
- object.\_\_le\_\_(self, other)
- object.\_\_eq\_\_(self, other)
- object.\_\_ne\_\_(self, other)
- object.\_\_gt\_\_(self, other)
- object.\_\_ge\_\_(self, other)

6. object.\_\_hash\_\_(self)
- Called by built-in function hash() 
- it is advised to mix together the hash values of the components of the object
- Changing hash values affects the iteration order of sets
- ...

7. object.\_\_bool\_\_(self)
- Called to implement truth value testing and the built-in operation bool(); 
- should return False or True. When this method is not defined, __len__() is called, if it is defined, and the object is considered true if its result is nonzero.
- If a class defines neither __len__() nor __bool__(), all its instances are considered true.


## Customizing attribute access
**1. object.\_\_getattr\_\_(self, name)**
- Called when the default attribute access fails
    - \_\_getattribute\_\_() raises an AttributeError because name is:
        - not an instance attribute
        - or not an attribute in the class tree for self
    - \_\_get\_\_() of a name property raises AttributeError
- a way to access other attributes of the instance

Demo


```python
class SqliteDB:
    pass
class MySqlDB:
    def select(self, sql):
        print('select')
    def update(self, sql):
        print('update')
    def delete(self, sql):
        print('delete')

class DBProxy:
    def __init__(self, real_db):
        self._real_db = real_db
        print("===", self._real_db.__dict__)
    def __getattr__(self, name):
        return getattr(self._real_db, name)

db = DBProxy(MySqlDB())
db.select('test')
db.update('test')
db.delete('test')
```

    === {}
    select
    update
    delete
    

2.object.\_\_getattribute\_\_(self, name)
- Called unconditionally to implement attribute accesses for instances of the class.
- If the class also defines \_\_getattr\_\_(), the latter will not be called unless \_\_getattribute\_\_() either calls it explicitly or raises an AttributeError.
- In order to avoid infinite recursion in this method, its implementation should always call the base class method with the same name to access any attributes it needs, for example, object.\_\_getattribute\_\_(self, name).


3.object.\_\_setattr\_\_(self, name, value)
- Called when an attribute assignment is attempted.
- If \_\_setattr\_\_() wants to assign to an instance attribute, it should call the base class method with the same name, for example, object.\_\_setattr\_\_(self, name, value).

4.object.\_\_delattr\_\_(self, name)

- Like __setattr__() but for attribute deletion instead of assignment. This should only be implemented if del obj.name is meaningful for the object.

5.object.\_\_dir\_\_(self)

- Called when dir() is called on the object. A sequence must be returned. dir() converts the returned sequence to a list and sorts it.


## Emulating callable objects

object.\_\_call\_\_(self[, args...])
- Called when the instance is “called” as a function; 
- if this method is defined, x(arg1, arg2, ...) is a shorthand for x.__call__(arg1, arg2, ...).


## Emulating container types

1. object.\_\_len\_\_(self)

2. object.\_\_length_hint\_\_(self)

3. object.\_\_getitem\_\_(self, key)
    - Called to implement evaluation of self[key]
 
4. object.\_\_setitem\_\_(self, key, value)
    - Called to implement assignment to self[key]
    
5. object.\_\_delitem\_\_(self, key)
    - Called to implement deletion of self[key].

6. object.\_\_missing\_\_(self, key)
    - Called by dict.\_\_getitem\_\_() to implement self[key] for dict subclasses when key is not in the dictionary.
    
7. object.\_\_iter\_\_(self)
    - This method is called when an iterator is required for a container.
    - This method should return a new iterator object that can iterate over all the objects in the container.
    - For mappings, it should iterate over the keys of the container.
    - Iterator objects also need to implement this method; they are required to return themselves. For more information on iterator objects, see Iterator Types.
    
8. object.\_\_reversed\_\_(self)
    - Called (if present) by the reversed() built-in to implement reverse iteration.
    - It should return a new iterator object that iterates over all the objects in the container in reverse order.

9. object.\_\_contains\_\_(self, item)
    - Called to implement membership test operators. Should return true if item is in self, false otherwise.


## Emulating numeric types
- object.\_\_add\_\_(self, other)
- object.\_\_sub\_\_(self, other)
- object.\_\_mul\_\_(self, other)
- ...

 (+, -, *, @, /, //, %, divmod(), pow(), **, <<, >>, &, ^, |). 
 
 (+=, -=, *=, @=, /=, //=, %=, **=, <<=, >>=, &=, ^=, |=). 
 
 ...

## With Statement Context Managers
A context manager is an object that defines the runtime context to be established when executing a with statement

1. object.\_\_enter\_\_(self)
- Enter the runtime context related to this object.
- The with statement will bind this method’s return value to the target(s) specified in the as clause of the statement, if any.
2. object.\_\_exit\_\_(self, exc_type, exc_value, traceback)
- Exit the runtime context related to this object.
- The parameters describe the exception that caused the context to be exited.
- If the context was exited without an exception, all three arguments will be None.
- If an exception is supplied, and the method wishes to suppress the exception (i.e., prevent it from being propagated), it should return a true value. Otherwise, the exception will be processed normally upon exit from this method.
- Should not reraise the passed-in exception; this is the caller’s responsibility.


**Demo**: python RLock implement code fragment


```python
class RLock:
    def __init__(self):
        pass

    def acquire(self, blocking=True, timeout=-1):
        print("---fake acquire")
        pass
    __enter__ = acquire

    def release(self):
        print("---fake release")
        pass
    def __exit__(self, t, v, tb):
        self.release()
```


```python
lock = RLock()
lock.acquire()
print('Do someting')
lock.release()
```

    ---fake acquire
    Do someting
    ---fake release
    

Simplifier and safer by:


```python
with RLock():
    print('Do someting')
```

    ---fake acquire
    Do someting
    ---fake release
    

### Another method


```python
from contextlib import contextmanager
class RLock_A:
    def __init__(self):
        pass

    def acquire(self, blocking=True, timeout=-1):
        print("---fake acquire")
        pass

    def release(self):
        print("---fake release")
        pass

    @contextmanager
    def lock(self):
        try:
            self.acquire()
            yield
        finally:
            self.release()
    
```


```python
A = RLock_A()
with A.lock():
    print('Do someting')
```

    ---fake acquire
    Do someting
    ---fake release
    

# Magic functions

## \_\_slots\_\_
- Decrease memory usage
- Cannot add attributes dynamically

Demo


```python
class Student(object):
    __slots__ = ('name', 'age')

s = Student()
s.name = 'Who'
s.age = 23
```


```python
s.score=90
```


    ---------------------------------------------------------------------------

    AttributeError                            Traceback (most recent call last)

    <ipython-input-3-103cb7d42de3> in <module>
    ----> 1 s.score=90
    

    AttributeError: 'Student' object has no attribute 'score'


# Multiple consturctor


```python
class Date:
    def __init__(self, y, m, d):
        self.y = y
        self.m = m
        self.d = d
    def __repr__(self):
        return '{}-{}-{}'.format(self.y, self.m, self.d)
    
    @classmethod
    def now(cls):
        from datetime import datetime
        now = datetime.now()
        return cls(now.year, now.month, now.day)

print(Date(2008, 7, 1))
print(Date.now())
```

    2008-7-1
    2020-3-23
    


```python

```
