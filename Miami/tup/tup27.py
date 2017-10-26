from xml.etree.ElementTree import *
import Image

#frame {{2,2},{40,40}}
#return [2,2,40,40]
def frame_str2int(frame):
    bound = frame.replace('{','')
    bound = bound.replace('}','')
    x,y,w,h = bound.split(',')
    return int(x),int(y),int(w),int(h)

#png: png_file_name
#config: list[ dict[frame,rotate] ]
#return: little_img
def deal_png(png, config):
    png = Image.open(png)

    for xf in config:
        x,y,w,h = frame_str2int( xf['frame'] )
        if xf['rotate']=='true':
            w,h = h,w

        img = png.crop( [ x,y,w+x,h+y ] )
        if xf['rotate']=='true':
            img = img.rotate(90)
        
        yield (xf['src_file'],img)
    

#fname: *.plist
#return list[ dict[src_file,frame,offset,roate,sourceColorRect,sourceSize] ]
def deal_plist(fname):
    root = parse(fname).getroot()

    frames_data = root[0][1]

    for i in range(0, len(frames_data), 2):
        src_file_name = frames_data[i].text
        file_info = frames_data[i+1]
        
        config = {}
        config['src_file'] = src_file_name
        config['frame'] = file_info[1].text
        config['offset'] = file_info[3].text
        config['rotate'] = file_info[5].tag
        config['sourceColorRect'] = file_info[7].text
        config['sourceSize'] = file_info[9].text
        
        yield config
        
#fname: some_file.plist
#return: some_file.png
def get_tp_png_name(fname):
    try:
        return parse(fname).getroot()[0][3][3].text
    except:
        return ''
    
    
    
    
    
    
    
    
    
    
    
    