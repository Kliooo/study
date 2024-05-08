@echo off
chcp 65001 > log
del log

set MAIN=main
set TEMPLATES=templates
set EXE=example_static_array

:: .ii - файл после препроцессинга.
:: .s - ассемблерный код программы.
:: .o - объектный файл машинного кода (но не конечного вида) 
::		отдельной единицы трансляции.

g++ -E %TEMPLATES%.cpp -o %TEMPLATES%.ii
g++ -S %TEMPLATES%.ii -o %TEMPLATES%.s
as %TEMPLATES%.s -o %TEMPLATES%.o

g++ -E %MAIN%.cpp -o %MAIN%.ii
g++ -S %MAIN%.ii -o %MAIN%.s
as %MAIN%.s -o %MAIN%.o

g++ %TEMPLATES%.o %MAIN%.o -o %EXE%
