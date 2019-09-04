#include "mex.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
  


void mexFunction(int nlhs,mxArray *plhs[ ],int nrhs,const mxArray *prhs[ ])   
{   


    if(nrhs<2 )
        mexErrMsgTxt("Atleast 2 arguments needed.");   
    else if(nlhs>3)   
        mexErrMsgTxt("Too many output arguments.");

    //if(mxIsChar(prhs[0])!=1)
    //    mexErrMsgTxt("Input 1 must be a char matrix.");

    //if(nrhs==2 && mxIsChar(prhs[0])!=2)
      //  mexErrMsgTxt("Input 2 must be an integer array.");

    mxArray *heads;
    mxArray *seqs;
    mxArray *quals;
    FILE *file_ptr;
    char* file_name;
    int file_name_buffer,status;
    char* line = NULL;
    mxArray* mx_line=NULL;
    int k=0;
    int i=0;
    int li,lj;
    int counter=0;
    int seq_length=0;
    int qual_length=0;
    int number_of_sequences;
    int* block;
    size_t len=0;
    ssize_t read;
    
    number_of_sequences=(int)mxGetScalar(prhs[1]);
    
    if (nrhs==3)
    {
        int sz1,sz2;
        sz1=mxGetM(prhs[2]);
        sz2=mxGetN(prhs[2]);
        
        sz1=1;
        sz2=2;
        
        if (sz1!=1 || sz2!=2)
        {
            mexErrMsgTxt("Block input must be a 1 x 2 array");
        }
        
        block=(int*)mxGetInt32s(prhs[2]);
     

        
        if (block[1]<=block[0])
        {
            mexErrMsgTxt("First element of block array must be smaller than the second");
        }
        
        if (block[0]<1)
        {
            mexErrMsgTxt("First element of block must be non-negative");
        }
        
        if (block[1]>number_of_sequences)
        {
            block[1]=number_of_sequences;
        }
        
        number_of_sequences=block[1]-block[0]+1;
        
        
        
    }
    else
    {
        block=mxCalloc(2,sizeof(int));
        block[0]=1;
        block[1]=number_of_sequences;
    }

    file_name_buffer=(mxGetM(prhs[0]) *mxGetN(prhs[0]))+1; 
    file_name = mxMalloc(file_name_buffer);

    status=mxGetString(prhs[0],file_name,file_name_buffer); 


    if (status != 0) {
        mexErrMsgTxt( "Failed to copy input string into allocated memory.");
    }
    
    
    

    heads= mxCreateCellMatrix((mwSize)number_of_sequences,1);
    seqs= mxCreateCellMatrix((mwSize)number_of_sequences,1);
    quals= mxCreateCellMatrix((mwSize)number_of_sequences,1);
   

    file_ptr = fopen(file_name,"r");

    if (file_ptr==NULL)
        mexErrMsgTxt("Cannot open file");

    counter=0;
    k=0;
    
    
    
    while ((read = getline(&line, &len, file_ptr)) != -1) 
    {
       k=k%4;
       
       
       
       

       lj = -1;
       li = 0;
       while(line[li] != '\0' )
       {
           if(line[li] != ' ' && line[li] != '\t' && line[i] != '\n')
           {
               lj=li;
           }

           li++;
       }
       
       line[lj] = '\0';
       

       if (k==0)
       {
           if (counter+1>=block[0] && counter+1<=block[1])
           {
               mx_line=mxCreateString(line);
               mxSetCell(heads,(mwIndex)(counter-block[0]+1),mxDuplicateArray(mx_line));
           }
       }

       if (k==1)
       {
           if (counter+1>=block[0] && counter+1<=block[1])
           {
               mx_line=mxCreateString(line);
               mxSetCell(seqs,(mwIndex)(counter-block[0]+1),mxDuplicateArray(mx_line));
           }
       }

       if (k==3)
       {
           if (counter+1>=block[0] && counter+1<=block[1])
           {
              mx_line=mxCreateString(line);
              mxSetCell(quals,(mwIndex)(counter-block[0]+1),mxDuplicateArray(mx_line));
           }
           
       counter++;    
       }
    
       

       k++;
    }


    fclose(file_ptr);
    plhs[0]=heads;
    plhs[1]=seqs;
    plhs[2]=quals;


    return;
}