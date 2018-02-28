#!/usr/bin/env python


from setuptools import setup, find_packages

VERSION = "0.1"
DESCRIPTION = "A wrapper for sparse file detection"

setup(
        name="pysparse",
        version=VERSION,
        description=DESCRIPTION,
        long_description=open("README.md", "rt").read(),
        author="Feiyi Wang",
        author_email="fwang2@ornl.gov",
        license="Apache",
        packages=find_packages(),
        platforms=['Linux'],
        install_requires=['cffi>=1.0.0'],
        setup_requires=['cffi>=1.0.0'],
        cffi_modules=['./sparse/sparse_build.py:ffibuilder']
)
