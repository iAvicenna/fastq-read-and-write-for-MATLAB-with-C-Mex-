#include "mex.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
  


void mexFunction(int nlhs,mxArray *plhs[ ],int nrhs,const mxArray *prhs[ ])   
{   

    
    if(nrhs!=1)
        mexErrMsgTxt("This function needs 1 arguments.");   
    else if(nlhs!=1)   
        mexErrMsgTxt("This function gives only 1 output.");
    
    if(mxIsChar(prhs[0])!=1)
        mexErrMsgTxt("Input 1 must be a char array.");
    
    
    mxArray *heads;
    mxArray *seqs;
    mxArray *quals;
    FILE *file_ptr;
    char* file_name;
    int file_name_buffer,status;
    char* line = NULL;
    mxArray* mx_line=NULL;
    char* error_message;
    char* error_line;
    char* error_col;
    int k=0;
    int i=0;
    int counter=0;
    int seq_length=0;
    int qual_length=0;
   
    size_t len=0;
    ssize_t read;
    
    file_name_buffer=(mxGetM(prhs[0]) *mxGetN(prhs[0]))+1; 
    file_name = mxMalloc(file_name_buffer);
    error_message=mxMalloc(1000);
    error_line=mxMalloc(100);
    error_col=mxMalloc(100);
    
    status=mxGetString(prhs[0],file_name,file_name_buffer); 
    

    if (status != 0) {
        mexErrMsgTxt( "Failed to copy input string into allocated memory.");
    }
    
    file_ptr = fopen(file_name,"r");

    if (file_ptr==NULL)
        mexErrMsgTxt("Cannot open file.");
    
    
    while ((read = getline(&line, &len, file_ptr)) != -1) {
        k=k%4;

        
        if (k==0 )
        {
            
            
            if  (line[0]!='@')
            {
                sprintf(error_line,"%d",counter+1);
                strcat(strcat(strcpy(error_message,"Error in the header at line "),error_line),". It should start with a @.");
                mexErrMsgTxt(error_message);
            }
        }
        
        if (k==2 )
        {
            
            

            
            if  (line[0]!='+')
            {
                sprintf(error_line,"%d",counter+1);
                strcat(strcat(strcpy(error_message,"Error in the header at line "),error_line),". It should start with a +.");
                mexErrMsgTxt(error_message);
            }
        }
        

        
        
        if (k==1)
        {
            seq_length=strlen(line);

            for (i=0; i<seq_length-1; i++)
            {
                
                if (line[i]!='A' && line[i]!='G' && line[i]!='C' && line[i]!='T' && line[i]!='N')
                {
                    sprintf(error_line,"%d",counter+1);
                    sprintf(error_col,"%d.",i+1);
                    strcat(strcat(strcat(strcpy(error_message,"Error in the sequence at line "),error_line),". It contains a non A,G,C,T,N letter at position "),error_col);
                    mexErrMsgTxt(error_message);
                    
                }
                
            }
            
            
        }
        
        if (k==3)
        {
            qual_length=strlen(line);
            
            if (qual_length != seq_length)
            {
                sprintf(error_line,"%d",counter+1);
                strcat(strcat(strcpy(error_message,"Error in the quals at line "),error_line),". It should have the same length as its sequence.");
                mexErrMsgTxt(error_message);
            }
            
            for (i==0; i<qual_length-1; i++)
            {
                
                if (line[i]-33<0 || line[i]-33>41)
                {
                    sprintf(error_line,"%d",counter+1);
                    sprintf(error_col,"%d",i+1);
                    strcat(strcat(strcat(strcpy(error_message,"Error in the quality at line "),error_line),". It contains a non phred33 letter at position"),error_col);
                    mexErrMsgTxt(error_message);
                    
                }
                
            }
            
            
        }
        
        
        k++;
        counter++;
        line[0] = '\0';
   }
    
    
   if (floor((double)(counter)/4)!=(double)(counter)/4) 
   {
        strcpy(error_message,"Number of lines is not divisible by 4, check for missing entries");
        mexErrMsgTxt(error_message);
       
   }
       
   plhs[0] = mxCreateNumericMatrix(1,1, mxINT32_CLASS, mxREAL);
   int* number_of_sequences = (int*)mxGetPr (plhs[0]); 
   number_of_sequences[0]=(double)(counter)/4;
   
 
    
   return;
}