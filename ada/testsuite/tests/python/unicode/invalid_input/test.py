import libadalang

from unicode_utils import *

ctx = libadalang.AnalysisContext('utf-8')
unit = ctx.get_from_buffer('foo.adb', src_buffer_iso_8859_1)
for d in unit.diagnostics:
    print '  {}'.format(d)

print 'Done'
