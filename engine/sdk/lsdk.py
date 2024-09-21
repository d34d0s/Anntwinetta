import os, sys, json, ctypes, shutil, platform, zipfile, argparse

# TODO: Implement a simple logger for the SDK!!! (consider rich?)

lotus_version:str='1.0.2024-alpha'
lotus_repo_dir:str='https://github.com/F4R4W4Y/Lotus'
lotus_releases_dir:str='https://github.com/F4R4W4Y/Lotus/releases/download/v{lotus_version}/Lotus_{lotus_version}.zip'

def query_stdin(msg:str) -> str: return str(input(f'{msg}: '))

def lotus_load_dll() -> bool:
    lotus_dir:str=os.environ.get('LOTUS_DIR', None)
    if lotus_dir and os.path.exists(f'{lotus_dir}\\build\\bin'):
        lotus_dir='\\'.join(lotus_dir.split('/'))
        try:
            lotuslib = ctypes.CDLL(f'{lotus_dir}\\build\\bin\\Lotus.dll')
        except (FileNotFoundError) as err: print(f'[ WARNING ] Lotus Engine DLL Not Yet Built!', err); return False
        
        lotus_init=lotuslib.lotus_init
        lotus_init.argtypes=None
        lotus_init.restype=None
        
        lotus_exit=lotuslib.lotus_exit
        lotus_exit.argtypes=None
        lotus_exit.restype=None
        
        lotus_get_ver=lotuslib.lotus_get_ver
        lotus_get_ver.argtypes=None
        lotus_get_ver.restype=ctypes.c_char_p

        lotus_init()
        print(lotus_get_ver())
        lotus_exit()
        return True
    else: print('Error Installing Environment Variables or Missing Engine Binaries!'); return False

"""
Installation/Update Systems
"""
def lotus_install(args:argparse.Namespace) -> None:
    
    install_dir:str=query_stdin('Enter A Path For Install')
    if not os.path.exists(install_dir): os.mkdir(install_dir)

    if args.ver:
        lotus_version=args.ver
        print(f'Installing Lotus v{lotus_version}')

        os.system(f'curl -L https://github.com/F4R4W4Y/Lotus/releases/download/v{lotus_version}/Lotus_{lotus_version}.zip -o {install_dir}/Lotus_{lotus_version}.zip')
        shutil.unpack_archive(f'{install_dir}/Lotus_{lotus_version}.zip', install_dir)
        os.remove(f'{install_dir}/Lotus_{lotus_version}.zip')
        os.system(f'setx LOTUS_DIR {install_dir}\\Lotus_{lotus_version}'); os.environ['LOTUS_DIR']=f'{install_dir}\\Lotus_{lotus_version}'
        if lotus_load_dll():
            print(f'Lotus v{lotus_version} Installed Successfully At: {install_dir}')

    elif args.repo:
        os.system(f'git clone -b {args.repo} https://github.com/F4R4W4Y/Lotus.git {install_dir}')
        os.system(f'setx LOTUS_DIR {install_dir}\\Lotus'); os.environ['LOTUS_DIR']=f'{install_dir}\\Lotus'
        if lotus_load_dll(): print(f'Lotus Engine Repo Cloned Successfully To: {install_dir}')

    elif args.dev:
        if os.path.exists(install_dir):
            os.system(f'curl -L https://github.com/F4R4W4Y/Lotus/releases/download/v{args.dev}/Lotus_{args.dev}_devkit.zip -o {install_dir}/Lotus_{args.dev}_devkit.zip')
            shutil.unpack_archive(f'{install_dir}/Lotus_{args.dev}_devkit.zip', install_dir)
            os.remove(f'{install_dir}/Lotus_{args.dev}_devkit.zip')
        os.system(f'setx LOTUS_DIR {install_dir}'); os.environ['LOTUS_DIR']=f'{install_dir}'
        if lotus_load_dll(): print(f'Lotus DevKit v{args.dev} Installed Successfully At: {install_dir}')


"""
Platform Detection
"""
mac_os:bool=False
linux_os:bool=False
windows_os:bool=True if os.getenv('SYSTEMROOT', None) else False
lotus_installed:bool=True if os.environ.get('LOTUS_DIR', None) else False
if not lotus_installed: print('[ ERROR ] Could Not Locate Lotus Engine Installation Directory!'); sys.exit()


"""
Build Systems
"""
def lotus_build_windows() -> None:
    print(f'\nBuilding Lotus Engine Native DLL For Windows OS\n')
    
    o_files:str = ''
    c_files:list[str]=[]
    lotus_dir:str=os.environ.get('LOTUS_DIR', None); lotus_dir='\\'.join(lotus_dir.split('/'))

    engine_dir:str=f'{lotus_dir}\\engine'
    build_dir:str=f'{lotus_dir}\\build\\'
    vendor_dir:str=f'{engine_dir}\\vendor'
    if os.path.exists(f'{build_dir}\\bin\\Lotus.dll'): os.system(f'del {build_dir}\\bin\\Lotus.dll /Q')

    if not os.path.exists(build_dir):
        os.mkdir(build_dir)
    if not os.path.exists(f'{build_dir}\\bin'):
        os.mkdir(f'{build_dir}\\bin')

    for r, _, f in os.walk(engine_dir):
        for cfile in f:
            if cfile.endswith('.c'): c_files.append([cfile, os.path.join(r, cfile)])
    [ os.system(f'gcc -D_LOTUS_GL_ -D_LOTUS_WINDOWS_ -D_LOTUS_EXPORT_ -c {fp} -o {build_dir}\\bin\\{f.removesuffix('.c')}.o') for f, fp in c_files ]

    for r, _, f in os.walk(f'{build_dir}\\bin'):
        for ofile in f:
            o_files += f'{build_dir}\\bin\\{ofile}'+' '
    os.system(f'gcc -shared {o_files} -o {build_dir}\\bin\\Lotus.dll -I{lotus_dir}\\engine -I{vendor_dir} -L{vendor_dir}\\bin -lSDL2 -lopengl32 -luser32')
    os.system(f'del {build_dir}\\bin\\*.o /Q')

    if lotus_load_dll(): print(f'\nNative DLL Build Successful')

def lotus_build_webassembly() -> None:
    print(f'\nBuilding Lotus Engine Web Native Binary!\n')
    
    o_files:str = ''
    c_files:list[str]=[]
    lotus_dir:str=os.environ.get('LOTUS_DIR', None); lotus_dir='\\'.join(lotus_dir.split('/'))

    engine_dir:str=f'{lotus_dir}\\engine'
    build_dir:str=f'{lotus_dir}\\build\\'
    vendor_dir:str=f'{engine_dir}\\vendor'
    if not os.path.exists(build_dir):
        os.mkdir(build_dir)
    if not os.path.exists(f'{build_dir}\\wasm'):
        os.mkdir(f'{build_dir}\\wasm')

    for r, _, f in os.walk(engine_dir):
        if 'ext' in _: _.remove('ext')
        if 'obj_temp' in r: continue
        for cfile in f:
            if cfile.endswith('.c'): c_files.append([cfile, os.path.join(r, cfile)])
    
    cstr:str=''
    for arr in c_files:
        cstr += f'{arr[1]} '

    emcc_command = (
        f'emcc {cstr} '
        f'-g '  # embed debug symbols into .wasm
        f'-lm ' # math lib
        f'-D_LOTUS_GL_ '
        f'-D_LOTUS_WASM_ '
        f'-o {build_dir}\\wasm\\lotus.js '
        f'-s USE_SDL=2 '
        f'-s USE_WEBGL2=1 '  # enable WebGL 2 support
        f'-s FULL_ES3=1 '    # full WebGL ES3 support
        f'-s MAX_WEBGL_VERSION=2 '  # ensure WebGL 2 compatibility
        # f'--preload-file {asset_dir} '  # preload some assets
        f'--no-entry '
    ); os.system(emcc_command)

    print(f'\nNative Web Build Successful')

def lotus_build_project() -> None: raise NotImplementedError

def lotus_build(args:argparse.Namespace) -> None:
    if args.win: lotus_build_windows()
    elif args.web: lotus_build_webassembly()


"""
Entry Point
"""
def main() -> None:
    parser=argparse.ArgumentParser(description='Lotus SDK')
    subparsers=parser.add_subparsers(dest='command', help='Sub-commands')

    ldll_cmd=subparsers.add_parser(name='ldll', help='Tests a Lotus DLL by loading and initializing the engine')
    
    install_cmd=subparsers.add_parser(name='install', help='Install a tagged release of Lotus')
    install_cmd.add_argument('-ver', required=False, help='Install a specific version of Lotus')
    install_cmd.add_argument('-repo', required=False, help='Clone A Branch Of The Lotus Engine Repo')
    install_cmd.add_argument('-dev', required=False, help='Install a specific version of Lotus\' devkits')
    
    build_cmd=subparsers.add_parser(name='build', help='Build Lotus Engine or your own project')
    build_cmd.add_argument('-win', nargs=1, choices=['dll'], required=False, help='Target Windows for compilation')
    build_cmd.add_argument('-web', nargs=1, choices=['wasm'], required=False, help='Target Windows for compilation')

    args=parser.parse_args()

    match args.command:
        case 'ldll': lotus_load_dll()
        case 'build': lotus_build(args)
        case 'install': lotus_install(args)

if __name__ == '__main__': main()