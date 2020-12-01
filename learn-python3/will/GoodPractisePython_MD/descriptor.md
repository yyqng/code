## what is a descriptor?
Three behaviors for an attribute of an object:
1. read
2. set
3. delete

Desctiptor is a hook when accessing an attribute

## Demo


```python
class Book(object):
    def __init__(self):
        self._page = 0
    @property
    def page(self):
        return self._page
    @page.setter
    def page(self, value):
        if value < 0:
            raise Exception("page value should >= 0")
        self._page = value

book = Book()
print(book.page)
book.page=-2
print(book.page)
print("done")
```

## What is *property*


```python
help(property)
```

    Help on class property in module builtins:
    
    class property(object)
     |  property(fget=None, fset=None, fdel=None, doc=None)
     |  
     |  Property attribute.
     |  
     |    fget
     |      function to be used for getting an attribute value
     |    fset
     |      function to be used for setting an attribute value
     |    fdel
     |      function to be used for del'ing an attribute
     |    doc
     |      docstring
     |  
     |  Typical use is to define a managed attribute x:
     |  
     |  class C(object):
     |      def getx(self): return self._x
     |      def setx(self, value): self._x = value
     |      def delx(self): del self._x
     |      x = property(getx, setx, delx, "I'm the 'x' property.")
     |  
     |  Decorators make defining new properties or modifying existing ones easy:
     |  
     |  class C(object):
     |      @property
     |      def x(self):
     |          "I am the 'x' property."
     |          return self._x
     |      @x.setter
     |      def x(self, value):
     |          self._x = value
     |      @x.deleter
     |      def x(self):
     |          del self._x
     |  
     |  Methods defined here:
     |  
     |  __delete__(self, instance, /)
     |      Delete an attribute of instance.
     |  
     |  __get__(self, instance, owner, /)
     |      Return an attribute of instance, which is of type owner.
     |  
     |  __getattribute__(self, name, /)
     |      Return getattr(self, name).
     |  
     |  __init__(self, /, *args, **kwargs)
     |      Initialize self.  See help(type(self)) for accurate signature.
     |  
     |  __set__(self, instance, value, /)
     |      Set an attribute of instance to value.
     |  
     |  deleter(...)
     |      Descriptor to change the deleter on a property.
     |  
     |  getter(...)
     |      Descriptor to change the getter on a property.
     |  
     |  setter(...)
     |      Descriptor to change the setter on a property.
     |  
     |  ----------------------------------------------------------------------
     |  Static methods defined here:
     |  
     |  __new__(*args, **kwargs) from builtins.type
     |      Create and return a new object.  See help(type) for accurate signature.
     |  
     |  ----------------------------------------------------------------------
     |  Data descriptors defined here:
     |  
     |  __isabstractmethod__
     |  
     |  fdel
     |  
     |  fget
     |  
     |  fset
    
    


```python
class Book(object):
    def __init__(self):
        self._page = 0

    def get_page(self):
        return self._page

    def set_page(self, value):
        if value < 0:
            raise Exception("page value should >= 0")
        self._page = value
    page = property(get_page, set_page)

book = Book()
print(book.page)
book.page=6
print(book.page)
print("done")
```

### Discussion
- print(book.page) -> property.\_\_get\_\_ be triggered
- bool.page = 6 -> property.\_\_set\_\_ be triggered

> We can define a class like property with \_\_get\_\_ and \_\_set\_\_

## Your descriptor


```python
class JobStatus(object):
    def __init__(self, name):
        self._name = name
    def __set__(self, instance, value):
        if value not in ('running', 'stopped', 'unknown'):
            raise Exception('wrong job status:{}'.format(value))
        instance.__dict__[self._name] = value
    def __get__(self, instance, owner):
        return instance.__dict__[self._name]

class Job(object):
    status = JobStatus('status')
    def __init__(self):
        self.status = 'unknown'

j1, j2 = Job(), Job()
j1.status = 'running'
print(j1.status)
print(j2.status)
#j.status='abc'
```

## Why put the descriptor in class level instead of instance level
Behavior is belong to class rather than instance

## Lazy Property
demo from \<\<python cookbook\>\>


```python
class lazyproperty:
    def __init__(self, func):
        self.func = func
    def __get__(self, instance, cls):
        value = self.func(instance)
        setattr(instance, self.func.__name__, value)
        return value

import math
class Circle:
    def __init__(self, radius):
        self.radius = radius
        
    def area_v0(self):
        print('Computing area')
        return math.pi * self.radius ** 2
        
    @lazyproperty
    def area_v1(self):
        print('Computing area')
        return math.pi * self.radius ** 2

```


```python
c = Circle(9)
print(c.area_v0())
print(c.area_v0())
```

    Computing area
    254.46900494077323
    Computing area
    254.46900494077323
    


```python
print(c.area_v1)
print(c.area_v1)
```

    Computing area
    254.46900494077323
    254.46900494077323
    

## Usage situations
1. Additional control to the attribute
    - that is your control of the attributes is complicated enough to extract to a class
