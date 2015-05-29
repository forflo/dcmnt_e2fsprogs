#include <ext2fs/ext2fs.h>
#include <ext2fs/ext2_fs.h>
#include <stdio.h>
#include <stdlib.h>
#include <et/com_err.h>
#include <stdint.h>

static const char DEV[] = "/dev/loop0p1";
/* Muss immer angepasst werden */
static const int INODE = 20;

int main(int argc, char *argv[]){
	errcode_t err;
	struct struct_ext2_filsys *fs;
    struct ext2_inode inode;

	err = ext2fs_open(DEV, EXT2_FLAG_RW, 0, 0, unix_io_manager, &fs);
	if (err){
		if (err == 13) {
			printf("[ext2fs_open] Insufficient permissions\n");
		} else {
			printf("[ext2fs_open] Error number: %ld\n", err);
		}
		return EXIT_FAILURE;
	}

    err = ext2fs_read_inode(fs, INODE, &inode); 
    if (err){
        printf("[ext2fs_read_inode] Could not read inode %d\n", INODE);
        return EXIT_FAILURE;
    }

    printf("User-ID: %d\n", inode.i_uid);
    printf("Modifikationsdatum: %d\n", inode.i_mtime);
    printf("Zugriffsdatum: %d\n", inode.i_atime);
    printf("Berechtigungen: %o\n", inode.i_mode);
    printf("Anzahl der Blöcke: %d\n", inode.i_blocks);

	err = ext2fs_close(fs);
	if (err){
		printf("[ext2fs_close] Error number: %ld\n", err);
		return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}
