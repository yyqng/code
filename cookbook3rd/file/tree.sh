#cd /var/log
find . -exec sh -c 'echo -n {} | tr -d "[:alnum:]_.\-" | \
        tr "/" " "; basename {}' \;
