class readcache
{
public:
	bool open(const char* file)
	{
		fp = fopen(file, "rb");
		if (fp == NULL)
			return false;
		else
			return true;
	}
	template <typename T>
	bool read(T& dat)
	{
		return read(reinterpret_cast<char*>(&dat), sizeof(T));
	}
	bool read(char* dat, unsigned int size)
	{
		if (end == NULL)
			return false;
		if ((p+size) > end)
		{
			int cur = end-p;
			memcpy(dat, p, cur);
			int len;
			len = fread(buf, 1, 4194304, fp);
			if (len == 0)
			{
				end = NULL;
				return false;
			}
			p = buf;
			end = buf + len;
			return read(dat+cur, size-cur);
		}
		memcpy(dat, p, size);
		p += size;
		return true;
	}
	readcache() : fp(NULL)
	{
		buf = new char[4194304];
		p = buf;
		end = buf;
	}
	~readcache()
	{
		if (fp)
			fclose(fp);
		delete[] buf;
	}
private:
	FILE* fp;
	char* buf;
	char* p;
	char* end;
};

class writecache
{
public:
	bool open(const char* file)
	{
		fp = fopen(file, "wb");
		if (fp == NULL)
			return false;
		else
			return true;
	}
	template <typename T>
	bool write(T& dat)
	{
		return write(reinterpret_cast<const char*>(&dat), sizeof(T));
	}
	bool write(const char* dat, unsigned int size)
	{
		if ((p+size) > end)
		{
			fwrite(buf, 1, p-buf, fp);
			p = buf;
			if (size >= 1048576)
			{
				fwrite(dat, 1, size, fp);
				return true;
			}
		}
		memcpy(p, dat, size);
		p += size;
		return true;
	}
	writecache() : fp(NULL)
	{
		buf = new char[4194304];
		p = buf;
		end = buf + 4194304;
	}
	~writecache()
	{
		if (p > buf)
			fwrite(buf, 1, p-buf, fp);
		fclose(fp);
		delete[] buf;
	}
private:
	FILE* fp;
	char* buf;
	char* p;
	char* end;
};
