#!/usr/bin/python

import os, sys

result_literal = {'AC': 'Yes', 'WA': 'No - Wrong Answer'}
def return_to_judge(result):
	print >>res, '<?xml version="1.0"?>'
	print >>res, '<result outcome="%s" security="%s"/>' % (result_literal[result],sys.argv[4])
	print >>sys.stderr, 'Judged as: ', result_literal[result]

def trim(x):
	while len(x) and ( x[-1] == '\r' or x[-1] == '\n' ):
		x = x[:-1]
	return x

def judge():
	T = int(inp.readline())
	for i in xrange(T):
		al = ansf.readline()
		assert al.startswith('Case #')
		pl = outf.readline()
		if not pl.startswith('Case #'): return 'WA'
		id = int(al[6:].split(':')[0])

		try:
			pl = pl[6:]
			if pl.find(':') == -1: return 'WA'
			if id != int(pl[:pl.find(':')]): return 'WA'
			if pl[:pl.find(':')].strip() != pl[:pl.find(':')]: return 'WA'
			if pl[pl.find(':')+1:].strip() != '': return 'WA'
		except:
			return 'WA'

		JN = int(ansf.readline())
		try:
			nl = outf.readline()
			if nl.lstrip() != nl: return 'WA'
			PN = int(nl)
		except:
			return 'WA'

		if JN != PN: return 'WA'

		collector_ja = []
		collector_pa = []
		for i in xrange(JN): collector_ja.append(ansf.readline().rstrip())
		try:
			for i in xrange(JN): collector_pa.append(outf.readline().rstrip())
		except:
			return 'WA'
		if sorted(collector_ja) != sorted(collector_pa): return 'WA'
	assert ansf.read().strip() == ''
	if outf.read().strip() != '': return 'WA'
	return 'AC'

inp = open(sys.argv[1], 'rt')
outf = open(sys.argv[2], 'rt')
ansf = open(sys.argv[3], 'rt')
res = open(sys.argv[4], 'wt')

return_to_judge(judge())
