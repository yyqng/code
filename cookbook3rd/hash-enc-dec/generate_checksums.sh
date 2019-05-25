#/bin/bash
#filename: generate_checksums.sh

start=$(date +%s)
PIDARRAY=()
#    for file in linux.x64_11gR2_database.zip win64_11gR2_database.zip
    for file in File1.iso File2.iso
    do
        md5sum $file &
        echo $!
        PIDARRAY+=("$!")
    done
wait ${PIDARRAY[@]}
end=$(date +%s)
t=$((end -start))
echo takes $t seconds

start=$(date +%s)
#md5sum linux.x64_11gR2_database.zip win64_11gR2_database.zip
md5sum File1.iso File2.iso
end=$(date +%s)
t=$((end -start))
echo takes $t seconds
