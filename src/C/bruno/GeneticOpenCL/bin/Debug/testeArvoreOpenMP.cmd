@echo off
setlocal enableextensions enabledelayedexpansion

SET parameter=popVal
SET Caminho=..\..

SET popVal=1024
SET seeds=14,15,16,17,18

break>resultFiles.txt
FOR %%i IN (%popVal%) DO (
	break>resultFiles_%%i.txt
	ECHO resultFiles_%%i.txt>>resultFiles.txt

	FOR %%j IN (%seeds%) DO (
		PUSHD %Caminho%
		make -f GeneticOpenCL.cbp.mak clean
		make -f GeneticOpenCL.cbp.mak NUM_INDIV=%%i SEED=%%j TWODEVICES=0 EVOLOCL=0 AVALOCL=1 EVOLOMP=1 AVALGPU=0 DIF_CONTEXT=0
		POPD

		for %%F in ("*.dat") do (
			SET nomeArquivo=%%~nF_ompCpu_seed_%%j_%parameter%_%%i.txt
			ECHO Extraindo dados para "!nomeArquivo!"
			ECHO !nomeArquivo!>>resultFiles_%%i.txt
			GeneticOpenCL.exe %%F>"Resultados\ompCpu\!nomeArquivo!"
		)
	)
)

PAUSE