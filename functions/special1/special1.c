  
#include "special1.h"
/* one to copy from the normal filesystem to your filesystem */
/* command = "special2 sourceFile linuxDestinationFile" */

int special1(struct filesystem_volume volume, struct arguments command) {
    ssize_t returnSource

    /* check if command.argc != 2 */
    if(command.argc < 4) {
        printf("***Not Enough Args***\n");
        return 0; // check
    }
    else if(command.argc > 4) {
	    printf("***TOO many Args***\n");
	    return 0; //check
    }

    char* sourceFile = command.args[1];
    char* ourFileName = command.args[2];
    char* ourFileDirectory = command.args[3];

    // how many blocks the file is 
    int blockSize;

    // declare stat variable
    struct stat st; 

    // a new File is created using the touch command, with the name and directory coming from args
    createFile(ourFileName, ourFileDirectory);

    // get index of new file created
    fileIndex = getIndex(ourFileName);

    // get file size of the file we want to copy 
    /* http://man7.org/linux/man-pages/man2/stat.2.html */
    if(stat(file_name,&st) == 0)
        // st_blocks - Number of 512B blocks allocated
        // st_size - Total size, in bytes *might be needed instead for the read function*
        blockSize = st.st_blocks;
    else {
        printf("***ERROR UNABLE TO RETRIEVE SIZE***");
        return 0;
    }

    // find empty LBA
    int freeLBAIndex = getNextEmptyLBA(volume);

    // open linux file
    int linuxFile = open(sourceFile, O_RDONLY);

    // read linux file *need to make sure this dumps contents of file into returnSource*
    returnSource = read(linuxFile, 'need a buffer', 'size of file')

    // write buffer back to the LBA
    LBAwrite('same buffer', blockSize, freeLBAIndex);

    // add freeLBAIndex as child to new file
    addChild(freeLBAIndex, fileIndex, volume);

    // free mallocs
 

    printf("File successfuly copied from LINUX to Filesystem");
    return 1;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Open Linux File 
    //int linuxFile = open(linuxFile, O_RDONLY);
    // Open Destination File
    //int DSFile = open(destinationFile, O_WRONLY | O_CREAT, 0644);
    //negative value is returned, then there was an error opening the file
   // if(linuxFile < 0){
//	printf("***ERROR CANNOT OPEN FILE***");
      //  return 0;
   // }
   // if(linuxFile > 0){
   // 	printf("*OPENING THE FILE*");
	//FILE* newFile;
	//newFile = fopen(comman.args[1], "r");
	//if(newFile == NULL)
    //	{
        /* File not created hence exit */
      //  printf("***UNABLE TO CREATE FILE.***\n");
       // return 0;
    //	}
	//else if(newFile != NULL){
//	printf("***CREATING FILE***\n")	
	//	while((returnSource = read (linuxFile, &buffer, BUF_SIZE)) > 0){
            	//	returnDestination = write (DSFile, &buffer, (ssize_t) returnSource);
            	//	if(returnDestination != returnSource){
                	/* Write error */
                //	perror("***FILE DO NOT MATCH***");
                //	return 4;
            	//	}
   	//	}
//	}
	
//	return 1;
 //   }
 //   returnSource = read(linuxFile,&buffer,BUF_SIZE));

  //  if(returnSource < 1)

//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 
[0] command -done
[1] local file path (linux) -done
[2] our file name -done
[3] file directory -done

1. create new file --> createFile(...) -done
2. get index of new file --> fileIndex = getIndex(...) -done
3. get file size of the file we want to copy -done
4. find empty LBA --> emptyLBAIndex -done
5. read blockSize # of bytes from linux file --> copyBuffer = malloc(blocksize) {this line might not be needed}
                                             --> FILE file = open(command.args[1])
                                             --> copyBuffer = file.readNbytes(blockSize);
6. write buffer back to the LBA --> LBAwrite(copyBuffer, 1, emptyLBAIndex) -
7. add emptyLBAIndex as child to new file --> addChild(emptyLBAIndex, fileIndex, volume); -
8. free(mallocs)...
NOTE: I would write a function in structs called addBody(fileIndex, blockSize, linuxFileSize) --> adds a body to a file
						 addBody(230, 512, 1024) --> for(2 LBAs) 
						 				--> find free block
						 				--> write linux buffer to LBA
										--> addChild to fileIndex
						                         	
*/