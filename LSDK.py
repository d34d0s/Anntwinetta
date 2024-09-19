import os, sys, shutil, argparse, sqlite3, ctypes

def exit_sdk() -> None:
    # backup project/config db [ local/CSP ]
    sys.exit()

def ext_init() -> None: ...
def lotus_init() -> bool:
    lotus_dir:str=os.environ.get('LOTUS_DIR', None)
    if lotus_dir and os.path.exists(f'{lotus_dir}\\bin'):
        lotus_dir='\\'.join(lotus_dir.split('/'))
        try:
            lotuslib = ctypes.CDLL(f'{lotus_dir}\\bin\\Lotus.dll')
        except (FileNotFoundError) as err: print(f'[ WARNING ] Lotus Engine DLL Not Yet Built!'); return True
        
        lotusInit=lotuslib.lotusInit
        lotusInit.argtypes=None
        lotusInit.restype=None
        
        lotusExit=lotuslib.lotusExit
        lotusExit.argtypes=None
        lotusExit.restype=None
        
        lotusGetVersion=lotuslib.lotusGetVersion
        lotusGetVersion.argtypes=None
        lotusGetVersion.restype=ctypes.c_char_p

        lotusInit()
        print(lotusGetVersion())
        lotusExit()
        return True
    else: print('Error Installing Configuring Lotus Environment Variables or Missing The Bin Directory!'); return False

def ext_update() -> None: ...
def lotus_update() -> None: ...

def ext_install() -> None: ...
def lotus_install(args) -> None:
    ipath:str=input('Target Install Directory: ')
    if not os.path.exists(ipath): os.mkdir(ipath)
    print(f'Installing Lotus Engine\n')

    if args.ver:
        os.system(f'curl -L https://github.com/F4R4W4Y/Lotus/releases/download/v{args.ver}/Lotus_{args.ver}.zip -o {ipath}/Lotus_{args.ver}.zip')
        shutil.unpack_archive(f'{ipath}/Lotus_{args.ver}.zip', ipath)
        os.remove(f'{ipath}/Lotus_{args.ver}.zip')
        os.system(f'setx LOTUS_DIR {ipath}/Lotus_{args.ver}'); os.environ['LOTUS_DIR']=f'{ipath}/Lotus_{args.ver}'
        if lotus_init():
            print(f'Lotus v{args.ver} Installed Successfully At: {ipath}')

    elif args.ext: print('Installing Lotus Extension!')
    elif args.latest: print('Installing Lotus\'s Latest Tagged Release!')

    elif args.repo:
        os.system(f'git clone -b {args.repo} https://github.com/F4R4W4Y/Lotus.git {ipath}')
        os.system(f'setx LOTUS_DIR {ipath}/Lotus'); os.environ['LOTUS_DIR']=f'{ipath}/Lotus'
        if lotus_init():
            print(f'Lotus Engine Repo Cloned Successfully To: {ipath}')

    elif args.dev:
        if os.path.exists(ipath):
            os.system(f'curl -L https://github.com/F4R4W4Y/Lotus/releases/download/v{args.dev}/Lotus_{args.dev}_devkit.zip -o {ipath}/Lotus_{args.dev}_devkit.zip')
            shutil.unpack_archive(f'{ipath}/Lotus_{args.dev}_devkit.zip', ipath)
            os.remove(f'{ipath}/Lotus_{args.dev}_devkit.zip')
        os.system(f'setx LOTUS_DIR {ipath}/Lotus_{args.dev}_devkit'); os.environ['LOTUS_DIR']=f'{ipath}/Lotus_{args.dev}_devkit'
        if lotus_init():
            print(f'Lotus DevKit v{args.dev} Installed Successfully At: {ipath}')

def lotus_build_ext() -> None: ...

# TODO: Finish This To Begin Final Round Of Testing Before LSDK 1.0!
def lotus_build_proj(args) -> None:
    if not os.path.exists(args.proj): print('[ ERROR ] Unable To Locate Project Source Files!'); return
    lotus_dir:str=os.environ.get('LOTUS_DIR', None)
    if not lotus_dir: print('[ ERROR ] Could Not Locate Lotus Engine Installation Directory!'); return

    print(f'\nBuilding Engine Entry-Point')
    ext_str:str=''
    def add_ext(estr, e): estr+=f'-l{e} '; return estr
    [ ext_str:=add_ext(ext_str, e) for e in str(input('Project Extension Names or\'d together (ext1|ext2...): ')).split('|') ]
    # xcopy engine bin dir to project bin dir
    os.system(f'gcc {args.proj} -I{lotus_dir}\\engine\\headers -I{lotus_dir}\\ext\\headers -L{lotus_dir}\\lib -L{lotus_dir}\\ext\\lib -lLotus -lglfw3 -lglew32 -lopengl32 {ext_str} -o {lotus_dir}\\bin\\main.exe')
    print(f'\nEngine Entry-Point Built Successfully')

def lotus_build_native_static() -> None:
    lotus_dir:str=os.environ.get('LOTUS_DIR', None)
    if not lotus_dir: print('[ ERROR ] Could Not Locate Lotus Engine Installation Directory!'); return
    lotus_dir='\\'.join(lotus_dir.split('/'))

    print(f'\nBuilding Lotus Engine Native Archive For Windows OS\n')
    OBJ_FILE_STR:str = ''
    SRC_FILES:list[str]=[]
    if not os.path.exists(f'{lotus_dir}\\obj_temp'): os.mkdir(f'{lotus_dir}\\obj_temp')

    for r, _, f in os.walk(lotus_dir):
        if 'ext' in _: _.remove('ext')
        if 'obj_temp' in r: continue
        for cfile in f:
            if '.c' in cfile and 'main' not in cfile: SRC_FILES.append([cfile, os.path.join(r, cfile)])
    [ os.system(f'gcc -c {fp}  -o {lotus_dir}\\obj_temp\\{f.removesuffix('.c')}.o') for f, fp in SRC_FILES ]

    for r, _, f in os.walk(f'{lotus_dir}\\obj_temp'):
        for ofile in f:
            OBJ_FILE_STR += f'{lotus_dir}\\obj_temp\\{ofile}'+' '
    os.system(f'ar rcs {lotus_dir}\\lib\\libLotus.a {OBJ_FILE_STR}')
    os.system(f'del {lotus_dir}\\obj_temp /S /Q'); os.rmdir(f'{lotus_dir}\\obj_temp')
    print(f'\nNative Archive Build Successful')

def lotus_build_native_dynamic() -> None:
    lotus_dir:str=os.environ.get('LOTUS_DIR', None)
    if not lotus_dir: print('[ ERROR ] Could Not Locate Lotus Engine Installation Directory!'); return
    lotus_dir='\\'.join(lotus_dir.split('/'))
    
    print(f'\nBuilding Lotus Engine Native DLL For Windows OS\n')
    OBJ_FILE_STR:str = ''
    SRC_FILES:list[str]=[]
    if not os.path.exists(f'{lotus_dir}\\obj_temp'): os.mkdir(f'{lotus_dir}\\obj_temp')

    for r, _, f in os.walk(lotus_dir):
        if 'ext' in _: _.remove('ext')
        if 'obj_temp' in r: continue
        for cfile in f:
            if '.c' in cfile and 'main' not in cfile: SRC_FILES.append([cfile, os.path.join(r, cfile)])
    [ os.system(f'gcc -c {fp} -o {lotus_dir}\\obj_temp\\{f.removesuffix('.c')}.o -DLOTUS_EXPORT') for f, fp in SRC_FILES ]

    for r, _, f in os.walk(f'{lotus_dir}\\obj_temp'):
        for ofile in f:
            OBJ_FILE_STR += f'{lotus_dir}\\obj_temp\\{ofile}'+' '
    os.system(f'gcc -DLOTUS_EXPORT -shared {OBJ_FILE_STR} -o {lotus_dir}\\bin\\Lotus.dll -I{lotus_dir}\\engine\\headers -L{lotus_dir}\\bin -lglfw3 -lglew32 -lopengl32 -luser32')
    os.system(f'del {lotus_dir}\\obj_temp /S /Q'); os.rmdir(f'{lotus_dir}\\obj_temp')
    print(f'\nNative DLL Build Successful')

def lotus_build(args) -> None:
    if args.proj: lotus_build_proj(args)
    elif args.native:
        if 'lib' in args.native: lotus_build_native_static()
        elif 'dll' in args.native: lotus_build_native_dynamic()
        elif 'all' in args.native: lotus_build_native_static(); lotus_build_native_dynamic()
        else: print('Invalid Instruction Set!'); return

def main() -> None:
    parser=argparse.ArgumentParser(description='Lotus SDK')
    subparsers=parser.add_subparsers(dest='command', help='Sub-commands')

    exit_cmd=subparsers.add_parser(name='exit', help='Exit Lotus SDK')

    init_cmd=subparsers.add_parser(name='init', help='Init A Specified Target')
    update_cmd=subparsers.add_parser(name='update', help='Update A Specified Target')
    
    build_cmd=subparsers.add_parser(name='build', help='Build A Specified Target')
    build_cmd.add_argument('-proj', required=False, help='Clone A Branch Of The Lotus Engine Repo!')
    build_cmd.add_argument('-native', choices=['lib', 'dll', 'all'], nargs=1, required=False, help='Clone A Branch Of The Lotus Engine Repo!')
    
    install_cmd=subparsers.add_parser(name='install', help='Install A Specified Target')
    install_cmd.add_argument('-repo', required=False, help='Clone A Branch Of The Lotus Engine Repo!')
    install_cmd.add_argument('-ver', required=False, help='Install The Specified Tagged Lotus Release!')
    install_cmd.add_argument('-dev', required=False, help='Install The Specified Tagged Lotus DevKit Release!')
    install_cmd.add_argument('-latest', required=False, help='Install The Latest Tagged Release Of Lotus Engine!')
    install_cmd.add_argument('-ext', choices=[ 'TinyCubes' ], required=False, help='Install The Latest Tagged Release Of The Specified Lotus Extension!')

    # parse the arguments
    args=parser.parse_args()

    match args.command:
        case 'exit':
            print('Exit Command!\n')
            exit_sdk()

        case 'init': print('Init Command!\n'); lotus_init()
        case 'update': print('Update Command!\n')
        
        case 'build':
            print('Build Command!\n')
            lotus_build(args)
        
        case 'install':
            print('Install Command!\n')
            lotus_install(args)
            
def main2() :
    db = sqlite3.connect('.\\lext.db')
    extension_table = db.execute('select * from lext')
    print(extension_table.fetchall())

if __name__ == '__main__': main()