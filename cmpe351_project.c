#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 5
#define LINE_MAX 1024


struct linkedList {
	
    	int Name; 
    	int bTime;
    	int aTime; 
    	int wTime;
    	int p;
    	int sr;
		
}

linkedList;

void FCFS(struct linkedList process[]){

	FILE *fptr;
	fptr = fopen("output.txt", "a");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	
	
    	struct linkedList *temp;
    	temp = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    	int i;
   	 	int totalWaiting=0;
    	double averageWaiting;

    for(i=0;i<SIZE;i++)
        temp[i]=process[i];

    struct linkedList list;
    int a,b;
    for(a=1;a<SIZE;a++) {
        for (b = 0; b < SIZE - a; b++) 
		
		{
            if (temp[b].aTime > temp[b + 1].aTime) {
            list = temp[b];
            temp[b] = temp[b + 1];
            temp[b + 1] = list;
            
            }
        }
    }

    totalWaiting = temp[0].wTime = 0;

    for(i = 1; i < SIZE; i++){
        temp[i].wTime = (temp[i-1].bTime + temp[i-1].aTime + temp[i-1].wTime) - temp[i].aTime;
        
        totalWaiting += temp[i].wTime;
    }
    
    	averageWaiting = (double)totalWaiting/SIZE;
    		fprintf(fptr, "%s" ,"\nScheduling Method : First Come First Served\nProcess Waiting Times:\n");

    for(i = 0; i < SIZE; i++) 
	
	{
		
        fprintf(fptr,"\nP%d: %d ms", i+1, temp[i].wTime);
    
	}

    fprintf(fptr, "\nAverage waiting time: %f ms\n",averageWaiting);
    printf("%s" ,"\nOutput is stored in the output file \n");
    fclose(fptr);
}

void SJFS_nonpreemptive(struct linkedList process[])

{
	
	FILE *fptr;
	fptr = fopen("output.txt", "a");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	
	
    	struct linkedList *temp, list, list2;
   	 	temp = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    	int i,a,b;
    	int totalWaitingTime=0;
    	double averageWaitingTime;

    for(i=0;i<SIZE;i++) {
        temp[i] = process[i];
        
    }

    for(a=1;a<SIZE;a++) {
        for (b = 0; b < SIZE - a; b++) 
		
		{
           		if (temp[b].aTime > temp[b + 1].aTime) {
            list2 = temp[b];
            temp[b] = temp[b + 1];
            temp[b + 1] = list2;
            
            }
        }
    }

    for(a=2;a<SIZE;a++) {
        for (b = 1; b < SIZE - a+1; b++) 
		{
            	if (temp[b].bTime > temp[b + 1].bTime) {
            list = temp[b];
            temp[b] = temp[b + 1];
            temp[b + 1] = list;
            }
        }
    }

    totalWaitingTime = temp[0].wTime = 0;

    for(i = 1; i < SIZE; i++)
	
	{
        temp[i].wTime = (temp[i-1].bTime + temp[i-1].aTime + temp[i-1].wTime) - temp[i].aTime;
        totalWaitingTime += temp[i].wTime;
    }

    averageWaitingTime = (double)totalWaitingTime/SIZE;

    for(a=1;a<SIZE;a++) 
	
	{
        for (b = 0; b < SIZE - a; b++) 
		
		{
            	if (temp[b].Name > temp[b + 1].Name) {
            list = temp[b];
            temp[b] = temp[b + 1];
            temp[b + 1] = list;
            }
        }
    }

    fprintf(fptr, "%s" , "\nScheduling Method : Shortest Job First Scheduling (Non-Preemptive)\nProcess Waiting Times:");
   
    for(i = 0; i < SIZE; i++) 
	
	{
        fprintf(fptr,"\nP%d: %d ms", i+1, temp[i].wTime);
    }
    
    
    fprintf(fptr,"\nAverage waiting time: %f ms\n",averageWaitingTime);
    printf("%s" ,"\nOutput is stored in the output file \n");
    fclose(fptr);
    
}

void SJFS_preemptive(struct linkedList process[])

{
	
	FILE *fptr;
	fptr = fopen("output.txt", "a");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	
	
    	struct linkedList *temp;
    	temp = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    	int i,x,timer,shortestJob,totalBurstTime;
    	int totalWaitingTime=0;
    	double averageWaitingTime;

    for(i=0;i<SIZE;i++) 
	
	{
        temp[i] = process[i];
        totalBurstTime += process[i].bTime;
    }

    struct linkedList list;
    int a,b;
    for(a=1;a<SIZE;a++) 
	
	{
        for (b = 0; b < SIZE - a; b++) 
		
		{
           		 if (temp[b].aTime > temp[b + 1].aTime) {
            list = temp[b];
            temp[b] = temp[b + 1];
            temp[b + 1] = list;
            }
        }
    }

    totalWaitingTime = temp[0].wTime = 0;

    i=0;
    for (timer = 0; timer < totalBurstTime; timer++) 
	
	{
        if(temp[i].bTime > 0 && temp[i].aTime <= timer)
            temp[i].bTime--;

        if(temp[i].bTime<=0 && temp[i].sr != 1)
        
        {
            temp[i].sr = 1;
            temp[i].wTime = (timer+1) - process[i].bTime - temp[i].aTime;
            totalWaitingTime+=temp[i].wTime;
        }
        
        shortestJob = 65435;
        for(x = 0; x < SIZE; x++)
		{

            if(temp[x].aTime <= (timer+1) && temp[x].sr != 1){

                if(shortestJob != temp[x].bTime && shortestJob > temp[x].bTime){
                    shortestJob = temp[x].bTime;
                    i=x;
                }
            }
        }
    }

    averageWaitingTime = (double)totalWaitingTime/SIZE;

    fprintf(fptr , "%s" , "\nScheduling Method : Shortest Job Scheduling (Preemptive)\nProcess Waiting Times:");
   
    for(i = 0; i < SIZE; i++)
	
	{
        fprintf(fptr , "\nP%d: %d ms", i+1, temp[i].wTime);
    }

    fprintf(fptr,"\nAverage waiting time: %f ms\n",averageWaitingTime);
    printf("%s" ,"\nOutput is stored in the output file \n");
    fclose(fptr);
}



void PS_preemptive(struct linkedList process[], FILE *fp



){
    struct linkedList *temp;
    temp = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    int i,x,timer,minimumPriority,totalBurstTime;
    int totalWaitingTime=0;
    double averageWaitingTime;
    
	FILE *fptr;
	fptr = fopen("output.txt", "a");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
    for(i=0;i<SIZE;i++) 
	
	{
        temp[i] = process[i];
        totalBurstTime += process[i].bTime;
    }

    struct linkedList list;
    int a,b;
    for(a=1;a<SIZE;a++) 
	
	{
        for (b = 0; b < SIZE - a; b++) {
            if (temp[b].aTime > temp[b + 1].aTime) {
                list = temp[b];
                temp[b] = temp[b + 1];
                temp[b + 1] = list;
            }
        }
    }

    totalWaitingTime = temp[0].wTime = 0;

    i=0;
    for (timer = 0; timer < totalBurstTime; timer++) 
	
	{
        if(temp[i].bTime > 0 && temp[i].aTime <= timer)
            temp[i].bTime--;

        if(temp[i].bTime<=0 && temp[i].sr != 1)
        
        {
            temp[i].sr = 1;
            temp[i].wTime = (timer+1) - process[i].bTime - temp[i].aTime;
            totalWaitingTime+=temp[i].wTime;
        }
        minimumPriority = 65435;
        for(x = 0; x < SIZE; x++)
		
		{

            if(temp[x].aTime <= (timer+1) && temp[x].sr != 1){

                if(minimumPriority != temp[x].p && minimumPriority > temp[x].p){
                    minimumPriority = temp[x].p;
                    i=x;
                }
            }
        }
    }

    averageWaitingTime = (double)totalWaitingTime/SIZE;

    fprintf(fptr  ,  "%s" , "\nScheduling Method : Priority Scheduling (Preemptive)\nProcess Waiting Times:");
 
    for(i = 0; i < SIZE; i++) {
        fprintf(fptr , "\nP%d: %d ms", i+1, temp[i].wTime);
    }
    
    fprintf(fptr,"\nAverage waiting time: %f ms\n",averageWaitingTime);
    printf("%s" ,"\nOutput is stored in the output file \n");
    fclose(fptr);
}


void PS_nonpreemptive(struct linkedList process[]){
    struct linkedList *temp;
    temp = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    struct  linkedList list1,list2;
    int i,j,x,y;
    int totalWaitingTime=0;
    double averageWaitingTime;
    
    FILE *fptr;
	fptr = fopen("output.txt", "a");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	
	
    for(i=0;i<SIZE;i++) 
	
	{
        temp[i] = process[i];
    }

    for(i=2;i<SIZE;i++)
        for(j=1;j<SIZE-i+1;j++){
            if(temp[j].p > temp[j+1].p)
			
			{
                list1 = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = list1;
            }
        }

    totalWaitingTime = temp[0].wTime = 0;

    for(i=1;i<SIZE;i++)
	
	{
        temp[i].wTime = (temp[i-1].bTime + temp[i-1].aTime + temp[i-1].wTime) - temp[i].aTime;
        totalWaitingTime+=temp[i].wTime;
    }
    averageWaitingTime = (double)totalWaitingTime/SIZE;

    for(x=1;x<SIZE;x++) 
	
	{
        for (y = 0; y < SIZE - x; y++) {
            if (temp[y].Name > temp[y + 1].Name) {
                list2 = temp[y];
                temp[y] = temp[y + 1];
                temp[y + 1] = list2;
            }
        }
    }


    fprintf(fptr , "%s" , "\nScheduling Method : Priority Scheduling (Non-Preemptive)\nProcess Waiting Times:");

    for(i = 0; i < SIZE; i++) {
        fprintf(fptr , "\nP%d: %d ms", i+1, temp[i].wTime);
    }

   
    fprintf(fptr,"\nAverage waiting time: %f ms\n",averageWaitingTime);
    printf("%s" ,"\nOutput is stored in the output file \n");
    fclose(fptr);
}

void RR(struct linkedList process[], int quantumTime){
    int i,x;
    int y = 0;
    int resumeStatus=0;
    int currentTime=0;
    int totalWaitingTime=0;
    double averageWaiting;
    struct linkedList *temp1, *temp2;
    temp1 = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    temp2 = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    
    FILE *fptr;
	fptr = fopen("output.txt", "a");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}

    for(i=0;i<SIZE;i++)
        temp1[i]=process[i];

    struct linkedList list;
    int a,b;
    for(a=1;a<SIZE;a++) {
        for (b = 0; b < SIZE - a; b++) {
            if (temp1[b].aTime > temp1[b + 1].aTime) {
                list = temp1[b];
                temp1[b] = temp1[b + 1];
                temp1[b + 1] = list;
            }
        }
    }

    for(i = 0;i < SIZE; i++)
        temp2[i]=temp1[i];

    do{
        if(y>SIZE-1){y=0;}

        x=0;
        while(x<quantumTime && temp1[y].bTime > 0){
            x++;
            currentTime++;
            temp1[y].bTime--;
        }

        if(temp1[y].bTime <= 0 && temp1[y].sr != 1){
            temp1[y].wTime = currentTime - temp2[y].bTime - temp1[y].aTime;
            resumeStatus++;
            temp1[y].sr = 1;
            totalWaitingTime = totalWaitingTime + temp1[y].wTime;
        }
        y++;
    }while (resumeStatus < SIZE);

    averageWaiting = (double)totalWaitingTime/SIZE;
   
    fprintf(fptr  , "%s" ,"\nScheduling Method : Round-Robin\nProcess Waiting Times:");
   
    fprintf(fptr,"\nAverage waiting time: %f ms\n",averageWaiting);
    
    fprintf(fptr,"Scheduling Method : First Come First Served\nProcess Waiting Times:");

    for(i = 0; i < SIZE; i++) {
        fprintf(fptr,"\nP%d: %d ms", i+1, temp1[i].wTime);
    }
    fprintf(fptr,"\nAverage waiting time: %f ms\n",averageWaiting);
    printf("%s" ,"\nOutput is stored in the output file \n");
    fclose(fptr);
}



int main(int argc, char **argv) 

	{
    	struct linkedList *process;
    	process = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    	int i = 0;
    	int mode = 0;
    	int choice,option,option2,quantumTime;
    

    FILE *fp = fopen("input.txt", "r");
    
    
    char line[LINE_MAX];
    char *ovalue = NULL;
    unsigned int num[3];



    opterr = 0;

    while ((choice = getopt (argc, argv, "f:o:")) != -1)
        switch (choice)
        {
            case 's':
                if ((fp = fopen(optarg, "r")) == NULL)
                    return 0;
                    
                while (fgets(line, LINE_MAX, fp) != NULL) {
                    sscanf(line,"%d:%d:%d\n",&num[0],&num[1],&num[2]);
                    process[i].Name = i+1;
                    process[i].bTime = num[0];
                    process[i].aTime = num[1];
                    process[i].p = num[2];
                    i++;
                }
                fclose(fp);
                break;
            case 'o':
                ovalue = optarg;
                fp = fopen(optarg,"w");
                break;
            default:
                abort ();
        }
        
        printf("\t\t\t\t\t CPU Scheduler Simulator\n");
        
    do{
        if (mode == 0)
            printf("\nMODE : Preemptive\n\n");
            
        else if (mode == 1)
            printf("\nMODE : Non-Preemptive\n"); 
            
            
        printf("1- Scheduling Method (None)\n");
        printf("2- Preemptive Mode\n");
        printf("3- Non-Preemptive Mode\n");
        printf("4- Show Result\n");
        printf("5- End Program\n");
        printf("Option> ");
        scanf("%d",&option);
        switch (option)
		
		{
            case 1:
                if (mode == 0)
                    printf("\n\n\n\n MODE : Preemptive\n");
                    
                else if (mode == 1)
                    printf("\nMODE : Non-Preemptive\n"); 
                    
                printf("1- First Come, First Served Scheduling\n");
                printf("2- Shortest-Job-First Scheduling\n");
                printf("3- Priority Scheduling\n");
                printf("4- Round-Robin Scheduling\n");
                printf("5- Back\n");
                printf("\n\n");
                printf("Option> ");
                
                scanf("%d",&option2);
                switch (option2)
                
				
				{
                    case 1:
                       		FCFS(process);
                        break;
                    case 2:
                        if (mode == 0){
                            SJFS_preemptive(process);
                        }
                        if (mode == 1){
                            SJFS_nonpreemptive(process);
                        }
                        break;
                    case 3:
                        if (mode == 0){
                            PS_preemptive(process,fp);
                        }
                        if (mode == 1){
                            PS_nonpreemptive(process);
                        }
                        break;
                        
                    case 4:
                        printf("\nEnter quantum time : ");
                        scanf("%d",&quantumTime);
                        RR(process, quantumTime);
                        break;
                        
                    case 5:
                        break;
                        
                    default:
                        printf("Invalid Option! Please Choose From 1 - 5\n");
                        break;
                }
                break;
                
            case 2:
                mode = 0;
                break;
            case 3:
                mode = 1;
                break;


            case 4:
                fp = fopen(ovalue, "r");
                while (fgets(line, LINE_MAX, fp)){
                    printf(line);
                }
                break;
                
            case 5:
                abort();
                
            default:
                printf("\nInvalid Option! Please Choose From 1 to 5 \n");
                break;
        }
    }
	
	while (option != 5);
    return 0;
}
