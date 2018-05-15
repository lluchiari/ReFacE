import os
import sys

# TODO IN FUTURE
def givePath(path, default=None):
    """ This function returns a path ons the OS specific mode or None if wrong directory is indicated or path does't exist"""
    if sys.platform.startswith('win32'):
        new_path = cur_path + '\\test.ply'
    else:
        new_path = cur_path + '/test.ply'
