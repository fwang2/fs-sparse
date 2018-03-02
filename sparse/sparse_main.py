#
# Copyright (c) 2018
#
# Feiyi Wang, Oak Ridge National Laboratory
#
# This is the main program that leverage the extension module generated
# and provide a more pythonic interface
#

from sparse._sparse import lib, ffi
import os


def error(path=None):
    errno = ffi.errno
    strerror = os.strerror(ffi.errno)
    if path:
        raise IOError(errno, strerror, path)
    else:
        raise IOError(errno, strerror)


def seek_hole(path):
    """ return offset of the first hole """
    fd = lib.open(path, lib.O_RDONLY)
    if fd == -1:
        error(path)
    ret = lib.lseek(fd, 0, lib.SEEK_HOLE)
    lib.close(fd)
    return ret


def get_extents(path):
    """ return a list of extents """
    fd = lib.open(path, lib.O_RDONLY)
    fsize = os.path.getsize(path)

    if fd == -1:
        error(path)

    offset = 0
    extents = []
    while True:
        beg = lib.lseek(fd, offset, lib.SEEK_DATA)
        if beg == -1:
            # there is a corner case of zero byte file
            # in this case, there is no valid extent we
            # can return, just []
            end = lib.lseek(fd, 0, lib.SEEK_HOLE)
            if end == 0: break
        else:
            end = lib.lseek(fd, beg, lib.SEEK_HOLE)
        extents.append((beg, end))
        if end >= fsize:
            break
        offset = end

    return extents


def is_sparse(path):
    """ return true/false on if this is a sparse file"""
    fsize = os.path.getsize(path)
    offset = seek_hole(path)
    if offset == fsize:
        return False
    else:
        return True
