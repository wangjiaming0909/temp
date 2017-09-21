all: linux

win: ppd.exe porenet.exe

linux: ppd porenet

linux-x64: ppd-x64 porenet-x64

porenet.exe: porenet.cpp os.h config.h filecache.h dataloader.h reference.h util.h metaball.h network.h
	@cl /nologo /EHsc /Ox porenet.cpp /link -LARGEADDRESSAWARE
	@del *.obj

ppd.exe: ppd.cpp os.h filecache.h dataloader.h config.h
	@cl /nologo /EHsc /Ox ppd.cpp
	@del *.obj

porenet: porenet.cpp os.h config.h filecache.h dataloader.h reference.h util.h metaball.h network.h
	g++ -O4 -mtune=i686 -march=i686 -s -fomit-frame-pointer porenet.cpp -o porenet -static
	rm -f *.o

porenet-x64: porenet.cpp os.h config.h filecache.h dataloader.h reference.h util.h metaball.h network.h
	g++ -O4 -mtune=opteron -march=opteron -s -fomit-frame-pointer porenet.cpp -o porenet -static
	rm -f *.o
	
ppd: ppd.cpp os.h filecache.h dataloader.h config.h
	g++ -O4 -mtune=i686 -march=i686 -s -fomit-frame-pointer ppd.cpp -o ppd -static
	rm -f *.o

ppd-x64: ppd.cpp os.h filecache.h dataloader.h config.h
	g++ -O4 -mtune=opteron -march=opteron -s -fomit-frame-pointer ppd.cpp -o ppd -static
	rm -f *.o