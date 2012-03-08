
def unionRect(*parts):
  result = None
  for p in parts:
    if result:
      if p[2] and p[3]:
        x = min(result[0], p[0])
        y = min(result[1], p[1])
        xMax = max(result[0] + result[2], p[0] + p[2])
        yMax = max(result[1] + result[3], p[1] + p[3])
        result = [x, y, xMax - x, yMax - y]
    else:
      result = p[:]

  return result
