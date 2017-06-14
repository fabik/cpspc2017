import os
import random
import subprocess
import threading

random.seed(32132231)

def run_command(cmd):
  def target():
    devnull = open(os.devnull, 'w')
    process = subprocess.Popen(cmd, shell=True, stdout=devnull, stderr=devnull, close_fds=True)
    process.communicate()

  thread = threading.Thread(target=target)
  thread.start()
  thread.join()

def write_test(set_number, test_number, min_n, max_n, m, min_q, max_q):
  letter = chr(ord('a') + test_number)
  filename = 'test/%02d.%s.in' % (set_number, letter)

  seed = random.randint(0, 10**9)
  run_command('./gen %d %d %d %d %d %d > %s' % (min_n, max_n, m, min_q, max_q, seed, filename))

set_parameters = [
  # (set_number, min_n, max_n, m, min_q, max_q)
  (1, 1, 15, 50, 1, 10**6), # 10 points
  (2, 1, 2, 50, 1, 10**18), # 30 points
  (3, 1, 15, 50, 1, 10**18) # 60 points
]

for set_number, min_n, max_n, m, min_q, max_q in set_parameters:
  for test_number in xrange(0, 5):
    write_test(set_number, test_number, min_n, max_n, m, min_q, max_q)
