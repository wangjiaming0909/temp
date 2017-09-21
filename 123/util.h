
ostream& operator<<(ostream& ios, voxel* v)
{
	ios << '(' << v->x << ',' << v->y << ',' << v->z << ',';
	if (v->ball != NULL)
		ios << v->ball->limit << ')';
	else
		ios << "null)";
	return ios;
}
#include <math.h>
inline double f_shape () // to randomly distribute the shape factors
{
/*	double f = rand()*0.048/RAND_MAX;
	if ( f < 0.0001)
		f=0.079;
	return f;*/
	
	double x1, x2, w, y;
	do{
		x1 = 2.0 * rand()/RAND_MAX - 1.0;
		x2 = 2.0 * rand()/RAND_MAX - 1.0;
		w = x1 * x1 + x2 * x2;
	} while (w >= 1.0);
	w = sqrt ( (-2.0 * log(w)) / w);
//	y = 0.0048 * (x1 * w + 5.0);
//	if (y < 0.0005)
//		y= 0.079;
	y = 0.00625 * (x1 * w + 5.0);
	if (y > 0.049)
		y= 0.0625;
	return y;
}
inline double makeradius1(double v, double r, int minr2) // return the Rright as radius
{


	return sqrt(v);
}


inline double makeradius2(double v, double r, int minr2) // return a radius randomly between (Rleft-1, Rright); but the minimum is no less than 0.1 times of a voxel size.
{

	v = sqrt(v);
	r = sqrt(r) - 1.0;
	if (r < 0.1)
		r = 0.1;
	return r + rand()*(abs(v-r))/RAND_MAX;
}

inline short sqrts(short n) // a faster square root calculation function
{
	if (n<1)        return 0;	// 359598
	else if (n<4)   return 1;	// 1386123
	else if (n<9)   return 2;	// 1019265
	else if (n<16)  return 3;	// 339721
	else if (n<25)  return 4;	// 120510
	else if (n<36)  return 5;	// 36767
	else if (n<49)  return 6;	// 13948
	else if (n<64)  return 7;	// 1471
	else if (n<81)  return 8;	// 477
	else if (n<100) return 9;
	else if (n<121) return 10;
	else if (n<144) return 11;
	else if (n<169) return 12;
	else if (n<196) return 13;
	else if (n<225) return 14;
	else if (n<256) return 15;
	else
	{
		short root = 16;
		root *= sqrts(n/(root*root));
		root += (n-root*root)/(3*root);
		root += (n-root*root)/(2*root+1);
		return root;
	}
}

inline double dist(voxel& i, voxel& j) // distance between two voxels
{
	return sqrt(double((i.x-j.x)*(i.x-j.x)+(i.y-j.y)*(i.y-j.y)+(i.z-j.z)*(i.z-j.z)));
}

inline unsigned long dist2(voxel& i, voxel& j) 
{
	return (i.x-j.x)*(i.x-j.x)+(i.y-j.y)*(i.y-j.y)+(i.z-j.z)*(i.z-j.z);
}

inline bool series(voxel& i, voxel& j, voxel& k, voxel& m) 
{
	double ang = fabs(((i.x-j.x)*(k.x-m.x)+(i.y-j.y)*(k.y-m.y)+(i.z-j.z)*(k.z-m.z))/dist(i,j)/dist(k,m));
	if (ang >= 0.70710678) 
		return true;
	else
		return false;
}

inline double relative(double R, double r, double d)
{
	return (R+r-d)*(R+r-d)*(d*d+2*d*(R+r)-3*(R-r)*(R-r))/(16*d*r*r*r);
}

class metaballcomparer
{
public:
	bool operator()(const voxel* a, const voxel* b) const
	{
		return (a->ball->r2) > (b->ball->r2);
	}
};



class porecomparer // prioritize the pore with its level number (generation number)
{
public:
	bool operator()(const voxel* a, const voxel* b) const
	{
		if (a->ball->r2 > b->ball->r2)
		{
			return true;
		}
		else if (a->ball->r2 == b->ball->r2)
		{
			if (a->ball->level < b->ball->level)
				return true;
			else
				return false;
		}
		else
		{
			return false;
		}
	}
};

class throatcomparer 
{
public:
	bool operator()(const voxel* a, const voxel* b) const
	{
		if (a->ball->level < b->ball->level)
		{
			return true;
		}
		else if (a->ball->level == b->ball->level)
		{
			if (a->ball->r2 > b->ball->r2)
				return true;
			else
				return false;
		}
		else
		{
			return false;
		}
	}
};

class markcomparer 
{
public:
	bool operator()(const voxel* a, const voxel* b) const
	{
		if (a->ball->level > b->ball->level)
		{
			return true;
		}
		else if (a->ball->level == b->ball->level)
		{
			if (a->ball->r2 > b->ball->r2)
				return true;
			else
				return false;
		}
		else
		{
			return false;
		}
	}
};
