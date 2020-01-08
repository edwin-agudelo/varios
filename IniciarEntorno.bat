@echo off
REM *************************************************
REM
REM Script para inicializar ciertas rutas de 
REM para agregarlas al entorno
REM
REM Ing. Edwin A. Agudelo G.
REM 2020-01-08
REM
REM *************************************************
@setlocal enableextensions enabledelayedexpansion
echo Inicializando variables de entorno

set fileini=D:\Portables\bin\Entorno.ini
set opcion=%~1
set area=[%~2]
set key=rutabin
set derechos=Ing. Edwin Agudelo -- 2020
set currpath="%PATH%"

rem echo Prueba:!opcion!
rem echo Valor %currpath%

if [%opcion%]==[] (
    echo Listado de opciones:
    echo -p [ALIAS] : Alias de la ruta a agregar; recuerde que debe estar en el archivo [%fileini%]
    echo -l : Listado de alias
) else (
    if "%opcion%!" == "-l" (
        echo Listado de los alias en [%fileini%]
        findstr "descripcion [" %fileini%
    ) else (
        if "%opcion%" == "-p" (
            if "%area%" == "[]" (
                echo No se indico el alias, por favor valide
            ) else (
                echo Iniciando para el alias [%area%]
                set currarea=
                for /f "usebackq delims=" %%a in ("!fileini!") do (
                    set ln=%%a
                    rem echo !%ln!
                    if "x!ln:~0,1!"=="x[" (
                        set currarea=!ln!
                    ) else (
                        for /f "tokens=1,2 delims==" %%b in ("!ln!") do (
                            set currkey=%%b
                            set currval=%%c
                            if "x!area!"=="x!currarea!" if "x!key!"=="x!currkey!" (
                                echo Agregando a entorno [!currval!]
                                echo "%PATH%" | find "!currval!" >nul
                                if errorlevel 1 (
                                    if "%PATH:~-1%"==";" (
                                        rem echo "%PATH%!currval!"
                                        set currpath="%PATH%!currval!"
                                    ) else (
                                        set currpath="%PATH%;!currval!;"
                                    )
                                    echo Agregado
                                ) else (
                                    echo Ya existe el directorio en la variable PATH
                                )
                                rem if  "x!PATH:~0,1!"
                                rem echo Ultimo caracter: "%PATH:~-1%"
                                rem set PATH "%PATH%;!currval!"
                                rem echo El path: %currpath%
                            )
                        )
                    )
                )
            )
        ) else (
            echo Opcion [%opcion%] no valida
        )
    )
)
echo --------------------------------------
echo Por: %derechos%
echo --------------------------------------
REM setx PATH "%PATH%";
rem echo %PATH%
endlocal & set PATH=%currpath:"=%
