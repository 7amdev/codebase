@ECHO OFF
SetLocal EnableDelayedExpansion

SET current_dir=%~dp0
SET root_dir=
FOR %%G IN ("%~dp0..") DO SET "root_dir=%%~fG"
SET build_folder_name=build
SET build_dir=%current_dir%%build_folder_name%

@REM ECHO ROOT_DIR:    %root_dir%
@REM ECHO CURRENT_DIR: %current_dir%

IF NOT EXIST %build_dir% MKDIR %build_folder_name%
PUSHD %build_dir%
cl /TC /Zi /I "%root_dir%" ../tests.c ../t_dynamic_array.c ../t_linked_list.c ../t_queue.c ../t_stack.c /link /nologo /out:tests.exe
@REM link main.obj /out:main.exe
POPD