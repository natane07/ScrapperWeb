cd %USERPROFILE%\repos\ScrapperWeb\ScrapperWeb
gcc -Wall -mwindows -Iinclude -c main.c -o obj/main.o
gcc -Wall -mwindows -Iinclude -c src/app.c -o obj/app.o
gcc -Wall -mwindows -Iinclude -c src/file.c -o obj/file.o
gcc -Wall -mwindows -Iinclude -c src/info.c -o obj/info.o
gcc -Wall -mwindows -Iinclude -c src/list.c -o obj/list.o
gcc -Wall -mwindows -Iinclude -c src/menu.c -o obj/menu.o
gcc -Wall -mwindows -Iinclude -c src/parser.c -o obj/parser.o
gcc -Wall -mwindows -Iinclude -c src/utils.c -o obj/utils.o
gcc -Wall -mwindows -Iinclude -c src/json.c -o obj/json.o
gcc -Wall -mwindows -Iinclude -c src/jsmn.c -o obj/jsmn.o
gcc -Wall -mwindows -Iinclude -c src/scan.c -o obj/scan.o
gcc -Wall -mwindows -Iinclude -c src/article.c -o obj/article.o
gcc -Wall obj/main.o obj/app.o obj/file.o obj/info.o obj/list.o obj/menu.o obj/parser.o obj/utils.o obj/json.o obj/jsmn.o obj/scan.o obj/article.o -L"C:\Programs\MinGW\lib" lib/libcurl.a lib/libcurl.dll.a -o bin/scrapper.exe