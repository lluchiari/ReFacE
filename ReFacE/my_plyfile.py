import os
import sys
# from Thirdparty.netpbm.netpbm import ImgColor as pbm
from plyfile import PlyData, PlyElement

# Reference
# https://github.com/dranjan/python-plyfile

def loadImage(source):
    """ This function load the image and the datas into the library class """

    print("Loading Image on path: ", source)

    # Open and load to the class
    plydata = PlyData.read(source)

    print(plydata.elements[0].properties)
    # for elements in range(len(plydata.elements)):
    #     print("Elements Qty: ", plydata.elements[elements].count)
    #     print("Element: ", elements)
    #     for data in range(len(plydata.elements[elements].data)):
    #         print("Data[", data, "]: ", plydata.elements[elements].data[data)
    # print(len(plydata.elements[0].data))
    # print(len(plydata.elements[1].data))




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
