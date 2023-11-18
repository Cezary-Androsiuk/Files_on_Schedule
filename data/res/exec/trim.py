from PIL import Image

def trim_img(p_in:str, p_out:str, left:int, top:int, width:int, height:int):
    im = Image.open(p_in)
    print(im.size)
    right = left + width
    bottom = top + height
    
    im.crop((left, top, right, bottom)).save(p_out)
    