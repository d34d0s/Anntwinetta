"""
Official Python Wrapper For Anntwinetta Engine

Contributors: [
    d34d0s
]
"""

from .load import load_DLL as _load_DLL

import ctypes as c

_lib:c.CDLL = _load_DLL()

class DrawCallType:
    DRAW_CLEAR:int=     0x0000
    DRAW_MESH:int=      0x0001

class DrawCallMode:
    POINT_MODE:int=     0x0000  # GL equivalent
    LINE_MODE:int=      0x0001  # GL equivalent
    TRIANGLE_MODE:int=  0x0004  # GL equivalent

def init() -> int:
    return _lib.atInit()

def isRunning() -> int:
    return _lib.atRunning()

def exit() -> int:
    return _lib.atExit()

def pollEvents() -> None:
    _lib.atPollEvents()

def render() -> None:
    _lib.atRender()

def drawCall(type:DrawCallType, glMode:int) -> None:
    _lib.atDrawCall(type, glMode)

def drawCallSelect(type:DrawCallType, glMode:int, shader:int, vao:int, nVerts:int) -> None:
    _lib.atDrawCallSelect(type, glMode, shader, vao, nVerts)



