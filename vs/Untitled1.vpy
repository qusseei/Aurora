import vapoursynth as vs
import sys
import havsfunc as haf
import mvsfunc as mvf
import RW7T6
import GradFun3 as GF3
core = vs.get_core(accept_lowercase=True)
core.max_cache_size = 1500

core.avs.LoadPlugin(r"C:/VapourSynth/plugins64/DGDecodeNV.dll")

src = core.ffms2.Source(source=r'00.mkv')#mkv
src = core.lsmas.LibavSMASHSource(source=r'00.mp4')#MP4
src = core.lsmas.LWLibavSource(source=r'00.mp4')#m2ts，mkv，ts

src = core.avs.DGSource(r"G:\Movies.HD\Jade.dgi",fieldop=0,deinterlace=1)#dgi具体路径
src = mvf.ToYUV(src,matrix="601")
src = core.std.Trim(src,10000,11000)
src = core.std.SelectEvery(clip=src,cycle=1800,offsets= range(96))
src = core.std.AssumeFPS(clip=src,fpsnum=24000,fpsden=1001)
src = core.std.CropRel(clip=src,left=0,right=0,top=22,bottom=22)#切边
src = core.std.AddBorders(clip=src,left=0,right=0,top=22,bottom=22)#加黑边
src = mvf.Depth(src, depth=16)
src = RW7T6.RW7T6(src,854,480)
src = core.fmtc.resample(clip=src, w=960, h=480)
src = core.fmtc.resample (clip=src, css="420")
src = core.fmtc.bitdepth (clip=src, bits=8)
src = core.resize.Spline36(clip=src,width=960, height=540)#缩放
src = core.text.Text(clip=src,text="Source")#标注Source
src = core.text.FrameProps(clip=src,props=["_PictType"],alignment=9)#帧类型
enc = core.ffms2.Source(source=r'Shinjuku.Incident.2009.vpy_Encoded_21.0_ss.mkv')
enc = core.text.Text(clip=src,text="Encode")#标注Encode
enc = core.text.FrameProps(clip=enc,props=["_PictType"],alignment=9)#帧类型
sec = core.std.Interleave([src,enc])#对比图
src = haf.SMDegrain(src)#降噪
src = core.knlm.KNLMeansCL(src, device_type='gpu')#降噪 速度慢
src = core.f3kdb.Deband(clip=src,range=15,y=32,cb=32,cr=32,grainy=64,grainc=64)#去色带,小写
src = haf.QTGMC(src, Preset='Medium', TFF=True)#反交错
src = core.sub.TextFile(clip=src,file=r"chs1.ass")#字幕
src.set_output()



