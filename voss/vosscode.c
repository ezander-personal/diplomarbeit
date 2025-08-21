fopen
/* File einlesen */
 fscanf(fip,"%ld\n %ld\n",&start,&dauer);
 laenge=dauer/(nchan*2);starttime=start/(nchan*2)/(sf*samdown)/60.0;}
/* anzahl=ceil(laenge/samdown)-1; */
 anzahl=dimlaenge+ordnung+1;
 readchannel(fip,vector,chan,nchan,siw,anzahl,samdown,asciornot,mb);
 fclose(fip); 
mb=1.15;chan=1;nchan=2;siw=startimfenster;asciornot=0;sf=100.0Hz
/* *************************************************
   K A N A L  E I N L E S E N
   ************************************************* */
void readchannel(FILE *fp, float *vector,int kanal,int nchan,int start,
                 int anzahl, int downsample,int asciornot,float mb)
{unsigned char byte1,byte2;
 int zeit,k,j,i,korr=0,flow,volume;
 double dvolt;
 char charvolt[9];
 float neuwert,mittel=0.0,voltwert, voltfakt=2.0*mb/4096.0;

 if(asciornot==0)
 {
 for(zeit=1;zeit<=start+anzahl;zeit++)
    { for(k=1;k<=downsample;k++)
         { for(i=1;i<=nchan;i++)
              {byte1=fgetc(fp); byte2=fgetc(fp);
               voltwert=voltfakt*((byte1*16.0+byte2/16.0)-2048);
               if(i==kanal){sprintf(charvolt,"%.3f\0",voltwert);}}}
      dvolt=atof(charvolt);
      if(zeit>=start)
      {vector[zeit-start+1]=(float) dvolt;}}


 if(fabs(vector[1])>=mb-0.01*mb){korr++;vector[1]=vector[2];}
 if(fabs(vector[anzahl])>=mb-0.01*mb){korr++;vector[anzahl]=vector[anzahl-1];}
 for(i=2;i<=anzahl;i++){if(fabs(vector[i])>=mb-0.01*mb){
                           korr++;vector[i]=0.5*(vector[i-1]+vector[i+1]);}}
 }
 if(asciornot==1)
   {for(zeit=1;zeit<=anzahl;zeit++)
       {for(i=1;i<=downsample;i++)
            {fscanf(fp,"%d %d\n",&flow,&volume);}
        if(kanal==1)vector[zeit]=flow*1.0;
        if(kanal==2)vector[zeit]=volume*1.0;}
       }

 for(i=1;i<=anzahl;i++){mittel=mittel+vector[i];}
     mittel=mittel/anzahl;
 for(i=1;i<=anzahl;i++) {vector[i]=vector[i]-mittel;}

 return;}

 /* Filtern */
filpar1= /* ugf (Hz)*/
  filpar2=/* ogf (Hz)*/ 
if(filpar2>0){ filter(vector,anzahl,filpar2,filpar1,sf,ordnung);
                anzahl=anzahl-ordnung;}
/* *******************************
   Filter Version 2
   ******************************* */
void filter(float *vector, int laenge, float ogf, float ugf, float sf, int ordnung)
{ int i,k,j,N=ordnung+1,alf=ordnung/2,m=ordnung;
  float x1,x2,bet=0.025,onf,unf,omg,pi=3.141592654, wk, *gk, *vecopy;
  vecopy=calloc(laenge+1,sizeof(float));
  gk=calloc(ordnung+1,sizeof(float));
  omg=2.0*pi*(ogf-ugf)/sf;
  onf=2*pi*(ogf/sf);
  unf=2*pi*(ugf/sf);
  for(k=0;k<alf;k++)
     {x1=bet*sqrt(alf*alf-(k-alf)*(k-alf));
      x2=bet*alf;
      wk=bessel(x1)/bessel(x2);
      /* Hamming wk=0.235*2.0*cos((pi*k/m))+1.0-2.0*0.235; */
      /* Blackman wk=0.42-0.5*cos(2.0*pi*k/m)+0.08*cos(4.0*pi*k/m); */
      gk[k]=1.0/pi*(sin((alf-k)*onf)-sin((alf-k)*unf))/(alf-k);
      gk[m-k]=gk[k];}
  gk[alf]=1.0/pi*(onf-unf);

  for(i=m+1;i<=laenge;i++)
     {vecopy[i]=0.0;
      for(k=0;k<=m;k++)
         {vecopy[i-m]=vecopy[i-m]+vector[i-k]*gk[k];}}

  for(i=1;i<=laenge-m;i++)
     {vector[i]=vecopy[i];}
  for(i=laenge-m+1;i<=laenge;i++)vector[i]=0.0;
  free(gk);free(vecopy);
  return;
  }

/* ************************************
   G R E N Z F R E Q U E N Z I N D E X
   ************************************ */

int pass(float frequenz,float timestep)
 {int i=0;
  float icopy=0.0;
  while((icopy*timestep)<=frequenz)
       {i=i+2;icopy=i*1.0;}
  return(i);
  }




/* ***************************
   mod. Besselfunktion
   *************************** */
float bessel(float x)
{ float y=0.5*x,sum=1.0,delta=1.0,iter=1.0,eps=1.0e-8;
  int i=1;
  while((sum*eps-iter)<=0.0 && (i<26))
       {delta=delta*y/i;
        iter=sqrt(delta);
        sum=sum+iter;
        i++;}
  return(sum);
  }
