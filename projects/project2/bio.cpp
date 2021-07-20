#include <iostream>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
#include "bio.h"

bool IsValidDNASequence(const std::string &input) {
  string::size_type i = 0;
  for (auto chr : input) {
    if ((chr == 'A') || (chr == 'C') || (chr == 'T') || (chr == 'G')) {
      ++i;
    }
  }
  if (i == input.length()) {
    return true;
  } else {
    return false;
  }
}

void GetReverseComplementSequence(const std::string &input,
                                  std::string *const output) {
  string inpt_cpy = input;
  std::reverse(inpt_cpy.begin(), inpt_cpy.end());
  bool is_DNA =
      (inpt_cpy.find("T") !=
       string::npos);  // bool to check whether the input is dna or rna
  for (auto &chr : inpt_cpy) {
    switch (chr) {
      case 'A':
        if (is_DNA != 0) {
          *output += 'T';
        } else {
          *output += 'U';
        }
        break;
      case 'T':
        *output += 'A';
        break;
      case 'U':
        *output += 'A';
        break;
      case 'G':
        *output += 'C';
        break;
      case 'C':
        *output += 'G';
        break;
      default:
        break;
    }
  }
}

std::string GetRNATranscript(const std::string &input) {
  string output = "";
  string *ptr_output = &output;
  GetReverseComplementSequence(input, ptr_output);
  for (auto &chr : output) {
    if (chr == 'T') {
      chr = 'U';
    }
  }
  return output;
}

vector<string> FrameBuilder(const string &input) {
  /*
  this function takes in a RNA transcript for a frame and returns a vector of
  codons for that frame, then GetReadingFramesAsCodons appends that vector of
  codons for that frame to a vector of all the frames
  */
  string codon = "";
  vector<string> frame;
  for (auto &chr : input) {
    codon += chr;
    if (codon.length() == 3) {
      frame.push_back(codon);
      codon = "";
      continue;
    }
  }
  return frame;
}  // made this one

std::vector<std::vector<std::string>> GetReadingFramesAsCodons(
    const std::string &input) {
  string RNA_org = GetRNATranscript(input);
  string RNA_antip = GetRNATranscript(RNA_org);
  vector<vector<string>> super_frames;

  for (string::size_type i = 0; i < 3; ++i) {
    super_frames.push_back(FrameBuilder(RNA_org));
    RNA_org.erase(RNA_org.begin());
  }
  for (string::size_type i = 0; i < 3; ++i) {
    super_frames.push_back(FrameBuilder(RNA_antip));
    RNA_antip.erase(RNA_antip.begin());
  }

  return super_frames;
}

string FindAminoAcids(const string &input) {
  /*
  the following piazza post helped me create this function:
  https://piazza.com/class/k4wvjqt9b2x72k?cid=786
  this function takes in a codon, find that index for that codon in the codon
  vector, then use that index to find the corresponding amino acid in the vector
  of amino acids, then returns that amino acid
  */
  vector<string> codons = {
      "GCU", "GCC", "GCA", "GCG", "CGU", "CGC", "CGA", "CGG", "AGA", "AGG",
      "AAU", "AAC", "GAU", "GAC", "UGU", "UGC", "CAA", "CAG", "GAA", "GAG",
      "GGU", "GGC", "GGA", "GGG", "CAU", "CAC", "AUU", "AUC", "AUA", "UUA",
      "UUG", "CUU", "CUC", "CUA", "CUG", "AAA", "AAG", "AUG", "UUU", "UUC",
      "CCU", "CCC", "CCA", "CCG", "UCU", "UCC", "UCA", "UCG", "AGU", "AGC",
      "ACU", "ACC", "ACA", "ACG", "UGG", "UAU", "UAC", "GUU", "GUC", "GUA",
      "GUG", "UAG", "UGA", "UAA"};
  vector<string> aa_vec = {
      "A", "A", "A", "A", "R", "R", "R", "R", "R", "R", "N", "N", "D",
      "D", "C", "C", "Q", "Q", "E", "E", "G", "G", "G", "G", "H", "H",
      "I", "I", "I", "L", "L", "L", "L", "L", "L", "K", "K", "M", "F",
      "F", "P", "P", "P", "P", "S", "S", "S", "S", "S", "S", "T", "T",
      "T", "T", "W", "Y", "Y", "V", "V", "V", "V", "*", "*", "*"};
  string::size_type i = 0;
  for (string &elem : codons) {
    if (elem == input) {
      break;
    }
    ++i;
  }
  return aa_vec.at(i);
}

std::string Translate(const std::vector<std::string> &codon_sequence) {
  string amino_acids = "";
  for (auto &codon : codon_sequence) {
    amino_acids += FindAminoAcids(codon);
  }
  return amino_acids;
}

string LongestAminoAcidFrame(const string &input) {
  /*
  this function takes in a reading frame that's been translated, iterate thru
  the string, make substring for each amino acid seq and append to a vector of
  strings then find the largest seq and return that string in
  GetLongestOpenReadingFrame append the longest seq for that reading frame into
  a vector of largest amino acid seq for each reading frame, then iterate
  through that vector to find the overall largest amino acid sequence
  */
  string::size_type i = 0;
  vector<string> aa_seqs;
  string seq;
  int begin = 0;
  int end = 0;
  string longest_seq = "";
  int m_occurence = 0;
  for (auto aa : input) {
    if ((aa == 'M') && (m_occurence < 1)) {
      begin = i;
      ++m_occurence;
    } else if ((aa == '*') && (begin > end)) {
      end = i;
      seq = input.substr(begin, (end - begin) + 1);
      aa_seqs.push_back(seq);
      seq = "";
      m_occurence = 0;
    }
    ++i;
  }
  for (string aa : aa_seqs) {
    if (aa.length() > longest_seq.length()) {
      longest_seq = aa;
    }
  }
  return longest_seq;
}

std::string GetLongestOpenReadingFrame(const std::string &DNA_sequence) {
  vector<vector<string>> all_frames = GetReadingFramesAsCodons(DNA_sequence);
  string aa_seq;
  vector<string> longest_aa_per_frame;
  string longest_aa = "";
  bool is_valid;  // checks to see if there's m and * in the amino acid seq
  for (vector<string> &frame : all_frames) {
    aa_seq = Translate(frame);
    is_valid = ((aa_seq.find('M') != string::npos) &&
                (aa_seq.find('*') != string::npos));
    if (is_valid != 0) {
      aa_seq = LongestAminoAcidFrame(aa_seq);
      longest_aa_per_frame.push_back(aa_seq);
      aa_seq = "";
    } else {
      continue;
    }
  }

  for (string frame : longest_aa_per_frame) {
    if (frame.size() > longest_aa.size()) {
      longest_aa = frame;
    }
  }

  return longest_aa;
}