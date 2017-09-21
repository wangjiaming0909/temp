class metaballspace
{
public:
	metaballspace(reference& r, config& c) : rf(r), cg(c) {}
	long paradoxremoveincludedball() //to remove the included maximal bals
	{
		//cout << "remove included balls...\n";
		//cout << "sorting...";
		voxel** tv = new voxel*[rf.porosity];//allocate memory for void voxels
		voxel** tp = tv;
		voxel* ti = rf.voxelspace;
		voxel* tend = rf.voxelspace+rf.porosity;
		while (ti<tend)
		{
			*tp++ = ti++;
		}
		sort(tv, tv+rf.porosity, metaballcomparer());
		cout << '\n';
		long nsize = 0;
		long ndel = 0;
		short x,y,z;
		short r,r2,limit,limit2;
		voxel** i = tv;
		voxel** end = tv+rf.porosity;
		while (i < end)
		{
			voxel* vi = *i;
			if (vi->ball == NULL)
			{
				++i;
				continue;
			}
			x = vi->x;
			y = vi->y;
			z = vi->z;
			r = vi->ball->r2;
			limit = vi->ball->limit;
			if (r==0)
				break;
			short ex, ey, ez;
			ex = sqrts(r);
			for (short a=-ex; a<=ex; ++a)
			{
				ey = sqrts(r-a*a);
				for (short b=-ey; b<=ey; ++b)
				{
					ez = sqrts(r-a*a-b*b);
					for (short c=-ez; c<=ez; ++c)
					{
						voxel* j = rf(x+a, y+b, z+c);
						if ((j != NULL) && (j->ball != NULL) && (j != vi)) //if find ball centers
						{
							r2 = j->ball->r2;
							limit2 = j->ball->limit;
							double R1 = sqrt(double(limit));
							double R2 = sqrt(double(r2));
							double R3 = sqrt(double(limit2));
							double D = sqrt(double(a*a+b*b+c*c));
							if ((D < (R1-R2)) || ((D < (R1+R2)) && (relative(R1, R3, D) > cg.relative))) // if the ball is included
							{
								delete j->ball;
								j->ball = NULL;
								++ndel;
							}
						}
					}
				}
			}
			++i;
			//if ((++nsize)%128==0)
				//cout << "\rround=" << nsize << " remove=" << ndel;
		}
		//cout << "\rround=" << nsize << " remove=" << ndel << " remained=" << rf.porosity-ndel << " balls\n";
		delete[] tv;
		rf.ballcount = rf.porosity-ndel;
		return rf.ballcount;
	}
	long search() //search  MBs at each voxel
	{
		metaball* pball;
		voxel* pv = rf.voxelspace;
		for (unsigned long i=0; i<rf.porosity; ++i)
		{
			pball = searchmetaball(pv->x, pv->y, pv->z);
			pv->ball = pball;
			++pv;
			//if (i%521 == 0)
				//cout << "\rfind " << i+1 << " balls";
		}
		//cout << "\rfind " << rf.porosity << " balls.\n";
		return rf.porosity;
	}
	metaball* searchmetaball(short i, short j, short k) 
	{
		short e;
		short e2;
		short mode;
		expandsearch(i, j, k, e, e2, mode); //along the 26 dirctions
		return shrinksearch(i, j, k, e, e2, mode); // check each voxel in the defined potential range
	}
	void expandsearch(short i, short j, short k, short& e, short& e2, short& mode)
	{
		short ep1 = 0;
		short ep2 = 0;
		short ep3 = 0;
		
// three types of directions according to the step speed
		
//		i++, j++, k++;
//		i++, j++, k--;
//		i++, j--, k++;
//		i++, j--, k--;
//		i--, j++, k++;
//		i--, j++, k--;
//		i--, j--, k++;
//		i--, j--, k--;
		while (1) 
		{
			++ep3;
			if (rf.issolid(i+ep3, j+ep3, k+ep3) == false)
			{
				if (rf.issolid(i+ep3, j+ep3, k-ep3) == false)
				{
					if (rf.issolid(i+ep3, j-ep3, k+ep3) == false)
					{
						if (rf.issolid(i+ep3, j-ep3, k-ep3) == false)
						{
							if (rf.issolid(i-ep3, j+ep3, k+ep3) == false)
							{
								if (rf.issolid(i-ep3, j+ep3, k-ep3) == false)
								{
									if (rf.issolid(i-ep3, j-ep3, k+ep3) == false)
									{
										if (rf.issolid(i-ep3, j-ep3, k-ep3) == false)
										{
											;
										}
										else
											break;
									}
									else
										break;
								}
								else
									break;
							}
							else
								break;
						}
						else
							break;
					}
					else
						break;
				}
				else
					break;
			}
			else
				break;
		}
		
//		i++, j++, k;
//		i++, j--, k;
//		i--, j++, k;
//		i--, j--, k;
//		i++, j, k++;
//		i++, j, k--;
//		i--, j, k++;
//		i--, j, k--;
//		i, j++, k++;
//		i, j++, k--;
//		i, j--, k++;
//		i, j--, k--;
		while (1) 
		{
			++ep2;
			if (rf.issolid(i+ep2, j+ep2, k) == false)
			{
				if (rf.issolid(i+ep2, j-ep2, k) == false)
				{
					if (rf.issolid(i-ep2, j+ep2, k) == false)
					{
						if (rf.issolid(i-ep2, j-ep2, k) == false)
						{
							if (rf.issolid(i+ep2, j, k+ep2) == false)
							{
								if (rf.issolid(i+ep2, j, k-ep2) == false)
								{
									if (rf.issolid(i-ep2, j, k+ep2) == false)
									{
										if (rf.issolid(i-ep2, j, k-ep2) == false)
										{
											if (rf.issolid(i, j+ep2, k+ep2) == false)
											{
												if (rf.issolid(i, j+ep2, k-ep2) == false)
												{
													if (rf.issolid(i, j-ep2, k+ep2) == false)
													{
														if (rf.issolid(i, j-ep2, k-ep2) == false)
														{
															;
														}
														else
															break;
													}
													else
														break;
												}
												else
													break;
											}
											else
												break;
										}
										else
											break;
									}
									else
										break;
								}
								else
									break;
							}
							else
								break;
						}
						else
							break;
					}
					else
						break;
				}
				else
					break;
			}
			else
				break;
		}
		
//		i++, j, k;
//		i--, j, k;
//		i, j++, k;
//		i, j--, k;
//		i, j, k++;
//		i, j, k--;
		while (1) 
		{
			++ep1;
			if (rf.issolid(i+ep1, j, k) == false)
			{
				if (rf.issolid(i-ep1, j, k) == false)
				{
					if (rf.issolid(i, j+ep1, k) == false)
					{
						if (rf.issolid(i, j-ep1, k) == false)
						{
							if (rf.issolid(i, j, k+ep1) == false)
							{
								if (rf.issolid(i, j, k-ep1) == false)
								{
									;
								}
								else
									break;
							}
							else
								break;
						}
						else
							break;
					}
					else
						break;
				}
				else
					break;
			}
			else
				break;
		}
		
		// the real smallest radius and mode
		if ((ep3*ep3*3) < (ep2*ep2*2))
		{
			e = short(ep3*1.732+0.5);
			e2 = ep3*ep3*3;
			mode = 3;
		}
		else
		{
			e = short(ep2*1.414+0.5);
			e2 = ep2*ep2*2;
			mode = 2;
		}
		
		if ((ep1*ep1) < e2)
		{
			e = ep1-1;
			e2 = ep1*ep1;
			mode = 1;
		}
		
		// keep the ball within the image boundary
		if (e>i)
		{
			e = i;
			e2 = (e+1)*(e+1);
		}
		if (e>j)
		{
			e = j;
			e2 = (e+1)*(e+1);
		}
		if (e>k)
		{
			e = k;
			e2 = (e+1)*(e+1);
		}
		if ((i+e)>=rf.x)
		{
			e = rf.x-i-1;
			e2 = (e+1)*(e+1);
		}
		if ((j+e)>=rf.y)
		{
			e = rf.y-j-1;
			e2 = (e+1)*(e+1);
		}
		if ((k+e)>=rf.z)
		{
			e = rf.z-k-1;
			e2 = (e+1)*(e+1);
		}
	}
	// this function is to find the real radius
	metaball* shrinksearch(short i, short j, short k, short &e, short& e2, short& mode)
	{
		metaball* pball = new metaball;
		if (e == 0) // lateral
		{
			pball->r2 = 0;
			pball->limit = 1;
			return pball;
		}
		if ((mode == 2) && (e == 1)) // diagonal
		{
			pball->r2 = 1;
			pball->limit = 2;
			return pball;
		}
		if ((mode == 3) && (e == 2)) // diametrical
		{
			pball->r2 = 2;
			pball->limit = 3;
			return pball;
		}
		
		// ex^2+ey^2+ez^2 <= e2
		bool bfind = false;
		short fr2 = 3*e*e; // minimal failure radii squre
		short sr2 = 0; // maximal sucessful radii sq.
		short ex, ey, ez;
		--e2; // squre radius is no more than e2
		ex = sqrts(e2);
		for (short a=-ex; a<=ex; ++a)
		{
			ey = sqrts(e2-a*a);
			for (short b=-ey; b<=ey; ++b)
			{
				ez = sqrts(e2-a*a-b*b);
				for (short c=-ez; c<=ez; ++c)
				{
					if (rf.issolid(i+a, j+b, k+c) == true) // find a failure voxel
					{
						bfind = true;
						if ((a*a+b*b+c*c) < fr2)
							fr2 = a*a+b*b+c*c;
					}
					else
					{
						if ((a*a+b*b+c*c) > sr2)
							sr2 = a*a+b*b+c*c;
					}
				}
			}
		}
		if (bfind) // there is a failure voxel. the radius of the maximal ball is less than fr2
		{
			short bfr2 = 0;
			--fr2; //square radius is no more than fr2
			ex = sqrts(fr2);
			for (short a=-ex; a<=ex; ++a)
			{
				ey = sqrts(fr2-a*a);
				for (short b=-ey; b<=ey; ++b)
				{
					ez = sqrts(fr2-a*a-b*b);
					for (short c=-ez; c<=ez; ++c)
					{
						if ((a*a+b*b+c*c) > bfr2)
							bfr2 = a*a+b*b+c*c;
					}
				}
			}
			pball->r2 = bfr2;
			pball->limit = fr2+1;
		}
		else // this is the case happening on the boundary; the sr2 defines the radius of MB
		{
			pball->r2 = sr2;
			pball->limit = e2+1;
		 }
		return pball;
	}
public:
	reference& rf;
	config& cg;
};
