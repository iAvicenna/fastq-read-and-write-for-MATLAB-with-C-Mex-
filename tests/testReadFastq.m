function [test_name,isFailed]=testReadFastq(failSwitch)
    
    if nargin ~=1
        error('Requires failSwitch argument');
    end

    addpath('../');
    isFailed=0;
    test_name='testReadFastq';
    
    [heads1,seqs1,quals1]=fastqread('test2.fastq');
    [heads2,seqs2,quals2]=readFastq('./test2.fastq');
    [heads3,seqs3,quals3]=readFastq('./test2.fastq',[100 200]);
    
    
    if any(cellfun(@(x,y)strcmp(x,y(2:end)),heads1,heads2')==0) || ...
             any(cellfun(@(x,y)strcmp(x,y),quals1,quals2')==0) || ...
             any(cellfun(@(x,y)strcmp(x,y),seqs1,seqs2')==0)
         
         isFailed=1;
         return;
         
    end
    if any(cellfun(@(x,y)strcmp(x,y),heads3,heads2(100:200))==0) || ...
             any(cellfun(@(x,y)strcmp(x,y),quals3,quals2(100:200))==0) || ...
             any(cellfun(@(x,y)strcmp(x,y),seqs3,seqs2(100:200))==0)
         
         isFailed=1;
         return;
         
    end
    
    isFailed=1;
    try
        readFastq('test_badheader.fastq');
    catch ME
        if strcmp(ME.message,'Error in the header at line 157. It should start with a @.')
            isFailed=0;
        end
    end
    
    isFailed=1;
    
    try
        readFastq('test_badseq.fastq');
    catch ME
        if strcmp(ME.message,'Error in the sequence at line 190. It contains a non A,G,C,T,N letter at position 33.')
            isFailed=0;
        end
    end
    
    isFailed=1;
    
    try
        if ~failSwitch
            readFastq('test_badqual.fastq');
        else
            readFastq('test_badseq.fastq');
        end
    catch ME
        if strcmp(ME.message,'Error in the quals at line 188. It should have the same length as its sequence.')
            isFailed=0;
        end
    end



end