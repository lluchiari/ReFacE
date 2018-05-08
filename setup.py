import os
try:
    from setuptools import setup
except ImportError:
    from distutils.core import setup

# Utility function to read the README file.
# Used for the long_description.  It's nice, because now 1) we have a top level
# README file and 2) it's easier to type in the README file than to put a raw
# string in below ...
def read(fname):
    return open(os.path.join(os.path.dirname(__file__), fname)).read()

config = {
    'description': 'This project is my graduation project in computer vision. It\'s a system that recognizes users\'s face in a database.',
    'long_description':read('README'),
    'author': 'Lucas Luchiari',
    'url': 'https://github.com/lluchiari/ReFacE',
    'author_email': 'luchiari.lucas@gmail.com',
    'version': '0.1',
    'install_requires': ['nose'],
    'packages': ['ReFacE'],
    'scripts': ['bin/main.py'],
    'name': 'ReFacE'
}

setup(**config)
