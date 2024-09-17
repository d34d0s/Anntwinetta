import os, sys, shutil

class LotusBuildSys:
    version:str='1.0.2024'
    _bsysversion:str='1.0.0'
    
    def __init__(self) -> None:
        ...

    def build(self, target:str="native") -> None:
        match target.lower():
            case "web": self._build_web()
            case "entry": self._build_entry()
            case "native": self._build_native()
            case "web|entry": self._build_web(); self._build_entry()
            case "native|entry": self._build_native(); self._build_entry()

    def _build_entry(self) -> None:
        print(f'\nBuilding Engine Entry-Point | Lotus Engine v{self.version}\n')
        filepath = 'main.c'
        os.system(f'gcc {filepath} -Lbin -Llib -lglfw3 -lglew32 -lopengl32 -lLotus -o bin\\main.exe')
        print(f'\nEngine Entry-Point Built Successfully | Lotus Engine v{self.version}\n')

    def _build_web(self) -> None:
        print(f'\nBuilding Lotus Engine For The Web | Lotus Engine v{self.version}\n')

    def _build_native(self) -> None:
        print(f'\nBuilding Lotus Engine Native For Windows OS | Lotus Engine v{self.version}\n')
        OBJ_FILE_STR:str = ''
        SRC_FILES:list[str]=[]

        if not os.path.exists('./obj_temp'): os.mkdir('./obj_temp')

        for r, _, f in os.walk(os.getcwd()):
            if 'obj_temp' in r: continue
            for cfile in f:
                if '.c' in cfile and '_main' not in cfile: SRC_FILES.append([cfile, os.path.join(r, cfile)])
        [ os.system(f'gcc -c {fp} -o .\\obj_temp\\{f.removesuffix('.c')}.o -DLOTUS_EXPORT') for f, fp in SRC_FILES ]

        for r, _, f in os.walk('./obj_temp'):
            for ofile in f:
                OBJ_FILE_STR += f'./obj_temp/{ofile}'+' '
        os.system(f'ar rcs ./lib/libLotus.a {OBJ_FILE_STR}')
        
        os.system(f'gcc -DLOTUS_EXPORT -shared {OBJ_FILE_STR} -o ./bin/Lotus.dll -Icore -Iplatform -Ibackend -Lbin -lglfw3 -lglew32 -lopengl32 -luser32')

        os.system('del obj_temp /S /Q'); os.rmdir('obj_temp')
        print(f'\nNative Build Successful | Lotus Engine v{self.version}')
LBS:LotusBuildSys=LotusBuildSys()
print(f"[ Lotus Engine v{LBS.version} | Build System v{LBS._bsysversion} ]\n")
print("Target An Instruction Set (-n/native, -w/web):", end=" ")
LBS.build(str(input()))