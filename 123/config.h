#define MICROCTDATA 1
#define BINARYDATA 2
#define RAWDATA 3

class config
{
public:
	config() : valid(false), datatype(RAWDATA), failgo(true), precision(3), relative(0.95), minr2(2) {}
	bool load(const char* file)
	{
		char buf[1024];
		FILE* fp;
		fp = fopen(file, "r");
		if (fp == NULL)
			return false;
		while (fgets(buf, 1000, fp) != NULL)
		{
			if (buf[0]!='#' && buf[0] != '\n' && buf[0] != '\r')
			{
				char* p = strchr(buf, '\n');
				if (p == NULL)
					continue;
				*p = '\0';
				--p;
				if (*p == '\r')
				{
					*p = '\0';
					--p;
				}
				while (*p == ' ' || *p == '\t')
				{
					*p = '\0';
					--p;
				}
				p = strchr(buf, ':');
				if (p == NULL)
					continue;
				*p = '\0';
				++p;
				while (*p == ' ' || *p == '\t')
					++p;
				if (strcmp(buf, "datatype") == 0)
				{
					if (strcmp(p, "microct") == 0)
						datatype = MICROCTDATA;
					else if (strcmp(p, "binary") == 0)
						datatype = BINARYDATA;
					else
						datatype = RAWDATA;
				}
				else if (strcmp(buf, "datafile") == 0)
				{
					filename = p;
				}
				else if (strcmp(buf, "x") == 0)
				{
					x = atoi(p);
				}
				else if (strcmp(buf, "y") == 0)
				{
					y = atoi(p);
				}
				else if (strcmp(buf, "z") == 0)
				{
					z = atoi(p);
				}
				else if (strcmp(buf, "precision") == 0)
				{
					precision = atof(p);
				}
		
				else if (strcmp(buf, "minr2") == 0)
				{
					minr2 = atoi(p);
				}
			}
		}
		if (filename.size())
			valid = true;
		fclose(fp);
		return true;
	}
	void dump()
	{
		cout<<"\nData Information:\n";
        cout<<"-----------------------------------";
		cout << "\nDatatype: ";
		if (datatype == MICROCTDATA)
			cout << "Micro CT data";
		else if (datatype == BINARYDATA)
			cout << "Binary data";
		else
			cout << "Raw data";
		cout << "\nData File: " << filename << ".dat";
		cout << "\nData Size: " << x << ' ' << y << ' ' << z;
		cout << "\nData Resolution: " << precision << " um/pixel\n";
		cout<<"-----------------------------------\n";
	}
public:
	bool valid;
	bool failgo;
	short datatype;
	short x, y, z;
	short minr2;
	double precision;
	double relative;
	string filename;
};
