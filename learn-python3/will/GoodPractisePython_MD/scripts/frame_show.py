def bar(y):
    z = y + 3
    return z

def foo():
    a = 1
    b = 2
    return a + bar(b)
foo()          