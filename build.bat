cd %USERPROFILE%\repos\ScrapperWeb\ScrapperWeb
gcc -Wall -mwindows -Iinclude -c main.c -o obj/main.o
gcc -Wall -mwindows -Iinclude -c src/file.c -o obj/file.o
gcc -Wall -mwindows -Iinclude -c src/list.c -o obj/list.o
gcc -Wall -mwindows -Iinclude -c src/parser.c -o obj/parser.o
gcc -Wall -mwindows -Iinclude -c src/utils.c -o obj/utils.o
gcc -Wall -mwindows -Iinclude -c src/action.c -o obj/action.o
gcc -Wall -mwindows -Iinclude -c src/tache.c -o obj/tache.o
gcc -Wall -mwindows -Iinclude -c src/option.c -o obj/option.o
gcc -Wall -mwindows -Iinclude -c src/planificateur.c -o obj/planificateur.o
gcc -Wall -mwindows -Iinclude -c src/httpScrapper.c -o obj/httpScrapper.o

gcc -Wall obj/main.o obj/file.o obj/list.o obj/parser.o obj/utils.o obj/action.o obj/tache.o obj/option.o obj/planificateur.o obj/httpScrapper.o -L"C:\MinGW\lib" lib/libcurl.a lib/libcurl.dll.a -o bin/scrapper.exe