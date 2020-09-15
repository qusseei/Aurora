import vapoursynth as vs
import sys
import havsfunc as haf
import mvsfunc as mvf
core = vs.get_core(accept_lowercase=True,threads=8) #CPU线程数
core.max_cache_size = 6000 #VS最大使用的内存（MB）
core.avs.LoadPlugin("C:/Program Files (x86)/MeGUI/tools/dgindexnv/x64 Binaries/DGDecodeNV.dll") #64位DGDecodeNV.dll的位置
src = core.avs.DGSource("G:/DGNVindex/AAA/AAA.dgi") #64位DGI索引文件的位置。能用DGNV尽量用DGNV，不能用再考虑下面的滤镜。
#src = core.ffms2.Source(source="G:/DGNVindex/AAA/AAA.wmv",fpsnum=30000,fpsden=1001) #适用于WMV等老格式，帧率写源的平均帧率即可转化为CFR。
#src = core.lsmas.LibavSMASHSource(source="G:/DGNVindex/AAA/AAA.mp4") #适用于mp4格式
#src = core.lsmas.LWLibavSource(source="G:/DGNVindex/AAA/AAA.mkv") #适用于非mp4格式，例如MKV。
#src = core.knlm.KNLMeansCL(src, d=1,a=2,h=1.8,channels="Y", device_type='gpu') #对Y平面降噪。h表示降噪力度。d和a表示降噪精度。
#src = core.knlm.KNLMeansCL(src, d=1,a=2,h=1.8,channels="UV",device_type='gpu') #对UV平面降噪。
super_params="{pel:2,gpu:1}" #gpu:1表示开启gpu运算，0为纯cpu运算。下同。
analyse_params="{gpu:1}"
smoothfps_params="{rate:{num:60000,den:1001,abs:true},algo:23}" #设定目标绝对帧率的分子和分母。algo表示算法，参考SVP的说明。23一般是效果最好的。
super = core.svp1.Super(src,super_params)
vectors = core.svp1.Analyse(super["clip"],super["data"],src,analyse_params)
smooth = core.svp2.SmoothFps(src,super["clip"],super["data"],vectors["clip"],vectors["data"],smoothfps_params)
src = core.std.AssumeFPS(smooth,fpsnum=smooth.fps_num,fpsden=smooth.fps_den)
src16 = core.fmtc.bitdepth (src, bits=16) #16bit高精度gamma-aware缩放。如不需要缩放，则删掉这一整段。
gray = core.std.ShufflePlanes(src16, 0, colorfamily=vs.GRAY)
gray = core.fmtc.transfer(gray,transs="709",transd="linear")
gray = core.fmtc.resample(gray,1280,720,kernel="spline36") #1280.720改成你想缩放的尺寸。注意成比例。不建议用于放大。
gray = core.fmtc.transfer(gray,transs="linear",transd="709")
UV = core.fmtc.resample(src16,1280,720,kernel="spline36") #1280.720改成你想缩放的尺寸。注意成比例。不建议用于放大。
down = core.std.ShufflePlanes([gray,UV],[0,1,2], vs.YUV)
src = core.fmtc.bitdepth (down, bits=8) #如果要输出10bit，则改成10。
#src = core.warp.AWarpSharp2(src,depth=4,chroma=1) #补偿性锐化。一般不建议使用，除非源的锐利度实在太烂。depth表示锐化强度。
src.set_output()
