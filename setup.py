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
    'name': 'ReFacE',
    'description': 'This project is my graduation project in computer vision. It\'s a system that recognizes users\'s face in a database.',
    'long_description':read('README'),
    'author': 'Lucas Luchiari',
    'url': 'https://github.com/lluchiari/ReFacE',
    'author_email': 'luchiari.lucas@gmail.com',
    'version': '0.1',
    'install_requires': ['nose >= 1.3.7',
                        'pip >= 10',
                        'numpy >= 1.14.3',
                        'opencv-python >= 3.4.0.12',
                        'reface >= 0.1',
                        'stereovision >= 1.0.4',
                        'virtualenv >= 15.2.0',
                        'simplejson'
                        ],
    'dependency_links': ['git+https://github.com/juancarlospaco/netpbm.git'],
    'packages': ['ReFacE', 'tests'],
    'scripts': ['bin/main']
}

setup(**config)
