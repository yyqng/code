1. Unpacking Elements

```python
first, *others = (1,2,3,4)
first, *middle, last = (1,2,3,4)
name, email, *phone_numbers = ('Jack', 'jack@gmail.com', '1234567', '122333')
```

2. Keeping the last N items

```python
collections.deque(maxlen=5)
```

3. Finding the largest or smallest N items

```python
heapq.nlargest(3, [1,8,-1,4])
heapq.nsmallest(3, [1,8,-1,4])
```

```python
portfolio = [
{'name': 'IBM', 'shares': 100, 'price': 91.1},
{'name': 'AAPL', 'shares': 50, 'price': 543.22},
{'name': 'FB', 'shares': 200, 'price': 21.09},
{'name': 'HPQ', 'shares': 35, 'price': 31.75},
{'name': 'YHOO', 'shares': 45, 'price': 16.35},
{'name': 'ACME', 'shares': 75, 'price': 115.65}
]
cheap = heapq.nsmallest(3, portfolio, key=lambda s: s['price'])
expensive = heapq.nlargest(3, portfolio, key=lambda s: s['price'])
```
    See more about heapq
    
4. defaultdict

```python
from collections import defaultdict
d = defaultdict(list)
d['a'].append(1)
d['a'].append(2)
d['b'].append(4)
d = defaultdict(set)
d['a'].add(1)
d['a'].add(2)
d['b'].add(4)
```

5. OrderedDict vs dict

6. Filter sequence elements

```python
>>> mylist = [1, 4, -5, 10, -7, 2, 3, -1]
>>> [n for n in mylist if n > 0] # what differences compared with the 2 followings?
>>> it1 = (n for n in mylist if n > 0) 
>>> it2 =filter(lambda e: e > 0, mylist)
```

7. namedtuple

```python
from collections import namedtuple
Student = namedtuple(typename='Student', field_names=('age', 'name'))
s = Student(14, 'Tom')
print(s.age, s.name)
```

8. Using '?' to change from greedy match to shortest match about regular expression

```python
>>> re.findall(r'\".+\"', 'Computer syas "No", Phone says "Yes"')
['"No", Phone says "Yes"']
>>> re.findall(r'\".+?\"', 'Computer syas "No", Phone says "Yes"')
['"No"', '"Yes"']
```

9. Matching multiple lines

```python
>>> comment = re.compile(r'/\*(.*?)\*/', re.DOTALL)
>>> comment.findall(text2)
```

10. Taking a slice of an iterator

```python
>>> def count(n):
... while True:
... yield n
... n += 1
...
>>> c = count(0)
>>> c[10:20]
Traceback (most recent call last):
File "<stdin>", line 1, in <module>
TypeError: 'generator' object is not subscriptable
>>> # Now using islice()
>>> import itertools
>>> for x in itertools.islice(c, 10, 20):
    ...
```

11. Skipping the first part of an iterator

```python
>>> from itertools import dropwhile
>>> with open('/etc/passwd') as f:
... for line in dropwhile(lambda line: line.startswith('#'), f):
... print(line, end='')
```

```python
>>> from itertools import islice
>>> items = ['a', 'b', 'c', 1, 4, 10, 15]
>>> for x in islice(items, 3, None):
... print(x)
```

12. Using enummerate to return index

```python
>>> my_list = ['a', 'b', 'c']
>>> for idx, val in enumerate(my_list):
...     print(idx, val)
```

13. Iterating over multiple sequences

```python
>>> xpts = [1, 5, 4, 2, 10, 7]
>>> ypts = [101, 78, 37, 15, 62, 99]
>>> for x, y in zip(xpts, ypts):
... print(x,y)
```

```python
>>> a = [1, 2, 3]
>>> b = ['w', 'x', 'y', 'z']
>>> for i in zip(a,b):
... print(i)
...
(1, 'w')
(2, 'x')
(3, 'y')
```

```python
>>> from itertools import zip_longest
>>> for i in zip_longest(a,b):
... print(i)
(1, 'w')
(2, 'x')
(3, 'y')
(None, 'z')
>>> for i in zip_longest(a, b, fillvalue=0):
... print(i)
...
(1, 'w')
(2, 'x')
(3, 'y')
(0, 'z')
```

14. itertools.chain

```python
>>> from itertools import chain
>>> a = [1, 2, 3, 4]
>>> b = ['x', 'y', 'z']
>>> for x in chain(a, b):
... print(x)
...
1
2
3
4
x
y
z
```

15. Parsing huge XML files incrementally

```python
from xml.etree.ElementTree import iterparse

def parse_and_remove(filename, path):
    path_parts = path.split('/')
    doc = iterparse(filename, ('start', 'end'))
    # Skip the root element
    next(doc)
    tag_stack = []
    elem_stack = []
    for event, elem in doc:
        ...
```

16. functools.partial

```python
def spam(a, b, c, d):
    print(a, b, c, d)

>>> s3 = partial(spam, 1, 2, d=42) # a = 1, b = 2, d = 42
>>> s3(3)
1 2 3 42
```

17. with

```python
from datetime import datetime
class Timer():
    def __enter__(self):
        self._begin = datetime.now()
    def __exit__(self, *exec_info):
        self._end = datetime.now()
        print('cost time:', self._end - self._begin)

from contextlib import contextmanager

@contextmanager
def timeit():
    begin = datetime.now()
    yield
    print('cost time:', datetime.now() - begin)
```

```python
import time
with Timer():
    time.sleep(1)
    
with timeit():
    time.sleep(1)

# output:
cost time: 0:00:01.005418
cost time: 0:00:01.003908
```

18. Saving memory when creating a large number of instances

```python
class Date:
    __slots__ = ['year', 'month', 'day']
    def __init__(self, year, month, day):
        self.year = year
        self.month = month
        self.day = day
```

19. Defining more than 1 constructor in a class

```python
import time
class Date:
    # Primary constructor
    def __init__(self, year, month, day):
        self.year = year
        self.month = month
        self.day = day
        
    # Alternate constructor
    @classmethod
    def today(cls):
        t = time.localtime()
        return cls(t.tm_year, t.tm_mon, t.tm_mday)
```

20. Managing memory in cyclic data structres---weakref

```python
import weakref
class Node:
    def __init__(self, value):
        self.value = value
        self._parent = None
        self.children = []
    def __repr__(self):
        return 'Node({!r:})'.format(self.value)
    # property that manages the parent as a weak-reference
    @property
    def parent(self):
        return self._parent if self._parent is None else self._parent()

    @parent.setter
    def parent(self, node):
        self._parent = weakref.ref(node)

    def add_child(self, child):
        self.children.append(child)
        child.parent = self
```

21. Preserving function metadata when writing decorators

```python
import time
from functools import wraps
def timethis(func):
    '''
    Decorator that reports the execution time.
    '''
    @wraps(func)
    def wrapper(*args, **kwargs):
        start = time.time()
        result = func(*args, **kwargs)
        end = time.time()
        print(func.__name__, end-start)
        return result
    return wrapper
```


22. Raise an exception in response to another exception---use raise from instead of raise

```python
def example():
    try:
        int('N/A')
    except ValueError as e:
        raise RuntimeError('A parsing error occured') from e
example()
```

```python
ValueError Traceback (most recent call last)
<ipython-input-67-1d9d6fd16392> in example()
      2     try:
----> 3         int('N/A')
      4     except ValueError as e:

ValueError: invalid literal for int() with base 10: 'N/A'

The above exception was the direct cause of the following exception:

RuntimeError                              Traceback (most recent call last)
<ipython-input-68-270ee176495d> in <module>
----> 1 example()

<ipython-input-67-1d9d6fd16392> in example()
      3         int('N/A')
      4     except ValueError as e:
----> 5         raise RuntimeError('A parsing error occured') from e
      6 

RuntimeError: A parsing error occured
```

23. Reraise the last exception

```python
def example():
    try:
        int('N/A')
    except ValueError as e:
        #raise RuntimeError('A parsing error occured') from e
        raise
---------------------------------------------------------------------------
ValueError                                Traceback (most recent call last)
<ipython-input-71-270ee176495d> in <module>
----> 1 example()

<ipython-input-70-1539a7d60511> in example()
      1 def example():
      2     try:
----> 3         int('N/A')
      4     except ValueError as e:
      5         #raise RuntimeError('A parsing error occured') from e

ValueError: invalid literal for int() with base 10: 'N/A'
```

24. import a package not always import its all modules

    A demo using py27
- don't work
```python
import scipy
scipy.stats.pearsonr(range(10), range(10,20))
```

```
AttributeError                            Traceback (most recent call last)
<ipython-input-1-de092ca79670> in <module>()
      1 import scipy
----> 2 scipy.stats.pearsonr(range(10), range(10,20))

AttributeError: 'module' object has no attribute 'stats'
```

- work
    
```python
from scipy import stats

stats.pearsonr(range(10), range(10,20))

(1.0, 0.0)
```

25. re.split to discard the seperaters

```python
> fields = re.split(r'(;|,|\s)\s*', line)
>>> fields
['asdf', ' ', 'fjdk', ';', 'afed', ',', 'fjek', ',', 'asdf', ',', 'foo']
```

```python
>>> re.split(r'(?:,|;|\s)\s*', line)
['asdf', 'fjdk', 'afed', 'fjek', 'asdf', 'foo']
```