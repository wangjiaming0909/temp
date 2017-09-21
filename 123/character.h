class character
{
public:
	character(config &c,reference &r):cg(c),rf(r){}
	void saveporedtr()
	{
		string fname=cg.filename+"_poredtr.dat";
		FILE *fp=fopen(fname.c_str(),"w");
		long porenumber=rf.pores.size();


		multiset<double> porer;
		for (list<poreblock*>::iterator li = rf.pores.begin(); li != rf.pores.end(); ++li)
		{
			
			double radius2 = makeradius2((*li)->v->ball->limit, (*li)->v->ball->r2, cg.minr2); 
			radius2=radius2 *cg.precision ; 
			porer.insert (radius2);

 
		}
		long i=0;
		for(multiset<double> ::iterator li=porer.begin (); li!=porer.end (); ++li)	
		{
			
			fprintf(fp,"%6d  %f\n",++i,*li);
		}
		/*double *poredis=new double[porenumber];
		double *i=poredis;
		double *j=poredis;
		double *end=poredis+porenumber;
		long cnt;
		
		for(multiset<double> ::iterator li=porer.begin (); li!=porer.end (); ++li)	
		{
			
			*i=*li;
			++i;
		}
		while(j< end)
		{
			i=j;
			j++;
			cnt=1;
			while(j< end)
			{
				
					if(*j-*i< 1)
					{
						cnt++;
						++j;
					}
					else
						break;
				
				
			}
			fprintf(fp,"%2f    %2f\n",*i, (double)cnt/(double)porenumber);
		}
		delete[] poredis;*/


		fclose(fp);
	}


	void savethroatdtr()
	{
		string fname=cg.filename+"_throatdtr.dat";
		FILE *fp=fopen(fname.c_str(),"w");
		long throatnumber=rf.throats.size();


		multiset<double> throat_r;
		for (list<throatblock*>::iterator li = rf.throats.begin(); li != rf.throats.end(); ++li)
		{
			
			double radius2 = makeradius2((*li)->v->ball->limit, (*li)->v->ball->r2, cg.minr2); 
			radius2=radius2 *cg.precision ; 
			throat_r.insert (radius2);

 
		}
		long i=0;
		for(multiset<double> ::iterator li=throat_r.begin (); li!=throat_r.end (); ++li)	
		{
			
			fprintf(fp,"%6d  %f\n",++i,*li );
		}
		
		/*double *throatdis=new double[throatnumber];
		double *i=throatdis;
		double *j=throatdis;
		double *end=throatdis+throatnumber;
		long cnt;
		
		for(multiset<double> ::iterator li=throat_r.begin (); li!=throat_r.end (); ++li)	
		{
			
			*i=*li;
			++i;
		}
		while(j< end)
		{
			i=j;
			j++;
			cnt=1;
			while(j< end)
			{
				
					if(*j-*i< 1)
					{
						cnt++;
						++j;
					}
					else
						break;
				
			}
			fprintf(fp,"%2f    %2f\n",*i, (double)cnt/(double)throatnumber);
		}
		delete[] throatdis;*/


		fclose(fp);
	}


	void saveconnectdtr()
	{
		string fname=cg.filename+"_connectdtr.dat";
		FILE *fp=fopen(fname.c_str(),"w");
		long porenumber=rf.pores.size();


		multiset<short> coordination;
		for (list<poreblock*>::iterator li = rf.pores.begin(); li != rf.pores.end(); ++li)
		{
			
			short connumber = (*li)->throats.size () ; 
			coordination.insert (connumber);

 
		}
		/*long i=0;
		for(multiset<short> ::iterator li=coordination.begin (); li!=coordination.end (); ++li)	
		{
			
			fprintf(fp,"%6d  %3d\n",++i,*li);
		}*/
		short *connectdis=new short[porenumber];
		short *i=connectdis;
		short *j=connectdis;
		short *end=connectdis+porenumber;
		long cnt;
		
		for(multiset<short> ::iterator li=coordination.begin (); li!=coordination.end (); ++li)	
		{
			
			*i=*li;
			++i;
		}
		while(j< end)
		{
			i=j;
			j++;
			cnt=1;
			while(j< end)
			{
				if(*j-*i< 0.1)
				{
					cnt++;
					++j;
				}
				else
					break;
			}
			fprintf(fp,"%3d    %2f\n",*i, (double)cnt/(double)porenumber);
		}
		delete[] connectdis;


		fclose(fp);
	}


	void saveaspratio()
	{
		string fname=cg.filename+"_aspratio.dat";
		FILE *fp=fopen(fname.c_str(),"w");

		double pradius;
		double tradius;
		double tradius_ave;
		double aspectratio;

		multiset<double> aspectset;
		for (list<poreblock*>::iterator li = rf.pores.begin(); li != rf.pores.end(); ++li)
		{
			
			short connumber = (*li)->throats.size () ; 
			if( connumber>0 )
			{

				pradius = makeradius2((*li)->v->ball->limit, (*li)->v->ball->r2, cg.minr2);
				double sum=0;
				for(set<block*>::iterator bi=(*li)->throats.begin ();bi!=(*li)->throats.end ();++bi)
				{
					throatblock* tb=dynamic_cast<throatblock*>(*bi);
					tradius = makeradius2(tb->v->ball->limit, tb->v->ball->r2, cg.minr2);
					sum = sum + tradius;
				}
			
				tradius_ave=sum/connumber;
				aspectratio=pradius/tradius_ave;
				aspectset.insert (aspectratio);
			}
		
			else
				continue;

 
		}
		long i=0;
		for(multiset<double> ::iterator li=aspectset.begin (); li!=aspectset.end (); ++li)	
		{
			
			fprintf(fp,"%6d  %2f\n",++i,*li);
		}
		/*long porenumber=aspectset.size ();
		double *aspectdis=new double[porenumber];
		double *i=aspectdis;
		double *j=aspectdis;
		double *end=aspectdis+porenumber;
		long cnt;
		
		for(multiset<double> ::iterator li=aspectset.begin (); li!=aspectset.end (); ++li)	
		{
			
			*i=*li;
			++i;
		}
		while(j< end)
		{
			i=j;
			j++;
			cnt=1;
			while(j< end)
			{
				if(*j-*i< 0.4)
				{
					cnt++;
					++j;
				}
				else
					break;
			}
			fprintf(fp,"%2f    %2f\n",*i, (double)cnt/(double)porenumber);
		}
		delete[] aspectdis;*/


		fclose(fp);
	}

	void saveporefactor()
	{
		string fname=cg.filename+"_pfactor.dat";
		FILE *fp=fopen(fname.c_str(),"w");
		long porenumber=rf.pores.size();


		multiset<double> porefactor;
		for (list<poreblock*>::iterator li =rf.pores.begin(); li != rf.pores.end(); ++li)
		{
			if ((*li)->length == 0)
				(*li)->length = (*li)->v->ball->limit;
			
			double p_shape1 = (*li)->volumn*sqrt(double((*li)->length))*2/(*li)->area/(*li)->area;
			porefactor.insert(p_shape1);
		}
		/*long i=0;
		for(multiset<double> ::iterator li=porefactor.begin (); li!=porefactor.end (); ++li)	
		{
			
			fprintf(fp,"%6d  %2f\n",++i,*li);
		}*/
		double *dataspace=new double[porenumber];
		double *i=dataspace;
		double *j=dataspace;
		double *end=dataspace+porenumber;
		long cnt;
		
		for(multiset<double> ::iterator li=porefactor.begin (); li!=porefactor.end (); ++li)	
		{
			
			*i=*li;
			++i;
		}
		while(j< end)
		{
			i=j;
			j++;
			cnt=1;
			while(j< end)
			{
				if(*j-*i< 0.01)
				{
					cnt++;
					++j;
				}
				else
					break;
			}
			fprintf(fp,"%2f    %2f\n",*i, (double)cnt/(double)porenumber);
		}
		delete[] dataspace;


		fclose(fp);
	}


	void savethroatfactor()
	{
		string fname=cg.filename+"_tfactor.dat";
		FILE *fp=fopen(fname.c_str(),"w");
		long throatnumber=rf.throats.size();


		multiset<double> throatfactor;
		for (list<throatblock*>::iterator li = rf.throats.begin(); li != rf.throats.end(); ++li)
		{
			/*long id1, id2;
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
			double p1 = 0;
			double p2 = 0;
			
			list<voxel*>::iterator last = (*li)->chain.begin();
			list<voxel*>::iterator vi = last;
			for (++vi; vi != (*li)->chain.end(); ++vi)
			{
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
			

			double t_shape1 = (*li)->volumn*length/(*li)->area/(*li)->area ;*/
			double t_shape1=f_shape ();
			if (t_shape1 > 0.08)
				t_shape1 = 0.0796;
			throatfactor.insert (t_shape1);
		}
		/*long i=0;
		for(multiset<double> ::iterator li=throatfactor.begin (); li!=throatfactor.end (); ++li)	
		{
			
			fprintf(fp,"%6d  %2f\n",++i,*li);
		}*/
		double *dataspace=new double[throatnumber];
		double *i=dataspace;
		double *j=dataspace;
		double *end=dataspace+throatnumber;
		long cnt;
		
		for(multiset<double> ::iterator li=throatfactor.begin (); li!=throatfactor.end (); ++li)	
		{
			
			*i=*li;
			++i;
		}
		while(j< end)
		{
			i=j;
			j++;
			cnt=1;
			while(j< end)
			{
				if(*j-*i< 0.0025)
				{
					cnt++;
					++j;
				}
				else
					break;
			}
			fprintf(fp,"%f    %2f\n",*i, (double)cnt/(double)throatnumber);
		}
		delete[] dataspace;


		fclose(fp);
	}


	void savethroatlength()
	{
		string fname1=cg.filename+"_ttlength.dat";
		FILE *fp1=fopen(fname1.c_str(),"w");

		string fname2=cg.filename+"_tlength.dat";
		FILE *fp2=fopen(fname2.c_str(),"w");



		multiset<double> ttlengthset;
		multiset<double> tlengthset;

		
		double length = 0;
		double tlength = 0;
		double p1 = 0;
		double p2 = 0;
		double pt1 = 0;
		double pt2 = 0;

		for (list<throatblock*>::iterator li = rf.throats.begin(); li != rf.throats.end(); ++li)
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
					tlength=tlength*cg.precision; 
					length=length*cg.precision;
					ttlengthset.insert(tlength);
					tlengthset.insert(length);
				}
		}
		long ii=0;
		for(multiset<double> ::iterator li=ttlengthset.begin (); li!=ttlengthset.end (); ++li)	
		{
			
			fprintf(fp1,"%6d  %2f\n",++ii,*li*cg.precision );
		}
		ii=0;
		for(multiset<double> ::iterator li=tlengthset.begin (); li!=tlengthset.end (); ++li)	
		{
			
			fprintf(fp2,"%6d  %2f\n",++ii,*li*cg.precision);
		}

		/*long number=tlengthset.size(); 
		double *dataspace=new double[number];
		double *i=dataspace;
		double *j=dataspace;
		double *end=dataspace+number;
		long cnt;
		
		for(multiset<double> ::iterator li=ttlengthset.begin (); li!=ttlengthset.end (); ++li)	
		{
			
			*i=*li;
			++i;
		}
		while(j< end)
		{
			i=j;
			j++;
			cnt=1;
			while(j< end)
			{
				if(*j-*i< 1000)
				{
					cnt++;
					++j;
				}
				else
					break;
			}
			fprintf(fp1,"%f    %2f\n",*i, (double)cnt/(double)number);
		}
		i=dataspace;
		j=dataspace;
		end=dataspace+number;

		
		for(multiset<double> ::iterator li=tlengthset.begin (); li!=tlengthset.end (); ++li)	
		{
			
			*i=*li;
			++i;
		}
		while(j< end)
		{
			i=j;
			j++;
			cnt=1;
			while(j< end)
			{
				if(*j-*i< 30)
				{
					cnt++;
					++j;
				}
				else
					break;
			}
			fprintf(fp2,"%f    %2f\n",*i, (double)cnt/(double)number);
		}


		delete[] dataspace;*/


		fclose(fp1);
		fclose(fp2);
	}
	void saveporevolume()
	{
		string fname=cg.filename+"_pvolume.dat";
		FILE *fp=fopen(fname.c_str(),"w");
		long porenumber=rf.pores.size();


		multiset<double> porevolume;
		for (list<poreblock*>::iterator li =rf.pores.begin(); li != rf.pores.end(); ++li)
		{
			
			double pvolume = (*li)->volumn;
			if(pvolume< 1)
				pvolume=1;
			pvolume=pvolume*cg.precision*cg.precision *cg.precision *0.001*0.001*0.001;
			porevolume.insert(pvolume);
		}
		long i=0;
		for(multiset<double> ::iterator li=porevolume.begin (); li!=porevolume.end (); ++li)	
		{
			
			fprintf(fp,"%6d  %2f\n",++i,*li*cg.precision*cg.precision *cg.precision *0.001*0.001*0.001);
		}
		/*double *dataspace=new double[porenumber];
		double *i=dataspace;
		double *j=dataspace;
		double *end=dataspace+porenumber;
		long cnt;
		
		for(multiset<double> ::iterator li=porevolume.begin (); li!=porevolume.end (); ++li)	
		{
			
			*i=*li;
			++i;
		}
		while(j< end)
		{
			i=j;
			j++;
			cnt=1;
			while(j< end)
			{
				if(*j-*i< 0.000001)
				{
					cnt++;
					++j;
				}
				else
					break;
			}
			fprintf(fp,"%e    %2f\n",*i, (double)cnt/(double)porenumber);
		}
		delete[] dataspace;*/


		fclose(fp);
	}

	void savethroatvolume()
	{
		string fname=cg.filename+"_tvolume.dat";
		FILE *fp=fopen(fname.c_str(),"w");
		long throatnumber= rf.throats.size();


		multiset<double> throatvolume;
		for (list<throatblock*>::iterator li =rf.throats.begin(); li != rf.throats.end(); ++li)
		{
			
			double tvolume = (*li)->volumn;
			if(tvolume< 1)
				tvolume=1;
			tvolume=tvolume*cg.precision*cg.precision *cg.precision *0.001*0.001*0.001;
			throatvolume.insert(tvolume);
		}
		long i=0;
		for(multiset<double> ::iterator li= throatvolume.begin (); li!=throatvolume.end (); ++li)	
		{
			
			fprintf(fp,"%6d  %2f\n",++i,*li*cg.precision*cg.precision *cg.precision *0.001*0.001*0.001);
		}

		/*double *dataspace=new double[throatnumber];
		double *i=dataspace;
		double *j=dataspace;
		double *end=dataspace+throatnumber;
		long cnt;
		
		for(multiset<double> ::iterator li=throatvolume.begin (); li!=throatvolume.end (); ++li)	
		{
			
			*i=*li;
			++i;
		}
		while(j< end)
		{
			i=j;
			j++;
			cnt=1;
			while(j< end)
			{
				if(*j-*i< 0.000001)
				{
					cnt++;
					++j;
				}
				else
					break;
			}
			fprintf(fp,"%e    %f\n",*i, (double)cnt/(double)throatnumber);
		}
		delete[] dataspace;*/


		fclose(fp);
	}

	/*void saveporedtr()
	{

		string fname=cg.filename+"_poredtr.dat";
		FILE *fp=fopen(fname.c_str(),"w");

		cout << "save pore distribution\n";
		long porenumber=rf.pores.size();
		voxel** tv = new voxel*[porenumber];
		voxel** tp = tv;

		for(list<poreblock*>::iterator li=rf.pores.begin();li!=rf.pores.end();++li)
		{

				*tp++ = (*li)->v;

		}
		sort(tv, tv+porenumber, metaballcomparer());	
		voxel** i;
		voxel** j = tv;
		voxel** end = tv+porenumber;
		long cnt;
		while(j < end)
		{
			cnt=0;
			i=j;
			++j;
			while(j < end)
			{
				++cnt;
				if((*j)->ball->r2 < (*i)->ball->r2)
					break;

				++j;
			}
			fprintf(fp,"%E    %E\n",(double)cnt/(double)porenumber, sqrt((double)(*i)->ball->r2)*cg.precision *0.000001);

		}
		fclose(fp);
		delete[] tv;
	}
	void savethroatdtr()
	{

		string fname=cg.filename+"_throatdtr.dat";
		FILE *fp=fopen(fname.c_str(),"w");

		cout << "save throat distribution\n";
		long throatnumber=rf.throats.size();
		voxel** tv = new voxel*[throatnumber];
		voxel** tp = tv;

		for(list<throatblock*>::iterator li=rf.throats.begin();li!=rf.throats.end();++li)
		{

				*tp++ = (*li)->v;

		}
		sort(tv, tv+throatnumber, metaballcomparer());	
		voxel** i;
		voxel** j = tv;
		voxel** end = tv+throatnumber;
		long cnt;
		while(j < end)
		{
			cnt=0;
			i=j;
			++j;
			while(j < end)
			{
				++cnt;
				if((*j)->ball->r2 < (*i)->ball->r2)
					break;

				++j;
			}
			fprintf(fp,"%E    %E\n",(double)cnt/(double)throatnumber, sqrt((double)(*i)->ball->r2)*cg.precision *0.000001);

		}
		fclose(fp);
		delete[] tv;
	}
	
	*/
public:
	config& cg;
	reference& rf;
};