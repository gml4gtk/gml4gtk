# PTGLweb is a web server and database of protein structure topologies 
# http://ptgl.uni-frankfurt.de/index.php
graph [
  id 1
  label "VPLG Protein Graph 7tim-A-alpha-FG2[8V,7E]"
  comment "pdbid=7tim|graphtype=alpha|chainid=A|graphclass=folding graph|foldinggraphnumber=3|"
  directed 0
  isplanar 0
  creator "PLCC version 0.98.3"
  pdb_id "7tim"
  chain_id "A"
  graph_type "alpha"
  is_protein_graph 0
  is_folding_graph 1
  is_SSE_graph 1
  is_AA_graph 0
  is_all_chains_graph 0
  node [
    id 0
    label "0-H"
    num_in_chain 8
    num_residues 6
    pdb_res_start "A-96- "
    pdb_res_end "A-101- "
    dssp_res_start 95
    dssp_res_end 100
    pdb_residues_full "A-96- ,A-97- ,A-98- ,A-99- ,A-100- ,A-101- "
    aa_sequence "SERRSY"
    index_in_parent_pg "3"
    sse_type "H"
    fg_notation_label "h"
  ]
  node [
    id 1
    label "1-H"
    num_in_chain 9
    num_residues 13
    pdb_res_start "A-106- "
    pdb_res_end "A-118- "
    dssp_res_start 105
    dssp_res_end 117
    pdb_residues_full "A-106- ,A-107- ,A-108- ,A-109- ,A-110- ,A-111- ,A-112- ,A-113- ,A-114- ,A-115- ,A-116- ,A-117- ,A-118- "
    aa_sequence "DKFIADKTKFALG"
    index_in_parent_pg "4"
    sse_type "H"
    fg_notation_label "h"
  ]
  node [
    id 2
    label "2-H"
    num_in_chain 11
    num_residues 5
    pdb_res_start "A-131- "
    pdb_res_end "A-135- "
    dssp_res_start 130
    dssp_res_end 134
    pdb_residues_full "A-131- ,A-132- ,A-133- ,A-134- ,A-135- "
    aa_sequence "LEEKK"
    index_in_parent_pg "5"
    sse_type "H"
    fg_notation_label "h"
  ]
  node [
    id 3
    label "3-H"
    num_in_chain 12
    num_residues 15
    pdb_res_start "A-139- "
    pdb_res_end "A-153- "
    dssp_res_start 138
    dssp_res_end 152
    pdb_residues_full "A-139- ,A-140- ,A-141- ,A-142- ,A-143- ,A-144- ,A-145- ,A-146- ,A-147- ,A-148- ,A-149- ,A-150- ,A-151- ,A-152- ,A-153- "
    aa_sequence "TLDVVERQLNAVLEE"
    index_in_parent_pg "6"
    sse_type "H"
    fg_notation_label "h"
  ]
  node [
    id 4
    label "4-H"
    num_in_chain 14
    num_residues 3
    pdb_res_start "A-167- "
    pdb_res_end "A-169- "
    dssp_res_start 166
    dssp_res_end 168
    pdb_residues_full "A-167- ,A-168- ,A-169- "
    aa_sequence "VWA"
    index_in_parent_pg "7"
    sse_type "H"
    fg_notation_label "h"
  ]
  node [
    id 5
    label "5-H"
    num_in_chain 15
    num_residues 19
    pdb_res_start "A-178- "
    pdb_res_end "A-196- "
    dssp_res_start 177
    dssp_res_end 195
    pdb_residues_full "A-178- ,A-179- ,A-180- ,A-181- ,A-182- ,A-183- ,A-184- ,A-185- ,A-186- ,A-187- ,A-188- ,A-189- ,A-190- ,A-191- ,A-192- ,A-193- ,A-194- ,A-195- ,A-196- "
    aa_sequence "PEDAQDIHASIRKFLASKL"
    index_in_parent_pg "8"
    sse_type "H"
    fg_notation_label "h"
  ]
  node [
    id 6
    label "6-H"
    num_in_chain 16
    num_residues 6
    pdb_res_start "A-198- "
    pdb_res_end "A-203- "
    dssp_res_start 197
    dssp_res_end 202
    pdb_residues_full "A-198- ,A-199- ,A-200- ,A-201- ,A-202- ,A-203- "
    aa_sequence "DKAASE"
    index_in_parent_pg "9"
    sse_type "H"
    fg_notation_label "h"
  ]
  node [
    id 7
    label "7-H"
    num_in_chain 18
    num_residues 4
    pdb_res_start "A-217- "
    pdb_res_end "A-220- "
    dssp_res_start 216
    dssp_res_end 219
    pdb_residues_full "A-217- ,A-218- ,A-219- ,A-220- "
    aa_sequence "AVTF"
    index_in_parent_pg "10"
    sse_type "H"
    fg_notation_label "h"
  ]
  edge [
    source 0
    target 1
    label "m"
    spatial "m"
  ]
  edge [
    source 1
    target 3
    label "m"
    spatial "m"
  ]
  edge [
    source 2
    target 3
    label "m"
    spatial "m"
  ]
  edge [
    source 2
    target 4
    label "m"
    spatial "m"
  ]
  edge [
    source 3
    target 5
    label "p"
    spatial "p"
  ]
  edge [
    source 5
    target 6
    label "m"
    spatial "m"
  ]
  edge [
    source 5
    target 7
    label "m"
    spatial "m"
  ]
]
