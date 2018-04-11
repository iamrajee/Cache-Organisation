#include<stdio.h>

int tag[2][4];
int mru[4] = {1,1,1,1};

void mruUpdate(int i,int j){

	mru[i] = j;

}


int main(){

int addr,i,j,t;
int hits, accesses;
FILE *fp;

fp = fopen("trace.txt","r");
hits = 0;
accesses = 0;

	while(fscanf(fp,"%x",&addr) > 0){

	accesses += 1;
	printf("%3d: 0x%08x ", accesses, addr);

	i = (addr >> 2) & 3; // get block number or column index

	//printf("%d\n",i);

		for(j=0;j<2;j++){

			if(tag[j][i] == addr){

				hits += 1;
				printf("Hit%d ",i);
				//mru Update
				mru[i] = j;
				break;
			}
		}

		
		if (j == 2){

			
			printf("Miss ");
			int least_index;

			if(mru[i] == 1)
				least_index = 0;

			else 
				least_index = 1;

			tag[least_index][i] = addr;

			// mru update
			mru[i] = least_index;
	
		}


		for(int n=0;n<2;n++){
				for(int m=0;m<4;m++){
					printf("0x%08x ", tag[n][m]);

				}
			}

			printf("  ");

			for(int n=0;n<4;n++)
				printf("%d ",mru[n]);
						
			printf("\n");

	}

printf("Hits = %d, Accesses = %d, Hit ratio = %f\n", hits, accesses, ((float)hits)/accesses);

fclose(fp);


}
