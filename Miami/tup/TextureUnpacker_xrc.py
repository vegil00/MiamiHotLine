# This file was automatically generated by pywxrc.
# -*- coding: UTF-8 -*-

import wx
import wx.xrc as xrc

__res = None

def get_resources():
    """ This function provides access to the XML resources in this module."""
    global __res
    if __res == None:
        __init_resources()
    return __res




class xrcMainFrame(wx.Frame):
#!XRCED:begin-block:xrcMainFrame.PreCreate
    def PreCreate(self, pre):
        """ This function is called during the class's initialization.
        
        Override it for custom setup before the window is created usually to
        set additional window styles using SetWindowStyle() and SetExtraStyle().
        """
        pass
        
#!XRCED:end-block:xrcMainFrame.PreCreate

    def __init__(self, parent):
        # Two stage creation (see http://wiki.wxpython.org/index.cgi/TwoStageCreation)
        pre = wx.PreFrame()
        self.PreCreate(pre)
        get_resources().LoadOnFrame(pre, parent, "MainFrame")
        self.PostCreate(pre)

        # Define variables for the controls, bind event handlers
        self.plist_file = xrc.XRCCTRL(self, "plist_file")
        self.cur_plist = xrc.XRCCTRL(self, "cur_plist")
        self.content = xrc.XRCCTRL(self, "content")
        self.png_img = xrc.XRCCTRL(self, "png_img")
        self.input_dir = xrc.XRCCTRL(self, "input_dir")
        self.export = xrc.XRCCTRL(self, "export")
        self.tip = xrc.XRCCTRL(self, "tip")

        self.Bind(wx.EVT_LISTBOX, self.OnListbox_plist_file, self.plist_file)
        self.Bind(wx.EVT_LISTBOX, self.OnListbox_cur_plist, self.cur_plist)
        self.Bind(wx.EVT_BUTTON, self.OnButton_btnDirectory, id=xrc.XRCID('btnDirectory'))
        self.Bind(wx.EVT_BUTTON, self.OnButton_export, self.export)

        self.input_dir.SetValue( open('tup.cfg','r').read() )
        self.OnButton_btnDirectory(None)
#!XRCED:begin-block:xrcMainFrame.OnListbox_plist_file
#!XRCED:begin-block:xrcMainFrame.OnListbox_plist_file
    def OnListbox_plist_file(self, evt):
        self.cur_plist.Clear()
        self.cur_plist_data = {}
        import tup27
        for x in tup27.deal_plist(evt.GetString()):
            self.cur_plist.Append( x['src_file'] )
            self.cur_plist_data[ x['src_file'] ] = x
		
        png = wx.Image(tup27.get_tp_png_name(evt.GetString()), wx.BITMAP_TYPE_PNG).ConvertToBitmap()
        #self.png_img.Clear()
        self.png_img.SetBitmap( png )
        self.Refresh()
		
#!XRCED:begin-block:xrcMainFrame.OnListbox_cur_plist
    def OnListbox_cur_plist(self, evt):
        text = ''
        for (k,v) in self.cur_plist_data[evt.GetString()].items():
            text += '%s\t%s\r\n'%(k,v)
        self.content.SetLabelText( text )
        
        import tup27
        x,y,w,h = tup27.frame_str2int(self.cur_plist_data[evt.GetString()]['frame'])
        if self.cur_plist_data[evt.GetString()]['rotate']=='true':
            w,h = h,w
            
        bmp = wx.Image(tup27.get_tp_png_name( self.plist_file.GetString(self.plist_file.GetSelections()[0]) ), wx.BITMAP_TYPE_PNG).ConvertToBitmap()
        dc = wx.MemoryDC(bmp)
        
        dc.SetBackground(wx.WHITE_BRUSH)
        dc.Clear()

        dc.DrawBitmap(wx.Image(tup27.get_tp_png_name( self.plist_file.GetString(self.plist_file.GetSelections()[0]) ), wx.BITMAP_TYPE_PNG).ConvertToBitmap(),0,0)
        
        dc.SetPen(wx.Pen( wx.Colour(255,0,0),2 ))
        
        dc.DrawLine( x,y, x+w,y )
        dc.DrawLine( x+w-1,y, x+w-1,y+h )
        dc.DrawLine( x+w,y+h-1, x,y+h-1 )
        dc.DrawLine( x,y+h, x,y )
        
        self.png_img.SetBitmap(dc.GetAsBitmap())
        
        self.Refresh()
        
#!XRCED:end-block:xrcMainFrame.OnListbox_cur_plist        

#!XRCED:begin-block:xrcMainFrame.OnButton_btnDirectory
    def OnButton_btnDirectory(self, evt):
        self.plist_file.Clear()
        self.cur_plist.Clear()
        self.content.SetValue('')
        self.tip.SetLabelText('')
        import glob, os
        if not os.path.isdir( self.input_dir.GetValue() ):
            self.tip.SetLabelText( "'%s' is not available"%self.input_dir.GetValue() )
            return
        os.chdir(self.input_dir.GetValue())
        for x in glob.glob('*.plist'):
			self.plist_file.Append( x )
            
        if self.plist_file.GetCount()==0:
            self.tip.SetLabelText( "'%s' has no .plist file"%self.input_dir.GetValue() )
        else:
            import sys
            open(os.path.dirname(sys.argv[0])+'\\tup.cfg','w').write(os.getcwd())


        
    def OnButton_export(self, evt):
        import tup27,os
        
        self.tip.SetLabelText('')
        
        tips = ''
        for i in self.plist_file.GetSelections():
            file = self.plist_file.GetString(i)
            
            if not os.path.isdir( file[0:-6] ):
                os.mkdir( file[0:-6] )
            
            for name,img in tup27.deal_png( tup27.get_tp_png_name(file), tup27.deal_plist(file) ):
                img.save( '%s\\%s'%(file[0:-6], name) )

            print file
            tips += '%s '%file
           
        self.tip.SetLabelText(tips+' succeed')




# ------------------------ Resource data ----------------------

def __init_resources():
    global __res
    __res = xrc.EmptyXmlResource()

    __res.Load('TextureUnpacker.xrc')