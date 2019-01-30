import vapoursynth as vs
import sys
import havsfunc as haf
import mvsfunc as mvf
import nnedi3_resample as nnrs
core = vs.get_core(accept_lowercase=True,threads=8)
core.max_cache_size = 6000
core.avs.LoadPlugin(r"C:/Program Files (x86)/MeGUI/tools/dgindexnv/x64 Binaries/DGDecodeNV.dll")
src = core.avs.DGSource(r"G:/DGNVindex/AAA/AAA x64.dgi")
src = core.fmtc.bitdepth (src, bits=16)
src = core.knlm.KNLMeansCL(src, d=1,a=2,h=1.8,channels="Y", device_type='gpu', device_id=1)
src = nnrs.nnedi3_resample(src,target_width=1280,target_height=720,mats="601", matd="709",kernel="Lanczos",taps=4)
src = core.f3kdb.Deband(src,range=15,y=64,cb=64,cr=64,grainy=64,grainc=64)
src = core.warp.AWarpSharp2(src,depth=12,chroma=1)
src = core.fmtc.bitdepth (src, bits=8)
src.set_output()
