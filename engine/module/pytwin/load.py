import os, sys, ctypes as c

def load_DLL() -> c.CDLL | None:
    at_dir:str=os.environ.get('ATWIN_DIR', None)
    if at_dir and os.path.exists(f'{at_dir}\\build\\bin'):
        at_dir='\\'.join(at_dir.split('/'))
        try:
            sdl2Lib = c.CDLL(f'{at_dir}\\engine\\vendor\\bin\\SDL2.dll')
            return c.CDLL(f'{at_dir}\\build\\bin\\Anntwinetta.dll')
        except (FileNotFoundError) as err:
            print(f'[ WARNING ] Anntwinetta DLL Not Yet Built!', err)
            return None
    else:
        print('Error Installing Environment Variables or Missing Engine Binaries!')
        return None


def configure_DLL(lib:c.CDLL) -> c.CDLL | None:
    lib.atInit.restype=None
    lib.atInit.argtypes=[None,]

    return lib


