const long LEVEL_MAX = 0x7fffffff;

class metaball;
class block;

class voxel 
{
public:
	voxel() : x(-1), y(-1), z(-1), edge(0), ball(NULL), blk(NULL) {}
	~voxel();
public:
	short x, y, z; 
	short edge; 
	metaball* ball; 
	block* blk;
};

class block
{
public:
	block() : area(0), volumn(0) {}
	virtual ~block() {}
	virtual bool ispore() = 0;
	voxel* v;
	unsigned long id;
	unsigned long area;
	unsigned long volumn;
};

class poreblock: public block
{
public:
	poreblock() : edgeball(NULL), length(0) {}
	virtual ~poreblock() {}
	bool ispore() {return true;}
public:
	set<block*> throats;
	voxel* edgeball;
	unsigned long length;
};

class throatblock : public block
{
public:
	virtual ~throatblock() {}
	bool ispore() {return false;}
public:
	voxel* p1;
	voxel* p2;
	list<voxel*> chain;
};

class metaball 
{
public:
	metaball() : r2(-1), limit(0), level(LEVEL_MAX), pore(NULL), parent(NULL), blk(NULL) {}
	~metaball() { }
public:
	short r2; 
	short limit; 
	long level;
	voxel* pore; 
	voxel* parent; 
	block* blk; 
public:
	bool ismaster() 
	{
		if (level == 1) 
			return true;
		else
			return false;
	}
};

voxel::~voxel()
{
	if (ball != NULL)
		delete ball;
}

struct segment
{
	short start;
	short end;
	voxel* v;
};

struct segments
{
	short cnt;
	segment* s;
	bool* v;
	segments() : s(NULL), v(NULL) {}
	~segments()
	{
		if (s != NULL)
			delete[] s;
	}
};

#include "util.h"
#include <math.h>
#include <vector>

class reference
{
public:
	bool open(const char* file)
	{
		string ppdfile = cg.filename + ".ppd";
		readcache cache;
		if (!cache.open(ppdfile.c_str()))
		{
			string cmd = "ppd ";
			cmd += file;
			if (system(cmd.c_str()) != 0)
			{
				cout << "open preprocess data of " << cg.filename << " failed\n";
				return false;
			}
			if (!cache.open(ppdfile.c_str()))
			{
				cout << "open preprocess data of " << cg.filename << " failed\n";
				return false;
			}
		}
		char flag[4];
		cache.read(flag, 4);
		if (strcmp(flag, "PPD"))
		{
			cout << "open preprocess data of " << cg.filename << " failed\n";
			return false;
		}
		cache.read(x);
		cache.read(y);
		cache.read(z);
		cache.read(precision);
		seg = new segments*[z];
		for (int izz=0; izz<z; ++izz)
			seg[izz] = new segments[y];
		short cnt;
		for (short iz=0; iz<z; ++iz)
		{
			for (short iy=0; iy<y; ++iy)
			{
				cache.read(cnt);
				seg[iz][iy].cnt = cnt;
				if (cnt == 0)
					seg[iz][iy].s = NULL;
				else
				{
					seg[iz][iy].s = new segment[cnt];
					for (short ix=0; ix<cnt; ++ix)
					{
						short start;
						short len;
						cache.read(start);
						cache.read(len);
						seg[iz][iy].s[ix].start = start;
						seg[iz][iy].s[ix].end = start+len;
						seg[iz][iy].s[ix].v = NULL;
					}
				}
			}
			//cout << "\rloading " << (iz+1)*100/z << "%";
		}
		cache.read(porosity);
		//cout << "\rload " << x*y*z << " voxels.\n";

		return true;
	}
	voxel* operator()(short i, short j, short k)
	{
		if (i<0 || j<0 || k<0 || i>=x || j>=y || k>=z)
			return NULL;
		segments& s = seg[k][j];
		for (short p=0; p<s.cnt; ++p)
		{
			if (i>=s.s[p].start && i<s.s[p].end)
				return s.s[p].v+i-s.s[p].start;
		}
		return NULL;
	}

	
	bool issolid(short i, short j, short k)
	{
		if (i<0 || j<0 || k<0 || i>=x || j>=y || k>=z)
			return true;
		segments& s = seg[k][j];
		if (s.cnt == 0)
			return true;
		if (i < s.s[0].start)
			return true;
		for (short p=1; p<s.cnt; ++p)
		{
			if (i < s.s[p].start)
			{
				if (i < s.s[p-1].end)
					return false;
				else
					return true;
			}
		}
		if (i < s.s[s.cnt-1].end)
			return false;
		else
			return true;
	}
	bool isvalid(short i, short j, short k) 
	{
		if (i<0 || j<0 || k<0 || i>=x || j>=y || k>=z)
			return false;
		else
			return true;
	}
	void buildvoxelspace()
	{
		voxelspace = new voxel[porosity];
		voxel* p = voxelspace;
		for (short iz=0; iz<z; ++iz)
		{
			for (short iy=0; iy<y; ++iy)
			{
				segments& s = seg[iz][iy];
				for (short ix=0; ix<s.cnt; ++ix)
				{
					for (short i=s.s[ix].start; i<s.s[ix].end; ++i)
					{
						p->x = i;
						p->y = iy;
						p->z = iz;
						++p;
					}
				}
			}
		}
	}
	void attachmetaball()
	{
		voxel* p = voxelspace;
		for (short iz=0; iz<z; ++iz)
		{
			for (short iy=0; iy<y; ++iy)
			{
				segments& s = seg[iz][iy];
				for (short ix=0; ix<s.cnt; ++ix)
				{
					s.s[ix].v = p;
					p += s.s[ix].end - s.s[ix].start;
				}
			}
		}
	}
	reference(config& c) : cg(c), seg(NULL), voxelspace(NULL) {}
	~reference()
	{
		if (seg != NULL)
		{
			for (int iz=0; iz<z; ++iz)
				delete[] seg[iz];
			delete[] seg;
		}
		if (voxelspace != NULL)
			delete[] voxelspace;
	}


	void dumporiginalimage()
	{
		unsigned char* image = new unsigned char[x*y*z];
		memset(image, 0, x*y*z);
		for (short i=0; i<x; i++)
		{
			for (short j=0; j<y; j++)
			{
				for (short k=0; k<z; k++)
				{
					if (issolid(i, j, k) == false)
						image[i+x*(j+y*k)] = 1;
				}
			}
		}
		string fname = cg.filename + ".orig.dat";
		FILE* fp = fopen(fname.c_str(), "wb");
		fwrite(image, 1, x*y*z, fp);
		fclose(fp);
		delete[] image;
	}
	
	
	void savelink1()
	{

		
		string fname = cg.filename + "_link1.dat";
		FILE* fp = fopen(fname.c_str(), "w");
		fprintf(fp, "%6d\n", throats.size());
		
		
		for (list<throatblock*>::iterator li = throats.begin(); li != throats.end(); ++li)
		{
			long id1, id2;
			if ((*li)->p1 == (voxel*)(-1))
				id1 = -1;
			else if ((*li)->p1 == (voxel*)(0))
				id1 = 0;
			else
				id1 = (*li)->p1->blk->id;
			if ((*li)->p2 == (voxel*)(-1))
				id2 = -1;
			else if ((*li)->p2 == (voxel*)(0))
				id2 = 0;
			else
				id2 = (*li)->p2->blk->id;
			block* pb1 = NULL;
			block* pb2 = NULL;
			block* tb = (*li)->v->blk;
			if (id1 > 0)
				pb1 = (*li)->p1->blk;
			if (id2 > 0)
				pb2 = (*li)->p2->blk;
			
			double tlength = 0;
			double length = 0;
			double p1 = 0;
			double p2 = 0;
			
			list<voxel*>::iterator last = (*li)->chain.begin();
			list<voxel*>::iterator vi = last;
			for (++vi; vi != (*li)->chain.end(); ++vi)
			{
				double l = dist(**last, **vi);
				tlength += l;
				if (tb == pb2)
				{
					if ((*last)->blk == pb1)
						p1 += l;
					else if ((*vi)->blk == pb2)
						p2 += l;
					else
						length += l;
				}
				else
				{
					if ((*vi)->blk == pb2)
						p2 += l;
					else if ((*last)->blk == pb1)
						p1 += l;
					else
						length += l;
				}
				last = vi;
			}
			if (id1 < 1)
			{
				p2 += p1;
				if (p2 < 0.000001)
					p2 = 1;
				p1 = p2;
				length = sqrt(double((*li)->v->ball->limit));
			}
			if (id2 < 1)
			{
				p1 += p2;
				if (p1 < 0.000001)
					p1 = 1;
				p2 = p1;
				length = sqrt(double((*li)->v->ball->limit));
			}
			if (id1 > 0 && id2 > 0 && length < 0.000001)
			{
				length = 1;
				if (p2 > p1)
					p2 -= 1;
				else
					p1 -= 1;
			}
			if (tlength < 0.000001)
				tlength = 1;
			if ((*li)->volumn == 0)
				(*li)->volumn = 1;
			if ((*li)->area == 0)
				(*li)->area = 6;
			
			double radius2 = makeradius2((*li)->v->ball->limit, (*li)->v->ball->r2, cg.minr2);
			double t_shape1 = (*li)->volumn*length/(*li)->area/(*li)->area ;
			if (t_shape1 > 0.08)
				t_shape1 = 0.0796;
			double t_shape2 = f_shape();
			
			fprintf(fp, "%6d %6d %6d %E %E %E\n", (*li)->id, id1, id2, radius2*precision*0.000001, t_shape2, tlength*precision*0.000001);
			
		}
		
		fclose(fp);
	
	}

	void savelink2()
	{
				

		string fname = cg.filename + "_link2.dat";
		FILE* fp = fopen(fname.c_str(), "w");


		for (list<throatblock*>::iterator li = throats.begin(); li != throats.end(); ++li)
		{
			long id1, id2;
			if ((*li)->p1 == (voxel*)(-1))
				id1 = -1;
			else if ((*li)->p1 == (voxel*)(0))
				id1 = 0;
			else
				id1 = (*li)->p1->blk->id;
			if ((*li)->p2 == (voxel*)(-1))
				id2 = -1;
			else if ((*li)->p2 == (voxel*)(0))
				id2 = 0;
			else
				id2 = (*li)->p2->blk->id;
			block* pb1 = NULL;
			block* pb2 = NULL;
			block* tb = (*li)->v->blk;
			if (id1 > 0)
				pb1 = (*li)->p1->blk;
			if (id2 > 0)
				pb2 = (*li)->p2->blk;
			
			
			double length = 0;
			double tlength = 0;
			double p1 = 0;
			double p2 = 0;
			double pt1 = 0;
			double pt2 = 0;
			
			list<voxel*>::iterator last = (*li)->chain.begin();
			list<voxel*>::iterator vi = last;
			for (++vi; vi != (*li)->chain.end(); ++vi)
			{
				tlength +=1;
				double l = dist(**last, **vi);
				if (tb == pb2)
				{
					if ((*last)->blk == pb1)
						p1 += l;
					else if ((*vi)->blk == pb2)
						p2 += l;
					else
						length += l;
				}
				else
				{
					if ((*vi)->blk == pb2)
						p2 += l;
					else if ((*last)->blk == pb1)
						p1 += l;
					else
						length += l;
				}
				last = vi;
			}
			if (id1 < 1)
			{
				p2 += p1;
				if (p2 < 0.000001)
					p2 = 1;
				p1 = p2;
				length = sqrt(double((*li)->v->ball->limit));
			}
			if (id2 < 1)
			{
				p1 += p2;
				if (p1 < 0.000001)
					p1 = 1;
				p2 = p1;
				length = sqrt(double((*li)->v->ball->limit));
			}
			if (id1 > 0 && id2 > 0 && length < 0.000001)
			{
				length = 1;
				if (p2 > p1)
					p2 -= 1;
				else
					p1 -= 1;
			}
			if ((*li)->volumn == 0)
				(*li)->volumn = 1;
			if ((*li)->area == 0)
				(*li)->area = 6;
				
				if (id1 > 0 && id2 > 0)
				{
					tlength = dist (*((*li)->p1),*((*li)->p2));
					pt1 = dist (*((*li)->p1), *((*li)->v));
					pt2 = dist (*((*li)->p2), *((*li)->v));
					p1 = pt1 * (1 - 0.6 * sqrt(double((*li)->v->ball->limit)/(double((*li)->p1->ball->limit))));
//					p1 = sqrt (double((*li)->p1->ball->r2));
					if (p1<1)
						p1=1;
					p2 = pt2 * (1 - 0.6 * sqrt(double((*li)->v->ball->limit)/(double((*li)->p2->ball->limit))));
//					p2 = sqrt (double((*li)->p2->ball->r2));
					if (p2<1)
						p2=1;
					length = tlength - p1 -p2;
					
					if (length < 0.0000001)
						length =0.1;
				}

			fprintf(fp, "%6d %6d %6d %E %E %E %E %E\n", (*li)->id, id1, id2, p1*precision*0.000001, p2*precision*0.000001, length*precision*0.000001, (*li)->volumn*precision*0.000001*precision*0.000001*precision*0.000001, 0.0);
		}

		
		fclose(fp);
		
	}



void savenode1()
	{
		string fname = cg.filename + "_node1.dat";
		FILE* fp = fopen(fname.c_str(), "w");
		fprintf(fp, "%6d  %E  %E  %E\n", pores.size(), x*precision*0.000001, y*precision*0.000001, z*precision*0.000001);

		
		for (list<poreblock*>::iterator li = pores.begin(); li != pores.end(); ++li)
		{
			fprintf(fp, "%6d %E %E %E %3d", (*li)->id, (*li)->v->x*precision*0.000001, (*li)->v->y*precision*0.000001, (*li)->v->z*precision*0.000001, (*li)->throats.size());
			bool inlet = false;
			bool outlet = false;
			for (set<block*>::iterator bi = (*li)->throats.begin(); bi != (*li)->throats.end(); ++bi)
			{
				throatblock* tb = dynamic_cast<throatblock*>(*bi);
				if (tb->p1 == (*li)->v)
				{
					if (tb->p2 == (voxel*)(-1))
						inlet = true,  fprintf(fp, "\t%5d", -1);
					else if (tb->p2 == (voxel*)(0))
						outlet = true,  fprintf(fp, "\t%5d", 0);
					else
						fprintf(fp, "\t%5d", tb->p2->blk->id);
				}
				else
				{
					if (tb->p1 == (voxel*)(-1))
						inlet = true,  fprintf(fp, "\t%5d", -1);
					else if (tb->p1 == (voxel*)(0))
						outlet = true, fprintf(fp, "\t%5d", 0);
					else
						fprintf(fp, "\t%5d", tb->p1->blk->id);
				}
			}
			if (inlet)
				 fprintf(fp, "\t%5d", 1);
			else
				fprintf(fp, "\t%5d", 0);
			if (outlet)
				 fprintf(fp, "\t%5d", 1);
			else
				 fprintf(fp, "\t%5d", 0);

			for (set<block*>::iterator bj = (*li)->throats.begin(); bj != (*li)->throats.end(); ++bj)
			{
				throatblock* tb = dynamic_cast<throatblock*>(*bj);
				fprintf(fp, "\t%5d", tb->id);
			}
			fputs("\n", fp);
		}
		
		
		fclose(fp);
		
	}

	void savenode2()
	{
	

	

		string fname = cg.filename + "_node2.dat";
		FILE* fp = fopen(fname.c_str(), "w");

		

		for (list<poreblock*>::iterator li =pores.begin(); li != pores.end(); ++li)
		{
			if ((*li)->length == 0)
				(*li)->length = (*li)->v->ball->limit;
			
			double radius2 = makeradius2((*li)->v->ball->limit, (*li)->v->ball->r2, cg.minr2);
			double t_shape1 = (*li)->volumn*sqrt(double((*li)->length))*2/(*li)->area/(*li)->area;
			double t_shape2 = f_shape();

			fprintf(fp, "%6d %E %E %E %E\n", (*li)->id, (*li)->volumn*precision*0.000001*precision*0.000001*precision*0.000001, radius2*precision*0.000001, t_shape1, 0.0);
		}
		
		fclose(fp);
	}

public:
	short x, y, z;
	double precision;
	unsigned long porosity;
	unsigned long ballcount;
	config& cg;
	segments** seg;
	voxel* voxelspace;
	list<poreblock*> pores;
	list<throatblock*> throats;
};
