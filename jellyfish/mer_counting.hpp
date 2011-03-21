/*  This file is part of Jellyfish.

    Jellyfish is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Jellyfish is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Jellyfish.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __JELLYFISH_MER_COUNTING__
#define __JELLYFISH_MER_COUNTING__

#include <sys/types.h>
#include <stdint.h>
#include <stdarg.h>
#include <vector>
#include <utility>

#include <jellyfish/misc.hpp>
#include <jellyfish/storage.hpp>
#include <jellyfish/hash.hpp>
#include <jellyfish/concurrent_queues.hpp>
#include <jellyfish/atomic_gcc.hpp>
#include <jellyfish/allocators_mmap.hpp>
#include <jellyfish/compacted_hash.hpp>
#include <jellyfish/compacted_dumper.hpp>
#include <jellyfish/raw_dumper.hpp>
#include <jellyfish/fasta_parser.hpp>
#include <jellyfish/fastq_sequence_parser.hpp>
#include <jellyfish/parse_dna.hpp>

// Invertible hash types
#include <jellyfish/invertible_hash_array.hpp>
#include <jellyfish/sorted_dumper.hpp>
typedef jellyfish::invertible_hash::array<uint64_t,atomic::gcc<uint64_t>,allocators::mmap> inv_hash_storage_t;
typedef jellyfish::sorted_dumper< inv_hash_storage_t,atomic::gcc<uint64_t> > inv_hash_dumper_t;
typedef jellyfish::raw_hash_dumper<inv_hash_storage_t> raw_inv_hash_dumper_t;
typedef jellyfish::hash< uint64_t,uint64_t,inv_hash_storage_t,atomic::gcc<uint64_t> > inv_hash_t;

// Direct indexing types
#include <jellyfish/direct_indexing_array.hpp>
#include <jellyfish/direct_sorted_dumper.hpp>
#include <jellyfish/capped_integer.hpp>
typedef jellyfish::direct_indexing::array<uint64_t,jellyfish::capped_integer<uint32_t>,atomic::gcc<uint32_t>,allocators::mmap> direct_index_storage_t;
typedef jellyfish::direct_sorted_dumper< direct_index_storage_t, atomic::gcc<uint64_t> > direct_index_dumper_t;
typedef jellyfish::hash< uint64_t,uint32_t,direct_index_storage_t,atomic::gcc<uint64_t> > direct_index_t;

// Quake types
#include <jellyfish/aligned_values_array.hpp>
#include <jellyfish/floats.hpp>
#include <jellyfish/fastq_dumper.hpp>
#include <jellyfish/fastq_seq_qual_parser.hpp>
#include <jellyfish/parse_quake.hpp>
typedef jellyfish::aligned_values::array<uint64_t,jellyfish::Float,atomic::gcc<uint64_t>,atomic::gcc<jellyfish::Float::bits_t>,allocators::mmap> fastq_storage_t;
typedef jellyfish::hash<uint64_t,jellyfish::Float,fastq_storage_t,atomic::gcc<uint64_t> > fastq_hash_t;
typedef jellyfish::fastq_hash::raw_dumper<fastq_storage_t> raw_fastq_dumper_t;

// Compacted hash types
typedef jellyfish::compacted_hash::reader<uint64_t,uint64_t> hash_reader_t;
typedef jellyfish::compacted_hash::query<uint64_t,uint64_t> hash_query_t;
typedef jellyfish::compacted_hash::writer<hash_reader_t> hash_writer_t;

#endif /* __MER_COUNTING__ */
