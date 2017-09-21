class dataloader
{
public:
	virtual ~dataloader() {}
	virtual bool open(const char* file) = 0;
	virtual bool read() = 0;
	string filename;
	short x, y, z;
	double precision;
};

class micro_ct_loader : public dataloader
{
public:
	virtual bool open(const char* file)
	{
		fp = fopen(file, "rb");
		if (fp == NULL)
			return false;
		filename = file;
		if (data != NULL)
			delete[] data;
		data = new char[4194304];
		long len = fread(data, sizeof(char), 4194304, fp);
		end = data+len;
		pt = data;
		//filter out the first four lines
		long na = 0;
		while (na != 4)
		{
			if (*pt == 0x0a)
				++na;
			++pt;
		}
		return true;
	}
	virtual bool read()
	{
		if (pt < end)
		{
			while (*pt < 0x30 || *pt > 0x39)
				++pt;
			bool v = (*pt == 0x30) ? false : true;
			pt += 2;
			return v;
		}
		else if (fp != NULL)
		{
			long len = fread(data, sizeof(char), 4194304, fp);
			end = data+len;
			pt = data;
			if (len < 4194304)
			{
				fclose(fp);
				fp = NULL;
			}
			return read();
		}
		else
		{
			return true;
		}
	}
	virtual ~micro_ct_loader()
	{
		if (data != NULL)
			delete[] data;
		if (fp != NULL)
			fclose(fp);
	}
	micro_ct_loader() : data(NULL), end(NULL), pt(NULL), fp(NULL) {}
private:
	char* data;
	char* end;
	char* pt;
	FILE* fp;
};

class raw_loader : public dataloader
{
public:
	virtual bool open(const char* file)
	{
		fp = fopen(file, "rb");
		if (fp == NULL)
			return false;
		filename = file;
		if (data != NULL)
			delete[] data;
		data = new char[4194304];
		long len = fread(data, sizeof(char), 4194304, fp);
		end = data+len;
		pt = data;
		return true;
	}
	virtual bool read()
	{
		if (pt < end)
		{
			while (*pt < 0x30 || *pt > 0x39)
				++pt;
			bool v = (*pt == 0x30) ? false : true;
			pt += 2;
			return v;
		}
		else if (fp != NULL)
		{
			long len = fread(data, sizeof(char), 4194304, fp);
			end = data+len;
			pt = data;
			if (len < 4194304)
			{
				fclose(fp);
				fp = NULL;
			}
			return read();
		}
		else
		{
			return true;
		}
	}
	virtual ~raw_loader()
	{
		if (data != NULL)
			delete[] data;
		if (fp != NULL)
			fclose(fp);
	}
	raw_loader() : data(NULL), end(NULL), pt(NULL), fp(NULL) {}
private:
	char* data;
	char* end;
	char* pt;
	FILE* fp;
};

class binary_loader : public dataloader
{
public:
	virtual bool open(const char* file)
	{
		fp = fopen(file, "rb");
		if (fp == NULL)
			return false;
		filename = file;
		if (data != NULL)
			delete[] data;
		data = new char[4194304];
		long len = fread(data, sizeof(char), 4194304, fp);
		end = data+len;
		pt = data;
		return true;
	}
	virtual bool read()
	{
		if (pt < end)
		{
			bool v = (*pt == 0x0) ? false : true;
			++pt;
			return v;
		}
		else if (fp != NULL)
		{
			long len = fread(data, sizeof(char), 4194304, fp);
			end = data+len;
			pt = data;
			if (len < 4194304)
			{
				fclose(fp);
				fp = NULL;
			}
			return read();
		}
		else
		{
			return true;
		}
	}
	virtual ~binary_loader()
	{
		if (data != NULL)
			delete[] data;
		if (fp != NULL)
			fclose(fp);
	}
	binary_loader() : data(NULL), end(NULL), pt(NULL), fp(NULL) {}
private:
	char* data;
	char* end;
	char* pt;
	FILE* fp;
};
