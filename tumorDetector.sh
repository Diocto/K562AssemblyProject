#!/bin/bash

if [ $# -eq 4 ]
then

reference=$1
fastq1=$2
fastq2=$3
kmer=$4
fastqPath1=$2
fastqPath2=$3
mkdir abyss_origin
mkdir abyss_input
mkdir output

rm abyss_input/input* abyss_input/coverage*
rm abyss_origin/origin* abyss_origin/coverage*

echo ../$fastqPath1 ../$fastqPath2

./assemble $reference $fastq1 $fastq2 $kmer

cd abyss_origin

abyss-pe k=$kmer name=origin in="../$fastqPath1 ../$fastqPath2" 

cd ..
cd abyss_input

abyss-pe k=$kmer name=input in='../output/nodabread_1.fastq ../output/nodabread_2.fastq'

cd ..

./lastz_32 abyss_origin/origin-8.fa[multiple] abyss_input/input-8.fa \
      --notransition --step=20 --nogapped \
      --progress=1 \
      --ambiguous=iupac \
      --format=axt+ > sub_align.txt

./make_fa sub_align.txt

./lastz_32 $reference[multiple] extended.fa --notransition --step=20 --nogapped --ambiguous=iupac --identity=95 --format=axt+ > final_align_axt.txt

./extract_bp final_align_axt.txt $reference $fastq1 $fastq2 > transmutedSequences.txt

else
echo ""
echo "[Error] Please Input correct parameter"
echo 'example :	$shellscript.sh reference.fa fq_1.fq fq_2.fq kmersize'
echo ""
fi
