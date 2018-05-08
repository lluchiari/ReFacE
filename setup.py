try:
    from setuptools import setup
except ImportError:
    from distutils.core import setup

config = {
    'description': 'This project is my graduation project in computer vision. It\'s a system that recognizes users\'s face in a database.',
    'author': 'Lucas Luchiari',
    'url': 'https://github.com/lluchiari/ReFacE',
    'author_email': 'luchiari.lucas@gmail.com',
    'version': '0.1',
    'install_requires': ['nose'],
    'packages': ['ReFacE'],
    'scripts': [],
    'name': 'ReFacE'
}

setup(**config)
