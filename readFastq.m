function [heads,seqs,quals]=readFastq(file_path,block)

    script_path=mfilename('fullpath');
    ind=regexp(script_path,'/');
    if isempty(ind)
        ind=regexp(script_path,'\');
    end
    script_dir=script_path(1:ind(end));

    addpath([script_dir 'functs']);

    number_of_sequences=queryFastqC(file_path);

  
    if exist('block','var') && ~isempty(block)
        [heads,seqs,quals]=readFastqC(file_path,number_of_sequences,int32(block)); 
    else      
        [heads,seqs,quals]=readFastqC(file_path,number_of_sequences);
    end

        

end