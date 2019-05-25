myrename()
{
    local count=1
    for img in `find . -iname '*.jpg' -type f -maxdepth 1`
    do
        new=image-$count.${img##*.}
        echo "Renameing $img to $new"
        mv "$img" "$new"
        let count++
    done
}

#rename *.jpg *.JPG  ####wrong
#ls
#rename *.JPG *.jpg
#ls
