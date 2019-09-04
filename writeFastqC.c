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


    mxArray *cell_element;
    
    FILE *file_ptr;
    char* file_name;
    int file_name_buffer,status,cell_buffer;
    char* line1;
    char* line2;
    char* line3;
    mxArray *cell_element_ptr1;
    mxArray *cell_element_ptr2;
    mxArray *cell_element_ptr3;
    char* error_line;
    char* error_message;
    char* error_col;
            
    error_message=mxMalloc(1000);
    error_line=mxMalloc(100);
    error_col=mxMalloc(100);
    
    int k=0;
    int i=0;
    
    int seq_length=0;
    int qual_length=0;
    
    int sz1,sz2,sz3,sz4,sz5,sz6,min_sz,max_sz;
    int number_of_sequences;
    
    sz1=mxGetM(prhs[1]);
    sz2=mxGetN(prhs[1]);
    sz3=mxGetM(prhs[2]);
    sz4=mxGetN(prhs[2]);
    sz5=mxGetM(prhs[3]);
    sz6=mxGetN(prhs[3]);
    
    if (sz1*sz2 != sz3*sz4 || sz1*sz2 != sz5*sz6)
    {
        mexErrMsgTxt("Number of entries in heads, seqs and quals should be the same");
    }
    
    if(sz1!=1 && sz2!=1 || sz3!=1 && sz4!=1 ||sz5!=1 && sz6!=1)
    {
        mexErrMsgTxt("Head, seqs and quals should be 1xN cells");
    }
    
    number_of_sequences=sz1;
    
    if (sz2>sz1)
        number_of_sequences=sz2;
    

    file_name_buffer=(mxGetM(prhs[0]) *mxGetN(prhs[0]))+1; 
    file_name = mxMalloc(file_name_buffer);

    status=mxGetString(prhs[0],file_name,file_name_buffer); 


    if (status != 0) {
        mexErrMsgTxt( "Failed to copy input string into allocated memory.");
    }
      


   

    file_ptr = fopen(file_name,"w");

    if (file_ptr==NULL)
        mexErrMsgTxt("Cannot open file");

    k=0;
    
    while (k<number_of_sequences){
    
        cell_element_ptr1 = mxGetCell(prhs[1],k);
        cell_buffer = mxGetN(cell_element_ptr1)*sizeof(mxChar)+1;
        line1 = mxMalloc(cell_buffer);
        
        cell_element_ptr2 = mxGetCell(prhs[2],k);
        cell_buffer = mxGetN(cell_element_ptr2)*sizeof(mxChar)+1;
        line2 = mxMalloc(cell_buffer);
        
        cell_element_ptr3 = mxGetCell(prhs[3],k);
        cell_buffer = mxGetN(cell_element_ptr3)*sizeof(mxChar)+1;
        line3 = mxMalloc(cell_buffer);
        
        
        if (mxGetN(cell_element_ptr2)!=mxGetN(cell_element_ptr3))
        {
            sprintf(error_line,"%d",k+1);
            strcat(strcat(strcpy(error_message,"Error sequence "),error_line),". Quality and Sequence length not the same.");
            mexErrMsgTxt(error_message);
        }   
        
        
        
  

        status = mxGetString(cell_element_ptr1,line1,cell_buffer);
        if (status != 0) {
            mexErrMsgTxt( "Failed to copy header string into allocated memory.");
        }
        status = mxGetString(cell_element_ptr2,line2,cell_buffer);
        if (status != 0) {
            mexErrMsgTxt( "Failed to copy sequence string into allocated memory.");
        }
        status = mxGetString(cell_element_ptr3,line3,cell_buffer);
        if (status != 0) {
            mexErrMsgTxt( "Failed to copy quality string into allocated memory.");
        }
        
        for (i=0; i<mxGetN(cell_element_ptr2); i++)
        {

            if (line2[i]!='A' && line2[i]!='G' && line2[i]!='C' && line2[i]!='T' && line2[i]!='N')
            {
                sprintf(error_line,"%d",k+1);
                sprintf(error_col," %d.",i+1);
                strcat(strcat(strcat(strcpy(error_message,"Error in the sequence at line "),error_line),". It contains a non A,G,C,T,N letter at position"),error_col);
                mexErrMsgTxt(error_message);

            }

        }
        
        for (i=0; i<mxGetN(cell_element_ptr3); i++)
        {

            if (line3[i]-33<0 || line3[i]-33>41)
            {
                sprintf(error_line,"%d",k+1);
                sprintf(error_col,"%d",i+1);
                strcat(strcat(strcat(strcpy(error_message,"Error in the quality at line "),error_line),". It contains a non phred33 letter at position"),error_col);
                mexErrMsgTxt(error_message);

            }

        }

   
        
        if (line1[0]!='@')
            fprintf (file_ptr, "@");
        fprintf(file_ptr,"%s\n",line1);
        fprintf(file_ptr,"%s\n",line2);
        fprintf (file_ptr, "+");
        fprintf(file_ptr,"%s\n",line1);
        fprintf(file_ptr,"%s\n",line3);
        
        
        
        k++;
    	
    }
    

    fclose(file_ptr);
    

    return;
}