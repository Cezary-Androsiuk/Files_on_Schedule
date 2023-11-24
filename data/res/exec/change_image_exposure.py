from PIL import Image, ImageTk
import os


def brightness_exponential(name, val):
    img = Image.open("in/" + name)
    result_img = Image.new('RGB', (img.width, img.height))
    if int(val) < 0:
        new_val = 1 - (float(val) / -255)
    else:
        new_val = 1 + (float(val) / 25)
    w, h = img.size
    for i in range(w):
        for j in range(h):
            r, g, b = img.getpixel((i,j))
            r = int(255 * (r/255) ** new_val)
            g = int(255 * (g/255) ** new_val)
            b = int(255 * (b/255) ** new_val)
            result_img.putpixel((i,j), (r,g,b))
    if not os.path.exists('schedules/'):
        os.mkdir('schedules/')
    if os.path.exists('schedules/' + name ):
        os.remove('schedules/' + name )
    result_img.save('schedules/' + name )#os.path.splitext(name)[0] + "_graphic.png")

if __name__ == '__main__':
    i = 0
    for file in os.listdir('in'):
        # print(file, i)
        brightness_exponential(file, 2550)
        i+=1
        
