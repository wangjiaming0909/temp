#include "os.h"
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

#include "config.h"
#include "dataloader.h"
#include "filecache.h"

struct segment
{
	short end;
	short length;
};

int usage()
{
	cout << "usage: ppd config ...\n";
	return 1;
}

bool preprocess(const char* file)
{
	config cfg;
	dataloader* loader;
	if (cfg.load(file))
	{
		cfg.dump();
		if (cfg.datatype == MICROCTDATA)
			loader = new micro_ct_loader;
		else if (cfg.datatype == BINARYDATA)
			loader = new binary_loader;
		else
			loader = new raw_loader;
		string datfile = cfg.filename + ".dat";
		string ppdfile = cfg.filename + ".ppd";
		if (loader->open(datfile.c_str()))
		{
			writecache cache;
			if (cache.open(ppdfile.c_str()))
			{
				cache.write("PPD");
				cache.write(cfg.x);
				cache.write(cfg.y);
				cache.write(cfg.z);
				cache.write(cfg.precision);
				segment* seg = new segment[cfg.x];
				short cnt = 0;
				unsigned long porosity = 0;
				for (short z=0; z<cfg.z; ++z)
				{
					for (short y=0; y<cfg.y; ++y)
					{
						memset(seg, 0, sizeof(segment)*cfg.x);
						cnt = 0;
						for (short x=0; x<cfg.x; ++x)
						{
							if (!loader->read())
							{
								++porosity;
								if ((seg[cnt].length != 0) && (x > (seg[cnt].end+1)))
									++cnt;
								seg[cnt].end = x;
								seg[cnt].length++;
							}
						}
						if (seg[cnt].length != 0)
							++cnt;
						cache.write(cnt);
						for (short i=0; i<cnt; ++i)
						{
							short start = seg[i].end+1-seg[i].length;
							cache.write(start);
							cache.write(seg[i].length);
						}
					}
					cout << '\r' << int((z+1.0)*100/cfg.z) << "% compeleted";
				}
				cache.write(porosity);
				delete[] seg;
				cout << '\n';
				return true;
			}
			else
			{
				cout << "preprocess: open " << ppdfile << " failed.\n";
				delete loader;
				return false;
			}
		}
		else
		{
			cout << "preprocess: open " << datfile << " failed.\n";
			delete loader;
			return false;
		}
	}
	else
	{
		cout << "preprocess: parser " << file << " failed.\n";
		return false;
	}
}

int main(int argc, char* argv[])
{
	cout << "pore network: data preprocess program\n";
	/*if (argc < 2)
		return usage();
	for (int i=1; i<argc; ++i)
	{
		if (preprocess(argv[i]) == false)
			return 1;
	}*/
	if (preprocess("input.dat") == false)
			return 1;
	return 0;
}
