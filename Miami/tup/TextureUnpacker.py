from TextureUnpacker_xrc import *
import wx

app = wx.App()

mf = xrcMainFrame(None)
mf.Show()


app.MainLoop()