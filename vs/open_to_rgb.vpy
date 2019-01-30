import vapoursynth as vs
import sys
import havsfunc as haf
import mvsfunc as mvf

core = vs.get_core(accept_lowercase=True,threads=8)
core.max_cache_size = 2000

source = r"C:\Users\qusse\Desktop\2017_OURDISC_VTS_04_1.d2v"
#res = core.lsmas.LWLibavSource(source,threads=1)
res = core.d2v.Source(input = r"C:\Users\qusse\Desktop\2017_OURDISC_VTS_04_1.d2v")
#src = core.resize.Spline36(src,1280,720)
#rip = src
#rip = core.rgvs.RemoveGrain(rip,[11,4])
#rip = core.f3kdb.Deband(clip = rip, range = 15, y = 32, cb = 24, cr =24)
#src = core.std.SetFrameProp(src, prop="_FieldBased", intval=0)
#res = core.std.Interleave(clips = [src,rip])
#res = core.std.CropRel(clip = res, left = 0, right = 0, top = 0, bottom = 0)
#res = core.std.AddBorders(clip = res, left = 106, right = 106, top = 0, bottom = 0)
#res = core.resize.Spline36(res,852,480)
#res = core.text.ClipInfo(rip)
#res = mvf.ToRGB(res)
res.set_output()
