import vapoursynth as vs
import sys
import havsfunc as haf
import mvsfunc as mvf

core = vs.get_core(threads=8)
core.max_cache_size = 2000

# src = r"D:\Movie\00002.m2ts"
# rip = r"D:\Movie\Lover.Letter.1995.720p.BluRay.AC3.x264-CQ.mkv"

core.avs.LoadPlugin(r"C:\Protable\VapourSynth64Portable_2018_12_19\VapourSynth64Portable\VapourSynth64\vapoursynth64\plugins\dgdecnv2053\x64 Binaries\DGDecodeNV.dll")
src = core.avs.DGSource(r"D:\00003_T1_Video - .dgi")

# src8 = core.lsmas.LWLibavSource(src,threads=1)
# src16 = mvf.Depth(src8,depth = 16)

# src16 = core.resize.Spline36(src16,1280,720)
# src16 = core.f3kdb.Deband(src16,output_depth = 16)

# rip8 = core.lsmas.LWLibavSource(rip,threads = 1)
# rip16 = mvf.Depth(rip8,depth = 16)

# res = core.std.Interleave([src16,rip16])
# res =core.text.ClipInfo(res, 7)

res = mvf.ToRGB(src,full=False,depth=8)
res.set_output()

