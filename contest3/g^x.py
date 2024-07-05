def is_even(x):
    return not x%2
N = 0


def group_pow(g,x):
    if x == 1:
        return g
    if is_even(x):
        a = group_pow(g,x/2)
        return (a*a) % N
    else:
        a = group_pow(g,(x-1)/2)
        return (((g*a) % N) *a) % N
    
