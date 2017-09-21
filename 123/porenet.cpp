/**************************************************************************************
Porenet extraction code version 0.1 - Dec. 2007                         
email: hu.dong03@imperial.ac.uk
Imperial College Consortium on Pore-Scale Modelling 
http://www3.imperial.ac.uk/earthscienceandengineering/research/perm/porescalemodelling
***************************************************************************************/

#include "os.h"
#include <cstdio>
#include <cmath>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

#include "config.h"
#include "filecache.h"
#include "dataloader.h"
#include "reference.h"
#include "metaball.h"
#include "network.h"
#include "character.h"

 struct segment_ppd
{
	short end;
	short length;
};


bool preprocess(const char* file)
{
	config cfg;
	dataloader* loader;
	if (cfg.load(file))
	{
		cfg.dump();
		cout<<"\n******************** Start ***********************\n";	
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
				segment_ppd* seg = new segment_ppd[cfg.x];
				short cnt = 0;
				unsigned long porosity = 0;
				for (short z=0; z<cfg.z; ++z)
				{
					for (short y=0; y<cfg.y; ++y)
					{
						memset(seg, 0, sizeof(segment_ppd)*cfg.x);
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
					//cout << '\r' << int((z+1.0)*100/cfg.z) << "% compeleted";
					
				}
				cout<<"\nData Preprocessing...";
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
int usage()
{
	cout << "usage: porenet config\n";
	return 1;
}

int main(int argc, char* argv[])
{

	
	long t1,t2,totaltime;
	t1=clock();

	cout<<"\n==================================================\n";
	cout<<"\n   Pore Structure Characteristic Code Version 1.0\n";
	cout<<"\n==================================================\n";



	if (preprocess("input.dat") == false)
	{
		cout<<"ppd error";
		exit(1);
	}
	

	srand(time(NULL));
	//cout << "\nPore Network Extraction Code Version 0.1\n";
	//if (argc < 2)
		//return usage();

	config cfg;
	cfg.load("input.dat");
	reference ref(cfg);


	//cout << "\nstep 1: load voxel data ...\n\n";
	cout << "\nData load ...\n\n";
	if (!ref.open("input.dat"))
		return 1;
	cout << "porosity: " << ref.porosity*100.0/ref.x/ref.y/ref.z << "%\n";

	ref.buildvoxelspace();

	//cout << "\nstep 2: search maximal balls ...\n\n";
	cout << "\nSearch and Move Maximal balls. \nPlease wait for a minute ...\n\n";
	metaballspace mbs(ref, cfg);
	mbs.search();
	ref.attachmetaball();
	mbs.paradoxremoveincludedball();


	//cout << "\nstep 3: connect maximal balls ...\n\n";
	cout << "\nPore and Throat Partition.\nThis may need some time, please wait...\n\n";
	porenetwork pn(ref, cfg);
	pn.connection();
	pn.marknullpore(); 
	pn.markthroat();
	pn.markpore(1); // define the direction for the inlets and outlets 1=x,2=y,3=z
	pn.connect_in_out(1);
	pn.valid();
	pn.setid();
	pn.calc(); 

	//ref.dumporiginalimage();

	ref.savelink1();
	ref.savelink2();
	ref.savenode1();
    ref.savenode2();

	character ch(cfg, ref);
	ch.saveporedtr();
	ch.savethroatdtr();
	ch.saveconnectdtr();
	ch.saveaspratio();
	/*ch.saveporefactor();
	ch.savethroatfactor();
	ch.savethroatlength();
	ch.saveporevolume();
	ch.savethroatvolume();*/


	t2=clock();
	totaltime=t2-t1;
	cout << "\nTotaltime: "<<totaltime/1000<<"s"<<endl;
	cout<<"********************* End ************************\n";


	return 0;
}
