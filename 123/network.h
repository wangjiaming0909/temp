#define RATIO 0.7
class porenetwork
{
public:
	porenetwork(reference& r, config& c) : rf(r), cg(c) {}
	void connection() // start from the first mb to cluster them into pore-throat chains and eventually the pore network
	{
		//cout << "search connection...\n";
		//cout << "sorting...";
		voxel** tv = new voxel*[rf.ballcount];
		voxel** tp = tv;
		voxel* ti = rf.voxelspace;
		voxel* tend = rf.voxelspace+rf.porosity;
		while (ti<tend)
		{
			if (ti->ball != NULL)
				*tp++ = ti++;
			else
				ti++;
		}
		sort(tv, tv+rf.ballcount, metaballcomparer());
		cout << '\n';
		voxel** i;
		voxel** j = tv;
		voxel** end = tv+rf.ballcount;
		long cnt = 1; 
		long last_level;
		
		if (j < end)
		{
			count = 0;
			counter = 0;
			connectball(*j); // process the first ball
			last_level = (*j)->ball->level;
			++j;
			while (j < end)
			{
				i = j;
				if ((*i)->ball->r2 >= cg.minr2) // Only balls bigger than minr2 can be pores
				{
					++j;
					while (j < end)
					{
						if ((*j)->ball->r2 < (*i)->ball->r2)
							break;
						++j;
					}
					while (i < j)
					{
						//if ((cnt++)%128==0)
							//cout << "\rb:" << cnt;
						if (((*i)->ball->level != last_level) || ((*i)->ball->level == LEVEL_MAX))
						{
							sort(i, j, porecomparer()); // re-compare the priority (generation number) after each processing
						}
						connectball(*i);
						last_level = (*i)->ball->level;
						++i;
					}
				}
				else // only can be throats
				{
					j = end;
					while (i < j)
					{
						//if ((cnt++)%128==0)
							//cout << "\rb:" << cnt;
						if (((*i)->ball->level != last_level) || ((*i)->ball->level == LEVEL_MAX))
						{
							sort(i, j, throatcomparer()); //  re-compare the priority (generation number) after each processing
						}
						if ((*i)->ball->level != LEVEL_MAX)
						{
							connectball(*i);
							last_level = (*i)->ball->level;
							++i;
						}
						else
						{
							// considered as isolated small holes to be removed
							rf.ballcount -= j-i;
							while (i < j)
							{
								delete (*i)->ball;
								(*i)->ball = NULL;
								++i;
							}
						}
					}
				}
				//cout << "\rb:" << cnt << "\t\tt:" << count << "\t\ttr:" << counter << '\n';
			}
		}
	}
	void connectball(voxel* i)
	{
		short x,y,z,r,r2;
		x = i->x;
		y = i->y;
		z = i->z;
		r = i->ball->limit;
		if (i->ball->pore == NULL) // this is a pore. the generation number is 1
			i->ball->level = 1;
		// absorb 2R range balls
		short ex, ey, ez;
		ex = 2*sqrts(r);
		for (short a=-ex; a<=ex; ++a)
		{
			ey = sqrts(4*r-a*a);
			for (short b=-ey; b<=ey; ++b)
			{
				ez = sqrts(4*r-a*a-b*b);
				for (short c=-ez; c<=ez; ++c)
				{
					voxel* j = rf(x+a, y+b, z+c);
					if ((j != NULL) && (j->ball != NULL) && (j != i)) // ball centers are found
					{
						r2 = j->ball->limit;
						if (sqrt(double(a*a+b*b+c*c)) < (sqrt(double(r))+sqrt(double(r2)))) // balls are overlapped
						{
							if ((r >= r2) || (j->ball->r2 < cg.minr2)) // j will be absorbed (given a family name)
							{ 
								if (j->ball->pore != NULL) // if j has been absorbed, j defines a throat
								{
									
									if ((r > r2) || ((r == r2) && (i->ball->level <= j->ball->level)))
									{
										if ((j->ball->pore != i->ball->pore) && (j->ball->pore != i) && (i->ball->pore != j))
										{
											voxel* parent;
											voxel* iball;
											voxel* jball;
											if (i->ball->pore != NULL)
												iball = i->ball->pore;
											else
												iball = i;
											jball = j->ball->pore;
											block* iblk = iball->ball->blk;
											block* jblk = jball->ball->blk;
											block* tblk = j->ball->blk;
											poreblock* ipore;
											poreblock* jpore;
											throatblock* throat;
											if (iblk == NULL)
											{
												ipore = new poreblock;
												ipore->v = iball;
												rf.pores.push_front(ipore);
											}
											else
											{
												ipore = dynamic_cast<poreblock*>(iblk);
											}
											if (jblk == NULL)
											{
												jpore = new poreblock;
												jpore->v = jball;
												rf.pores.push_front(jpore);
											}
											else
											{
												jpore = dynamic_cast<poreblock*>(jblk);
											}
											// to check the key balls
											voxel* ivoxel = NULL;
											voxel* jvoxel = NULL;
											block* iblock;
											block* jblock;
											bool itype = true; // true && ivoxel==NULL means a new chain; true&&ivoxel!=NULL means an exisiting pore; false means an existing throat
											bool jtype = true;
											parent = i;
											while (parent != NULL)
											{
												iblock = parent->ball->blk;
												if (iblock != NULL)
												{
													ivoxel = parent;
													itype = iblock->ispore();
													break;
												}
												parent = parent->ball->parent;
											}
											parent = j;
											while (parent != NULL)
											{
												jblock = parent->ball->blk;
												if (jblock != NULL)
												{
													jvoxel = parent;
													jtype = jblock->ispore();
													break;
												}
												parent = parent->ball->parent;
											}
											if (itype == true)
											{
												if (ivoxel == NULL)
												{
													if (jtype == true)
													{
														if (jvoxel == NULL)
														{
															// new chain
															throat = new throatblock;
															throat->v = j;
															throat->p1 = iball;
															throat->p2 = jball;
															// throat->chain = iball .. j .. jball
															parent = i;
															while (parent != NULL)
															{
																throat->chain.push_front(parent);
																parent = parent->ball->parent;
															}
															parent = j;
															while (parent != NULL)
															{
																throat->chain.push_back(parent);
																parent = parent->ball->parent;
															}
															rf.throats.push_front(throat);
															ipore->throats.insert(throat);
															jpore->throats.insert(throat);
															
															double di = sqrt(double(iball->ball->limit));
															double dj = sqrt(double(jball->ball->limit));
															double dt = sqrt(double(j->ball->limit));
															double ratio;
															parent = i;
															while (parent != NULL)
															{
																if (iball->ball->limit > j->ball->limit) 
																{
																	ratio = (sqrt((double)parent->ball->limit)-dt) / (di-dt);
																}
																else 
																{
																	ratio = dist(*parent, *j) / dist(*iball, *j);
																}
																if (ratio > RATIO)
																{
																	parent->ball->blk = ipore;
																	parent->blk = ipore;
																}
																else
																{
																	parent->ball->blk = throat;
																	parent->blk = throat;
																}
																parent = parent->ball->parent;
															}
															j->ball->blk = throat;
															j->blk = throat;
															parent = j->ball->parent;
															while (parent != NULL)
															{
																if (jball->ball->limit > j->ball->limit) 
																{
																	ratio = (sqrt((double)parent->ball->limit)-dt) / (dj-dt);
																}
																else 
																{
																	ratio = dist(*parent, *j) / dist(*jball, *j);
																}
																if (ratio > RATIO)
																{
																	parent->ball->blk = jpore;
																	parent->blk = jpore;
																}
																else
																{
																	parent->ball->blk = throat;
																	parent->blk = throat;
																}
																parent = parent->ball->parent;
															}
															count++;//cout << '\n' << iball << jball << j;
														}
														else
														{
															// from j to i, it is a new chain; but there is an existing pore on j direction
															throat = new throatblock;
															throat->v = j;
															throat->p1 = iball;
															throat->p2 = jball;
															// throat->chain = iball .. j .. jball
															parent = i;
															while (parent != NULL)
															{
																throat->chain.push_front(parent);
																parent = parent->ball->parent;
															}
															parent = j;
															while (parent != NULL)
															{
																throat->chain.push_back(parent);
																parent = parent->ball->parent;
															}
															rf.throats.push_front(throat);
															ipore->throats.insert(throat);
															jpore->throats.insert(throat);
															
															double di = sqrt((double)iball->ball->limit);
															double dj = sqrt((double)jball->ball->limit);
															double dt = sqrt((double)j->ball->limit);
															double ratio;
															parent = i;
															while (parent != NULL)
															{
																if (iball->ball->limit > j->ball->limit) 
																{
																	ratio = (sqrt((double)parent->ball->limit)-dt) / (di-dt);
																}
																else 
																{
																	ratio = dist(*parent, *j) / dist(*iball, *j);
																}
																if (ratio > RATIO)
																{
																	parent->ball->blk = ipore;
																	parent->blk = ipore;
																}
																else
																{
																	parent->ball->blk = throat;
																	parent->blk = throat;
																}
																parent = parent->ball->parent;
															}
															if (j != jvoxel)
															{
																j->ball->blk = throat;
																j->blk = throat;
																parent = j->ball->parent;
																while (parent != NULL)
																{
																	if (parent == jvoxel)
																		break;
																	if (jball->ball->limit > j->ball->limit) 
																	{
																		ratio = (sqrt((double)parent->ball->limit)-dt) / (dj-dt);
																	}
																	else 
																	{
																		ratio = dist(*parent, *j) / dist(*jball, *j);
																	}
																	if (ratio > RATIO)
																	{
																		parent->ball->blk = jpore;
																		parent->blk = jpore;
																	}
																	else
																	{
																		parent->ball->blk = throat;
																		parent->blk = throat;
																	}
																	parent = parent->ball->parent;
																}
															}
															count++;//cout << '\n' << iball << jball << j;
														}
													}
													else
													{
														// i...new; j...existing throat
														throat = dynamic_cast<throatblock*>(jblock);
														
														int pc = 0;
														int tc = 0;
														bool findj = false;
														for (list<voxel*>::iterator li = throat->chain.begin(); li != throat->chain.end(); ++li)
														{
															if ((*li) == jvoxel)
															{
																findj = true;
																break;
															}
														}
														parent = jvoxel;
														while (parent != NULL)
														{
															block* b = parent->ball->blk;
															if (b != NULL)
															{
																if (b->ispore())
																	++pc;
																else
																	++tc;
															}
															parent = parent->ball->parent;
														}
														if (1) 
														{
															parent = jvoxel;
															while (parent != NULL)
															{
																parent->ball->blk = jpore;
																parent->blk = jpore;
																parent = parent->ball->parent;
															}
															
															throat = new throatblock;
															throat->v = j;
															throat->p1 = iball;
															throat->p2 = jball;
															// throat->chain = iball .. j .. jball
															parent = i;
															while (parent != NULL)
															{
																throat->chain.push_front(parent);
																parent = parent->ball->parent;
															}
															parent = j;
															while (parent != NULL)
															{
																throat->chain.push_back(parent);
																parent = parent->ball->parent;
															}
															rf.throats.push_front(throat);
															ipore->throats.insert(throat);
															jpore->throats.insert(throat);
														
															double di = sqrt((double)iball->ball->limit);
															double dj = sqrt((double)jball->ball->limit);
															double dt = sqrt((double)j->ball->limit);
															double ratio;
															parent = i;
															while (parent != NULL)
															{
																if (iball->ball->limit > j->ball->limit) 
																{
																	ratio = (sqrt((double)parent->ball->limit)-dt) / (di-dt);
																}
																else 
																{
																	ratio = dist(*parent, *j) / dist(*iball, *j);
																}
																if (ratio > RATIO)
																{
																	parent->ball->blk = ipore;
																	parent->blk = ipore;
																}
																else
																{
																	parent->ball->blk = throat;
																	parent->blk = throat;
																}
																parent = parent->ball->parent;
															}
															if (j != jvoxel)
															{
																j->ball->blk = throat;
																j->blk = throat;
																parent = j->ball->parent;
																while (parent != NULL)
																{
																	if (parent == jvoxel)
																		break;
																	if (jball->ball->limit > j->ball->limit) 
																	{
																		ratio = (sqrt((double)parent->ball->limit)-dt) / (dj-dt);
																	}
																	else 
																	{
																		ratio = dist(*parent, *j) / dist(*jball, *j);
																	}
																	if (ratio > RATIO)
																	{
																		parent->ball->blk = jpore;
																		parent->blk = jpore;
																	}
																	else
																	{
																		parent->ball->blk = throat;
																		parent->blk = throat;
																	}
																	parent = parent->ball->parent;
																}
															}
															count++;//cout << '\n' << iball << jball << j;
														}
														else
														{
															if (findj == true) 
															{
															}
															else
															{
															}
														}
													}
												}
												else
												{
													if (jtype == true)
													{
														if (jvoxel == NULL)
														{
															// i ... existing pore; j ... new
															throat = new throatblock;
															throat->v = j;
															throat->p1 = iball;
															throat->p2 = jball;
															// throat->chain = iball .. j .. jball
															parent = i;
															while (parent != NULL)
															{
																throat->chain.push_front(parent);
																parent = parent->ball->parent;
															}
															parent = j;
															while (parent != NULL)
															{
																throat->chain.push_back(parent);
																parent = parent->ball->parent;
															}
															rf.throats.push_front(throat);
															ipore->throats.insert(throat);
															jpore->throats.insert(throat);
													
															double di = sqrt((double)iball->ball->limit);
															double dj = sqrt((double)jball->ball->limit);
															double dt = sqrt((double)j->ball->limit);
															double ratio;
															if (i != ivoxel)
															{
																parent = i;
																while (parent != NULL)
																{
																	if (parent == ivoxel)
																		break;
																	if (iball->ball->limit > j->ball->limit) 
																	{
																		ratio = (sqrt((double)parent->ball->limit)-dt) / (di-dt);
																	}
																	else 
																	{
																		ratio = dist(*parent, *j) / dist(*iball, *j);
																	}
																	if (ratio > RATIO)
																	{
																		parent->ball->blk = ipore;
																		parent->blk = ipore;
																	}
																	else
																	{
																		parent->ball->blk = throat;
																		parent->blk = throat;
																	}
																	parent = parent->ball->parent;
																}
															}
															j->ball->blk = throat;
															j->blk = throat;
															parent = j->ball->parent;
															while (parent != NULL)
															{
																if (jball->ball->limit > j->ball->limit) 
																{
																	ratio = (sqrt((double)parent->ball->limit)-dt) / (dj-dt);
																}
																else 
																{
																	ratio = dist(*parent, *j) / dist(*jball, *j);
																}
																if (ratio > RATIO)
																{
																	parent->ball->blk = jpore;
																	parent->blk = jpore;
																}
																else
																{
																	parent->ball->blk = throat;
																	parent->blk = throat;
																}
																parent = parent->ball->parent;
															}
															count++;//cout << '\n' << iball << jball << j;
														}
														else
														{
															// i...existing pore; j...existin g pore
															throatblock* t;
															bool find = false;
															for (set<block*>::iterator li = ipore->throats.begin(); li != ipore->throats.end(); ++li)
															{
																t = dynamic_cast<throatblock*>(*li);
																if ((t->p1 == iball && t->p2 == jball) || (t->p2 == iball && t->p1 == jball))
																	find = true;
															}
															if (find)
															{
																throat = t;
															}
															else
															{
																throat = new throatblock;
																throat->v = j;
																throat->p1 = iball;
																throat->p2 = jball;
																// throat->chain = iball .. j .. jball
																parent = i;
																while (parent != NULL)
																{
																	throat->chain.push_front(parent);
																	parent = parent->ball->parent;
																}
																parent = j;
																while (parent != NULL)
																{
																	throat->chain.push_back(parent);
																	parent = parent->ball->parent;
																}
																rf.throats.push_front(throat);
																ipore->throats.insert(throat);
																jpore->throats.insert(throat);
															}
															
															double di = sqrt((double)iball->ball->limit);
															double dj = sqrt((double)jball->ball->limit);
															double dt = sqrt((double)j->ball->limit);
															double ratio;
															if (i != ivoxel)
															{
																parent = i;
																while (parent != NULL)
																{
																	if (parent == ivoxel)
																		break;
																	if (iball->ball->limit > j->ball->limit) 
																	{
																		ratio = (sqrt((double)parent->ball->limit)-dt) / (di-dt);
																	}
																	else 
																	{
																		ratio = dist(*parent, *j) / dist(*iball, *j);
																	}
																	if (ratio > RATIO)
																	{
																		parent->ball->blk = ipore;
																		parent->blk = ipore;
																	}
																	else
																	{
																		parent->ball->blk = throat;
																		parent->blk = throat;
																	}
																	parent = parent->ball->parent;
																}
															}
															if (j != jvoxel)
															{
																j->ball->blk = throat;
																j->blk = throat;
																parent = j->ball->parent;
																while (parent != NULL)
																{
																	if (parent == jvoxel)
																		break;
																	if (jball->ball->limit > j->ball->limit) 
																	{
																		ratio = (sqrt((double)parent->ball->limit)-dt) / (dj-dt);
																	}
																	else 
																	{
																		ratio = dist(*parent, *j) / dist(*jball, *j);
																	}
																	if (ratio > RATIO)
																	{
																		parent->ball->blk = jpore;
																		parent->blk = jpore;
																	}
																	else
																	{
																		parent->ball->blk = throat;
																		parent->blk = throat;
																	}
																	parent = parent->ball->parent;
																}
															}
															count++;//cout << '\n' << iball << jball << j;
														}
													}
													else
													{
														// i ... existing pore; j... existing throat
														throat = dynamic_cast<throatblock*>(jblock);
														if (throat->p1 == iball || throat->p2 == iball)
														{
															
															double di = sqrt((double)iball->ball->limit);
															double dj = sqrt((double)jball->ball->limit);
															double dt = sqrt((double)j->ball->limit);
															double ratio;
															if (i != ivoxel)
															{
																parent = i;
																while (parent != NULL)
																{
																	if (parent == ivoxel)
																		break;
																	if (iball->ball->limit > j->ball->limit) 
																	{
																		ratio = (sqrt((double)parent->ball->limit)-dt) / (di-dt);
																	}
																	else 
																	{
																		ratio = dist(*parent, *j) / dist(*iball, *j);
																	}
																	if (ratio > RATIO)
																	{
																		parent->ball->blk = ipore;
																		parent->blk = ipore;
																	}
																	else
																	{
																		parent->ball->blk = throat;
																		parent->blk = throat;
																	}
																	parent = parent->ball->parent;
																}
															}
															if (j != jvoxel)
															{
																j->ball->blk = throat;
																j->blk = throat;
																parent = j->ball->parent;
																while (parent != NULL)
																{
																	if (parent == jvoxel)
																		break;
																	if (jball->ball->limit > j->ball->limit) 
																	{
																		ratio = (sqrt((double)parent->ball->limit)-dt) / (dj-dt);
																	}
																	else 
																	{
																		ratio = dist(*parent, *j) / dist(*jball, *j);
																	}
																	if (ratio > RATIO)
																	{
																		parent->ball->blk = jpore;
																		parent->blk = jpore;
																	}
																	else
																	{
																		parent->ball->blk = throat;
																		parent->blk = throat;
																	}
																	parent = parent->ball->parent;
																}
															}
															count++;//cout << '\n' << iball << jball << j;
														}
														else
														{
															throat = dynamic_cast<throatblock*>(jblock);
															
															int pc = 0;
															int tc = 0;
															bool findj = false;
															for (list<voxel*>::iterator li = throat->chain.begin(); li != throat->chain.end(); ++li)
															{
																if ((*li) == jvoxel)
																{
																	findj = true;
																	break;
																}
															}
															parent = jvoxel;
															while (parent != NULL)
															{
																block* b = parent->ball->blk;
																if (b != NULL)
																{
																	if (b->ispore())
																		++pc;
																	else
																		++tc;
																}
																parent = parent->ball->parent;
															}
															if (1) 
															{
																parent = jvoxel;
																while (parent != NULL)
																{
																	parent->ball->blk = jpore;
																	parent->blk = jpore;
																	parent = parent->ball->parent;
																}
																
																throatblock* t;
																bool find = false;
																for (set<block*>::iterator li = jpore->throats.begin(); li != jpore->throats.end(); ++li)
																{
																	t = dynamic_cast<throatblock*>(*li);
																	if ((t->p1 == iball && t->p2 == jball) || (t->p2 == iball && t->p1 == jball))
																		find = true;
																}
																if (find)
																{
																	throat = t;
																}
																else
																{
																	throat = new throatblock;
																	throat->v = j;
																	throat->p1 = iball;
																	throat->p2 = jball;
																	// throat->chain = iball .. j .. jball
																	parent = i;
																	while (parent != NULL)
																	{
																		throat->chain.push_front(parent);
																		parent = parent->ball->parent;
																	}
																	parent = j;
																	while (parent != NULL)
																	{
																		throat->chain.push_back(parent);
																		parent = parent->ball->parent;
																	}
																	rf.throats.push_front(throat);
																	ipore->throats.insert(throat);
																	jpore->throats.insert(throat);
																}
																
																double di = sqrt((double)iball->ball->limit);
																double dj = sqrt((double)jball->ball->limit);
																double dt = sqrt((double)j->ball->limit);
																double ratio;
																if (i != ivoxel)
																{
																	parent = i;
																	while (parent != NULL)
																	{
																		if (parent == ivoxel)
																			break;
																		if (iball->ball->limit > j->ball->limit) 
																		{
																			ratio = (sqrt((double)parent->ball->limit)-dt) / (di-dt);
																		}
																		else 
																		{
																			ratio = dist(*parent, *j) / dist(*iball, *j);
																		}
																		if (ratio > RATIO)
																		{
																			parent->ball->blk = ipore;
																			parent->blk = ipore;
																		}
																		else
																		{
																			parent->ball->blk = throat;
																			parent->blk = throat;
																		}
																		parent = parent->ball->parent;
																	}
																}
																if (j != jvoxel)
																{
																	j->ball->blk = throat;
																	j->blk = throat;
																	parent = j->ball->parent;
																	while (parent != NULL)
																	{
																		if (parent == jvoxel)
																			break;
																		if (jball->ball->limit > j->ball->limit) 
																		{
																			ratio = (sqrt((double)parent->ball->limit)-dt) / (dj-dt);
																		}
																		else 
																		{
																			ratio = dist(*parent, *j) / dist(*jball, *j);
																		}
																		if (ratio > RATIO)
																		{
																			parent->ball->blk = jpore;
																			parent->blk = jpore;
																		}
																		else
																		{
																			parent->ball->blk = throat;
																			parent->blk = throat;
																		}
																		parent = parent->ball->parent;
																	}
																}
																count++;//cout << '\n' << iball << jball << j;
															}
															else 
															{
																if (findj == true)
																{
																}
																else
																{
																}
															}
														}
													}
												}
											}
											else
											{
												if (jtype == true)
												{
													if (jvoxel == NULL)
													{
														// i...existing throat; j...new
														throat = dynamic_cast<throatblock*>(iblock);
														
														int pc = 0;
														int tc = 0;
														bool findi = false;
														for (list<voxel*>::iterator li = throat->chain.begin(); li != throat->chain.end(); ++li)
														{
															if ((*li) == ivoxel)
															{
																findi = true;
																break;
															}
														}
														parent = ivoxel;
														while (parent != NULL)
														{
															block* b = parent->ball->blk;
															if (b != NULL)
															{
																if (b->ispore())
																	++pc;
																else
																	++tc;
															}
															parent = parent->ball->parent;
														}
														if (1) 
														{
															parent = ivoxel;
															while (parent != NULL)
															{
																parent->ball->blk = ipore;
																parent->blk = ipore;
																parent = parent->ball->parent;
															}
															
															throat = new throatblock;
															throat->v = j;
															throat->p1 = iball;
															throat->p2 = jball;
															// throat->chain = iball .. j .. jball
															parent = i;
															while (parent != NULL)
															{
																throat->chain.push_front(parent);
																parent = parent->ball->parent;
															}
															parent = j;
															while (parent != NULL)
															{
																throat->chain.push_back(parent);
																parent = parent->ball->parent;
															}
															rf.throats.push_front(throat);
															ipore->throats.insert(throat);
															jpore->throats.insert(throat);
															
															double di = sqrt((double)iball->ball->limit);
															double dj = sqrt((double)jball->ball->limit);
															double dt = sqrt((double)j->ball->limit);
															double ratio;
															if (i != ivoxel)
															{
																parent = i;
																while (parent != NULL)
																{
																	if (parent == ivoxel)
																		break;
																	if (iball->ball->limit > j->ball->limit) 
																	{
																		ratio = (sqrt((double)parent->ball->limit)-dt) / (di-dt);
																	}
																	else 
																	{
																		ratio = dist(*parent, *j) / dist(*iball, *j);
																	}
																	if (ratio > RATIO)
																	{
																		parent->ball->blk = ipore;
																		parent->blk = ipore;
																	}
																	else
																	{
																		parent->ball->blk = throat;
																		parent->blk = throat;
																	}
																	parent = parent->ball->parent;
																}
															}
															j->ball->blk = throat;
															j->blk = throat;
															parent = j->ball->parent;
															while (parent != NULL)
															{
																if (jball->ball->limit > j->ball->limit) 
																{
																	ratio = (sqrt((double)parent->ball->limit)-dt) / (dj-dt);
																}
																else 
																{
																	ratio = dist(*parent, *j) / dist(*jball, *j);
																}
																if (ratio > RATIO)
																{
																	parent->ball->blk = jpore;
																	parent->blk = jpore;
																}
																else
																{
																	parent->ball->blk = throat;
																	parent->blk = throat;
																}
																parent = parent->ball->parent;
															}
															count++;//cout << '\n' << iball << jball << j;
														}
														else
														{
														    if (findi == true) 
															{
															}
															else
															{
															}
														}
													}
													else
													{
														
														throat = dynamic_cast<throatblock*>(iblock);
														if (throat->p1 == jball || throat->p2 == jball)
														{
															
															double di = sqrt((double)iball->ball->limit);
															double dj = sqrt((double)jball->ball->limit);
															double dt = sqrt((double)j->ball->limit);
															double ratio;
															if (i != ivoxel)
															{
																parent = i;
																while (parent != NULL)
																{
																	if (parent == ivoxel)
																		break;
																	if (iball->ball->limit > j->ball->limit) 
																	{
																		ratio = (sqrt((double)parent->ball->limit)-dt) / (di-dt);
																	}
																	else 
																	{
																		ratio = dist(*parent, *j) / dist(*iball, *j);
																	}
																	if (ratio > RATIO)
																	{
																		parent->ball->blk = ipore;
																		parent->blk = ipore;
																	}
																	else
																	{
																		parent->ball->blk = throat;
																		parent->blk = throat;
																	}
																	parent = parent->ball->parent;
																}
															}
															if (j != jvoxel)
															{
																j->ball->blk = throat;
																j->blk = throat;
																parent = j->ball->parent;
																while (parent != NULL)
																{
																	if (parent == jvoxel)
																		break;
																	if (jball->ball->limit > j->ball->limit) 
																	{
																		ratio = (sqrt((double)parent->ball->limit)-dt) / (dj-dt);
																	}
																	else
																	{
																		ratio = dist(*parent, *j) / dist(*jball, *j);
																	}
																	if (ratio > RATIO)
																	{
																		parent->ball->blk = jpore;
																		parent->blk = jpore;
																	}
																	else
																	{
																		parent->ball->blk = throat;
																		parent->blk = throat;
																	}
																	parent = parent->ball->parent;
																}
															}
															count++;//cout << '\n' << iball << jball << j;
														}
														else
														{
															throat = dynamic_cast<throatblock*>(iblock);
															
															int pc = 0;
															int tc = 0;
															bool findi = false;
															for (list<voxel*>::iterator li = throat->chain.begin(); li != throat->chain.end(); ++li)
															{
																if ((*li) == ivoxel)
																{
																	findi = true;
																	break;
																}
															}
															parent = ivoxel;
															while (parent != NULL)
															{
																block* b = parent->ball->blk;
																if (b != NULL)
																{
																	if (b->ispore())
																		++pc;
																	else
																		++tc;
																}
																parent = parent->ball->parent;
															}
															if (1) 
															{
																parent = ivoxel;
																while (parent != NULL)
																{
																	parent->ball->blk = ipore;
																	parent->blk = ipore;
																	parent = parent->ball->parent;
																}
																
																throatblock* t;
																bool find = false;
																for (set<block*>::iterator li = ipore->throats.begin(); li != ipore->throats.end(); ++li)
																{
																	t = dynamic_cast<throatblock*>(*li);
																	if ((t->p1 == iball && t->p2 == jball) || (t->p2 == iball && t->p1 == jball))
																		find = true;
																}
																if (find)
																{
																	throat = t;
																}
																else
																{
																	throat = new throatblock;
																	throat->v = j;
																	throat->p1 = iball;
																	throat->p2 = jball;
																	// throat->chain = iball .. j .. jball
																	parent = i;
																	while (parent != NULL)
																	{
																		throat->chain.push_front(parent);
																		parent = parent->ball->parent;
																	}
																	parent = j;
																	while (parent != NULL)
																	{
																		throat->chain.push_back(parent);
																		parent = parent->ball->parent;
																	}
																	rf.throats.push_front(throat);
																	ipore->throats.insert(throat);
																	jpore->throats.insert(throat);
																}
																
																double di = sqrt((double)iball->ball->limit);
																double dj = sqrt((double)jball->ball->limit);
																double dt = sqrt((double)j->ball->limit);
																double ratio;
																if (i != ivoxel)
																{
																	parent = i;
																	while (parent != NULL)
																	{
																		if (parent == ivoxel)
																			break;
																		if (iball->ball->limit > j->ball->limit) 
																		{
																			ratio = (sqrt((double)parent->ball->limit)-dt) / (di-dt);
																		}
																		else 
																		{
																			ratio = dist(*parent, *j) / dist(*iball, *j);
																		}
																		if (ratio > RATIO)
																		{
																			parent->ball->blk = ipore;
																			parent->blk = ipore;
																		}
																		else
																		{
																			parent->ball->blk = throat;
																			parent->blk = throat;
																		}
																		parent = parent->ball->parent;
																	}
																}
																if (j != jvoxel)
																{
																	j->ball->blk = throat;
																	j->blk = throat;
																	parent = j->ball->parent;
																	while (parent != NULL)
																	{
																		if (parent == jvoxel)
																			break;
																		if (jball->ball->limit > j->ball->limit) 
																		{
																			ratio = (sqrt((double)parent->ball->limit)-dt) / (dj-dt);
																		}
																		else 
																		{
																			ratio = dist(*parent, *j) / dist(*jball, *j);
																		}
																		if (ratio > RATIO)
																		{
																			parent->ball->blk = jpore;
																			parent->blk = jpore;
																		}
																		else
																		{
																			parent->ball->blk = throat;
																			parent->blk = throat;
																		}
																		parent = parent->ball->parent;
																	}
																}
																count++;//cout << '\n' << iball << jball << j;
															}
															else 
															{
																if (findi == true) 
																{
																}
																else
																{
																}
															}
														}
													}
												}
												else
												{
													// i...existing throat; j...existing throat
													if (iblock == jblock)
													{
														throat = dynamic_cast<throatblock*>(iblock);
														
														parent = i;
														while (parent != NULL)
														{
															block* b = parent->ball->blk;
															if (b == iblock)
																break;
															else
															{
																parent->ball->blk = throat;
																parent->blk = throat;
															}
															parent = parent->ball->parent;
														}
														parent = j;
														while (parent != NULL)
														{
															block* b = parent->ball->blk;
															if (b == jblock)
																break;
															else
															{
																parent->ball->blk = throat;
																parent->blk = throat;
															}
															parent = parent->ball->parent;
														}
													}
													else
													{
														
														throat = dynamic_cast<throatblock*>(iblock);
														if ((iball == throat->p1 && jball == throat->p2) || (iball == throat->p2 && jball == throat->p1))
														{
															parent = i;
															while (parent != NULL)
															{
																if (parent == ivoxel)
																	break;
																else
																{
																	parent->ball->blk = throat;
																	parent->blk = throat;
																}
																parent = parent->ball->parent;
															}
															parent = j;
															while (parent != NULL)
															{
																if (parent == jvoxel)
																	break;
																else
																{
																	parent->ball->blk = throat;
																	parent->blk = throat;
																}
																parent = parent->ball->parent;
															}
															continue;
														}
														
														throat = dynamic_cast<throatblock*>(jblock);
														if ((iball == throat->p1 && jball == throat->p2) || (iball == throat->p2 && jball == throat->p1))
														{
															parent = i;
															while (parent != NULL)
															{
																if (parent == ivoxel)
																	break;
																else
																{
																	parent->ball->blk = throat;
																	parent->blk = throat;
																}
																parent = parent->ball->parent;
															}
															parent = j;
															while (parent != NULL)
															{
																if (parent == jvoxel)
																	break;
																else
																{
																	parent->ball->blk = throat;
																	parent->blk = throat;
																}
																parent = parent->ball->parent;
															}
															continue;
														}
														
														parent = ivoxel;
														while (parent != NULL)
														{
															parent->ball->blk = ipore;
															parent->blk = ipore;
															parent = parent->ball->parent;
														}
														parent = jvoxel;
														while (parent != NULL)
														{
															parent->ball->blk = jpore;
															parent->blk = jpore;
															parent = parent->ball->parent;
														}
													
														throatblock* t;
														bool find = false;
														for (set<block*>::iterator li = ipore->throats.begin(); li != ipore->throats.end(); ++li)
														{
															t = dynamic_cast<throatblock*>(*li);
															if ((t->p1 == iball && t->p2 == jball) || (t->p2 == iball && t->p1 == jball))
																find = true;
														}
														if (find)
														{
															throat = t;
														}
														else
														{
															throat = new throatblock;
															throat->v = j;
															throat->p1 = iball;
															throat->p2 = jball;
															// throat->chain = iball .. j .. jball
															parent = i;
															while (parent != NULL)
															{
																throat->chain.push_front(parent);
																parent = parent->ball->parent;
															}
															parent = j;
															while (parent != NULL)
															{
																throat->chain.push_back(parent);
																parent = parent->ball->parent;
															}
															rf.throats.push_front(throat);
															ipore->throats.insert(throat);
															jpore->throats.insert(throat);
														}
														
														double di = sqrt((double)iball->ball->limit);
														double dj = sqrt((double)jball->ball->limit);
														double dt = sqrt((double)j->ball->limit);
														double ratio;
														if (i != ivoxel)
														{
															parent = i;
															while (parent != NULL)
															{
																if (parent == ivoxel)
																	break;
																if (iball->ball->limit > j->ball->limit) 
																{
																	ratio = (sqrt((double)parent->ball->limit)-dt) / (di-dt);
																}
																else 
																{
																	ratio = dist(*parent, *j) / dist(*iball, *j);
																}
																if (ratio > RATIO)
																{
																	parent->ball->blk = ipore;
																	parent->blk = ipore;
																}
																else
																{
																	parent->ball->blk = throat;
																	parent->blk = throat;
																}
																parent = parent->ball->parent;
															}
														}
														if (j != jvoxel)
														{
															j->ball->blk = throat;
															j->blk = throat;
															parent = j->ball->parent;
															while (parent != NULL)
															{
																if (parent == jvoxel)
																	break;
																if (jball->ball->limit > j->ball->limit) 
																{
																	ratio = (sqrt((double)parent->ball->limit)-dt) / (dj-dt);
																}
																else 
																{
																	ratio = dist(*parent, *j) / dist(*jball, *j);
																}
																if (ratio > RATIO)
																{
																	parent->ball->blk = jpore;
																	parent->blk = jpore;
																}
																else
																{
																	parent->ball->blk = throat;
																	parent->blk = throat;
																}
																parent = parent->ball->parent;
															}
														}
														++counter;
													}
												}
											}
										}
									}
								}
								else
								{
									if (j->ball->level == LEVEL_MAX) 
									{
										j->ball->level = i->ball->level+1;
										j->ball->parent = i;
										if (i->ball->pore != NULL) 
											j->ball->pore = i->ball->pore;
										else
											j->ball->pore = i;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	void markthroat()
	{
		long nsize = 0;
		voxel* vp = rf.voxelspace;
		voxel* end = rf.voxelspace+rf.porosity;
		while (vp < end)
		{
			if (vp->ball != NULL)
			{
				if (vp->ball->blk == NULL)
				{
					voxel* parent = vp->ball->parent;
					while (parent != NULL)
					{
						if (parent->ball->blk != NULL)
							break;
						parent = parent->ball->parent;
					}
					if (parent != NULL)
					{
						block* b = parent->ball->blk;
						parent = vp;
						while (parent != NULL)
						{
							if (parent->ball->blk != NULL)
								break;
							parent->ball->blk = b;
							parent->blk = b;
							parent = parent->ball->parent;
						}
					}
				}
				if (vp->ball->blk != NULL && vp->ball->blk->ispore() == false)
				{
					
					short vx,vy,vz,r;
					vx = vp->x;
					vy = vp->y;
					vz = vp->z;
					r = vp->ball->limit;
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
								voxel* j = rf(vx+a, vy+b, vz+c);
								if ((j != NULL) && (j != vp))
								{
									if (j->blk == NULL)
										j->blk = vp->ball->blk;
								}
							}
						}
					}
					//if ((++nsize)%128==0)
						//cout << "\rmark throat " << nsize;
				}
			}
			++vp;
		}
		//cout << "\rmark throat " << nsize << '\n';
	}
	void markpore(short fx)
	{
		long nsize = 0;
		//cout << "sorting...";
		voxel** tv = new voxel*[rf.porosity];
		voxel** tp = tv;
		voxel* ti = rf.voxelspace;
		voxel* tend = rf.voxelspace+rf.porosity;
		while (ti<tend)
		{
			if (ti->ball != NULL)
			{
				*tp++ = ti++;
				nsize++;
			}
			else
			{
				++ti;
			}
		}
		sort(tv, tv+nsize, markcomparer());
		cout << '\n';
		voxel** i = tv;
		voxel** end = tv+nsize;
		nsize = 0;
		while (i < end)
		{
			voxel* vp = *i;

			if (vp->ball != NULL)
			{
				if (vp->ball->blk == NULL)
				{
					voxel* parent = vp->ball->parent;
					while (parent != NULL)
					{
						if (parent->ball->blk != NULL)
							break;
						parent = parent->ball->parent;
					}
					if (parent != NULL)
					{
						block* b = parent->ball->blk;
						parent = vp;
						while (parent != NULL)
						{
							if (parent->ball->blk != NULL)
								break;
							parent->ball->blk = b;
							parent->blk = b;
							parent = parent->ball->parent;
						}
					}
				}

				if (vp->ball->blk != NULL && vp->ball->blk->ispore() == true)
				{
					poreblock* pore  = dynamic_cast<poreblock*>(vp->ball->blk);
					
					short vx,vy,vz,r;
					vx = vp->x;
					vy = vp->y;
					vz = vp->z;
					r = vp->ball->limit;
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
								voxel* j = rf(vx+a, vy+b, vz+c);
								if (j != NULL)
								{
									j->blk = pore;
									if (j != vp)
									{
										unsigned long pl = dist2(*pore->v, *j);
										if (pl > pore->length)
											pore->length = pl;
									}
								}
								if (fx == 1)
								{
									if ((vx+a)<=0)
									{
										pore->v->edge = 1;
										pore->edgeball = vp;
									}
									if ((vx+a)>=(rf.x-1))
									{
										pore->v->edge = 2;
										pore->edgeball = vp;
									}
								}
								else if (fx == 2)
								{
									if ((vy+b)<=0)
									{
										pore->v->edge = 1;
										pore->edgeball = vp;
									}
									if ((vy+b)>=(rf.y-1))
									{
										pore->v->edge = 2;
										pore->edgeball = vp;
									}
								}
								else if (fx == 3)
								{
									if ((vz+c)<=0)
									{
										pore->v->edge = 1;
										pore->edgeball = vp;
									}
									if ((vz+c)>=(rf.z-1))
									{
										pore->v->edge = 2;
										pore->edgeball = vp;
									}
								}
							}
						}
					}
					//if ((++nsize)%128==0)
						//cout << "\rmark pore " << nsize;
				}
			}
			++i;
		}
		//cout << "\rmark pore " << nsize << '\n';
		delete[] tv;
	}
	void marknullpore()
	{
		long nsize = 0;
		voxel* vp = rf.voxelspace;
		voxel* end = rf.voxelspace+rf.porosity;
		while (vp < end)
		{
			if (vp->ball != NULL)
			{
				if (vp->ball->level == 1 && vp->ball->blk == NULL)
				{
					poreblock* pore = new poreblock;
					pore->v = vp;
					rf.pores.push_back(pore);
					vp->ball->blk = pore;
					vp->blk = pore;
					//if ((++nsize)%128==0)
						//cout << "\rmark null pore " << nsize;
				}
			}
			++vp;
		}
		//cout << "\rmark null pore " << nsize << '\n';
	}
	void connect_in_out(short fx)
	{
		throatblock* throat;
		for (list<poreblock*>::iterator li = rf.pores.begin(); li != rf.pores.end(); ++li)
		{
			if ((*li)->v->edge == 1)
			{
				throat = new throatblock;
				throat->v = (*li)->edgeball;
				throat->p1 = (voxel*)(-1);
				throat->p2 = (*li)->v;
				voxel* parent = (*li)->edgeball;
				while (parent != NULL)
				{
					throat->chain.push_back(parent);
					parent = parent->ball->parent;
				}
				rf.throats.push_front(throat);
				(*li)->throats.insert(throat);
				short vx,vy,vz,r;
				vx = throat->v->x;
				vy = throat->v->y;
				vz = throat->v->z;
				r = throat->v->ball->limit;
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
							voxel* j = rf(vx+a, vy+b, vz+c);
							if (j != NULL)
							{
								if (fx == 1)
								{
									if ((vx+a)==0)
									{
										j->blk = throat;
									}
								}
								else if (fx == 2)
								{
									if ((vy+b)==0)
									{
										j->blk = throat;
									}
								}
								else if (fx == 3)
								{
									if ((vz+c)==0)
									{
										j->blk = throat;
									}
								}
							}
						}
					}
				}
			}
			else if ((*li)->v->edge == 2)
			{
				throat = new throatblock;
				throat->v = (*li)->edgeball;
				throat->p1 = (*li)->v;
				throat->p2 = (voxel*)(0);
				voxel* parent = (*li)->edgeball;
				while (parent != NULL)
				{
					throat->chain.push_back(parent);
					parent = parent->ball->parent;
				}
				rf.throats.push_front(throat);
				(*li)->throats.insert(throat);
				short vx,vy,vz,r;
				vx = throat->v->x;
				vy = throat->v->y;
				vz = throat->v->z;
				r = throat->v->ball->limit;
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
							voxel* j = rf(vx+a, vy+b, vz+c);
							if (j != NULL)
							{
								if (fx == 1)
								{
									if ((vx+a)==(rf.x-1))
									{
										j->blk = throat;
									}
								}
								else if (fx == 2)
								{
									if ((vy+b)==(rf.y-1))
									{
										j->blk = throat;
									}
								}
								else if (fx == 3)
								{
									if ((vz+c)==(rf.z-1))
									{
										j->blk = throat;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	void valid()
	{
		long nsize = 0;
		voxel* vp = rf.voxelspace;
		voxel* end = rf.voxelspace+rf.porosity;
		while (vp < end)
		{
			if (vp->blk == NULL)
				++nsize;
			++vp;
		}
		//cout << "\rinvalid voxel " << nsize << ", about " << nsize*100.0/rf.porosity << "%\n";
	}
	void setid()
	{
		unsigned long id = 0;
		for (list<poreblock*>::iterator li = rf.pores.begin(); li != rf.pores.end(); ++li)
		{
			(*li)->id = ++id;
		}
		id = 0;
		for (list<throatblock*>::iterator li = rf.throats.begin(); li != rf.throats.end(); ++li)
		{
			(*li)->id = ++id;
		}
	}
	void calc()
	{
		long nsize = 0;
		voxel* vp = rf.voxelspace;
		voxel* end = rf.voxelspace+rf.porosity;
		while (vp < end)
		{
			if (vp->blk != NULL)
			{
				vp->blk->volumn++;
				voxel* v;
				v = rf(vp->x-1,vp->y,vp->z);
				if (v == NULL)
					vp->blk->area++;
				else
				{
					if (v->blk != vp->blk)
						vp->blk->area++;
				}
				v = rf(vp->x+1,vp->y,vp->z);
				if (v == NULL)
					vp->blk->area++;
				else
				{
					if (v->blk != vp->blk)
						vp->blk->area++;
				}
				v = rf(vp->x,vp->y-1,vp->z);
				if (v == NULL)
					vp->blk->area++;
				else
				{
					if (v->blk != vp->blk)
						vp->blk->area++;
				}
				v = rf(vp->x,vp->y+1,vp->z);
				if (v == NULL)
					vp->blk->area++;
				else
				{
					if (v->blk != vp->blk)
						vp->blk->area++;
				}
				v = rf(vp->x,vp->y,vp->z-1);
				if (v == NULL)
					vp->blk->area++;
				else
				{
					if (v->blk != vp->blk)
						vp->blk->area++;
				}
				v = rf(vp->x,vp->y,vp->z+1);
				if (v == NULL)
					vp->blk->area++;
				else
				{
					if (v->blk != vp->blk)
						vp->blk->area++;
				}
				++nsize;
			}
			//if (nsize%128 == 1)
				//cout << "\rcalc " << nsize;
			++vp;
		}
		//cout << "\rcalc " << nsize << '\n';
	}
public:
	reference& rf;
	config& cg;
	long count;
	long counter;
};
