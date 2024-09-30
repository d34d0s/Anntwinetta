import os, sys, json, ctypes, shutil, platform, zipfile, argparse

# TODO:
# Implement a simple versioning system!!!
# Implement a simple logger for the SDK!!! (consider rich? or just hook into the engine's?)

at_version:str='1.0.2024-alpha'
at_repo_dir:str='https://github.com/F4R4W4Y/Anntwinetta'
at_releases_dir:str='https://github.com/F4R4W4Y/Anntwinetta/releases/download/v{at_version}/Anntwinetta_{at_version}.zip'

def query_stdin(msg:str) -> str: return str(input(f'{msg}: '))

def at_load_dll() -> bool:
    at_dir:str=os.environ.get('ATWIN_DIR', None)
    if at_dir and os.path.exists(f'{at_dir}\\build\\bin'):
        at_dir='\\'.join(at_dir.split('/'))
        try:
            sdl2lib = ctypes.CDLL(f'{at_dir}\\engine\\vendor\\bin\\SDL2.dll')
            anntlib = ctypes.CDLL(f'{at_dir}\\build\\bin\\Anntwinetta.dll')
        except (FileNotFoundError) as err: print(f'[ WARNING ] Anntwinetta DLL Not Yet Built!', err); return False
        return True
    else: print('Error Installing Environment Variables or Missing Engine Binaries!'); return False


"""
Installation/Update Systems
"""
def at_install(args:argparse.Namespace) -> None:
    
    install_dir:str=query_stdin('Enter A Path For Install')
    if not os.path.exists(install_dir): os.mkdir(install_dir)

    if args.ver:
        at_version=args.ver
        print(f'Installing Anntwinetta v{at_version}')

        os.system(f'curl -L https://github.com/F4R4W4Y/Anntwinetta/releases/download/v{at_version}/Anntwinetta_{at_version}.zip -o {install_dir}/Anntwinetta_{at_version}.zip')
        shutil.unpack_archive(f'{install_dir}/Anntwinetta_{at_version}.zip', install_dir)
        os.remove(f'{install_dir}/Anntwinetta_{at_version}.zip')
        os.system(f'setx at_DIR {install_dir}\\at_{at_version}'); os.environ['ATWIN_DIR']=f'{install_dir}\\at_{at_version}'
        if at_load_dll():
            print(f'Anntwinetta v{at_version} Installed Successfully At: {install_dir}')

    elif args.repo:
        os.system(f'git clone -b {args.repo} https://github.com/F4R4W4Y/Anntwinetta.git {install_dir}')
        os.system(f'setx at_DIR {install_dir}\\Anntwinetta'); os.environ['ATWIN_DIR']=f'{install_dir}\\Anntwinetta'
        if at_load_dll(): print(f'Anntwinetta Repo Cloned Successfully To: {install_dir}')

    elif args.dev:
        if os.path.exists(install_dir):
            os.system(f'curl -L https://github.com/F4R4W4Y/Anntwinetta/releases/download/v{args.dev}/Anntwinetta_{args.dev}_devkit.zip -o {install_dir}/Anntwinetta_{args.dev}_devkit.zip')
            shutil.unpack_archive(f'{install_dir}/Anntwinetta_{args.dev}_devkit.zip', install_dir)
            os.remove(f'{install_dir}/Anntwinetta_{args.dev}_devkit.zip')
        os.system(f'setx at_DIR {install_dir}'); os.environ['ATWIN_DIR']=f'{install_dir}'
        if at_load_dll(): print(f'Anntwinetta DevKit v{args.dev} Installed Successfully At: {install_dir}')


"""
Platform Detection
"""
mac_os:bool=False
linux_os:bool=False
windows_os:bool=True if os.getenv('SYSTEMROOT', None) else False
at_installed:bool=True if os.environ.get('ATWIN_DIR', None) else False
if not at_installed: print('[ ERROR ] Could Not Locate Anntwinetta Installation Directory!'); sys.exit()


"""
Build Systems
"""
def at_build_windows() -> None:
    print(f'\nBuilding Anntwinetta Native DLL For Windows OS\n')
    
    o_files:str = ''
    c_files:list[str]=[]
    at_dir:str=os.environ.get('ATWIN_DIR', None); at_dir='\\'.join(at_dir.split('/'))

    engine_dir:str=f'{at_dir}\\engine'
    build_dir:str=f'{at_dir}\\build'
    vendor_dir:str=f'{engine_dir}\\vendor'
    if os.path.exists(f'{build_dir}\\bin\\Anntwinetta.dll'): os.system(f'del {build_dir}\\bin\\Anntwinetta.dll /Q')

    if not os.path.exists(build_dir):
        os.mkdir(build_dir)
    if not os.path.exists(f'{build_dir}\\bin'):
        os.mkdir(f'{build_dir}\\bin')

    for r, _, f in os.walk(f'{engine_dir}'):
        for cfile in f:
            if cfile.endswith('.c'): c_files.append([cfile, os.path.join(r, cfile)])
    [ os.system(f'gcc -D_ATWIN_GL_ -D_ATWIN_WINDOWS_ -D_ATWIN_EXPORT_ -c {fp} -o {build_dir}\\bin\\{f.removesuffix('.c')}.o') for f, fp in c_files ]

    for r, _, f in os.walk(f'{build_dir}\\bin'):
        for ofile in f:
            o_files += f'{build_dir}\\bin\\{ofile}'+' '
    os.system(f'gcc -shared {o_files} -o {build_dir}\\bin\\Anntwinetta.dll -I{at_dir}\\engine -I{vendor_dir} -L{vendor_dir}\\bin -lSDL2 -lopengl32 -luser32')
    os.system(f'ar rcs {build_dir}\\lib\\libAnntwinetta.a {o_files}')
    os.system(f'del {build_dir}\\bin\\*.o /Q')
    os.system(f'xcopy {vendor_dir}\\bin {build_dir}\\bin /s /q')
    

    if at_load_dll(): print(f'\nNative DLL/Archive Build Successful')

def at_build_webassembly() -> None:
    print(f'\nBuilding Anntwinetta Web Binary!\n')
    
    o_files:str = ''
    c_files:list[str]=[]
    at_dir:str=os.environ.get('ATWIN_DIR', None); at_dir='\\'.join(at_dir.split('/'))

    engine_dir:str=f'{at_dir}\\engine'
    build_dir:str=f'{at_dir}\\build'
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

    o_files:str=''
    for f, p in c_files:
        o_file = f'{f.removesuffix('.c')}.o'
        o_files+=f'{build_dir}\\wasm\\{o_file} '
        emcc_command = (
            f'emcc --no-entry -g -c {p} -D_ATWIN_GL_ -D_ATWIN_WEB_ -o {build_dir}\\wasm\\{o_file}'
        ); os.system(emcc_command)

    emcc_command = (
        f'emar rcs {build_dir}\\lib\\libAnntwinettaWeb.a {o_files}'
    ); os.system(emcc_command); os.system(f'del {build_dir}\\wasm\\*.o /Q')

    print(f'\nWeb Build Successful')

def at_build_project_windows() -> None:
    if at_load_dll(): print(f'\nBuilding Project Windows Native')

    at_dir:str=os.environ.get('ATWIN_DIR', None); at_dir='\\'.join(at_dir.split('/'))

    engine_dir:str=f'{at_dir}\\engine'
    vendor_dir:str=f'{engine_dir}\\vendor'
    at_build_dir:str=f'{at_dir}\\build'
    
    build_dir:str=query_stdin('Enter A Path To A Source File/Directory')
    build_dir=build_dir.replace('/', '\\')
    if not os.path.exists(build_dir): os.mkdir(build_dir)
    if not os.path.exists(f'{build_dir}\\build'): os.mkdir(f'{build_dir}\\build')

    c_file_str:str=''
    for r, d, f in os.walk(build_dir):
        for c_file in f:
            if not c_file.endswith('.c'): continue
            c_file_str += os.path.join(r, c_file)

    os.system( f' gcc -D_ATWIN_GL_ -D_ATWIN_WINDOWS_ {c_file_str} -I{engine_dir} -I{vendor_dir} -L{at_build_dir}\\bin -L{vendor_dir}\\bin -lAnntwinetta -lSDL2 -lopengl32 -o {build_dir}\\build\\at_project ' )
    os.system( f'xcopy {vendor_dir}\\bin\\ {build_dir}\\build /s /q' )
    os.system( f'xcopy {at_build_dir}\\bin\\ {build_dir}\\build /s /q' )

    print(f'\nWindows Native Project Built Successfully')

def at_build_project_webassembly() -> None:
    if at_load_dll(): print(f'\nBuilding Project For Web')

    at_dir:str=os.environ.get('ATWIN_DIR', None); at_dir='\\'.join(at_dir.split('/'))

    engine_dir:str=f'{at_dir}\\engine'
    vendor_dir:str=f'{engine_dir}\\vendor'
    at_build_dir:str=f'{at_dir}\\build'
    
    build_dir:str=query_stdin('Enter A Path To A Source File/Directory')
    build_dir=build_dir.replace('/', '\\')
    if not os.path.exists(build_dir): os.mkdir(build_dir)
    if not os.path.exists(f'{build_dir}\\web_build'): os.mkdir(f'{build_dir}\\web_build')

    at_c_file_str:str=''
    for r, d, f in os.walk(engine_dir):
        for c_file in f:
            if not c_file.endswith('.c'): continue
            at_c_file_str += os.path.join(r, c_file) + ' '
    
    c_file_str:str=''
    for r, d, f in os.walk(build_dir):
        for c_file in f:
            if not c_file.endswith('.c'): continue
            c_file_str += os.path.join(r, c_file)

    emcc_command = (
        f'emcc '
        f'-Os '
        f'-Wall '
        f'-D_ATWIN_GL_ '
        f'-D_ATWIN_WEB_ '
        f'{c_file_str} '
        f'-o {build_dir}\\web_build\\at_game.html '
        f'-s USE_SDL=2 '
        f'-s FULL_ES3=1 '
        f'-s USE_WEBGL2=1 '
        f'-s NO_EXIT_RUNTIME=1 '
        f'-s MAX_WEBGL_VERSION=2 '
        f'-I{engine_dir}\\ '
        f'-L{at_build_dir}\\lib '
        f'{at_build_dir}\\lib\\libAnntwinettaWeb.a '
        f'--shell-file {at_build_dir}\\wasm\\shell.html '
    ); os.system(emcc_command);
    
    print(f'\nWeb Project Built Successfully')

def at_build(args:argparse.Namespace) -> None:
    if args.win:
        if 'engine' in args.win: at_build_windows()
        elif 'proj' in args.win: at_build_project_windows()
    elif args.web:
        if 'engine' in args.web: at_build_webassembly()
        elif 'proj' in args.web: at_build_project_webassembly()


"""
Entry Point
"""
def main() -> None:
    parser=argparse.ArgumentParser(description='~Anntwinetta SDK~')
    subparsers=parser.add_subparsers(dest='command', help='Sub-commands')

    ldll_cmd=subparsers.add_parser(name='ldll', help='Tests Anntwinetta\'s DLL by loading and initializing the engine')
    
    install_cmd=subparsers.add_parser(name='install', help='Install a tagged release of Lotus')
    install_cmd.add_argument('-ver', required=False, help='Install a specific version of Lotus')
    install_cmd.add_argument('-repo', required=False, help='Clone A Branch Of The Anntwinetta Repo')
    install_cmd.add_argument('-dev', required=False, help='Install a specific version of Anntwinetta\'s devkits')
    
    build_cmd=subparsers.add_parser(name='build', help='Build Anntwinetta or your own project')
    build_cmd.add_argument('-web', nargs=1, choices=['engine', 'proj'], required=False, help='Target Web for compilation')
    build_cmd.add_argument('-win', nargs=1, choices=['engine', 'proj'], required=False, help='Target Windows for compilation')

    args=parser.parse_args()

    match args.command:
        case 'ldll': at_load_dll()
        case 'build': at_build(args)
        case 'install': at_install(args)

if __name__ == '__main__': main()