@echo off
rem Written by H. Roumani in 2005 (www.cs.yorku.ca/~roumani)
g77 -ffree-form %1.for -o%1.exe ..\mine\*.o %LIBRARY_PATH%\..\..\SLATEC\lib\libSLATEC.a 
