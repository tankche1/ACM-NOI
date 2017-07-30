#!/usr/bin/python

import os, sys

EPS = 1e-6

result_literal = {'AC': 'Yes', 'WA': 'No - Wrong Answer'}
def return_to_judge(result):
	print >>res, '<?xml version="1.0"?>'
	print >>res, '<result outcome="%s" security="%s"/>' % (result_literal[result],sys.argv[4])
	print >>sys.stderr, 'Judged as: ', result_literal[result]

def check_ans(pa,ja):
	if abs(pa-ja) <= EPS: return True
	# relative error, comment out if not needed
	# if abs(ja) > EPS and abs(pa-ja)/abs(ja) <= EPS: return True
	return False

def trim(x):
	while len(x) and ( x[-1] == '\r' or x[-1] == '\n' ):
		x = x[:-1]
	return x

def judge():
	T = int(inp.readline())
	out, ans = outf.readlines(), ansf.readlines()
	out, ans = trim(out), trim(ans)
	assert len(ans) == T
	if len(out) != T: return 'WA'
	for i in xrange(T):
		assert ans[i].startswith('Case #')
		id, ja = ans[i][6:].split(': ')
		id = int(id)
		ja = float(ja)

		if not out[i].startswith('Case #'): return 'WA'
		try:
			pid, pa = out[i][6:].split(': ')
			if pid.strip() != pid: return 'WA'
			pid = int(pid)
			if pa.lstrip() != pa: return 'WA'
			pa = float(pa)
		except:
			return 'WA'
		if id != pid or (not check_ans(pa, ja)): return 'WA'
	return 'AC'

inp = open(sys.argv[1], 'rt')
outf = open(sys.argv[2], 'rt')
ansf = open(sys.argv[3], 'rt')
res = open(sys.argv[4], 'wt')

return_to_judge(judge())
