#!/bin/bash
# backup.sh
# Backup files with suffix. Do not backup temp files that start with ~
backup()
{
    read -p " What folder should be backed up:" folder
    read -p " What type of files should be backed up: " suffix
    find $folder -name "*.$suffix" -a ! -name '~*' 
    find $folder -name "*.$suffix" -a ! -name '~*' -exec cp {} /tmp/$folder \;
    echo "Backed up files from $folder  to /tmp/$folder"
}

folder=rename
suffix=jpg
#echo -e "$folder\n$suffix\n" | backup
backup < input.data
ls -al $folder
ls -al /tmp/$folder
