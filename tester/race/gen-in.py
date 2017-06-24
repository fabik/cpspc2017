import os
import random
import subprocess
import threading

random.seed(3123112)

def run_command(cmd):
  def target():
    devnull = open(os.devnull, 'w')
    process = subprocess.Popen(cmd, shell=True, stdout=devnull, stderr=devnull, close_fds=True)
    process.communicate()

  thread = threading.Thread(target=target)
  thread.start()
  thread.join()

def write_test(set_number, test_number, min_nm, max_nm, q, type, empty_percentage):
  letter = chr(ord('a') + test_number)
  filename = 'test/%02d.%s.in' % (set_number, letter)

  seed = random.randint(0, 10**9)
  run_command('./gen %d %d %d %d %d %d > %s' % (min_nm, max_nm, q, type, empty_percentage, seed, filename))

set_parameters = [
  # (set_number, min_nm, max_nm, q)
  (1, 970, 1000, 300), # 30 points
  (2, 970, 1000, 10**6) # 70 points
]

for set_number, min_nm, max_nm, q in set_parameters:
  test_number = 0
  for type in xrange(0, 2):
    for empty_percentage in (99, 90, 70, 50, 10, 5):
      write_test(set_number, test_number, min_nm, max_nm, q, type, empty_percentage)
      test_number += 1
