set filename=%1
echo %filename%
%filename%_gen.exe
%filename%.exe
%filename%_trau.exe
fc /w %filename%.out %filename%.ans
