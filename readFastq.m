function [heads,seqs,quals]=readFastq(file_path,block)

    

    number_of_sequences=queryFastqC(file_path);

  
    if exist('block','var') && ~isempty(block)
        [heads,seqs,quals]=readFastqC(file_path,number_of_sequences,int32(block)); 
    else      
        [heads,seqs,quals]=readFastqC(file_path,number_of_sequences);
    end

        

end