import vapoursynth as vs
import sys
import havsfunc as haf
import mvsfunc as mvf

core = vs.get_core(accept_lowercase=True,threads=8)
core.max_cache_size = 2000

source = r"C:\Users\AkiYami\Desktop\The.Cabin.in.the.Woods.2011.480p.BluRay.x264-HANDJOB.mkv"
ripped = r"C:\Users\AkiYami\Desktop\The.Cabin.in.the.Woods.2011.480p.BluRay.x264-HANDJOB.mkv"
src16 = core.lsmas.LWLibavSource(source,format="yuv420p16")
rip16 = core.lsmas.LWLibavSource(ripped,format="yuv420p16")
res = core.std.Interleave([src16,rip16])
res = mvf.ToRGB(res,full=False,depth=8)
res.set_output()
