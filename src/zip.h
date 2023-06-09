#ifndef _ZIP_H
#define _ZIP_H

#include <stdint.h>

#define LOCAL_FILE_HEADER_SIGNATURE 			   0x04034B50
#define CENTRAL_DIRECTORY_FILE_HEADER_SIGNATURE    0x02014B50
#define CENTRAL_DIRECTORY_RECORD_TAIL_SIGNATURE    0x06054B50

#define ZIP_VERSION  							   45
#define WINDOWS_NTFS 							   0x0A
#define UTF8_ENCODING 							   1 << 11

#define LOCAL_FILE_HEADER_CRC32_OFFSET 			   14

/* Zip Structs */

typedef struct {
	uint32_t signature;
	uint16_t version;
	uint16_t flags;
	uint16_t compression;
	uint16_t mod_time;
	uint16_t mod_date;
	uint32_t crc32;
	uint32_t compressed_size;
	uint32_t uncompressed_size;
	uint16_t file_name_length;
	uint16_t extra_field_length;
	//char file_name[];
	//unsigned char extra_field[];
} __attribute__((packed)) local_file_header;

typedef struct {
	uint32_t signature;
	uint16_t version_made_by;
	uint16_t version_needed_to_extract;
	uint16_t flags;
	uint16_t compression;
	uint16_t mod_time;
	uint16_t mod_date;
	uint32_t crc32;
	uint32_t compressed_size;
	uint32_t uncompressed_size;
	uint16_t file_name_length;
	uint16_t extra_field_length;
	uint16_t file_comment_length;
	uint16_t disk_number_start;
	uint16_t internal_file_attributes;
	uint32_t external_file_attributes;
	uint32_t local_header_offset;
	//char file_name[];
	//unsigned char extra_field[];
	//char file_comment[];
} __attribute__((packed)) central_directory_file_header;

typedef struct {
	uint32_t signature;
	uint16_t disk_number;
	uint16_t central_directory_start_disk_number;
	uint16_t num_records_on_disk;
	uint16_t num_total_records;
	uint32_t central_directory_size;
	uint32_t central_directory_start_offset;
	uint16_t comment_length;
	//char comment[];
} __attribute__((packed)) central_directory_record_tail;


/* Additional Structs */

#define ZIP64_EXTRA_FIELD_HEADER_ID	0x0001

#define ZIP64_EXTRA_FIELD_COMPRESSED_SIZE_OFFSET_FROM_END 8

typedef struct {
	uint16_t header_id;
	uint16_t data_size;
	uint64_t uncompressed_size;
	uint64_t compressed_size;
} __attribute__((packed)) zip64_extra_field;

#endif