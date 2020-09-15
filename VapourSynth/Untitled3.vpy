import vapoursynth as vs
import sys
import havsfunc as haf
import mvsfunc as mvf
core = vs.get_core(accept_lowercase=True,threads=8) #CPU线程数
core.max_cache_size = 6000 #VS最大使用的内存（MB）
core.avs.LoadPlugin("C:/Program Files (x86)/MeGUI/tools/dgindexnv/x64 Binaries/DGDecodeNV.dll") #64位DGDecodeNV.dll的位置
src = core.avs.DGSource("G:/DGNVindex/AAA/AAA.dgi",deinterlace=0) #64位DGI索引文件的位置。能用DGNV尽量用DGNV，不能用再考虑下面的滤镜。deinterlace=0为不反交错，1为普通反交错，2为倍帧反交错。
#src = core.ffms2.Source(source="G:/DGNVindex/AAA/AAA.wmv",fpsnum=30000,fpsden=1001) #适用于WMV等老格式，帧率写源的平均帧率即可转化为CFR。
#src = core.lsmas.LibavSMASHSource(source="G:/DGNVindex/AAA/AAA.mp4") #适用于mp4格式
#src = core.lsmas.LWLibavSource(source="G:/DGNVindex/AAA/AAA.mkv") #适用于非mp4格式，例如MKV。
#截取
#src = core.std.Trim(src,0,1) #0和1为开始帧和结束帧。
#黑边处理
#src = core.std.CropRel(src,left=0,right=0,top=0,bottom=0) #切黑边
#src = core.std.AddBorders(src,left=0,right=0,top=0,bottom=0) #加黑边
#降噪
#src = core.knlm.KNLMeansCL(src, d=1,a=2,h=1.8,channels="Y", device_type='gpu') #对Y平面降噪。h表示降噪力度。d和a表示时间和空间的降噪精度。
#src = core.knlm.KNLMeansCL(src, d=1,a=2,h=1.8,channels="UV",device_type='gpu') #对UV平面降噪。
#色彩空间转换（RGBtoYUV）
#src = mvf.ToYUV(src,matrix="709") #1080P和720P是709,480P是601.
#色彩空间转换（YUV标准互转） #两个"""之间表示整段被注释掉，去掉两个"""可开启这段代码的功能
"""
src = core.fmtc.bitdepth (src, bits=16)
src = core.fmtc.resample (src, css="444")
src = core.fmtc.matrix (src, mats="601", matd="709") #mats为源的色彩标准，matd为输出的色彩标准
src = core.fmtc.resample (src, css="420")
src = core.fmtc.bitdepth (src, bits=8)
"""
#字幕
#src = core.sub.TextFile(src,file="G:/DGNVindex/AAA/AAA1.ass") #支持srt，ass，ssa等格式字幕文件。
#SVP补帧 #两个"""之间表示整段被注释掉，去掉两个"""可开启这段代码的功能
"""
super_params="{pel:2,gpu:1}" #gpu:1表示开启gpu运算，0为纯cpu运算。下同。
analyse_params="{gpu:1}"
smoothfps_params="{rate:{num:60000,den:1001,abs:true},algo:23}" #设定目标绝对帧率的分子和分母。algo表示算法，参考SVP的说明。23一般是效果最好的。
super = core.svp1.Super(src,super_params)
vectors = core.svp1.Analyse(super["clip"],super["data"],src,analyse_params)
smooth = core.svp2.SmoothFps(src,super["clip"],super["data"],vectors["clip"],vectors["data"],smoothfps_params)
src = core.std.AssumeFPS(smooth,fpsnum=smooth.fps_num,fpsden=smooth.fps_den)
"""
#非Gamma-aware分辨率缩小
#src = core.resize.Spline36(src,1280,720)
#Gamma-aware分辨率缩小
"""
src16 = core.fmtc.bitdepth (src, bits=16) #16bit高精度gamma-aware缩放。如不需要缩放，则删掉这一整段。
gray = core.std.ShufflePlanes(src16, 0, colorfamily=vs.GRAY)
gray = core.fmtc.transfer(gray,transs="709",transd="linear")
gray = core.fmtc.resample(gray,1280,720,kernel="spline36") #1280.720改成你想缩放的尺寸。注意成比例。不建议用于放大。
gray = core.fmtc.transfer(gray,transs="linear",transd="709")
UV = core.fmtc.resample(src16,1280,720,kernel="spline36") #1280.720改成你想缩放的尺寸。注意成比例。不建议用于放大。
down = core.std.ShufflePlanes([gray,UV],[0,1,2], vs.YUV)
src = core.fmtc.bitdepth (down, bits=8) #如果要输出10bit，则改成10。
"""
#576p以上缩小到576p以下
"""
src16 = core.fmtc.bitdepth (src, bits=16)
gray = core.std.ShufflePlanes(src16, 0, colorfamily=vs.GRAY)
gray = core.fmtc.transfer(gray,transs="709",transd="linear")
gray = core.fmtc.resample(gray,640,480,kernel="spline36",css="444") #640,480改成你想缩放的尺寸。注意成比例。不建议用于放大。
gray = core.fmtc.transfer(gray,transs="linear",transd="709")
UV = core.fmtc.resample(src16,640,480,kernel="spline36",css="444") #640,480改成你想缩放的尺寸。注意成比例。不建议用于放大。
down = core.std.ShufflePlanes([gray,UV],[0,1,2], vs.YUV)
src = core.fmtc.matrix (down, mats="709", matd="601") #mats为源的色彩标准，matd为输出的色彩标准
src = core.fmtc.resample (src, css="420")
src = core.fmtc.bitdepth (down, bits=8) #如果要输出10bit，则改成10。
"""
#普通DVD放大
"""
src_480 = src
src_480 = core.fmtc.bitdepth (src_480, bits=16)
upscaled = core.fmtc.resample(src_480,1280,720, kernel="lanczos",taps=4,css="444") #本行和下一行的分辨率改成720p或1080p。
src = core.rgvs.Repair(upscaled, core.fmtc.resample(src_480,1280,720, kernel="gauss",a1=100,css="444"),1)
src = core.fmtc.matrix (src, mats="601", matd="709") #已做色彩标准处理
src = core.fmtc.resample (src, css="420")
src = core.fmtc.bitdepth (src, bits=8)
"""
#NNEDI3_resize16的DVD放大（高质量，极慢，需要import nnedi3_resample as nnrs）
"""
src = core.fmtc.bitdepth (src, bits=16)
src = nnrs.nnedi3_resample(src,target_width=1280,target_height=720,mats="601", matd="709",kernel="Lanczos",taps=4) #分辨率改为720p或1080p。
src = core.f3kdb.Deband(src,range=15,y=64,cb=64,cr=64,grainy=64,grainc=64) #去色带，选择性开启。参数可以自行调整。
src = core.fmtc.bitdepth (src, bits=8)
"""
#补偿性锐化/deringring
#src = core.warp.AWarpSharp2(src,depth=4,chroma=1) #补偿性锐化。一般不建议使用，除非源的锐利度实在太烂。depth表示锐化强度。
src.set_output()
