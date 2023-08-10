//DSPD ASSIGNMENT R4 BATCH 
//ROLL .NO: BT21CSE084, BT21CSE086;
//NAMES: LAGISHETTI VARSHITH, NIMMA SHYAM KIRAN
#include<stdio.h>
#include<string.h>
#include<math.h>
struct temperature_record
{
	int station;
	int day;
	float sky_view_factor;
	float vegetation_density_ratio;
	int population_density;
	float pervious_surface_fraction;
	float impervious_surface_fraction;
	char station_satus[10];
	float distance_to_other_stations[];
	float air_temperature;
	float relative_humidity;
};
void intialize_DB(struct temperature_record temperature_DB[][30],int n)
{
	int i,j,k;
	for(i=0;i<n;i++)
	{
		for(j=0;j<30;j++)
		{
			temperature_DB[i][j].station=0;
			temperature_DB[i][j].day=0;
			temperature_DB[i][j].sky_view_factor=0;
			temperature_DB[i][j].vegetation_density_ratio=0;
			temperature_DB[i][j].population_density=0;
			temperature_DB[i][j].pervious_surface_fraction=0;
			temperature_DB[i][j].impervious_surface_fraction=0;
			temperature_DB[i][j].station_satus[0]='\0';
			temperature_DB[i][j].air_temperature=0;
			temperature_DB[i][j].relative_humidity=0;
			for(k=0;k<n;k++)
			{
				temperature_DB[i][j].distance_to_other_stations[k]=0;
			}
		}
	}
}
void highestHeatDegree(struct temperature_record temperature_DB[][30],int n,float avg)
{
	int i,j;
	int heat_degree_days[n];
	//INTIALIZING THE HEAT DEGREE DAYS ARRAY TO ZERO
	for(i=0;i<n;i++)
	{
		heat_degree_days[i]=0;
	}
	//STORING THE NO.OF HEAT DEGREE DAYS OF EVERY STATION IN THE ARRAY
	for(i=0;i<n;i++)
	{
		for(j=0;j<30;j++)
		{
			if(temperature_DB[i][j].air_temperature>avg)
			{
				heat_degree_days[i]++;
			}
		}
	}
	//FINDING THE MAXIMUM HEAT DEGREE DAYS 
	int max=heat_degree_days[0];
	for(i=0;i<n;i++)
	{
		if(max<heat_degree_days[i])
		{
			max=heat_degree_days[i];
		}
	}
	//PRINTING ALL THE STATIONS WITH HIGHEST HEAT DEGREE DAYS 
	printf("Stations with highest heat degree days are ");
	for(i=0;i<n;i++)
	{
		if(max==heat_degree_days[i])
		{
			printf("%d ");
		}
	}
	printf("\n");
}
void datesWithDecearsingVegetation(struct temperature_record temperature_DB[][30],int n,float avg)
{
	int i,j,k,sorted;
	struct temperature_record temp;
	//SORTING EVERY ROW IN DECRESING ORDER OF VEGETATION DENSITY
	for(i=0;i<n;i++)
	{
		sorted=0;
		for(j=0;(j<29)&&(sorted==0);j++)
		{
			sorted=1;
			for(k=0;k<29-j;k++)
			{
				if(temperature_DB[i][k].vegetation_density_ratio<temperature_DB[i][k+1].vegetation_density_ratio)
				{
					temp=temperature_DB[i][k];
					temperature_DB[i][k]=temperature_DB[i][k+1];
					temperature_DB[i][k+1]=temp;
					sorted=0;
				}
			}
		}
		//PRINTING THE DATES OF EACH STATION WHICH DECRESING VEGETATION DENSITY(CONSEDERING THE FACTOR OF AVG TEMPERARTURE)
		printf("List of dates of station %d with decreasing vegetation density order: ",i+1);
		for(j=0;j<30;j++)
		{
			if(temperature_DB[i][j].air_temperature>avg)
			{
				printf("%d ",temperature_DB[i][j].day);
			}
		}
		printf("\n");
	}
}
void kTopCitiesWithMinPopulation(struct temperature_record temperature_DB[][30],int n,int k)
{
	int i,j,sorted;
	struct temperature_record temp,t;
	//SORTING A COLOMN IN DECREASING POPULATION DENSITY
	for(i=0;(i<n-1)&&(sorted==0);i++)
	{
		sorted=1;
		for(j=0;j<n-1-i;j++)
		{
			if(temperature_DB[j][1].population_density>temperature_DB[j+1][1].population_density)
			{
				temp=temperature_DB[j][1];
				temperature_DB[j][1]=temperature_DB[j+1][1];
				temperature_DB[j+1][1]=temp;
				sorted=0;
			}
		}
	}
	//FINDING THE MAXIMUM TEAMPERATURE OF EACH SATION AND STORING IT IN AN ARRAY
	float max;
	float max_temp[n];
	for(i=0;i<n;i++)
	{
		max=temperature_DB[i][0].air_temperature;
		for(j=1;j<30;j++)
		{
			if(max<temperature_DB[i][j].air_temperature)
			{
				max=temperature_DB[i][j].air_temperature;
			}	
		}
		max_temp[i]=max;
	}
	//PRINTING TOP K STATIONS IN THE ORDER OF MIN POPULATION DENSITY(WITH CONSIDERING THE MAX TEMPERATURE OF STAION AS A FACTOR)
	for(i=0;i<k-1;i++)
	{
		if(temperature_DB[i][1].population_density==temperature_DB[i+1][1].population_density)
		{
			if(max_temp[i]>max_temp[i+1])
			{
				printf("%d ",temperature_DB[i][1].station);
			}
			else
			{
				printf("%d ",temperature_DB[i+1][1].station);
				t=temperature_DB[i][1];
				temperature_DB[i][1]=temperature_DB[i+1][1];
				temperature_DB[i+1][1]=t;
			}
		}
		else
		{
			printf("%d ",temperature_DB[i][1].station);
		}
		
	}
}
int nearestRuralStation(struct temperature_record temperature_DB[][30],int n,int x)
{
	int i,j,k,loc,loc1,found=0;
	float min;
	char s[]="rural";
	for(i=0;i<n &&found==0;i++)
	{
		if(strcmp(temperature_DB[i][1].station_satus,s)==0)
		{
			min=temperature_DB[x-1][1].distance_to_other_stations[i];
			found=1;
			loc1=i;
		}
	}
	for(i=loc1;i<n;i++)
	{
		if(temperature_DB[x-1][1].distance_to_other_stations[i]==min&&temperature_DB[i][1].pervious_surface_fraction>temperature_DB[loc][1].pervious_surface_fraction)
		{
			min=temperature_DB[x-1][1].distance_to_other_stations[i];
			loc=i;
		}
		else if(strcmp(temperature_DB[i][1].station_satus,s)==0&&temperature_DB[x-1][1].distance_to_other_stations[i]<min)
		{
			min=temperature_DB[x-1][1].distance_to_other_stations[i];
			loc=i;
		}
	}
	return loc;
}
void thermallyComfortableDays(struct temperature_record temperature_DB[][30],int n,int x)
{
	int nrs;
	char u[10]="urban";
	if(strcmp(temperature_DB[x-1][0].station_satus,u)==0)
	{
		nrs=nearestRuralStation(temperature_DB,n,x);//FINDING THE NEAREST RURAL STATION
		int i,min;
		float temp_diff[n];
		min=fabs(temperature_DB[x-1][0].air_temperature-temperature_DB[nrs][0].air_temperature);
		for(i=0;i<30;i++)
		{
			temp_diff[i]=fabs(temperature_DB[x-1][i].air_temperature-temperature_DB[nrs][i].air_temperature);//STORING TEAMPERATURE DIFF OF URBAN AND NEAREST RURAL STATION 
			if(temp_diff[n]<min)
			{
				min=temperature_DB[x-1][i].air_temperature;//FINDING MINIMUM TEAMPERRATURE DIFF
			}
		}
		for(i=0;i<30;i++)
		{
			if(temp_diff[i]==min)
			{
				printf("%d ",i+1);//PRINTING THE THERMALLY COMFORTABLE DAYS 
			}
		}
	}
	else
	{
		printf("You have entered an rural station");
	}
}
float avgStationTemperature(struct temperature_record temperature_DB[][30],int n,int x)
{
	int i;
	float avg,sum;
	for(i=0;i<30;i++)
	{
		sum=sum+temperature_DB[x-1][i].air_temperature;
	}
	avg=sum/30.0;
	return avg;
}
void heatIslandIntensity(struct temperature_record temperature_DB[][30],int n)
{
	int i,rs;
	float u_avg,r_avg,hii;
	char s[]="urban";
	for(i=0;i<n;i++)
	{
		//ALLOWING ONLY URBAN STATIONS
		if(strcmp(temperature_DB[i][1].station_satus,s)==0)
		{
			rs=nearestRuralStation(temperature_DB,n,i+1);
			u_avg=avgStationTemperature(temperature_DB,n,i+1);//CALUCULATING AVG TEAMPERATURE OF URBAN STATION
			r_avg=avgStationTemperature(temperature_DB,n,rs+1);//CALUCULATING AVG TEAMPERATURE OF NEAREST RURAL STATION STATION
			hii=u_avg-r_avg;//CALUCULATING NEAREST RURAL STATION
			printf("Heat Island Intensity of station %d: %.1f",i+1,hii);
		}
	}
}
main()
{
	int i,j,k,n; //n is no.of sations
	float  SKV,PD,PSF,ISF;
	char SS[10];
	printf("Enter no.of staions in city: ");
	scanf("%d",&n);
	float distance[n];
	struct temperature_record temperature_DB[n][30];
	//INTIALIZING THE DATA BASE
	intialize_DB(temperature_DB,n);
	//ENTERING THE DATA INTO THE DATA BASE
	for(i=0;i<n;i++)
	{
		printf("Enter the Sky View Factor of station %d: ",i+1);
		scanf("%f",&SKV);
		printf("Enter the Population Density of station %d: ",i+1);
		scanf("%d",&PD);
		printf("Enter the Pervious Surface Fraction of station %d: ",i+1);
		scanf("%f",&PSF);
		printf("Enter the Impervious Surface Fraction of station %d: ",j+1,i+1);
		scanf("%f",&ISF);
		printf("Enter the station staus of station %d: ",i+1);
		scanf("%s",SS);
		for(k=0;k<n;k++)
		{
			if(k==i)
			{
				distance[k]=0;
			}
			else
			{
				printf("Enter the distance from station %d to %d: ",i+1,k+1);
				scanf("%f",&distance[k]);
			}
		}
		for(j=0;j<30;j++)
		{
			temperature_DB[i][j].station=i+1;
			temperature_DB[i][j].day=j+1;
			temperature_DB[i][j].sky_view_factor=SKV;
			temperature_DB[i][j].population_density=PD;
			temperature_DB[i][j].pervious_surface_fraction=PSF;
			temperature_DB[i][j].impervious_surface_fraction=ISF;
			strcpy(temperature_DB[i][j].station_satus,SS);
			for(k=0;k<n;k++)
			{
				temperature_DB[i][j].distance_to_other_stations[k]=distance[k];
			}
			printf("Enter day %d Vegetation Density Ratio of station %d: ",j+1,i+1);
			scanf("%f",&temperature_DB[i][j].vegetation_density_ratio);
			printf("Enter day %d Air Temperature of station %d: ",j+1,i+1);
			scanf("%f",&temperature_DB[i][j].air_temperature);
			printf("Enter day %d Relative Density of station %d: ",j+1,i+1);
			scanf("%f",&temperature_DB[i][j].relative_humidity);
		}
	}
	//CREATING TWO TEMPERORY DATA BASE
	struct temperature_record temp1[n][30],temp2[n][30];
	for(i=0;i<n;i++)
	{
		for(j=0;j<30;j++)
		{
			temp1[i][j].station=temp2[i][j].station=temperature_DB[i][j].station;
			temp1[i][j].day=temp2[i][j].day=temperature_DB[i][j].day;
			temp1[i][j].sky_view_factor=temp2[i][j].sky_view_factor=temperature_DB[i][j].sky_view_factor;
			temp1[i][j].population_density=temp2[i][j].population_density=temperature_DB[i][j].population_density;
			temp1[i][j].pervious_surface_fraction=temp2[i][j].pervious_surface_fraction=temperature_DB[i][j].pervious_surface_fraction;
			temp1[i][j].impervious_surface_fraction=temp2[i][j].impervious_surface_fraction=temperature_DB[i][j].impervious_surface_fraction;
			strcpy(temp1[i][j].station_satus,temperature_DB[i][j].station_satus);
			strcpy(temp2[i][j].station_satus,temperature_DB[i][j].station_satus);
			temp1[i][j].vegetation_density_ratio=temp2[i][j].vegetation_density_ratio=temperature_DB[i][j].vegetation_density_ratio;
			temp1[i][j].air_temperature=temp2[i][j].air_temperature=temperature_DB[i][j].air_temperature;
			temp1[i][j].relative_humidity=temp2[i][j].relative_humidity=temperature_DB[i][j].relative_humidity;
			for(k=0;k<n;k++)
			{
				temp1[i][j].distance_to_other_stations[k]=temperature_DB[i][j].distance_to_other_stations[k];
				temp2[i][j].distance_to_other_stations[k]=temperature_DB[i][j].distance_to_other_stations[k];
			}
		}
	}
	//CALUCULATING THE AVERAGE CITY TEMPERATURE
	float sum=0,avg_city_temp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<30;j++)
		{
			sum=sum+temperature_DB[i][j].air_temperature;
		}
	}
	avg_city_temp=sum/(30*n);
	//CREATING THE MENU DRIVEN PROGRAM TO ACESS THE REQUIRED QUERIES
	int next=1,op,s_n,y;
	char check;
	while(next==1)
	{
		printf("1.HIGHEST HEAT DEGRREE DAYS\n");
		printf("2.THERMALLY CONFORTABLE DAYS FOR A PATICULAR STATION\n");
		printf("3.LIST OF DATES ALL STATIONS WITH DERESING VEGITATION DENSITY RATIO WITH TEMPERATUE MORE THAN AVG TEMPERATURE\n");
		printf("4.TOP K SATIONS WITH MIN PORPULATION DENSITY\n");
		printf("5.HEAT ISLAND DENSITY\n");
		printf("Enter the operation you want to choose: ");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				highestHeatDegree(temperature_DB,n,avg_city_temp);
				break;
			case 2:
				printf("Enter the station no you want to search: ");
				scanf("%d",&s_n);
				thermallyComfortableDays(temperature_DB,n,s_n);
				break;
			case 3:
				datesWithDecearsingVegetation(temp1,n,avg_city_temp);
				break;
			case 4:
				printf("Enter the value of k: ");
				scanf("%d",&y);
				kTopCitiesWithMinPopulation(temp2,n,y);
				break;
			case 5:
				heatIslandIntensity(temperature_DB,n);
				break;
			default :
				printf("Entered invalid input\n");
				break;		
		}
		printf("Do you want to continue(y/n): ");
		scanf("%c",&check);
		if(check=='n')
		{
			next=0;
		}
	}
}
