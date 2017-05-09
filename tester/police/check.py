import filecmp
import os
import subprocess
import threading

class Command(object):
  def __init__(self, cmd):
    self.cmd = cmd
    self.process = None

  def run(self, timeout):
    def target():
      devnull = open(os.devnull, 'w')
      self.process = subprocess.Popen(self.cmd, shell=True, stdout=devnull, stderr=devnull, close_fds=True)
      self.process.communicate()

    thread = threading.Thread(target=target)
    thread.start()
    thread.join(timeout)

    if thread.is_alive():
        self.process.kill()
        thread.join()

    return self.process.returncode

for input in os.listdir('test'):
  if input.endswith('.in'):
    output = input.replace('.in', '.out')
    tmpoutput = 'tmp_' + input.replace('.in', '.out')

    command = Command('./sol-slow < test/' + input + ' > test/' + tmpoutput)
    exitcode = command.run(timeout=5)

    if exitcode == 0:
      result = 'OK' if filecmp.cmp('test/' + output, 'test/' + tmpoutput) else 'Wrong Answer'
    else:
      result = 'Runtime Error'

    print input, result
