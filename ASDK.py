import os, sys, json, ctypes, shutil, platform, zipfile, argparse

# TODO:
# Implement a simple versioning system!!!
# Implement a simple logger for the SDK!!! (consider rich? or just hook into the engine's?)

at_version:str='1.0.2024-alpha'
at_repo_dir:str='https://github.com/d34d0s/Anntwinetta'
at_releases_dir:str='https://github.com/d34d0s/Anntwinetta/releases/download/v{at_version}/Anntwinetta_{at_version}.zip'

def io_query(msg:str) -> str: return str(input(f'{msg}: '))

def load_DLL() -> bool:
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
Installation/Update System
"""
def install(args:argparse.Namespace) -> None:
    
    install_dir:str=io_query('Enter A Path For Install')
    if not os.path.exists(install_dir): os.mkdir(install_dir)

    if args.ver:
        at_version=args.ver
        print(f'Installing Anntwinetta v{at_version}')

        os.system(f'curl -L https://github.com/F4R4W4Y/Anntwinetta/releases/download/v{at_version}/Anntwinetta_{at_version}.zip -o {install_dir}/Anntwinetta_{at_version}.zip')
        shutil.unpack_archive(f'{install_dir}/Anntwinetta_{at_version}.zip', install_dir)
        os.remove(f'{install_dir}/Anntwinetta_{at_version}.zip')
        os.system(f'setx ATWIN_DIR {install_dir}\\Anntwinetta_{at_version}'); os.environ['ATWIN_DIR']=f'{install_dir}\\Anntwinetta_{at_version}'
        os.system(f'setx C_INCLUDE_PATH {os.environ.get('C_INCLUDE_PATH', '')}{install_dir}\\Anntwinetta_{at_version}\\engine\\headers;')

    elif args.repo:
        os.system(f'git clone -b {args.repo} https://github.com/F4R4W4Y/Anntwinetta.git {install_dir}')
        os.system(f'setx ATWIN_DIR {install_dir}'); os.environ['ATWIN_DIR']=f'{install_dir}'
        os.system(f'setx C_INCLUDE_PATH {os.environ.get('C_INCLUDE_PATH', '')}{install_dir}\\engine\\headers;')

    elif args.dev:
        if os.path.exists(install_dir):
            os.system(f'curl -L https://github.com/F4R4W4Y/Anntwinetta/releases/download/v{args.dev}/Anntwinetta_{args.dev}_devkit.zip -o {install_dir}/Anntwinetta_{args.dev}_devkit.zip')
            shutil.unpack_archive(f'{install_dir}/Anntwinetta_{args.dev}_devkit.zip', install_dir)
            os.remove(f'{install_dir}/Anntwinetta_{args.dev}_devkit.zip')
            os.system(f'setx ATWIN_DIR {install_dir}\\Anntwinetta_{args.dev}_devkit'); os.environ['ATWIN_DIR']=f'{install_dir}\\Anntwinetta_{args.dev}_devkit'
            os.system(f'setx C_INCLUDE_PATH {os.environ.get('C_INCLUDE_PATH', '')}{install_dir}\\Anntwinetta_{args.dev}_devkit\\engine\\headers;')

    build_windows()
    if load_DLL(): print(f'Anntwinetta Installed + Built Successfully At: {install_dir}')


"""
Build Systems
"""
def build_windows() -> None:
    print(f'\nBuilding Anntwinetta For Windows OS\n')
    
    o_files:str = ''
    c_files:list[str]=[]
    install_dir:str=os.environ.get('ATWIN_DIR', None); install_dir='\\'.join(install_dir.split('/'))

    build_dir:str=f'{install_dir}\\build'
    engine_dir:str=f'{install_dir}\\engine'
    vendor_dir:str=f'{engine_dir}\\vendor'
    
    if os.path.exists(f'{build_dir}\\bin\\Anntwinetta.dll'):
        os.system(f'del {build_dir}\\bin\\Anntwinetta.dll /Q')

    if not os.path.exists(f'{build_dir}'):
        os.mkdir(f'{build_dir}')
    if not os.path.exists(f'{build_dir}\\bin'):
        os.mkdir(f'{build_dir}\\bin')
    if not os.path.exists(f'{build_dir}\\lib'):
        os.mkdir(f'{build_dir}\\lib')

    for root, dirs, files in os.walk(f'{engine_dir}'):
        for cfile in files:
            if cfile.endswith('.c'):
                c_files.append([cfile, os.path.join(root, cfile)])

    for file, filePath in c_files:
        os.system(
            f'gcc '
            f'-c '
            f'{filePath} '
            f'-D_ATWIN_EXPORT_ '
            f'-D_ATWIN_WINDOWS_ '
            f'-o '
            f'{build_dir}\\bin\\{file.removesuffix('.c')}.o'
        )

    for root, dirs, files in os.walk(f'{build_dir}\\bin'):
        for ofile in files:
            o_files += f'{build_dir}\\bin\\{ofile}'+' '

    os.system(
        f'gcc '
        f'-shared '
        f'{o_files} '
        f'-lSDL2 '
        f'-lglfw3 '
        f'-luser32 '
        f'-lglew32 '
        f'-lopengl32 '
        f'-I{vendor_dir} '
        f'-L{vendor_dir}\\bin '
        f'-I{install_dir}\\engine '
        f'-o {build_dir}\\bin\\Anntwinetta.dll '
    )
    
    os.system(f'ar rcs {build_dir}\\lib\\libAnntwinetta.a {o_files}')
    os.system(f'del {build_dir}\\bin\\*.o /Q')
    os.system(f'xcopy {vendor_dir}\\bin {build_dir}\\bin /s /q')

    if load_DLL(): print(f'\nNative DLL/Archive Build Successful')

def build_project_windows() -> None:
    if load_DLL(): print(f'\nBuilding Anntwinetta Project For Windows OS')

    at_dir:str=os.environ.get('ATWIN_DIR', None); at_dir='\\'.join(at_dir.split('/'))

    engine_dir:str=f'{at_dir}\\engine'
    vendor_dir:str=f'{engine_dir}\\vendor'
    at_build_dir:str=f'{at_dir}\\build'
    
    build_dir:str=io_query('Enter A Path To A Source File/Directory')
    build_dir=build_dir.replace('/', '\\')
    if not os.path.exists(build_dir): os.mkdir(build_dir)
    if not os.path.exists(f'{build_dir}\\build'): os.mkdir(f'{build_dir}\\build')

    c_file_str:str=''
    for r, d, f in os.walk(build_dir):
        for c_file in f:
            if not c_file.endswith('.c'): continue
            c_file_str += os.path.join(r, c_file)

    os.system(
        f'gcc '
        f'{c_file_str} '
        f'-D_ATWIN_GL_ '
        f'-D_ATWIN_WINDOWS_ '
        f'-lSDL2 '
        f'-lglfw3 '
        f'-lglew32 '
        f'-lopengl32 '
        f'-lAnntwinetta '
        f'-I{engine_dir} '
        f'-I{vendor_dir} '
        f'-L{vendor_dir}\\bin '
        f'-L{at_build_dir}\\bin '
        f'-o {build_dir}\\build\\at_project '
    )

    os.system(f'xcopy {vendor_dir}\\bin\\ {build_dir}\\build /s /q')
    os.system(f'xcopy {at_build_dir}\\bin\\ {build_dir}\\build /s /q')

    print(f'\nWindows Project Built Successfully')

def build(args:argparse.Namespace) -> None:
    if args.engine:
        build_windows()
    if args.project:
        build_project_windows()

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
    build_cmd.add_argument('-engine', choices=['win', ], required=False, help='Target Engine Source Compilation')
    build_cmd.add_argument('-project', choices=['win', ], required=False, help='Target Engine Source Compilation')

    args=parser.parse_args()

    match args.command:
        case 'ldll': load_DLL()
        case 'build': build(args)
        case 'install': install(args)


if __name__ == '__main__': main()