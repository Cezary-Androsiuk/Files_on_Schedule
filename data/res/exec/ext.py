from PIL import Image # pip install Pillow





def get_dir_files(dir_path):
    import os
    files = []
    for file in os.listdir(dir_path):
        files.append(os.path.join(dir_path,file))

    return files


def convert_all_gif_in_dir_to_png(dir_path):
    def gif_to_png(file_path: str):
        print(file_path)
        image = Image.open(file_path)
        png_image = image.convert("RGBA")
        png_image.save(file_path.replace(".gif", ".png"),'PNG')
        image.close()

    files = get_dir_files(dir_path)

    print(len(files))
    for file in files:
        gif_to_png(file)











def crop_image():
    name_in = r".\1.png"
    name_out = r".\w_top.png"
    
    im = Image.open(name_in)
    print(im.size)
    cords = (0,0, im.size[0],3)
    im.crop(cords).save(name_out)












