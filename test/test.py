#! /usr/bin/env python3

#
# Created by Gustavo Viegas on 2017/06
#

from subprocess import Popen
from os import path, mkdir
from sys import argv

unit_bin = '../../../bin/unit'
unit_arg = {
    '--key': '0',
    '--node': 'localhost',
    '--port': 45100,
    '--option': 0,
    # '--clear': ''
}
tdir = 'test/td/'

if len(argv) < 2:
    print('Usage: ' + argv[0] + ' <NUMBER_OF_UNITS>')
elif not argv[1].isdigit():
    print('<NUMBER_OF_UNITS> argument must be a number')
else:
    p = None
    if not path.exists(tdir):
        mkdir(tdir)
    for i in range(0, int(argv[1])):
        l = [unit_bin, '--clear']
        unit_arg['--port'] += 1
        unit_arg['--option'] += 1
        for k, v in unit_arg.items():
            l.append(k)
            l.append(str(v))
        udir = tdir + 'u' + str(i+1)
        if not path.exists(udir):
            mkdir(udir)
        p = Popen(l, cwd=udir)
    if p is not None:
        p.wait()
