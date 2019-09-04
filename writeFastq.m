function writeFastq(output_file_path,heads,seqs,quals)



    script_path=mfilename('fullpath');
    ind=regexp(script_path,'/');
    if isempty(ind)
        ind=regexp(script_path,'\');
    end
    script_dir=script_path(1:ind(end));

    addpath([script_dir 'functs']);
    
  
    writeFastqC(output_file_path,heads,seqs,quals); 
   
       
        

end