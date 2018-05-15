import pymesh
import os
import sys

# Reference
# http://pymesh.readthedocs.io/en/latest/installation.html#

def loadImage(source):
    """ This function load the image and the datas into the library class """

    print("Loading Image on path: ", source)
    mesh = pymesh.load_mesh(source)



if __name__ == '__main__':
    # Find the directory name
    cur_path = os.path.dirname(__file__)

    # Check if is windows or linux derectory pattern
    if sys.platform.startswith('win32'):
        new_path = cur_path + '\\test.ply'
    else:
        new_path = cur_path + '/test.ply'
    loadImage(new_path)
    # with open(new_path, 'r',  encoding="utf-8") as f:
    #     plydata = f.read()
    # print(plydata)
