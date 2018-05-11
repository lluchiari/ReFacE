import os
import sys
# from Thirdparty.netpbm.netpbm import ImgColor as pbm
from plyfile import PlyData, PlyElement

def loadImage(source):
    with open(source, 'r') as f:
        plydata = PlyData.read(f)
    print(pladata.elements[0].name)
    print(pladata.elements[1].name)




if __name__ == '__main__':
    # filepath = os.path.abspath(__file__) + "/../images/DataSets/00001_20061015_00418_neutral_face05.ply"
    # filepath = os.path.abspath('./')
    # filepath += '\\test.ply'
    # print (filepath)
    # print("Loadinf File: " + filepath)
    # file = open(filepath, 'r')
    # print(file.read())


    cur_path = os.path.dirname(__file__)
    print (cur_path)
    if sys.platform.startswith('win32')
        print (new_path)
        new_path = os.path.relpath('test.ply', cur_path)
    else
        print (new_path)
        new_path = os.path.relpath('./test.ply', cur_path)

    with open(new_path, 'r') as f:
        print(f.read(data))
    # loadImage(filepath)
