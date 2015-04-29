#include <ext2fs/ext2fs.h>
#include <ext2fs/ext2_fs.h>
#include <stdio.h>
#include <stdlib.h>
#include <et/com_err.h>
#include <stdint.h>

static const char DEV[] = "/dev/loop0p1";
static const char OS_L[] = "LINUX";
static const char OS_O[] = "OTHER";

int main(int argc, char **argv){
	errcode_t err;
	ext2_filsys fs;
	struct ext2_super_block *super;

	err = ext2fs_open(DEV, EXT2_FLAG_RW, 0, 0, unix_io_manager, &fs);
	if (err){
		if (err == 13) {
			printf("[ext2fs_open] Insufficient permissions\n");
		} else {
			printf("[ext2fs_open] Error number: %ld\n", err);
		}
		return EXIT_FAILURE;
	}
	
	super = fs->super;	

	printf("Anzahl der Inodes: %d\n", super->s_inodes_count);
	printf("Insgesamte Anzahl der Blöcke: %d\n", super->s_blocks_count);
	printf("Erster Datenblock: %d\n", super->s_first_data_block);
	printf("Anzahl freier Inodes: %d\n", super->s_free_inodes_count);
	printf("Anzahl freier Datenblöcke: %d\n", super->s_free_blocks_count);
	printf("Magic Number: %02X\n", super->s_magic);

	/* Remember each hexadecimal integer will be represented in reverse
	 	byte order because of the x86-endianness (little endian) */
	printf("UUID des Dateisystems: %08X-%08X-%08X-%08X\n", 
			/* Read 4 4-byte words */
			*(((uint32_t *) super->s_uuid) + 0),
			*(((uint32_t *) super->s_uuid) + 1),
			*(((uint32_t *) super->s_uuid) + 2), 
			*(((uint32_t *) super->s_uuid) + 3));
	printf("ID des Ersteller-OSes: %s\n", 
			(super->s_creator_os == 0 ? OS_L : OS_O));

	err = ext2fs_close(fs);
	if (err){
		printf("[ext2fs_close] Error number: %ld\n", err);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
