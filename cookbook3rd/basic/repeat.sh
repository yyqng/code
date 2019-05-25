repeat()
{
 while true ####/bin/true
 do
 $@ && return
 sleep 1
 done
}

repeat ls

repeat2()
{
 while :;
 do
 $@ && return
 sleep 1
 done
}

repeat2 lsss
