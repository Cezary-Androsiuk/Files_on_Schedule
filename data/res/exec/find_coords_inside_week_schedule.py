import cv2 # pip install opencv-python
import numpy as np
import ext
import trim
import os


def locate_top_left_coords(schedule_path, tmplate_path):
    schedule = cv2.imread(schedule_path)
    tmplate = cv2.imread(tmplate_path)
    

    coords = []
    res = cv2.matchTemplate(schedule, tmplate, cv2.TM_CCOEFF_NORMED)  # idk not my code
    threshold = .997                                                # best value to find tmplates
    loc = np.where(res >= threshold)                                # idk not my code
    for pt in zip(*loc[::-1]):  # Switch columns and rows           # idk not my code
        coords.append([int(pt[0])-1, int(pt[1])-1])

    return coords


def get_rectangles_from_points(coords_top, coords_bottom, template_width=134, template_height=3):
    def get_dic_from_coords(coords):
        coordinate_groups = {}
        for c in coords:
            x = c[0]
            if x not in coordinate_groups:
                coordinate_groups[x] = []
            coordinate_groups[c[0]].append(c[1])
            
        return coordinate_groups
    
    x_coordinate_groups = get_dic_from_coords(coords_top)
    y_coordinate_groups = get_dic_from_coords(coords_bottom)

    # print(x_coordinate_groups)
    # print(y_coordinate_groups)

    rectangles = []
    for key in x_coordinate_groups:

        while x_coordinate_groups[key]:
            top_left = [key,0]
            top_left[1] = min(x_coordinate_groups[key]) # znajdz najmniejszą wartość
            x_coordinate_groups[key].remove(top_left[1]) # usuń ją

            bottom_right = [key + template_width, 0]
            bottom_right[1] = min(y_coordinate_groups[key]) # znajdz najmniejszą wartość (bo jest najbliżej najniższej wartości top_left)
            y_coordinate_groups[key].remove(bottom_right[1]) # usuń ją
            bottom_right[1] += template_height

            # wiedząc że jak jest wartość top a następna jest bottom można je pogrupować (biorąc pod uwagę jeden rząd)
            rectangles.append((top_left[0], top_left[1], bottom_right[0], bottom_right[1]))

    return rectangles
    

def locate_areas(schedule_path, lesson_top_path_white, lesson_bottom_path_white, lesson_top_path_yellow, lesson_bottom_path_yellow, template_width=134, template_height=3):
    coords_top = locate_top_left_coords(schedule_path, lesson_top_path_white)
    coords_bottom = locate_top_left_coords(schedule_path, lesson_bottom_path_white)
    rectangles_tmp = get_rectangles_from_points(coords_top, coords_bottom, template_width, template_height)

    coords_top = locate_top_left_coords(schedule_path, lesson_top_path_yellow)
    coords_bottom = locate_top_left_coords(schedule_path, lesson_bottom_path_yellow)
    rectangles = get_rectangles_from_points(coords_top, coords_bottom, template_width, template_height)

    for rectangle in rectangles_tmp:
        rectangles.append(rectangle)

    # print(coords_top)
    # print(coords_bottom)

    schedule = cv2.imread(schedule_path)
    os.remove(schedule_path)

    file = open(str(schedule_path).replace(".png", "_coords.txt"), 'w')
    for rectangle in rectangles:
        tlx = rectangle[0] # top left x
        tly = rectangle[1] # top left y
        brx = rectangle[2] # bottom right x
        bry = rectangle[3] # bottom right y
        file.write( str(tlx) + ' ' + str(tly) + ' ' + str(brx+1) + ' ' + str(bry+1) + '\n\n' )
        cv2.rectangle(schedule, (tlx, tly), (brx, bry), (0,0,255), 1)

    file.close()
    # cv2.imwrite(str(schedule_path).replace(".png", "_graphic.png"), schedule)


def clear_from_graphic_and_coords_path(path):
    import os
    files = []
    for file in os.listdir(path):
        if str(file).find('_coords') != -1 or str(file).find('graphic') != -1:
            os.remove(os.path.join(path,file))





def main():
    # test_run()
    # kinda_working_run()
    tmp_top_white = r'src/top.png'
    tmp_bottom_white = r'src/bottom.png'
    tmp_top_yellow = r'src/top_col.png'
    tmp_bottom_yellow = r'src/bottom_col.png'

    th, tw = cv2.imread(tmp_top_white).shape[:-1]
    bh, bw = cv2.imread(tmp_bottom_white).shape[:-1]

    if tw != bw:
        # print("error1")
        exit(1)
    if th != bh:
        # print("error2")
        exit(1)
        
    th, tw = cv2.imread(tmp_top_yellow).shape[:-1]
    bh, bw = cv2.imread(tmp_bottom_yellow).shape[:-1]

    if tw != bw:
        # print("error3")
        exit(1)
    if th != bh:
        # print("error4")
        exit(1)

    # clear_from_graphic_and_coords_path('schedules')
    files = ext.get_dir_files('schedules')
    for file in files:
        # print(file)
        locate_areas(file, tmp_top_white, tmp_bottom_white, tmp_top_yellow, tmp_bottom_yellow);

if __name__ == '__main__':
    main()
