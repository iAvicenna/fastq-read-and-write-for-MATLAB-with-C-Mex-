# fastqRead and fastqWrite

This is a fast (compared to MATLAB bioinformatics tool box provided functions) fastq read and write function for MATLAB mostly coded in C and mexed. The functions can be called as

<p align="center">
[heads,quals,seqs]=readFastq(input_name);
</p>

<p align="center">
writeFastq(output_name,heads,seqs,quals);
</p>


It allows block reads as follows:

<p align="center">
[heads,quals,seqs]=readFastq(input_name, [10000 20000]);
</p>


There is also a query function that counts the number of sequences and does simple integrity checks on the fastq file to make sure there are no errors.

# Comparison to fastqread and fastqwrite from Bioinformatics Toolbox


Number of sequences 2998212
Writing using writeFastq.Elapsed time is 18.933540 seconds.
Writing using fastqwrite.Elapsed time is 135.610968 seconds.
Reading using readFastq.Elapsed time is 15.899386 seconds.
Reading using fastqread.Elapsed time is 37.236882 seconds.


# Requirements

Matlab(2018b), C. Speed testing function also requires nt2aa function from the bioinformatics toolbox. 

# Author
Sina Tureli


# Licensing

This repository is
[Apache-licensed](https://github.com/bamos/densenet.pytorch/blob/master/LICENSE).
