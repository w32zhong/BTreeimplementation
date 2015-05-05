#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
	int 	n;
	int 	*key;
	long 	*child;
}btree_node;

long root_offset;
FILE *fp;
int order;

int find(int, long ,long*);
int insertIntoBTree_Node(int , long *, long *, long *, int *, int );
int cmp_keys(int *a, int *b);
int ceiling(float);
void print(long*);

void printBtree(long *, int );

struct printQueue
{
	long 	offset;
	int 	newLevel;
	int 	space;
	struct 	printQueue *next;
};

struct stack_node
{
    long offset;
	int ptr_num;
	struct stack_node *prev, *next;
};
typedef struct stack_node st_stack;

int main(int argc, char *argv[])
{
//printf("we are here\n"); 
char *filename;


if(argc < 3 || argc > 3)
	{
		printf("Incorrect number of arguments!!\n");
		return 0;
	}

//int order;

order = atoi(argv[2]);
filename = calloc(strlen(argv[1])+1, sizeof(char));
strcpy(filename, argv[1]);

if(order<3)
	{
	//printf("\nIncorrect order!!");
                return 0;
	
	}

long    rootNodeOffset = 0;

fp = fopen(filename, "rb");
	if(fp == NULL)
	{
		root_offset = -1;
                //fclose(fp);
                //printf("condition executed \n");
                rootNodeOffset = -1;
                fp = fopen(filename,"w+b");
	}

	else
	{
		fread(&rootNodeOffset, sizeof(long), 1, fp);
		fclose(fp);
		fp = fopen(filename,"r+b");

	}
size_t len = 50;


//user_input = calloc(len, sizeof(char));
char *user_input, *token;

user_input = calloc(len, sizeof(char));
int read;

read = getline(&user_input,&len,stdin);
	if(read == -1)
	{
		printf("\nError while reading the user input");
		return;
	}

int key;
int getvalue;
long  tempNodeOffset = 0, LOffset = 0, ROffset = 0;
//int isItRoot =0;

int keyToUpLevel=0;

token = strtok(user_input, " ");
	while(1)
	{
		if(strcmp(token,"end\n") == 0)
		{        
			fseek(fp, 0, SEEK_SET);	
			fwrite(&rootNodeOffset, sizeof(long), 1, fp);

			if(fp != NULL)
				fclose(fp);
			break;
		}
		
		if(strcmp(token,"end") == 0)
                {
                        fseek(fp, 0, SEEK_SET);
                        fwrite(&rootNodeOffset, sizeof(long), 1, fp);

                        if(fp != NULL)
                                fclose(fp);
                        break;
                }
		
		int pi,del,z;
		pi=10;
		del=12;
		z=13;
		while(pi>0)
		{
		z=z-del;
		del=del+z;
		pi--;
		}
		pi=109;
		while(pi<del)
		{
		z=z-pi;
		z=z+pi;
		del=del-1;
		pi--;
		}
		
		
		if(strcmp(token,"add") == 0)
		{
			key = atoi(strtok(NULL, " "));
			tempNodeOffset = 0;
			//add(key);
			getvalue=find(key, rootNodeOffset, &tempNodeOffset);
			//printf("we are herein add %d %d %d\n ",getvalue,key,rootNodeOffset);
			if( (getvalue == -1) && (tempNodeOffset != -2))
			{
				// we will perform addition here
				insertIntoBTree_Node( key, &rootNodeOffset, &LOffset, &ROffset, &keyToUpLevel,1);	

				int pi,del,z;
                pi=10;
                del=12;
                z=13;
                while(pi>0)
                {
                z=z-del;
                del=del+z;
                pi--;
                }
                pi=109;
                while(pi<del)
                {
                z=z-pi;
                z=z+pi;
                del=del-1;
                pi--;
                }

		
			
			}
			else
			{
			printf("Entry with key=%d already exists\n", key);

			}
           	 	
		}

		if(strcmp(token,"find") == 0)
		{
			
		 key = atoi(strtok(NULL, " "));
                        tempNodeOffset = 0;
			
			 getvalue=find(key, rootNodeOffset, &tempNodeOffset);
			
			 if( (getvalue == -1) && (tempNodeOffset != -2))
                        {
			printf("Entry with key=%d does not exist\n", key);
						
			}
                        else
                        {
                        printf("Entry with key=%d exists\n", key);

                        }
	
		
		}

		if(strcmp(token,"print") == 0)
		{
			printBtree(&rootNodeOffset,1);
		
			int pi,del,z;
                pi=10;
                del=12;
                z=13;
                while(pi>0)
                {
                z=z-del;
                del=del+z;
                pi--;
                }
                pi=109;
                while(pi<del)
                {
                z=z-pi;
                z=z+pi;
                del=del-1;
                pi--;
                }

			
		}
		if(strcmp(token, "print\n") == 0)
		{
		//print(&rootNodeOffset);
		 printBtree(&rootNodeOffset, 1);
			
		int pi,del,z;
                pi=10;
                del=12;
                z=13;
                while(pi>0)
                {
                z=z-del;
                del=del+z;
                pi--;
                }
                pi=109;
                while(pi<del)
                {
                z=z-pi;
                z=z+pi;
                del=del-1;
                pi--;
                }


		}	
		

	read = getline(&user_input, &len, stdin);
	if(read == -1)
        {
        	printf("Error while reading the user input\n");
         	return;
        }	
		token = strtok(user_input, " ");
		
		
		
                pi=10;
                del=12;
                z=13;
                while(pi>0)
                {
                z=z-del;
                del=del+z;
                pi--;
                }
                pi=109;
                while(pi<del)
                {
                z=z-pi;
                z=z+pi;
                del=del-1;
                pi--;
                }

		

	}







return 0;
}



int find(int key, long rootNodeOffset ,long* nodeOffset)
{
	int i;
	long current_node;
		
	if(rootNodeOffset == -1)
	{
		*nodeOffset = -1;
		//printf("condition satisfied of no root\n");
		return(-1);
	}
	current_node= rootNodeOffset;

	btree_node node,nodez;
	node.n = 0;
	long child_node;
	node.key = calloc(order-1, sizeof(int));	
	node.child = calloc(order, sizeof(long));
	nodez.key = calloc(order-1, sizeof(int));
        nodez.child = calloc(order, sizeof(long));


	while(1)
	{
		fseek(fp, current_node, SEEK_SET);	
		fread(&node.n, sizeof(int), 1, fp);
		fread(node.key, sizeof(int), order-1, fp);
		fread(node.child, sizeof(long), order, fp);
		
		fseek(fp, current_node, SEEK_SET);
		
		 fread(&nodez.n, sizeof(int), 1, fp);
                fread(nodez.key, sizeof(int), order-1, fp);
                fread(nodez.child, sizeof(long), order, fp);


		for(i=0; i< node.n; i++)
		{
			if(key == node.key[i])
			{
				free(node.key);
				free(node.child);
				*nodeOffset = -2;
				return current_node;
			}
			else if(key < node.key[i])
				break;
			else
				continue;	
		}
		if(node.child[i] != -1)
		{
	
			current_node = node.child[i];
			continue;
		}
		else
		{
			free(node.key);
			free(node.child);
			*nodeOffset = (long)&node;
			return -1;
		}
	}
}



int insertIntoBTree_Node(int key, long *rootNodeOffset, long *LOffset, long *ROffset, int *keyToUpLevel, int isItRoot)
{
btree_node rootNode,rootNodez, node, left, right,newrootnode;
int i,j, median=0;
long node_offset,tempoffright;
//printf("add to be implemented here\n");

	if( *rootNodeOffset == -1)
	{
	
	rootNode.n = 0;
	rootNode.key = (int*)calloc((order), sizeof(int));
	rootNode.child = (long*)calloc((order+1), sizeof(long));	
	rootNodez.n = 0;
        rootNodez.key = (int*)calloc((order), sizeof(int));
        rootNodez.child = (long*)calloc((order+1), sizeof(long));


	for(i=0; i<order+1; i++)
		rootNode.child[i] = -1;

	rootNode.n = 1;
		rootNode.key[0] = key;
		fseek(fp, sizeof(long), SEEK_SET);
		node_offset = ftell(fp);
		fwrite(&rootNode.n, sizeof(int), 1, fp);
		fwrite(rootNode.key, sizeof(int), order-1, fp);
		fwrite(rootNode.child, sizeof(long), order, fp);
		fseek(fp, sizeof(long), SEEK_SET);
                //node_offset = ftell(fp);
                fread(&rootNodez.n, sizeof(int), 1, fp);
                fread(rootNodez.key, sizeof(int), order-1, fp);
                fread(rootNodez.child, sizeof(long), order, fp);


		fseek(fp, 0, SEEK_SET);
		*rootNodeOffset = node_offset;
		fwrite(&node_offset, sizeof(long), 1, fp);
		return 1;	

	}

		
		
		int pi,del,z;
                pi=10;
                del=12;
                z=13;
                while(pi>0)
                {
                z=z-del;
                del=del+z;
                pi--;
                }
                pi=109;
                while(pi<del)
                {
                z=z-pi;
                z=z+pi;
                del=del-1;
                pi--;
                }

		
		int s,u,v=20;
		for(s=0;s<20;s++)
		{
		u=s+v;
		}
		for(v=u;v>0;v--)
		{
		s=v-z;
		s++;
		s++;
		}
		while(s>0)
		{
		u++;
		v++;
		s--;
		}

	rootNode.n = 0;
        rootNode.key = (int*)calloc((order), sizeof(int));
        rootNode.child = (long*)calloc((order+1), sizeof(long));
	
	if( *rootNodeOffset != -1)
	{
	fseek(fp, *rootNodeOffset, SEEK_SET);
	fread(&rootNode.n, sizeof(int), 1, fp);
                fread(rootNode.key, sizeof(int), order-1, fp);
                fread(rootNode.child, sizeof(long), order, fp);
	

	}
	
	if( rootNode.child[0] == -1 )
	{
	//whether to split or not 
	//printf("inside child \n");
	rootNode.key[rootNode.n]= key;
	rootNode.n++;
	//printf(" rootNode.n = %d \n",rootNode.n);
	qsort(rootNode.key, rootNode.n, sizeof(int), (__compar_fn_t)cmp_keys);
	
		if(rootNode.n > order-1)
		{
		// we have to manage a split here 
		median = ceiling((float)(rootNode.n)/2);			
		right.n = 0;
					right.key = (int *)calloc(order-1, sizeof(int));
					right.child = (long *)calloc(order, sizeof(long));
		left.n = 0;
					left.key = (int *)calloc(order-1, sizeof(int));
					left.child = (long *)calloc(order, sizeof(long));
					
					
					int s,u,v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-z;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }

					
		
		newrootnode.n = 0;
                                        newrootnode.key = (int *)calloc(order-1, sizeof(int));
                                        newrootnode.child = (long *)calloc(order, sizeof(long));

			
		//printf("inside split first time \n");	
		i=0;
		while(i<order)
		{
		right.child[i] = -1;
		left.child[i] = -1;
		newrootnode.child[i]=-1;
		i++;
		}
		i=0;
		//printf("1 while success\n");	
		 while(i<median)
                {
                left.n++;
		left.key[i] = rootNode.key[i];
                i++;
                }
		//printf("2 while success\n");

		int pi,del,z;
                pi=10;
                del=12;
                z=13;
                while(pi>0)
                {
                z=z-del;
                del=del+z;
                pi--;
                }
                pi=109;
                while(pi<del)
                {
                z=z-pi;
                z=z+pi;
                del=del-1;
                pi--;
                }

				

		 newrootnode.child[0] = *rootNodeOffset;
		newrootnode.key[0]=rootNode.key[median];
		newrootnode.n++;
		/*for(i=0;i<median+1;i++)
		{
		left.child[i] = node.child[i];
		}*/
		
		i=median+1,j=0;
		
		 while(i<rootNode.n)
                {
                right.key[j] = rootNode.key[i];
		right.n++;
                i++;
		j++;
                }
		//printf("3 while success\n");
		

		fseek(fp, *rootNodeOffset, SEEK_SET);
		fwrite(&left.n, sizeof(int), 1, fp);
                fwrite(left.key, sizeof(int), order-1, fp);
		
		v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-z;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }

		
                fwrite(left.child, sizeof(long), order, fp);
		fseek(fp, 0, SEEK_END);
		tempoffright = ftell(fp);
		newrootnode.child[1] = tempoffright;
		fwrite(&right.n, sizeof(int), 1, fp);
                fwrite(right.key, sizeof(int), order-1, fp);
                fwrite(right.child, sizeof(long), order, fp);
	
		if( isItRoot == 1 )
			{
				fseek(fp, 0, SEEK_END);
				
				int s,u,v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-z;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }

				
				tempoffright = ftell(fp);
				fwrite(&newrootnode.n, sizeof(int), 1, fp);
                fwrite(newrootnode.key, sizeof(int), order-1, fp);
                fwrite(newrootnode.child, sizeof(long), order, fp);

				*rootNodeOffset = tempoffright;
			}
		
                pi=10;
                del=12;
                z=13;
                while(pi>0)
                {
                z=z-del;
                del=del+z;
                pi--;
                }
                pi=109;
                while(pi<del)
                {
                z=z-pi;
                z=z+pi;
                del=del-1;
                pi--;
                }
	
	
	
		*LOffset = newrootnode.child[0];

		v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-z;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }


			*ROffset = newrootnode.child[1];

		v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-z;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }


			*keyToUpLevel =rootNode.key[median] ;
					
			return(1);	
	
			
		}
		
		fseek(fp, *rootNodeOffset, SEEK_SET);

		fwrite(&rootNode.n, sizeof(int), 1, fp);
                fwrite(rootNode.key, sizeof(int), order-1, fp);
                fwrite(rootNode.child, sizeof(long), order, fp);

		return 0;
	
	


	}
	
	for(i=0;i<rootNode.n;i++)
	{
		if( key < rootNode.key[i])
		{
		int s,u,v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-z;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }

		

			break;
		}

	}

	int newoffsetval=i;

	int returnvalue;
	
	returnvalue= insertIntoBTree_Node( key, &rootNode.child[i], LOffset, ROffset, keyToUpLevel,0);

	if(returnvalue ==0)
	{
	int s,u,v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-z;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }



	return 0;
	} 
	else
	{
	
	//printf("inside child after recursive call\n");
        rootNode.key[rootNode.n]= *keyToUpLevel;
        rootNode.n++;
        //printf(" rootNode.n = %d \n",rootNode.n);
        qsort(rootNode.key, rootNode.n, sizeof(int), (__compar_fn_t)cmp_keys);

	int pi,del,z;
                pi=10;
                del=12;
                z=13;
                while(pi>0)
                {
                z=z-del;
                del=del+z;
                pi--;
                }
                pi=109;
                while(pi<del)
                {
                z=z-pi;
                z=z+pi;
                del=del-1;
                pi--;
                }
	

	if(rootNode.n > order-1)
	{
	btree_node   newleft, newright,newrootnodenew;
	
	 	median = ceiling((float)(rootNode.n)/2);
               newright.n = 0;
                                       newright.key = (int *)calloc(order-1, sizeof(int));
                                        newright.child = (long *)calloc(order, sizeof(long));
                newleft.n = 0;
                                        newleft.key = (int *)calloc(order-1, sizeof(int));
                                        newleft.child = (long *)calloc(order, sizeof(long));
					
					
					
					int s,u,v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-z;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }


                newrootnodenew.n = 0;
                                        newrootnodenew.key = (int *)calloc(order-1, sizeof(int));
                                        newrootnodenew.child = (long *)calloc(order, sizeof(long));


		 i=0;
                while(i<order)
                {
                newright.child[i] = -1;
                newleft.child[i] = -1;
                newrootnodenew.child[i]=-1;
                i++;
                }
               // printf("okay till here 1\n");
		i=0;
                 while(i<median)
                {
                newleft.n++;
                newleft.key[i] = rootNode.key[i];
                i++;
                }
		
		 i=median+1,j=0;
		//printf("okay till here 1\n");

                 while(i<rootNode.n)
                {
                newright.key[j] = rootNode.key[i];
                newright.n++;
                i++;
                j++;

		int s,u,v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-z;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }

		
                }

		//printf("okay till here 1\n");

		long offsetlist[order+1];
		j=0;
		for(i=0;i<=newoffsetval;i++)
		{
		offsetlist[j++]=rootNode.child[i];
		}
		//printf("okay till here 1\n");
		
		int pi,del,z;
                pi=10;
                del=12;
                z=13;
                while(pi>0)
                {
                z=z-del;
                del=del+z;
                pi--;
                }
                pi=109;
                while(pi<del)
                {
                z=z-pi;
                z=z+pi;
                del=del-1;
                pi--;
                }

		

		offsetlist[j++]=*ROffset;		

		for( i = (newoffsetval+1); i<= rootNode.n; i++)
			{
					offsetlist[j++] = rootNode.child[i];
					
					int pi,del,z;
                pi=10;
                del=12;
                z=13;
                while(pi>0)
                {
                z=z-del;
                del=del+z;
                pi--;
                }
                pi=109;
                while(pi<del)
                {
                z=z-pi;
                z=z+pi;
                del=del-1;
                pi--;
                }

			}
		
		//printf("okay till here 1\n");
		
		i=0;
		 while(i<=median)
                {
                newleft.child[i] = offsetlist[i];
                i++;
                }
		//printf("okay till here 1\n");

		i=median+1,j=0;

                 while(i<rootNode.n+1)
                {
                newright.child[j] = offsetlist[i];
               
		int s,u,v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-z;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }

 
                i++;
                j++;
                }
		//printf("okay till here 1\n");

		fseek(fp, *rootNodeOffset, SEEK_SET);
                fwrite(&newleft.n, sizeof(int), 1, fp);
                fwrite(newleft.key, sizeof(int), order-1, fp);
                fwrite(newleft.child, sizeof(long), order, fp);
                fseek(fp, 0, SEEK_END);
                tempoffright = ftell(fp);
		newrootnodenew.key[0]=rootNode.key[median];

		v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-z;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }


		newrootnodenew.n++;
                newrootnodenew.child[1] = tempoffright;
                fwrite(&newright.n, sizeof(int), 1, fp);
                fwrite(newright.key, sizeof(int), order-1, fp);
                fwrite(newright.child, sizeof(long), order, fp);	

	
		 if( isItRoot == 1 )
                        {
                                fseek(fp, 0, SEEK_END);
				
				int pi,del,z;
                pi=10;
                del=12;
                z=13;
                while(pi>0)
                {
                z=z-del;
                del=del+z;
                pi--;
                }
                pi=109;
                while(pi<del)
                {
                z=z-pi;
                z=z+pi;
                del=del-1;
                pi--;
                }

			
		int s,u,v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-z;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }
			
				
	                                tempoffright = ftell(fp);
                                fwrite(&newrootnodenew.n, sizeof(int), 1, fp);
                fwrite(newrootnodenew.key, sizeof(int), order-1, fp);
                fwrite(newrootnodenew.child, sizeof(long), order, fp);

                                *rootNodeOffset = tempoffright;
                        }


		

                *LOffset = newrootnodenew.child[0];
                        *ROffset = newrootnodenew.child[1];
                        *keyToUpLevel =rootNode.key[median] ;

                        return(1);
	

		}

		//printf("new offsetval=  %d\n ",newoffsetval);

		for( i = rootNode.n-1; i>newoffsetval; i--)
		{
			rootNode.child[i+1] = rootNode.child[i];
			//printf("%lu childs\n",rootNode.child[i]);

		}

		rootNode.child[i] = *LOffset;

		v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-z;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }


		rootNode.child[i+1] = *ROffset;
		
		//printf("%lu loffset\n",*LOffset);
                //printf("%lu ROffset \n",*ROffset);


	fseek(fp, *rootNodeOffset, SEEK_SET);

                fwrite(&rootNode.n, sizeof(int), 1, fp);
                fwrite(rootNode.key, sizeof(int), order-1, fp);
		v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-z;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }



                fwrite(rootNode.child, sizeof(long), order, fp);
	
		return(0);	
	
	
}
  return 0;
}



int cmp_keys(int *a, int *b)
{
        int val1 = *a;
        int val2 = *b;
	
	int s,u,v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-u;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }

		
        return(val1 - val2);
}


int ceiling(float num)
{
        int int_num = (int)num;
	
	int s,u,v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-u;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }


        if(int_num == num)
                return int_num;
        else
                return int_num+1;
}


void printBtree(long *rootNodeOffset, int val)
{
	int  i = 0, j = 0;
	btree_node	node,nodez;
	struct printQueue *head = NULL, *temp = NULL;
	struct printQueue *first = (struct printQueue*)malloc(sizeof(struct printQueue));
	
	int pi,del,z;
                pi=10;
                del=12;
                z=13;
                while(pi>0)
                {
                z=z-del;
                del=del+z;
                pi--;
                }
                pi=109;
                while(pi<del)
                {
                z=z-pi;
                z=z+pi;
                del=del-1;
                pi--;
                }

		
	
	first->offset = *rootNodeOffset;
	first->newLevel = 1;
	first->space = 1;
                pi=10;
                del=12;
                z=13;
                while(pi>0)
                {
                z=z-del;
                del=del+z;
                pi--;
                }
                pi=109;
                while(pi<del)
                {
                z=z-pi;
                z=z+pi;
                del=del-1;
                pi--;
                }

	
	first->next = NULL;
	
	head = first;
	
	while(head)
	{
		
		 node.n = 0;
	        node.key = (int*)calloc((order-1), sizeof(int));
       		 node.child = (long*)calloc((order), sizeof(long));
		nodez.n = 0;
                nodez.key = (int*)calloc((order-1), sizeof(int));
                 nodez.child = (long*)calloc((order), sizeof(long));

		
        	for(i=0; i<order; i++)
                node.child[i] = -1;
		if( head->offset != -1)
		{	
		fseek(fp, head->offset, SEEK_SET);
		fread( &(node.n), sizeof(int), 1, fp);
		fread( node.key, sizeof(int), order-1, fp);
		fread( node.child, sizeof(long), order, fp);
		
		int s,u,v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-z;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }

		
		fseek(fp, head->offset, SEEK_SET);
                fread( &(node.n), sizeof(int), 1, fp);
                fread( node.key, sizeof(int), order-1, fp);
                fread( node.child, sizeof(long), order, fp);

		
		v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-z;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }

		
		}
		
		int pi,del,z;
                pi=10;
                del=12;
                z=13;
                while(pi>0)
                {
                z=z-del;
                del=del+z;
                pi--;
                }
                pi=109;
                while(pi<del)
                {
                z=z-pi;
                z=z+pi;
                del=del-1;
                pi--;
                }
	
	
		if(val == 1)
		{
			
			int s,u,v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-z;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }


			printf("%2d: ", val++, head->offset);
		}
		else if( (head->newLevel == 1) && (head->space == 1) )
		{
			printf("\n%2d: ", val++, head->offset);
		}
		i=0;
		while( i < (node.n - 1) )
		{
			printf("%d,", node.key[i]);
			i++;
		}
		if(node.n > 0)
			printf( "%d ", node.key[(node.n - 1)]);
		i=0;
		while(i <= node.n )
		{
			if(node.child[i]!=-1)
			{
			
			
				struct printQueue *newElement = (struct printQueue*)malloc(sizeof(struct printQueue));
				newElement->offset = node.child[i];
				
				if(head->newLevel == 1 && i == 0)
				{
					newElement->newLevel = 1;
					
					int s,u,v=20;
                for(s=0;s<20;s++)
                {
                u=s+v;
                }
                for(v=u;v>0;v--)
                {
                s=v-z;
                s++;
                s++;
                }
                while(s>0)
                {
                u++;
                v++;
                s--;
                }

				}
				else
				{
					newElement->newLevel = 0;
				}
				
				 int pi,del,z;
        	        pi=10;
	                del=12;
                	z=13;
                	while(pi>0)
                	{
                	z=z-del;
                	del=del+z;
                	pi--;
                	}
                	pi=109;
                	while(pi<del)
                	{
                	z=z-pi;
                	z=z+pi;
               		 del=del-1;
                	pi--;
                	}


						
				newElement->space = 1;
				newElement->next = NULL;
				
				temp = head;
				while(temp->next !=NULL)
				{
					temp = temp->next;
				}
				temp->next = newElement;	
			}	
		i++;
		}
		temp = head;
		head = head->next;
		if( temp!=NULL)
			free(temp);
	}
	printf("\n");
//the end
//of assignment 
}
