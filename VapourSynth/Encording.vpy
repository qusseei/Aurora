import vapoursynth as vs
import sys
import havsfunc as haf
import mvsgfunc as mvf

core = vs.get_core(thread = 8)
core.max_cache_size = 2000

