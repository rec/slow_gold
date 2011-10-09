
def order(x, y):
  if len(y) > len(x):
    x, y = y, x
  return x, y

def overlapLeft(x, y):
  l = len(order(x, y))
  x = x[0:l]
  y = y[0:l]

def overlap(x, y):
  return order(overlapLeft(x, y), overlapLeft(y, x))
