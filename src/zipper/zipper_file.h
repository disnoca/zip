#ifndef _ZIPPER_FILE_H
#define _ZIPPER_FILE_H

#include <stdint.h>
#include <stdbool.h>
#include <windows.h>

typedef struct zipper_file zipper_file;

struct zipper_file {
	bool is_directory;
	unsigned num_children;
	zipper_file** children;
	HANDLE hFile;
	char* name;
	uint16_t name_length;
	LPWSTR wide_char_name;
	bool is_large;
	uint64_t uncompressed_size, compressed_size;
	uint16_t compression_method;
	uint16_t mod_time, mod_date;
	uint32_t crc32;
	uint32_t local_header_offset;
	void (*compression_func)(zipper_file* zf, LPWSTR dest_name, uint64_t dest_offset);
};

/**
 * Returns a zipper_file struct pointer with the zipper_file's data and info.
 * 
 * @param path the relative path to the zipper_file
 * @param compression_method the compression method to use
 * @return a zipper_file struct pointer with the zipper_file's data and info
*/
zipper_file* zfile_create(LPWSTR path, unsigned compression_method);

/**
 * Destroys the specified zipper_file struct, freeing its allocated memory.
 * 
 * @param zf the zipper_file struct to destroy
*/
void zfile_destroy(zipper_file* zf);

/**
 * Compresses and writes the zipper_file specified by the zipper_file struct to the destination zipper_file.
 * 
 * @param zf the zipper_file struct of the zipper_file to compress the data from
 * @param dest_name the path to the zipper_file to write the compressed data to
 * @param dest_offset the offset of the zipper_file to write the compressed data to
*/
void zfile_compress_and_write(zipper_file* zf, LPWSTR dest_name, uint64_t dest_offset);

#endif