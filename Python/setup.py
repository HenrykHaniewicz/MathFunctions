import setuptools

with open( "README.md", "r" ) as fh:
    long_description = fh.read()

setuptools.setup(
    name="MathFunctions - Python",
    version="0.0.1a",
    author="Henryk Haniewicz",
    author_email="henryk.haniewicz@gmail.com",
    description="A small math package for my own amusement",
    long_description=long_description,
    url="https://github.com/HenrykHaniewicz/MathFunctions",
    packages=setuptools.find_packages(),
    classifiers=[
        'Development Status :: 2',
        'Intended Audience :: Developers',
        'License :: MIT',
        'Operating System :: OS Independent',
        'Programming Language :: Python',
    ],
)
