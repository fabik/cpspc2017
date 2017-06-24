import random

random.seed(92938082)

def gen_random(min_n, max_n, min_m, max_m, min_in_degree):
  n = random.randint(min_n, max_n)
  m = random.randint(min_m, max_m)
  
  if min_in_degree != 0:
    n = min(n, m / min_in_degree)

  edges = set()

  for v in xrange(0, n):
    for i in xrange(0, min_in_degree):
      while True:
        u = random.randint(0, n-1)
        edge = (u, v)
        if u != v and edge not in edges:
          edges.add(edge)
          break

  while len(edges) < m:
    u = random.randint(0, n-1)
    v = random.randint(0, n-1)
    edge = (u, v)
    if u != v and edge not in edges:
      edges.add(edge)

  return (n, m, edges)

def gen_cycle_with_star(max_n, max_m):
  n = m = min(max_n, max_m)
  k = n/2

  edges = set()
  for u in xrange(0, k):
    v = (u+1) % k
    edges.add((u, v))
  edges.add((0, k))
  for v in xrange(k+1, n):
    edges.add((k, v))

  return (n, m, edges)

def gen_cycle_with_path(max_n, max_m):
  n = m = min(max_n, max_m)
  k = n/2

  edges = set()
  for u in xrange(0, k):
    v = (u+1) % k
    edges.add((u, v))
  for v in xrange(k, n):
    u = v-1
    edges.add((u, v))

  return (n, m, edges)

def gen_cycle_with_path_and_cycle(max_n, max_m):
  n = min(max_n, max_m-1)
  m = n+1
  k = n/3

  edges = set()
  for u in xrange(0, k):
    v = (u+1) % k
    edges.add((u, v))
  for v in xrange(k, n-k):
    u = v-1
    edges.add((u, v))
  for u in xrange(n-k-1, n-1):
    v = u+1
    edges.add((u, v))
  edges.add((n-1, n-k-1))

  return (n, m, edges)

def get_path_of_cycles(max_n, max_m):
  n = min(max_n, max_m * 2 / 3)
  if n % 2 == 0:
    n -= 1
  k = n / 2
  m = k * 3 - 1

  edges = set()
  for i in xrange(0, k):
    u = i * 2
    v = i * 2 + 1
    w = i * 2 + 2

    edges.add((u, v))
    edges.add((v, w))

    if i != k / 2:
      edges.add((w, u))

  return (n, m, edges)

def get_trivial_cases():
  return [
    (2, 1, [(0, 1)]),
    (2, 2, [(0, 1), (1, 0)]),
    (3, 1, [(0, 1)]),
    (10, 9, [(0, 1), (1, 2), (2, 3), (3, 4), (4, 5), (5, 6), (6, 7), (7, 8), (8, 9)]),
    (10, 10, [(0, 1), (1, 2), (2, 3), (3, 4), (4, 5), (5, 6), (6, 7), (7, 8), (8, 9), (4, 0)]),
    (10, 11, [(0, 1), (1, 2), (2, 3), (3, 4), (4, 5), (5, 6), (6, 7), (7, 8), (8, 9), (4, 0), (9, 4)])
  ]

def shuffle_graph(n, m, edges):
  vertices = [i for i in xrange(0, n)]
  random.shuffle(vertices)

  edges = [(vertices[u], vertices[v]) for (u, v) in edges]
  random.shuffle(edges)

  return (n, m, edges)

def write_tests(set_number, set_data):
  for test_number, test_data in enumerate(set_data):
    write_test(set_number, test_number, test_data)

def write_test(set_number, test_number, test_data):
  letter = chr(ord('a') + test_number)
  filename = 'test/%02d.%s.in' % (set_number, letter)
  (n, m, edges) = test_data
  (n, m, edges) = shuffle_graph(n, m, edges)
  assert len(edges) == m

  f = open(filename, 'w')
  f.write('%d %d\n' % (n, m))
  for (u, v) in edges:
    f.write('%d %d\n' % (u+1, v+1))
  f.close()

set_parameters = [
  # (set_number, min_n, max_n, min_m, max_m)
  (1, 500, 1000, 1000, 3000), # 30 points
  (2, 500000, 1000000, 1000000, 1000000) # 70 points
]

for set_number, min_n, max_n, min_m, max_m in set_parameters:
  set_data = [
    gen_random(min_n, max_n, min_m, max_m, 0),
    gen_random(min_n, max_n, min_m, max_m, 0),
    gen_random(min_n, max_n, min_m, max_m, 0),
    gen_random(min_n, max_n, min_m, max_m, 1),
    gen_random(min_n, max_n, min_m, max_m, 1),
    gen_random(min_n, max_n, min_m, max_m, 1),
    gen_random(min_n, max_n, min_m, max_m, 2),
    gen_random(min_n, max_n, min_m, max_m, 2),
    gen_random(min_n, max_n, min_m, max_m, 2),
    gen_random(min_n, max_n, min_m, max_m, 3),
    gen_random(min_n, max_n, min_m, max_m, 3),
    gen_random(min_n, max_n, min_m, max_m, 3),
    gen_cycle_with_star(max_n, max_m),
    gen_cycle_with_path(max_n, max_m),
    gen_cycle_with_path_and_cycle(max_n, max_m),
    get_path_of_cycles(max_n, max_m)
  ]
  set_data.extend(get_trivial_cases())
  write_tests(set_number, set_data)
