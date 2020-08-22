def sumto(a):
    if a <= 1:
        return 1
    else:
         return sumto(a-1) * a

print(sumto(3))