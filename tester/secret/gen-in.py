import os
import random
import subprocess
import threading

random.seed(5453454)

def run_command(cmd):
  def target():
    devnull = open(os.devnull, 'w')
    process = subprocess.Popen(cmd, shell=True, stdout=devnull, stderr=devnull, close_fds=True)
    process.communicate()

  thread = threading.Thread(target=target)
  thread.start()
  thread.join()

def write_special_test(filename, n, p, sx, sy, dx, dy):
  f = open(filename, 'w')
  f.write('%d\n' % (n))
  f.write('%s\n' % (p))
  f.write('%d %d\n' % (sx + 1, sy + 1))
  f.write('%d %d\n' % (dx + 1, dy + 1))
  f.close()

def write_test(set_number, test_number, max_logn):
  letter = chr(ord('a') + test_number)
  filename = 'test/%02d.%s.in' % (set_number, letter)

  if test_number == 0:
    logn = max_logn

    write_special_test(filename,
      n = 2 ** logn,
      p = 'W',
      sx = 0, sy = 0,
      dx = 2 ** logn - 1, dy = 2 ** logn - 1
    )

  elif test_number == 1:
    logn = max_logn

    write_special_test(filename,
      n = 2 ** logn,
      p = '('
          + '('
            + ((logn - 3) * '(') + 'W' + ((logn - 3) * 'BWB)')
            + ((logn - 3) * '(') + 'W' + ((logn - 3) * 'WBB)')
          + 'WB)'
          + '('
            + ((logn - 3) * '(') + 'W' + ((logn - 3) * 'BWB)')
          + 'BWB)'
        + 'WW)',
      sx = 0, sy = 0,
      dx = 2 ** (logn - 2), dy = 0
    )

  elif test_number == 2:
    logn = max_logn

    write_special_test(filename,
      n = 2 ** logn,
      p = '('
          + '('
            + ((logn - 3) * '(') + 'W' + ((logn - 3) * 'BWB)')
            + '('
              + ((logn - 4) * '(') + 'W' + ((logn - 4) * 'WBB)')
            + 'BBB)'
          + 'WB)'
          + '('
            + ((logn - 3) * '(') + 'W' + ((logn - 3) * 'BWB)')
          + 'BWB)'
        + 'WW)',
      sx = 0, sy = 0,
      dx = 2 ** (logn - 2), dy = 0
    )

  else:
    logn = random.randint(3, max_logn) if test_number < 10 else max_logn
    ans = test_number % 2
    step = random.randint(2, min(12, logn - 1)) if test_number < 10 else (logn / 5)
    seed = random.randint(0, 10**9)
    run_command('./gen %d %d %d %d > %s' % (logn, step, ans, seed, filename))

set_parameters = [
  # (set_number, max_logn)
  (1, 10), # 20 points
  (2, 60), # 80 points
]

for set_number, max_logn in set_parameters:
  for test_number in xrange(0, 15):
    write_test(set_number, test_number, max_logn)
